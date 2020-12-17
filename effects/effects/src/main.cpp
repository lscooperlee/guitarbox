
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

#include <emi/emi.h>

#include "AudioPlayer.h"
#include "plugin.h"

int handler(struct emi_msg const *msg) { return 0; };

constexpr eu32 EMI_MSG_KEY = 101;

int main(void) {

  // Plugin p("http://guitarix.sourceforge.net/plugins/gx_amp#GUITARIX");
  Plugin p("http://lv2plug.in/plugins/eg-amp");
  p.run(512);

  AudioPlayer player(p);

  player.play();

  emi_init();

  emi_msg_register(EMI_MSG_KEY, handler);

  while (1) {
    pause();
  }
}
