#include "gamestates/map/monster.h"

#include <ace/managers/blit.h>
#include <ace/managers/game.h>

#include "game.h"
#include "atlas.h"
#include "gamestates/map/ship.h"

tBitMap *pMonsterBitMapAtlas[MONSTER_TYPE_COUNT][MONSTER_ATLAS_SIZE];
tBitMap *pMonsterBitMapMaskAtlas[MONSTER_TYPE_COUNT][MONSTER_ATLAS_SIZE];

tMonster pMonsters[MONSTER_COUNT_MAX];
UBYTE ubMonsterCount = 0;
ULONG ulMonsterUpdateTimer = 0;
UBYTE ubMonsterUpdateIndex = 0;
UBYTE ubMonsterFrame = 0;
BYTE bMonsterMoveDir = -1;
UBYTE ubMoveDown = 0;

void monsterCreateBitMapAtlas() {
    createAtlasFileWithMask(pMonsterBitMapAtlas[0], pMonsterBitMapMaskAtlas[0], 0, "/data/monster_1_frames/monster_1_0.bm", "/data/monster_1_frames/monster_1_0.msk");
    createAtlasFileWithMask(pMonsterBitMapAtlas[0], pMonsterBitMapMaskAtlas[0], 1, "/data/monster_1_frames/monster_1_1.bm", "/data/monster_1_frames/monster_1_1.msk");
    createAtlasFileWithMask(pMonsterBitMapAtlas[0], pMonsterBitMapMaskAtlas[0], 2, "/data/monster_1_frames/monster_1_2.bm", "/data/monster_1_frames/monster_1_2.msk");
    createAtlasFileWithMask(pMonsterBitMapAtlas[0], pMonsterBitMapMaskAtlas[0], 3, "/data/monster_1_frames/monster_1_3.bm", "/data/monster_1_frames/monster_1_3.msk");

    createAtlasFileWithMask(pMonsterBitMapAtlas[1], pMonsterBitMapMaskAtlas[1], 0, "/data/monster_2_frames/monster_2_0.bm", "/data/monster_2_frames/monster_2_0.msk");
    createAtlasFileWithMask(pMonsterBitMapAtlas[1], pMonsterBitMapMaskAtlas[1], 1, "/data/monster_2_frames/monster_2_1.bm", "/data/monster_2_frames/monster_2_1.msk");
    createAtlasFileWithMask(pMonsterBitMapAtlas[1], pMonsterBitMapMaskAtlas[1], 2, "/data/monster_2_frames/monster_2_2.bm", "/data/monster_2_frames/monster_2_2.msk");
    createAtlasFileWithMask(pMonsterBitMapAtlas[1], pMonsterBitMapMaskAtlas[1], 3, "/data/monster_2_frames/monster_2_3.bm", "/data/monster_2_frames/monster_2_3.msk");

    createAtlasFileWithMask(pMonsterBitMapAtlas[2], pMonsterBitMapMaskAtlas[2], 0, "/data/monster_3_frames/monster_3_0.bm", "/data/monster_3_frames/monster_3_0.msk");
    createAtlasFileWithMask(pMonsterBitMapAtlas[2], pMonsterBitMapMaskAtlas[2], 1, "/data/monster_3_frames/monster_3_1.bm", "/data/monster_3_frames/monster_3_1.msk");
    createAtlasFileWithMask(pMonsterBitMapAtlas[2], pMonsterBitMapMaskAtlas[2], 2, "/data/monster_3_frames/monster_3_2.bm", "/data/monster_3_frames/monster_3_2.msk");
    createAtlasFileWithMask(pMonsterBitMapAtlas[2], pMonsterBitMapMaskAtlas[2], 3, "/data/monster_3_frames/monster_3_3.bm", "/data/monster_3_frames/monster_3_3.msk");
}

