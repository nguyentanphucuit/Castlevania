#pragma once
#include "WDagger.h"
#include "Bone.h"
#include "WAxe.h"

enum class EWeapon {
	NONE,
	DAGGER,
	BONE,
	AXE
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
	case EWeapon::BONE:
		return new Bone();
		break;
	case EWeapon::AXE:
		return new WAxe();
		break;
	default:
		break;
	}
	return T();
}
