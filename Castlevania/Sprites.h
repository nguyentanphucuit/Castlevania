#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
#include "define.h"

using namespace std;

class CSprite
{
	string id;				// Sprite ID in the sprite database

	int left; 
	int top;
	int right;
	int bottom;

	LPDIRECT3DTEXTURE9 texture;
public: 
	CSprite(string id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);

	void Draw(DIRECTION nx, float x, float y, int alpha = 255 );
};

typedef CSprite * LPSPRITE;

/*
	Manage sprite database
*/
class CSprites
{
	static CSprites * __instance;

	unordered_map<string, LPSPRITE> sprites;

public:
	void Add(string id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	LPSPRITE Get(string id);
	LPSPRITE &operator[](string id) {return sprites[id];}

	static CSprites * GetInstance();
};

/*
	Sprite animation
*/
class CAnimationFrame
{
	LPSPRITE sprite;
	DWORD time;

public:
	CAnimationFrame(LPSPRITE sprite, int time) { this->sprite = sprite; this->time = time; }
	DWORD GetTime() { return time; }
	LPSPRITE GetSprite() { return sprite; }
};

typedef CAnimationFrame *LPANIMATION_FRAME;

class CAnimation
{
	DWORD lastFrameTime;
	int defaultTime;
	int currentFrame;
	vector<LPANIMATION_FRAME> frames;
	bool isLoop = true;
	bool isDone = false;
public:
	void SetLoop(bool flag) { isLoop = flag; }
	CAnimation(int defaultTime) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; }
	void Add(string spriteId, DWORD time = 0);
	void ResetFrame() { this->currentFrame = -1; }
	void ResetAnimation() { lastFrameTime = -1; currentFrame = -1; }
	int GetCurrentFrame() { return this->currentFrame; }
	void Render(DIRECTION nx ,float x, float y, int alpha=255);
	int GetLastFrame() {
		return frames.size() - 1;
	}
	bool CheckAnimationDone() {
		return this->isDone;
	};
	void ResetLastFrame() {
		this->isDone = false;
	}
};

typedef CAnimation *LPANIMATION;

class CAnimations
{
	static CAnimations * __instance;

	unordered_map<string, LPANIMATION> animations;

public:
	void Add(string id, LPANIMATION ani);
	LPANIMATION Get(string id);

	static CAnimations * GetInstance();
};

