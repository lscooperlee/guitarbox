#!/bin/sh

systemctl start bluetooth

bluealsa &

bluetoothctl -- power on

sleep 1

bluetoothctl -- scan on

sleep 1

bluetoothctl -- pair 00:0B:97:45:31:2C

sleep 1

bluetoothctl -- connect 00:0B:97:45:31:2C

sleep 1

bluetoothctl -- trust 00:0B:97:45:31:2C

sleep 1

#echo 
#"
#defaults.bluealsa.service "org.bluealsa"
#defaults.bluealsa.device "00:0B:97:45:31:2C"
#defaults.bluealsa.profile "a2dp"
#defaults.bluealsa.delay 10000
#"
#> /etc/asound.conf

echo '-Chw:CODEC,0 -Pbluealsa' > /tmp/config

run.sh
