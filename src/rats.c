#include "rats.h"

/* Function start: 0x401000 */
int WINAPI WinMain(
    HINSTANCE instance,
    HINSTANCE previous_instance,
    LPSTR command_line,
    int show_command)
{
    (void)instance;
    (void)previous_instance;
    (void)command_line;
    (void)show_command;

    return 0;
}

/* Function start: 0x40215C */
int __cdecl IsLevelIndexInRange(int index)
{
    int x;
    int y;

    x = g_levelXs_00414df8[index * 10];
    y = g_levelYs_00414dfc[index * 10];

    if (x < g_bitmapWidth_004149d4 * 20 || y < g_bitmapHeight_004149d8 * 20) {
        return 0;
    }

    if (x >= (g_maxLevelWidth_0041e7c4 + g_bitmapWidth_004149d4) * 20) {
        return 0;
    }

    if (y >= (g_maxLevelHeight_0041496c + g_bitmapHeight_004149d8) * 20) {
        return 0;
    }

    return 1;
}

/* Function start: 0x402205 */
void ShowLevelComplete(void)
{
    HDC hDC;
    HBRUSH hBrush;
    RECT rcClient;
    RECT rcRect;
    char szBuffer[64];
    int iTextLen;
    int iBonusPoints;
    int i;

    SetCursor(*(HCURSOR *)0x0041ec4c);
    *(int *)0x0041ec24 = 1;

    hDC = GetDC(g_mainWindow_00414978);
    GetClientRect(g_mainWindow_00414978, &rcClient);

    rcRect.left = (rcClient.right - 0xb2) / 2 - 0x49;
    rcRect.top = (rcClient.bottom - 0x2e) / 2 - 0x21;
    rcRect.right = (rcClient.right - 0xb2) / 2 + 0x7f;
    rcRect.bottom = (rcClient.bottom - 0x2e) / 2 + 0x57;

    hBrush = GetStockObject(WHITE_BRUSH);
    FillRect(hDC, &rcRect, hBrush);

    rcRect.left = (rcClient.right - 0xb2) / 2 - 0x4d;
    rcRect.top = (rcClient.bottom - 0x2e) / 2 - 0x25;
    rcRect.right = (rcClient.right - 0xb2) / 2 + 0x7b;
    rcRect.bottom = (rcClient.bottom - 0x2e) / 2 + 0x53;

    hBrush = GetStockObject(BLACK_BRUSH);
    FillRect(hDC, &rcRect, hBrush);

    if (g_soundEnabled_00415624 == 1 && g_musicEnabled_004149e0 == 1) {
        sndPlaySoundA("WELLDONE.WAV", SND_FILENAME | SND_ASYNC);
    }

    SetTextAlign(hDC, TA_CENTER | TA_TOP);

    iTextLen = wsprintfA(szBuffer, "Well Done!");
    TextOutA(hDC, (rcClient.right - 0xb2) / 2 + 0x17, (rcClient.bottom - 0x2e) / 2 - 0x11, szBuffer, iTextLen);

    iTextLen = wsprintfA(szBuffer, "That took %d seconds", *(int *)0x00415630);
    TextOutA(hDC, (rcClient.right - 0xb2) / 2 + 0x17, (rcClient.bottom - 0x2e) / 2 + 0xd, szBuffer, iTextLen);

    iBonusPoints = ((g_currentScoreValue_0041e86c * 5 + 100) - *(int *)0x00415630) * 10;

    if (iBonusPoints < 1) {
        iTextLen = wsprintfA(szBuffer, "No bonus...");
        TextOutA(hDC, (rcClient.right - 0xb2) / 2 + 0x17, (rcClient.bottom - 0x2e) / 2 + 0x2b, szBuffer, iTextLen);
    }
    else {
        for (i = 1; i <= iBonusPoints; i++) {
            iTextLen = wsprintfA(szBuffer, "%d bonus points", i * *(int *)0x004155e0);
            TextOutA(hDC, (rcClient.right - 0xb2) / 2 + 0x17, (rcClient.bottom - 0x2e) / 2 + 0x2b, szBuffer, iTextLen);
            g_score_0041560c += *(int *)0x004155e0;
            DrawScore();
        }
    }

    ReleaseDC(g_mainWindow_00414978, hDC);
    g_currentScoreValue_0041e86c++;
    InitializeGameLevel();
    (*(void (*)(void))0x00403840)();
    *(int *)0x0041ec24 = 0;
    (*(void (*)(void))0x00404764)();
    *(int *)0x00415630 = 0;
}

