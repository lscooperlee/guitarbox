#!/bin/sh

WORKINGPATH=/home/cooper/

#/usr/bin/jackd -P99 -dalsa -r48000 -p512 -n2 -S -M -D -Chw:CODEC,0 -Phw:CODEC
nice -n -19 /usr/bin/jackd -P99 -dalsa -r48000 -p512 -n2 -S -M -D -Chw:Device,0 -Phw:Headphones &

/usr/bin/emi_core -d

sleep 0.5

cd $WORKINGPATH/virtual_keyboard/linux
.out/bin/virtual_keyboard /dev/ttyAMA0 &

cd $WORKINGPATH/guitarbox/volume/
.out/bin/volume_ctrl &

cd $WORKINGPATH/guitarbox/drum/
chrt --rr 99 .out/bin/drum_machine &

sleep 1

for i in 1 2 3
do
	/usr/bin/jack_connect drum_machine:out system:playback_1
	sleep 0.1
	/usr/bin/jack_connect drum_machine:out system:playback_2
	sleep 0.1
done

for i in 1 2 3
do
	/usr/bin/jack_connect system:capture_1 system:playback_1
	sleep 0.1
	/usr/bin/jack_connect system:capture_1 system:playback_2
	sleep 0.1
done

#fluidsynth --server --audio-driver=jack --connect-jack-outputs /usr/share/soundfonts/FluidR3_GM.sf2 -d
#jalv -c Drive=2 http://guitarix.sourceforge.net/plugins/gx_amp#GUITARIX
#mpv -ao=jack --loop-file chongerfei.wav

exit 0
