#ifndef PLAYER_H
#define PLAYER_H

#include <gb/gb.h>

void setup_player();

void handle_player_controller();

/// @brief Plays a certain animation according to UBYTE playerAnimation.
/// Bits 0-3 determine which animation should be played.
/// Bit 4 flags whether the sprites for a given animation have been set.
/// @example 0x10 means the idle sprites have been already set and the idle animation should be playing
/// @note 0x00 idle
/// @note 0x01 turning
void handle_player_animation();

#endif