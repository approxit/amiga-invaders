#ifndef GUARD_INVADERS_GAMESTATES_MAP_ENGINE_H
#define GUARD_INVADERS_GAMESTATES_MAP_ENGINE_H

#include <ace/types.h>

#include "game.h"

#define ENGINE_ATLAS_SIZE 5
#define ENGINE_DELAY 4

#define ENGINE_WIDTH 16
#define ENGINE_HEIGHT 16
#define ENGINE_SHIFT_Y 3

void engineCreateBitMapAtlas();
void engineDestroyBitMapAtlas();
void engineDraw();
void engineUndraw();
void engineAccelerate();
void engineDecelerate();
UBYTE engineIsPowerJustChanged();

#endif