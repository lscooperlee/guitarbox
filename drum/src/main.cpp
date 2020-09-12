#include "AudioPlayer.h"
#include "CtrlState.h"
#include "DrumkitPlayer.h"
#include "Rhythm.h"

#include <emi/emi.h>
#include <iostream>
#include <memory>
#include <unistd.h>

Rhythm r = {};
AudioPlayer p = {};

// CtrlState *c = new DrumCtrlState(DrumkitPlayer(r, p));
std::unique_ptr<CtrlState> c =
    std::make_unique<DrumCtrlState>(DrumkitPlayer(r, p));

constexpr eu32 EMI_MSG_KEY = 101;

int emi_msg_handler(emi_msg const *msg) {
  std::cout << msg->msg << ", " << msg->cmd << std::endl;
  //  c.reset(c->handle(msg->cmd));
  //  c = std::unique_ptr<CtrlState>(c->handle(msg->cmd));
  auto next = c->handle(msg->cmd);
  if (c.get() != next) {
    c.reset(next);
  }

  return 0;
}

int main(int argc, char **argv) {

  if (emi_init()) {
    std::cout << "Failed to init emi" << std::endl;
    return -1;
  }

  if (emi_msg_register(EMI_MSG_KEY, emi_msg_handler)) {
    std::cout << "Failed to register emi msg" << std::endl;
    return -1;
  }

  r.start(false);

  return 0;
}
