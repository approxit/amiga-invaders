#ifndef GUARD_INVADERS_GAMESTATES_SHIP_H
#define GUARD_INVADERS_GAMESTATES_SHIP_H

#include <ace/types.h>

#include "game.h"

#define SHIP_ATLAS_MIDDLE 2
#define SHIP_ATLAS_SIZE 5

#define SHIP_WIDTH 16
#define SHIP_HEIGHT 16
#define SHIP_SPEED_MAX 3
#define SHIP_SPEED_DELAY 8
#define SHIP_TILT_DELAY 6

extern tUwCoordYX g_sShipCoord;
extern tUwCoordYX g_sShipLastCoord;

void shipCreateBitMapAtlas();
void shipDestroyBitMapAtlas();
void shipDraw();
void shipUndraw();
void shipAccelerateLeft();
void shipAccelerateRight();
void shipDecelerate();
void shipMove();
void shipTiltLeft();
void shipTiltRight();
void shipTiltCenter();
UBYTE shipIsJustTilted();
UBYTE shipIsJustMoved();

#endif