EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:ESP8266
LIBS:sim800l
LIBS:gottochblandat
LIBS:5v_boost
LIBS:aquasense-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Q_NPN_CBE Q1
U 1 1 570F2D5F
P 1900 2700
F 0 "Q1" H 2200 2750 50  0000 R CNN
F 1 "Q_NPN_CBE" H 2500 2650 50  0000 R CNN
F 2 "" H 2100 2800 50  0000 C CNN
F 3 "" H 1900 2700 50  0000 C CNN
	1    1900 2700
	1    0    0    -1  
$EndComp
$Comp
L Q_NPN_CBE Q2
U 1 1 570F2D8A
P 2300 1950
F 0 "Q2" H 2600 2000 50  0000 R CNN
F 1 "Q_NPN_CBE" H 2900 1900 50  0000 R CNN
F 2 "" H 2500 2050 50  0000 C CNN
F 3 "" H 2300 1950 50  0000 C CNN
	1    2300 1950
	1    0    0    -1  
$EndComp
$Comp
L ESP-12E U1
U 1 1 570F2EA6
P 4650 4550
F 0 "U1" H 4650 4450 50  0000 C CNN
F 1 "ESP-12E" H 4650 4650 50  0000 C CNN
F 2 "" H 4650 4550 50  0001 C CNN
F 3 "" H 4650 4550 50  0001 C CNN
	1    4650 4550
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 570F2FC4
P 1550 2700
F 0 "R2" V 1630 2700 50  0000 C CNN
F 1 "10K" V 1550 2700 50  0000 C CNN
F 2 "" V 1480 2700 50  0000 C CNN
F 3 "" H 1550 2700 50  0000 C CNN
	1    1550 2700
	0    1    1    0   
$EndComp
Text GLabel 1300 2700 0    55   Input ~ 0
GPIO15
$Comp
L R R1
U 1 1 570F308D
P 1350 2500
F 0 "R1" V 1430 2500 50  0000 C CNN
F 1 "10K" V 1350 2500 50  0000 C CNN
F 2 "" V 1280 2500 50  0000 C CNN
F 3 "" H 1350 2500 50  0000 C CNN
	1    1350 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 2700 1400 2700
Wire Wire Line
	1350 2700 1350 2650
Connection ~ 1350 2700
Wire Wire Line
	2100 1950 2000 1950
Wire Wire Line
	2000 1950 2000 2500
$Comp
L R R3
U 1 1 570F3282
P 1850 1950
F 0 "R3" V 1930 1950 50  0000 C CNN
F 1 "10K" V 1850 1950 50  0000 C CNN
F 2 "" V 1780 1950 50  0000 C CNN
F 3 "" H 1850 1950 50  0000 C CNN
	1    1850 1950
	0    1    1    0   
$EndComp
$Comp
L +BATT #PWR2
U 1 1 570F32B9
P 1700 1950
F 0 "#PWR2" H 1700 1800 50  0001 C CNN
F 1 "+BATT" H 1700 2090 50  0000 C CNN
F 2 "" H 1700 1950 50  0000 C CNN
F 3 "" H 1700 1950 50  0000 C CNN
	1    1700 1950
	1    0    0    -1  
$EndComp
$Comp
L IRF540N Q3
U 1 1 570F32EA
P 2700 1150
F 0 "Q3" H 2950 1225 50  0000 L CNN
F 1 "IRF540N" H 2950 1150 50  0000 L CNN
F 2 "TO-220" H 2950 1075 50  0000 L CIN
F 3 "" H 2700 1150 50  0000 L CNN
	1    2700 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 1200 2400 1200
Wire Wire Line
	2400 1200 2400 1750
$Comp
L R R4
U 1 1 570F3434
P 2250 1200
F 0 "R4" V 2330 1200 50  0000 C CNN
F 1 "10K" V 2250 1200 50  0000 C CNN
F 2 "" V 2180 1200 50  0000 C CNN
F 3 "" H 2250 1200 50  0000 C CNN
	1    2250 1200
	0    1    1    0   
$EndComp
$Comp
L +5V #PWR4
U 1 1 570F347A
P 2100 1200
F 0 "#PWR4" H 2100 1050 50  0001 C CNN
F 1 "+5V" H 2100 1340 50  0000 C CNN
F 2 "" H 2100 1200 50  0000 C CNN
F 3 "" H 2100 1200 50  0000 C CNN
	1    2100 1200
	1    0    0    -1  
$EndComp
Text GLabel 2750 850  0    55   Input ~ 0
MOSFET_DRAIN
Wire Wire Line
	2800 950  2800 850 
