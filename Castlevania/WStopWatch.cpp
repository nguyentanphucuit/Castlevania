#include "WStopWatch.h"
#include "EnemyFactory.h"


void WStopWatch::Update(DWORD dt, Scene *scene,vector<LPGAMEOBJECT>* coObjects)
{

	if (this->isDestroy)
	{
		return;
	}
	if (this->motionless != 0)
	{
		//enemy->SetMotionless(true);
	}
	if (GetTickCount() - this->motionless > STOPWATCH_FREEZE_TIME)
	{
		//enemy->SetMotionless(false);
		this->motionless = 0;
	}

}


WStopWatch::WStopWatch() :Weapon()
{
	this->motionless = GetTickCount();
	this->damage = 0;
}
