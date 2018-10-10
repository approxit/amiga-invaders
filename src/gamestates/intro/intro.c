#include "gamestates/intro/intro.h"

#include "game.h"
#include "gamestates/map/map.h"

#include <ace/managers/key.h>
#include <ace/managers/game.h>
#include <ace/managers/blit.h>

#define WRITER_DELAY 3
#define WRITER_DELAY_DONE 25
#define WRITER_OFFSET_X 0
#define WRITER_OFFSET_Y 0
#define WRITER_LETTER_SPACING 2

UWORD uwWriterX = 0;
UWORD uwWriterY = 0;
ULONG ulWriterTimer = 0;
UBYTE ubWriterBlockVisibility = 0;
FILE *pWriterFile = 0;

void gsIntroCreate() {
    pWriterFile = fopen("/data/intro.txt", "r");

    blitCopyAligned(g_pBackgroundBitMap, 0, 0, g_pBufferManager->pBuffer, 0, 0, WINDOW_SCREEN_WIDTH, WINDOW_SCREEN_HEIGHT);

    ulWriterTimer = timerGet() + (WRITER_DELAY * 2);
}

void gsIntroLoop() {
    if (!feof(pWriterFile) && (timerCheck(&ulWriterTimer, WRITER_DELAY) || keyCheck(KEY_SPACE))) {
        writerWrite();
    }

    if (feof(pWriterFile)) {
        if (timerCheck(&ulWriterTimer, WRITER_DELAY_DONE)) {
            ubWriterBlockVisibility ^= 1;
            writerDrawBlock(ubWriterBlockVisibility);
        }

        if (keyUse(KEY_SPACE)) {
            gameChangeState(gsMapCreate, gsMapLoop, gsMapDestroy);
            return;
        }
    }

    if (keyCheck(KEY_ESCAPE)) {
        gameClose();
        return;
    }
}

void gsIntroDestroy() {
    fclose(pWriterFile);
}

void writerWrite() {
    char cChar = fgetc(pWriterFile);
    UBYTE ubSpaceWidth = g_pFont->pCharOffsets[' ' + 1] - g_pFont->pCharOffsets[' '];

    if (cChar == EOF) {
        keySetState(KEY_SPACE, KEY_USED);
        ulWriterTimer = timerGet();
        return;
    }

    writerDrawBlock(0);

    switch (cChar) {
        case '\n':
            uwWriterX = 0;
            uwWriterY += g_pFont->uwHeight * 2;
            break;
        case ' ':
            uwWriterX += ubSpaceWidth + WRITER_LETTER_SPACING;
            break;
        default:
            blitCopy(
                g_pFont->pRawData, g_pFont->pCharOffsets[cChar], 0,
                g_pBufferManager->pBuffer, uwWriterX, uwWriterY,
                g_pFont->pCharOffsets[cChar + 1] - g_pFont->pCharOffsets[cChar], g_pFont->uwHeight,
                MINTERM_COOKIE, 0x01
            );

            uwWriterX += g_pFont->pCharOffsets[cChar + 1] - g_pFont->pCharOffsets[cChar] + WRITER_LETTER_SPACING;
    }

    if (WINDOW_SCREEN_WIDTH <= uwWriterX + ubSpaceWidth) {
        uwWriterX = 0;
        uwWriterY += g_pFont->uwHeight * 2;
    }
    
    if (WINDOW_SCREEN_HEIGHT <= uwWriterY + g_pFont->uwHeight) {
        uwWriterY = 0;
    }

    writerDrawBlock(1);
}

void writerDrawBlock(UBYTE ubBlockVisibility) {
    UBYTE ubSpaceWidth = g_pFont->pCharOffsets[' ' + 1] - g_pFont->pCharOffsets[' '];

    if (ubBlockVisibility) {
        blitRect(
            g_pBufferManager->pBuffer, uwWriterX, uwWriterY,
            ubSpaceWidth, g_pFont->uwHeight,
            1
        );
    }
    else {
        blitCopy(
            g_pBackgroundBitMap, uwWriterX, uwWriterY,
            g_pBufferManager->pBuffer, uwWriterX, uwWriterY,
            ubSpaceWidth, g_pFont->uwHeight,
            MINTERM_COOKIE, 0x01
        );
    }
}