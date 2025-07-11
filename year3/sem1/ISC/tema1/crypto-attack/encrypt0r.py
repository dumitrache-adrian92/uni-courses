#!/usr/bin/env python3

import base64
import json
import gmpy2

def str_to_number(text):
    """ Encodes a text to a long number representation (big endian). """
    return int.from_bytes(text.encode("ASCII"), 'big')

def number_to_str(num):
    """ Decodes a text to a long number representation (big endian). """
    num = int(num)
    return num.to_bytes((num.bit_length() + 7) // 8, byteorder='big').decode('ASCII')

def encrypt(pub_k, msg_num):
    """ We only managed to steal this function... """
    cipher_num = gmpy2.powmod(msg_num, pub_k["e"], pub_k["n"])
    # note: gmpy's to_binary uses a custom format (little endian + special GMPY header)!
    cipher_b64 = base64.b64encode(gmpy2.to_binary(cipher_num))
    return cipher_b64

def decrypt(priv_k, cipher):
    """ We don't have the privary key, anyway :( """
    # you'll never get it!
    pass


if __name__ == "__main__":
    # public key
    pub_k = {"e": 425207, "n": 10698506624831129730761861233813354967289673747790853929839597311144848213553868575280809016377185399741519358410139537305031072024501237006407298286239730415856268766311600255605785615278755147439132705117114094663726482021958870743680196193647504692651234705657453594797384135188423215451050474820823974729075535142829182018117064322557490825031066162064784903497615468864117525635321502135976921071845266005383809209011604443882336143676607315772460888329740518338076170906347270380806976014557237907278037281598932362331956866368376256847239506812606963459291038208773464194069084824761989276791338089322989497163}

    # send a modified ciphertext to the server and have the server translate it
    ciphertext = "AQF87zeHLUv5PbMNTvf9XAGcQWTNK6KvkCBACq2E0RtyGtbV6F7aEH9UYkMlCKVIQJqz588Rm7BJGVC3BzCIKsd5Y6HduHrjTq6AGd2s7jD4u41ex3fehb2uaO1PXap+EzTdXk+/8rlAhppexY2N1ICALdIwfFLnhwecu2UjFm5EciDBWqCsJrWpdRb2xR8sFU/lkgfr1jNaFK0zCNkqq9KbUGDIUXalp6Dwo4gfDkzYlsvmMXI9USWMnxixNyZllKN6We9Py7EgPV/IL1nve5yIOmhby+Sss2PoEL5UQ+rWJxVIk2wpL/LcOOO5RDA2XH7o5St9lDdir7Eb/ZUVqCIx"
    number = gmpy2.from_binary(base64.b64decode(ciphertext))

    input = gmpy2.mod(gmpy2.mul(number, gmpy2.powmod(2, pub_k["e"], pub_k["n"])), pub_k["n"])
    input = base64.b64encode(gmpy2.to_binary(input))

    # data that we can send to server
    data = json.dumps({"n" : pub_k["n"], "e" : pub_k["e"], "flag": input.decode("ASCII")})
    print(base64.b64encode(data.encode("ASCII")).decode("ASCII"))

    # use the servers response to find the plaintext of the original message
    server_output = b'\xa6\xe0\xca\xd2\xe6\xd0\x8c\xd8\xc2\xce\xf6\x9c\xaa\x9a\xceb\xa0\xe0\xe8\xb2\xd6\xa4\xec\xcc\xb0\x88\x96\x84\xe2\xa4\xee\x9e\xe0\xec\x90j\xe0\x82\xec\xac\xf4\x92\xf2\xfa'
    print(number_to_str(int.from_bytes(server_output, 'big') // 2))
