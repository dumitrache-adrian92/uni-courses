import subprocess

msg = b'FIRE_NUKES_MELA!'
new = b'SEND_NUDES_MELA!'
IV = ''

with open('original_iv', 'r') as f:
    IV = f.read().strip()

iv = bytes.fromhex(IV)
new_iv = b''

# iv ^ msg = enc
# new_iv ^ new = enc => new_iv = enc ^ new = iv ^ msg ^ new
for i in range(16):
    new_iv += bytes([iv[i] ^ msg[i] ^ new[i]])
new_iv = new_iv.hex()

proc = subprocess.Popen(['./oracle', new_iv])
proc.wait()
