#pragma once
#include "Item.h"
#include "Heart.h"
#include "BHeart.h"
#include "IDagger.h"
#include "IWhip.h"
#include "IMoney.h"
#include "IAXE.h"
#include "IFireBomb.h"
#include "IBoomerang.h"
#include "IInvisible.h"
#include "ICrown.h"
#include "IChicken.h"
#include "IStopWatch.h"
#include "DoubleShot.h"
#include "TripleShot.h"
#include "HolyCross.h"
#include "IMoneyRed.h"
#include "IMoneyBlue.h"
#include "IMoneyWhite.h"
// declarate Item
enum class EItem
{
    DEFAUT,
	BIGHEART=1,
	WHIP,
	DAGGER,
	HEART,
    MONEY,
    AXE,
    FIREBOMB,
    BOOMERANG,
    INVISIBLE,
    CROWN,
    CHICKEN,
    STOPWATCH,
    DOUBLESHOT,
    TRIPLESHOT,
    HOLYCROSS,
    MONEYRED,
    MONEYBLUE,
    MONEYWHITE,
};

class ItemFactory
{

public:

	template <typename T> static T SpawnItem(EItem item);

};

template<typename T>
inline T ItemFactory::SpawnItem(EItem eitem)
{
   
    switch (eitem)
    {
    case EItem::BIGHEART: 
        return new BHeart();
    case EItem::WHIP:
        return new IWhip();
    case EItem::DAGGER:
        return new IDagger();
    case EItem::HEART:
        return new CHeart();
    case EItem::MONEY:
        return new IMoney();
    case EItem::AXE:
        return new IAXE();
    case EItem::FIREBOMB:
        return new IFireBomb();
    case EItem::BOOMERANG:
        return new IBoomerang();
    case EItem::INVISIBLE:
        return new IInvisible();
    case EItem::CROWN:
        return new ICrown();
    case EItem::CHICKEN:
        return new IChicken();
    case EItem::STOPWATCH:
        return new IStopWatch();
    case EItem::DOUBLESHOT:
        return new DoubleShot();
    case EItem::TRIPLESHOT:
        return new TripleShot();
    case EItem::HOLYCROSS:
        return new IHolyCross();
    case EItem::MONEYRED:
        return new IMoneyRed();
    case EItem::MONEYBLUE:
        return new IMoneyBlue();
    case EItem::MONEYWHITE:
        return new IMoneyWhite();
    case EItem::DEFAUT:
        break;
    default:
        break;
    }

    return T();
}
