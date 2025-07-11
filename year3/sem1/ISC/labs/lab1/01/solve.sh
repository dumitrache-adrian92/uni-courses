#!/bin/bash
lol="$(cat b64.txt)"
decoded_lol="$(echo "$lol" | base64 -d)"
grepdata="$(echo "$decoded_lol" | grep -oE "FLAG")"

while [[ -z "$grepdata" ]]
do
    lol="$decoded_lol"
    decoded_lol="$(echo "$lol" | base64 -d)"
    grepdata="$(echo "$decoded_lol" | grep -oE "FLAG")"
done

echo "$decoded_lol"