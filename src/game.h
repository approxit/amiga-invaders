#ifndef GUARD_AMIGA_INVADERS_GAME_H
#define GUARD_AMIGA_INVADERS_GAME_H

#include <ace/utils/extview.h>
#include <ace/managers/viewport/simplebuffer.h>
#include <ace/utils/font.h>
#include <ace/utils/bitmap.h>
#include <ace/generic/screen.h>

#define GAME_DEBUG

extern const UWORD WINDOW_SCREEN_WIDTH;
extern const UWORD WINDOW_SCREEN_HEIGHT;
extern const UWORD WINDOW_SCREEN_BPP;

extern tView *g_pView;
extern tVPort *g_pVPort;
extern tSimpleBufferManager *g_pBufferManager;
extern tFont *g_pFont;
extern tBitMap *g_pBackgroundBitMap;

#endif