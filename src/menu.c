#include "rats.h"

/* Function start: 0x408A51 */
void UpdateMainMenuState(void)
{
	EnableMenuItem(g_mainMenu_0041497c, 0xd2, 0);
	EnableMenuItem(g_mainMenu_0041497c, 0xd2, 0);
	EnableMenuItem(g_mainMenu_0041497c, 0xd3, 1);
	EnableMenuItem(g_mainMenu_0041497c, 0xd4, 1);
	EnableMenuItem(g_mainMenu_0041497c, 0xd5, 1);
	EnableMenuItem(g_mainMenu_0041497c, 0xdc, 1);
}

/* Function start: 0x408AD3 */
int __cdecl InitializeGameLevel(void)
{
    int i;
    int j;
    int k;

    for (i = 0; i < 0x20; i++) {
        for (j = 0; j < 0x20; j++) {
            *(char *)(g_levelData_004167c0 + (i * 0x400) + j) =
                g_levelMap_004149e8[j][i];
        }
    }

    g_levelCount_00414df4 = 0;
    g_bitmapWidth_004149d4 = (0x20 - g_maxLevelWidth_0041e7c4) / 2;
    g_bitmapHeight_004149d8 = (0x20 - g_maxLevelHeight_0041496c) / 2;
    g_displayState_0041ec1c = 10;
    g_highScoreMax_0041e894 = 999;
    g_scoreValue_0041e868 = 0;
    g_levelOffset_004149bc = 0;

    for (k = 0; k < 0x32; k++) {
        g_levelScores_00414e0c[k] = 0;
    }

    for (k = 0; k < (g_currentScoreValue_0041e86c / 2) + 0xc; k++) {
        g_levelXs_00414df8[k] = 0;
        g_levelYs_00414dfc[k] = 0;

        while (g_levelMap_004149e8[g_levelYs_00414dfc[k] / 20][g_levelXs_00414df8[k] / 20] == 1) {
            g_levelXs_00414df8[k] = (rand() % 30 * 4 + 4) * 5 + 10;
            g_levelYs_00414dfc[k] = (rand() % 30 * 4 + 4) * 5 + 10;
        }

        g_levelSizes_00414e04[k] = g_currentScoreValue_0041e86c * 20 + (rand() % 100);
        if (g_levelSizes_00414e04[k] > 300) {
            g_levelSizes_00414e04[k] = 300;
        }

        g_levelTypes_00414e00[k] = 0;
        g_levelIndices_00414e08[k] = k & 1;
        g_levelFlags_00414e10[k] = 0;
        g_levelFlags_00414e18[k] = (rand() % 5) + 20;
        g_levelScores_00414e0c[k] = 20;
        g_levelFlags_00414e1c[k] = 0;
    }

    for (k = 0; k < 10; k++) {
        g_levelIndices_0041e7d0[k] = 999;
    }

    for (k = 0; k < 7; k++) {
        g_scoreCounts_004155e8[k] = 0;
    }

    for (k = 0; k < 0x28; k++) {
        g_levelData_0041e8a0[k * 0x14] = 999;
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 7; j++) {
            DrawFrameBorder(i, j);
        }
    }

    return 1;
}
