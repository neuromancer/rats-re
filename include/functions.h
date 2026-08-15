#ifndef RATS_FUNCTIONS_H
#define RATS_FUNCTIONS_H

void __cdecl DrawBitmapPair(HGDIOBJ hObj1, HGDIOBJ hObj2, int x, int y, int cx, int cy); /* 0x00404D6E */
void __cdecl RenderBitmapToWindow(HGDIOBJ hObject, int x, int y, int cx, int cy); /* 0x00404E3B */
void DrawBitmapToWindow(void); /* 0x00404ECE */
void DrawScore(void); /* 0x00404F8B */
void DrawScorePanel(void); /* 0x0040507F */
void __cdecl DrawScoreDigits(void); /* 0x0040525D */
void __cdecl RenderScoreOverlay(void); /* 0x00405343 */
void __cdecl DrawFrameBorder(int offset_x, int offset_y); /* 0x0040546B */
void __cdecl ExplodeBomb(int index); /* 0x0040552E */
void DrawPausedOverlay(void); /* 0x00405AF5 */
void UpdateMainMenuState(void); /* 0x00408A51 */
BOOL LoadLevelData(void); /* 0x00408E6A */
void SaveHighScores(void); /* 0x00409092 */
int IsRatsHelpFile(void); /* 0x00409DB6 */
#endif
