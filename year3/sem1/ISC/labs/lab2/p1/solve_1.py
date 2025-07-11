from Crypto.Cipher import AES

BLOCK_SIZE = 32
PADDING = b'#'
iv = b"\x00" * 16

with open('isc-lab02-secret.enc', 'rb') as f:
    key = f.read(BLOCK_SIZE)
    data = f.read()

decrypted_data = AES.new(key, AES.MODE_CBC, iv).decrypt(data)

with open('isc-lab02-plain.jpg', 'wb') as f:
    f.write(decrypted_data)