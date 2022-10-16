#!/bin/bash 

# change to current working directory
cd `dirname $0`

# just for output
clear

# target device (doesn't matter here)
DEVICE=STM8TL5x

# set make tool (if not in PATH, set complete path)
MAKE=make

# STM8TL5xxx has no bootloader, see tech note UM0560 and TN0189 on http://www.st.com

# set SWIM upload tool and device name (stm8flash from https://github.com/vdudouyt/stm8flash)
SWIM_LOADER=~/Öffentlich/GitHub/stm8flash/stm8flash
SWIM_TOOL=stlink
SWIM_DEVICE=stm8tl5??4

# target hexfile
TARGET=./$DEVICE/$DEVICE.hex

# make project
echo "make application"
$MAKE -f Makefile DEVICE=$DEVICE
if [ $? -ne 0 ]; then
  echo " "
  read -p "press key to close window..."
  echo on
  exit
fi
echo "done with application"
echo " "

# upload using SWIM debug interface
$SWIM_LOADER -c $SWIM_TOOL -w $TARGET -p $SWIM_DEVICE

echo " "
read -p "press key to close window..."
echo " "


