#include <gb/gb.h>
#include <gb/cgb.h>
#include "../res/include/player-idle.h"
#include "include/player-animation.h"
#include "include/utils.h"

Metasprite Player;

uint8_t i;

UBYTE padUp = 1;
uint8_t currentSpeed = 0;
uint8_t acceleration = 1;
uint8_t maxVelocityCounter = 0;
uint8_t minVelocityCounter = 0;
int8_t direction = 0;

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

UBYTE isWithinRange() {
    return Player.position[0] + currentSpeed * direction < 12 || Player.position[0] + currentSpeed * direction > 134;
}

void move_player(int8_t direction, UBYTE shouldStop) {
    if(shouldStop && currentSpeed > 0) {
        minVelocityCounter++;

        if(minVelocityCounter == 10) {
            currentSpeed -= acceleration;
            minVelocityCounter = 0;
        }

    } else if (!shouldStop) {
        maxVelocityCounter++;

        if(maxVelocityCounter == 4) {
            currentSpeed += acceleration;
            maxVelocityCounter = 0;
        }
    }

    if(currentSpeed >= 2)
        currentSpeed = 2;

    if(isWithinRange())
        return;

    Player.position[0] += currentSpeed * direction;
    
    for(i = 0; i != 11; i++)
        scroll_sprite(i, currentSpeed * direction, 0);
}

void handle_player_controller() {
    if(joypad() & J_LEFT) {
        if(direction != -1 && currentSpeed != 0)
            move_player(direction, 1);
        else {
            direction = -1;
            move_player(direction, 0);
        }
    } else if(joypad() & J_RIGHT) {
        if(direction != 1 && currentSpeed != 0)
            move_player(direction, 1);
        else {
            direction = 1;
            move_player(direction, 0);
        }
    } else move_player(direction, 1);

    handle_player_animation();
}