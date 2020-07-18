#pragma once
#include "Effect.h"
#include "Flame.h"
#include"DebrisBrick.h"
#include "Star.h"
#include "MONEY100.h"
#include "MONEY400.h"
#include "MONEY700.h"
#include "MONEY1000.h"
#include "MONEY2000.h"
enum class CEffect {
	FLAME,
	DEBRIS,
	STAR,
	MONEY100,
	MONEY400,
	MONEY700,
	MONEY1000,
	MONEY2000
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
	case CEffect::MONEY100:
		return new Money100();
		break;
	case CEffect::MONEY400:
		return new Money400();
		break;
	case CEffect::MONEY700:
		return new Money700();
		break;
	case CEffect::MONEY1000:
		return new Money1000();
		break;	
	case CEffect::MONEY2000:
		return new Money2000();
		break;
	default:
		break;
	}
	return T();
}
