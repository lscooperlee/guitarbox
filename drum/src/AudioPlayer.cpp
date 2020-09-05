#include "AudioPlayer.h"
#include "DrumPattern.h"

#include <iostream>

typedef jack_default_audio_sample_t sample_t;

int process(jack_nframes_t nframes, void *data) {
  AudioPlayer *player = static_cast<AudioPlayer *>(data);
  sample_t *out =
      static_cast<sample_t *>(jack_port_get_buffer(player->out, nframes));

  //  memset(out, 0, sizeof(sample_t) * nframes);

  // window->enabled_mutex.lock();
  // if (window->enabled) {

  for (unsigned int i = 0; i < nframes; ++i) {
    // if (player->cur_frame < player->wav_len) {
    // out[i] = player->amp * player->wav[player->cur_frame];
    //++window->cur_frame;
    //}
  }

  //}
  // window->enabled_mutex.unlock();

  return 0;
}

AudioPlayer::AudioPlayer() {
  std::cout << "jack start" << std::endl;

  jack_client = jack_client_open("Drum machine", JackNullOption, nullptr);

  if (jack_client == nullptr) {
    std::cout << "jack open error" << std::endl;
  }

  out = jack_port_register(jack_client, "out", JACK_DEFAULT_AUDIO_TYPE,
                           JackPortIsOutput, 0);
  if (out == nullptr) {
    std::cout << "jack register error" << std::endl;
    jack_client_close(jack_client);
  }

  jack_set_process_callback(jack_client, &process, this);

  if (jack_activate(jack_client)) {
    jack_port_unregister(jack_client, out);
    jack_client_close(jack_client);
    std::cout << "jack activate error" << std::endl;
  }
}

AudioPlayer::~AudioPlayer() {
  jack_port_unregister(jack_client, out);
  jack_client_close(jack_client);
}

void AudioPlayer::play(DrumPattern::audio_type data) {
  std::cout << "audio play" << std::endl;
}
