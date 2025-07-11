#!/usr/bin/python3
import socket
import threading
import struct
import time
from diffiehellman import DiffieHellman
from Crypto.Cipher import AES
from hashlib import sha256

host = '127.0.01'
mitm_port = 1337

CONTENT_LENGTH = 128
PACKET_LENGTH = (3 + 128 + 4)  # MSG_TYPE(3) | CONTENT(128) | TIME(4)
MAX_ACCEPTED_DELAY = 3

BLOCK_SIZE = 32
PADDING = b'#'
iv = b'\00' * 16
shared_key = None

def verify_time(packet_time):
    current_time = int(time.time())

    if current_time - packet_time > MAX_ACCEPTED_DELAY:  # max accepted delay is 3 seconds
        return False

    return True


def pad_packet_content(packet_content):
    return packet_content + PADDING * (CONTENT_LENGTH - len(packet_content))


def assemble_packet(packet_type, packet_content, is_key_packet):
    packet_time = int(time.time())

    if len(packet_content) < CONTENT_LENGTH:
        packet_content = pad_packet_content(packet_content)

    elif len(packet_content) > CONTENT_LENGTH:
        packet_content = packet_content[:CONTENT_LENGTH + 1]

    enc_time = struct.pack(">L", packet_time)
    if not is_key_packet:
        # encrypt the content if is not a key packet
        packet = packet_type.encode() + encrypt_message(packet_content) + enc_time
    else:
        # do not encrypt if is an auth packet
        packet = packet_type.encode() + packet_content + enc_time

    return packet


def compute_shared_key(other_key):
    global shared_key
    global dh
    shared_key = sha256(dh.generate_shared_key(other_key)).digest()
    print("MITM: shared key:", shared_key, flush=True)


def encrypt_message(message):
    global shared_key
    aes = AES.new(shared_key, AES.MODE_CBC, iv)
    encrypted_message = aes.encrypt(message)
    return encrypted_message


def decrypt_message(message):
    global shared_key
    aes = AES.new(shared_key, AES.MODE_CBC, iv)
    decrypted_message = aes.decrypt(message)
    return decrypted_message.decode("ASCII", "ignore")


def send_func(sock, packet, addr):
    print("MITM: send", packet, addr, flush=True)
    sock.sendto(packet, addr)


def receive_func(sock):
    clientPublicKey = None
    serverPublicKey = None

    while True:
        data, from_addr = sock.recvfrom(PACKET_LENGTH)
        packet_time = struct.unpack(">L", data[-4:])[0]
        if not verify_time(packet_time):
            send_func(sock, assemble_packet('MSG', 'ERROR'.encode(), False), from_addr)

        packet_type = data[:3]  # first 3 bytes
        packet_data = data[3:-4]  # the content
        packet_type = packet_type.decode()
        print("MITM: got packet", packet_type, packet_data, flush=True)

        if packet_type == 'KEY':
            global dh
            if from_addr[1] == 1336:
                clientPublicKey = packet_data
                send_func(sock, assemble_packet('KEY', dh.get_public_key(), True), (host, 1338))
            elif from_addr[1] == 1338:
                serverPublicKey = packet_data
                send_func(sock, assemble_packet('KEY', dh.get_public_key(), True), (host, 1336))
        elif packet_type == 'MSG':
            if from_addr[1] == 1336:
                compute_shared_key(clientPublicKey)
                decrypted = decrypt_message(packet_data)
                compute_shared_key(serverPublicKey)
                if decrypted.startswith("GIFF_ME_FLAG"):
                    send_func(sock, assemble_packet('MSG', decrypted.encode(), False), (host, 1338))
            elif from_addr[1] == 1338:
                compute_shared_key(serverPublicKey)
                print(decrypt_message(packet_data), flush=True)  # print flag


def main():
    global dh
    dh = DiffieHellman(group=2)

    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as sock:
        sock.bind((host, mitm_port))

        threaded_receive = threading.Thread(target=receive_func, args=(sock,))
        threaded_receive.start()
        threaded_receive.join()


if __name__ == '__main__':
    main()
