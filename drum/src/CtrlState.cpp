#include "CtrlState.h"
#include "DrumPattern.h"

#include <iostream>

namespace {

using namespace res_types;

DrumPattern Billie_Jean = {{{Kick, HatClosed}, {}},
                           {{HatClosed}, {}},
                           {{Snare, HatClosed}, {}},
                           {{HatClosed}, {}}};

DrumPattern Cold_Sweat = {{{Kick, Ride}, {}, {}, {}},
                          {{Kick, Ride}, {}, {}, {}},
                          {{Snare, Ride}, {}, {}, {}},
                          {{Ride}, {}, {Snare}, {}}};

DrumPattern Walk_This_Way = {{{Kick, HatOpen}, {}, {HatClosed}, {}},
                             {{Snare, HatClosed}, {}, {HatClosed}, {Kick}},
                             {{Kick, HatClosed}, {}, {Kick, HatClosed}, {}},
                             {{Snare, HatClosed}, {}, {HatClosed}, {}}};

DrumPattern Impeach_the_president = {
    {{Kick, HatClosed}, {}, {HatClosed}, {}},
    {{Snare, HatClosed}, {}, {HatClosed}, {Kick, HatClosed}},
    {{Kick, HatClosed}, {}, {HatOpen}, {}},
    {{Snare, HatClosed}, {}, {Kick, HatClosed}, {}}};

} // namespace

DrumCtrlState::DrumCtrlState(DrumkitPlayer player_) : player(player_){};
CtrlState *DrumCtrlState::handle(unsigned int key) {
  switch (key) {
  case '0':
    player.stop();
    break;
  case '1':
    player.play(Billie_Jean);
    break;
  case 'a':
  case 'A':
    break;
  case '*':
    drum_bpm = drum_bpm <= 60 ? 60 : drum_bpm - 5;
    player.set_bpm(drum_bpm);
    break;
  case '#':
    drum_bpm = drum_bpm >= 120 ? 120 : drum_bpm + 5;
    player.set_bpm(drum_bpm);
    break;
  default:
    break;
  }

  return this;
}
