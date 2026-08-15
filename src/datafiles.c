#include "rats.h"

/* Function start: 0x408E6A */
BOOL LoadLevelData(void)
{
	HFILE hFile;
	OFSTRUCT of;
	UINT bytesRead;

	hFile = OpenFile("level.dat", &of, OF_READ);
	bytesRead = _lread(hFile, g_levelData_004167c0, 0x8000);
	_lclose(hFile);
	if (bytesRead != 0x8000) {
		MessageBoxA(g_mainWindow_00414978, "Can't find valid file", "LEVEL.DAT", MB_ICONERROR);
	}

	return bytesRead == 0x8000;
}
