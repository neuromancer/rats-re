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
void __cdecl RenderExplosionWave(int x, int y, int step_x, int step_y); /* 0x0040560E */
void __cdecl DrawBombExplosion(int index); /* 0x0040591A */
void DrawPausedOverlay(void); /* 0x00405AF5 */
int CALLBACK ScorePanelDialogProc(HWND hWnd, int message, WPARAM wParam, LPARAM lParam); /* 0x00405DB8 */
int CALLBACK DemoVersionDialogProc(HWND hWnd, int message, WPARAM wParam, LPARAM lParam); /* 0x00405F72 */
void DrawStartButton(void); /* 0x00408854 */
void UpdateMainMenuState(void); /* 0x00408A51 */
BOOL LoadLevelData(void); /* 0x00408E6A */
int LoadHighScores(void); /* 0x00408F02 */
void SaveHighScores(void); /* 0x00409092 */
int IsRatsHelpFile(void); /* 0x00409DB6 */
#endif
