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
