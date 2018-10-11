#ifndef GUARD_INVADERS_GAMESTATES_MAP_H
#define GUARD_INVADERS_GAMESTATES_MAP_H

#include <ace/types.h>

void gsMapCreate();
void gsMapLoop();
void gsMapDestroy();

void undrawShipWithEngine();

void mapLoadLevel();

#endif