# Energy Detection (ED)

The Energy Detection (ED) module is characterized by: 

*  85 unique energy levels defined
*  1 dB resolution

##  Overview

The receiver ED measurement is used by the network layer as part of a channel selection algorithm. It is an estimation of the received signal power within the bandwidth of an IEEE 802.15.4 channel. No attempt is made to identify or decode signals on the channel. The ED value is calculated by averaging RSSI values over eight symbols (128 µs).

 For High Data Rate Modes the automated ED measurement duration is reduced to 32 µs. For manually initiated ED measurements in these modes the measurement period is still 128 µs as long as the receiver is in RX_ON state.

## Measurement Description

There are two ways to initiate an ED measurement:

* Manually, by writing an arbitrary value to register 0x07 (PHY_ED_LEVEL),
*  Automatically, after detection of a valid SHR of an incoming frame

An automated ED measurement is started if an SHR is detected. The end of the automated measurement is not signaled by an interrupt. it is not recommended to manually initiate an ED measurement when using the Extended Operating Mode


## Data Interpretation

![Register 0x07 (PHY_ED_LEVEL)](C:\Users\569hm\code\CatFly-Tutorial\附件\image-20191222170930351.png)

- Bit [7:0] - ED_LEVEL
The minimum ED value (ED_LEVEL = 0) indicates receiver power less than or equal to
RSSI_BASE_VAL. The range is 84 dB with a resolution of 1 dB and an absolute accuracy of
±5 dB. A manual ED measurement can be initiated by a write access to the register. A value
0xFF signals that a measurement has never been started yet (reset value).
The measurement duration is 8 symbol periods (128 µs) for a data rate of 250 kb/s

![Mapping between Received Input Power and ED Value](C:\Users\569hm\code\CatFly-Tutorial\附件\image-20191222170852053.png)

The PHY_ED_LEVEL is an 8-bit register. The ED value of the AT86RF231 has a valid range from 0x00 to 0x54 with a resolution of 1 dB. All other values do not occur; a value of 0xFF indicates the reset value. A value of PHY_ED_LEVEL = 0 indicates that the measured energy is less than -91 dBm

Due to environmental conditions (temperature, voltage, semiconductor parameters, etc.) the calculated ED value has a maximum tolerance of ±5 dB, this is to be considered as constant offset over the measurement range.

A An ED value of 0 indicates an RF input power of PRF ≤ -91 dBm. For an ED value in the range of 0 to 84, the RF input power can be calculated as follows: 

PRF = -91 + ED [dBm]

