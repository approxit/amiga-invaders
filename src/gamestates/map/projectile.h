#ifndef GUARD_INVADERS_GAMESTATES_MAP_PROJECTILE_H
#define GUARD_INVADERS_GAMESTATES_MAP_PROJECTILE_H

#include <ace/types.h>

#include "game.h"
#include "gamestates/map/ship.h"

#define PROJECTILE_ATLAS_SIZE 1
#define PROJECTILE_SPEED 5
#define PROJECTILE_TIMER 150

#define PROJECTILE_WIDTH 2
#define PROJECTILE_HEIGHT 62
#define PROJECTILE_SHIFT_Y 1
#define PROJECTILE_SHIFT_X ((SHIP_WIDTH / 2) - (PROJECTILE_WIDTH / 2))

void projectileCreateBitMapAtlas();
void projectileDestroyBitMapAtlas();
void projectileDraw();
void projectileUndraw();
void projectileFire();
void projectileMove();
void projectileAdjustHeight();
UBYTE projectileIsJustMoved();

#endif