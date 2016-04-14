# AquaSense
AquaSense water sensor. Reports water temperature, water visibility and waves/wind through GPRS to a node.js server that presents some nice "realtime" graphs and allows users to receive alarms when certain water conditions are met. 
The sensor firmware can be updated through WiFi by going within range of the sensor with a smartphone turn on a hotspot with a specific name and password. At the next wakeup the sensor will use the wifi to connect to the update server and download the new firmware. This could ofcourse be done over GPRS but thats not implemented.
Feel free to fork and add more features :)


## Mobile data

### For Swedes
Comviq kontant tankat med 100kr räcker i 12mån och data kostar 0.35kr/MB vilket ger ca 285MB/år, dvs ca 23.75MB/mån.
Skickar vi data 1 gång per 15min så kan vi skicka 8100bytes varje gång.

### For the rest of the world
Use Konekt global sim and modify the code to send a binary struct of the data instead of JSON to keep the amount of data as low as possible.


## Hardware
Vad | Info | Varför | Antal | Styckpris
--- | --- | --- | --- | ---
DHT11||Intern fukt & temp|2|US $0.71 / piece
DS18b20 stainless|onewire|Vattentemp vid ca 10cm och ca 90cm|2|US $1.10 / piece
MMA8451|i2c|Våghöjd|1|US $1.81 / piece
TSL2561 (BH1750 är billigare)|i2c|Siktdjup|2|US $1.75 / piece
SIM800L|UART|Internet|1|US $4.78 / piece
Solar power bank||Ström|1|US $9.28 / piece
Waterproof clear box 158x90x60mm||Ytlåda|1|US $4.42 / piece
Waterproof clear box 85x58x33mm||UV-låda|1|US $1.87 / piece
Gängstång 1m 10mm, vinkeljärn, bultar & muttrar, buntband, silikon||||~ US $10
MOSFET, transistorer, resistorer, kondensatorer, PCB, kablar||||~ US $4
ESP8266 (nodemcu v3 eller witty)|||1|~ US $3.2
5V boost|||1|US $0.51 / piece

### KiCad
ESP schematic and footprint from https://github.com/jdunmire/kicad-ESP8266

## Testing
Easy way to start a TCP server for testing: netcat -l 5416

Easy way to serve static files for testing: http-server -p 5417 (node.js)
