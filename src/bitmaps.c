#include "rats.h"

/* Function start: 0x40910C */
void __cdecl LoadLevelBitmaps(int levelIndex)
{
  int iVar1;
  unsigned int uVar2;
  int local_c;

  uVar2 = (int)g_currentScoreValue_0041e86c >> 0x1f;
  iVar1 = ((g_currentScoreValue_0041e86c ^ uVar2) - uVar2 & 0x1f ^ uVar2) - uVar2;
  iVar1 = (int)(iVar1 + (iVar1 >> 0x1f & 7U)) >> 3;
  if ((levelIndex != 0) || (iVar1 != g_loadedLevelIndex_0041e890)) {
    if (levelIndex == 0) {
      DeleteObject(g_bitmapN_00414970);
      DeleteObject(g_bitmapE_00414998);
      DeleteObject(g_bitmapS_00414984);
      DeleteObject(g_bitmapW_00414974);
      DeleteObject(g_bitmapNE_00415654);
      DeleteObject(g_bitmapSE_004167b4);
      DeleteObject(g_bitmapSW_004167ac);
      DeleteObject(g_bitmapNW_004167b8);
      DeleteObject(g_bitmapEN_00416658);
      DeleteObject(g_bitmapES_00416670);
      DeleteObject(g_bitmapWS_004167a8);
      DeleteObject(g_bitmapWN_004167b0);
      for (local_c = 0; local_c < 4; local_c = local_c + 1) {
        DeleteObject((&g_grassBitmaps_00416660[0])[local_c]);
        DeleteObject(g_flowerBitmaps_004149c0[local_c]);
        DeleteObject((&g_caveBitmaps_004155d0[0])[local_c]);
        DeleteObject((&g_gasBitmaps_0041ebc8[0])[local_c]);
        DeleteObject((&g_explosionBitmaps_00416678[0])[local_c]);
      }
    }
    g_loadedLevelIndex_0041e890 = iVar1;
    switch(iVar1) {
    case 0:
      g_grassBitmaps_00416660[0] = LoadBitmapA(g_hInstance_004149b8,"BMP_1_GRASS_1");
      g_grassBitmaps_00416660[1] = LoadBitmapA(g_hInstance_004149b8,"BMP_1_GRASS_2");
      g_grassBitmaps_00416660[2] = LoadBitmapA(g_hInstance_004149b8,"BMP_1_GRASS_3");
      g_grassBitmaps_00416660[3] = LoadBitmapA(g_hInstance_004149b8,"BMP_1_GRASS_4");
      g_bitmapS_00414984 = LoadBitmapA(g_hInstance_004149b8,"BMP_1_S");
      g_bitmapE_00414998 = LoadBitmapA(g_hInstance_004149b8,"BMP_1_E");
      g_bitmapW_00414974 = LoadBitmapA(g_hInstance_004149b8,"BMP_1_W");
      g_bitmapNE_00415654 = LoadBitmapA(g_hInstance_004149b8,"BMP_1_NE");
      g_bitmapSE_004167b4 = LoadBitmapA(g_hInstance_004149b8,"BMP_1_SE");
      g_bitmapSW_004167ac = LoadBitmapA(g_hInstance_004149b8,"BMP_1_SW");
      g_bitmapNW_004167b8 = LoadBitmapA(g_hInstance_004149b8,"BMP_1_NW");
      g_bitmapEN_00416658 = LoadBitmapA(g_hInstance_004149b8,"BMP_1_EN");
      g_bitmapES_00416670 = LoadBitmapA(g_hInstance_004149b8,"BMP_1_ES");
      g_bitmapWS_004167a8 = LoadBitmapA(g_hInstance_004149b8,"BMP_1_WS");
      g_bitmapWN_004167b0 = LoadBitmapA(g_hInstance_004149b8,"BMP_1_WN");
      g_bitmapN_00414970 = LoadBitmapA(g_hInstance_004149b8,"BMP_1_N");
      g_caveBitmaps_004155d0[0] = LoadBitmapA(g_hInstance_004149b8,"BMP_1_CAVE_UP");
      g_caveBitmaps_004155d0[1] = LoadBitmapA(g_hInstance_004149b8,"BMP_1_CAVE_DOWN");
      g_caveBitmaps_004155d0[2] = LoadBitmapA(g_hInstance_004149b8,"BMP_1_CAVE_LEFT");
      g_caveBitmaps_004155d0[3] = LoadBitmapA(g_hInstance_004149b8,"BMP_1_CAVE_RIGHT");
      g_flowerBitmaps_004149c0[0] = LoadBitmapA(g_hInstance_004149b8,"BMP_1_FLOWER_1");
      g_flowerBitmaps_004149c0[1] = LoadBitmapA(g_hInstance_004149b8,"BMP_1_FLOWER_2");
      g_flowerBitmaps_004149c0[2] = LoadBitmapA(g_hInstance_004149b8,"BMP_1_FLOWER_3");
      g_flowerBitmaps_004149c0[3] = LoadBitmapA(g_hInstance_004149b8,"BMP_1_FLOWER_4");
      g_gasBitmaps_0041ebc8[0] = LoadBitmapA(g_hInstance_004149b8,"BMP_1_GAS_UP");
      g_gasBitmaps_0041ebc8[1] = LoadBitmapA(g_hInstance_004149b8,"BMP_1_GAS_DOWN");
      g_gasBitmaps_0041ebc8[2] = LoadBitmapA(g_hInstance_004149b8,"BMP_1_GAS_LEFT");
      g_gasBitmaps_0041ebc8[3] = LoadBitmapA(g_hInstance_004149b8,"BMP_1_GAS_RIGHT");
      g_explosionBitmaps_00416678[0] = LoadBitmapA(g_hInstance_004149b8,"BMP_1_EXPLOSION_UP");
      g_explosionBitmaps_00416678[1] = LoadBitmapA(g_hInstance_004149b8,"BMP_1_EXPLOSION_DOWN");
      g_bombFrame2_00416680 = LoadBitmapA(g_hInstance_004149b8,"BMP_1_EXPLOSION_LEFT");
      g_bombFrame3_00416684 = LoadBitmapA(g_hInstance_004149b8,"BMP_1_EXPLOSION_RIGHT");
      break;
    case 1:
      g_grassBitmaps_00416660[0] = LoadBitmapA(g_hInstance_004149b8,"BMP_2_GRASS_1");
      g_grassBitmaps_00416660[1] = LoadBitmapA(g_hInstance_004149b8,"BMP_2_GRASS_2");
      g_grassBitmaps_00416660[2] = LoadBitmapA(g_hInstance_004149b8,"BMP_2_GRASS_3");
      g_grassBitmaps_00416660[3] = LoadBitmapA(g_hInstance_004149b8,"BMP_2_GRASS_4");
      g_bitmapN_00414970 = LoadBitmapA(g_hInstance_004149b8,"BMP_2_N");
      g_bitmapS_00414984 = LoadBitmapA(g_hInstance_004149b8,"BMP_2_S");
      g_bitmapE_00414998 = LoadBitmapA(g_hInstance_004149b8,"BMP_2_E");
      g_bitmapW_00414974 = LoadBitmapA(g_hInstance_004149b8,"BMP_2_W");
      g_bitmapNE_00415654 = LoadBitmapA(g_hInstance_004149b8,"BMP_2_NE");
      g_bitmapSE_004167b4 = LoadBitmapA(g_hInstance_004149b8,"BMP_2_SE");
      g_bitmapSW_004167ac = LoadBitmapA(g_hInstance_004149b8,"BMP_2_SW");
      g_bitmapNW_004167b8 = LoadBitmapA(g_hInstance_004149b8,"BMP_2_NW");
      g_bitmapEN_00416658 = LoadBitmapA(g_hInstance_004149b8,"BMP_2_EN");
      g_bitmapES_00416670 = LoadBitmapA(g_hInstance_004149b8,"BMP_2_ES");
      g_bitmapWS_004167a8 = LoadBitmapA(g_hInstance_004149b8,"BMP_2_WS");
      g_bitmapWN_004167b0 = LoadBitmapA(g_hInstance_004149b8,"BMP_2_WN");
      g_caveBitmaps_004155d0[0] = LoadBitmapA(g_hInstance_004149b8,"BMP_2_CAVE_UP");
      g_caveBitmaps_004155d0[1] = LoadBitmapA(g_hInstance_004149b8,"BMP_2_CAVE_DOWN");
      g_caveBitmaps_004155d0[2] = LoadBitmapA(g_hInstance_004149b8,"BMP_2_CAVE_LEFT");
      g_caveBitmaps_004155d0[3] = LoadBitmapA(g_hInstance_004149b8,"BMP_2_CAVE_RIGHT");
      g_flowerBitmaps_004149c0[0] = LoadBitmapA(g_hInstance_004149b8,"BMP_2_FLOWER_1");
      g_flowerBitmaps_004149c0[1] = LoadBitmapA(g_hInstance_004149b8,"BMP_2_FLOWER_2");
      g_flowerBitmaps_004149c0[2] = LoadBitmapA(g_hInstance_004149b8,"BMP_2_FLOWER_3");
      g_flowerBitmaps_004149c0[3] = LoadBitmapA(g_hInstance_004149b8,"BMP_2_FLOWER_4");
      g_gasBitmaps_0041ebc8[0] = LoadBitmapA(g_hInstance_004149b8,"BMP_2_GAS_UP");
      g_gasBitmaps_0041ebc8[1] = LoadBitmapA(g_hInstance_004149b8,"BMP_2_GAS_DOWN");
      g_gasBitmaps_0041ebc8[2] = LoadBitmapA(g_hInstance_004149b8,"BMP_2_GAS_LEFT");
      g_gasBitmaps_0041ebc8[3] = LoadBitmapA(g_hInstance_004149b8,"BMP_2_GAS_RIGHT");
      g_explosionBitmaps_00416678[0] = LoadBitmapA(g_hInstance_004149b8,"BMP_2_EXPLOSION_UP");
      g_explosionBitmaps_00416678[1] = LoadBitmapA(g_hInstance_004149b8,"BMP_2_EXPLOSION_DOWN");
      g_bombFrame2_00416680 = LoadBitmapA(g_hInstance_004149b8,"BMP_2_EXPLOSION_LEFT");
      g_bombFrame3_00416684 = LoadBitmapA(g_hInstance_004149b8,"BMP_2_EXPLOSION_RIGHT");
      break;
    case 2:
      g_grassBitmaps_00416660[0] = LoadBitmapA(g_hInstance_004149b8,"BMP_3_GRASS_1");
      g_grassBitmaps_00416660[1] = LoadBitmapA(g_hInstance_004149b8,"BMP_3_GRASS_2");
      g_grassBitmaps_00416660[2] = LoadBitmapA(g_hInstance_004149b8,"BMP_3_GRASS_3");
      g_grassBitmaps_00416660[3] = LoadBitmapA(g_hInstance_004149b8,"BMP_3_GRASS_4");
      g_bitmapN_00414970 = LoadBitmapA(g_hInstance_004149b8,"BMP_3_N");
      g_bitmapS_00414984 = LoadBitmapA(g_hInstance_004149b8,"BMP_3_S");
      g_bitmapE_00414998 = LoadBitmapA(g_hInstance_004149b8,"BMP_3_E");
      g_bitmapW_00414974 = LoadBitmapA(g_hInstance_004149b8,"BMP_3_W");
      g_bitmapNE_00415654 = LoadBitmapA(g_hInstance_004149b8,"BMP_3_NE");
      g_bitmapSE_004167b4 = LoadBitmapA(g_hInstance_004149b8,"BMP_3_SE");
      g_bitmapSW_004167ac = LoadBitmapA(g_hInstance_004149b8,"BMP_3_SW");
      g_bitmapNW_004167b8 = LoadBitmapA(g_hInstance_004149b8,"BMP_3_NW");
      g_bitmapEN_00416658 = LoadBitmapA(g_hInstance_004149b8,"BMP_3_EN");
      g_bitmapES_00416670 = LoadBitmapA(g_hInstance_004149b8,"BMP_3_ES");
      g_bitmapWS_004167a8 = LoadBitmapA(g_hInstance_004149b8,"BMP_3_WS");
      g_bitmapWN_004167b0 = LoadBitmapA(g_hInstance_004149b8,"BMP_3_WN");
      g_caveBitmaps_004155d0[0] = LoadBitmapA(g_hInstance_004149b8,"BMP_3_CAVE_UP");
      g_caveBitmaps_004155d0[1] = LoadBitmapA(g_hInstance_004149b8,"BMP_3_CAVE_DOWN");
      g_caveBitmaps_004155d0[2] = LoadBitmapA(g_hInstance_004149b8,"BMP_3_CAVE_LEFT");
      g_caveBitmaps_004155d0[3] = LoadBitmapA(g_hInstance_004149b8,"BMP_3_CAVE_RIGHT");
      g_flowerBitmaps_004149c0[0] = LoadBitmapA(g_hInstance_004149b8,"BMP_3_FLOWER_1");
      g_flowerBitmaps_004149c0[1] = LoadBitmapA(g_hInstance_004149b8,"BMP_3_FLOWER_2");
      g_flowerBitmaps_004149c0[2] = LoadBitmapA(g_hInstance_004149b8,"BMP_3_FLOWER_3");
      g_flowerBitmaps_004149c0[3] = LoadBitmapA(g_hInstance_004149b8,"BMP_3_FLOWER_4");
      g_gasBitmaps_0041ebc8[0] = LoadBitmapA(g_hInstance_004149b8,"BMP_3_GAS_UP");
      g_gasBitmaps_0041ebc8[1] = LoadBitmapA(g_hInstance_004149b8,"BMP_3_GAS_DOWN");
      g_gasBitmaps_0041ebc8[2] = LoadBitmapA(g_hInstance_004149b8,"BMP_3_GAS_LEFT");
      g_gasBitmaps_0041ebc8[3] = LoadBitmapA(g_hInstance_004149b8,"BMP_3_GAS_RIGHT");
      g_explosionBitmaps_00416678[0] = LoadBitmapA(g_hInstance_004149b8,"BMP_3_EXPLOSION_UP");
      g_explosionBitmaps_00416678[1] = LoadBitmapA(g_hInstance_004149b8,"BMP_3_EXPLOSION_DOWN");
      g_bombFrame2_00416680 = LoadBitmapA(g_hInstance_004149b8,"BMP_3_EXPLOSION_LEFT");
      g_bombFrame3_00416684 = LoadBitmapA(g_hInstance_004149b8,"BMP_3_EXPLOSION_RIGHT");
      break;
    case 3:
      g_grassBitmaps_00416660[0] = LoadBitmapA(g_hInstance_004149b8,"BMP_4_GRASS_1");
      g_grassBitmaps_00416660[1] = LoadBitmapA(g_hInstance_004149b8,"BMP_4_GRASS_2");
      g_grassBitmaps_00416660[2] = LoadBitmapA(g_hInstance_004149b8,"BMP_4_GRASS_3");
      g_grassBitmaps_00416660[3] = LoadBitmapA(g_hInstance_004149b8,"BMP_4_GRASS_4");
      g_bitmapN_00414970 = LoadBitmapA(g_hInstance_004149b8,"BMP_4_N");
      g_bitmapS_00414984 = LoadBitmapA(g_hInstance_004149b8,"BMP_4_S");
      g_bitmapE_00414998 = LoadBitmapA(g_hInstance_004149b8,"BMP_4_E");
      g_bitmapW_00414974 = LoadBitmapA(g_hInstance_004149b8,"BMP_4_W");
      g_bitmapNE_00415654 = LoadBitmapA(g_hInstance_004149b8,"BMP_4_NE");
      g_bitmapSE_004167b4 = LoadBitmapA(g_hInstance_004149b8,"BMP_4_SE");
      g_bitmapSW_004167ac = LoadBitmapA(g_hInstance_004149b8,"BMP_4_SW");
      g_bitmapNW_004167b8 = LoadBitmapA(g_hInstance_004149b8,"BMP_4_NW");
      g_bitmapEN_00416658 = LoadBitmapA(g_hInstance_004149b8,"BMP_4_EN");
      g_bitmapES_00416670 = LoadBitmapA(g_hInstance_004149b8,"BMP_4_ES");
      g_bitmapWS_004167a8 = LoadBitmapA(g_hInstance_004149b8,"BMP_4_WS");
      g_bitmapWN_004167b0 = LoadBitmapA(g_hInstance_004149b8,"BMP_4_WN");
      g_caveBitmaps_004155d0[0] = LoadBitmapA(g_hInstance_004149b8,"BMP_4_CAVE_UP");
      g_caveBitmaps_004155d0[1] = LoadBitmapA(g_hInstance_004149b8,"BMP_4_CAVE_DOWN");
      g_caveBitmaps_004155d0[2] = LoadBitmapA(g_hInstance_004149b8,"BMP_4_CAVE_LEFT");
      g_caveBitmaps_004155d0[3] = LoadBitmapA(g_hInstance_004149b8,"BMP_4_CAVE_RIGHT");
      g_flowerBitmaps_004149c0[0] = LoadBitmapA(g_hInstance_004149b8,"BMP_4_FLOWER_1");
      g_flowerBitmaps_004149c0[1] = LoadBitmapA(g_hInstance_004149b8,"BMP_4_FLOWER_2");
      g_flowerBitmaps_004149c0[2] = LoadBitmapA(g_hInstance_004149b8,"BMP_4_FLOWER_2");
      g_flowerBitmaps_004149c0[3] = LoadBitmapA(g_hInstance_004149b8,"BMP_4_FLOWER_2");
      g_gasBitmaps_0041ebc8[0] = LoadBitmapA(g_hInstance_004149b8,"BMP_4_GAS_UP");
      g_gasBitmaps_0041ebc8[1] = LoadBitmapA(g_hInstance_004149b8,"BMP_4_GAS_DOWN");
      g_gasBitmaps_0041ebc8[2] = LoadBitmapA(g_hInstance_004149b8,"BMP_4_GAS_LEFT");
      g_gasBitmaps_0041ebc8[3] = LoadBitmapA(g_hInstance_004149b8,"BMP_4_GAS_RIGHT");
      g_explosionBitmaps_00416678[0] = LoadBitmapA(g_hInstance_004149b8,"BMP_4_EXPLOSION_UP");
      g_explosionBitmaps_00416678[1] = LoadBitmapA(g_hInstance_004149b8,"BMP_4_EXPLOSION_DOWN");
      g_bombFrame2_00416680 = LoadBitmapA(g_hInstance_004149b8,"BMP_4_EXPLOSION_LEFT");
      g_bombFrame3_00416684 = LoadBitmapA(g_hInstance_004149b8,"BMP_4_EXPLOSION_RIGHT");
    }
  }
  return;
}