Wire Wire Line
	2800 850  2750 850 
$Comp
L GND #PWR3
U 1 1 570F3585
P 2000 2900
F 0 "#PWR3" H 2000 2650 50  0001 C CNN
F 1 "GND" H 2000 2750 50  0000 C CNN
F 2 "" H 2000 2900 50  0000 C CNN
F 3 "" H 2000 2900 50  0000 C CNN
	1    2000 2900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR5
U 1 1 570F35A9
P 2400 2150
F 0 "#PWR5" H 2400 1900 50  0001 C CNN
F 1 "GND" H 2400 2000 50  0000 C CNN
F 2 "" H 2400 2150 50  0000 C CNN
F 3 "" H 2400 2150 50  0000 C CNN
	1    2400 2150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR6
U 1 1 570F35CD
P 2800 1350
F 0 "#PWR6" H 2800 1100 50  0001 C CNN
F 1 "GND" H 2800 1200 50  0000 C CNN
F 2 "" H 2800 1350 50  0000 C CNN
F 3 "" H 2800 1350 50  0000 C CNN
	1    2800 1350
	1    0    0    -1  
$EndComp
$Comp
L SIM800L S1
U 1 1 570F38E7
P 7750 2900
F 0 "S1" H 7750 2000 55  0000 C CNN
F 1 "SIM800L" H 7750 2900 55  0000 C CNN
F 2 "" H 7750 2900 55  0000 C CNN
F 3 "" H 7750 2900 55  0000 C CNN
	1    7750 2900
	1    0    0    -1  
$EndComp
$Comp
L +BATT #PWR11
U 1 1 570F3CAE
P 7100 2900
F 0 "#PWR11" H 7100 2750 50  0001 C CNN
F 1 "+BATT" H 7100 3040 50  0000 C CNN
F 2 "" H 7100 2900 50  0000 C CNN
F 3 "" H 7100 2900 50  0000 C CNN
	1    7100 2900
	1    0    0    -1  
$EndComp
$Comp
L R R7
U 1 1 570F3D82
P 7000 3100
F 0 "R7" V 7080 3100 50  0000 C CNN
F 1 "10K" V 7000 3100 50  0000 C CNN
F 2 "" V 6930 3100 50  0000 C CNN
F 3 "" H 7000 3100 50  0000 C CNN
	1    7000 3100
	-1   0    0    1   
$EndComp
Wire Wire Line
	7100 2900 7100 3150
Wire Wire Line
	7100 3150 7300 3150
Wire Wire Line
	7300 3250 7000 3250
Wire Wire Line
	7000 2950 7100 2950
Connection ~ 7100 2950
Text GLabel 7300 3350 0    55   Input ~ 0
GPIO2
Text GLabel 7300 3450 0    55   Input ~ 0
GPIO0
Text GLabel 7300 3550 0    55   Input ~ 0
MOSFET_DRAIN
$Comp
L GND #PWR1
U 1 1 570F443E
P 1150 2350
F 0 "#PWR1" H 1150 2100 50  0001 C CNN
F 1 "GND" H 1150 2200 50  0000 C CNN
F 2 "" H 1150 2350 50  0000 C CNN
F 3 "" H 1150 2350 50  0000 C CNN
	1    1150 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	1350 2350 1350 2300
Wire Wire Line
	1350 2300 1150 2300
Wire Wire Line
	1150 2300 1150 2350
$Comp
L AP2112K-3.3TRG1 LDO1
U 1 1 570F48C1
P 5300 1300
F 0 "LDO1" H 5350 800 60  0000 C CNN
F 1 "AP2112K-3.3TRG1" H 5350 1300 60  0000 C CNN
F 2 "" H 5300 1300 60  0000 C CNN
F 3 "" H 5300 1300 60  0000 C CNN
	1    5300 1300
	1    0    0    -1  
$EndComp
$Comp
L 5V_boost U2
U 1 1 570F4AF7
P 7600 1300
F 0 "U2" H 7650 800 55  0000 C CNN
F 1 "5V_boost" H 7600 1300 55  0000 C CNN
F 2 "" H 7600 1300 55  0000 C CNN
F 3 "" H 7600 1300 55  0000 C CNN
	1    7600 1300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR13
U 1 1 570F4DC4
P 7200 1650
F 0 "#PWR13" H 7200 1400 50  0001 C CNN
F 1 "GND" H 7200 1500 50  0000 C CNN
F 2 "" H 7200 1650 50  0000 C CNN
F 3 "" H 7200 1650 50  0000 C CNN
	1    7200 1650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR14
