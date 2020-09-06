#include "AudioPlayer.h"
#include "DrumPattern.h"
#include "DrumkitPlayer.h"
#include "Rhythm.h"

#include <memory>

Rhythm r = {};
AudioPlayer p = {};

int main(int argc, char **argv) {
  using namespace res_types;

  // DrumPattern test = {{{Kick}}, {{Snare}}, {{Ride}}, {{HatOpen}}};
  DrumPattern test = {{{Kick}}, {{Kick}}, {{Kick}}, {{Kick}}};

  DrumPattern Billie_Jean = {{{Kick, HatClosed}, {}, {}, {}},
                             {{HatClosed}, {}, {}, {}},
                             {{Snare, HatClosed}, {}, {}, {}},
                             {{HatClosed}, {}, {}, {}}};

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

  DrumkitPlayer player{r, p};
  player.play(test);

  r.set_bpm(60);
  r.start();

  while (1)
    ;

  return 0;
}