/* Function start: 0x40250C */
void CheckHighScore(void)
{
  int local_8;

  LoadHighScores();
  if (((*(int *)0x004167a4) <= g_score_0041560c) &&
     (((*(int *)0x004167a2) <= g_currentScoreValue_0041e86c || ((*(int *)0x004167a4) != g_score_0041560c)))) {
    (*(int *)0x00416688) = 9;
    while ((0 < (*(int *)0x00416688) &&
           ((*(int *)((char *)0x004166a8 + ((*(int *)0x00416688) + -1) * 0x1c) < g_score_0041560c ||
            ((*(short *)((char *)0x004166a6 + ((*(int *)0x00416688) + -1) * 0x1c) < g_currentScoreValue_0041e86c &&
             (*(int *)((char *)0x004166a8 + ((*(int *)0x00416688) + -1) * 0x1c) == g_score_0041560c))))))) {
      (*(int *)0x00416688) = (*(int *)0x00416688) + -1;
    }
    if ((*(int *)0x00416688) < 9) {
      for (local_8 = 9; (*(int *)0x00416688) < local_8; local_8 = local_8 + -1) {
        *(unsigned int *)((char *)0x004166a8 + local_8 * 0x1c) =
             *(unsigned int *)((char *)0x004166a8 + (local_8 + -1) * 0x1c);
        *(unsigned short *)((char *)0x004166a6 + local_8 * 0x1c) =
             *(unsigned short *)((char *)0x004166a6 + (local_8 + -1) * 0x1c);
        strcpy((char *)&g_highScores_00416690 + local_8 * 0x1c,(char *)&g_highScores_00416690 + (local_8 + -1) * 0x1c);
      }
    }
    if ((g_soundEnabled_00415624 == 1) && (g_musicEnabled_004149e0 == 1)) {
      sndPlaySoundA("VICTORY.WAV",1);
    }
    DialogBoxParamA((*(int *)0x00414980),"DLG_NAME",g_mainWindow_00414978,HighScoreDialogProc,0);
    SaveHighScores();
  }
  return;
}

