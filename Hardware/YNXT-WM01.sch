EESchema Schematic File Version 4
EELAYER 30 0
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
L RF_Module:E18-MS1-PCB U4
U 1 1 629F7D04
P 5600 6350
F 0 "U4" H 5600 7331 50  0000 C CNN
F 1 "E18-MS1-PCB" H 5600 7240 50  0000 C CNN
F 2 "RF_Module:E18-MS1-PCB" H 5400 6550 50  0001 C CNN
F 3 "http://www.cdebyte.com/en/downpdf.aspx?id=122" H 5400 6550 50  0001 C CNN
	1    5600 6350
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW1
U 1 1 629FAF4A
P 3600 6450
F 0 "SW1" H 3600 6735 50  0000 C CNN
F 1 "SW_Push" H 3600 6644 50  0000 C CNN
F 2 "Button_Switch_SMD:SW_SPST_TL3342" H 3600 6650 50  0001 C CNN
F 3 "~" H 3600 6650 50  0001 C CNN
	1    3600 6450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR012
U 1 1 62A0C6DA
P 2900 2350
F 0 "#PWR012" H 2900 2100 50  0001 C CNN
F 1 "GND" H 2905 2177 50  0000 C CNN
F 2 "" H 2900 2350 50  0001 C CNN
F 3 "" H 2900 2350 50  0001 C CNN
	1    2900 2350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR020
U 1 1 62A0D0FC
P 5600 7300
F 0 "#PWR020" H 5600 7050 50  0001 C CNN
F 1 "GND" H 5605 7127 50  0000 C CNN
F 2 "" H 5600 7300 50  0001 C CNN
F 3 "" H 5600 7300 50  0001 C CNN
	1    5600 7300
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR019
U 1 1 62A0F18E
P 5600 5200
F 0 "#PWR019" H 5600 5050 50  0001 C CNN
F 1 "+3.3V" H 5615 5373 50  0000 C CNN
F 2 "" H 5600 5200 50  0001 C CNN
F 3 "" H 5600 5200 50  0001 C CNN
	1    5600 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 7050 5600 7300
$Comp
L power:+3.3V #PWR07
U 1 1 62A3D757
P 3200 5750
F 0 "#PWR07" H 3200 5600 50  0001 C CNN
F 1 "+3.3V" H 3215 5923 50  0000 C CNN
F 2 "" H 3200 5750 50  0001 C CNN
F 3 "" H 3200 5750 50  0001 C CNN
	1    3200 5750
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 62A4318B
P 3200 6150
F 0 "R1" H 3270 6196 50  0000 L CNN
F 1 "10k" H 3270 6105 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3130 6150 50  0001 C CNN
F 3 "~" H 3200 6150 50  0001 C CNN
	1    3200 6150
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 62A44144
P 3950 6800
F 0 "C2" H 4065 6846 50  0000 L CNN
F 1 "100nF" H 4065 6755 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3988 6650 50  0001 C CNN
F 3 "~" H 3950 6800 50  0001 C CNN
	1    3950 6800
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 5750 3200 6000
Wire Wire Line
	3800 6450 3950 6450
Connection ~ 3950 6450
Wire Wire Line
	3950 6650 3950 6450
$Comp
L power:GND #PWR010
U 1 1 62A479E1
P 3950 7200
F 0 "#PWR010" H 3950 6950 50  0001 C CNN
F 1 "GND" H 3955 7027 50  0000 C CNN
F 2 "" H 3950 7200 50  0001 C CNN
F 3 "" H 3950 7200 50  0001 C CNN
	1    3950 7200
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 6950 3950 7200
$Comp
L Device:C C3
U 1 1 62A56CC8
P 4200 5850
F 0 "C3" V 3950 5800 50  0000 L CNN
F 1 "100nF" V 4050 5750 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4238 5700 50  0001 C CNN
F 3 "~" H 4200 5850 50  0001 C CNN
	1    4200 5850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR016
U 1 1 62A59D11
P 4200 6050
F 0 "#PWR016" H 4200 5800 50  0001 C CNN
F 1 "GND" H 4205 5877 50  0000 C CNN
F 2 "" H 4200 6050 50  0001 C CNN
F 3 "" H 4200 6050 50  0001 C CNN
	1    4200 6050
	1    0    0    -1  
$EndComp
$Comp
L Device:R R6
U 1 1 62A5AB03
P 4200 5350
F 0 "R6" H 4270 5396 50  0000 L CNN
F 1 "1k" H 4270 5305 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4130 5350 50  0001 C CNN
F 3 "~" H 4200 5350 50  0001 C CNN
	1    4200 5350
	1    0    0    1   
$EndComp
Text Label 6450 6850 0    50   ~ 10
DC
$Comp
L Device:R R10
U 1 1 62A704CA
P 6900 6250
F 0 "R10" V 6800 6150 50  0000 L CNN
F 1 "1k" V 7000 6200 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6830 6250 50  0001 C CNN
F 3 "~" H 6900 6250 50  0001 C CNN
	1    6900 6250
	1    0    0    -1  
$EndComp
Wire Wire Line
	5100 6150 4600 6150
Wire Wire Line
	5100 6250 4600 6250
Wire Wire Line
	5100 6350 4600 6350
Text Label 4600 6150 0    50   ~ 10
CAPTURE0
Text Label 4600 6250 0    50   ~ 10
CAPTURE1
Text Label 4600 6350 0    50   ~ 10
CAPTURE2
$Comp
L Device:C C1
U 1 1 62A5B610
P 2050 1600
F 0 "C1" H 2165 1646 50  0000 L CNN
F 1 "1uF" H 2165 1555 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2088 1450 50  0001 C CNN
F 3 "~" H 2050 1600 50  0001 C CNN
	1    2050 1600
	-1   0    0    1   
