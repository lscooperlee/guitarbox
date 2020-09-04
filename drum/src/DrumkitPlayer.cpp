#include "DrumkitPlayer.h"
#include "AudioPlayer.h"
#include "DrumPattern.h"
#include "Rhythm.h"

#include <chrono>

DrumkitPlayer::DrumkitPlayer(Rhythm &rhythm_, AudioPlayer &player_)
    : rhythm(rhythm_), player(player_){};

void DrumkitPlayer::play(const DrumPattern &pattern_) { pattern = pattern_; }
