#!/bin/bash

# run local.sh 1000 times and see if it ever fails

: > out.txt

for i in {1..1000}
do
    sudo ./local.sh checker | sudo tee -a out.txt
done