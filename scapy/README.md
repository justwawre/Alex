# overview

https://scapy.net/



In other words, Scapy is a powerful interactive packet manipulation program. It is able to forge or decode packets of a wide number of protocols, send them on the wire, capture them, match requests and replies, and much more. Scapy’s paradigm is to propose a Domain Specific Language (DSL) that enables a powerful and fast description of any kind of packet.

# install

centos

    [alex@scapy]$pip3 install scapy pyx PyGnuplot
    Successfully installed scapy-2.4.0
    [alex@scapy]$conda install matplotlib graphviz 
    [alex@scapy]$sudo yum install  python-cryptography sox gnuplot
    [alex@scapy]$scapy    //to send packet ,need running as root


# run scapy

    >>> ls()      //list the layers supported
    AH         : AH
    ARP        : ARP
    ASN1P_INTEGER : None
    ASN1P_OID  : None
    ASN1P_PRIVSEQ : None
    ASN1_Packet : None


    >>> ls(IP)    //list the attribute of the layer
    version    : BitField (4 bits)                   = (4)
    ihl        : BitField (4 bits)                   = (None)
    tos        : XByteField                          = (0)
    len        : ShortField                          = (None)
    id         : ShortField                          = (1)
    flags      : FlagsField (3 bits)                 = (<Flag 0 ()>)
    frag       : BitField (13 bits)                  = (0)
    ttl        : ByteField                           = (64)
    proto      : ByteEnumField                       = (0)
    chksum     : XShortField                         = (None)
    src        : SourceIPField                       = (None)
    dst        : DestIPField                         = (None)
    options    : PacketListField                     = ([])

    >>> help(sendp)    //get help of 1 func    


## compose some packet
    >>> a=Ether()/IP(dst="www.baidu.com")/"GET / HTTP/1.0\r\n\r\n"
    >>> a
    <Ether  type=0x800 |<IP  dst=Net('www.baidu.com') |<Raw  load='GET / HTTP/1.0\r\n\r\n' |>>>


    >>> b=Ether()/IP(dst="www.baidu.com")/ICMP()
    >>> b
    <Ether  type=0x800 |<IP  frag=0 proto=icmp dst=Net('www.baidu.com') |<ICMP  |>>>
    >>>     

 ## send/receive packet

    >>>  p = sr1(IP(dst="www.slashdot.org")/ICMP())
    Begin emission:
    Finished sending 1 packets.
    *
    Received 1 packets, got 1 answers, remaining 0 packets
    >>> p
    <IP  version=4 ihl=5 tos=0x0 len=39 id=55252 flags= frag=0 ttl=45 proto=icmp chksum=0xf3de src=216.105.38.15 dst=192.168.3.2 options=[] |<ICMP  type=echo-reply code=0 chksum=0xee45 id=0x0 seq=0x0 |<Raw  load='XXXXXXXXXXX' |<Padding  load='\x00\x00\x00\x00\x00\x00\x00' |>>>>
    >>> p.show()
    ###[ IP ]### 
    version= 4
    ihl= 5
    tos= 0x0
    len= 39
    id= 10350
    flags= 
    frag= 0
    ttl= 45
    proto= icmp
    chksum= 0xa345
    src= 216.105.38.15
    dst= 192.168.3.2
    \options\
    ###[ ICMP ]### 
        type= echo-reply
        code= 0
        chksum= 0xee45
        id= 0x0
        seq= 0x0
    ###[ Raw ]### 
            load= 'XXXXXXXXXXX'
    ###[ Padding ]### 
            load= '\x00\x00\x00\x00\x00\x00\x00'  


## emulate a DNS query

    >>> p=sr1(IP(dst="114.114.114.114")/UDP()/DNS(rd=1,qd=DNSQR(qname="www.slashdot.org")))
    Begin emission:
    .Finished sending 1 packets.
    ........*
    Received 10 packets, got 1 answers, remaining 0 packets
    >>> p.show()
    ###[ IP ]### 
    version= 4
    ihl= 5
    tos= 0x0
    len= 183
    id= 0
    flags= 
    frag= 0
    ttl= 149
    proto= udp
    chksum= 0x7ca7
    src= 114.114.114.114
    dst= 192.168.3.2
    \options\
    ###[ UDP ]### 
        sport= domain
        dport= domain
        len= 163
        chksum= 0x2c7c
    ###[ DNS ]### 
            id= 0             

## dig

    [alex@~]$dig www.baidu.com

    ; <<>> DiG 9.9.4-RedHat-9.9.4-61.el7_5.1 <<>> www.baidu.com
    ;; global options: +cmd
    ;; Got answer:
    ;; ->>HEADER<<- opcode: QUERY, status: NOERROR, id: 51909
    ;; flags: qr aa rd ra; QUERY: 1, ANSWER: 2, AUTHORITY: 0, ADDITIONAL: 1

    ;; OPT PSEUDOSECTION:
    ; EDNS: version: 0, flags:; udp: 4096
    ;; QUESTION SECTION:
    ;www.baidu.com.			IN	A

    ;; ANSWER SECTION:
    www.baidu.com.		300	IN	A	183.232.231.173
    www.baidu.com.		300	IN	A	183.232.231.172

    ;; Query time: 5 msec
    ;; SERVER: 114.114.114.114#53(114.114.114.114)
    ;; WHEN: Sat Nov 24 19:32:50 CST 2018
    ;; MSG SIZE  rcvd: 74

## sr

