# Cell size dimension
* from power view, decided by  UE Tx power/path loss/eNB acceptable Rx power
* if TDD, as UE Rx/Tx switch time needed， decided by the GP of special subframe，
   
   ![tbd](images/frame_2.png)

 * Random access phase
   - preamble  detection windows size decided by  Preach format & Ncs.
   - TA command,  its value was detected by eNB during RA phase, in theory, its value will limit the cell size.
* acceptable  "channel delay spread" due to "inter OFDM symbol interference",  decided by CP length

# Why in LTE the SSS is transmitted before the PSS?
![tbd](images/DL.png)

Three major synchronization requirements can be identified in the LTE system:
1. Symbol and frame timing acquisition, by which the correct symbol start position is determined, for example to set the Discrete Fourier Transform (DFT) window position;
2. Carrier frequency synchronization, which is required to reduce or eliminate the effect of frequency errors arising from a mismatch of the local oscillators between the transmitter and the receiver, as well as the Doppler shift caused by any UE motion;
3. Sampling clock synchronization

so PSS/SSS is designed as:
* 在FDD小区内，PSS总是位于slot #0和slot #10 的最后一个OFDM符号上，使得UE在不考虑循环前缀（CP）长度下获得slot边界定时；SSS直接位于PSS之前；
* In a TDD cell, the PSS is located in the 3rd symbol of DwPTS, while the SSS is located three symbols earlier(alex: end of the first Downlink subframe，这样无论是FDD还是TDD，SSS都在子帧0和5上传输);


Synchronization and Cell Search：

* 一般来说应该UE先对可能存在小区的频率范围内测量小区信号强度，据此找到一个可能存在小区的中心频点；note:[RSSI](https://www.sharetechnote.com/html/Handbook_LTE_RSSI.html) 
* 然后在这个中心频点周围收PSS，这两个信号和系统带宽没有限制，配置是固定的，而且信号本身以5ms为周期重复，并且是ZC序列，具有很强的相关性，因此可以直接检测并接收到，据此可以得到小区Id，同时得到小区定时的5ms边界；（UE不知道解出的PSS是radio frame 中的第一个还是第二个）
* LTE中，SSS的设计有其特别之处：2个SSS（SSS1位于子帧0，SSS2位于子帧5）的值来源于168个可选值的集合，在同一个小区中，SSS2与SSS1使用相同的2个m-sequence，不同的是，在SSS2中，这2个sequence（X和Y）在频域上交换了一下位置。通过尝试解码SSS，UE就能确定这是TDD还是FD，解出来的是SSS1还是2就能确定radio frame 的边界。

* 5ms边界得到后，根据PBCH的时频位置，使用滑窗方法盲检测，一旦发现CRC校验结果正确，则说明当前滑动窗就是10ms的帧边界，并且可以根据PBCH的内容得到系统帧号和带宽信息，以及PHICH的配置；
至此，UE实现了和eNB的定时同步。

![LTE_TDD_SubFrameConfig](images/LTE_TDD_SubFrameConfig_Switching_01.png)

![LTE_TDD_SubFrameConfig](images/LTE_TDD_specialframe.png)

alex: 正是因为PSS检测时，频率/时间未知，所以为了减少解码的effort, PSS设计只有3个取值，对应三种不同的Zadoff-Chu序列


# RNTI during RACH
Random Access process plays two main roles - establishment of uplink synchronization and establishment of a unique UE ID (C-RNTI) known to both the network and the UE.So Random Access is used not only for initial access, but also after periods of uplink inactivity when uplink sync got lost in LTE_ACTIVE states.
 
![RNTI](images/rnti.png)

* RA-RNTI（ Random Access-RNTI）
RA-RNTI = msg 1 时Preamble的时频位置对应到PRACH_Config中的索引；理论取值：1~60（0x0001~0x003C）
使用：eNB回复msg2时 ，在PDCCH上用RA-RNTI加扰，收端UE知道自己之前 Preamble的发送位置，就用RA-RNTI来盲检PDCCH；如有，则说明接入被响应，在依据PDCCH上的指示 去PDSCH上读取RA Response消息（MSG2）。

* T-CRNTI : It stands for Temporary C-RNTI. Mainly used during RACH
在MSG2里，ENB给用户分配一个T-CRNTI。用于随后的Msg中标识UE，当然UE有C-RNTI也可以不用TC-RNTI，此种情况是，这个用户已经在网络中，并且分配过CRNTI。用户获取T-CRNTI后，会在MSG3传输中使用此RNTI。在正常的竞争随机接入中，msg3是RRC信令，则Msg4的PDCCH用Temporary C-RNTI 加扰， msg4中应当携带48bits的MAC控制元素“UE Contention Resolution Identity”，该控制元素就是msg3的SDU。如果该控制元素和UE保存的msg3的SDU相等，则认为自己的msg3被基站正确接收了，竞争解决完成。

* C-RNTI : It stands for Cell RNTI. Used for the transmission to a specific UE after RACH.C-RNTI并不是一开始就有，而是在用户入网之后基站给入网成功的用户分配的。UE若处于RRC_CONNECTED模式，说明已经分配到了C-RNTI，接入时需要上报；UE若处于IDLE模式，说明还没有C-RNTI；在用户切换的时候，则用户可以将本小区分配的C-RNTI带入下一个小区，则不用再重新分配C-RNTI。

about the attach procedure can check  [Non-Access Stratum](NAS.md)


# What is CA?
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


# Does CA activate in RRC idle mode?
There is no carrier aggregation for the UE in RRC Idle mode.

## Is there any a change or impact in Camping process due to CA?
No, there is no change in camping process due to CA because CA will activate in connected mode only.