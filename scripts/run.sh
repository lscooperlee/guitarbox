#!/bin/sh

WORKINGPATH=/home/cooper/

nice -n -19 /usr/bin/jackd -P99 -dalsa -r48000 -p512 -n2 -S -M -D `cat /tmp/config` &
#nice -n -19 /usr/bin/jackd -P99 -dalsa -r48000 -p512 -n2 -S -M -D -Chw:CODEC,0 -Phw:CODEC &
#nice -n -19 /usr/bin/jackd -P99 -dalsa -r48000 -p512 -n2 -S -M -D -Chw:Device,0 -Phw:Headphones &


cd $WORKINGPATH/guitarbox/volume/
.out/bin/volume_ctrl &

cd $WORKINGPATH/guitarbox/effects/
python effects.py &

sleep 1

cd $WORKINGPATH/guitarbox/drum/
chrt --rr 99 .out/bin/drum_machine &

for i in 1 2 3
do
	/usr/bin/jack_connect system:capture_1 system:playback_1
	sleep 0.1
	/usr/bin/jack_connect system:capture_1 system:playback_2
	sleep 0.1
done


fluidsynth --server --audio-driver=jack --connect-jack-outputs /usr/share/soundfonts/FluidR3_GM.sf2 -i &
#jalv -i -c Drive=2 http://guitarix.sourceforge.net/plugins/gx_amp#GUITARIX
#mpv -ao=jack --loop-file chongerfei.wav

exit 0
