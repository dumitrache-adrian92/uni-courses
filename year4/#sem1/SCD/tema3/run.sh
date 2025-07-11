#!/bin/bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
docker build -t scd2024/adapter "$SCRIPT_DIR"/adapter

docker swarm init
docker stack deploy -c stack.yml scd3
