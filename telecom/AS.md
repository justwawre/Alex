The access stratum (AS) contains the functionality associated with access to the radio network and the control of active connections between a UE and the radio network. The AS consists of a user plane and a control plane. The user plane is mainly concerned with carrying user data—e.g., internet protocol (IP) packets—through the access stratum. The control plane is concerned with controlling the connection between the UE and the network.
## User Plane
 ![User plane protocol stack](4.1-1.png)

## Control Plane
 ![Control plane protocol stack](4.1-2.png)

## Physical Layer Downlink Control Information
The eNB normally transmits many DCI messages per subframe, each using a different PDCCH. Each message is intended to be received by one or many UEs. A UE does not know which PDCCH channels have been used on a particular subframe by the eNB and, of those used, whether the PDCCH contains a DCI message intended for that UE. To receive DCI messages a UE must perform a large number of blind decodes every subframe. The DCI messages intended for that UE will be decoded successfully, whereas those not intended for that UE will fail the cyclic redundancy code (CRC) check.

The intended recipient or recipients of a DCI message are distinguished by use of a different radio network temporary identity (RNTI), which is an identifier used by the UE MAC. This identifier is encoded into the CRC of the message. A UE will be able to successfully decode only those DCI messages that contain an RNTI the UE is expecting to receive.

common RNTI ==>Common search space
* SI-RNTI and P-RNTI for system information (SI) and paging (P) messages 
* RA-RNTI for random access

ue specific RNTI ==>UE-specific search space
* the cell RNTI, or C-RNTI, SPS C-RNTI / Temporary C-RNTI

DCI carry on PDCCH, whose format is:
 ![Supported PDCCH formats](6.8.1-1.png)

PDCCH candidates monitored by a UE.
 ![](9.1.1-1.png)

 an example
  ![](4-6.png)
eNodeB在调度时，会针对每个待调度的UE，从对应的搜索空间中选择一个可用的PDCCH candidate。如果能分配到CCE就调度，否则就不调度。发给不同UE的PDCCH可以有不同的聚合等级。

DCI 有多种格式（见36.212 的5.3.3.1 节），但UE 事先并不知道接收到的PDCCH 携带的是哪种格式的DCI，也不知道该DCI 使用哪个PDCCH candidate 进行传输，所以UE 必须进行PDCCH盲检以接收对应的DCI。

UE 通过PSS/SSS，确定了物理层小区ID（PCI）和frame timing（说得通俗一点，就是subframe number #0 所在的位置，但此时还不知道system frame number）。因为小区特定的参考信号及其frequency shift（指定RS 的位置）与PCI 一一对应，所以间接确定了小区特定的参考信号及其在RB 中的位置。接着UE 就可以进行信道估计并进一步解调PBCH，从而获取system frame number、PHICH 占用的资源分布和天线端口数。再通过解调PCFICH 获取CFI，就知道了控制区域占用的OFDM符号数。至此，PCFICH的内容已经解调，PHICH的分布由PBCH确定，参考信号分布取决于物理小区ID和PBCH使用的天线端口数，从而PDCCH在一个子帧内所能占用的CCE总数就可以确定了。

虽然UE事先并不知道要接收的PDCCH携带的是哪种格式的DCI，也不知道该DCI使用哪个PDCCH candidate进行传输，但UE知道自己处于何种状态以及在该状态下期待收到的DCI信息。例如在IDLE态时UE期待收到Paging；在发起Random Access后UE期待的是RAR；在有上行数据待发送时期待UL Grant等。

并且UE知道自己的搜索空间，因此知道DCI可能分布在哪些CCE上。对于不同的期望信息，UE尝试使用相应的X-RNTI、可能的DCI format、可能的聚合等级（Aggregation Level，简称AL）去与属于自己的搜索空间内的CCE做CRC校验。如果CRC校验成功，那么UE就知道这个信息是自己需要的，也就知道相应的DCI format，从而进一步解出DCI内容。

UE不知道要收到的PDCCH使用哪种聚合等级，所以UE会把所有可能性都尝试一遍。例如：对于公共搜索空间，UE需要分别按Aggregation Level = 4和Aggregation Level = 8来搜索。当按AL = 4盲检时，16个CCE需要盲检4次，即有4个PDCCH candidate；当按AL = 8盲检时，16个CCE需要盲检2次，也就是有2个PDCCH candidates；那么对于公共空间来说，一共有4+2=6个PDCCH candidates。而对于UE特定的搜索空间，UE需要分别按Aggregation Level = 1、2、4、8来盲检一遍，此时一共有6+6+2+2=16个PDCCH candidates。（见36.213的Table 9.1.1-1）

