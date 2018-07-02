#include "stdafx.h"
#include "Item.h"


/////////////////////////////////  ////////////////////////////////////

void Item::createItem(int value, ITEMTYPE type, bool frame)
{
	ITEM _item;
	if (type == LONG_ATTACK)			// 1. 공격력 2 공격속도 .요정도 ?
	{
		for (int i = 0; i < 3; ++i)		// 0 1 2 일때  0 은 드랍템 1 은 인벤토리 2 는 착용
		{
			char str[128];
			sprintf_s(str, "총%d%d", value, i);
			_item.image[i] = IMAGEMANAGER->findImage(str);
			
		}
			if (value == 0) //기본무기 
			{
				_item.ad = 10;
				_item.attackSpeed = 20;
				_item.criticalPersent = 30;
				_item.fixedDamage = 7;	                                                                                                                                                                               "
				
			}

			if (value == 1) // 다음무기
			{
				_item.ad = 10;
				_item.attackSpeed = 20;
				_item.criticalPersent = 30;
				_item.fixedDamage = 7;
			}

			if (value == 2)
			{

			}

			if (value == 3)
			{

			}

		
		_item.type = type;
	}
	
	_item.isFrame = frame;
}
