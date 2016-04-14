/*
  AquaSense
 */
#include <ESP8266WiFi.h>
#include <ESP8266httpUpdate.h>
#include <GPRS_Shield_Arduino.h>  // (modified) SIM800 library: https://github.com/Seeed-Studio/GPRS_SIM900
#include <SoftwareSerial.h>
#include <stdio.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>    // Dallas DS18B20 library: https://github.com/milesburton/Arduino-Temperature-Control-Library
#include <DHT.h>                  // DHT library: https://github.com/adafruit/DHT-sensor-library
#include <TSL2561.h>              // (modified) TSL2561 library: https://github.com/adafruit/TSL2561-Arduino-Library
#include <MMA845XQ.h>             // MMA845XQ Library https://github.com/akafugu/MMA845XQ


#define USE_SERIAL        Serial
#define DEBUG_BAUDRATE    9600
#define MOSFET_POWER_PIN  15
#define PIN_TX            0 //13 //8 //grå
#define PIN_RX            2 //12 //7 //grön
//#define LED_PIN           2
#define GPRS_BAUDRATE     9600
#define APN_STR           F("internet.tele2.se") // Using Comviq kontant we can send about 2700 bytes every 5 minutes for 100kr/yr
#define GPRS_TIMEOUT      30000
#define ONE_WIRE_BUS      12
#define DALLAS_PRECISION  9
#define DHT_ABOVE_PIN     13
#define DHT_BELOW_PIN     14
#define DHT_TYPE          DHT11
#define SDA_PIN           4 // grön
#define SCL_PIN           5 // gul


struct AccelExtremes {
  float xmax;
  float xmin;
  float ymax;
  float ymin;
  float zmax;
  float zmin;
};


const char* aquasense_version   = "aquasense_1.0.1";
const char* ssid                = "aquasense";
const char* password            = "englunds";
uint32_t loopCounter            = 0;
uint32_t sleepCounter           = 0;
char buffer[512];
GPRS gprs(PIN_TX, PIN_RX, GPRS_BAUDRATE);
OneWire oneWire(ONE_WIRE_BUS); // Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
DallasTemperature dallasSensors(&oneWire); // Pass our oneWire reference to Dallas Temperature. 
DeviceAddress aboveThermometer, belowThermometer;
DHT dhtAbove(DHT_ABOVE_PIN, DHT_TYPE);
DHT dhtBelow(DHT_BELOW_PIN, DHT_TYPE);
TSL2561 tslAbove(TSL2561_ADDR_FLOAT);
TSL2561 tslBelow(TSL2561_ADDR_LOW);
MMA845XQ accel;
uint16_t lux_H, lux_L;
uint16_t ir_H, ir_L, full_H, full_L;
int it_H, it_L, ih_H, ih_L;
int wt_H, wt_L; // multiplied by 100
int wx, wy, wz; // multiplied by 10000
bool gprs_failed = false;


