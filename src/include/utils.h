#ifndef UTILS_H
#define UTILS_H

#include <gb/gb.h>

typedef struct Metasprite
{
    uint16_t position[2];
    uint8_t size[2];
    uint8_t sizeOffset[2];
    UBYTE animation;
} Metasprite;

UBYTE check_collision(Metasprite * enemyCollider, Metasprite * playerCollider);

#endif