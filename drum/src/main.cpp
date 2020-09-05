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
                         {{Tom1, Bell}, {}, {}, {}},
                         {{SideStick}, {}, {}, {}},
                         {{HatClosed}, {}, {}, {}}};

  DrumkitPlayer player{r, p};
  player.play(pattern);

  r.set_bpm(60);
  r.start();

  while (1)
    ;

  return 0;
}
