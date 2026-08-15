#include "rats.h"

/* Function start: 0x404D6E */
void __cdecl DrawBitmapPair(HGDIOBJ hObj1, HGDIOBJ hObj2, int x, int y, int cx, int cy)
{
  HDC hdc;
  HDC hdc_00;
  HDC hdc_01;

  hdc = GetDC(g_mainWindow_00414978);
  hdc_00 = CreateCompatibleDC(hdc);
  SelectObject(hdc_00, hObj1);
  SetMapMode(hdc_00, GetMapMode(hdc));
  hdc_01 = CreateCompatibleDC(hdc_00);
  SelectObject(hdc_01, hObj2);
  SetMapMode(hdc_01, GetMapMode(hdc_00));
  BitBlt(hdc_00, x, y, cx, cy, hdc_01, 0, 0, 0xcc0020);
  DeleteDC(hdc_01);
  DeleteDC(hdc_00);
  ReleaseDC(g_mainWindow_00414978, hdc);
}

/* Function start: 0x404E3B */
void __cdecl RenderBitmapToWindow(HGDIOBJ hObject, int x, int y, int cx, int cy)
{
    HDC hdc;
    HDC memDC;
    int iMode;

    hdc = GetDC(g_mainWindow_00414978);
    memDC = CreateCompatibleDC(hdc);
    SelectObject(memDC, hObject);
    iMode = GetMapMode(hdc);
    SetMapMode(memDC, iMode);
    BitBlt(hdc, x, y, cx, cy, memDC, 0, 0, SRCCOPY);
    DeleteDC(memDC);
    ReleaseDC(g_mainWindow_00414978, hdc);
}

/* Function start: 0x404ECE */
void DrawBitmapToWindow(void)
{
    RECT rc;
    HDC hdc;
    HDC hdcMem;
    int iMode;

    GetClientRect(g_mainWindow_00414978, &rc);
    hdc = GetDC(g_mainWindow_00414978);
    hdcMem = CreateCompatibleDC(hdc);
    SelectObject(hdcMem, g_memBitmap_00414940);
    iMode = GetMapMode(hdc);
    SetMapMode(hdcMem, iMode);
    BitBlt(hdc, 0x17, 0x17, rc.right - 0xb2, rc.bottom - 0x2e, hdcMem, g_bitmapWidth_004149d4 * 0x14, g_bitmapHeight_004149d8 * 0x14, SRCCOPY);
    DeleteDC(hdcMem);
    ReleaseDC(g_mainWindow_00414978, hdc);
}

/* Function start: 0x404F8B */
void DrawScore(void)
{
    HDC hdc;
    RECT rcClient;
    RECT rcRect;
    char buf[20];
    HBRUSH hbr;
    int len;

    if (g_score_0041560c < 0) {
        g_score_0041560c = 0;
    }

    hdc = GetDC(g_mainWindow_00414978);
    GetClientRect(g_mainWindow_00414978, &rcClient);
    SetTextAlign(hdc, TA_CENTER);

    rcRect.left = rcClient.right - 0x80;
    rcRect.top = 0x1c;
    rcRect.right = rcClient.right - 4;
    rcRect.bottom = 0x3b;

    hbr = GetStockObject(WHITE_BRUSH);
    FillRect(hdc, &rcRect, hbr);

    SetTextColor(hdc, RGB(255, 255, 255));
    SetBkMode(hdc, TRANSPARENT);

    len = wsprintfA(buf, "  %ld  ", g_score_0041560c);
    TextOutA(hdc, rcClient.right - 0x42, rcClient.top + 0x1c, buf, len);

    ReleaseDC(g_mainWindow_00414978, hdc);
}

