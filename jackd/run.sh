/usr/bin/jackd -P99 -dalsa -r48000 -p512 -n2 -S -M -D -Chw:CODEC,0 -Phw:CODEC

sleep 1

jack_connect system:capture_1 gx_head_amp:in_0
jack_connect  gx_head_amp:out_0 gx_head_fx:in_0
jack_connect  gx_head_fx:out_0 system:playback_1
jack_connect  gx_head_fx:out_1 system:playback_2

#fluidsynth --server --audio-driver=jack --connect-jack-outputs /usr/share/soundfonts/FluidR3_GM.sf2 -d
