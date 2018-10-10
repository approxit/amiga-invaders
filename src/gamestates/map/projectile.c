#include "gamestates/map/projectile.h"

#include <ace/managers/blit.h>

#include "game.h"
#include "atlas.h"
#include "gamestates/map/ship.h"

tBitMap *pProjectileBitMapAtlas[PROJECTILE_ATLAS_SIZE];
tBitMap *pProjectileBitMapMaskAtlas[PROJECTILE_ATLAS_SIZE];

ULONG ulProjectileTimer = 0;
UBYTE ubProjectileFired = 0;
tUwCoordYX sProjectileCoord;
tUwCoordYX sProjectileLastCoord;
UBYTE ubProjectileHeight = 0;
UBYTE ubProjectileLastHeight = 0;

void projectileCreateBitMapAtlas() {
    createAtlasFileWithMask(pProjectileBitMapAtlas, pProjectileBitMapMaskAtlas, 0, "/data/projectile_frames/projectile_0.bm", "/data/projectile_frames/projectile_0.msk");
}

void projectileDestroyBitMapAtlas() {
    destroyAtlasFilesWithMask(pProjectileBitMapAtlas, pProjectileBitMapMaskAtlas, PROJECTILE_ATLAS_SIZE);
}

void projectileDraw() {
    if (ubProjectileHeight) {
        blitCopyMask(
            pProjectileBitMapAtlas[0], 0, 0,
            g_pBufferManager->pBuffer, sProjectileCoord.sUwCoord.uwX, sProjectileCoord.sUwCoord.uwY,
            PROJECTILE_WIDTH, ubProjectileHeight,
            (UWORD *) pProjectileBitMapMaskAtlas[0]->Planes[0]
        );
    }
}

void projectileUndraw() {
    blitCopy(
        g_pBackgroundBitMap, sProjectileLastCoord.sUwCoord.uwX, sProjectileLastCoord.sUwCoord.uwY,
        g_pBufferManager->pBuffer, sProjectileLastCoord.sUwCoord.uwX, sProjectileLastCoord.sUwCoord.uwY,
        PROJECTILE_WIDTH, ubProjectileLastHeight,
        MINTERM_COOKIE, 0xFF
    );
}

void projectileFire() {
    if (!ubProjectileFired && timerCheck(&ulProjectileTimer, PROJECTILE_TIMER)) {
        ubProjectileFired = 1;
        sProjectileCoord.sUwCoord.uwX = g_sShipCoord.sUwCoord.uwX + PROJECTILE_SHIFT_X;
        sProjectileCoord.sUwCoord.uwY = g_sShipCoord.sUwCoord.uwY - PROJECTILE_SHIFT_Y;
        ubProjectileHeight = 1;
    }
}

void projectileMove() {
    ubProjectileLastHeight = ubProjectileHeight;

    if (ubProjectileFired) {
        sProjectileLastCoord.ulYX = sProjectileCoord.ulYX;

        if (PROJECTILE_SPEED < sProjectileCoord.sUwCoord.uwY) {
            sProjectileCoord.sUwCoord.uwY -= PROJECTILE_SPEED;
        }
        else {
            sProjectileCoord.sUwCoord.uwY = 0;
        }

        if (sProjectileCoord.sUwCoord.uwY) {
            if (ubProjectileHeight < PROJECTILE_HEIGHT - PROJECTILE_SPEED) {
                ubProjectileHeight += PROJECTILE_SPEED;
            }
            else {
                ubProjectileHeight = PROJECTILE_HEIGHT;
            }
        }
        else {
            if (PROJECTILE_SPEED < ubProjectileHeight) {
                ubProjectileHeight -= PROJECTILE_SPEED;
            }
            else {
                ubProjectileHeight = 0;
                ubProjectileFired = 0;
            }
        }

        logWrite("ubProjectileHeight: %d\n", ubProjectileHeight);
    }
}

UBYTE projectileIsJustMoved() {
    return (ubProjectileFired || ubProjectileLastHeight) && ((sProjectileLastCoord.ulYX != sProjectileCoord.ulYX) || (ubProjectileLastHeight != ubProjectileHeight));
}