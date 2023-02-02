#include <gb/gb.h>
#include <gb/cgb.h>
#include "include/utils.h"
#include "../res/include/gustav-sprites.h"

Metasprite Gustav;

const uint8_t firstSpriteAddress = 17;

const UWORD gustavSpritePalette[] = {
    GustavSpritesCGBPal1c0,
    GustavSpritesCGBPal1c1,
    GustavSpritesCGBPal1c2,
    GustavSpritesCGBPal1c3,

    GustavSpritesCGBPal2c0,
    GustavSpritesCGBPal2c1,
    GustavSpritesCGBPal2c2,
    GustavSpritesCGBPal2c3,

    GustavSpritesCGBPal3c0,
    GustavSpritesCGBPal3c1,
    GustavSpritesCGBPal3c2,
    GustavSpritesCGBPal3c3,

    GustavSpritesCGBPal4c0,
    GustavSpritesCGBPal4c1,
    GustavSpritesCGBPal4c2,
    GustavSpritesCGBPal4c3
};

void setup_enemy() {
    Gustav.position[0] = 70;
    Gustav.position[1] = 70;

    set_sprite_palette(2, 4, &gustavSpritePalette[0]);
    set_sprite_data(firstSpriteAddress, 11, GustavSprites);

    setup_enemy_sprites();
}

void setup_enemy_sprites() {
    set_sprite_tile(17, 17);
    set_sprite_prop(17, 2);
    move_sprite(17, Gustav.position[0], Gustav.position[1]);

    set_sprite_tile(18, 18);
    set_sprite_prop(18, 2);
    move_sprite(18, Gustav.position[0] + 8, Gustav.position[1]);
    
    set_sprite_tile(19, 19);
    set_sprite_prop(19, 3);
    move_sprite(19, Gustav.position[0] + 8, Gustav.position[1] + 8);
    
    set_sprite_tile(20, 20);
    set_sprite_prop(20, 4);
    move_sprite(20, Gustav.position[0] - 8, Gustav.position[1] + 16);
    
    set_sprite_tile(21, 21);
    set_sprite_prop(21, 5);
    move_sprite(21, Gustav.position[0], Gustav.position[1] + 16);

    set_sprite_tile(22, 22);
    set_sprite_prop(22, 2);
    move_sprite(22, Gustav.position[0] + 8, Gustav.position[1] + 16);

    set_sprite_tile(23, 20);
    set_sprite_prop(23,  S_FLIPX | 4);
    move_sprite(23, Gustav.position[0] + 21, Gustav.position[1] + 16);
    
    set_sprite_tile(24, 21);
    set_sprite_prop(24, S_FLIPX | 5);
    move_sprite(24, Gustav.position[0] + 13, Gustav.position[1] + 16);

    set_sprite_tile(25, 23);
    set_sprite_prop(25, 2);
    move_sprite(25, Gustav.position[0] - 8, Gustav.position[1] + 24);

    set_sprite_tile(26, 24);
    set_sprite_prop(26, 2);
    move_sprite(26, Gustav.position[0], Gustav.position[1] + 24);

    set_sprite_tile(27, 25);
    set_sprite_prop(27, 2);
    move_sprite(27, Gustav.position[0] + 8, Gustav.position[1] + 24);

    set_sprite_tile(28, 23);
    set_sprite_prop(28, S_FLIPX | 2);
    move_sprite(28, Gustav.position[0] + 21, Gustav.position[1] + 24);

    set_sprite_tile(29, 24);
    set_sprite_prop(29, S_FLIPX | 2);
    move_sprite(29, Gustav.position[0] + 13, Gustav.position[1] + 24);
}

uint8_t gustavSpriteIndex;
uint8_t gustavSpeedCounter = 0;

uint8_t gustavPropellerAnimationFrames[2] = {26, 27};

void move_enemy() {
    set_sprite_tile(26, gustavPropellerAnimationFrames[0]);
    set_sprite_tile(27, gustavPropellerAnimationFrames[1]);

    for(gustavSpriteIndex = 17; gustavSpriteIndex != 30; gustavSpriteIndex++)
        scroll_sprite(gustavSpriteIndex, 0, 1);

    gustavSpeedCounter++;

    if(gustavSpeedCounter == 3) {
        gustavSpeedCounter = 0;

        if(gustavPropellerAnimationFrames[0] == 26) {
            gustavPropellerAnimationFrames[0] = 24;
            gustavPropellerAnimationFrames[1] = 25;
        } else {
            gustavPropellerAnimationFrames[0] = 26;
            gustavPropellerAnimationFrames[1] = 27;
        }
    }
}