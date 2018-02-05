#!/bin/sh
BITRATE=`expr $2 \\* 1000`

ifconfig $1 down
echo ip link set $1 type can bitrate $BITRATE
ip link set $1 type can bitrate $BITRATE
ifconfig $1 up





