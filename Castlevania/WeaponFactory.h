#pragma once
#include "WDagger.h"
#include "Bone.h"
#include "WAxe.h"
#include "WFirebomb.h"
#include "WBoomerang.h"
#include "WStopWatch.h"

enum class EWeapon {
	NONE,
	DAGGER,
	AXE,
	FIREBOMB,
	BOOMERANG,
	BONE,
	STOPWATCH,

};

class WeaponFactory
{
public :
	template<typename T> static T SpawnWeapon(EWeapon eWeapon);
	EWeapon eWeapon;
};

template<typename T>
inline T WeaponFactory::SpawnWeapon(EWeapon eWeapon)
{
	switch (eWeapon)
	{
	case EWeapon::DAGGER:
		return new WDagger();
		break;
	case EWeapon::AXE:
		return new WAxe();
		break;
	case EWeapon::FIREBOMB:
		return new WFireBomb();
		break;
	case EWeapon::BOOMERANG:
		return new WBoomerang();
		break;
	case EWeapon::STOPWATCH:
		return new WStopWatch();
		break;
	default:
		break;
	}
	return T();
}
