#pragma once
#include "Effect.h"
#include "Flame.h"
#include"DebrisBrick.h"
#include "Star.h"

enum class CEffect {
	FLAME,
	DEBRIS,
	STAR
};
class EffectFactory
{
public:
	template <typename T> static T SpawnEffect(CEffect ceffect);
};

template<typename T>
inline T EffectFactory::SpawnEffect(CEffect ceffect)
{
	switch (ceffect) {
	case CEffect::FLAME:
		return new Flame();
		break;
	case CEffect::DEBRIS:
		return new DebrisBrick();
		break;
	case CEffect::STAR:
		return new Star();
		break;
	default:
		break;
	}
	return T();
}
