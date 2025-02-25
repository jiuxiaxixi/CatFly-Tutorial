# Link Quality Indication (LQI)

According to IEEE 802.15.4, the LQI measurement is a characterization of the strength and/or quality of a received packet. The measurement may be implemented using receiver ED, a signal-to-noise ratio estimation, or a combination of these methods. The use of the LQI result by the network or application layers is not specified in this standard. LQI values shall be an integer ranging from 0x00 to 0xFF. The minimum and maximum LQI values (0x00 and 0xFF) should be associated with the lowest and highest quality compliant signals, respectively, and LQI values in between should be uniformly distributed between these two limits.

## Overview

The LQI measurement of the AT86RF231 is implemented as a measure of the link quality which can be described with the packet error rate (PER) for this link. An LQI value can be associated with an expected packet error rate. The PER is the ratio of erroneous received frames to the total number of received frames. A PER of zero indicates no frame error, whereas at a PER of one no frame was received correctly. The radio transceiver uses correlation results of multiple symbols within a frame to determine the LQI value. This is done for each received frame. The minimum frame length for a valid LQI value is two octets PSDU. LQI values are integers ranging from 0 to 255.



![Conditional Packet Error Rate versus LQI](..\附件\image-20191222171430569.png)

The values are taken from received frames of PSDU length of 20 octets on transmission channels with reasonable low multipath delay spreads. If the transmission channel characteristic has higher multipath delay spread than assumed in the example, the PER is slightly higher for certain LQI value. Since the packet error rate is a statistical value, the PER shown in “Conditional Packet Error Rate versus LQI”  is based on a huge number of transactions. A reliable estimation of the packet error rate cannot be based on a single or a small number of LQI values.

## Data Interpretation

According to IEEE 802.15.4 a low LQI value is associated with low signal strength and/or high signal distortions. Signal distortions are mainly caused by interference signals and/or multipath propagation. High LQI values indicate a sufficient high signal power and low signal distortions. Note, the received signal power as indicated by received signal strength indication (RSSI) value or energy detection (ED) value of the AT86RF231 do not characterize the signal quality and the ability to decode a signal. As an example, a received signal with an input power of about 6 dB above the receiver sensitivity likely results in a LQI value close to 255 for radio channels with very low signal distortions. For higher signal power the LQI value becomes independent of the actual signal strength. This is because the packet error rate for these scenarios tends towards zero and further increased signal strength, i.e. increasing the transmission power does not decrease the error rate any further. In this case RSSI or ED can be used to evaluate the signal strength and the link margin.

Combinations of LQI, RSSI and ED are possible for routing decisions. As a rule of thumb RSSI and ED values are useful to differentiate between links with high LQI values. Transmission links with low LQI values should be discarded for routing decisions even if the RSSI/ED values are high. This is because RSSI/ED does not say anything about the possibility to decode a signal. It is only an information about the received signal strength whereas the source can be an interferer.