void gprsConnectAndSend() {
  Serial.println("gprsConnectAndSend()");
  //delay(1000); // TODO: remove this maybe?

  gprs_failed = false;
  uint32_t timout_time = millis() + GPRS_TIMEOUT;
  
  while (!gprs.init()) {
      delay(1000);
      if (millis() > timout_time) {
        Serial.println("gprs timeout, skipping");
        gprs_failed = true;
        return;
      }
      Serial.println(F("gprs init error"));
  }
  Serial.println(F("gprs init ok"));
  delay(1000);    

  while (!gprs.join(APN_STR)) { // attempt DHCP
      Serial.println(F("gprs join network error"));
      if (millis() > timout_time) {
        Serial.println("gprs timeout, skipping");
        gprs_failed = true;
        return;
      }
      delay(1000);
  }
  //Serial.print(F("gprs IP address is "));
  //Serial.println(gprs.getIPAddress());
  
  if (gprs.connect(TCP, "englund.asuscomm.com", 5416, 15)) {
    Serial.println(F("gprs connect success"));
  }
  else {
    Serial.println(F("gprs connect error"));
  }

  Serial.print(F("gprs sending data: "));
  uint32_t milli = millis();
  float batt = analogRead(A0);
  float vbatt = ((batt/1024 * 1.0) * 0.97) * (21.93+6.77)/6.77; // Uses pre-measures voltage and resistance
  char str_temp[6];
  dtostrf(vbatt, 4, 2, str_temp);
  // {v:"0.1.0",m:123456,b:12345,iah:83,iat:33,ibh:85,ibt:15,at:25,bt:12,al:123456,bl:123456,w:123456}
  sprintf(buffer, "{version:\"%s\",millis:%ul,batt:%s,ihh:%d,ihl:%d,ith:%d,itl:%d,luxh:%d,luxl:%d,irh:%d,irl:%d,fh:%d,fl:%d,wth:%d,wtl:%d,wx:%d,wy:%d,wz:%d}\n", aquasense_version, milli, str_temp, ih_H, ih_L, it_H, it_L, lux_H, lux_L, ir_H, ir_L, full_H, full_L, wt_H, wt_L, wx, wy, wz);
  Serial.println(buffer);
  gprs.send(buffer, strlen(buffer)-1);

  /*Serial.println(F("gprs waiting for response.."));
  while (true) {
    int ret = gprs.recv(buffer, sizeof(buffer)-1);
    if (ret <= 0){
        Serial.println(F("gprs done waiting for data"));
        break; 
    }
    buffer[ret] = '\0';
    Serial.print(F("gprs recv: "));
    Serial.print(ret);
    Serial.print(F(" bytes: "));
    Serial.println(buffer);
  }*/

  Serial.println(F("gprs close and leave network"));
  gprs.close();
  gprs.disconnect();
  //gprs.powerOff(); // Causes arduino reset :(
}

// function to print a device address
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    // zero pad the address if necessary
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

