#include "gamestates/map/map.h"

#include <ace/managers/key.h>
#include <ace/managers/game.h>
#include <ace/managers/blit.h>

#include "game.h"
#include "gamestates/map/ship.h"
#include "gamestates/map/engine.h"
#include "gamestates/map/projectile.h"

BYTE bMoveDir = 0;

void gsMapCreate() {
    blitCopyAligned(g_pBackgroundBitMap, 0, 0, g_pBufferManager->pBuffer, 0, 0, WINDOW_SCREEN_WIDTH, WINDOW_SCREEN_HEIGHT);

    shipCreateBitMapAtlas();
    engineCreateBitMapAtlas();
    projectileCreateBitMapAtlas();

    g_sShipCoord.sUwCoord.uwX = (WINDOW_SCREEN_WIDTH + SHIP_WIDTH) >> 2;
    g_sShipCoord.sUwCoord.uwY = WINDOW_SCREEN_HEIGHT - SHIP_HEIGHT - 24;

    shipDraw();
    engineDraw();
}

void gsMapLoop() {
    if (keyCheck(KEY_ESCAPE)) {
        gameClose();
        return;
    }

    bMoveDir = 0;

    if (keyCheck(KEY_A) || keyCheck(KEY_LEFT)) {
        bMoveDir -= 1;
    }

    if (keyCheck(KEY_D) || keyCheck(KEY_RIGHT)) {
        bMoveDir += 1;
    }

    if (keyCheck(KEY_SPACE) || keyCheck(KEY_RETURN)) {
        projectileFire();
    }

    switch (bMoveDir) {
        case -1:
            shipAccelerateLeft();
            shipTiltLeft();
            engineAccelerate();
            break;
        case 0:
            shipDecelerate();
            shipTiltCenter();
            engineDecelerate();
            break;
        case 1:
            shipAccelerateRight();
            shipTiltRight();
            engineAccelerate();
            break;
    }

    shipMove();
    projectileMove();

    if (shipIsJustMoved() || shipIsJustTilted() || engineIsPowerJustChanged()) {
        undrawShipWithEngine();

        shipDraw();
        engineDraw();
    }

    if (projectileIsJustMoved()) {
        projectileUndraw();
        projectileDraw();
    }
}

void gsMapDestroy() {
    shipDestroyBitMapAtlas();
    engineDestroyBitMapAtlas();
    projectileDestroyBitMapAtlas();
}

void undrawShipWithEngine() {
    blitCopy(
        g_pBackgroundBitMap, g_sShipLastCoord.sUwCoord.uwX, g_sShipLastCoord.sUwCoord.uwY,
        g_pBufferManager->pBuffer, g_sShipLastCoord.sUwCoord.uwX, g_sShipLastCoord.sUwCoord.uwY,
        MAX(SHIP_WIDTH, ENGINE_WIDTH), MAX(SHIP_HEIGHT, ENGINE_SHIFT_Y + ENGINE_HEIGHT),
        MINTERM_COOKIE, 0xFF
    );
}