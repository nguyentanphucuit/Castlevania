#include "IMoneyBlue.h"
#include "PlayScene.h"
#include "EffectFactory.h"

void IMoneyBlue::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject)
{
	Item::Update(dt, scene, coObject);
	auto pScene = dynamic_cast<PlayScene*>(scene);
	auto effect = EffectFactory::SpawnEffect<Effect*>(CEffect::MONEY400);
	if (isDestroy) {
		float tx, ty;
		float l, t, r, b;
		pScene->GetSimon()->GetBoundingBox(l, t, r, b);
		pScene->GetSimon()->GetPosition(tx, ty);
		effect->SetPosition(tx + (r - l) / 2, ty - DISTANCE_EFFECT_Y);
		pScene->SpawnObject(effect);
	}
}

void IMoneyBlue::Render()
{

	if (isDestroy || time_wait)
	{
		return;
	}
	animations[0]->Render(nx, x, y);
	////RenderBoundingBox();
}

void IMoneyBlue::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + MONEYBLUE_WIDTH;
	b = y + MONEYBLUE_HEIGHT;
}
