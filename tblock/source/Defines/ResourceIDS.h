#ifndef _RESOURCEIDS_H_
#define _RESOURCEIDS_H_

enum E_RES_TYPE
{
	RES_TYPE_AUDIO,
	RES_TYPE_INTERFACE,
	RES_TYPE_GAME,
	RES_TYPE_LANG,
	RES_TYPE_FONT,
	RES_TYPE_MENU,
	RES_TYPE_SPRITE,
	RES_TYPE_ATLAS,

	RES_TYPE_COUNT
};

static char* RES_TYPE_ARRAY[] =
{
	"audio",
	"interface",
	"interface",
	"langs",
	"interface/fonts",
	"menus",
	"sprites",
	"interface/atlases"
};

enum E_RES_ID
{
	RES_ID_NONE,
	RES_ID_IMG_BACKGROUND,
	RES_ID_IMG_BG_OVERLAY,
	RES_ID_IMG_BLOCK_BLUE,
	RES_ID_IMG_BLOCK_CARBON,
	RES_ID_IMG_BLOCK_GREY,
	RES_ID_IMG_BLOCK_GREEN,
	RES_ID_IMG_BLOCK_ORANGE,
	RES_ID_IMG_BLOCK_PURPLE,
	RES_ID_IMG_BLOCK_RED,
	RES_ID_IMG_BLOCK_YELLOW,
	RES_ID_IMG_BTN_ROTATE,
	RES_ID_IMG_BTN_LEFT,
	RES_ID_IMG_BTN_RIGHT,
	RES_ID_IMG_BTN_DOWN,
	RES_ID_IMG_BTN_FORCEDOWN,
	RES_ID_AUDIO_BTN_CLICK,
	RES_ID_AUDIO_ERASE_LINE,
	RES_ID_AUDIO_FIGURE_DOWN,
	RES_ID_AUDIO_FIGURE_MOVE,
	RES_ID_AUDIO_LEVEL_UP,
	RES_ID_AUDIO_THEME,
	RES_ID_AUDIO_GAME_OVER,
	RES_ID_IMG_PLUS,
	RES_ID_IMG_MINUS,
	RES_ID_FONT_COMIC,
	RES_ID_IMG_TITLE,
	RES_ID_IMG_BTN_BACK,
	RES_ID_FONT_TAHOMA,
	RES_ID_CHECKBOX_ON_OFF,

	RES_ID_COUNT
};

static char* RES_ID_ARRAY[] =
{
	"",
	"background",
	"bg_overlay",
	"block_blue",
	"block_carbon",
	"block_gray",
	"block_green",
	"block_orange",
	"block_purple",
	"block_red",
	"block_yellow",
	"rotate",
	"left",
	"right",
	"down",
	"force_down",
	"button_click",
	"erase_line",
	"figure_down",
	"figure_move",
	"level_up",
	"theme",
	"game_over",
	"plus",
	"minus",
	"font_comic",
	"title",
	"back",
	"font_tahoma",
	"checkbox_on_off"
};

#endif