$EndComp
$Comp
L Device:R R3
U 1 1 62A76634
P 2400 1550
F 0 "R3" H 2250 1600 50  0000 L CNN
F 1 "470" H 2200 1500 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2330 1550 50  0001 C CNN
F 3 "~" H 2400 1550 50  0001 C CNN
	1    2400 1550
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 62A7DD74
P 2400 2100
F 0 "R2" H 2470 2146 50  0000 L CNN
F 1 "1.5k" H 2470 2055 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2330 2100 50  0001 C CNN
F 3 "~" H 2400 2100 50  0001 C CNN
	1    2400 2100
	-1   0    0    1   
$EndComp
Wire Wire Line
	2400 1950 2400 1850
Wire Wire Line
	2400 1850 2500 1850
$Comp
L power:GND #PWR06
U 1 1 62AB405E
P 2050 2350
F 0 "#PWR06" H 2050 2100 50  0001 C CNN
F 1 "GND" H 2055 2177 50  0000 C CNN
F 2 "" H 2050 2350 50  0001 C CNN
F 3 "" H 2050 2350 50  0001 C CNN
	1    2050 2350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR03
U 1 1 62AE6DF1
P 1050 3750
F 0 "#PWR03" H 1050 3500 50  0001 C CNN
F 1 "GND" H 1055 3577 50  0000 C CNN
F 2 "" H 1050 3750 50  0001 C CNN
F 3 "" H 1050 3750 50  0001 C CNN
	1    1050 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	1050 3750 1050 3600
$Comp
L Regulator_Switching:NCP1529A U5
U 1 1 62AFAD2E
P 7950 1450
F 0 "U5" H 7950 1817 50  0000 C CNN
F 1 "STI3408B" H 7950 1726 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-5" H 8000 1200 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/NCP1529-D.PDF" H 7700 1900 50  0001 C CNN
	1    7950 1450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR023
U 1 1 62B042BE
P 7950 2100
F 0 "#PWR023" H 7950 1850 50  0001 C CNN
F 1 "GND" H 7955 1927 50  0000 C CNN
F 2 "" H 7950 2100 50  0001 C CNN
F 3 "" H 7950 2100 50  0001 C CNN
	1    7950 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	7650 1450 7550 1450
Connection ~ 7550 1450
$Comp
L pspice:INDUCTOR L1
U 1 1 62B33355
P 8600 1350
F 0 "L1" H 8600 1565 50  0000 C CNN
F 1 "2.2uH" H 8600 1474 50  0000 C CNN
F 2 "Inductor_SMD:CD43" H 8600 1350 50  0001 C CNN
F 3 "~" H 8600 1350 50  0001 C CNN
	1    8600 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	8250 1350 8350 1350
$Comp
L Device:R R12
U 1 1 62B3A188
P 8700 1450
F 0 "R12" V 8500 1400 50  0000 L CNN
F 1 "45.3k" V 8600 1350 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 8630 1450 50  0001 C CNN
F 3 "~" H 8700 1450 50  0001 C CNN
	1    8700 1450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8850 1450 9000 1450
Wire Wire Line
	9000 1450 9000 1350
Wire Wire Line
	9000 1350 8850 1350
Wire Wire Line
	8250 1450 8400 1450
Connection ~ 8400 1450
Wire Wire Line
	8400 1450 8550 1450
$Comp
L Device:C C6
U 1 1 62B516E3
P 9000 1700
F 0 "C6" H 9115 1746 50  0000 L CNN
F 1 "10uF" H 9115 1655 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 9038 1550 50  0001 C CNN
F 3 "~" H 9000 1700 50  0001 C CNN
	1    9000 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	9000 1550 9000 1450
Connection ~ 9000 1450
$Comp
L power:+3.3V #PWR025
U 1 1 62B5D020
P 9000 900
F 0 "#PWR025" H 9000 750 50  0001 C CNN
F 1 "+3.3V" H 9015 1073 50  0000 C CNN
F 2 "" H 9000 900 50  0001 C CNN
F 3 "" H 9000 900 50  0001 C CNN
	1    9000 900 
	1    0    0    -1  
$EndComp
Wire Wire Line
	9000 900  9000 1350
Connection ~ 9000 1350
Wire Wire Line
	7550 1550 7550 1450
$Comp
L Device:C C5
U 1 1 62B0F390
P 7550 1700
F 0 "C5" H 7665 1746 50  0000 L CNN
F 1 "4.7uF" H 7665 1655 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 7588 1550 50  0001 C CNN
F 3 "~" H 7550 1700 50  0001 C CNN
	1    7550 1700
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4200 4850 4200 5200
Text Label 4200 4850 3    50   ~ 10
RESET
Wire Wire Line
	8400 1450 8400 1550
$Comp
L Device:R R11
U 1 1 62B39345
P 8400 1700
F 0 "R11" H 8470 1746 50  0000 L CNN
F 1 "10k" H 8470 1655 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 8330 1700 50  0001 C CNN
F 3 "~" H 8400 1700 50  0001 C CNN
	1    8400 1700
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR09
U 1 1 62C4D9C1
P 2400 2350
F 0 "#PWR09" H 2400 2100 50  0001 C CNN
F 1 "GND" H 2405 2177 50  0000 C CNN
F 2 "" H 2400 2350 50  0001 C CNN
F 3 "" H 2400 2350 50  0001 C CNN
	1    2400 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 2250 2400 2350
Wire Wire Line
	7950 1750 7950 2100
