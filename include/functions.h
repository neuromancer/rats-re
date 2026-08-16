#ifndef RATS_FUNCTIONS_H
#define RATS_FUNCTIONS_H

int __cdecl IsLevelIndexInRange(int index); /* 0x0040215C */
void ShowLevelComplete(void); /* 0x00402205 */
void SubmitHighScore(void); /* 0x0040250C */
void RenderScoreboard(void); /* 0x004026D0 */
void __cdecl AddLevelToTable(int index, int x, int y); /* 0x00402BF3 */
void UpdateGameDisplay(void); /* 0x00402DC6 */
int __cdecl GetLevelDisplayInfo(int index); /* 0x00402EE7 */
int __cdecl GetLevelIndex(int level_index); /* 0x00402FD5 */
int __cdecl IsBombAtLevel(int level_index, int direction); /* 0x00403430 */
void __cdecl PlaceLevel(int source_index); /* 0x00403607 */
void __cdecl DrawLevelIndicator(void); /* 0x00404764 */
void __cdecl RenderCornerGlyph(HDC hdc, int panel_index, int is_active); /* 0x0040499F */
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
int CALLBACK HighScoreDialogProc(HWND hWnd, int message, WPARAM wParam, LPARAM lParam); /* 0x00405C52 */
int CALLBACK ScorePanelDialogProc(HWND hWnd, int message, WPARAM wParam, LPARAM lParam); /* 0x00405DB8 */
int CALLBACK DemoVersionDialogProc(HWND hWnd, int message, WPARAM wParam, LPARAM lParam); /* 0x00405F72 */
int CALLBACK OrderDialogProc(HWND hWnd, int message, WPARAM wParam, LPARAM lParam); /* 0x004061D3 */
void DrawStartButton(void); /* 0x00408854 */
void UpdateMainMenuState(void); /* 0x00408A51 */
int __cdecl InitializeGameLevel(void); /* 0x00408AD3 */
BOOL LoadLevelData(void); /* 0x00408E6A */
int LoadHighScores(void); /* 0x00408F02 */
void SaveHighScores(void); /* 0x00409092 */
void __cdecl LoadLevelBitmaps(int levelIndex); /* 0x0040910C */
int IsRatsHelpFile(void); /* 0x00409DB6 */
#endif
