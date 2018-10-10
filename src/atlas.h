#ifndef GUARD_SPACE_INVADERS_ATLAS_H
#define GUARD_SPACE_INVADERS_ATLAS_H

#include <ace/types.h>
#include <ace/utils/bitmap.h>

void createAtlasFile(
	INOUT tBitMap **pBitMapAtlas,
	IN UBYTE ubAtlasIndex,
	IN char *szBitMapFilePath
);

void destroyAtlasFiles(
	INOUT tBitMap **pBitMapAtlas,
	IN UBYTE ubAtlasCount
);

void createAtlasFileWithMask(
	INOUT tBitMap **pBitMapAtlas,
	INOUT tBitMap **pBitMapMaskAtlas,
	IN UBYTE ubAtlasIndex,
	IN char *szBitMapFilePath,
	IN char *szBitMapMaskFilePath
);

void destroyAtlasFilesWithMask(
	INOUT tBitMap **pBitMapAtlas,
	INOUT tBitMap **pBitMapMaskAtlas,
	IN UBYTE ubAtlasCount
);

#endif