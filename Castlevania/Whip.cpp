#include "Whip.h"
#include "Torch.h"
#include "Candle.h"
#include "ItemFactory.h"
#include "PlayScene.h"
#include "EffectFactory.h"

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
	RenderBoundingBox();// vẽ bbox
}

void Whip::Upgrade()
{
	switch (state) {
	case NORMAL:
		state = CHAIN;
		break;
	case CHAIN:
		state = MORINGSTAR;
	case MORINGSTAR:
		break;
	default:
		break;
	}
}

void Whip::GetBoundingBox(float& l, float& t, float& r, float& b)
{

	if (nx < 0)
	{
		l = x + 20;
		t = y;
		r = l + WHIP_BBOX_NORMAL_WIDTH;
		b = y + WHIP_BBOX_NORMAL_HEIGHT;
	}
	else
	{
		l = x + 140;
		t = y;
		r = l + WHIP_BBOX_NORMAL_WIDTH;
		b = y + WHIP_BBOX_NORMAL_HEIGHT;

	}

}

void Whip::Update(DWORD dt,Scene* scene, vector<LPGAMEOBJECT>* colliable_objects)
{
	if (animations[WHIP_ANI_NORMAL]->GetCurrentFrame()<2)
	{
		return;
	}
	//xử lý va chạmgiữaa whip và các object dùng aabb

	//for (size_t i = 0; i < colliable_objects->size(); i++)
	//{
	//	if (dynamic_cast<CTorch*>(colliable_objects->at(i))) // kiểm tra phải torch không
	//	{
	//		CTorch * torch= dynamic_cast<CTorch*>(colliable_objects->at(i));
	//		if (this->isColliding(torch))// kiểm tra có va chạm k
	//		{
	//			torch->SetDestroy(); // có va chạm hủy torch
	//		}
	//	}
	//}

	for (size_t i = 0; i < colliable_objects->size(); i++)
	{
		if (dynamic_cast<CCandle*>(colliable_objects->at(i))) // kiểm tra phải candle không
		{
			CCandle* candle = dynamic_cast<CCandle*>(colliable_objects->at(i));
			if (this->isColliding(candle))// kiểm tra có va chạm k
			{
				candle->SetDestroy(); // có va chạm hủy candle
			}
		}
		if (dynamic_cast<CTorch*>(colliable_objects->at(i))) // kiểm tra phải candle không
		{
			CTorch* torch = dynamic_cast<CTorch*>(colliable_objects->at(i));
			if (this->isColliding(torch) && !torch->IsDestroyed())// kiểm tra có va chạm k
			{
				auto item = ItemFactory::SpawnItem<Item*>(torch->GetItem());
				auto effect = EffectFactory::SpawnEffect<Effect*>(CEffect::FLAME);
				if (dynamic_cast<PlayScene*>(scene)) //kiểm tra xem scene hiện tại có phải playscene k
				{
					float tx, ty;
					torch->GetPosition(tx, ty);
					PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
					item->SetPosition(tx,ty);
					effect->SetPosition(tx, ty);
					pScene->SpawnObject(item);
					pScene->SpawnObject(effect);
				}
				torch->SetDestroy(); // có va chạm hủy candle
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
