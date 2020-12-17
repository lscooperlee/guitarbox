#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <jack/jack.h>

#include "plugin.h"

class AudioPlayer {
public:
  AudioPlayer(Plugin &p);
  ~AudioPlayer();

  void play();

private:
  friend int process(jack_nframes_t nframes, void *data);

  jack_client_t *jack_client = nullptr;
  jack_port_t *out = nullptr;
  jack_port_t *in = nullptr;

  Plugin &plugin;
};

#endif /* AUDIOPLAYER_H */
