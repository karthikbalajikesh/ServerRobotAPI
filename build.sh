#!/bin/bash

# Script to build the project with cmake

echo "building the project"

cd build 

rm -rf *

cmake .. -G "CodeBlocks - Unix Makefiles"
