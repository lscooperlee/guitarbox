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

  rhythm.update(call, 1);
}

void DrumkitPlayer::callback(void) {
  player.play(pattern.data()[current_pattern]);
  current_pattern = current_pattern == pattern.size() ? 0 : current_pattern + 1;
}
