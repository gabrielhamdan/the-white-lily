#include <gb/gb.h>
#include "include/player.h"
#include "include/gustav-test.h"

void main() {
   setup_player();
   setup_enemy();

   SHOW_SPRITES;
   SHOW_BKG;

   while(1) {
         handle_player_controller();
         move_enemy();

         wait_vbl_done();
     }
}