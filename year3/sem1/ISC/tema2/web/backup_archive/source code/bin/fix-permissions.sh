#!/bin/sh

# sometimes the sysadmin uploads files with the wrong permissions...
chmod 755 -R /var/www

ls -ld /var/www
echo "Done!"

