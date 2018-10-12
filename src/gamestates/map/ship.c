#include "gamestates/map/ship.h"

#include <ace/managers/blit.h>

#include "game.h"
#include "atlas.h"
#include "gamestates/map/map.h"

tBitMap *pShipBitMapAtlas[SHIP_ATLAS_SIZE];
tBitMap *pShipBitMapMaskAtlas[SHIP_ATLAS_SIZE];

tUwCoordYX g_sShipCoord;
tUwCoordYX g_sShipLastCoord;
ULONG ulShipSpeedTimer = 0;
BYTE bShipSpeed = 0;
ULONG ulShipTiltTimer = 0;
UBYTE ubShipTilt = SHIP_ATLAS_MIDDLE;
UBYTE ubShipLastTilt = SHIP_ATLAS_MIDDLE;

void shipCreateBitMapAtlas() {
    createAtlasFileWithMask(pShipBitMapAtlas, pShipBitMapMaskAtlas, 0, "/data/ship_frames/ship_0.bm", "/data/ship_frames/ship_0.msk");
    createAtlasFileWithMask(pShipBitMapAtlas, pShipBitMapMaskAtlas, 1, "/data/ship_frames/ship_1.bm", "/data/ship_frames/ship_1.msk");
    createAtlasFileWithMask(pShipBitMapAtlas, pShipBitMapMaskAtlas, 2, "/data/ship_frames/ship_2.bm", "/data/ship_frames/ship_2.msk");
    createAtlasFileWithMask(pShipBitMapAtlas, pShipBitMapMaskAtlas, 3, "/data/ship_frames/ship_3.bm", "/data/ship_frames/ship_3.msk");
    createAtlasFileWithMask(pShipBitMapAtlas, pShipBitMapMaskAtlas, 4, "/data/ship_frames/ship_4.bm", "/data/ship_frames/ship_4.msk");
    // char szBitMapPath[255];
    // char szBitMapMaskPath[255];

    // UBYTE ubIndex = SHIP_ATLAS_SIZE;
    // while (ubIndex--) {
    //     sprintf(szBitMapPath, "/data/ship_frames/ship_%u.bm", ubIndex);
    //     sprintf(szBitMapMaskPath, "/data/ship_frames/ship_%u.msk", ubIndex);

    //     createAtlasFileWithMask(pShipBitMapAtlas, pShipBitMapMaskAtlas, ubIndex, szBitMapPath, szBitMapMaskPath);
    // }
}

void shipDestroyBitMapAtlas() {
    destroyAtlasFilesWithMask(pShipBitMapAtlas, pShipBitMapMaskAtlas, SHIP_ATLAS_SIZE);
}

void shipDraw() {
	blitCopyMask(
		pShipBitMapAtlas[ubShipTilt], 0, 0,
		g_pBufferManager->pBuffer, g_sShipCoord.sUwCoord.uwX, g_sShipCoord.sUwCoord.uwY,
		SHIP_WIDTH, SHIP_HEIGHT,
		(UWORD *) pShipBitMapMaskAtlas[ubShipTilt]->Planes[0]
	);
}

void shipUndraw() {
    blitCopy(
        g_pBackgroundBitMap, g_sShipCoord.sUwCoord.uwX, g_sShipCoord.sUwCoord.uwY,
        g_pBufferManager->pBuffer, g_sShipCoord.sUwCoord.uwX, g_sShipCoord.sUwCoord.uwY,
        SHIP_WIDTH, SHIP_HEIGHT,
        MINTERM_COPY, 0xFF
    );
}

void shipAccelerateLeft() {
    if (!ulShipSpeedTimer) {
        ulShipSpeedTimer = timerGet();
    }

    if (timerCheck(&ulShipSpeedTimer, SHIP_SPEED_DELAY)) {
        if (-SHIP_SPEED_MAX < bShipSpeed - 1) {
            bShipSpeed -= 1;
        }
        else {
            bShipSpeed = -SHIP_SPEED_MAX;
        }
    }
}

void shipAccelerateRight() {
    if (!ulShipSpeedTimer) {
        ulShipSpeedTimer = timerGet();
    }

    if (timerCheck(&ulShipSpeedTimer, SHIP_SPEED_DELAY)) {
        if (bShipSpeed + 1 < SHIP_SPEED_MAX) {
            bShipSpeed += 1;
        }
        else {
            bShipSpeed = SHIP_SPEED_MAX;
        }
    }
}

void shipDecelerate() {
    if (bShipSpeed < 0) {
        shipAccelerateRight();
    }
    if (0 < bShipSpeed) {
        shipAccelerateLeft();
    }
}

void shipMove() {
    g_sShipLastCoord.ulYX = g_sShipCoord.ulYX;

    if (bShipSpeed < 0) {
        if (-bShipSpeed < g_sShipCoord.sUwCoord.uwX) {
            g_sShipCoord.sUwCoord.uwX += bShipSpeed;
        }
        else {
            g_sShipCoord.sUwCoord.uwX = 0;
        }
    }
    else if (0 < bShipSpeed) {
        if (g_sShipCoord.sUwCoord.uwX < WINDOW_SCREEN_WIDTH - SHIP_WIDTH - bShipSpeed) {
            g_sShipCoord.sUwCoord.uwX += bShipSpeed;
        }
        else {
            g_sShipCoord.sUwCoord.uwX = WINDOW_SCREEN_WIDTH - SHIP_WIDTH;
        }
    }
}

void shipTiltLeft() {
    ubShipLastTilt = ubShipTilt;

    if (!ulShipTiltTimer) {
        ulShipTiltTimer = timerGet();
    }

    if (timerCheck(&ulShipTiltTimer, SHIP_TILT_DELAY)) {
        if (1 < ubShipTilt) {
            ubShipTilt -= 1;
        }
        else {
            ubShipTilt = 0;
        }
    }
}

void shipTiltRight() {
    ubShipLastTilt = ubShipTilt;

    if (!ulShipTiltTimer) {
        ulShipTiltTimer = timerGet();
    }

    if (timerCheck(&ulShipTiltTimer, SHIP_TILT_DELAY)) {
        if (ubShipTilt < SHIP_ATLAS_SIZE - 1) {
            ubShipTilt += 1;
        }
        else {
            ubShipTilt = SHIP_ATLAS_SIZE - 1;
        }
    }
}

void shipTiltCenter() {
    if (ubShipTilt < SHIP_ATLAS_MIDDLE) {
        shipTiltRight();
    }
    else if (SHIP_ATLAS_MIDDLE < ubShipTilt) {
        shipTiltLeft();
    }
}

UBYTE shipCheckCollision(UWORD uwX, UWORD uwY) {
    if ((g_sShipCoord.sUwCoord.uwX <= uwX) && (uwX <= (g_sShipCoord.sUwCoord.uwX + SHIP_WIDTH))) {
        if ((g_sShipCoord.sUwCoord.uwY <= uwY) && (uwY <= (g_sShipCoord.sUwCoord.uwY + SHIP_HEIGHT))) {
            shipKill();
            return 1;
        }
    }

    return 0;
}

void shipKill() {
    mapLoadLevel();
}

UBYTE shipIsJustTilted() {
    return ubShipTilt != ubShipLastTilt;
}

UBYTE shipIsJustMoved() {
    return g_sShipCoord.ulYX != g_sShipLastCoord.ulYX;
}