/* Function start: 0x40507F */
void DrawScorePanel(void)
{
    HDC hdc;
    RECT rect;
    int i;

    for (i = 0; i < 2; i++) {
        g_scoreCounts_00414948[i] = 0;
    }

    for (i = 0; i < 50; i++) {
        if (g_levelScores_00414e0c[i] > 0) {
            g_scoreCounts_00414948[g_levelIndices_00414e08[i]]++;
        }
    }

    g_totalScore_00414954 = g_baseScore_0041494c + g_scoreCounts_00414948[0];

    GetClientRect(g_mainWindow_00414978, &rect);
    hdc = GetDC(g_mainWindow_00414978);
    SelectObject(hdc, g_fontSmall_0041ec18);
    SelectObject(hdc, g_fontMedium_00415618);
    Rectangle(hdc, rect.right - 30, 168, rect.right - 10, 400 - (g_totalScore_00414954 * 232) / 50);
    SelectObject(hdc, g_fontLarge_0041ebc0);
    Rectangle(hdc, rect.right - 30, 400 - (g_totalScore_00414954 * 232) / 50, rect.right - 10, 400 - (g_scoreCounts_00414948[0] * 232) / 50);
    SelectObject(hdc, g_fontTitle_00415604);
    Rectangle(hdc, rect.right - 30, 400 - (g_scoreCounts_00414948[0] * 232) / 50, rect.right - 10, 400);
    ReleaseDC(g_mainWindow_00414978, hdc);
}

/* Function start: 0x40525D */
void __cdecl DrawScoreDigits(void)
{
    RECT rc;
    HDC hDC;
    int i;
    int j;

    GetClientRect(g_mainWindow_00414978, &rc);
    hDC = GetDC(g_mainWindow_00414978);

    for (i = 0; i < 7; i++) {
        if (g_scoreCounts_004155e8[i] > 0) {
            for (j = 0; j < g_scoreCounts_004155e8[i]; j++) {
                RenderBitmapToWindow(
                    g_scoreObjects_00415638[i],
                    rc.right + j * 22 - 124,
                    (i * 232) / 7 + 170,
                    20, 20
                );
            }
        }
    }

    ReleaseDC(g_mainWindow_00414978, hDC);
}

/* Function start: 0x405343 */
void __cdecl RenderScoreOverlay(void)
{
    RECT rect;
    HDC hdc;
    HGDIOBJ hObj;

    GetClientRect(g_mainWindow_00414978, &rect);
    RenderBitmapToWindow((HGDIOBJ)0x0041665c, rect.right - 0x72, 0x3c, 0x60, 0x60);

    if (g_scorePanelActive == 0) {
        hdc = GetDC(g_mainWindow_00414978);

        if (abs(g_currentScoreValue) < 0x10 || abs(g_currentScoreValue) > 0x18) {
            SelectObject(hdc, g_scorePanelDefaultBitmap);
        } else {
            SelectObject(hdc, g_scorePanelActiveBitmap);
        }

        hObj = GetStockObject(5);
        SelectObject(hdc, hObj);

        Rectangle(hdc,
                  rect.right + g_bitmapWidth_004149d4 * 3 - 0x71,
                  g_bitmapHeight_004149d8 * 3 + 0x3d,
                  (g_scorePanelYOffset + g_bitmapWidth_004149d4) * 3 + rect.right - 0x72,
                  (g_scorePanelXOffset + g_bitmapHeight_004149d8) * 3 + 0x3c);

        ReleaseDC(g_mainWindow_00414978, hdc);
    }
}

/* Function start: 0x40546B */
void __cdecl DrawFrameBorder(int offset_x, int offset_y)
{
    RECT rc;
    int x;
    int y;
    HDC hdc;
    HGDIOBJ hObj1;
    HGDIOBJ hObj2;

    GetClientRect(g_mainWindow_00414978, &rc);
    x = rc.right + offset_x * 0x16;
    y = (offset_y * 0xe8) / 7;
    hdc = GetDC(g_mainWindow_00414978);
    hObj1 = GetStockObject(8);
    SelectObject(hdc, hObj1);
    hObj2 = GetStockObject(2);
    SelectObject(hdc, hObj2);
    Rectangle(hdc, x - 0x7c, y + 0xaa, x - 0x67, y + 0xbf);
    ReleaseDC(g_mainWindow_00414978, hdc);
}

