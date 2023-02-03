#include <gb/gb.h>
#include <gb/cgb.h>
#include "../res/include/player-sprites.h"
#include "include/player-animation.h"
#include "include/utils.h"
#include "../res/include/gustav-sprites.h"


extern UBYTE shouldFlipSprite;

Metasprite Player;

uint8_t i;

uint8_t currentSpeed = 0;
uint8_t acceleration = 1;
uint8_t maxVelocityCounter = 0;
uint8_t minVelocityCounter = 0;
int8_t direction = 0;

const UWORD playerSpritePalette[] = {
    PlayerSpritesCGBPal1c0,
    PlayerSpritesCGBPal1c1,
    PlayerSpritesCGBPal1c2,
    PlayerSpritesCGBPal1c3,

    PlayerSpritesCGBPal2c0,
    PlayerSpritesCGBPal2c1,
    PlayerSpritesCGBPal2c2,
    PlayerSpritesCGBPal2c3
};

void setup_player() {
    Player.position[0] = 30;
    Player.position[1] = 115;
    Player.size[0] = 30;
    Player.size[1] = 17;
    Player.animation = 0x00;

    set_sprite_palette(0, 2, &playerSpritePalette[0]);
    set_sprite_data(0, 17, PlayerSprites);
}

UBYTE isNotWithinRange() {
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

    if(isNotWithinRange())
        return;

    Player.position[0] += currentSpeed * direction;
    
    for(i = 0; i != 11; i++)
        scroll_sprite(i, currentSpeed * direction, 0);
}

void handle_player_controller() {
    if(joypad() & J_LEFT) {
        if(Player.animation != 0x11)
            Player.animation = 0x01;

        if(direction != -1 && currentSpeed != 0)
            move_player(direction, 1);
        else {
            direction = -1;
            move_player(direction, 0);
        }
    } else if(joypad() & J_RIGHT) {
        if(Player.animation != 0x12)
            Player.animation = 0x02;

        if(direction != 1 && currentSpeed != 0)
            move_player(direction, 1);
        else {
            direction = 1;
            move_player(direction, 0);
        }
    } else {
        if(Player.animation != 0x10 && currentSpeed == 0)
            Player.animation = 0x00;

        move_player(direction, 1);
    }

    handle_player_animation();
}