$Comp
L power:GND #PWR021
U 1 1 62C5E8A2
P 7550 2100
F 0 "#PWR021" H 7550 1850 50  0001 C CNN
F 1 "GND" H 7555 1927 50  0000 C CNN
F 2 "" H 7550 2100 50  0001 C CNN
F 3 "" H 7550 2100 50  0001 C CNN
	1    7550 2100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR026
U 1 1 62C5EC8E
P 9000 2100
F 0 "#PWR026" H 9000 1850 50  0001 C CNN
F 1 "GND" H 9005 1927 50  0000 C CNN
F 2 "" H 9000 2100 50  0001 C CNN
F 3 "" H 9000 2100 50  0001 C CNN
	1    9000 2100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR024
U 1 1 62C5F496
P 8400 2100
F 0 "#PWR024" H 8400 1850 50  0001 C CNN
F 1 "GND" H 8405 1927 50  0000 C CNN
F 2 "" H 8400 2100 50  0001 C CNN
F 3 "" H 8400 2100 50  0001 C CNN
	1    8400 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	7550 1850 7550 2100
Wire Wire Line
	8400 1850 8400 2100
Wire Wire Line
	9000 1850 9000 2100
Wire Wire Line
	2050 950  2050 1450
Wire Wire Line
	2050 2350 2050 1750
Wire Wire Line
	3400 6450 3200 6450
Wire Wire Line
	3200 6450 3200 6300
Wire Wire Line
	2900 2150 2900 2350
Wire Wire Line
	5600 5200 5600 5550
Wire Wire Line
	4200 6050 4200 6000
Wire Wire Line
	7650 1350 7550 1350
Wire Wire Line
	7550 1350 7550 1450
$Comp
L power:PWR_FLAG #FLG01
U 1 1 62AC8A2D
P 750 4250
F 0 "#FLG01" H 750 4325 50  0001 C CNN
F 1 "PWR_FLAG" H 750 4423 50  0000 C CNN
F 2 "" H 750 4250 50  0001 C CNN
F 3 "~" H 750 4250 50  0001 C CNN
	1    750  4250
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG02
U 1 1 62AC8E45
P 1150 4250
F 0 "#FLG02" H 1150 4325 50  0001 C CNN
F 1 "PWR_FLAG" H 1150 4423 50  0000 C CNN
F 2 "" H 1150 4250 50  0001 C CNN
F 3 "~" H 1150 4250 50  0001 C CNN
	1    1150 4250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR01
U 1 1 62AC9305
P 750 4500
F 0 "#PWR01" H 750 4250 50  0001 C CNN
F 1 "GND" H 755 4327 50  0000 C CNN
F 2 "" H 750 4500 50  0001 C CNN
F 3 "" H 750 4500 50  0001 C CNN
	1    750  4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	750  4250 750  4500
$Comp
L power:+5V #PWR04
U 1 1 62ACDA52
P 1150 4500
F 0 "#PWR04" H 1150 4350 50  0001 C CNN
F 1 "+5V" H 1165 4673 50  0000 C CNN
F 2 "" H 1150 4500 50  0001 C CNN
F 3 "" H 1150 4500 50  0001 C CNN
	1    1150 4500
	-1   0    0    1   
$EndComp
Wire Wire Line
	1150 4250 1150 4500
$Comp
L power:PWR_FLAG #FLG03
U 1 1 62AD615A
P 1550 4250
F 0 "#FLG03" H 1550 4325 50  0001 C CNN
F 1 "PWR_FLAG" H 1550 4423 50  0000 C CNN
F 2 "" H 1550 4250 50  0001 C CNN
F 3 "~" H 1550 4250 50  0001 C CNN
	1    1550 4250
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR08
U 1 1 62AD64BF
P 1550 4500
F 0 "#PWR08" H 1550 4350 50  0001 C CNN
F 1 "+3.3V" H 1565 4673 50  0000 C CNN
F 2 "" H 1550 4500 50  0001 C CNN
F 3 "" H 1550 4500 50  0001 C CNN
	1    1550 4500
	-1   0    0    1   
$EndComp
Wire Wire Line
	1550 4250 1550 4500
Wire Wire Line
	6100 6750 6550 6750
Text Label 6450 6750 0    50   ~ 10
DD
Wire Wire Line
	6100 6450 6550 6450
Text Label 6250 6450 0    50   ~ 10
BUZZER
Entry Wire Line
	6750 5650 6650 5750
$Comp
L power:+5V #PWR05
U 1 1 62C91C30
P 2050 950
F 0 "#PWR05" H 2050 800 50  0001 C CNN
F 1 "+5V" H 2065 1123 50  0000 C CNN
F 2 "" H 2050 950 50  0001 C CNN
F 3 "" H 2050 950 50  0001 C CNN
	1    2050 950 
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR011
U 1 1 62B896DB
P 2900 950
F 0 "#PWR011" H 2900 800 50  0001 C CNN
F 1 "+5V" H 2915 1123 50  0000 C CNN
F 2 "" H 2900 950 50  0001 C CNN
F 3 "" H 2900 950 50  0001 C CNN
	1    2900 950 
	1    0    0    -1  
$EndComp
Connection ~ 7550 1350
Entry Wire Line
	6750 5750 6650 5850
Entry Wire Line
	6750 5850 6650 5950
Entry Wire Line
	6750 5950 6650 6050
Entry Wire Line
	6750 6050 6650 6150
Entry Wire Line
	6750 6150 6650 6250
Wire Wire Line
	6650 6250 6100 6250
Wire Wire Line
	6100 6150 6650 6150
Wire Wire Line
	6650 6050 6100 6050
Wire Wire Line
	6100 5950 6650 5950
Wire Wire Line
	6100 5850 6650 5850
Entry Wire Line
	6750 4400 6850 4300
Entry Wire Line
	6750 4500 6850 4400
