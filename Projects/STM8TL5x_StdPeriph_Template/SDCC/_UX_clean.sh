#!/bin/bash 

# change to current working directory
cd `dirname $0`

# just for output
echo off
clear

# target device (doesn't matter here)
DEVICE=STM8TL5x

# set make tool (if not in PATH, set complete path)
MAKE=make

# use Makefiles to delete outputs
$MAKE -f Makefile DEVICE=$DEVICE clean 

echo on

