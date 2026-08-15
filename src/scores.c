#include "rats.h"

/* Function start: 0x408F02 */
int LoadHighScores(void)
{
    HFILE hFile;
    OFSTRUCT ofs;
    UINT bytesRead;
    int i;

    hFile = OpenFile("scores.dat", &ofs, OF_READ);
    if (hFile == HFILE_ERROR) {
        return 0;
    }

    bytesRead = _lread(hFile, g_highScores_00416690, sizeof(g_highScores_00416690));
    _lclose(hFile);

    if (bytesRead != sizeof(g_highScores_00416690)) {
        return 0;
    }

    for (i = 0; i < 9; i++) {
        if ((g_highScores_00416690[i].score > g_highScores_00416690[i + 1].score) ||
            (g_highScores_00416690[i].level < g_highScores_00416690[i + 1].level &&
             g_highScores_00416690[i].score == g_highScores_00416690[i + 1].score) ||
            (g_highScores_00416690[i].score < 0)) {
            return 0;
        }

        if (g_highScores_00416690[i].level < 0 || g_highScores_00416690[i].level > 100) {
            return 0;
        }
    }

    return 1;
}

/* Function start: 0x409092 */
void SaveHighScores(void)
{
    HFILE hFile;
    OFSTRUCT ofStruct;
    UINT result;

    hFile = OpenFile("scores.dat", &ofStruct, 0x3800);
    result = _lwrite(hFile, g_highScores_00416690, 0x118);
    if (result != 0x118) {
        MessageBoxA(g_mainWindow_00414978, "File Save Error...", "High Scores", 0x10);
    }
    _lclose(hFile);
}
