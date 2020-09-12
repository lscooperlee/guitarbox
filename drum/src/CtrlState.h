#ifndef CTRLSTATE_H
#define CTRLSTATE_H

#include <iostream>

class CtrlState {
public:
  virtual CtrlState *handle(unsigned int /*key*/) = 0;
};

#include "DrumkitPlayer.h"

class DrumCtrlState : public CtrlState {
public:
  DrumCtrlState(DrumkitPlayer player_);
  CtrlState *handle(unsigned int /*key*/) override;

private:
  DrumkitPlayer player;
  int drum_bpm = 60;
};

#endif /* CTRLSTATE_H */
