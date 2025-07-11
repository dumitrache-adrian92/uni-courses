#!/usr/bin/python3

import sys

def main():
    cipher={'A':'A',
            'B':'Y',
            'C':'W',
            'D':'M',
            'E':'C',
            'F':'N',
            'G':'O',
            'H':'P',
            'I':'H',
            'J':'Q',
            'K':'R',
            'L':'S',
            'M':'T',
            'N':'Z',
            'O':'I',
            'Q':'K',
            'R':'D',
            'S':'L',
            'T':'E',
            'U':'G',
            'V':'X',
            'W':'U',
            'X':'V',
            'Y':'F',
            'Z':'B'
            }
    with open (sys.argv[1]) as text:
        f=text.read()
        for i in range(0, len(f)):
            if (f[i] in cipher) == True:
                print("\033[1;31m%s\033[0m" % (cipher[f[i]]), end="")
            else:
                print(f[i], end="")

if __name__ == '__main__':
    main()