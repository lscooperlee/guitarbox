#include "DrumkitPlayer.h"
#include "AudioPlayer.h"
#include "DrumPattern.h"
#include "Rhythm.h"

#include <chrono>

DrumkitPlayer::DrumkitPlayer(Rhythm &rhythm_, AudioPlayer &player_)
    : rhythm(rhythm_), player(player_){};

void DrumkitPlayer::play(const DrumPattern &pattern_) {
  pattern = pattern_;

  auto call = [this]() { return callback(); };
  auto hit_per_beat = std::get<1>(pattern.size());
  rhythm.update(call, hit_per_beat);
}

void DrumkitPlayer::set_bpm(int bpm) { rhythm.set_bpm(bpm); }

#include <iostream>

void DrumkitPlayer::callback(void) {
  std::cout << "Drumkit play: " << current_pattern << std::endl;
  auto [beat, hit] = pattern.size();
  player.play(pattern.data()[current_pattern]);
  current_pattern = current_pattern >= beat * hit - 1 ? 0 : current_pattern + 1;
}
