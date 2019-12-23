

# AT8RF231介绍



![AT86RF231](..\附件\image-20191220121451359.png)

## Chip Over

The AT86RF231 is a feature rich, low-power 2.4 GHz radio transceiver designed for industrial and consumer `ZigBee/IEEE 802.15.4`, 6LoWPAN, RF4CE and high data rate 2.4 GHz ISM band applications. 

The radio transceiver is a true SPI-to-antenna solution. All RF-critical components except the antenna, crystal and de-coupling capacitors are integrated on-chip. Therefore, the AT86RF231 is particularly suitable for applications like: 

* 2.4 GHz IEEE 802.15.4 and ZigBee systems

*  6LoWPAN and RF4CE systems

*  Wireless sensor networks

* Industrial control, sensing and automation (SP100, WirelessHART) 

*  Residential and commercial automation 

* Health care 

*  Consumer electronics 

* PC peripherals



## Radio Transceiver Features:

- 128-byte FIFO (SRAM) for Data Buffering
- Programmable Clock Output, to Clock the Host Microcontroller or as Timer Reference 
- Integrated RX/TX Switch 
- Fully Integrated, Fast Settling PLL to support Frequency Hopping – Battery Monitor – Fast Wake-Up Time < 0.4 msec 
-  Special IEEE 802.15.4-2006 Hardware Support: 
-   FCS Computation and Clear Channel Assessment – RSSI Measurement, Energy Detection and Link Quality Indication 

 ## MAC Hardware Accelerator: 
-  Automated Acknowledgement, CSMA-CA and Retransmission – Automatic Address Filtering 
-  Automated FCS Check 
-  Extended Feature Set Hardware Support: 
-  AES 128-bit Hardware Accelerator 
-  RX/TX Indication (external RF Front-End Control) 
-  RX Antenna Diversity 
-  Supported PSDU data rates: 250 kb/s, 500 kb/s, 1 Mb/s and 2 Mb/s – True Random Number Generation for Security Application 

## Microcontroller Interface

![image-20191220122350977](..\附件\image-20191220122350977.png)

| Signal | Description                                                  |
| ------ | ------------------------------------------------------------ |
| /SEL   | SPI select signal, active low                                |
| MOSI   | SPI data (master output slave input) signa                   |
| MISO   | SPI data (master input slave output) signal                  |
| CLKM   | Clock output, refer to Section 9.6.4 usable as: -microcontroller clock source -high precision timing reference -MAC timer reference |
| IRQ    | Interrupt request signal, further used as: -Frame Buffer Empty Indicator, refer to Section 11.7 |
| SLP_TR | Multipurpose control signal (functionality is state dependent, see Section 6.5): <br />-Sleep/Wakeup enable/disable SLEEP state<br /> -TX start BUSY_TX_(ARET) state<br /> -disable/enable CLKM RX_(AACK)_ON state |
| /RST   | AT86RF231 reset signal, active low                           |
| DIG2   | Optional, IRQ_2 (RX_START) for RX Frame Time Stamping, see Section 11.6 |

