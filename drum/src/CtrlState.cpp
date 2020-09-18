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

enum class Keyset {
  key_0,
  key_1,
  key_2,
  key_3,
  key_4,
  key_5,
  key_6,
  key_7,
  key_8,
  key_9,

  key_A,
  key_B,
  key_C,
  key_D,

  key_E,
  key_F,

};

} // namespace

extern Rhythm r;
extern AudioPlayer p;

CtrlState *DummyCtrlState::handle(unsigned int key_) {
  auto key = static_cast<Keyset>(key_);
  switch (key) {
  case Keyset::key_A:
    return new DrumCtrlState(DrumkitPlayer(r, p));
    break;
  default:
    break;
  }

  return this;
}

DrumCtrlState::DrumCtrlState(DrumkitPlayer player_) : player(player_){};
CtrlState *DrumCtrlState::handle(unsigned int key_) {
  auto key = static_cast<Keyset>(key_);

  switch (key) {
  case Keyset::key_0:
    player.stop();
    break;
  case Keyset::key_1:
    player.play(Billie_Jean);
    break;
  case Keyset::key_2:
    player.play(Cold_Sweat);
    break;
  case Keyset::key_3:
    player.play(Walk_This_Way);
    break;
  case Keyset::key_4:
    player.play(Impeach_the_president);
    break;
  case Keyset::key_A:
    break;
  case Keyset::key_D:
    player.stop();
    return new DummyCtrlState();
    break;
  case Keyset::key_E:
    drum_bpm = drum_bpm <= 60 ? 60 : drum_bpm - 5;
    player.set_bpm(drum_bpm);
    break;
  case Keyset::key_F:
    drum_bpm = drum_bpm >= 120 ? 120 : drum_bpm + 5;
    player.set_bpm(drum_bpm);
    break;
  default:
    break;
  }

  return this;
}
