#include "AudioPlayer.h"

#include <jack/jack.h>

typedef jack_default_audio_sample_t sample_t;

void AudioPlayer::play() {

  jack_client_t *jack_client =
      jack_client_open("Drum machine", JackNullOption, nullptr);

  if (jack_client == nullptr) {
  }

  //  jack_set_process_callback(jack_client, &process, this);

  jack_port_t *out = jack_port_register(
      jack_client, "out", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
  if (out == nullptr) {
    jack_client_close(jack_client);
  }

  jack_port_unregister(jack_client, out);
  jack_client_close(jack_client);
}
