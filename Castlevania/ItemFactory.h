#pragma once
#include"Item.h"
#include"Heart.h"
#include"BHeart.h"
// khai báo các loại item tại đây
enum class EItem
{
	BIGHEART=1,
	HEART,
	DAGGER,
	WHIP,

};

class ItemFactory
{

public:
	// Kiểu T trả về nhiều kiểu đối tượng khác nhau
	//đọc thêm về template
	template <typename T> static T SpawnItem(EItem item);

};

template<typename T>
inline T ItemFactory::SpawnItem(EItem eitem)
{
    Item* item = NULL;
    switch (eitem)
    {
    case EItem::BIGHEART: 
        return new BHeart();
        break;
    case EItem::HEART:
        return new CHeart();
        break;
    case EItem::DAGGER:
        break;
    case EItem::WHIP:
        break;
    default:
        break;
    }

    return T();
}
