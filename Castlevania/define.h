#pragma once

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"04 - Collision"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define MAX_FRAME_RATE 120

#define ID_TEX_SIMON 0
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20


const enum  SCREENSIZE
{
	WIDTH=512,
	HEIGHT=480
};

enum class DIRECTION {
	DEFAULT = 0,
	LEFT = -1,
	RIGHT = 1,
	TOP = 2,
	BOTTOM = -2,
};

enum class STAIRDIRECTION {
	DEFAULT = -1,
	UPRIGHT,
	UPLEFT,
	DOWNRIGHT,
	DOWNLEFT,
};

enum ENEMYDEF {
	BAT
};