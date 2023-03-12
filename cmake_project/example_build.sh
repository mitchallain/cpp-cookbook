#!/bin/bash
# Simple example invoking cmake and make to build the project
# and link the compile commands to the cookbook project root

mkdir -p build && cd build && \
    cmake .. && make && \
    ln -sf "$(pwd)"/compile_commands.json ../../compile_commands.json
