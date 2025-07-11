def otp(cipher, key):
    res = ''
    for c in cipher:
        res = res + chr(c ^ key)
    return res

with open("isc-lab02-otp.txt", "rb") as f:
    enc = f.read()

for i in range(256):
    res = otp(enc, i)
    if res.isprintable():
        print(res)