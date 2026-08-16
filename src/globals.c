#include "rats.h"

HWND g_mainWindow_00414978;
HMENU g_mainMenu_0041497c;
HighScore g_highScores_00416690[10];
char g_levelData_004167c0[0x8000];

HBITMAP g_memBitmap_00414940;
int g_bitmapWidth_004149d4;
int g_bitmapHeight_004149d8;

long g_score_0041560c;

int g_scoreCounts_00414948[2];
int g_baseScore_0041494c;
int g_totalScore_00414954;
int g_levelIndices_00414e08[50];
int g_levelScores_00414e0c[50];
HFONT g_fontSmall_0041ec18;
HFONT g_fontMedium_00415618;
HFONT g_fontLarge_0041ebc0;
HFONT g_fontTitle_00415604;

int g_scoreCounts_004155e8[7];
HGDIOBJ g_scoreObjects_00415638[7];

int g_scorePanelActive;
HGDIOBJ g_scorePanelDefaultBitmap;
HGDIOBJ g_scorePanelActiveBitmap;
int g_currentScoreValue;
int g_scorePanelXOffset;
int g_scorePanelYOffset;

BombData g_bombData_0041e898[20];
int g_bombActive_0041668c;
HGDIOBJ g_bombFrame1_0041ebbc;
HGDIOBJ g_bombFrame2_00416680;
HGDIOBJ g_bombFrame3_00416684;
HGDIOBJ g_bombFrame4_00416688;
int g_soundEnabled_00415624;
int g_musicEnabled_004149e0;

HGDIOBJ g_bombFrame5_0041668c;

HGDIOBJ g_scorePanelDefaultBitmap_004149dc;

int g_currentScoreValue_0041e86c;

int g_levelXs_0041e7c8[10];
int g_levelYs_0041e7cc[10];
int g_levelIndices_0041e7d0[10] = { 999, 999, 999, 999, 999, 999, 999, 999, 999, 999 };

int g_displayState_0041ec1c;

int g_levelTypes_00414e00[50];
int g_levelSizes_00414e04[50];
int g_displayTable_0041ebd8[16];

int g_levelXs_00414df8[50];
int g_levelYs_00414dfc[50];
int g_levelFlags_00414e18[50];
int g_levelFlags_00414e1c[50];
int g_levelFlags_00414e10[50];

char g_levelMap_004149e8[32][32];
int g_levelCount_00414df4;
int g_maxLevelWidth_0041e7c4;
int g_maxLevelHeight_0041496c;
int g_highScoreMax_0041e894;
int g_scoreValue_0041e868;
int g_levelOffset_004149bc;
int g_levelData_0041e8a0[0x28 * 0x14];

int g_levelTime_00415630;
int g_pointsPerBonus_004155e0;

HCURSOR g_cursor_0041ec4c;
HINSTANCE g_hInstance_004149b8;
int g_flag_0041e888;
HBITMAP g_bitmap_00415620;
HBITMAP g_memBitmap_0041495c;

HINSTANCE g_hInstance_00414980;
