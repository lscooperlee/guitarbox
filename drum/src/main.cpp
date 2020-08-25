#include "DrumPattern.h"

#include <memory>

int main(int argc, char **argv) {
  using namespace res_types;

  DrumPattern r = {{{Snare, Bell}, {}, {}, {}},
                   {{Tom1}, {}, {}, {}},
                   {{SideStick}, {}, {}, {}},
                   {{HatClosed}, {}, {}, {}}};

  return 0;
}
