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

#endif
