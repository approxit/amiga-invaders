#ifndef GUARD_INVADERS_GAMESTATES_INTRO_H
#define GUARD_INVADERS_GAMESTATES_INTRO_H

#include <ace/types.h>

void gsIntroCreate();
void gsIntroLoop();
void gsIntroDestroy();

void writerWrite();
void writerDrawBlock(UBYTE);

#endif