Entry Wire Line
	6750 4600 6850 4500
Entry Wire Line
	6750 4700 6850 4600
Entry Wire Line
	6750 4800 6850 4700
Entry Wire Line
	6750 4900 6850 4800
Entry Wire Line
	6750 5000 6850 4900
Entry Wire Line
	6750 5100 6850 5000
Wire Wire Line
	6850 4300 7200 4300
Wire Wire Line
	6850 4400 7200 4400
Wire Wire Line
	6850 4500 7200 4500
Wire Wire Line
	6850 4600 7200 4600
Wire Wire Line
	6850 4700 7200 4700
Wire Wire Line
	6850 4800 7200 4800
Wire Wire Line
	6850 4900 7200 4900
Wire Wire Line
	6850 5000 7200 5000
Text Label 6250 5750 0    50   ~ 0
P1.0
Text Label 6250 5850 0    50   ~ 0
P1.1
Text Label 6250 5950 0    50   ~ 0
P1.2
Text Label 6250 6050 0    50   ~ 0
P1.3
Text Label 6250 6150 0    50   ~ 0
P1.4
Text Label 6250 6250 0    50   ~ 0
P1.5
Entry Wire Line
	6750 6550 6650 6650
Wire Wire Line
	6650 6650 6100 6650
Text Label 6250 6650 0    50   ~ 0
P2.0
Text Label 6950 4300 0    50   ~ 0
P1.0
Text Label 6950 4400 0    50   ~ 0
P1.1
Text Label 6950 4500 0    50   ~ 0
P1.2
Text Label 6950 4600 0    50   ~ 0
P1.3
Text Label 6950 4700 0    50   ~ 0
P1.4
Text Label 6950 4800 0    50   ~ 0
P1.5
Text Label 6950 4900 0    50   ~ 0
P1.6
Text Label 6950 5000 0    50   ~ 0
P2.0
Text Label 4600 5950 0    50   ~ 10
BAT_ADC
Wire Wire Line
	5100 5950 4600 5950
Wire Wire Line
	3500 1750 3500 950 
Wire Wire Line
	3300 1750 3500 1750
$Comp
L power:GND #PWR015
U 1 1 62BA4E02
P 3750 2050
F 0 "#PWR015" H 3750 1800 50  0001 C CNN
F 1 "GND" H 3755 1877 50  0000 C CNN
F 2 "" H 3750 2050 50  0001 C CNN
F 3 "" H 3750 2050 50  0001 C CNN
	1    3750 2050
	1    0    0    -1  
$EndComp
$Comp
L power:+BATT #PWR013
U 1 1 62CC317C
P 3500 950
F 0 "#PWR013" H 3500 800 50  0001 C CNN
F 1 "+BATT" H 3515 1123 50  0000 C CNN
F 2 "" H 3500 950 50  0001 C CNN
F 3 "" H 3500 950 50  0001 C CNN
	1    3500 950 
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D2
U 1 1 62D7F658
P 850 6600
F 0 "D2" V 889 6680 50  0000 L CNN
F 1 "LED" V 798 6680 50  0000 L CNN
F 2 "LED_SMD:LED_0603_1608Metric" H 850 6600 50  0001 C CNN
F 3 "~" H 850 6600 50  0001 C CNN
	1    850  6600
	0    1    -1   0   
$EndComp
$Comp
L Device:R R4
U 1 1 62D81460
P 850 6100
F 0 "R4" H 700 6150 50  0000 L CNN
F 1 "470" H 650 6050 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 780 6100 50  0001 C CNN
F 3 "~" H 850 6100 50  0001 C CNN
	1    850  6100
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR014
U 1 1 62D9ABB6
P 850 7150
F 0 "#PWR014" H 850 6900 50  0001 C CNN
F 1 "GND" H 855 6977 50  0000 C CNN
F 2 "" H 850 7150 50  0001 C CNN
F 3 "" H 850 7150 50  0001 C CNN
	1    850  7150
	1    0    0    -1  
$EndComp
Wire Wire Line
	850  7150 850  6750
Wire Wire Line
	850  6450 850  6250
Wire Wire Line
	850  5950 850  5600
Text Label 850  5600 0    50   ~ 10
LED
Wire Wire Line
	6650 5750 6100 5750
$Comp
L Device:Buzzer BZ1
U 1 1 62B001E4
P 10550 5300
F 0 "BZ1" H 10702 5329 50  0000 L CNN
F 1 "Buzzer" H 10702 5238 50  0000 L CNN
F 2 "Buzzer_Beeper:MLT-9032" V 10525 5400 50  0001 C CNN
F 3 "~" V 10525 5400 50  0001 C CNN
	1    10550 5300
	1    0    0    -1  
$EndComp
Text Label 8900 5750 0    50   ~ 10
BUZZER
Wire Wire Line
	9550 5750 8900 5750
Wire Wire Line
	9850 5750 10050 5750
$Comp
L Device:R R13
U 1 1 62B15366
P 9700 5750
F 0 "R13" H 9770 5796 50  0000 L CNN
F 1 "470" H 9770 5705 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 9630 5750 50  0001 C CNN
F 3 "~" H 9700 5750 50  0001 C CNN
	1    9700 5750
	0    1    -1   0   
$EndComp
Wire Wire Line
	10350 5500 10350 5550
Connection ~ 10350 5500
Wire Wire Line
	10100 5500 10350 5500
Wire Wire Line
	10100 5450 10100 5500
Wire Wire Line
	10350 5400 10350 5500
Wire Wire Line
	10450 5400 10350 5400
Wire Wire Line
	10350 5100 10350 5200
Connection ~ 10350 5100
Wire Wire Line
	10100 5100 10350 5100
