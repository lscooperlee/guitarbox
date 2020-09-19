#include "DrumkitPlayer.h"
#include "AudioPlayer.h"
#include "DrumPattern.h"
#include "Rhythm.h"

#include <chrono>

#include <iostream>

DrumkitPlayer::DrumkitPlayer(Rhythm &rhythm_, AudioPlayer &player_)
    : rhythm(rhythm_), player(player_){};

DrumkitPlayer::~DrumkitPlayer() {
  std::cout << "leave" << std::endl;
  stop();
}

void DrumkitPlayer::play(const DrumPattern &pattern_) {
  pattern = pattern_;

  auto hit_per_beat = std::get<1>(pattern.size());
  rhythm.update(this, hit_per_beat);
  std::cout << "play " << hit_per_beat << std::endl;
}

void DrumkitPlayer::stop() { rhythm.remove(this); }

void DrumkitPlayer::set_bpm(int bpm) {
  std::cout << "player change bpm: " << bpm << std::endl;
  rhythm.set_bpm(bpm);
}

void DrumkitPlayer::callback(void) {
  std::cout << "Drumkit play: " << current_pattern << std::endl;
  auto [beat, hit] = pattern.size();
  player.play(pattern.data()[current_pattern]);
  current_pattern = current_pattern >= beat * hit - 1 ? 0 : current_pattern + 1;
}
