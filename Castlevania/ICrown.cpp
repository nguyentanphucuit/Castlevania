#include "ICrown.h"
#include "EffectFactory.h"
#include "PlayScene.h"
void ICrown::Render()
{
	if (isDestroy) {
		return;
	}
	animations[0]->Render(DIRECTION::DEFAULT, x, y);
	////RenderBoundingBox();
}

void ICrown::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject)
{
	CGameObject::Update(dt, scene);
	auto pScene = dynamic_cast<PlayScene*>(scene);
	auto effect = EffectFactory::SpawnEffect<Effect*>(CEffect::MONEY2000);
	if (isDestroy) {
		float tx, ty;
		float l, t, r, b;
		pScene->GetSimon()->GetBoundingBox(l, t, r, b);
		pScene->GetSimon()->GetPosition(tx, ty);
		effect->SetPosition(tx + (r - l) / 2, ty - DISTANCE_EFFECT_Y);
		pScene->SpawnObject(effect);
	}
	vy = -VELOCITY_Y;

	bool isCoGround = false;
	for (std::size_t i = 0; i < coObject->size(); i++) {
		if (dynamic_cast<Ground*>(coObject->at(i))) {
			Ground* g = dynamic_cast<Ground*>(coObject->at(i));
			if (this->isColliding(g)) {
				isCoGround = true;
			}
		}
	}
	if (isCoGround) {
		y += dy;
	}
	else
	{
		vx = 0;
		vy = 0;
	}

}

void ICrown::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + CROWN_WIDTH;
	b = y + CROWN_HEIGHT;
}
