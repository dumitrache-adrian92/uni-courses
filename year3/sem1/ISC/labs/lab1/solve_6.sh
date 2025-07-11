#!/bin/bash
find /usr/include -maxdepth 2 -type d | xargs -L1 du --max-depth=0 | sort -s -n -k 1,1 -r