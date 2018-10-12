#ifndef GUARD_INVADERS_GAMESTATES_MAP_MONSTER_PROJECTILE_H
#define GUARD_INVADERS_GAMESTATES_MAP_MONSTER_PROJECTILE_H

#include <ace/types.h>

#define MONSTER_PROJECTILE_SPEED 3

#define MONSTER_PROJECTILE_WIDTH 2
#define MONSTER_PROJECTILE_HEIGHT 6

void monsterProjectileDraw();
void monsterProjectileUndraw();
void monsterProjectileFire(UBYTE ubMonsterIndex);
void monsterProjectileMove();

#endif