void monsterDestroyBitMapAtlas() {
    destroyAtlasFilesWithMask(pMonsterBitMapAtlas[0], pMonsterBitMapMaskAtlas[0], MONSTER_ATLAS_SIZE);
    destroyAtlasFilesWithMask(pMonsterBitMapAtlas[1], pMonsterBitMapMaskAtlas[1], MONSTER_ATLAS_SIZE);
    destroyAtlasFilesWithMask(pMonsterBitMapAtlas[2], pMonsterBitMapMaskAtlas[2], MONSTER_ATLAS_SIZE);
}

void monsterDraw() {
    UBYTE ubIndex = ubMonsterCount;
    while (ubIndex--) {
        if (pMonsters[ubIndex].ubType != MONSTER_TYPE_COUNT) {
            monsterDrawIndex(ubIndex);
        }
    }
}

void monsterDrawIndex(UBYTE ubMonsterIndex) {
    blitCopyMask(
        pMonsterBitMapAtlas[pMonsters[ubMonsterIndex].ubType][ubMonsterFrame], 0, 0,
        g_pBufferManager->pBuffer, pMonsters[ubMonsterIndex].sCoord.sUwCoord.uwX, pMonsters[ubMonsterIndex].sCoord.sUwCoord.uwY,
        MONSTER_WIDTH, MONSTER_HEIGHT,
        (UWORD *) pMonsterBitMapMaskAtlas[pMonsters[ubMonsterIndex].ubType][ubMonsterFrame]->Planes[0]
    );
}

void monsterUndraw() {
    UBYTE ubIndex = ubMonsterCount;
    while (ubIndex--) {
        monsterUndrawIndex(ubIndex);
    }
}

void monsterUndrawIndex(UBYTE ubMonsterIndex) {
    blitCopy(
        g_pBackgroundBitMap, pMonsters[ubMonsterIndex].sCoord.sUwCoord.uwX, pMonsters[ubMonsterIndex].sCoord.sUwCoord.uwY - (pMonsters[ubMonsterIndex].ubFixupY * MONSTER_STEP_Y),
        g_pBufferManager->pBuffer, pMonsters[ubMonsterIndex].sCoord.sUwCoord.uwX, pMonsters[ubMonsterIndex].sCoord.sUwCoord.uwY - (pMonsters[ubMonsterIndex].ubFixupY * MONSTER_STEP_Y),
        MONSTER_WIDTH, MONSTER_HEIGHT,
        MINTERM_COOKIE, 0xFF
    );

    pMonsters[ubMonsterIndex].ubFixupY = 0;
}

void monsterMove() {
    if (ubMonsterUpdateIndex < ubMonsterCount) {
        monsterUndrawIndex(ubMonsterUpdateIndex);

        monsterMoveLeftRight();

        monsterDrawIndex(ubMonsterUpdateIndex);
    }
    else {
        ubMonsterFrame = (ubMonsterFrame + 1) % MONSTER_ATLAS_SIZE;
        if (ubMoveDown) {
            ubMoveDown = 0;
            monsterMoveDown();
        }
    }

    if (0 < bMonsterMoveDir) {
        monsterSetPrevAlive();
    }
    else {
        monsterSetNextAlive();
    }
}

void monsterMoveLeftRight() {
    if (0 < bMonsterMoveDir) {
        if (pMonsters[ubMonsterUpdateIndex].sCoord.sUwCoord.uwX < WINDOW_SCREEN_WIDTH - MONSTER_WIDTH - MONSTER_STEP_X) {
            pMonsters[ubMonsterUpdateIndex].sCoord.sUwCoord.uwX += MONSTER_STEP_X;
        }
        else {
            ubMoveDown = 1;
            pMonsters[ubMonsterUpdateIndex].sCoord.sUwCoord.uwX = WINDOW_SCREEN_WIDTH - MONSTER_WIDTH;
        }
    }
    else {
        if (MONSTER_STEP_X < pMonsters[ubMonsterUpdateIndex].sCoord.sUwCoord.uwX) {
            pMonsters[ubMonsterUpdateIndex].sCoord.sUwCoord.uwX -= MONSTER_STEP_X;
        }
        else {
            ubMoveDown = 1;
            pMonsters[ubMonsterUpdateIndex].sCoord.sUwCoord.uwX = 0;
        }
    }
}

