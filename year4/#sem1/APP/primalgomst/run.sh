#!/bin/bash

for file in bin/*; do
	filename=$(basename "$file")
	./wrapper.sh haswell 32 $filename
done
