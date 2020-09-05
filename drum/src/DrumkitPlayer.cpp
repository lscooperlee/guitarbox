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

  rhythm.update(call, 4);
}

#include <iostream>

void DrumkitPlayer::callback(void) {
  std::cout << current_pattern << std::endl;
  player.play(pattern.data()[current_pattern]);
  current_pattern =
      current_pattern >= pattern.size() - 1 ? 0 : current_pattern + 1;
}
