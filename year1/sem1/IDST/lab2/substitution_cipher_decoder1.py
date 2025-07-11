#!/usr/bin/python3

import sys

def main():
    cipher={
            'B':'D',
            'D':'X',
            'E':'V',
            'F':'H',
            'G':'B',
            'H':'G',
            'I':'A',
            'J':'S',
            'K':'F',
            'L':'O',
            'M':'J',
            'N':'K',
            'O':'T',
            'P':'I',
            'Q':'P',
            'R':'W',
            'S':'N',
            'T':'R',
            'U':'E',
            'V':'L',
            'W':'C',
            'X':'U',
            'Y':'Y',
            'Z':'M'
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