/* Function start: 0x4026D0 */
void RenderScoreboard(void)
{
    HDC hdc;
    HDC hdcMem;
    RECT rcClient;
    RECT rcFill;
    HBITMAP hBmp[4];
    HBITMAP hBmpVerminators;
    int i;
    int j;
    int k;
    int dwMapMode;
    int cchText;
    char szBuffer[32];

    SetCursor((HCURSOR)g_cursor_0041ec4c);
    UpdateMainMenuState();

    hBmp[0] = LoadBitmapA(g_hInstance_004149b8, "BMP_START_1");
    hBmp[1] = LoadBitmapA(g_hInstance_004149b8, "BMP_START_2_SHADED");
    hBmp[2] = LoadBitmapA(g_hInstance_004149b8, "BMP_START_3_SHADED");
    hBmp[3] = LoadBitmapA(g_hInstance_004149b8, "BMP_START_4_SHADED");
    hBmpVerminators = LoadBitmapA(g_hInstance_004149b8, "BMP_VERMINATORS");

    hdc = GetDC(g_mainWindow_00414978);
    GetClientRect(g_mainWindow_00414978, &rcClient);
    hdcMem = CreateCompatibleDC(hdc);
    dwMapMode = GetMapMode(hdc);
    SetMapMode(hdcMem, dwMapMode);

    rcFill.left = 0x17;
    rcFill.top = 0x17;
    rcFill.right = rcClient.right - 0x9b;
    rcFill.bottom = rcClient.bottom - 0x17;

    FillRect(hdc, &rcFill, (HBRUSH)GetStockObject(4));
    SetBkMode(hdc, 1);
    SetTextColor(hdc, 0xffff00);

    for (i = 0; i < 10; i++) {
        if (g_highScores_00416690[i].score > 0) {
            short sLevel;
            int y;

            sLevel = g_highScores_00416690[i].level;

            if (sLevel < 8) {
                SetTextColor(hdc, 0xff00);
            } else if (sLevel < 0x10) {
                SetTextColor(hdc, 0xffff);
            } else if (sLevel < 0x18) {
                SetTextColor(hdc, 0xc4c4c4);
            } else {
                SetTextColor(hdc, 0xff);
            }

            y = ((rcClient.bottom - 0xa6) * i) / 10 + 0x50;
            SetTextAlign(hdc, 2);

            cchText = wsprintfA(szBuffer, "%d", i + 1);
            TextOutA(hdc, (rcClient.right - 0xb2) / 2 - 0x7f, y, szBuffer, cchText);

            cchText = wsprintfA(szBuffer, "Lv.%d", sLevel + 1);
            TextOutA(hdc, (rcClient.right - 0xb2) / 2 + 0x6c, y, szBuffer, cchText);

            cchText = wsprintfA(szBuffer, "%dHP", g_highScores_00416690[i].score);
            TextOutA(hdc, (rcClient.right - 0xb2) / 2 + 0xad, y, szBuffer, cchText);

            SetTextAlign(hdc, 0);
            cchText = wsprintfA(szBuffer, g_highScores_00416690[i].name);
            TextOutA(hdc, (rcClient.right - 0xb2) / 2 - 0x61, y, szBuffer, cchText);
        }
    }

    for (i = 0; i < 4; i++) {
        SelectObject(hdcMem, hBmp[i]);
        BitBlt(hdc, (rcClient.right - 0x84) / 2 + i * 0x40 - 0x74, rcClient.bottom - 0x49, 0x28, 0x28, hdcMem, 0, 0, 0xcc0020);
    }

    SelectObject(hdcMem, hBmpVerminators);
    BitBlt(hdc, (rcClient.right - 0x84) / 2 - 0x62, 0x21, 0xc4, 0x18, hdcMem, 0, 0, 0xcc0020);

    ReleaseDC(g_mainWindow_00414978, hdc);
    DeleteDC(hdcMem);

    for (i = 0; i < 4; i++) {
        DeleteObject(hBmp[i]);
    }
    DeleteObject(hBmpVerminators);

    for (i = 0; i < 0x28; i++) {
        g_levelData_0041e8a0[i * 0x14] = 999;
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 7; j++) {
            DrawFrameBorder(i, j);
        }
    }

    g_flag_0041e888 = 1;
    InitializeGameLevel();

    DrawBitmapPair(g_memBitmap_00414940, g_bitmap_00415620, 0, 0, 0x280, 0x280);
    DrawBitmapPair(g_memBitmap_0041495c, g_bitmap_00415620, 0, 0, 0x280, 0x280);

    g_score_0041560c = 0;
}

/* Function start: 0x402BF3 */
void __cdecl AddLevelToTable(int index, int x, int y)
{
    int i;

    for (i = 0; g_levelIndices_0041e7d0[i] != 999 && i < 10; i++) {
    }

    if (i < 10) {
        g_levelXs_0041e7c8[i] = x;
        g_levelYs_0041e7cc[i] = y;

        switch (index - 5) {
            case 0:
                g_levelIndices_0041e7d0[i] = 0;
                break;
            case 1:
                g_levelIndices_0041e7d0[i] = 1;
                break;
            case 2:
                g_levelIndices_0041e7d0[i] = 2;
                break;
            case 3:
                g_levelIndices_0041e7d0[i] = 3;
                break;
            case 4:
                g_levelIndices_0041e7d0[i] = 4;
                break;
            case 5:
                g_levelIndices_0041e7d0[i] = 5;
                break;
        }
    }
}

