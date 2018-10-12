#include "game.h"

#include <stdio.h>

#include <ace/types.h>
#include <ace/generic/main.h>
#include <ace/managers/game.h>
#include <ace/managers/key.h>
#include <ace/managers/blit.h>
#include <ace/managers/rand.h>
#include <ace/utils/extview.h>
#include <ace/utils/palette.h>

#include "gamestates/intro/intro.h"
#include "gamestates/map/map.h"

const UWORD WINDOW_SCREEN_WIDTH = SCREEN_PAL_WIDTH;
const UWORD WINDOW_SCREEN_HEIGHT = SCREEN_PAL_HEIGHT;
const UWORD WINDOW_SCREEN_BPP = 4;

tView *g_pView;
tVPort *g_pVPort;
tSimpleBufferManager *g_pBufferManager;
tFont *g_pFont;
tBitMap *g_pBackgroundBitMap;

void genericCreate() {
	randInit(2184);

	g_pView = (tView *) viewCreate(0,
		TAG_VIEW_GLOBAL_CLUT, 1,
		TAG_DONE
	);

	copBlockDisableSprites(g_pView->pCopList, 0xFF);

	g_pVPort = vPortCreate(0,
		TAG_VPORT_VIEW, g_pView,
		TAG_DONE
	);

	g_pBufferManager = simpleBufferCreate(0,
		TAG_SIMPLEBUFFER_VPORT, g_pVPort,
		TAG_DONE
	);

	paletteLoad("/data/colors.plt", g_pVPort->pPalette, 1 << WINDOW_SCREEN_BPP);

	g_pFont = fontCreate("/data/silkscreen.fnt");
	g_pBackgroundBitMap = bitmapCreateFromFile("/data/background.bm");

	viewLoad(g_pView);

	gamePushState(gsIntroCreate, gsIntroLoop, gsIntroDestroy);
}

void genericProcess() {
	keyProcess();
	gameProcess();

	WaitTOF();
}

void genericDestroy() {
	fontDestroy(g_pFont);
	bitmapDestroy(g_pBackgroundBitMap);
	viewDestroy(g_pView);
}