/* Function start: 0x40552E */
void __cdecl ExplodeBomb(int index)
{
    int x;
    int y;

    x = g_bombData_0041e898[index].x / 20;
    y = g_bombData_0041e898[index].y / 20;

    g_bombActive_0041668c = 0;

    DrawBitmapPair(g_memBitmap_00414940, g_bombFrame1_0041ebbc, x * 20, y * 20, 20, 20);
    DrawBitmapPair(g_memBitmap_00414940, g_bombFrame2_00416680, x * 20, y * 20, 20, 20);
    DrawBitmapPair(g_memBitmap_00414940, g_bombFrame3_00416684, x * 20, y * 20, 20, 20);
    DrawBitmapPair(g_memBitmap_00414940, g_bombFrame4_00416688, x * 20, y * 20, 20, 20);

    DrawBitmapToWindow();

    if (g_soundEnabled_00415624 == 1) {
        if (g_musicEnabled_004149e0 == 1) {
            PlaySoundA("BOMB.WAV", NULL, SND_FILENAME | SND_ASYNC);
        } else {
            MessageBeep(MB_ICONEXCLAMATION);
        }
    }

    DrawScore();
    DrawScorePanel();
}

/* Function start: 0x40560E */
void __cdecl RenderExplosionWave(int x, int y, int step_x, int step_y)
{
    int i;

    for (; g_levelData_004167c0[x + y * 0x20] != '\x01'; x = x + step_x) {
        if (g_levelData_004167c0[x + y * 0x20] == '\0') {
            DrawBitmapPair(g_memBitmap_00414940, g_bombFrame1_0041ebbc, x * 0x14, y * 0x14, 0x14, 0x14);
        }
        else if (g_levelData_004167c0[x + y * 0x20] == '\x02') {
            DrawBitmapPair(g_memBitmap_00414940, g_bombFrame2_00416680, x * 0x14, y * 0x14, 0x14, 0x14);
        }
        else if (g_levelData_004167c0[x + y * 0x20] == '\x03') {
            DrawBitmapPair(g_memBitmap_00414940, g_bombFrame3_00416684, x * 0x14, y * 0x14, 0x14, 0x14);
        }
        else if (g_levelData_004167c0[x + (y - 1) * 0x20] == '\0') {
            DrawBitmapPair(g_memBitmap_00414940, g_bombFrame4_00416688, x * 0x14, y * 0x14, 0x14, 0x14);
        }
        else if (g_levelData_004167c0[x + (y + 1) * 0x20] == '\0') {
            DrawBitmapPair(g_memBitmap_00414940, g_bombFrame5_0041668c, x * 0x14, y * 0x14, 0x14, 0x14);
        }

        for (i = 0; i < 0x32; i = i + 1) {
            if ((g_levelScores_00414e0c[i] > 0) &&
                (g_bombData_0041e898[i].x / 0x14 == x) &&
                (g_bombData_0041e898[i].y / 0x14 == y)) {
                g_levelScores_00414e0c[i] = 0;

                if (g_bombActive_0041668c == 0) {
                    g_bombActive_0041668c = 10;
                }
                else if (g_bombActive_0041668c < 0xa0) {
                    g_bombActive_0041668c = g_bombActive_0041668c << 1;
                }

                g_score_0041560c = g_score_0041560c + g_bombActive_0041668c * g_baseScore_0041494c;
                DrawBitmapPair(g_memBitmap_00414940, g_bombFrame5_0041668c, g_bombData_0041e898[i].x, g_bombData_0041e898[i].y, 0x14, 0x14);
            }
        }

        for (i = 0; i < 0x28; i = i + 1) {
            if ((g_bombData_0041e898[i].x / 0x14 == x) &&
                (g_bombData_0041e898[i].y / 0x14 == y)) {
                g_bombData_0041e898[i].x = 999;
            }
        }

        y = y + step_y;
    }
}

