#include "DrumPattern.h"
#include "DrumkitPlayer.h"
#include "Rhythm.h"

#include <memory>

Rhythm r = {};

int main(int argc, char **argv) {
  using namespace res_types;

  DrumPattern p = {{{Snare, Bell}, {}, {}, {}},
                   {{Tom1}, {}, {}, {}},
                   {{SideStick}, {}, {}, {}},
                   {{HatClosed}, {}, {}, {}}};

  DrumkitPlayer player{r};
  player.play(p);

  return 0;
}
