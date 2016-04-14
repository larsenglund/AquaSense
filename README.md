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
Thanks to https://donatstudios.com/CsvToMarkdownTable

| What                                                               | Notes   | Why                                | QTY | Price per piece (USD) | Total price (USD) |
| ------------------------------------------------------------------ | ------- | ---------------------------------- | --- | --------------------- | ----------------- |
| ESP8266 (nodemcu v3 eller witty)                                   |         |                                    | 1   | 3.2                   | 3.2               |
| 5V boost                                                           |         |                                    | 1   | 0.51                  | 0.51              |
| DHT11                                                              |         | Intern fukt & temp                 | 2   | 0.71                  | 1.42              |
| DS18b20 stainless                                                  | onewire | Vattentemp vid ca 10cm och ca 90cm | 2   | 1.1                   | 2.2               |
| MMA8451                                                            | i2c     | Våghöjd                            | 1   | 1.81                  | 1.81              |
| TSL2561 (BH1750 är billigare)                                      | i2c     | Siktdjup                           | 2   | 1.75                  | 3.5               |
| SIM800L                                                            | UART    | Internet                           | 1   | 4.78                  | 4.78              |
| Solar power bank                                                   |         | Ström                              | 1   | 9.28                  | 9.28              |
| Waterproof clear box 158x90x60mm                                   |         | Ytlåda                             | 1   | 4.42                  | 4.42              |
| Waterproof clear box 85x58x33mm                                    |         | UV-låda                            | 1   | 1.87                  | 1.87              |
| Gängstång 1m 10mm, vinkeljärn, bultar & muttrar, buntband, silikon |         |                                    | 1   | 10                    | 10                |
| MOSFET, transistorer, resistorer, kondensatorer, PCB, kablar       |         |                                    | 1   | 4                     | 4                 |
|                                                                    |         |                                    |     |                       |                   |
| Sum (USD)                                                          |         |                                    |     |                       | 43.28             |
|                                                                    |         |                                    |     |                       |                   |
| Sum (SEK)                                                          |         | 1 usd in sek                       | 8.2 |                       | 354.896           |

### KiCad
ESP schematic and footprint from https://github.com/jdunmire/kicad-ESP8266

## Testing
Easy way to start a TCP server for testing: netcat -l 5416

Easy way to serve static files for testing: http-server -p 5417 (node.js)