UE在搜索空间进行盲检时，只需对可能出现的DCI format进行尝试解码，并不需要对所有的DCI format进行匹配。可能出现的DCI format取决于UE期望接收什么信息以及传输模式（见36.213的7.1节和8.0节）。例如：如果UE期待接收DL-SCH并使用TM 3，当UE对使用C-RNTI扰码的PDCCH进行解码时，只会使用自己的C-RNTI对DCI format 1A和DCI format 2A进行尝试解码。如果同时该UE期望在该子帧内接收系统信息（SI），则会使用SI-RNTI对DCI format 1A和DCI format 1C进行尝试解码。更确切地说，UE使用对应DCI format的payload长度来尝试盲检。

在成功解码PDCCH之前，UE会在每一个可能的PDCCH candidate上尝试解码，一旦解码成功就停止解码过程。

从36.213的Table 9.1.1-1可以看出，对于某种DCI format进行盲检时，可能的candidate有22个。
从36.213的7.1节和8.0节可以看出，在某种传输模式或状态下（如随机接入时使用RA-RNTI）解码时，可能的DCI format最多有2种。

所以一般情况下,UE进行PDCCH盲检的总次数不超过44（22 * 2）次。

## Medium Access Control (MAC)
The medium access control (MAC) layer is a protocol layer that runs in both the UE and the eNB. It has different behaviors when running in each, generally giving commands in the eNB and responding to them in the UE.

The random access procedure enables the UE to establish initial contact with the network, which is usually 
* the first thing a UE does after acquiring system information.
* Other scenarios in which the procedure is used are after failure of the radio link to reacquire a connection with the network, and
* during the handover procedure.

Random access can be
* contention-based or 
* non-contention-based. 
For the contention-based procedure, the physical random access channel (PRACH) preamble is chosen by the UE from a set of preambles whose configuration is broadcast in the SI messages. Since there is a possibility of two UEs choosing the same preamble at the same time, there are a few subsequent 
steps to allow the network to uniquely identify each UE. In contrast, for non-contention based random access, the eNB MAC assigns a dedicated preamble to each UE, which allows the UE to be uniquely identified from the start of the procedure.

The UE decodes the random access channel (RACH) transport channel configuration options from the SI messages. This informs the UE of the allowed random access configurations in the cell. The random access procedure is initiated by the UE’s MAC transmitting a PRACH preamble on the RACH. The eNB MAC can choose to respond to the UE’s MAC PRACH preamble with an uplink grant including an estimate of the UE’s timing alignment, or with a back-off value to the UE not to perform another random access for the signaled back-off duration. The uplink grant transmission is done on the DL-SCH transport channel
addressed with a random access radio network temporary identity (RA-RNTI).

If the eNB MAC provides an uplink grant, the UE schedules a UL-SCH transmission and starts a timing alignment timer. The eNB MAC periodically sends the timing advance MAC control element to the UE, whereupon the UE applies the timing advance and restarts its timing alignment timer. The UE MAC can also signal a scheduling request (SR) to signal to the eNB MAC that the UE needs more uplink resources. The SR can be used only if the UE’s timing alignment timer is running. After the UE’s timing alignment timer expires, the UE has to use the random access procedure before scheduling further uplink transmissions.

The MAC also participates in the contention resolution procedure. The UE MAC starts the contention resolution timer after performing a scheduled transmission in response to a random access uplink grant. If, during the period that the contention resolution timer is running, the UE MAC detects its cell radio network temporary identity (C-RNTI) on the PDCCH or detects a match of the UE’s contention resolution identity in a DL-SCH transmission addressed to the UE’s temporary C-RNTI, then the UE’s contention has been successfully resolved.

## Radio Link Controller (RLC)
The RLC has three modes of operation:
* transparent mode (TM), 
* unacknowledged mode (UM), and 
* acknowledged mode (AM).

## Packet Data Convergence Protocol (PDCP)
The packet data convergence protocol (PDCP) layer acts as a portal between the various higher layers of the protocol stack (RRC, RTP, UDP, TCP, etc.) and the RLC layer.

PDCP can operate on either of two planes,
* the control plane or
* the user plane. 
The control plane is used for RRC messages. The user plane is used for all other data.

## Radio Resource Control (RRC)
The radio resource control (RRC) layer is a layer 3 (L3) protocol in the radio interface and is located at the top of the access stratum (AS) of the air interface. The RRC provides access through which higher layer signaling entities can gain services in the form of signaling transfer from the AS.

