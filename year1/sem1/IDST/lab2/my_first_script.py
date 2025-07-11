#!/usr/bin/python3

import sys

def main():
	print('Hello world!\nReceived %d arguments are: %s' % \
		(len(sys.argv), str(sys.argv)))

if __name__ == '__main__':
	main()
