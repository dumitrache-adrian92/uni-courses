from Crypto.Cipher import AES
from Crypto import Random

BLOCK_SIZE = 32
PADDING = b'#'
iv = b"\x00" * 16

def encrypt(key, iv, data):
    aes = AES.new(key, AES.MODE_CBC, iv)
    data = aes.encrypt(data)
    return data

def pad(s):
    return s + (BLOCK_SIZE - len(s) % BLOCK_SIZE) * PADDING

key = Random.new().read(BLOCK_SIZE)

with open('plain.jpg', 'rb') as f:
    data = f.read()

enc = encrypt(key, iv, pad(data))

f_out = open("secret.enc", 'wb')
f_out.write(key)
f_out.write(enc)
f_out.close()