#include "rats.h"

/* Function start: 0x409DB6 */
int IsRatsHelpFile(void)
{
	HFILE hFile;
	OFSTRUCT ofStruct;
	char szBuffer[7];

	hFile = OpenFile("rats.hlp", &ofStruct, 0x2000);
	if (hFile == NULL) {
		return 0;
	}
	_llseek(hFile, 0x382a, SEEK_SET);
	_lread(hFile, szBuffer, 7);
	if ((szBuffer[0] == 't') &&
	    (szBuffer[1] == 'o') &&
	    (szBuffer[2] == ' ') &&
	    (szBuffer[3] == 'S') &&
	    (szBuffer[4] == 'e') &&
	    (szBuffer[5] == 'a') &&
	    (szBuffer[6] == 'n')) {
		_lclose(hFile);
		return 1;
	}
	return 0;
}
