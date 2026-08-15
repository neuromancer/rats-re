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
