#include <gb/gb.h>
#include <gb/cgb.h>
#include "../res/include/player-idle.h"
#include "include/player-animation.h"
#include "include/utils.h"

Metasprite Player;

uint8_t i;
uint8_t idleAnimationCounter = 0;
uint8_t animationFrame = 2;

UBYTE padUp = 1;
UBYTE shouldStop = 0;
BYTE direction = 0;

uint8_t maxSpeedCounter = 0;

uint8_t idleAnimationYCounter = 0;
uint8_t j = 0;
uint8_t acceleration = 0;

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
    Player.position[0] = 63;
    Player.position[1] = 78;
    Player.animation = 0x00;

    set_sprite_palette(0, 2, &playerSpritePalette[0]);
    set_sprite_data(0, 7, PlayerIdle);
}

void handle_player_animation() {
    if(Player.animation == 0x10)
        play_idle_animation();
    else if(Player.animation == 0x00)
        set_idle_sprites();
}

void play_idle_animation() {
    set_sprite_tile(1, animationFrame);
    set_sprite_tile(2, animationFrame);

    idleAnimationCounter++;
    idleAnimationYCounter++;

    if(idleAnimationCounter == 5) {
        idleAnimationCounter = 0;

        if(animationFrame == 2) {
            animationFrame = 3;
        } else {
            animationFrame = 2;
        }
    }

    if(acceleration == 0) {
        if(idleAnimationYCounter == 0) {
            for(j = 0; j != 11; j++)
                scroll_sprite(j, 0, -1);
        } else if(idleAnimationYCounter == 20) {
            for(j = 0; j != 11; j++)
                scroll_sprite(j, 0, -1);
        } else if(idleAnimationYCounter == 70) {
            for(j = 0; j != 11; j++)
                scroll_sprite(j, 0, 1);
        } else if(idleAnimationYCounter == 100) {
            for(j = 0; j != 11; j++)
                scroll_sprite(j, 0, 1);
        } else if(idleAnimationYCounter == 130) {
            for(j = 0; j != 11; j++)
                scroll_sprite(j, 0, -1);

            idleAnimationYCounter = 0;
        } 
    }
}

void accelerate() {
    if(acceleration == 2)
        return;

    if(maxSpeedCounter == 6) {
        acceleration += 1;
        maxSpeedCounter = 0;
    }
    
    maxSpeedCounter++;
}

void handle_player_controller() {
    if(joypad() & J_LEFT) {
        if(direction != -1) {
            if(acceleration != 0)
                    acceleration--;
            else
                direction = -1;
        } else {
            padUp = 0;
            shouldStop = 1;
            accelerate();

            for(i = 0; i != 11; i++)
                scroll_sprite(i, acceleration * direction, 0);
        }
    } else
        padUp = 1;
    
    if(joypad() & J_RIGHT) {
        if(direction != 1) {
            if(acceleration != 0)
                acceleration--;
            else
                direction = 1;
        } else {
            padUp = 0;
            shouldStop = 1;
            accelerate();

            for(i = 0; i != 11; i++)
                scroll_sprite(i, acceleration * direction, 0);
        }
    } else
        padUp = 1;
    
    if(!joypad() && padUp) {
        if(shouldStop) {
            maxSpeedCounter = 0;
            shouldStop = 0;
        }

        if(acceleration != 0) {
            for(i = 0; i != 11; i++)
                scroll_sprite(i, acceleration * direction, 0);
            if(maxSpeedCounter == 10) {
                acceleration--;
                maxSpeedCounter = 0;
            }

            maxSpeedCounter++;
        }
    }

    handle_player_animation();
}