void readSensors() {
  Serial.println("readSensors()");


  // Sample accelerometer for 3 seconds and perform fft, send buckets and maxmin
  Serial.println("accelerometer (waves)");
  Wire.begin(SDA_PIN, SCL_PIN);
  accel.begin(true, 8);
  AccelExtremes accel_extremes;
  Serial.println("X,\tY,\tZ,\tRho,\tPhi,\tTheta");
  accel.update();
  accel_extremes.xmax = accel_extremes.xmin = accel.getX();
  accel_extremes.ymax = accel_extremes.ymin = accel.getY();
  accel_extremes.zmax = accel_extremes.zmin = accel.getZ();
  uint32_t ts_start = millis();
  for (int n=0;n<500;n++) {
    accel.update();
    if (accel.getX() > accel_extremes.xmax) accel_extremes.xmax = accel.getX();
    if (accel.getX() < accel_extremes.xmin) accel_extremes.xmin = accel.getX();
    if (accel.getY() > accel_extremes.ymax) accel_extremes.ymax = accel.getY();
    if (accel.getY() < accel_extremes.ymin) accel_extremes.ymin = accel.getY();
    if (accel.getZ() > accel_extremes.zmax) accel_extremes.zmax = accel.getZ();
    if (accel.getZ() < accel_extremes.zmin) accel_extremes.zmin = accel.getZ();
    /*Serial.print(accel.getX());
    Serial.print(" , ");
    Serial.print(accel.getY());
    Serial.print(", ");
    Serial.print(accel.getZ());
    Serial.print(", ");
    Serial.print(accel.getRho());
    Serial.print(", ");
    Serial.print(accel.getPhi());
    Serial.print(", ");
    Serial.print(accel.getTheta());
    Serial.println();*/
    delay(10);
  }
  wx = (int)((accel_extremes.xmax - accel_extremes.xmin)*10000);
  wy = (int)((accel_extremes.ymax - accel_extremes.ymin)*10000);
  wz = (int)((accel_extremes.zmax - accel_extremes.zmin)*10000);
  Serial.println(wx);
  Serial.println(wy);
  Serial.println(wz);
  Serial.println(millis()-ts_start);

  
  // Sample internal humiture x 2 (dht11)
  Serial.println("internal humiture");
  dhtAbove.begin();
  dhtBelow.begin();
  ih_H = dhtAbove.readHumidity();
  it_H = dhtAbove.readTemperature(); // Read temperature as Celsius (the default)
  ih_L = dhtBelow.readHumidity();
  it_L = dhtBelow.readTemperature(); // Read temperature as Celsius (the default)
  if (isnan(ih_H) || isnan(it_H) || isnan(ih_L) || isnan(it_L)) {
    Serial.println("Failed to read from DHT sensors!");
  }
  Serial.printf("Above: %d, %d  Below: %d, %d\n", ih_H, it_H, ih_L, it_L);


  // Sample water temperature x 2 (ds18b20)
  Serial.println("water temperature");
  dallasSensors.begin();
  
  // locate devices on the bus
  Serial.print("Locating devices...");
  Serial.print("Found ");
  Serial.print(dallasSensors.getDeviceCount(), DEC);
  Serial.println(" devices.");

  if (!dallasSensors.getAddress(aboveThermometer, 0)) Serial.println("Unable to find address for Device 0"); 
  if (!dallasSensors.getAddress(belowThermometer, 1)) Serial.println("Unable to find address for Device 1"); 
  Serial.print("Device 0 Address: ");
  printAddress(aboveThermometer);
  Serial.println();
  Serial.print("Device 1 Address: ");
  printAddress(belowThermometer);
  Serial.println();
  
/*  dallasSensors.setResolution(aboveThermometer, DALLAS_PRECISION);
  Serial.print("Device 0 Resolution: ");
  Serial.print(dallasSensors.getResolution(aboveThermometer), DEC); 
  Serial.println();*/

  dallasSensors.requestTemperatures();
  
  float waterTempAbove = dallasSensors.getTempC(aboveThermometer);
  wt_H = (int)(waterTempAbove*100);
  Serial.print("Device 0 temp C: ");
  Serial.println(waterTempAbove);
  float waterTempBelow = dallasSensors.getTempC(belowThermometer);
  wt_L = (int)(waterTempBelow*100);
  Serial.print("Device 1 temp C: ");
  Serial.println(waterTempBelow);


  // Sample lux x 2 (water transparency) (TSL2561)
  Serial.println("water transparency");
  if (tslAbove.begin(SDA_PIN, SCL_PIN)) {
    Serial.println("Found TSL2561 sensor");
  } else {
    Serial.println("No TSL2561 sensor?");
  }
  // You can change the gain on the fly, to adapt to brighter/dimmer light situations
  //tsl.setGain(TSL2561_GAIN_0X);         // set no gain (for bright situtations)
  tslAbove.setGain(TSL2561_GAIN_16X);      // set 16x gain (for dim situations)
  
  // Changing the integration time gives you a longer time over which to sense light
  // longer timelines are slower, but are good in very low light situtations!
  tslAbove.setTiming(TSL2561_INTEGRATIONTIME_13MS);  // shortest integration time (bright light)
  //tsl.setTiming(TSL2561_INTEGRATIONTIME_101MS);  // medium integration time (medium light)
  //tsl.setTiming(TSL2561_INTEGRATIONTIME_402MS);  // longest integration time (dim light)

  // More advanced data read example. Read 32 bits with top 16 bits IR, bottom 16 bits full spectrum
  // That way you can do whatever math and comparisons you want!
  uint32_t lum = tslAbove.getFullLuminosity();
  //uint16_t ir, full;
  ir_H = lum >> 16;
  full_H = lum & 0xFFFF;
  Serial.print("IR: "); Serial.print(ir_H);   Serial.print("\t\t");
  Serial.print("Full: "); Serial.print(full_H);   Serial.print("\t");
  Serial.print("Visible: "); Serial.print(full_H - ir_H);   Serial.print("\t");
  lux_H = tslAbove.calculateLux(full_H, ir_H);
  Serial.print("Lux: "); Serial.println(lux_H);

  if (tslBelow.begin(SDA_PIN, SCL_PIN)) {
    Serial.println("Found TSL2561 sensor");
  } else {
    Serial.println("No TSL2561 sensor?");
  }
  tslBelow.setGain(TSL2561_GAIN_16X);      // set 16x gain (for dim situations)
  tslBelow.setTiming(TSL2561_INTEGRATIONTIME_13MS);  // shortest integration time (bright light)
  lum = tslBelow.getFullLuminosity();
  ir_L = lum >> 16;
  full_L = lum & 0xFFFF;
  Serial.print("IR: "); Serial.print(ir_L);   Serial.print("\t\t");
  Serial.print("Full: "); Serial.print(full_L);   Serial.print("\t");
  Serial.print("Visible: "); Serial.print(full_L - ir_L);   Serial.print("\t");
  lux_L = tslAbove.calculateLux(full_L, ir_L);
  Serial.print("Lux: "); Serial.println(lux_L);
}


