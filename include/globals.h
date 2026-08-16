#ifndef RATS_GLOBALS_H
#define RATS_GLOBALS_H

#include <windows.h>

#include "types.h"

extern HWND g_mainWindow_00414978;
extern HMENU g_mainMenu_0041497c;
extern HighScore g_highScores_00416690[10];
extern char g_levelData_004167c0[0x8000];

extern HBITMAP g_memBitmap_00414940;
extern int g_bitmapWidth_004149d4;
extern int g_bitmapHeight_004149d8;

extern long g_score_0041560c;

extern int g_scoreCounts_00414948[2];
extern int g_baseScore_0041494c;
extern int g_totalScore_00414954;
extern int g_levelIndices_00414e08[50];
extern int g_levelScores_00414e0c[50];
extern HFONT g_fontSmall_0041ec18;
extern HFONT g_fontMedium_00415618;
extern HFONT g_fontLarge_0041ebc0;
extern HFONT g_fontTitle_00415604;

extern int g_scoreCounts_004155e8[7];
extern HGDIOBJ g_scoreObjects_00415638[7];

extern int g_scorePanelActive;
extern HGDIOBJ g_scorePanelDefaultBitmap;
extern HGDIOBJ g_scorePanelActiveBitmap;
extern int g_currentScoreValue;
extern int g_scorePanelXOffset;
extern int g_scorePanelYOffset;

extern BombData g_bombData_0041e898[20];
extern int g_bombActive_0041668c;
extern HGDIOBJ g_bombFrame1_0041ebbc;
extern HGDIOBJ g_bombFrame2_00416680;
extern HGDIOBJ g_bombFrame3_00416684;
extern HGDIOBJ g_bombFrame4_00416688;
extern int g_soundEnabled_00415624;
extern int g_musicEnabled_004149e0;

extern HGDIOBJ g_bombFrame5_0041668c;

extern HGDIOBJ g_scorePanelDefaultBitmap_004149dc;

extern int g_currentScoreValue_0041e86c;

extern int g_levelXs_0041e7c8[10];
extern int g_levelYs_0041e7cc[10];
extern int g_levelIndices_0041e7d0[10];

extern int g_displayState_0041ec1c;

extern int g_levelTypes_00414e00[50];
extern int g_levelSizes_00414e04[50];
extern int g_displayTable_0041ebd8[16];

extern int g_levelXs_00414df8[50];
extern int g_levelYs_00414dfc[50];
extern int g_levelFlags_00414e18[50];
extern int g_levelFlags_00414e1c[50];
extern int g_levelFlags_00414e10[50];

extern char g_levelMap_004149e8[32][32];
extern int g_levelCount_00414df4;
extern int g_maxLevelWidth_0041e7c4;
extern int g_maxLevelHeight_0041496c;
extern int g_highScoreMax_0041e894;
extern int g_scoreValue_0041e868;
extern int g_levelOffset_004149bc;
extern int g_levelData_0041e8a0[0x28 * 0x14];

extern int g_levelTime_00415630;
extern int g_pointsPerBonus_004155e0;

extern HCURSOR g_cursor_0041ec4c;
extern HINSTANCE g_hInstance_004149b8;
extern int g_flag_0041e888;
extern HBITMAP g_bitmap_00415620;
extern HBITMAP g_memBitmap_0041495c;

extern HINSTANCE g_hInstance_00414980;

extern int g_loadedLevelIndex_0041e890;

extern HGDIOBJ g_bitmapN_00414970;
extern HGDIOBJ g_bitmapS_00414984;
extern HGDIOBJ g_bitmapE_00414998;
extern HGDIOBJ g_bitmapW_00414974;
extern HGDIOBJ g_bitmapNE_00415654;
extern HGDIOBJ g_bitmapSE_004167b4;
extern HGDIOBJ g_bitmapSW_004167ac;
extern HGDIOBJ g_bitmapNW_004167b8;
extern HGDIOBJ g_bitmapEN_00416658;
extern HGDIOBJ g_bitmapES_00416670;
extern HGDIOBJ g_bitmapWS_004167a8;
extern HGDIOBJ g_bitmapWN_004167b0;
extern HGDIOBJ g_grassBitmaps_00416660[4];
extern HGDIOBJ g_flowerBitmaps_004149c0[4];
extern HGDIOBJ g_caveBitmaps_004155d0[4];
extern HGDIOBJ g_gasBitmaps_0041ebc8[4];
extern HGDIOBJ g_explosionBitmaps_00416678[4];

#endif
