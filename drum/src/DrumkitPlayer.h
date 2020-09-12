#ifndef DRUMKITPLAYER_H
#define DRUMKITPLAYER_H

#include "DrumPattern.h"
#include "Rhythm.h"

class AudioPlayer;

class DrumkitPlayer : public Rhythm::RhythmType {
public:
  DrumkitPlayer(Rhythm &rhythm_, AudioPlayer &player);
  void play(const DrumPattern &);
  void stop();
  void set_bpm(int bpm);

private:
  Rhythm &rhythm;
  AudioPlayer &player;
  DrumPattern pattern = {};

  void callback(void) override;

  unsigned int current_pattern = 0;
};

#endif /* DRUMKITPLAYER_H */
