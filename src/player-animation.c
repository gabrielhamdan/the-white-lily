#include <gb/gb.h>
#include "include/utils.h"

extern Metasprite Player;
extern uint8_t currentSpeed;
extern uint8_t direction;

uint8_t propellerAnimationCnt = 0;
uint8_t propellerAnimationFrame = 2;
uint8_t hoverAnimationCnt = 0;
uint8_t spriteIndex = 0;

uint8_t turningPropellerAnimationFrames[2] = {8, 9};

UBYTE shouldFlipSprite = 1;

void play_hover_animation(uint8_t spritesLength) {
    hoverAnimationCnt++;

    if(hoverAnimationCnt == 0) {
        for(spriteIndex = 0; spriteIndex != spritesLength; spriteIndex++)
            scroll_sprite(spriteIndex, 0, -1);
    } else if(hoverAnimationCnt == 20) {
        for(spriteIndex = 0; spriteIndex != spritesLength; spriteIndex++)
            scroll_sprite(spriteIndex, 0, -1);
    } else if(hoverAnimationCnt == 70) {
        for(spriteIndex = 0; spriteIndex != spritesLength; spriteIndex++)
            scroll_sprite(spriteIndex, 0, 1);
    } else if(hoverAnimationCnt == 100) {
        for(spriteIndex = 0; spriteIndex != spritesLength; spriteIndex++)
            scroll_sprite(spriteIndex, 0, 1);
    } else if(hoverAnimationCnt == 130) {
        for(spriteIndex = 0; spriteIndex != spritesLength; spriteIndex++)
            scroll_sprite(spriteIndex, 0, -1);

        hoverAnimationCnt = 0;
    }
}

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

    if(propellerAnimationCnt == 5) {
        propellerAnimationCnt = 0;

        if(propellerAnimationFrame == 2) {
            propellerAnimationFrame = 3;
        } else {
            propellerAnimationFrame = 2;
        }
    }

    play_hover_animation(11);
}

void set_turning_sprites() {
    shouldFlipSprite = direction == 1 ? 0 : S_FLIPX;

    set_sprite_tile(8, 0);
    set_sprite_tile(9, 0);

    set_sprite_tile(shouldFlipSprite ? 2 : 0, 7);
    set_sprite_prop(shouldFlipSprite ? 2 : 0, shouldFlipSprite);
    move_sprite(shouldFlipSprite ? 2 : 0, shouldFlipSprite ? Player.position[0] + 16 : Player.position[0], Player.position[1]);

    set_sprite_tile(1, 8);
    set_sprite_prop(1, shouldFlipSprite);
    move_sprite(1, Player.position[0] + 8, Player.position[1]);
    
    set_sprite_tile(shouldFlipSprite ? 0 : 2, 9);
    set_sprite_prop(shouldFlipSprite ? 0 : 2, shouldFlipSprite);
    move_sprite(shouldFlipSprite ? 0 : 2, shouldFlipSprite ? Player.position[0] : Player.position[0] + 16, Player.position[1]);
    
    set_sprite_tile(shouldFlipSprite ? 5 : 3, 10);
    set_sprite_prop(shouldFlipSprite ? 5 : 3, shouldFlipSprite);
    move_sprite(shouldFlipSprite ? 5 : 3, shouldFlipSprite ? Player.position[0] + 16 : Player.position[0], Player.position[1] + 8);
    
    set_sprite_tile(4, 11);
    set_sprite_prop(4, shouldFlipSprite | 0x01);
    move_sprite(4, Player.position[0] + 8, Player.position[1] + 8);
    
    set_sprite_tile(shouldFlipSprite ? 3 : 5, 12);
    set_sprite_prop(shouldFlipSprite ? 3 : 5, shouldFlipSprite | 0x01);
    move_sprite(shouldFlipSprite ? 3 : 5, shouldFlipSprite ? Player.position[0] : Player.position[0] + 16, Player.position[1] + 8);
    
    set_sprite_tile(6, 13);
    set_sprite_prop(6, shouldFlipSprite | 0x01);
    move_sprite(6, Player.position[0] + 8, Player.position[1] + 16);
   
    set_sprite_tile(7, 14);
    set_sprite_prop(7, shouldFlipSprite | 0x01);
    move_sprite(7, shouldFlipSprite ? Player.position[0] : Player.position[0] + 16, Player.position[1] + 16);

    if(shouldFlipSprite)
        Player.animation = 0x11;
    else
        Player.animation = 0x12;
}

void play_turning_animation() {
    if(shouldFlipSprite){
        set_sprite_tile(1, turningPropellerAnimationFrames[0]);
        set_sprite_tile(0, turningPropellerAnimationFrames[1]);
    }
    else {
        set_sprite_tile(1, turningPropellerAnimationFrames[0]);
        set_sprite_tile(2, turningPropellerAnimationFrames[1]);
    }

    propellerAnimationCnt++;

    if(propellerAnimationCnt == 5) {
        propellerAnimationCnt = 0;

        if(turningPropellerAnimationFrames[0] == 8) {
            turningPropellerAnimationFrames[0] = 15;
            turningPropellerAnimationFrames[1] = 16;
        } else {
            turningPropellerAnimationFrames[0] = 8;
            turningPropellerAnimationFrames[1] = 9;
        }
    }

    play_hover_animation(9);
}

void handle_player_animation() {
    if(Player.animation == 0x10)
        play_idle_animation();
    else if(Player.animation == 0x00)
        set_idle_sprites();
    
    if(Player.animation == 0x11 || Player.animation == 0x12)
        play_turning_animation();
    else if(Player.animation == 0x01 || Player.animation == 0x02)
        set_turning_sprites();
}