/*void blinkLed() {
  digitalWrite(2, LOW);   // Turn the LED on (Note that LOW is the voltage level
  delay(200);                      // Wait for a second
  digitalWrite(2, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(200);                      // Wait for two seconds (to demonstrate the active low LED)
}*/


void setup() {
  pinMode(MOSFET_POWER_PIN, OUTPUT);
  digitalWrite(MOSFET_POWER_PIN, LOW);
  //pinMode(LED_PIN, OUTPUT);
  //digitalWrite(LED_PIN, LOW);

  Serial.begin(DEBUG_BAUDRATE);
  Serial.println(ESP.getResetReason());
  Serial.println(ESP.getResetInfo());
  Serial.print("AquaSense version: ");
  Serial.println(aquasense_version);

  Serial.print("Connecting to ssid ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  int n=12;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (n-- < 0) break;
  }
  Serial.println("");
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    Serial.println("Downloading update..");
    t_httpUpdate_return ret = ESPhttpUpdate.update("englund.asuscomm.com", 5417, "/aquasense.bin", aquasense_version);
    switch(ret) {
        case HTTP_UPDATE_FAILED:
            USE_SERIAL.printf("HTTP_UPDATE_FAILD Error (%d): %s\n", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
            break;

        case HTTP_UPDATE_NO_UPDATES:
            USE_SERIAL.println("HTTP_UPDATE_NO_UPDATES");
            break;

        case HTTP_UPDATE_OK:
            USE_SERIAL.println("HTTP_UPDATE_OK");
            break;
    }
  }
  else {
    Serial.println("Accesspoint not available");
  }

  WiFi.disconnect(); 
  WiFi.mode(WIFI_OFF);
  WiFi.forceSleepBegin();
  delay(1);

  //blinkLed();
}


void loop() {
  // Power on sensors and gprs module using MOSFET
  Serial.println(F("mosfet power on"));
  digitalWrite(MOSFET_POWER_PIN, HIGH); // Turn on MOSFET (sensors and gprs)
  delay(100); // Wait a bit for things to power on, might not be needed
  
  readSensors();
  gprsConnectAndSend();
  
  Serial.println(F("mosfet power off"));
  digitalWrite(MOSFET_POWER_PIN, LOW); // Turn off MOSFET (sensors and gprs)
  
  //blinkLed();blinkLed();
  //ESP.deepSleep(10*1000*1000, WAKE_RF_DEFAULT);//, WAKE_RF_DISABLED);
  if (gprs_failed) { // only sleep 1 min if gprs failed
    Serial.println("deepsleep for 1 min");
    Serial.flush();
    ESP.deepSleep(1*60*1000*1000, WAKE_RF_DEFAULT);//, WAKE_RF_DISABLED);
  }
  else {
    Serial.println("deepsleep for 10 min");
    Serial.flush();
    ESP.deepSleep(10*60*1000*1000, WAKE_RF_DEFAULT);//, WAKE_RF_DISABLED);
  }
}

