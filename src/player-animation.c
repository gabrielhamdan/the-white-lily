#include <gb/gb.h>
#include "include/utils.h"

extern Metasprite Player;
extern uint8_t acceleration;

uint8_t propellerAnimationCnt = 0;
uint8_t propellerAnimationFrame = 2;
uint8_t hoverAnimationCnt = 0;
uint8_t idleSpriteIndex = 0;

void set_idle_sprites() {
    set_sprite_tile(0, 1);
    set_sprite_prop(0, 0);
    move_sprite(0, Player.position[0], Player.position[1]);

    set_sprite_tile(1, 2);
    set_sprite_prop(1, 0);
    move_sprite(1, Player.position[0] + 8, Player.position[1]);
    
    set_sprite_tile(2, 2);
    set_sprite_prop(2, S_FLIPX);
    move_sprite(2, Player.position[0] + 15, Player.position[1]);
    
    set_sprite_tile(3, 1);
    set_sprite_prop(3, S_FLIPX);
    move_sprite(3, Player.position[0] + 23, Player.position[1]);
    
    set_sprite_tile(4, 4);
    set_sprite_prop(4, 0);
    move_sprite(4, Player.position[0], Player.position[1] + 8);
    
    set_sprite_tile(5, 5);
    set_sprite_prop(5, 1);
    move_sprite(5, Player.position[0] + 8, Player.position[1] + 8);
    
    set_sprite_tile(6, 5);
    set_sprite_prop(6, S_FLIPX | 0x01);
    move_sprite(6, Player.position[0] + 15, Player.position[1] + 8);
   
    set_sprite_tile(7, 4);
    set_sprite_prop(7, S_FLIPX);
    move_sprite(7, Player.position[0] + 23, Player.position[1] + 8);
   
    set_sprite_tile(8, 6);
    set_sprite_prop(8, 0);
    move_sprite(8, Player.position[0] + 8, Player.position[1] + 16);
   
    set_sprite_tile(9, 6);
    set_sprite_prop(9, S_FLIPX);
    move_sprite(9, Player.position[0] + 15, Player.position[1] + 16);

    Player.animation = 0x10;
}

void play_idle_animation() {
    set_sprite_tile(1, propellerAnimationFrame);
    set_sprite_tile(2, propellerAnimationFrame);

    propellerAnimationCnt++;
    hoverAnimationCnt++;

    if(propellerAnimationCnt == 5) {
        propellerAnimationCnt = 0;

        if(propellerAnimationFrame == 2) {
            propellerAnimationFrame = 3;
        } else {
            propellerAnimationFrame = 2;
        }
    }

    if(acceleration == 0) {
        if(hoverAnimationCnt == 0) {
            for(idleSpriteIndex = 0; idleSpriteIndex != 11; idleSpriteIndex++)
                scroll_sprite(idleSpriteIndex, 0, -1);
        } else if(hoverAnimationCnt == 20) {
            for(idleSpriteIndex = 0; idleSpriteIndex != 11; idleSpriteIndex++)
                scroll_sprite(idleSpriteIndex, 0, -1);
        } else if(hoverAnimationCnt == 70) {
            for(idleSpriteIndex = 0; idleSpriteIndex != 11; idleSpriteIndex++)
                scroll_sprite(idleSpriteIndex, 0, 1);
        } else if(hoverAnimationCnt == 100) {
            for(idleSpriteIndex = 0; idleSpriteIndex != 11; idleSpriteIndex++)
                scroll_sprite(idleSpriteIndex, 0, 1);
        } else if(hoverAnimationCnt == 130) {
            for(idleSpriteIndex = 0; idleSpriteIndex != 11; idleSpriteIndex++)
                scroll_sprite(idleSpriteIndex, 0, -1);

            hoverAnimationCnt = 0;
        } 
    }
}