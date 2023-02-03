#include <gb/gb.h>
#include <gb/cgb.h>
#include "include/player.h"
#include "include/gustav-test.h"
#include "include/utils.h"

#define BkgColor 19507

const UWORD bkgColor[] = {
    BkgColor,
    BkgColor,
    BkgColor,
    BkgColor
};

void main() {
   setup_player();
   setup_enemy();

   set_bkg_palette(0, 1, &bkgColor[0]);

   SHOW_SPRITES;
   SHOW_BKG;

   while(1) {
         handle_player_controller();
         move_enemy();

         wait_vbl_done();
     }
}