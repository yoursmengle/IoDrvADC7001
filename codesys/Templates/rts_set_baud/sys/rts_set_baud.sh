#!/bin/sh
BITRATE=`expr $2 \\* 1000`

ifconfig $1 down
echo 'echo '$BITRATE' > /sys/class/net/'$1'/can_bitrate'
`echo $BITRATE > /sys/class/net/$1/can_bitrate`
#`echo $BITRATE /sys/class/net/$1/can_bittiming/bitrate`
ifconfig $1 up



