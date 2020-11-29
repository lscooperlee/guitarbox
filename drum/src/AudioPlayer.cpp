#include "AudioPlayer.h"
#include "DrumPattern.h"

#include <iostream>

typedef jack_default_audio_sample_t sample_t;

int process(jack_nframes_t nframes, void *data) {

  AudioPlayer *player = static_cast<AudioPlayer *>(data);

  sample_t *out =
      static_cast<sample_t *>(jack_port_get_buffer(player->out, nframes));

  if (player->data == nullptr) {
    for (unsigned int i = 0; i < nframes; ++i) {
      out[i] = 0;
    }
    return 0;
  }

  for (unsigned int i = 0; i < nframes; ++i) {
    if (player->current_frame < player->data->size()) {
      const auto &wav = *player->data;
      out[i] = player->amp * wav[player->current_frame];
      ++player->current_frame;
    } else {
      out[i] = 0;
    }
  }

  return 0;
}

AudioPlayer::AudioPlayer() {
  std::cout << "jack start" << std::endl;

  jack_client = jack_client_open("drum_machine", JackNullOption, nullptr);

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
  else
  {
      jack_connect(jack_client, "drum_machine:out", "system:playback_1");
      jack_connect(jack_client, "drum_machine:out", "system:playback_2");
  }
}

AudioPlayer::~AudioPlayer() {
  jack_port_unregister(jack_client, out);
  jack_client_close(jack_client);
}

void AudioPlayer::play(DrumPattern::audio_type data_) {
  if (data_->empty()) {
    return;
  }
  data = data_;
  current_frame = 0;
  std::cout << "jack play" << std::endl;
}
