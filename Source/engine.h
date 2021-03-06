/**
 * @file engine.h
 *
 *  of basic engine helper functions:
 * - Sprite blitting
 * - Drawing
 * - Angle calculation
 * - RNG
 * - Memory allocation
 * - File loading
 * - Video playback
 */
#ifndef __ENGINE_H__
#define __ENGINE_H__

DEVILUTION_BEGIN_NAMESPACE

#ifdef __cplusplus
extern "C" {
#endif

inline BYTE *CelGetFrameStart(BYTE *pCelBuff, int nCel)
{
	DWORD *pFrameTable;

	pFrameTable = (DWORD *)pCelBuff;

	return pCelBuff + SwapLE32(pFrameTable[nCel]);
}

#define LOAD_LE32(b) (((DWORD)(b)[3] << 24) | ((DWORD)(b)[2] << 16) | ((DWORD)(b)[1] << 8) | (DWORD)(b)[0])
inline BYTE *CelGetFrame(BYTE *pCelBuff, int nCel, int *nDataSize)
{
	DWORD nCellStart;

	nCellStart = LOAD_LE32(&pCelBuff[nCel * 4]);
	*nDataSize = LOAD_LE32(&pCelBuff[(nCel + 1) * 4]) - nCellStart;
	return pCelBuff + nCellStart;
}

inline BYTE *CelGetFrameClipped(BYTE *pCelBuff, int nCel, int *nDataSize)
{
	DWORD nDataStart;
	BYTE *pRLEBytes = CelGetFrame(pCelBuff, nCel, nDataSize);

	nDataStart = pRLEBytes[1] << 8 | pRLEBytes[0];
	*nDataSize -= nDataStart;

	return pRLEBytes + nDataStart;
}

void CelDraw(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth);
void CelBlitFrame(BYTE *pBuff, BYTE *pCelBuff, int nCel, int nWidth);
void CelClippedDraw(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth);
void CelDrawLight(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, BYTE *tbl);
void CelClippedDrawLight(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth);
void CelClippedBlitLightTrans(BYTE *pBuff, BYTE *pCelBuff, int nCel, int nWidth);
void CelDrawLightRed(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, char light);
void CelBlitSafe(BYTE *pDecodeTo, BYTE *pRLEBytes, int nDataSize, int nWidth);
void CelClippedDrawSafe(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth);
void CelBlitLightSafe(BYTE *pDecodeTo, BYTE *pRLEBytes, int nDataSize, int nWidth, BYTE *tbl);
void CelDrawLightRedSafe(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, char light);
void CelBlitWidth(BYTE *pBuff, int x, int y, int wdt, BYTE *pCelBuff, int nCel, int nWidth);
void CelBlitOutline(BYTE col, int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth);
void ENG_set_pixel(int sx, int sy, BYTE col);
void DrawTransparentRectangle(int x0, int dx, int y0, int dy, int color);
void DrawSolidRectangle(int x0, int dx, int y0, int dy, int color);
int CalculateTextWidth(const char *s);
void DrawLine(int x0, int y0, int x1, int y1, BYTE col);
int GetDirection(int x1, int y1, int x2, int y2);
void SetRndSeed(int s);
int AdvanceRndSeed();
int GetRndSeed();
int random_(BYTE idx, int v);
BYTE *DiabloAllocPtr(DWORD dwBytes);
void mem_free_dbg(void *p);
BYTE *LoadFileInMem(const char *pszName, DWORD *pdwFileLen);
DWORD LoadFileWithMem(const char *pszName, BYTE *p);
void Cl2ApplyTrans(BYTE *p, BYTE *ttbl, int nCel);
void Cl2Draw(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth);
void Cl2DrawOutline(BYTE col, int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth);
void Cl2DrawLightTbl(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth, char light);
void Cl2DrawLight(int sx, int sy, BYTE *pCelBuff, int nCel, int nWidth);
void PlayInGameMovie(const char *pszMovie);

#ifdef __cplusplus
}
#endif

DEVILUTION_END_NAMESPACE

#endif /* __ENGINE_H__ */
