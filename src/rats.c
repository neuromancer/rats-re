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

    if (index < 0) {
        return 0;
    }

    x = g_levelIndices_00414e08[index];
    y = g_levelScores_00414e0c[index];

    if (x < g_bitmapWidth_004149d4 || y < g_bitmapHeight_004149d8) {
        return 0;
    }

    if (x >= g_scorePanelXOffset + g_bitmapWidth_004149d4) {
        return 0;
    }

    if (y >= g_scorePanelYOffset + g_bitmapHeight_004149d8) {
        return 0;
    }

    return 1;
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