/* Function start: 0x40591A */
void __cdecl DrawBombExplosion(int index)
{
    int radius;
    HDC hdc;
    HDC memDC;
    HGDIOBJ oldBitmap;
    int mapMode;
    int i;

    radius = g_bombData_0041e898[index].x * 8 + 0x1e;
    hdc = GetDC(g_mainWindow_00414978);
    memDC = CreateCompatibleDC(hdc);
    oldBitmap = SelectObject(memDC, g_memBitmap_00414940);
    mapMode = GetMapMode(hdc);
    SetMapMode(memDC, mapMode);
    SelectObject(memDC, g_fontLarge_0041ebc0);
    Ellipse(memDC,
            g_bombData_0041e898[index].x + 10 - radius,
            g_bombData_0041e898[index].y + 10 - radius,
            g_bombData_0041e898[index].x + 10 + radius,
            g_bombData_0041e898[index].y + 10 + radius);
    DeleteDC(memDC);
    ReleaseDC(g_mainWindow_00414978, hdc);
    DrawBitmapToWindow();

    if (g_soundEnabled_00415624 == 1) {
        if (g_musicEnabled_004149e0 == 1) {
            sndPlaySoundA("NUCLEAR.WAV", SND_ASYNC);
        }
        else {
            MessageBeep(MB_ICONASTERISK);
        }
    }

    for (i = 0; i < 50; i++) {
        int dx;
        int dy;

        dx = g_bombData_0041e898[index].x + 10 - g_levelIndices_00414e08[i];
        dy = g_bombData_0041e898[index].y + 10 - g_levelScores_00414e0c[i];

        if ((-radius < dx && dx < radius) && (-radius < dy && dy < radius)) {
            g_levelIndices_00414e08[i] = 1;
            g_levelScores_00414e0c[i] = 0;
        }
    }

    return;
}

/* Function start: 0x405AF5 */
void DrawPausedOverlay(void)
{
    HDC hDC;
    HBRUSH brush;
    RECT fillRect;
    char buffer[20];
    int textLen;
    RECT clientRect;

    hDC = GetDC(g_mainWindow_00414978);
    GetClientRect(g_mainWindow_00414978, &clientRect);

    fillRect.left = (clientRect.right - 178) / 2 - 73;
    fillRect.top = (clientRect.bottom - 46) / 2 - 33;
    fillRect.right = (clientRect.right - 178) / 2 + 127;
    fillRect.bottom = (clientRect.bottom - 46) / 2 + 87;

    brush = GetStockObject(4);
    FillRect(hDC, &fillRect, brush);

    fillRect.left = (clientRect.right - 178) / 2 - 77;
    fillRect.top = (clientRect.bottom - 46) / 2 - 37;
    fillRect.right = (clientRect.right - 178) / 2 + 123;
    fillRect.bottom = (clientRect.bottom - 46) / 2 + 83;

    brush = GetStockObject(0);
    FillRect(hDC, &fillRect, brush);

    SetTextAlign(hDC, 6);

    textLen = wsprintfA(buffer, "Paused");
    TextOutA(hDC, (clientRect.right - 178) / 2 + 23, (clientRect.bottom - 46) / 2 + 13, buffer, textLen);

    ReleaseDC(g_mainWindow_00414978, hDC);
}

