#include <gb/gb.h>
#include "include/player.h"

void main() {
    setup_player();

    SHOW_SPRITES;
    SHOW_BKG;

     while(1) {
        handle_player_controller();

        wait_vbl_done();
     }
}