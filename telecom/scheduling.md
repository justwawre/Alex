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
   * via SR & BSR, classified by LCG 
   
   UE通过SR告诉eNodeB是否需要上行资源以便用于UL-SCH传输，但并不会告诉eNodeB有多少上行数据需要发送（这是通过BSR上报的）,只有处于RRC_CONNECTED态且保持上行同步的UE才会发送SR；且SR只能用于请求新传数据（而不是重传数据）的UL-SCH资源。SR的周期是通过IE：SchedulingRequestConfig的sr-ConfigIndex字段配置的。      由于SR资源是UE专用且由eNodeB分配的，因此SR资源与UE一一对应且eNodeB知道具体的对应关系。也就是说，UE在发送SR信息时，并不需要指定自己的ID（C-RNTI），eNodeB通过SR资源的位置，就知道是哪个UE请求上行资源。SR资源是通过IE：SchedulingRequestConfig的sr-PUCCH-ResourceIndex字段配置的。   UE在某些情况下可能没有SR资源。

   - 场景一：从36.331可以看出，SchedulingRequestConfig是一个UE级的可选的IE（optional），默认为release。如果 eNodeB不给某UE配置SR（这取决于不同厂商的实现），则该UE只能通过随机接入过程来获取UL grant（在RAR中分配）。是否配置SR主要影响用户面的延迟，并不影响上行传输的功能！   
   - 场景二：UE在获得初始同步以后，随着时间的推移，由于信道情况的改变或者UE（以及eNodeB）的时钟漂移，UE可能重新变为失步状态。为此eNodeB会周期性的为UE发送TA命令，指导UE进行上行的同步，并且eNodeB为每个UE配置了一个Time Alignment Timer，规定了TA的有效期，为此eNodeB需要在UE的能力和系统的开销之间进行折中。UE在每次接收到eNodeB的TA命令后，都将此定时器重置为零。在Time Alignment Timer超时以后，如果UE未能收到任何的TA命令，那么UE认为上行已经失步，此时UE不能再进行任何的上行数据传输，而必须通过随机接入的过程来对上行的TA进行重新初始化。当UE丢失了上行同步，它也会释放SR资源，如果此时有上行数据要发送，也需要触发随机接入过程。

   * explicit granted via PDCCH or implicit grant e.g. IUA (SPS of interval 1/2/4ms)
   * RAR of RACH process

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
