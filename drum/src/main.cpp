#include "AudioPlayer.h"
#include "DrumPattern.h"
#include "DrumkitPlayer.h"
#include "Rhythm.h"

#include <memory>

Rhythm r = {};
AudioPlayer p = {};

int main(int argc, char **argv) {
  using namespace res_types;

  DrumPattern pattern = {{{Snare, Bell}, {}, {}, {}},
                         {{Tom1}, {}, {}, {}},
                         {{SideStick}, {}, {}, {}},
                         {{HatClosed}, {}, {}, {}}};

  DrumkitPlayer player{r, p};
  player.play(pattern);

  return 0;
}
