#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdio.h>
#include "../res/include/player-idle.h"

uint8_t y_row = 0;
uint8_t sprite_x = 63;
const uint8_t idle_pattern[12] = {1, 2, 2, 1, 4, 5, 5, 4, 0, 6, 6, 0};
const uint8_t idle_palette_pattern[12] = {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0};
const UBYTE idle_mirrored_pattern[12] = {0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1};

uint8_t i;
uint8_t idleAnimationCounter = 0;
uint8_t animationFrame = 2;

const UWORD bgkPalette[] = {
    PlayerIdleCGBPal1c0
};

const UWORD playerSpritePalette[] = {
    PlayerIdleCGBPal1c0,
    PlayerIdleCGBPal1c1,
    PlayerIdleCGBPal1c2,
    PlayerIdleCGBPal1c3,

    PlayerIdleCGBPal2c0,
    PlayerIdleCGBPal2c1,
    PlayerIdleCGBPal2c2,
    PlayerIdleCGBPal2c3
};

void setup_player() {
    set_sprite_palette(0, 2, &playerSpritePalette[0]);
    set_sprite_data(0, 7, PlayerIdle);

    for(i = 0; i != 11; i++) {
        set_sprite_tile(i, idle_pattern[i]);
        set_sprite_prop(i, idle_palette_pattern[i]);

        if(idle_mirrored_pattern[i])
            if(idle_pattern[i] == 5)
                set_sprite_prop(i, 0b00100001);
            else
                set_sprite_prop(i, S_FLIPX);

        if (i == 4 || i == 8) {
            sprite_x = 63;
            y_row++;
        }

        if(i == 2 || i == 6 || i == 10)
            sprite_x += 7;
        else
            sprite_x += 8;

        if (y_row == 0)
        {
            move_sprite(i, sprite_x, 78);
        } else if (y_row == 1) {
            move_sprite(i, sprite_x, 86);
        } else {
            move_sprite(i, sprite_x, 94);
        }
    }
}

void play_idle_animation() {
    set_sprite_tile(1, animationFrame);
    set_sprite_tile(2, animationFrame);

    idleAnimationCounter++;

    if(idleAnimationCounter == 3) {
        idleAnimationCounter = 0;

        if(animationFrame == 2) {
            animationFrame = 3;
        } else {
            animationFrame = 2;
        }
    }
}

void move_player() {
    if(joypad() & J_LEFT)
        for(i = 0; i != 11; i++)
            scroll_sprite(i, -1, 0);
    
    if(joypad() & J_RIGHT)
        for(i = 0; i != 11; i++)
            scroll_sprite(i, 1, 0);
}

void main() {
    setup_player();

    SHOW_SPRITES;
    SHOW_BKG;

     while(1) {
        play_idle_animation();
        move_player();

        wait_vbl_done();
     }
}