Wire Wire Line
	10100 5150 10100 5100
Wire Wire Line
	10350 5200 10450 5200
$Comp
L Device:D D3
U 1 1 62B0628F
P 10100 5300
F 0 "D3" V 10054 5380 50  0000 L CNN
F 1 "D" V 10145 5380 50  0000 L CNN
F 2 "Diode_SMD:D_MicroMELF" H 10100 5300 50  0001 C CNN
F 3 "~" H 10100 5300 50  0001 C CNN
	1    10100 5300
	0    1    1    0   
$EndComp
$Comp
L Device:Q_NPN_BCE Q2
U 1 1 62B0380D
P 10250 5750
F 0 "Q2" H 10441 5796 50  0000 L CNN
F 1 "C1815" H 10441 5705 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 10450 5850 50  0001 C CNN
F 3 "~" H 10250 5750 50  0001 C CNN
	1    10250 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	10150 4400 10150 4350
Connection ~ 10150 4400
Wire Wire Line
	10350 4400 10150 4400
Wire Wire Line
	10350 4200 10350 4400
Wire Wire Line
	10150 4500 10150 4400
Wire Wire Line
	10350 3850 10350 4100
Wire Wire Line
	10150 3850 10350 3850
Wire Wire Line
	10150 3950 10150 3850
$Comp
L power:GND #PWR031
U 1 1 62B20737
P 10150 4500
F 0 "#PWR031" H 10150 4250 50  0001 C CNN
F 1 "GND" H 10155 4327 50  0000 C CNN
F 2 "" H 10150 4500 50  0001 C CNN
F 3 "" H 10150 4500 50  0001 C CNN
	1    10150 4500
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 EXT1
U 1 1 62B1C27B
P 10550 4100
F 0 "EXT1" H 10550 3900 50  0000 C CNN
F 1 "External Load" V 10700 4050 50  0000 C CNN
F 2 "TerminalBlock_TE-Connectivity:TerminalBlock_TE_282834-2_1x02_P2.54mm_Horizontal" H 10550 4100 50  0001 C CNN
F 3 "~" H 10550 4100 50  0001 C CNN
	1    10550 4100
	1    0    0    -1  
$EndComp
Text Label 6950 4200 0    50   ~ 0
P0.7
Entry Wire Line
	6750 4300 6850 4200
Wire Wire Line
	6850 4200 7200 4200
$Comp
L power:GND #PWR018
U 1 1 62C3C6D1
P 6900 2100
F 0 "#PWR018" H 6900 1850 50  0001 C CNN
F 1 "GND" H 6905 1927 50  0000 C CNN
F 2 "" H 6900 2100 50  0001 C CNN
F 3 "" H 6900 2100 50  0001 C CNN
	1    6900 2100
	1    0    0    -1  
$EndComp
$Comp
L Device:R R8
U 1 1 62C2FEBA
P 6900 1400
F 0 "R8" H 6970 1446 50  0000 L CNN
F 1 "???" H 6970 1355 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6830 1400 50  0001 C CNN
F 3 "~" H 6900 1400 50  0001 C CNN
	1    6900 1400
	-1   0    0    1   
$EndComp
$Comp
L Device:R R9
U 1 1 62C30B2A
P 6900 1800
F 0 "R9" H 6970 1846 50  0000 L CNN
F 1 "???" H 6970 1755 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6830 1800 50  0001 C CNN
F 3 "~" H 6900 1800 50  0001 C CNN
	1    6900 1800
	-1   0    0    1   
$EndComp
Wire Wire Line
	6900 1950 6900 2100
Wire Wire Line
	6900 1550 6900 1600
Wire Wire Line
	6900 1600 7200 1600
Connection ~ 6900 1600
Wire Wire Line
	6900 1600 6900 1650
Text Label 6950 1600 0    50   ~ 10
BAT_ADC
Text Label 9300 3100 0    50   ~ 10
CAPTURE2
Text Label 9300 2600 0    50   ~ 10
CAPTURE1
Text Label 9300 2100 0    50   ~ 10
CAPTURE0
Wire Wire Line
	9900 2500 9900 3000
Wire Wire Line
	9900 3000 10250 3000
Connection ~ 9900 2500
Wire Wire Line
	10250 2500 9900 2500
Wire Wire Line
	9900 2000 9900 2500
Connection ~ 9900 2000
Wire Wire Line
	10250 2000 9900 2000
Wire Wire Line
	10250 3100 9300 3100
Wire Wire Line
	10250 2600 9300 2600
Wire Wire Line
	10250 2100 9300 2100
Connection ~ 10050 3200
Wire Wire Line
	10250 3200 10050 3200
Wire Wire Line
	10050 2700 10050 3200
Connection ~ 10050 2700
Wire Wire Line
	10250 2700 10050 2700
Wire Wire Line
	10050 2200 10050 2700
Wire Wire Line
	10250 2200 10050 2200
$Comp
L Connector:Screw_Terminal_01x03 WM3
U 1 1 62AA134A
P 10450 3100
F 0 "WM3" H 10530 3142 50  0000 L CNN
F 1 "Third" H 10530 3051 50  0000 L CNN
F 2 "TerminalBlock_TE-Connectivity:TerminalBlock_TE_282834-3_1x03_P2.54mm_Horizontal" H 10450 3100 50  0001 C CNN
F 3 "~" H 10450 3100 50  0001 C CNN
	1    10450 3100
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x03 WM2
U 1 1 62AA0C42
P 10450 2600
F 0 "WM2" H 10530 2642 50  0000 L CNN
F 1 "Second" H 10530 2551 50  0000 L CNN
F 2 "TerminalBlock_TE-Connectivity:TerminalBlock_TE_282834-3_1x03_P2.54mm_Horizontal" H 10450 2600 50  0001 C CNN
F 3 "~" H 10450 2600 50  0001 C CNN
	1    10450 2600
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x03 WM1
U 1 1 62A9FF51
P 10450 2100
F 0 "WM1" H 10530 2142 50  0000 L CNN
F 1 "First" H 10530 2051 50  0000 L CNN
F 2 "TerminalBlock_TE-Connectivity:TerminalBlock_TE_282834-3_1x03_P2.54mm_Horizontal" H 10450 2100 50  0001 C CNN
F 3 "~" H 10450 2100 50  0001 C CNN
	1    10450 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	10050 3200 10050 3450
