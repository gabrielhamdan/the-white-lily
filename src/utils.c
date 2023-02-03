#include <gb/gb.h>
#include <gb/cgb.h>
#include "include/utils.h"

extern const UWORD bkgColor[4];

#define DARK_RED 2131

const UWORD collisionBkg[] = {
    DARK_RED,
    DARK_RED,
    DARK_RED,
    DARK_RED
};

UBYTE check_collision(Metasprite * enemyCollider, Metasprite * playerCollider) {
    if((playerCollider->position[0] < enemyCollider->position[0] + enemyCollider->size[0] &&
        playerCollider->position[0] + playerCollider->size[0] > enemyCollider->position[0] &&
        enemyCollider->position[1] < playerCollider->position[1] + playerCollider->size[1] &&
        enemyCollider->position[1] + enemyCollider->size[1] > playerCollider->position[1]
       )
    ) {
        set_bkg_palette(0, 1, &collisionBkg[0]);
    } else {
        set_bkg_palette(0, 1, &bkgColor[0]);
    }
    
    return 0;
}