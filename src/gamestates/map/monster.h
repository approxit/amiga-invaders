#ifndef GUARD_INVADERS_GAMESTATES_MAP_MONSTER_H
#define GUARD_INVADERS_GAMESTATES_MAP_MONSTER_H

#include <ace/types.h>

#include "game.h"

#define MONSTER_TYPE_GRAY 0
#define MONSTER_TYPE_GREEN 1
#define MONSTER_TYPE_RED 2
#define MONSTER_TYPE_COUNT 3

#define MONSTER_ATLAS_SIZE 4
#define MONSTER_COUNT_MAX 70

#define MONSTER_WIDTH 16
#define MONSTER_HEIGHT 16

#define MONSTER_UPDATE_DELAY 100
#define MONSTER_STEP_X 5
#define MONSTER_STEP_Y 5

typedef struct _tMonster {
    UBYTE ubType;
    tUwCoordYX sCoord;
    UBYTE ubFixupY;
} tMonster;

void monsterCreateBitMapAtlas();
void monsterDestroyBitMapAtlas();
void monsterDraw();
void monsterDrawIndex(UBYTE);
void monsterUndraw();
void monsterUndrawIndex(UBYTE);
void monsterMove();
void monsterMoveLeftRight();
void monsterMoveDown();
void monsterSetNextAlive();
void monsterSetPrevAlive();
UBYTE monsterCheckCollision(UWORD uwX, UWORD uwY);
void monsterKill(UBYTE ubMonsterIndex);
void monsterGenerate(UBYTE ubMonsterType, UBYTE ubMonsterCount, UWORD uwCoordX, UWORD uwCoordY, UWORD uwDistanceX, UWORD uwShiftY);

#endif