/* Function start: 0x402DC6 */
void UpdateGameDisplay(void)
{
    switch (g_displayState_0041ec1c) {
        case 0:
            if (g_bitmapWidth_004149d4 < 1) {
                g_displayState_0041ec1c = 10;
                RenderScoreOverlay();
            } else {
                g_bitmapWidth_004149d4--;
                DrawBitmapToWindow();
            }
            break;
        case 1:
            if (g_bitmapHeight_004149d8 < 0x20 - g_levelXs_0041e7c8[0]) {
                g_bitmapHeight_004149d8++;
                DrawBitmapToWindow();
            } else {
                g_displayState_0041ec1c = 10;
                RenderScoreOverlay();
            }
            break;
        case 2:
            if (g_bitmapWidth_004149d4 < 0x20 - g_levelYs_0041e7cc[0]) {
                g_bitmapWidth_004149d4++;
                DrawBitmapToWindow();
            } else {
                g_displayState_0041ec1c = 10;
                RenderScoreOverlay();
            }
            break;
        case 3:
            if (g_bitmapHeight_004149d8 < 1) {
                g_displayState_0041ec1c = 10;
                RenderScoreOverlay();
            } else {
                g_bitmapHeight_004149d8--;
                DrawBitmapToWindow();
            }
            break;
    }
}

/* Function start: 0x402EE7 */
int __cdecl GetLevelDisplayInfo(int index)
{
    int type;
    int size_class;
    int style;

    type = g_levelTypes_00414e00[index];
    if (type == 0) {
        size_class = 2;
    } else if (type == 2) {
        size_class = 3;
    } else if (type == 3) {
        size_class = 0;
    } else {
        size_class = 1;
    }

    if (g_levelSizes_00414e04[index] < 300) {
        style = 2;
    } else if (g_levelIndices_00414e08[index] == 0) {
        style = 0;
    } else if (g_levelIndices_00414e08[index] == 1) {
        style = 1;
    }

    return g_displayTable_0041ebd8[size_class * 4 + style];
}

/* Function start: 0x403430 */
int __cdecl IsBombAtLevel(int level_index, int direction)
{
  int local_10;
  int local_c;
  int local_8;

  if (direction == 0) {
    local_8 = *(int *)((char *)&g_levelXs_00414df8 + level_index * 0x28) / 0x14 + -1;
    local_c = *(int *)((char *)&g_levelYs_00414dfc + level_index * 0x28) / 0x14;
  }
  else if (direction == 2) {
    local_8 = *(int *)((char *)&g_levelXs_00414df8 + level_index * 0x28) / 0x14 + 1;
    local_c = *(int *)((char *)&g_levelYs_00414dfc + level_index * 0x28) / 0x14;
  }
  else if (direction == 1) {
    local_8 = *(int *)((char *)&g_levelXs_00414df8 + level_index * 0x28) / 0x14;
    local_c = *(int *)((char *)&g_levelYs_00414dfc + level_index * 0x28) / 0x14 + 1;
  }
  else {
    local_8 = *(int *)((char *)&g_levelXs_00414df8 + level_index * 0x28) / 0x14;
    local_c = *(int *)((char *)&g_levelYs_00414dfc + level_index * 0x28) / 0x14 + -1;
  }
  local_10 = 0;
  while( 1 ) {
    if (0x27 < local_10) {
      return ((char *)&g_levelMap_004149e8)[local_8 + local_c * 0x20] != '\x01';
    }
    if (((*(int *)((char *)&g_levelData_0041e8a0 + local_10 * 0x14) == 6) &&
        (*(int *)((char *)&g_bombData_0041e898 + local_10 * 0x14) / 0x14 == local_8)) &&
       (*(int *)((char *)0x0041e89c + local_10 * 0x14) / 0x14 == local_c)) break;
    local_10 = local_10 + 1;
  }
  *(int *)((char *)0x0041e8a4 + local_10 * 0x14) = *(int *)((char *)0x0041e8a4 + local_10 * 0x14) + -1;
  if (*(int *)((char *)0x0041e8a4 + local_10 * 0x14) == 0) {
    *(unsigned int *)((char *)&g_levelData_0041e8a0 + local_10 * 0x14) = 999;
  }
  return 0;
}

