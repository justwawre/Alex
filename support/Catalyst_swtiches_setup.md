# Cisco IOS

In all versions of Cisco IOS, packet routing and forwarding (switching) are distinct functions. Routing and other protocols run as Cisco IOS processes and contribute to the Routing Information Base (RIB). This is processed to generate the final IP forwarding table (FIB, Forwarding Information Base), which is used by the forwarding function of the router.

# L3 switches

In a switched network, VLANs separate devices into different collision domains and Layer 3 (L3) subnets. Devices within a VLAN can communicate with one another without requiring routing.On the contrary, devices in separate VLANs require a routing device to communicate with one another.

L2 only switches require a L3 routing device (either external to the switch or in another module onthe same chassis). A new breed of switches, however, (for example, 3550 and 3750) incorporate routing capability within the switch. The switch receives a packet, determines that it belongs to another VLAN, and sends the packet to the appropriate port on the other VLAN.

# switch Stacks

A switch stack is a set of up to nine Catalyst 3750 switches connected through their StackWise ports. One of the switches controls the operation of the stack and is called the stack master. The stack master and the other switches in the stack are stack members. The stack members use the Cisco StackWise technology to behave and work together as a unified system. Layer 2 and Layer 3 protocols present the entire switch stack as a single entity to the network.

Now IPA lab:
* Gi1/0/1 ==> switch 1,
* Gi3/0/12 ==> switch 3

# show cmd

```
Cisco3750G#show switch
Switch# Role
```
# configure 

```
Cisco3750G#config t
Enter configuration commands, one per line. End with CNTL/Z.
Cisco3750G(config)#interface vlan 14
Cisco3750G(config-if)#ip address 10.0.14.1 255.255.255.0
Cisco3750G(config-if)#interface vlan 41
Cisco3750G(config-if)#ip address 10.0.41.1 255.255.255.0
Cisco3750G(config-if)#^Z
Cisco3750G#ping ip 10.0.14.1
Type escape sequence to abort.
Sending 5, 100-byte ICMP Echos to 10.0.14.1, timeout is 2 seconds:!!!!!
Success rate is 100 percent (5/5), round-trip min/avg/max = 1/2/9 ms

Cisco3750G(config)#ip routing

Cisco3750G(config)#ip http   //HTTP server configuration

```
# hub/bridge/switch/vlan
* Mac address is per hop, ip address is e2e 
* Hub: a broadcast domain
* Bridges: connect different broadcast domains
  Layer 2 and Layer 3 addresses remain unchanged as frames transit a bridge
  for broadcast and multicast traffic, bridge is the same as Hub
* Switch: A LAN switch is a multiport bridge that allows workstations to attach directly
* Vlan: The IEEE defines VLANs as a group of devices participating in the same Layer 2 domain
