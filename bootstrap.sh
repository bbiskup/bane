#!/bin/bash

# Create/update build files and build project

mkdir -p build && cd build && cmake -G Ninja .. && ninja
