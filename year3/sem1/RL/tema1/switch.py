#!/usr/bin/python3
import sys
import struct
import wrapper
import threading
import time
import ipaddress
from wrapper import recv_from_any_link, send_to_link, get_switch_mac, get_interface_name

def parse_ethernet_header(data):
    # Unpack the header fields from the byte array
    #dest_mac, src_mac, ethertype = struct.unpack('!6s6sH', data[:14])
    dest_mac = data[0:6]
    src_mac = data[6:12]

    # Extract ethertype. Under 802.1Q, this may be the bytes from the VLAN TAG
    ether_type = (data[12] << 8) + data[13]
    vlan_id = -1
    # Check for VLAN tag (0x8100 in network byte order is b'\x81\x00')
    if ether_type == 0x8200:
        vlan_tci = int.from_bytes(data[14:16], byteorder='big')
        vlan_id = vlan_tci & 0x0FFF  # extract the 12-bit VLAN ID
        ether_type = (data[16] << 8) + data[17]

    return dest_mac, src_mac, ether_type, vlan_id

def create_vlan_tag(vlan_id):
    # 0x8100 for the Ethertype for 802.1Q
    # vlan_id & 0x0FFF ensures that only the last 12 bits are used
    return struct.pack('!H', 0x8200) + struct.pack('!H', vlan_id & 0x0FFF)

def send_bdpu_every_sec():
    while True:
        # TODO Send BDPU every second if necessary
        time.sleep(1)

def parse_VLAN (file_path,VLAN_TABLE):
    with open(file_path, "r") as file:
        priority = int(file.readline().strip())
        # Split the line into fields by whitespaces
        for line in file:
            fields = line.split()
            int_name = fields[0]
            vlan = fields[1]
            VLAN_TABLE[int_name] = vlan
    return VLAN_TABLE

def main():
    # init returns the max interface number. Our interfaces
    # are 0, 1, 2, ..., init_ret value + 1
    switch_id = sys.argv[1]

    num_interfaces = wrapper.init(sys.argv[2:])
    interfaces = range(0, num_interfaces)

    print("# Starting switch with id {}".format(switch_id), flush=True)
    print("[INFO] Switch MAC", ':'.join(f'{b:02x}' for b in get_switch_mac()))

    # Create and start a new thread that deals with sending BDPU
    t = threading.Thread(target=send_bdpu_every_sec)
    t.start()

    # Printing interface names
    for i in interfaces:
        print(get_interface_name(i))

    # Tabele CAM - SWITCH -> MAC - PORT
    CAM_TABLE = {} # the key is the mac addr and the value is the interface
    VLAN_TABLE = {}
    next_interface = -1
    interface_name = ''
    next_interface_name = ''
    file_path = "configs/switch"
    file_path += switch_id  +".cfg"
    VLAN_TABLE = parse_VLAN(file_path,VLAN_TABLE)


    while True:
        # Note that data is of type bytes([...]).
        # b1 = bytes([72, 101, 108, 108, 111])  # "Hello"
        # b2 = bytes([32, 87, 111, 114, 108, 100])  # " World"
        # b3 = b1[0:2] + b[3:4].
        interface, data, length = recv_from_any_link()

        dest_mac, src_mac, ethertype, vlan_id = parse_ethernet_header(data)
        sent = False

        # remove tag when we receive a frame
        if vlan_id != -1 :
            data = data[0:12] + data[16:]
            length -=4
        else :
            vlan_id = int(VLAN_TABLE[get_interface_name(interface)])

        # Print the MAC src and MAC dst in human readable format
        dest_mac = ':'.join(f'{b:02x}' for b in dest_mac)
        src_mac = ':'.join(f'{b:02x}' for b in src_mac)

        # Note. Adding a VLAN tag can be as easy as
        # tagged_frame = data[0:12] + create_vlan_tag(10) + data[12:]
        print(f'Destination MAC: {dest_mac}')
        print(f'Source MAC: {src_mac}')
        print(f'EtherType: {ethertype}')
        print("Received frame of size {} on interface {}".format(length, interface), flush=True)

        # TODO: Implement forwarding with learning
        CAM_TABLE[src_mac] = interface
        interface_name = get_interface_name(interface)
        if dest_mac in CAM_TABLE:
            next_interface = CAM_TABLE[dest_mac]
            next_interface_name = get_interface_name(next_interface)
            if VLAN_TABLE[next_interface_name] == 'T' :
                    tag = create_vlan_tag(vlan_id)
                    data = data[0:12] + tag + data[12:]
                    length += 4
                    send_to_link(next_interface, data, length)
                    sent = True
            elif vlan_id == int(VLAN_TABLE[next_interface_name]) :
                send_to_link(next_interface, data, length)
                sent = True


        if sent is False :
            for o in interfaces:
                if  o != interface :
                    next_interface = o
                    next_interface_name = get_interface_name(next_interface)
                    if VLAN_TABLE[next_interface_name] == 'T' :
                            tag = create_vlan_tag(vlan_id)
                            data = data[0:12] + tag + data[12:]
                            length += 4
                            send_to_link(next_interface, data, length)
                    elif vlan_id ==  int(VLAN_TABLE[next_interface_name]) :
                        send_to_link(next_interface, data, length)


        # TODO: Implement VLAN support

        # TODO: Implement STP support

        # data is of type bytes.
        # send_to_link(i, data, length)

if __name__ == "__main__":
    main()