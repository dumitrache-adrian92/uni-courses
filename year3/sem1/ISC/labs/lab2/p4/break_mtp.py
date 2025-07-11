#!/usr/bin/python3

# HINT 1: https://en.wikipedia.org/wiki/One-time_pad
# HINT 2: we know that the key starts with 'ALEXCTF{'


# decrypt_part - partially decrypts all messages with a partial key
#   @c : list of encrypted messages
#   @k : partial key
def decrypt_part(c, k):
    k = k.encode()
    m = [ ''.join([ chr(c[i][j] ^ k[j]) for j in range(min(len(k), len(c[i]))) ]) for i in range(len(c)) ]

    for i, x in enumerate(m):
        print('%2d : %s' % (i, x))
    print()

# reveal_key - partially reveals the key, knowing the first few characters
#   @c : _one_ encrypted message
#   @m : partial plain text
def reveal_key(c, m):
    m = m.encode()
    k = ''.join([ chr(c[i] ^ m[i]) for i in range(min(len(c), len(m))) ])

    print(k)


def main():
    # c contains the hex decoded lines in the input file
    with open('many_time_pad.txt') as f:
        c = f.read()
        c = c.split('\n')[:-1]
        c = [ bytes.fromhex(it) for it in c ]

    # steps I took:
    # c[0] "Dear Friend, " => ALEXCTF{HERE_
    # c[10] "ncryption scheme" => ALEXCTF{HERE_GOE
    # c[1] "nderstood my mistake" => ALEXCTF{HERE_GOES_TH
    # c[4], 'is the only encryption' => ALEXCTF{HERE_GOES_THE
    # c[5], 'hod that is mathematically' => ALEXCTF{HERE_GOES_THE_KEY}
    decrypt_part(c,  'ALEXCTF{HERE_GOES_THE_KEY}')
    reveal_key(c[5], 'hod that is mathematically')

if __name__ == '__main__':
    main()