return a couple of two lists. The first element is a list of couples (packet sent, answer), and the second element is the list of unanswered packets.

    >>>  p = sr(IP(dst="www.slashdot.org")/ICMP())
    Begin emission:
    ..Finished sending 1 packets.
    *
    Received 3 packets, got 1 answers, remaining 0 packets
    >>> ans,unans=_
    >>> ans
    <Results: TCP:0 UDP:0 ICMP:1 Other:0>
    >>> ans.summary()
    IP / ICMP 192.168.3.2 > 216.105.38.15 echo-request 0 / Raw ==> IP / ICMP 216.105.38.15 > 192.168.3.2 echo-reply 0 / Raw / Padding
    >>> 

or

    >>> ans,unans = sr(IP(dst="www.baidu.com")/ICMP())
    Begin emission:
    ..Finished sending 1 packets.
    *
    Received 3 packets, got 1 answers, remaining 0 packets
    >>> ans.summary()
    IP / ICMP 192.168.3.2 > 117.185.16.31 echo-request 0 ==> IP / ICMP 117.185.16.31 > 192.168.3.2 echo-reply 0 / Padding
    >>>     

## list commands

    >>> lsc()
    IPID_count          : Identify IP id values classes in a list of packets
    arpcachepoison      : Poison target's cache with (your MAC,victim's IP) couple
    arping              : Send ARP who-has requests to determine which hosts are up
    bind_layers         : Bind 2 layers on some specific fields' values
    bridge_and_sniff    : Forward traffic between interfaces if1 and if2, sniff and return
    chexdump            :  Build a per byte hexadecimal representation
    computeNIGroupAddr  : Compute the NI group Address. Can take a FQDN as input parameter
    corrupt_bits        : Flip a given percentage or number of bits from a string
    corrupt_bytes       : Corrupt a given percentage or number of bytes from a string
    ...............    


## emulate traceroute

    >>> ans, unans =  traceroute(["www.baidu.com"], verbose=1)
    Begin emission:
    Finished sending 30 packets.

    Received 52 packets, got 24 answers, remaining 6 packets

    >>> ans.summary()
    IP / TCP 192.168.3.2:scientia_ssdb > 117.185.16.31:http S ==> IP / ICMP 192.168.3.1 > 192.168.3.2 time-exceeded ttl-zero-during-transit / IPerror / TCPerror
    IP / TCP 192.168.3.2:7193 > 117.185.16.31:http S ==> IP / ICMP 10.88.128.1 > 192.168.3.2 time-exceeded ttl-zero-during-transit / IPerror / TCPerror
    IP / TCP 192.168.3.2:38882 > 117.185.16.31:http S ==> IP / TCP 117.185.16.31:http > 192.168.3.2:38882 SA / Padding
    IP / TCP 192.168.3.2:10595 > 117.185.16.31:http S ==> IP / TCP 117.185.16.31:http > 192.168.3.2:10595 SA / Padding
    IP / TCP 192.168.3.2:44257 > 117.185.16.31:http S ==> IP / TCP 117.185.16.31:http > 192.168.3.2:44257 SA / Padding
    IP / TCP 192.168.3.2:22839 > 117.185.16.31:http S ==> IP / TCP 117.185.16.31:http > 192.168.3.2:22839 SA / Padding
    IP / TCP 192.168.3.2:44986 > 117.185.16.31:http S ==> IP / TCP 117.185.16.31:http > 192.168.3.2:44986 SA / Padding
    IP / TCP 192.168.3.2:8848 > 117.185.16.31:http S ==> IP / TCP 117.185.16.31:http > 19

## sniffer
you can sniffer the packet, and draw pics


## arp

    >>> ans, unans =arping("192.168.3.1")
    Begin emission:
    Finished sending 1 packets.
    *
    Received 1 packets, got 1 answers, remaining 0 packets
    34:79:16:00:d3:bf 192.168.3.1
    >>> ans.summary()
    Ether / ARP who has 192.168.3.1 says 192.168.3.2 ==> Ether / ARP is at 34:79:16:00:d3:bf says 192.168.3.1

    >>> [x for x in ans]
    [(<Ether  dst=ff:ff:ff:ff:ff:ff type=ARP |<ARP  pdst=192.168.3.1 |>>,
    <Ether  dst=78:0c:b8:f9:32:d3 src=34:79:16:00:d3:bf type=ARP |<ARP  hwtype=0x1 ptype=0x800 hwlen=6 plen=4 op=is-at hwsrc=34:79:16:00:d3:bf psrc=192.168.3.1 hwdst=78:0c:b8:f9:32:d3 pdst=192.168.3.2 |>>)]

    >>>  wrpcap("demo.pcap",ans)  //create a pcap file

## rtp

    >>> load_contrib("pnio_rtc")
    >>> p=PNIORealTime(cycleCounter=1024, data=[PNIORealTimeIOxS(),PNIORealTimeRawData(load='AAA', config={'length':4}) / PNIORealTimeIOxS(),Profisafe(load='AAA', Control_Status=0x20, CRC=0x424242, config={'length':
    ...: 8, 'CRC': 3}) / PNIORealTimeIOxS(),])
    >>> p.show()
    ###[ PROFINET Real-Time ]### 
    len= None
    dataLen= None
    \data\
    |###[ PNIO RTC IOxS ]### 
    |  dataState= good
    |  instance= subslot
    |  reserved= 0x0
    |  extension= 0
    |###[ PNIO RTC Raw data ]### 


# first simple program

    root@alex:/home/alex/base/python/scapy #python3 test.py 
    IP / TCP 13.250.177.223:http > 192.168.3.2:ftp_data SA / Padding


# ref:
https://github.com/secdev/scapy/


