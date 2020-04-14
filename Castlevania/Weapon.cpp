#include "Weapon.h"
#include "define.h"
#include "PlayScene.h"
#include "Torch.h"

void Weapon::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject)
{
	if (isDestroy) {
		return;
	}
	CGameObject::Update(dt, scene);
	if (dynamic_cast<PlayScene*>(scene)) {
		PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
		D3DXVECTOR2 cam = pScene->GetCamera();

		if (x < cam.x || x > cam.x + SCREENSIZE::WIDTH) {
			this->isDestroy = true;
		}
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die

	CalcPotentialCollisions(coObject, coEvents);

	// no collision occured, proceed normally
	if (coEvents.size() == 0) {
		x += dx;
	}
	else {
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		for (UINT i = 0; i < coEventsResult.size(); i++) {
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CTorch*>(e->obj)) {
				CTorch* torch = dynamic_cast<CTorch*>(e->obj);
				if (!torch->IsDestroy()) {
					torch->SetDestroy();
				}
				this->SetDestroy();
			}
			else {
				if (nx != 0)
					x += dx;
				else if (ny != 0) {
					y += dy;
				}
			}
		}
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}
