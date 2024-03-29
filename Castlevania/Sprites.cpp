#include "Sprites.h"
#include "Game.h"
#include "debug.h"

CSprite::CSprite(string id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;
}

CSprites * CSprites::__instance = NULL;

CSprites *CSprites::GetInstance()
{
	if (__instance == NULL) __instance = new CSprites();
	return __instance;
}

void CSprite::Draw(DIRECTION nx, float x, float y, int alpha )
{
	CGame * game = CGame::GetInstance();
	game->Draw(nx,x, y, texture, left, top, right, bottom, alpha);
}

void CSprite::DrawUI( float x, float y, int alpha)
{
	CGame* game = CGame::GetInstance();
	game->Draw(x, y, texture, left, top, right, bottom);
}

void CSprites::Add(string id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	LPSPRITE s = new CSprite(id, left, top, right, bottom, tex);
	sprites[id] = s;
}

LPSPRITE CSprites::Get(string id)
{
	return sprites[id];
}



void CAnimation::Add(string spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t=this->defaultTime;

	LPSPRITE sprite = CSprites::GetInstance()->Get(spriteId);
	LPANIMATION_FRAME frame = new CAnimationFrame(sprite, t);
	frames.push_back(frame);
}

void CAnimation::Render(DIRECTION nx,float x, float y, int alpha)
{
	DWORD now = GetTickCount();
	if (currentFrame == -1) 
	{
		currentFrame = 0; 
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			lastFrameTime = now;
			if (!isBlocking)
			{
				currentFrame++;
				if (currentFrame == frames.size())
				{
					if (isLoop)
					{
						currentFrame = 0;
					}
					else
					{
						currentFrame--;
					}
				}
			} 
			
			
		}
	}
	frames[currentFrame]->GetSprite()->Draw(nx,x, y, alpha);
}

CAnimations * CAnimations::__instance = NULL;

CAnimations * CAnimations::GetInstance()
{
	if (__instance == NULL) __instance = new CAnimations();
	return __instance;
}

void CAnimations::Add(string id, LPANIMATION ani)
{
	animations[id] = ani;
}

LPANIMATION CAnimations::Get(string id)
{
	return animations[id];
}