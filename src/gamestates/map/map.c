#include "gamestates/map/map.h"

#include <ace/managers/key.h>
#include <ace/managers/game.h>
#include <ace/managers/blit.h>

#include "game.h"
#include "gamestates/map/ship.h"
#include "gamestates/map/engine.h"
#include "gamestates/map/projectile.h"
#include "gamestates/map/monster.h"
#include "gamestates/map/monster_projectile.h"

BYTE bMoveDir = 0;

void gsMapCreate() {
    shipCreateBitMapAtlas();
    engineCreateBitMapAtlas();
    projectileCreateBitMapAtlas();
    monsterCreateBitMapAtlas();

    mapLoadLevel();
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
    monsterMove();
    monsterProjectileMove();

    if (shipIsJustMoved() || shipIsJustTilted() || engineIsPowerJustChanged()) {
        undrawShipWithEngine();

        shipDraw();
        engineDraw();
    }

    if (projectileIsJustMoved()) {
        projectileUndraw();
        projectileDraw();
    }

    if (!monsterIsAnyAlive() || monsterIsAnyTooLow()) {
        mapLoadLevel();
        monsterDraw();
    }
}

void gsMapDestroy() {
    shipDestroyBitMapAtlas();
    engineDestroyBitMapAtlas();
    projectileDestroyBitMapAtlas();
    monsterDestroyBitMapAtlas();
}

void undrawShipWithEngine() {
    blitCopy(
        g_pBackgroundBitMap, g_sShipLastCoord.sUwCoord.uwX, g_sShipLastCoord.sUwCoord.uwY,
        g_pBufferManager->pBuffer, g_sShipLastCoord.sUwCoord.uwX, g_sShipLastCoord.sUwCoord.uwY,
        MAX(SHIP_WIDTH, ENGINE_WIDTH), MAX(SHIP_HEIGHT, ENGINE_SHIFT_Y + ENGINE_HEIGHT),
        MINTERM_COOKIE, 0xFF
    );
}

void mapLoadLevel() {
    blitCopyAligned(g_pBackgroundBitMap, 0, 0, g_pBufferManager->pBuffer, 0, 0, WINDOW_SCREEN_WIDTH, WINDOW_SCREEN_HEIGHT);

    monsterRemoveAll();
    monsterGenerate(MONSTER_TYPE_RED, 5, 50, 20, 50, 0);
    monsterGenerate(MONSTER_TYPE_GREEN, 11, 30, 50, 25, 8);
    monsterGenerate(MONSTER_TYPE_GREEN, 11, 30, 80, 25, 8);
    monsterGenerate(MONSTER_TYPE_GRAY, 11, 30, 110, 25, 8);
    monsterGenerate(MONSTER_TYPE_GRAY, 11, 30, 140, 25, 8);

    g_sShipCoord.sUwCoord.uwX = (WINDOW_SCREEN_WIDTH + SHIP_WIDTH) >> 2;
    g_sShipCoord.sUwCoord.uwY = WINDOW_SCREEN_HEIGHT - SHIP_HEIGHT - 6;

    shipDraw();
    engineDraw();
    monsterDraw();
}