U 1 1 570F4E5C
P 8250 1350
F 0 "#PWR14" H 8250 1100 50  0001 C CNN
F 1 "GND" H 8250 1200 50  0000 C CNN
F 2 "" H 8250 1350 50  0000 C CNN
F 3 "" H 8250 1350 50  0000 C CNN
	1    8250 1350
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR15
U 1 1 570F4EA8
P 8250 1750
F 0 "#PWR15" H 8250 1600 50  0001 C CNN
F 1 "+5V" H 8250 1890 50  0000 C CNN
F 2 "" H 8250 1750 50  0000 C CNN
F 3 "" H 8250 1750 50  0000 C CNN
	1    8250 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	8250 1350 8250 1300
Wire Wire Line
	8250 1300 8050 1300
Wire Wire Line
	8050 1300 8050 1500
Wire Wire Line
	8050 1600 8050 1800
Wire Wire Line
	8050 1800 8250 1800
Wire Wire Line
	8250 1800 8250 1750
$Comp
L +BATT #PWR12
U 1 1 570F4FA7
P 7200 1450
F 0 "#PWR12" H 7200 1300 50  0001 C CNN
F 1 "+BATT" H 7200 1590 50  0000 C CNN
F 2 "" H 7200 1450 50  0000 C CNN
F 3 "" H 7200 1450 50  0000 C CNN
	1    7200 1450
	1    0    0    -1  
$EndComp
$Comp
L +BATT #PWR10
U 1 1 570F50C7
P 4450 1400
F 0 "#PWR10" H 4450 1250 50  0001 C CNN
F 1 "+BATT" H 4450 1540 50  0000 C CNN
F 2 "" H 4450 1400 50  0000 C CNN
F 3 "" H 4450 1400 50  0000 C CNN
	1    4450 1400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR9
U 1 1 570F50F3
P 4450 1850
F 0 "#PWR9" H 4450 1600 50  0001 C CNN
F 1 "GND" H 4450 1700 50  0000 C CNN
F 2 "" H 4450 1850 50  0000 C CNN
F 3 "" H 4450 1850 50  0000 C CNN
	1    4450 1850
	1    0    0    -1  
$EndComp
Text GLabel 3750 4750 0    55   Input ~ 0
OneWire
Text GLabel 5550 4450 2    55   Input ~ 0
SCL
Text GLabel 5550 4550 2    55   Input ~ 0
SDA
Text GLabel 3750 4850 0    55   Input ~ 0
DHT22_1
Text GLabel 3750 4650 0    55   Input ~ 0
DHT22_2
Wire Wire Line
	3750 4550 3650 4550
Wire Wire Line
	3650 4550 3650 4250
Wire Wire Line
	3650 4250 3750 4250
$Comp
L R R6
U 1 1 570F54B0
P 3200 4550
F 0 "R6" V 3280 4550 50  0000 C CNN
F 1 "6.8K" V 3200 4550 50  0000 C CNN
F 2 "" V 3130 4550 50  0000 C CNN
F 3 "" H 3200 4550 50  0000 C CNN
	1    3200 4550
	-1   0    0    1   
$EndComp
$Comp
L R R5
U 1 1 570F5564
P 3000 4350
F 0 "R5" V 3080 4350 50  0000 C CNN
F 1 "22K" V 3000 4350 50  0000 C CNN
F 2 "" V 2930 4350 50  0000 C CNN
F 3 "" H 3000 4350 50  0000 C CNN
	1    3000 4350
	0    1    1    0   
$EndComp
$Comp
L +BATT #PWR7
U 1 1 570F55E0
P 2850 4350
F 0 "#PWR7" H 2850 4200 50  0001 C CNN
F 1 "+BATT" H 2850 4490 50  0000 C CNN
F 2 "" H 2850 4350 50  0000 C CNN
F 3 "" H 2850 4350 50  0000 C CNN
	1    2850 4350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR8
U 1 1 570F5775
P 3200 4700
F 0 "#PWR8" H 3200 4450 50  0001 C CNN
F 1 "GND" H 3200 4550 50  0000 C CNN
F 2 "" H 3200 4700 50  0000 C CNN
F 3 "" H 3200 4700 50  0000 C CNN
	1    3200 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 4350 3750 4350
Wire Wire Line
	3200 4400 3200 4350
Connection ~ 3200 4350
$Comp
L R R?
U 1 1 570F5B5D
P 3500 4150
F 0 "R?" V 3580 4150 50  0000 C CNN
F 1 "10K" V 3500 4150 50  0000 C CNN
F 2 "" V 3430 4150 50  0000 C CNN
F 3 "" H 3500 4150 50  0000 C CNN
	1    3500 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 4300 3500 4450
