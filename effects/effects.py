
# cmd:
# jalv -c Drive=2 http://guitarix.sourceforge.net/plugins/gx_amp#GUITARIX
# jack_connect GxAmplifier-X:in system:capture_1
# jack_connect GxAmplifier-X:out system:playback_1
# jack_connect GxAmplifier-X:out system:playback_2

from subprocess import Popen
import emilib
import signal
import time

p = None
is_effect_mode = False

def msg_func(msg):
    global p

    if msg.cmd == 0xC:
        global is_effect_mode
        is_effect_mode = True

        if p:
            p.terminate()

        time.sleep(0.5)
        args =['jack_disconnect', 'system:capture_1', 'system:playback_1']
        Popen(args)

        time.sleep(0.5)
        args =['jack_disconnect', 'system:capture_1', 'system:playback_2']
        Popen(args)

        return 0


    if msg.cmd == 0xA or msg.cmd == 0xD:
        is_effect_mode = False

        return 0


    if msg.cmd == 1 and is_effect_mode:

        if p:
            p.terminate()

        args = ['jalv','-c','Drive=1.8','http://guitarix.sourceforge.net/plugins/gx_amp#GUITARIX']

        p = Popen(args)


        time.sleep(1)
        args =['jack_connect', 'system:capture_1', 'GxAmplifier-X:in']
        t = Popen(args)
        t.wait()

        time.sleep(0.2)
        args =['jack_connect', 'GxAmplifier-X:out', 'system:playback_1']
        t = Popen(args)
        t.wait()

        time.sleep(0.2)
        args =['jack_connect', 'GxAmplifier-X:out', 'system:playback_2']
        t = Popen(args)
        t.wait()

    elif msg.cmd == 0 and is_effect_mode:

        if p:
            p.terminate()

        time.sleep(0.5)
        args =['jack_connect', 'system:capture_1', 'system:playback_1']
        Popen(args)

        time.sleep(0.5)
        args =['jack_connect', 'system:capture_1', 'system:playback_2']
        Popen(args)

#        args = ['jalv', '-c', 'Drive=0.5', '-c', 'Volumn=0.5', 'http://guitarix.sourceforge.net/plugins/gx_mxrdist_#_mxrdist_']


    return 0


def main():

    emilib.emi_init()


    emilib.emi_msg_register(101, msg_func)


    while True:
        signal.pause()




if __name__ == '__main__':
    main()

