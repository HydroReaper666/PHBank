#include "ts.h"
#include "key.h"

#include <sf2d.h>
#include <stdlib.h>
#include <string.h>

// #define TS_DEBUG

#ifdef TS_DEBUG
#include <stdio.h>
#define debug_print(fmt, args ...) printf(fmt, ##args)
#define r(fmt, args ...) printf(fmt, ##args)
#else
#define debug_print(fmt, args ...)
#define r(fmt, args ...)
#endif

AM_TitleMediaEntry titleEntry;

static u32 titleCount;
static s32 titleCurrent;
static AM_TitleMediaEntry* titleList;
static sf2d_texture** titleIcons;

/**
 * @brief Updates the output title enty.
 */
static void TS_Select(void)
{
	debug_print("TS_Select:\n");

	titleEntry = titleList[titleCurrent];

	debug_print("Selected: %s\n[0x%014llx]\n", AM_GetPokemonTitleName(titleEntry.titleid), titleEntry.titleid);
}

/**
 * @brief Initializes the title module.
 */
static Result TS_Init(void)
{
	Result ret;

	debug_print("TS_Init:\n");

	titleCount = 0;
	titleCurrent = 0;

	amInit();

	ret = AM_GetPokemonTitleEntryList(&titleList, &titleCount);
	r(" > AM_GetPokemonTitleEntryList: %lx\n", ret);

	debug_print("Got: %li titles\n", titleCount);

	titleIcons = (sf2d_texture**) malloc(titleCount * sizeof(sf2d_texture*));

	for (u32 i = 0; i < titleCount; i++)
	{
		debug_print("Texturing %li\n", i);
		titleIcons[i] = sf2d_create_texture(48, 48, TEXFMT_RGB565, SF2D_PLACE_RAM);
		u16* dst = (u16*)(titleIcons[i]->data + 64 * 8 * 2 * sizeof(u16));
		u16* src = (u16*)(titleList[i].smdh->bigIconData);
		for (u8 j = 0; j < 48; j += 8)
		{
			memcpy(dst, src, 48 * 8 * sizeof(u16));
			src += 48 * 8;
			dst += 64 * 8;
		}
	}

	sf2d_set_clear_color(RGBA8(0x40,0x40,0x40,0xFF));

	debug_print("Textured\n");

	if (titleCount > 0)
	{
		TS_Select();
	}

	return ret;
}

/**
 * @brief Exits the title module.
 */
static void TS_Exit(void)
{
	AM_FreePokemonTitleEntryList(titleList, titleCount);
	free(titleIcons);

	amExit();
}
/**
 * @brief Selects the previous title.
 */
static void TS_Prev(void)
{
	titleCurrent--;
	if (titleCurrent < 0)
		titleCurrent = titleCount-1;
	TS_Select();
}

/**
 * @brief Selects the next title.
 */
static void TS_Next(void)
{
	titleCurrent++;
	if (titleCurrent > titleCount-1)
		titleCurrent = 0;
	TS_Select();
}