$Comp
L power:GND #PWR030
U 1 1 62AA2803
P 10050 3450
F 0 "#PWR030" H 10050 3200 50  0001 C CNN
F 1 "GND" H 10055 3277 50  0000 C CNN
F 2 "" H 10050 3450 50  0001 C CNN
F 3 "" H 10050 3450 50  0001 C CNN
	1    10050 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	9900 1700 9900 2000
$Comp
L power:+3.3V #PWR029
U 1 1 62AA1BD6
P 9900 1700
F 0 "#PWR029" H 9900 1550 50  0001 C CNN
F 1 "+3.3V" H 9915 1873 50  0000 C CNN
F 2 "" H 9900 1700 50  0001 C CNN
F 3 "" H 9900 1700 50  0001 C CNN
	1    9900 1700
	1    0    0    -1  
$EndComp
$Comp
L Device:C C7
U 1 1 62A6B9CF
P 9650 1100
F 0 "C7" H 9450 1150 50  0000 L CNN
F 1 "100nF" H 9300 1050 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 9688 950 50  0001 C CNN
F 3 "~" H 9650 1100 50  0001 C CNN
	1    9650 1100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR028
U 1 1 62A5FA07
P 10100 1400
F 0 "#PWR028" H 10100 1150 50  0001 C CNN
F 1 "GND" V 10105 1272 50  0000 R CNN
F 2 "" H 10100 1400 50  0001 C CNN
F 3 "" H 10100 1400 50  0001 C CNN
	1    10100 1400
	1    0    0    -1  
$EndComp
Text Label 10350 1200 0    50   ~ 10
RESET
Text Label 10350 1000 0    50   ~ 10
DD
Wire Wire Line
	10700 1200 10350 1200
Wire Wire Line
	10700 1000 10350 1000
$Comp
L power:+3.3V #PWR027
U 1 1 62A5E262
P 10100 750
F 0 "#PWR027" H 10100 600 50  0001 C CNN
F 1 "+3.3V" H 10115 923 50  0000 C CNN
F 2 "" H 10100 750 50  0001 C CNN
F 3 "" H 10100 750 50  0001 C CNN
	1    10100 750 
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x05_Male DBG1
U 1 1 62A004F1
P 10900 1100
F 0 "DBG1" H 11008 1481 50  0000 C CNN
F 1 "DEBUG" H 11008 1390 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Vertical" H 10900 1100 50  0001 C CNN
F 3 "~" H 10900 1100 50  0001 C CNN
	1    10900 1100
	-1   0    0    1   
$EndComp
Wire Wire Line
	10350 4950 10350 5100
Wire Wire Line
	10350 6150 10350 5950
$Comp
L power:GND #PWR033
U 1 1 62B01C87
P 10350 6150
F 0 "#PWR033" H 10350 5900 50  0001 C CNN
F 1 "GND" H 10355 5977 50  0000 C CNN
F 2 "" H 10350 6150 50  0001 C CNN
F 3 "" H 10350 6150 50  0001 C CNN
	1    10350 6150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5100 6050 4600 6050
$Comp
L Device:Q_NMOS_GDS Q1
U 1 1 62CE3546
P 10050 4150
F 0 "Q1" H 10000 4300 50  0000 L CNN
F 1 "Q_NMOS_DGS" H 9650 4000 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:TO-252-2" H 10250 4250 50  0001 C CNN
F 3 "~" H 10050 4150 50  0001 C CNN
	1    10050 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	9850 4150 9400 4150
Text Label 9400 4150 0    50   ~ 10
EXT_LOAD
$Comp
L power:+BATT #PWR0101
U 1 1 62AFC88D
P 10350 4950
F 0 "#PWR0101" H 10350 4800 50  0001 C CNN
F 1 "+BATT" H 10365 5123 50  0000 C CNN
F 2 "" H 10350 4950 50  0001 C CNN
F 3 "" H 10350 4950 50  0001 C CNN
	1    10350 4950
	1    0    0    -1  
$EndComp
Entry Wire Line
	6750 6250 6650 6350
Wire Wire Line
	6100 6350 6650 6350
Text Label 6250 6350 0    50   ~ 0
P1.6
Wire Wire Line
	5100 6550 4600 6550
Text Label 4600 6550 0    50   ~ 10
LED
$Comp
L Connector:USB_C_Plug P1
U 1 1 62BA611A
P 1050 1850
F 0 "P1" H 1157 3117 50  0000 C CNN
F 1 "USB_C_Plug" H 1157 3026 50  0000 C CNN
F 2 "Connector_USB:USB_C_Receptacle_HRO_TYPE-C-31-M-12" H 1200 1850 50  0001 C CNN
F 3 "https://www.usb.org/sites/default/files/documents/usb_type-c.zip" H 1200 1850 50  0001 C CNN
	1    1050 1850
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR02
U 1 1 62B88F85
P 1750 700
F 0 "#PWR02" H 1750 550 50  0001 C CNN
F 1 "+5V" H 1765 873 50  0000 C CNN
F 2 "" H 1750 700 50  0001 C CNN
F 3 "" H 1750 700 50  0001 C CNN
	1    1750 700 
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 850  1750 850 
Wire Wire Line
	1750 850  1750 700 
