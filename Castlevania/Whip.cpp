#include "Whip.h"
#include "Torch.h"
#include "ItemFactory.h"
#include "PlayScene.h"
#include "EffectFactory.h"
#include "define.h"
#include "Candle.h"
#include "BrickWall.h"
#include "Enemy.h"
#include "Simon.h"
void Whip::Render()
{
	int ani;
	switch (state)
	{			
	case NORMAL:
		ani = WHIP_ANI_NORMAL;
		break;
	case CHAIN:
		ani = WHIP_ANI_CHAIN;
		break;
	case MORINGSTAR:
		ani = WHIP_ANI_MORNINGSTAR;
		break;
	}
	animations[ani]->Render(nx, x, y);
	//RenderBoundingBox();// vẽ bbox
}



void Whip::Upgrade()
{
	switch (state) {
	case NORMAL:
		state = CHAIN;
		break;
	case CHAIN:
		state = MORINGSTAR;
		break;
	case MORINGSTAR:
		break;
	default:
		break;
	}
}

void Whip::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	
	if (nx == DIRECTION::LEFT)
	{
		l = x + WHIP_BBOX_NORMAL_HEIGHT;
		t = y;
		if (state == MORINGSTAR) {
			l = x + NEARLY_WIDTH_01;
			r = l + WHIP_BBOX_NORMAL_WIDTH + NEARLY_WIDTH_02;
		}
		else {
			r = l + WHIP_BBOX_NORMAL_WIDTH;
		}
		b = y + WHIP_BBOX_NORMAL_HEIGHT;
		
	}
	else if(nx == DIRECTION::RIGHT)
	{
		
		l = x + WHIP_BBOX_NORMAL_HEIGHT*3;
		t = y;	
		if (state == MORINGSTAR) {

			r = l + WHIP_BBOX_NORMAL_WIDTH + NEARLY_WIDTH_02;
		}
		else {
			r = l + WHIP_BBOX_NORMAL_WIDTH;
		}
		b = y + WHIP_BBOX_NORMAL_HEIGHT;
	}
	

}

void Whip::Update(DWORD dt,Scene* scene, vector<LPGAMEOBJECT>* colliable_objects)
{
	switch (state)
	{
	case NORMAL:
		if (animations[WHIP_ANI_NORMAL]->GetCurrentFrame() < 2)
		{
			return;
		}
		break;
	case CHAIN:
		if (animations[WHIP_ANI_CHAIN]->GetCurrentFrame() < 2)
		{
			return;
		}
		break;
	case MORINGSTAR:
		if (animations[WHIP_ANI_MORNINGSTAR]->GetCurrentFrame() < 8)
		{
			return;
		}
		break;
	default:
		break;
	}
	

	for (size_t i = 0; i < colliable_objects->size(); i++)
	{
		if (dynamic_cast<CTorch*>(colliable_objects->at(i)))
		{
			CTorch* torch = dynamic_cast<CTorch*>(colliable_objects->at(i));
			if (this->isColliding(torch) && !torch->IsDestroyed()) // check CO
			{

				auto item = ItemFactory::SpawnItem<Item*>(torch->GetItem());
				auto effect = EffectFactory::SpawnEffect<Effect*>(CEffect::FLAME);
				if (dynamic_cast<PlayScene*>(scene)) // check scene cur
				{
					float tx, ty;
					torch->GetPosition(tx, ty);
					PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
					item->SetPosition(tx,ty);
					effect->SetPosition(tx, ty);

					pScene->SpawnObject(item);
					pScene->SpawnObject(effect);
				}
				torch->SetDestroy(); 
			}
		}
		else if (dynamic_cast<CCandle*>(colliable_objects->at(i))) {
			CCandle* candle = dynamic_cast<CCandle*>(colliable_objects->at(i));
			if (this->isColliding(candle) && !candle->IsDestroyed()) // check CO
			{

				auto item = ItemFactory::SpawnItem<Item*>(candle->GetItem());
				auto effect = EffectFactory::SpawnEffect<Effect*>(CEffect::FLAME);
				if (dynamic_cast<PlayScene*>(scene)) // check scene cur
				{
					float tx, ty;
					candle->GetPosition(tx, ty);
					PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
					item->SetPosition(tx, ty);
					effect->SetPosition(tx, ty);

					pScene->SpawnObject(item);
					pScene->SpawnObject(effect);
				}
				candle->SetDestroy();
			}
		}
		else if (dynamic_cast<CBrickWall*>(colliable_objects->at(i))) {
			CBrickWall* brickWall = dynamic_cast<CBrickWall*>(colliable_objects->at(i));
			if (this->isColliding(brickWall) && !brickWall->IsDestroyed()) // check CO
			{

				auto item = ItemFactory::SpawnItem<Item*>(brickWall->GetItem());
				if (dynamic_cast<PlayScene*>(scene)) // check scene cur
				{
					float tx, ty;
					brickWall->GetPosition(tx, ty);
					PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
					item->SetPosition(tx, ty);
				
					for (size_t i = 0; i < 3; i++)
					{
						auto debris = EffectFactory::SpawnEffect<Effect*>(CEffect::DEBRIS);
						float vx = (float)(-100 + rand() % 200) / 1000;
						float vy = (float)(-100 + rand() % 200) / 1000;
						debris->vx = vx;
						debris->vy = vy;
						debris->SetPosition(tx, ty);
						pScene->SpawnObject(debris);
					}
					pScene->SpawnObject(item);
				
				}
				brickWall->SetDestroy();
			}
		}
		else if (dynamic_cast<Enemy*>(colliable_objects->at(i))) {
			Enemy* enemy = dynamic_cast<Enemy*>(colliable_objects->at(i));
			if (this->isColliding(enemy) && !enemy->IsDestroyed() ) // check CO
			{
				if (ColOneTime)
				{
					enemy->SubtractHP(this->damage);

					if (enemy->GetHp() == 0)
					{
						enemy->SetDestroy();
					}
				}
			
			
				ColOneTime = false;
				DebugOut(L"okey \n");
				
			}
		}
	}

}


void Whip::SetState(WHIPSTATE state)
{
	switch (state)
	{	
	case NORMAL:
		break;
	case CHAIN:
		break;
	case MORINGSTAR:
		break;
	default:
		break;
	}
	this->state = state;
}
