
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

#include <emi/emi.h>

bool is_volume_mode = false;

int volume_handler(struct emi_msg const *msg) {
  auto key = msg->cmd;
  switch (key) {
  case 0xd:
    is_volume_mode = true;
    break;
  case 0xe:
    if(is_volume_mode){
        system("amixer sset Master 5%-");
    }
    break;
  case 0xf:
    if(is_volume_mode){
        system("amixer sset Master 5%+");
    }
    break;
  default:
    is_volume_mode = false;
    break;
  }
  return 0;
};

constexpr eu32 EMI_MSG_KEY = 101;

int main(void) {

  emi_init();

  emi_msg_register(EMI_MSG_KEY, volume_handler);

  while (1) {
    pause();
  }
}