/* Function start: 0x403607 */
void __cdecl PlaceLevel(int source_index)
{
    int i;
    int src_type;

    for (i = 0; g_levelScores_00414e0c[i] > 0 && i < 50; i++)
        ;

    if (i < 50) {
        g_levelXs_00414df8[i] = (g_levelXs_00414df8[source_index] - 10) / 4;
        g_levelXs_00414df8[i] = g_levelXs_00414df8[i] * 4 + 10;

        g_levelYs_00414dfc[i] = (g_levelYs_00414dfc[source_index] - 10) / 4;
        g_levelYs_00414dfc[i] = g_levelYs_00414dfc[i] * 4 + 10;

        if (IsLevelIndexInRange(i)) {
            if (g_soundEnabled_00415624 == 1 && g_musicEnabled_004149e0 == 1) {
                sndPlaySoundA("BIRTH.WAV", 1);
            }
        }

        g_levelScores_00414e0c[i] = 20;
        g_levelFlags_00414e1c[i] = 0;
        g_levelFlags_00414e18[i] = 20;

        if (g_scoreCounts_00414948[0] < g_baseScore_0041494c) {
            g_levelIndices_00414e08[i] = 1;
        } else {
            g_levelIndices_00414e08[i] = 0;
        }

        g_levelSizes_00414e04[i] = 0;
        g_levelFlags_00414e10[i] = 0;

        src_type = g_levelTypes_00414e00[source_index];
        switch (src_type) {
            case 0:
                g_levelTypes_00414e00[i] = 2;
                break;
            case 1:
                g_levelTypes_00414e00[i] = 3;
                break;
            case 2:
                g_levelTypes_00414e00[i] = 0;
                break;
            case 3:
                g_levelTypes_00414e00[i] = 1;
                break;
        }

        DrawScorePanel();
    }
}

/* Function start: 0x404764 */
void __cdecl DrawLevelIndicator(void)
{
  HGDIOBJ pvVar1;
  CHAR local_34 [20];
  HDC local_20;
  int local_1c;
  int local_18;
  RECT local_14;

  GetClientRect(g_mainWindow_00414978,&local_14);
  local_20 = GetDC(g_mainWindow_00414978);
  for (local_1c = 0; local_1c < 4; local_1c = local_1c + 1) {
    RenderCornerGlyph(local_20,local_1c,0);
  }
  SetTextAlign(local_20,6);
  SetTextColor(local_20,0xffffff);
  SetBkColor(local_20,0x808080);
  local_18 = wsprintfA(local_34,"  Level %d  ",g_currentScoreValue_0041e86c + 1);
  TextOutA(local_20,local_14.right + -0x42,local_14.top + 6,local_34,local_18);
  pvVar1 = GetStockObject(6);
  SelectObject(local_20,pvVar1);
  MoveToEx(local_20,local_14.right + -0x81,local_14.bottom + -4,(LPPOINT)0x0);
  LineTo(local_20,local_14.right + -0x81,3);
  LineTo(local_20,local_14.right + -4,3);
  pvVar1 = GetStockObject(7);
  SelectObject(local_20,pvVar1);
  LineTo(local_20,local_14.right + -4,local_14.bottom + -4);
  LineTo(local_20,local_14.right + -0x81,local_14.bottom + -4);
  ReleaseDC(g_mainWindow_00414978,local_20);
  DrawScorePanel();
  DrawScoreDigits();
  DrawScore();
  if (g_flag_0041e888 == 0) {
    DrawBitmapToWindow();
    if ((*(int *)0x0041ec24) == 1) {
      DrawPausedOverlay();
    }
  }
  else {
    RenderScoreboard();
  }
  local_20 = GetDC(g_mainWindow_00414978);
  SetTextAlign(local_20,6);
  SetTextColor(local_20,0xffffff);
  SetBkColor(local_20,0x808080);
  local_18 = wsprintfA(local_34,"  Level %d  ",g_currentScoreValue_0041e86c + 1);
  TextOutA(local_20,local_14.right + -0x42,local_14.top + 6,local_34,local_18);
  ReleaseDC(g_mainWindow_00414978,local_20);
  RenderScoreOverlay();
  return;
}

