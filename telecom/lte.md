Personal review

# Cell size dimension
* from power view, decided by  UE Tx power/path loss/eNB acceptable Rx power
* if TDD, as UE Rx/Tx switch time needed， decided by the GP of special subframe，
   
   ![tbd](images/frame_2.png)

 * Random access phase
   - preamble  detection windows size decided by  Preach format
   - TA command,  its value was detected by eNB during RA phase, in theory, its value will limit the cell size.
* acceptable  "channel delay spread" due to "inter OFDM symbol interference",  decided by CP length

# Why in LTE the SSS is transmitted before the PSS?
beside carrying PCI info, the PSS/SSS has other function as to detect the CP length/subframe synchronize. Although the SSS seem transmitted a symbol earlier, for PCI decode, Still the PSS is decoded firstly.

![tbd](images/DL.png)

# HARQ when UL TTI bundling
it is quite special
* only 1 UL grant for the 4 consecutive UL subframe
* only 1 ACK/NACK from eNB related to the last subframe in a bundle, but The maximum number of HARQ retransmissions (maxHARQ-Tx) shall be configured to a value divisible by 4 (i.e. n4, n8, n12, n16, n20, n24).
* modulation order (QM) was fixed.  to UEs for that the TTI bundling mode is selected have to deal with 4 HARQ processes and an RTT of 16 ms which is different from the UEs in normal operation (8 HARQ processes and 8 ms RTT). Accordingly, the timing of thecorresponding acknowledgement of the HARQ process differs between the two modes. The 4 Subframes use RV 0,2,3,1
* so in HARQ Process view: 1 bundle is just treated as 1 transmission, but in time domain, it is still 4 TTI.
* switching on/off TTI bundling need a intra-cell HO to change the UE CONTEXT via  the RRC-ConnectionReconfiguration procedure

# Scheduling timing & HARQ prcess: FDD
* number of HARQ processes are fixed to 8.
* UL harq is synchronous,  UL ACK/NACK was fixed to 4 TTI after transmission
* DL harq is asynchronous, its Harq process and RV is indicated by PDCCH.

![timing](images/ULDL_timing.png)

* timing of UL/DL transmission. in above example UL grant happen at n TTI, transmission happen at n+4, retransmission happen at n+8.

![no adpative](images/ulharq_no_adaptive.png)

In UL, retransmissions are either triggered by the PDCCH (adaptive), or by a received (PHICH)
* If non-adaptive retransmission, the UE uses the same resources which were previously used by the same HARQ process, no PDCCH signalling needed.
* If adaptive retransmission, the UE uses the resources which are assigned by the PDCCH.

# UL scheduling
   * via SR/BSR, classified by LCG
   * explicit granted via PDCCH or implicit grant e.g. IUA (SPS of interval 1/2/4ms)

   ![tbd](images/ul_scheduling.png)

   * if retransmission, please refer previous chapter

# Beamforming
* a general signal processing technique used to control the directionality
* increase the reliability of the transmission by combining several decorrelated
signals (diversity),
* enhance the Signal to Interference plus Noise Ratio (SINR) by spatial focusing
of several correlated signals (beamforming),

# Carrier Aggregtion
* UE-->TB-->CC mapping

![tbd](images/CA_mapping.png)

* scheduling only happen on PCell,so from MAC sw view, the SCell is only accessed via the PCell
* SCell are configured based on UE capability
* Can have DL only resources or DL and UL resources.
* Rel. 8/9 compatible.
* configured via dedicated RRC Reconfiguration message.
* Can be dynamically activated/deactivated (MAC based).
* asymmetric of DL/UL CC

![tbd](images/CA_asymmetric.png)

* MAC handling, it split into two phase
  - phase 1, scell configuration/deconfiguration, dynamic, ue measurment based
  - activate/deactivate via MAC cmd, usually because of throughput


# Scheduler
   Goal: maximizie the UEs with satisfied QoS

## QoS
   * QCI
   * ARP
   * GBR/MBR
   * AMBR 

## Phases
   * admission control
   * active queue management (threshold Min/Max)
   * rate shapping
   * scheduling (weight)

the QCI is e2e, each network node shall decided its per Hop policy to ensure the e2e target. in the transport network, it may use he DSCP mapping to different queue with different weight. in Baseband, the similiar policy was used.
The framework of scheduler is based on 
   * Priority Queue: higher weight mean higher probability of being sceduled
   * weight functions:implements the scheduling algorithm
So scheduler only need care the weight.
## The algorithm examples:
   * roud robin: resource fair
   * proportional fair: a trade off between user fairness and the system performance
   * max cell throughput
   * strict priority:Used for BCCH, PCCH, CCCH, MAC Ctrl
   * delay based: VOIP, usually bundle the voice packets to intervals like 60ms

## weight functions used in frequency slective scheduling
   * each PRB has different weight for a SE/UE   

## the unit of scheduling
   * SB: scheduling block, (15*12khz)* (1ms),, the smallest scheduling unit:
   * SE: scheduling unit, correspond 1 UE
   * internal scheduling queue:
      - Radio bearer for DL,
      - LCG for UL

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

# Reference
* internal LTE RRM trainning video
* 温金辉: 深入理解LTE-A
* Moray Rumney, LTE and the Evolution to 4G Wireless
* http://sharetechnote.com/


