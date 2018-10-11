#include "gamestates/map/engine.h"

#include <ace/managers/blit.h>

#include "atlas.h"
#include "gamestates/map/ship.h"

tBitMap *pEngineBitMapAtlas[ENGINE_ATLAS_SIZE];
tBitMap *pEngineBitMapMaskAtlas[ENGINE_ATLAS_SIZE];

ULONG ulEngineTimer = 0;
UBYTE ubEnginePower = 0;
UBYTE ubEngineLastPower = 0;

void engineCreateBitMapAtlas() {
    createAtlasFileWithMask(pEngineBitMapAtlas, pEngineBitMapMaskAtlas, 0, "/data/engine_frames/engine_0.bm", "/data/engine_frames/engine_0.msk");
    createAtlasFileWithMask(pEngineBitMapAtlas, pEngineBitMapMaskAtlas, 1, "/data/engine_frames/engine_1.bm", "/data/engine_frames/engine_1.msk");
    createAtlasFileWithMask(pEngineBitMapAtlas, pEngineBitMapMaskAtlas, 2, "/data/engine_frames/engine_2.bm", "/data/engine_frames/engine_2.msk");
    createAtlasFileWithMask(pEngineBitMapAtlas, pEngineBitMapMaskAtlas, 3, "/data/engine_frames/engine_3.bm", "/data/engine_frames/engine_3.msk");
    createAtlasFileWithMask(pEngineBitMapAtlas, pEngineBitMapMaskAtlas, 4, "/data/engine_frames/engine_4.bm", "/data/engine_frames/engine_4.msk");
}

void engineDestroyBitMapAtlas() {
    destroyAtlasFilesWithMask(pEngineBitMapAtlas, pEngineBitMapMaskAtlas, ENGINE_ATLAS_SIZE);
}

void engineDraw() {
	blitCopyMask(
		pEngineBitMapAtlas[ubEnginePower], 0, 0,
		g_pBufferManager->pBuffer, g_sShipCoord.sUwCoord.uwX, g_sShipCoord.sUwCoord.uwY + ENGINE_SHIFT_Y,
		ENGINE_WIDTH, ENGINE_HEIGHT,
		(UWORD *) pEngineBitMapMaskAtlas[ubEnginePower]->Planes[0]
	);
}

void engineUndraw() {
    blitCopy(
        g_pBackgroundBitMap, g_sShipCoord.sUwCoord.uwX, g_sShipCoord.sUwCoord.uwY + ENGINE_SHIFT_Y,
        g_pBufferManager->pBuffer, g_sShipCoord.sUwCoord.uwX, g_sShipCoord.sUwCoord.uwY + ENGINE_SHIFT_Y,
        ENGINE_WIDTH, ENGINE_HEIGHT,
        MINTERM_COOKIE, 0xFF
    );
}

void engineAccelerate() {
    ubEngineLastPower = ubEnginePower;

    if (!ulEngineTimer) {
        ulEngineTimer = timerGet();
    }

    if (timerCheck(&ulEngineTimer, ENGINE_DELAY)) {
        if (ubEnginePower < ENGINE_ATLAS_SIZE - 1) {
            ubEnginePower += 1;
        }
        else {
            ubEnginePower = ENGINE_ATLAS_SIZE - 1;
        }
    }
}

void engineDecelerate() {
    ubEngineLastPower = ubEnginePower;

    if (ubEnginePower && !ulEngineTimer) {
        ulEngineTimer = timerGet();
    }

    if (timerCheck(&ulEngineTimer, ENGINE_DELAY)) {
        if (1 < ubEnginePower) {
            ubEnginePower -= 1;
        }
        else {
            ubEnginePower = 0;
            ulEngineTimer = 0;
        }
    }
}

UBYTE engineIsPowerJustChanged() {
    return ubEnginePower != ubEngineLastPower;
}