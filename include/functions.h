#ifndef RATS_FUNCTIONS_H
#define RATS_FUNCTIONS_H

void __cdecl DrawBitmapPair(HGDIOBJ hObj1, HGDIOBJ hObj2, int x, int y, int cx, int cy); /* 0x00404D6E */
void __cdecl RenderBitmapToWindow(HGDIOBJ hObject, int x, int y, int cx, int cy); /* 0x00404E3B */
void __cdecl DrawFrameBorder(int offset_x, int offset_y); /* 0x0040546B */
void UpdateMainMenuState(void); /* 0x00408A51 */
BOOL LoadLevelData(void); /* 0x00408E6A */
void SaveHighScores(void); /* 0x00409092 */
int IsRatsHelpFile(void); /* 0x00409DB6 */
#endif