bool TS_Loop(void)
{
	TS_Init();

	// If no title, cancel it.
	if (titleCount == 0)
	{
		TS_Exit();
		return false;
	}
	// If only one title, select it by default.
	// else if (titleCount == 1)
	// {
	// 	TS_Select();
	// 	TS_Exit();
	// 	return true;
	// }

	bool tsReturn = false;

	while (aptMainLoop())
	{
		hidScanInput();

		u32 kState = hidKeysDown();

		if (kState & (KEY_UP | KEY_LEFT))
		{
			TS_Prev();
		}
		if (kState & (KEY_DOWN | KEY_RIGHT))
		{
			TS_Next();
		}

		if (kState & KEY_A)
		{
			tsReturn = true;
			break;
		}

		if (kState & (KEY_B | KEY_START))
		{
			tsReturn = false;
			break;
		}

#ifdef TS_DEBUG
		gspWaitForVBlank();
#else
		sf2d_start_frame(GFX_TOP, GFX_LEFT);
		{
			// sf2d_draw_rectangle(151, 63, titleIcons[titleCurrent]->width*2+2, titleIcons[titleCurrent]->height*2+2, RGBA8(0xFF,0xAA,0x55,0xFF));
			// sf2d_draw_rectangle(152, 64, titleIcons[titleCurrent]->width*2, titleIcons[titleCurrent]->height*2, RGBA8(0x55,0xAA,0xFF,0xFF));

			// sf2d_draw_rectangle( 63, 95, titleIcons[titleCurrent]->width+2, titleIcons[titleCurrent]->height+2, RGBA8(0xAA,0x88,0x55,0xFF));
			// sf2d_draw_rectangle( 64, 96, titleIcons[titleCurrent]->width, titleIcons[titleCurrent]->height, RGBA8(0x55,0x88,0xAA,0xFF));

			// sf2d_draw_rectangle(287, 95, titleIcons[titleCurrent]->width+2, titleIcons[titleCurrent]->height+2, RGBA8(0xAA,0x88,0x55,0xFF));
			// sf2d_draw_rectangle(288, 96, titleIcons[titleCurrent]->width, titleIcons[titleCurrent]->height, RGBA8(0x55,0x88,0xAA,0xFF));

			if (titleCount > 0)
			{
				sf2d_draw_texture_scale(titleIcons[titleCurrent], 152, 160, 2.0f, -2.0f);

				// sf2d_draw_texture_scale(titleIcons[titleCurrent], 152, 64, 2.0f, 2.0f);

				if (titleList[titleCurrent].mediatype == MEDIATYPE_GAME_CARD)
				{
					sf2d_draw_rectangle(248, 64, 8, 16, RGBA8(0xFF,0xFF,0xFF,0xFF));
				}
			}

			if (titleCurrent > 0)
			{
				sf2d_draw_texture_scale(titleIcons[titleCurrent-1], 64, 144, 1.0f, -1.0f);

				// sf2d_draw_texture(titleIcons[titleCurrent-1], 64, 96);

				if (titleList[titleCurrent-1].mediatype == MEDIATYPE_GAME_CARD)
				{
					sf2d_draw_rectangle(112, 96, 4, 8, RGBA8(0xFF,0xFF,0xFF,0xFF));
				}
			}
			else if (titleCurrent < titleCount-1)
			{
				sf2d_draw_texture_scale(titleIcons[titleCount-1], 64, 144, 1.0f, -1.0f);

				if (titleList[titleCount-1].mediatype == MEDIATYPE_GAME_CARD)
				{
					sf2d_draw_rectangle(112, 96, 4, 8, RGBA8(0xFF,0xFF,0xFF,0xFF));
				}
			}

			if (titleCurrent < titleCount-1)
			{
				sf2d_draw_texture_scale(titleIcons[titleCurrent+1], 288, 144, 1.0f, -1.0f);

				// sf2d_draw_texture(titleIcons[titleCurrent+1], 288, 96);

				if (titleList[titleCurrent+1].mediatype == MEDIATYPE_GAME_CARD)
				{
					sf2d_draw_rectangle(336, 96, 4, 8, RGBA8(0xFF,0xFF,0xFF,0xFF));
				}
			}
			else if (titleCurrent > 0)
			{
				sf2d_draw_texture_scale(titleIcons[0], 288, 144, 1.0f, -1.0f);

				if (titleList[0].mediatype == MEDIATYPE_GAME_CARD)
				{
					sf2d_draw_rectangle(336, 96, 4, 8, RGBA8(0xFF,0xFF,0xFF,0xFF));
				}
			}
		}
		sf2d_end_frame();
		sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
		sf2d_end_frame();
		sf2d_swapbuffers();
#endif
	}

	TS_Exit();
	return tsReturn;
}