Wire Wire Line
	750  3450 750  3600
Wire Wire Line
	750  3600 1050 3600
Connection ~ 1050 3600
Wire Wire Line
	1050 3600 1050 3450
NoConn ~ 1650 1350
NoConn ~ 1650 1550
NoConn ~ 1650 1850
NoConn ~ 1650 1950
NoConn ~ 1650 2150
NoConn ~ 1650 2250
NoConn ~ 1650 2450
NoConn ~ 1650 2550
NoConn ~ 1650 2750
NoConn ~ 1650 2850
NoConn ~ 1650 3050
NoConn ~ 1650 3150
NoConn ~ 1650 1050
NoConn ~ 1650 1150
$Comp
L Mechanical:MountingHole H1
U 1 1 62D1A6E2
P 1950 4250
F 0 "H1" H 2050 4296 50  0000 L CNN
F 1 "MountingHole" H 2050 4205 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.5mm" H 1950 4250 50  0001 C CNN
F 3 "~" H 1950 4250 50  0001 C CNN
	1    1950 4250
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H3
U 1 1 62D1BA2E
P 2700 4250
F 0 "H3" H 2800 4296 50  0000 L CNN
F 1 "MountingHole" H 2800 4205 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.5mm" H 2700 4250 50  0001 C CNN
F 3 "~" H 2700 4250 50  0001 C CNN
	1    2700 4250
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H4
U 1 1 62D1BE95
P 2700 4500
F 0 "H4" H 2800 4546 50  0000 L CNN
F 1 "MountingHole" H 2800 4455 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.5mm" H 2700 4500 50  0001 C CNN
F 3 "~" H 2700 4500 50  0001 C CNN
	1    2700 4500
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H2
U 1 1 62D1C178
P 1950 4500
F 0 "H2" H 2050 4546 50  0000 L CNN
F 1 "MountingHole" H 2050 4455 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.5mm" H 1950 4500 50  0001 C CNN
F 3 "~" H 1950 4500 50  0001 C CNN
	1    1950 4500
	1    0    0    -1  
$EndComp
$Comp
L power:+BATT #PWR0102
U 1 1 62BD97C2
P 7550 850
F 0 "#PWR0102" H 7550 700 50  0001 C CNN
F 1 "+BATT" H 7565 1023 50  0000 C CNN
F 2 "" H 7550 850 50  0001 C CNN
F 3 "" H 7550 850 50  0001 C CNN
	1    7550 850 
	1    0    0    -1  
$EndComp
Wire Wire Line
	7550 850  7550 1350
$Comp
L power:+BATT #PWR0103
U 1 1 62BE3F20
P 6900 850
F 0 "#PWR0103" H 6900 700 50  0001 C CNN
F 1 "+BATT" H 6915 1023 50  0000 C CNN
F 2 "" H 6900 850 50  0001 C CNN
F 3 "" H 6900 850 50  0001 C CNN
	1    6900 850 
	1    0    0    -1  
$EndComp
Wire Wire Line
	6900 850  6900 1250
Wire Wire Line
	10700 900  10100 900 
Wire Wire Line
	10100 900  10100 750 
Wire Wire Line
	9650 900  9650 950 
Connection ~ 10100 900 
Wire Wire Line
	10700 1300 10100 1300
Wire Wire Line
	9650 1300 9650 1250
Wire Wire Line
	10100 1400 10100 1300
Connection ~ 10100 1300
Wire Wire Line
	10100 1300 9650 1300
$Comp
L Connector:Conn_01x09_Male FRC1
U 1 1 62DA51E7
P 7400 4600
F 0 "FRC1" H 7372 4482 50  0000 R CNN
F 1 "Free" H 7372 4573 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x09_P2.54mm_Vertical" H 7400 4600 50  0001 C CNN
F 3 "~" H 7400 4600 50  0001 C CNN
	1    7400 4600
	-1   0    0    1   
$EndComp
Wire Wire Line
	2900 950  2900 1450
$Comp
L Device:LED D1
U 1 1 62A6BFAA
P 2400 1150
F 0 "D1" V 2439 1230 50  0000 L CNN
F 1 "LED" V 2348 1230 50  0000 L CNN
F 2 "LED_SMD:LED_0603_1608Metric" H 2400 1150 50  0001 C CNN
F 3 "~" H 2400 1150 50  0001 C CNN
	1    2400 1150
	0    1    -1   0   
$EndComp
$Comp
L Battery_Management:LTC4054ES5-4.2 U1
U 1 1 62AE1DE9
P 2900 1750
F 0 "U1" H 2900 2100 50  0000 L CNN
F 1 "LTC4054ES5-4.2" H 2900 2000 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:TSOT-23-5" H 2900 1250 50  0001 C CNN
F 3 "https://www.analog.com/media/en/technical-documentation/data-sheets/405442xf.pdf" H 2900 1650 50  0001 C CNN
	1    2900 1750
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0104
U 1 1 62E33458
P 2400 950
F 0 "#PWR0104" H 2400 800 50  0001 C CNN
F 1 "+5V" H 2415 1123 50  0000 C CNN
F 2 "" H 2400 950 50  0001 C CNN
F 3 "" H 2400 950 50  0001 C CNN
	1    2400 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 1750 2400 1750
Wire Wire Line
	2400 1750 2400 1700
Wire Wire Line
	2400 1400 2400 1300
Wire Wire Line
	2400 1000 2400 950 
Wire Wire Line
	9650 900  10100 900 
Wire Wire Line
	10700 1100 10350 1100