Wire Wire Line
	3500 4450 3750 4450
$Comp
L +3.3V #PWR?
U 1 1 570F5CCB
P 3500 4000
F 0 "#PWR?" H 3500 3850 50  0001 C CNN
F 1 "+3.3V" H 3500 4140 50  0000 C CNN
F 2 "" H 3500 4000 50  0000 C CNN
F 3 "" H 3500 4000 50  0000 C CNN
	1    3500 4000
	1    0    0    -1  
$EndComp
$Comp
L C_Small C?
U 1 1 570F5FC1
P 4450 1650
F 0 "C?" H 4460 1720 50  0000 L CNN
F 1 "C_Small" H 4460 1570 50  0000 L CNN
F 2 "" H 4450 1650 50  0000 C CNN
F 3 "" H 4450 1650 50  0000 C CNN
	1    4450 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 1750 4450 1850
Wire Wire Line
	4450 1800 4700 1800
Wire Wire Line
	4700 1800 4700 1550
Wire Wire Line
	4700 1550 4850 1550
Connection ~ 4450 1800
Wire Wire Line
	4450 1400 4450 1550
Wire Wire Line
	4450 1450 4850 1450
Connection ~ 4450 1450
Wire Wire Line
	4850 1650 4800 1650
Wire Wire Line
	4800 1650 4800 1450
Connection ~ 4800 1450
NoConn ~ 5850 1650
$Comp
L C_Small C?
U 1 1 570F640E
P 6050 1650
F 0 "C?" H 6060 1720 50  0000 L CNN
F 1 "C_Small" H 6060 1570 50  0000 L CNN
F 2 "" H 6050 1650 50  0000 C CNN
F 3 "" H 6050 1650 50  0000 C CNN
	1    6050 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5850 1450 6050 1450
Wire Wire Line
	6050 1450 6050 1550
$Comp
L GND #PWR?
U 1 1 570F64A9
P 6050 1750
F 0 "#PWR?" H 6050 1500 50  0001 C CNN
F 1 "GND" H 6050 1600 50  0000 C CNN
F 2 "" H 6050 1750 50  0000 C CNN
F 3 "" H 6050 1750 50  0000 C CNN
	1    6050 1750
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR?
U 1 1 570F64DF
P 6050 1450
F 0 "#PWR?" H 6050 1300 50  0001 C CNN
F 1 "+3.3V" H 6050 1590 50  0000 C CNN
F 2 "" H 6050 1450 50  0000 C CNN
F 3 "" H 6050 1450 50  0000 C CNN
	1    6050 1450
	1    0    0    -1  
$EndComp
Text GLabel 5550 4650 2    55   Input ~ 0
GPIO0
Text GLabel 6150 4750 2    55   Input ~ 0
GPIO2
Text GLabel 5550 4850 2    55   Input ~ 0
GPIO15
$Comp
L GND #PWR?
U 1 1 570F6752
P 5550 5250
F 0 "#PWR?" H 5550 5000 50  0001 C CNN
F 1 "GND" H 5550 5100 50  0000 C CNN
F 2 "" H 5550 5250 50  0000 C CNN
F 3 "" H 5550 5250 50  0000 C CNN
	1    5550 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	5550 4750 6150 4750
Wire Wire Line
	5550 4950 5550 5250
$Comp
L R R?
U 1 1 570F6B23
P 6050 5000
F 0 "R?" V 6130 5000 50  0000 C CNN
F 1 "10K" V 6050 5000 50  0000 C CNN
F 2 "" V 5980 5000 50  0000 C CNN
F 3 "" H 6050 5000 50  0000 C CNN
	1    6050 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 4850 6050 4750
Connection ~ 6050 4750
Wire Wire Line
	6050 5150 5550 5150
Connection ~ 5550 5150
$Comp
L +3.3V #PWR?
U 1 1 570F6CE8
P 3500 5100
F 0 "#PWR?" H 3500 4950 50  0001 C CNN
F 1 "+3.3V" H 3500 5240 50  0000 C CNN
F 2 "" H 3500 5100 50  0000 C CNN
F 3 "" H 3500 5100 50  0000 C CNN
	1    3500 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 4950 3750 5100
Wire Wire Line
	3750 5100 3500 5100
NoConn ~ 8200 3150
NoConn ~ 8200 3250
NoConn ~ 8200 3350
NoConn ~ 8200 3450
NoConn ~ 8200 3550
NoConn ~ 8200 3650
$EndSCHEMATC