/* Function start: 0x40499F */
void __cdecl RenderCornerGlyph(HDC hdc, int panel_index, int is_active)
{
  HGDIOBJ pvVar1;
  int bVar2;
  unsigned int local_1c;
  unsigned int local_18;
  RECT local_14;

  pvVar1 = GetStockObject(1);
  SelectObject(hdc,pvVar1);
  bVar2 = is_active != 1;
  if (bVar2) {
    pvVar1 = GetStockObject(7);
    SelectObject(hdc,pvVar1);
  }
  else {
    SelectObject(hdc,g_fontSmall_0041ec18);
  }
  local_18 = (unsigned int)!bVar2;
  local_1c = (unsigned int)!bVar2;
  GetClientRect(g_mainWindow_00414978,&local_14);
  switch(panel_index) {
  case 0:
    Rectangle(hdc,0,0x17,0x17,local_14.bottom + -0x17);
    RenderBitmapToWindow((*(int *)0x00414990),local_18 + 2,local_1c + (local_14.bottom + -0x28) / 2 + 0xc,0x10,0x10)
    ;
    if (is_active == 0) {
      pvVar1 = GetStockObject(6);
      SelectObject(hdc,pvVar1);
    }
    else {
      pvVar1 = GetStockObject(7);
      SelectObject(hdc,pvVar1);
    }
    MoveToEx(hdc,0,local_14.bottom + -0x18,(LPPOINT)0x0);
    LineTo(hdc,0,0x17);
    LineTo(hdc,0x16,0x17);
    break;
  case 1:
    Rectangle(hdc,0x17,local_14.bottom + -0x17,local_14.right + -0x9b,local_14.bottom);
    RenderBitmapToWindow((*(int *)0x0041498c),local_18 + (local_14.right + -0xac) / 2 + 0xc,
                 local_1c + local_14.bottom + -0x15,0x10,0x10);
    if (is_active == 0) {
      pvVar1 = GetStockObject(6);
      SelectObject(hdc,pvVar1);
    }
    else {
      pvVar1 = GetStockObject(7);
      SelectObject(hdc,pvVar1);
    }
    MoveToEx(hdc,0x17,local_14.bottom + -1,(LPPOINT)0x0);
    LineTo(hdc,0x17,local_14.bottom + -0x17);
    LineTo(hdc,local_14.right + -0x9c,local_14.bottom + -0x17);
    break;
  case 2:
    Rectangle(hdc,local_14.right + -0x9b,0x17,local_14.right + -0x84,local_14.bottom + -0x17);
    RenderBitmapToWindow((*(int *)0x00414994),local_18 + local_14.right + -0x99,
                 local_1c + (local_14.bottom + -0x28) / 2 + 0xc,0x10,0x10);
    if (is_active == 0) {
      pvVar1 = GetStockObject(6);
      SelectObject(hdc,pvVar1);
    }
    else {
      pvVar1 = GetStockObject(7);
      SelectObject(hdc,pvVar1);
    }
    MoveToEx(hdc,local_14.right + -0x9b,local_14.bottom + -0x18,(LPPOINT)0x0);
    LineTo(hdc,local_14.right + -0x9b,0x17);
    LineTo(hdc,local_14.right + -0x84,0x17);
    break;
  case 3:
    Rectangle(hdc,0x17,0,local_14.right + -0x9b,0x17);
    RenderBitmapToWindow((*(int *)0x00414988),local_18 + (local_14.right + -0xac) / 2 + 0xc,local_1c + 2,0x10,0x10);
    if (is_active == 0) {
      pvVar1 = GetStockObject(6);
      SelectObject(hdc,pvVar1);
    }
    else {
      pvVar1 = GetStockObject(7);
      SelectObject(hdc,pvVar1);
    }
    MoveToEx(hdc,0x17,0x16,(LPPOINT)0x0);
    LineTo(hdc,0x17,0);
    LineTo(hdc,local_14.right + -0x9b,0);
  }
  return;
}
