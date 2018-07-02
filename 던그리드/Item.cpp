#include "stdafx.h"
#include "Item.h"



HRESULT Item::init()
{

	return S_OK;
}


void Item::release()
{

}


void Item::update()
{

}


void Item::render()
{
	
	for (int i = 0 ; i < 3; i ++)
	{
		_viItem->image[i]->render(getMemDC(), _viItem->rc.left, _viItem->rc.top);

	}

}

void Item::createItem(int value, ITEMTYPE type, bool frame)
{
	tagItem _item;
	if (type == LONG_ATTACK)		
	{
		for (int i = 0; i < 3; ++i)		// 0 ���� 1 ��� 2 �κ��丮
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
				_item.fixedDamage = 7;	                                                                                                                                                                               
		
			}

			if (value == 1) // ù��° ����
			{
				_item.ad = 10;
				_item.attackSpeed = 20;
				_item.criticalPersent = 30;
				_item.fixedDamage = 7;
			}

			if (value == 2) // �ι�° ����
			{
				_item.ad = 10;
				_item.attackSpeed = 20;
				_item.criticalPersent = 30;
				_item.fixedDamage = 7;
			}

			if (value == 3) // ����° ����
			{
				_item.ad = 10;
				_item.attackSpeed = 20;
				_item.criticalPersent = 30;
				_item.fixedDamage = 7;
			}

		
		_item.type = type;
	}
	
	_item.isFrame = frame;
}
