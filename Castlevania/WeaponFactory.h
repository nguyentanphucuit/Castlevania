#pragma once
#include "WDagger.h"

enum class EWeapon {
	NONE,
	Dagger
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
	case EWeapon::Dagger:
		return new WDagger();
		break;
	default:
		break;
	}
	return T();
}
