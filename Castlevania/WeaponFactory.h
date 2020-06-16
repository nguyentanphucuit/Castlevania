#pragma once
#include "WDagger.h"
#include "Skeleton.h"

enum class EWeapon {
	NONE,
	DAGGER,
	SKELETON
};

class WeaponFactory
{
public :
	template<typename T> static T SpawnWeapon(EWeapon eWeapon);
};

template<typename T>
inline T WeaponFactory::SpawnWeapon(EWeapon eWeapon)
{
	switch (eWeapon)
	{
	case EWeapon::DAGGER:
		return new WDagger();
		break;
	case EWeapon::SKELETON:
		return new Skeleton();
		break;
	default:
		break;
	}
	return T();
}
