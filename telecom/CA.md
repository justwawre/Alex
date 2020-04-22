## What is CA?
Carrier Aggregation is a technology through which, a UE can use multiple component carriers to transmit/receive data to/from the eNodeB.
It was introduced in 3GPP Release 10.

Release 8 and 9 UEs supported only one component carrier.
Release 10 UEs can support up to 5 Component Carriers – 1 Primary Carrier, up to 4 Secondary Carriers.

The main component carrier is called Primary Component Carrier (PCC) and others are called Secondary Component Carriers (SCC).

In CA, all the RRC layer communication happens between the PCell and the UE. No RRC messages are exchanged between the UE and SCells.

RRC Connection Establishment/Re-establishment is handled by PCell. Whenever there is a handover, RRC Connection Reconfiguration message is sent by PCell.

Measurement Reports are received by PCell. The number of SCells to be added depends on UE capability.

The configuration/reconfiguration, activation/deactivation, addition and removal of SCells is handled by RRC messages at PCell.

Whenever a new SCell is to be added, all the required details of System Information are sent through RRC Connection Reconfiguration message from the PCell. The UE does not have to SIBs from the SCell. During intra-NR handover, RRC can also add, remove, or reconfigure SCells for usage with the target PCell.

## Q&A
Does CA activate in RRC idle mode?
There is no carrier aggregation for the UE in RRC Idle mode.

Is there any a change or impact in Camping process due to CA?
No, there is no change in camping process due to CA because CA will activate in connected mode only.