/* Function start: 0x405DB8 */
int CALLBACK ScorePanelDialogProc(HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{
    RECT rcRef;
    RECT rcWin;
    HDC hdc;
    HDC hdcMem;
    int mapMode;

    if (message == 0xf) {
        hdc = GetDC(hWnd);
        GetClientRect(hWnd, &rcWin);
        hdcMem = CreateCompatibleDC(hdc);
        mapMode = GetMapMode(hdc);
        SetMapMode(hdcMem, mapMode);
        SelectObject(hdcMem, g_scorePanelDefaultBitmap_004149dc);
        StretchBlt(hdc,
                   (rcWin.right - rcWin.left) / 2 - 0x20,
                   (int)lParam - 0x20,
                   0x40,
                   0x40,
                   hdcMem,
                   0,
                   0,
                   0x20,
                   0x20,
                   0xcc0020);
        DeleteDC(hdcMem);
        ReleaseDC(hWnd, hdc);
    }
    else {
        if (message == 0x110) {
            GetWindowRect(g_mainWindow_00414978, &rcRef);
            GetWindowRect(hWnd, &rcWin);
            MoveWindow(
                hWnd,
                (rcRef.left + (rcRef.right - rcRef.left) / 2) - ((rcWin.right - rcWin.left) / 2),
                (rcRef.top + (rcRef.bottom - rcRef.top) / 2) - ((rcWin.bottom - rcWin.top) / 2),
                rcWin.right - rcWin.left,
                rcWin.bottom - rcWin.top,
                1);
            return 1;
        }

        if (message == 0x111 && wParam == 1) {
            EndDialog(hWnd, 1);
            return 1;
        }
    }

    return 0;
}

/* Function start: 0x405F72 */

int CALLBACK DemoVersionDialogProc(HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    RECT parentRect;
    RECT childRect;
    char buffer[64];
    int len;
    double temp;

    if (message == WM_INITDIALOG) {
        hdc = GetDC(hWnd);
        GetClientRect(hWnd, &childRect);
        SetTextAlign(hdc, TA_CENTER | TA_TOP);
        SetTextColor(hdc, 0);
        SetBkMode(hdc, TRANSPARENT);

        len = wsprintfA(buffer, "You have completed the demo version.");
        temp = (double)childRect.right * 0.5;
        TextOutA(hdc, childRect.right / 2, (int)floor(temp), buffer, len);

        len = wsprintfA(buffer, "Click on the 'Order' button for");
        temp = (double)childRect.right * 1.0;
        TextOutA(hdc, childRect.right / 2, (int)floor(temp), buffer, len);

        len = wsprintfA(buffer, "details on buying the full version.");
        temp = (double)childRect.right * 1.5;
        TextOutA(hdc, childRect.right / 2, (int)floor(temp), buffer, len);

        ReleaseDC(hWnd, hdc);
    }
    else if (message == WM_MOVE) {
        GetWindowRect(g_mainWindow_00414978, &parentRect);
        GetWindowRect(hWnd, &childRect);
        MoveWindow(hWnd,
            (parentRect.left + (parentRect.right - parentRect.left) / 2) - (childRect.right - childRect.left) / 2,
            (parentRect.top + (parentRect.bottom - parentRect.top) / 2) - (childRect.bottom - childRect.top) / 2,
            childRect.right - childRect.left,
            childRect.bottom - childRect.top,
            TRUE);
        return 1;
    }
    else if (message == WM_COMMAND) {
        if (wParam == IDOK) {
            EndDialog(hWnd, 1);
            return 1;
        }
        if (wParam == 800) {
            WinHelpA(g_mainWindow_00414978, "rats.hlp", HELP_CONTEXT, 0x104);
            return 1;
        }
    }

    return 0;
}

/* Function start: 0x408854 */
void DrawStartButton(void)
{
    RECT rc;
    int iMode;
    HBITMAP hBitmap;
    HDC hdc;
    HDC hdcMem;

    GetClientRect(g_mainWindow_00414978, &rc);

    if (g_currentScoreValue == 0) {
        iMode = 0;
        hBitmap = LoadBitmapA(NULL, "BMP_START_1_DOWN");
    } else if (g_currentScoreValue == 8) {
        iMode = 1;
        hBitmap = LoadBitmapA(NULL, "BMP_START_2_DOWN");
    } else if (g_currentScoreValue == 0x10) {
        iMode = 2;
        hBitmap = LoadBitmapA(NULL, "BMP_START_3_DOWN");
    } else if (g_currentScoreValue == 0x18) {
        iMode = 3;
        hBitmap = LoadBitmapA(NULL, "BMP_START_4_DOWN");
    } else {
        return;
    }

    hdc = GetDC(g_mainWindow_00414978);
    hdcMem = CreateCompatibleDC(hdc);
    iMode = GetMapMode(hdc);
    SetMapMode(hdcMem, iMode);
    SelectObject(hdcMem, hBitmap);
    BitBlt(hdc,
           (rc.right - 0x84) / 2 + iMode * 0x40 - 0x74,
           rc.bottom - 0x49,
           0x28,
           0x28,
           hdcMem,
           0,
           0,
           SRCCOPY);
    DeleteDC(hdcMem);
    ReleaseDC(g_mainWindow_00414978, hdc);
    DeleteObject(hBitmap);
}
