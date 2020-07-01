﻿#include "Weapon.h"
#include "define.h"
#include "PlayScene.h"
#include "Torch.h"
#include "ItemFactory.h"
#include "EffectFactory.h"
#include "Candle.h"
#include "Enemy.h"
#include "WeaponFactory.h"
#include "Simon.h"

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
		if (pScene->GetSimon()->GetEnergy() == 0)
			this->isDestroy = true;
	}

	WFireBomb* firebomb = new WFireBomb();

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die

	CalcPotentialCollisions(coObject, coEvents);

	// no collision occured, proceed normally
	if (coEvents.size() == 0) {
		x += dx;
		y += dy;
	}
	else {
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		for (UINT i = 0; i < coEventsResult.size(); i++) {
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CTorch*>(e->obj)) {
				CTorch* torch = dynamic_cast<CTorch*>(e->obj);
				if (!torch->IsDestroy()) {
					auto item = ItemFactory::SpawnItem<Item*>(torch->GetItem());
					auto effect = EffectFactory::SpawnEffect<Effect*>(CEffect::FLAME);
					if (dynamic_cast<PlayScene*>(scene)) //kiểm tra xem scene hiện tại có phải playscene k
					{
						float tx, ty;
						torch->GetPosition(tx, ty);
						PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
						item->SetPosition(tx, ty);
						effect->SetPosition(tx, ty);
						pScene->SpawnObject(item);
						pScene->SpawnObject(effect);
						_eWeapon = pScene->GetSimon()->GetCurrentWeapon();
					}
					torch->SetDestroy();
				}
				if (_eWeapon == EWeapon::DAGGER)
					this->SetDestroy();
					
				
			}
			else if (dynamic_cast<CCandle*>(e->obj)) {
				CCandle* candle = dynamic_cast<CCandle*>(e->obj);
				if (!candle->IsDestroy()) {
					auto item = ItemFactory::SpawnItem<Item*>(candle->GetItem());
					auto effect = EffectFactory::SpawnEffect<Effect*>(CEffect::FLAME);
					if (dynamic_cast<PlayScene*>(scene)) //kiểm tra xem scene hiện tại có phải playscene k
					{
						float tx, ty;
						candle->GetPosition(tx, ty);
						PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
						item->SetPosition(tx, ty);
						effect->SetPosition(tx, ty);
						pScene->SpawnObject(item);
						pScene->SpawnObject(effect);
						_eWeapon = pScene->GetSimon()->GetCurrentWeapon();
					}
					candle->SetDestroy();
				}
				if (_eWeapon == EWeapon::DAGGER)
					this->SetDestroy();
			}
			else if (dynamic_cast<Enemy*>(e->obj)) {
				if (timeCo == 0) {
					timeCo = GetTickCount();
					isCoEnemy = true;
				}
				Enemy* enemy = dynamic_cast<Enemy*>(e->obj);
				
				if (!enemy->IsDestroy() && isCoEnemy) {				
					enemy->SubtractHP(this->damage);
					if (dynamic_cast<PlayScene*>(scene)) 
					{
						auto effect = EffectFactory::SpawnEffect<Effect*>(CEffect::FLAME);
						float tx, ty;
						enemy->GetPosition(tx, ty);
						PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
						effect->SetPosition(tx, ty);
						pScene->SpawnObject(effect);						
					}	
				}
				if (enemy->GetHp() == 0) {
					if (dynamic_cast<PlayScene*>(scene)) {
						auto effect = EffectFactory::SpawnEffect<Effect*>(CEffect::STAR);
						float tx, ty;
						enemy->GetPosition(tx, ty);
						PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
						effect->SetPosition(tx, ty);
						pScene->SpawnObject(effect);
						_eWeapon = pScene->GetSimon()->GetCurrentWeapon();
						pScene->GetSimon()->AddScore(enemy->GetScore());
					}
					enemy->SetDestroy();
				}
				if (_eWeapon == EWeapon::DAGGER)
					this->SetDestroy();
				if (timeCo != 0 && GetTickCount() - timeCo > TIME_CO)
					timeCo = 0;
				else 
					isCoEnemy = false;
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