#include "IMoneyWhite.h"
#include "PlayScene.h"
#include "EffectFactory.h"

void IMoneyWhite::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject)
{
	Item::Update(dt, scene, coObject);
	auto pScene = dynamic_cast<PlayScene*>(scene);
	auto effect = EffectFactory::SpawnEffect<Effect*>(CEffect::MONEY700);
	if (isDestroy) {
		float tx, ty;
		float l, t, r, b;
		pScene->GetSimon()->GetBoundingBox(l, t, r, b);
		pScene->GetSimon()->GetPosition(tx, ty);
		effect->SetPosition(tx + (r-l) / 2, ty - DISTANCE_EFFECT_Y);
		pScene->SpawnObject(effect);
	}
}

void IMoneyWhite::Render()
{
	if (isDestroy || time_wait)
	{
		return;
	}
	animations[0]->Render(nx, x, y);
	////RenderBoundingBox();
}

void IMoneyWhite::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + MONEYWHITE_WIDTH;
	b = y + MONEYWHITE_HEIGHT;
}
