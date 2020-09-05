#ifndef DRUMKITPLAYER_H
#define DRUMKITPLAYER_H

#include "DrumPattern.h"

class Rhythm;
class AudioPlayer;

class DrumkitPlayer {
public:
  DrumkitPlayer(Rhythm &rhythm_, AudioPlayer &player);
  void play(const DrumPattern &);

private:
  Rhythm &rhythm;
  AudioPlayer &player;
  DrumPattern pattern = {};

  void callback(void);

  unsigned int current_pattern = 0;
};

#endif /* DRUMKITPLAYER_H */
