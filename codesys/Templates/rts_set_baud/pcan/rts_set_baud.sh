#!/bin/sh
CAN_NUM=$(echo $1 | sed 's,^can\([0-9]*\).*,\1,')
./pcan /dev/pcanusb$CAN_NUM $2
