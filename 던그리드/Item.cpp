#include "stdafx.h"
#include "Item.h"


/////////////////////////////////  ////////////////////////////////////

void Item::createItem(int value, ITEMTYPE type, bool frame)
{
	ITEM _item;
	if (type == LONG_ATTACK)			// 1. ���ݷ� 2 ���ݼӵ� .������ ?
	{
		for (int i = 0; i < 3; ++i)		// 0 1 2 �϶�  0 �� ����� 1 �� �κ��丮 2 �� ����
		{
			char str[128];
			sprintf_s(str, "��%d%d", value, i);
			_item.image[i] = IMAGEMANAGER->findImage(str);
			
		}
			if (value == 0) //�⺻���� 
			{
				_item.ad = 10;
				_item.attackSpeed = 20;
				_item.criticalPersent = 30;
				_item.fixedDamage = 7;	                                                                                                                                                                               "
				
			}

			if (value == 1) // ��������
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
