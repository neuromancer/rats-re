#include "rats.h"

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
