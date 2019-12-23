# Received Signal Strength Indicator (RSSI)

The Received Signal Strength Indicator is characterized by: 

* Minimum RSSI level is -91 dBm (RSSI_BASE_VAL) 
* Dynamic range is 81 dB
*  Minimum RSSI value is 0 
* Maximum RSSI value is 28

## Reading RSSI

In Basic Operating Mode the RSSI value is valid in any receive state, and is updated every tTR25 = 2 µs to register 0x06 (PHY_RSSI). It is not recommended to read the RSSI value when using the Extended Operating Mode. The automatically generated ED value should be used alternatively

![Register 0x06 (PHY_RSSI)](..\附件\image-20191222161215121.png)

Bit [4:0] - RSSI The result of the automated RSSI measurement is stored in register bits RSSI. The value is updated every 2 µs in receive states. The read value is a number between 0 and 28 indicating the received signal strength as a linear curve on a logarithmic input power scale (dBm) with a resolution of 3 dB. An RSSI value of 0 indicates an RF input power of PRF < -91 dBm, a value of 28 a power of PRF  10 dBm

## Data Interpretation

The RSSI value is a 5-bit value indicating the receive power, in steps of 3 dB and with a range of 0 - 28. An RSSI value of 0 indicates a receiver RF input power of PRF < -91 dBm. For an RSSI value in the range of 1 to 28, the RF input power can be calculated as follows: 

PRF = RSSAI_BASE_VAL + 3*(RSSI -1) [dBm]



![Mapping between RSSI Value and Received Input Power](..\附件\image-20191222161126768.png)

A