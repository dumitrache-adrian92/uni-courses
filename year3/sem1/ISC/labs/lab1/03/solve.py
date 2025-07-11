def decode_binary_string(s):
    return ''.join(chr(int(s[i*8:i*8+8],2)) for i in range(len(s)//8))

f = open("manchester.txt", "r")

current = f.read(2)
binary = ""

while current != "":
    if current == "01":
        binary += "0"
    elif current == "10":
        binary += "1"
    current = f.read(2)

n = int(binary, 2)
print(n.to_bytes((n.bit_length() + 7) // 8, 'big').decode())