Text Label 10350 1100 0    50   ~ 10
DC
Wire Wire Line
	6900 6850 6900 6400
Wire Wire Line
	6100 6850 6900 6850
$Comp
L power:+3.3V #PWR0105
U 1 1 62E9B2F6
P 6900 5950
F 0 "#PWR0105" H 6900 5800 50  0001 C CNN
F 1 "+3.3V" H 6915 6123 50  0000 C CNN
F 2 "" H 6900 5950 50  0001 C CNN
F 3 "" H 6900 5950 50  0001 C CNN
	1    6900 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	6900 5950 6900 6100
Wire Wire Line
	3950 6450 5100 6450
Wire Wire Line
	5100 5750 5000 5750
Wire Wire Line
	4200 5500 4200 5600
Wire Wire Line
	5000 5750 5000 5600
Wire Wire Line
	5000 5600 4200 5600
Connection ~ 4200 5600
Wire Wire Line
	4200 5600 4200 5700
Wire Wire Line
	4750 1400 4750 1200
Wire Wire Line
	4950 1300 5000 1300
Wire Wire Line
	5950 1400 6100 1400
Connection ~ 5950 1300
Wire Wire Line
	5800 1300 5950 1300
Wire Wire Line
	5950 1300 6050 1300
Wire Wire Line
	5950 1400 5950 1300
Wire Wire Line
	6100 1550 6100 1400
Wire Wire Line
	6100 2050 6450 2050
Connection ~ 6100 2050
Wire Wire Line
	6100 1850 6100 2050
Wire Wire Line
	4850 1300 4850 1200
Wire Wire Line
	5000 1200 4850 1200
NoConn ~ 5800 1200
Wire Wire Line
	4550 2050 4950 2050
Wire Wire Line
	5800 1400 5850 1400
$Comp
L Device:R R7
U 1 1 62C1475D
P 6200 1300
F 0 "R7" H 6270 1346 50  0000 L CNN
F 1 "100" H 6270 1255 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6130 1300 50  0001 C CNN
F 3 "~" H 6200 1300 50  0001 C CNN
	1    6200 1300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6350 1300 6450 1300
$Comp
L Device:C C4
U 1 1 62C48B76
P 6100 1700
F 0 "C4" H 6100 1800 50  0000 L CNN
F 1 "100nF" H 6100 1600 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 6138 1550 50  0001 C CNN
F 3 "~" H 6100 1700 50  0001 C CNN
	1    6100 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	6450 2050 6450 1850
Wire Wire Line
	6450 850  6450 1300
$Comp
L power:+BATT #PWR017
U 1 1 62CC40E3
P 6450 850
F 0 "#PWR017" H 6450 700 50  0001 C CNN
F 1 "+BATT" H 6465 1023 50  0000 C CNN
F 2 "" H 6450 850 50  0001 C CNN
F 3 "" H 6450 850 50  0001 C CNN
	1    6450 850 
	1    0    0    -1  
$EndComp
$Comp
L Device:Battery_Cell BT1
U 1 1 629F95F0
P 6450 1750
F 0 "BT1" H 6568 1846 50  0000 L CNN
F 1 "BAT" H 6568 1755 50  0000 L CNN
F 2 "Battery:BatteryHolder_Blossom_1042_1x18650" V 6450 1810 50  0001 C CNN
F 3 "~" V 6450 1810 50  0001 C CNN
	1    6450 1750
	1    0    0    -1  
$EndComp
$Comp
L LeoDJ-kicad:DW01A U3
U 1 1 62AD2C67
P 5400 1300
F 0 "U3" H 5400 991 47  0000 C CNN
F 1 "DW01A" H 5400 1078 47  0000 C CNN
F 2 "Package_TO_SOT_SMD:TSOT-23-6" H 4850 2050 60  0001 C CNN
F 3 "http://escooter.org.ua/_fr/1/DW01A-DS-10_EN.pdf" H 4850 2050 60  0001 C CNN
	1    5400 1300
	1    0    0    1   
$EndComp
Connection ~ 6450 1300
Wire Wire Line
	6450 1300 6450 1550
Wire Wire Line
	4550 1400 4550 2050
NoConn ~ 3750 1200
$Comp
L Transistor_FET_Extra:FS8205A U2
U 1 1 62D41CED
P 4150 1300
F 0 "U2" H 4150 1665 50  0000 C CNN
F 1 "FS8205A" H 4150 1574 50  0000 C CNN
F 2 "Package_SO:TSSOP-8_4.4x3mm_P0.65mm" H 4150 950 50  0001 C CNN
F 3 "" H 4200 950 50  0001 C CNN
	1    4150 1300
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4550 1200 4750 1200
Wire Wire Line
	4750 1400 5000 1400
Wire Wire Line
	4550 1300 4850 1300
Wire Wire Line
	3750 1400 3750 2050
Connection ~ 5850 2050
Wire Wire Line
	5850 2050 6100 2050
Wire Wire Line
	5850 1400 5850 2050
$Comp
L Device:R R5
U 1 1 62B788D5
P 4950 1700
F 0 "R5" H 5020 1746 50  0000 L CNN
F 1 "1k" H 5020 1655 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4880 1700 50  0001 C CNN
F 3 "~" H 4950 1700 50  0001 C CNN
	1    4950 1700
	-1   0    0    1   
$EndComp
Wire Wire Line
	4950 1300 4950 1550
Wire Wire Line
	4950 1850 4950 2050
Connection ~ 4950 2050
Wire Wire Line
	4950 2050 5850 2050
Text Label 4600 6050 0    50   ~ 10
EXT_LOAD
Wire Bus Line
	6750 4300 6750 6550
$EndSCHEMATC
