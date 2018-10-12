#include "gamestates/map/monster_projectile.h"

#include <ace/managers/blit.h>

#include "gamestates/map/monster.h"
#include "gamestates/map/projectile.h"
#include "gamestates/map/ship.h"
#include "game.h"

UBYTE ubMonsterProjectileFired = 0;
tUwCoordYX sMonsterProjectileCoord;

void monsterProjectileDraw() {
    if (ubMonsterProjectileFired) {
        blitCopyMask(
            pProjectileBitMapAtlas[0], 0, 0,
            g_pBufferManager->pBuffer, sMonsterProjectileCoord.sUwCoord.uwX, sMonsterProjectileCoord.sUwCoord.uwY,
            MONSTER_PROJECTILE_WIDTH, MONSTER_PROJECTILE_HEIGHT,
            (UWORD *) pProjectileBitMapMaskAtlas[0]->Planes[0]
        );
    }
}

void monsterProjectileUndraw() {
    blitCopy(
        g_pBackgroundBitMap, sMonsterProjectileCoord.sUwCoord.uwX, sMonsterProjectileCoord.sUwCoord.uwY,
        g_pBufferManager->pBuffer, sMonsterProjectileCoord.sUwCoord.uwX, sMonsterProjectileCoord.sUwCoord.uwY,
        MONSTER_PROJECTILE_WIDTH, MONSTER_PROJECTILE_HEIGHT,
        MINTERM_COOKIE, 0xFF
    );
}

void monsterProjectileFire(UBYTE ubMonsterIndex) {
    if (!ubMonsterProjectileFired) {
        ubMonsterProjectileFired = 1;

        sMonsterProjectileCoord.sUwCoord.uwX = pMonsters[ubMonsterIndex].sCoord.sUwCoord.uwX + (MONSTER_WIDTH >> 2);
        sMonsterProjectileCoord.sUwCoord.uwY = pMonsters[ubMonsterIndex].sCoord.sUwCoord.uwY + MONSTER_HEIGHT;
    }
}

void monsterProjectileMove() {
    monsterProjectileUndraw();

    if (ubMonsterProjectileFired) {
        if (sMonsterProjectileCoord.sUwCoord.uwY < WINDOW_SCREEN_HEIGHT - MONSTER_PROJECTILE_HEIGHT - PROJECTILE_SPEED) {
            sMonsterProjectileCoord.sUwCoord.uwY += MONSTER_PROJECTILE_SPEED;
        }
        else {
            sMonsterProjectileCoord.sUwCoord.uwY = WINDOW_SCREEN_HEIGHT - MONSTER_PROJECTILE_HEIGHT;
            ubMonsterProjectileFired = 0;
        }

        if (shipCheckCollision(sMonsterProjectileCoord.sUwCoord.uwX, sMonsterProjectileCoord.sUwCoord.uwY)) {
            ubMonsterProjectileFired = 0;
        }
    }

    monsterProjectileDraw();
}