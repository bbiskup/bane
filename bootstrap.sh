#!/bin/bash

# Create/update build files and build project

./docker-cmd.sh "mkdir -p build && cd build && cmake -G Ninja .. && ninja"
