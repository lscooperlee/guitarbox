#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <jack/jack.h>

class AudioPlayer {
public:
  AudioPlayer();
  ~AudioPlayer();
  void play();

private:
  friend int process(jack_nframes_t nframes, void *data);

  jack_client_t *jack_client = nullptr;
  jack_port_t *out = nullptr;
};

#endif /* AUDIOPLAYER_H */
