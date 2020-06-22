#include "IStopWatch.h"

void IStopWatch::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject)
{
	Item::Update(dt, scene, coObject);
}

void IStopWatch::Render()
{
	if (isDestroy || time_wait) {
		return;
	}
	animations[0]->Render(nx, x, y);
	//RenderBoundingBox();
}

void IStopWatch::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + STOPWATCH_WIDTH;
	b = y + STOPWATCH_HEIGHT;
}
