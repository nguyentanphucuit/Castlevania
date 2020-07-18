#include "WStopWatch.h"
#include "EnemyFactory.h"


void WStopWatch::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObjects)
{

	if (this->isDestroy)
	{
		return;
	}


	if (this->motionless != 0)
	{

		if (dynamic_cast<PlayScene*>(scene))
		{
			auto pScene = dynamic_cast<PlayScene*>(scene);
			pScene->Motionless(true);
		}
	}
	if (this->motionless != 0 && GetTickCount() - this->motionless > STOPWATCH_FREEZE_TIME)
	{
	
		this->motionless = 0;
		auto pScene = dynamic_cast<PlayScene*>(scene);
		


		pScene->Motionless(false);
		isDestroy = true;
	}

}


void WStopWatch::CountMotionless()
{
	if (motionless == 0)
		motionless = GetTickCount();
}

WStopWatch::WStopWatch() :Weapon()
{
	this->motionless = GetTickCount();
	this->damage = 0;
}
