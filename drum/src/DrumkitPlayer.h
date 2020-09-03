#ifndef DRUMKITPLAYER_H
#define DRUMKITPLAYER_H

#include "Rhythm.h"

class DrumPattern;

class DrumkitPlayer {
public:
  DrumkitPlayer(Rhythm &rhythm_);
  void play(const DrumPattern &);

private:
  Rhythm &rhythm;
};

#endif /* DRUMKITPLAYER_H */
