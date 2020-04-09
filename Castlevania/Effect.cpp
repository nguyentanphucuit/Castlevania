#include "Effect.h"

void Effect::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject)
{
	if (isDestroy) {
		return;
	}
	if (time_exist != 0 && GetTickCount() - time_exist > EFFECT_TIME_LIFE) {

		this->isDestroy = true;
	}
}
