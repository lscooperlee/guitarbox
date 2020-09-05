#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include "DrumPattern.h"

#include <jack/jack.h>

class AudioPlayer {
public:
  AudioPlayer();
  ~AudioPlayer();
  void play(DrumPattern::audio_type data_);

private:
  friend int process(jack_nframes_t nframes, void *data);

  jack_client_t *jack_client = nullptr;
  jack_port_t *out = nullptr;
  unsigned int current_frame = 0;
  int amp = 1;
  DrumPattern::audio_type data = {};
};

#endif /* AUDIOPLAYER_H */
