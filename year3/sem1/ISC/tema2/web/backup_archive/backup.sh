#!/bin/bash
# Dis iz mah backup script
# Powered by cat, ofc!

echo "can you guess what you'll find in here?" > /tmp/flag.txt
tar czf /tmp/flag.tar.gz -C /tmp/ flag.txt
# Backup website
tar czf backup-orig.tar.gz -C /var/www/ .
# Let the cat do its thing
DATE=$(date +'%Y-%m-%d' -d "$(( RANDOM % 15 + 2 )) days ago")
cat backup-orig.tar.gz /tmp/flag.tar.gz > backup-$DATE.tar.gz
rm -f backup-orig.tar.gz