void monsterMoveDown() {
    bMonsterMoveDir *= -1;
    UBYTE ubIndex = ubMonsterCount;
    while (ubIndex--) {
        if (pMonsters[ubIndex].ubType != MONSTER_TYPE_COUNT) {
            pMonsters[ubIndex].sCoord.sUwCoord.uwY += MONSTER_STEP_Y;
            pMonsters[ubIndex].ubFixupY = 1;
        }
    }
}

void monsterSetNextAlive() {
    if (ubMonsterCount < ubMonsterUpdateIndex) {
        ubMonsterUpdateIndex = -1;
    }

    do {
        ubMonsterUpdateIndex += 1;
    }
    while ((ubMonsterUpdateIndex < ubMonsterCount) && (pMonsters[ubMonsterUpdateIndex].ubType == MONSTER_TYPE_COUNT));
}

void monsterSetPrevAlive() {
    if (ubMonsterCount <= ubMonsterUpdateIndex) {
        ubMonsterUpdateIndex = ubMonsterCount;
    }

    do {
        ubMonsterUpdateIndex -= 1;
    }
    while ((ubMonsterUpdateIndex < ubMonsterCount) && (pMonsters[ubMonsterUpdateIndex].ubType == MONSTER_TYPE_COUNT));
}

UBYTE monsterCheckCollision(UWORD uwX, UWORD uwY) {
    UBYTE ubCollided = 0;
    UBYTE ubIndex = ubMonsterCount;
    while (ubIndex--) {
        if (pMonsters[ubIndex].ubType != MONSTER_TYPE_COUNT) {
            if ((pMonsters[ubIndex].sCoord.sUwCoord.uwX <= uwX) && (uwX <= (pMonsters[ubIndex].sCoord.sUwCoord.uwX + MONSTER_WIDTH))) {
                if ((pMonsters[ubIndex].sCoord.sUwCoord.uwY <= uwY) && (uwY <= (pMonsters[ubIndex].sCoord.sUwCoord.uwY + MONSTER_HEIGHT))) {
                    monsterKill(ubIndex);
                    ubCollided = 1;
                }
            }
        }
    }

    return ubCollided;
}

void monsterKill(UBYTE ubMonsterIndex) {
    pMonsters[ubMonsterIndex].ubType = MONSTER_TYPE_COUNT;
    monsterUndrawIndex(ubMonsterIndex);
}

void monsterGenerate(UBYTE ubMonsterType, UBYTE ubCount, UWORD uwCoordX, UWORD uwCoordY, UWORD uwDistanceX, UWORD uwShiftY) {
    for (UBYTE ubIndex = 0; ubIndex < ubCount; ++ubIndex) {
        pMonsters[ubMonsterCount].ubType = ubMonsterType;
        pMonsters[ubMonsterCount].sCoord.sUwCoord.uwX = uwCoordX + (uwDistanceX * ubIndex);
        pMonsters[ubMonsterCount].sCoord.sUwCoord.uwY = uwCoordY + (uwShiftY * (ubIndex % 2));
        pMonsters[ubMonsterCount].ubFixupY = 0;

        ++ubMonsterCount;
    }
}

void monsterRemoveAll() {
    ubMonsterCount = 0;
}

UBYTE monsterIsAnyAlive() {
    UBYTE ubIndex = ubMonsterCount;
    while (ubIndex--) {
        if (pMonsters[ubIndex].ubType != MONSTER_TYPE_COUNT) {
            return 1;
        }
    }

    return 0;
}

UBYTE monsterIsAnyTooLow() {
    UBYTE ubIndex = ubMonsterCount;
    while (ubIndex--) {
        if (pMonsters[ubIndex].ubType != MONSTER_TYPE_COUNT) {
            if (g_sShipCoord.sUwCoord.uwY <= pMonsters[ubIndex].sCoord.sUwCoord.uwY + MONSTER_HEIGHT) {
                logWrite("TOO LOW\n");
                return 1;
            }
        }
    }

    return 0;
}