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
