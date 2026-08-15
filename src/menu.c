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
