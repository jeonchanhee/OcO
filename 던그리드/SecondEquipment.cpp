#include "stdafx.h"
#include "SecondEquipment.h"


SecondEquipment::SecondEquipment(){} SecondEquipment::~SecondEquipment(){}

HRESULT SecondEquipment::init(ITEMTYPE type, const char* secondEquipmentName, int value, POINT position)
{
	_second.type = type;
	_secondName = secondEquipmentName;
	_value = value;
	_second.x = position.x;
	_second.y = position.y;
	CreateEquipment(type, secondEquipmentName, value);
	_count = 0;
	return S_OK;
}

void SecondEquipment::release()
{
}

void SecondEquipment::update()
{

	_count++;

	if (_second.isFrame)
	{
		if (_count % 10 == 0)
		{
			if (_second.frameX >= _second.image[2]->getMaxFrameX()) _second.frameX = 0;
			_second.image[2]->setFrameX(_second.frameX);
			_second.frameX++;
			_count = 0;
		}
	}

}

void SecondEquipment::render()
{
	
	if (_second.isFrame)
	{
		for (int i = 0; i < 3; i++)
		{
			if (i == 2)
			{
				_second.image[i]->frameRender(DC, _second.rc[i].left, _second.rc[i].top, _second.frameX, _second.frameY);
			}
			else
			{
				_second.image[i]->render(DC, _second.rc[i].left, _second.rc[i].top);
			}
		}
	}

	if(!_second.isFrame)
	{
		for (int i = 0; i < 2; i++)
		{
			_second.image[i]->render(DC, _second.rc[i].left, _second.rc[i].top);
		}
	}
}

void SecondEquipment::CreateEquipment(ITEMTYPE type, const char* secondEquipmentName, int value)
{


	switch (type)
	{
	case SECOND_EQUIPMENT:
		setEquip(secondEquipmentName, value);
		break;

	}
}

void SecondEquipment::setEquip(const char * secondEquipmentName, int value)
{
	char str[128];

	if (value == 1 || value == 2)
	{
		for (int i = 0; i < 2; i++)
		{
			{
				sprintf_s(str, "%s%d%d", secondEquipmentName, value, i);
				_second.image[i] = IMAGEMANAGER->findImage(str);
				_second.rc[i] = RectMake(_second.x + i * 100, _second.y, _second.image[i]->getWidth(),
					_second.image[i]->getHeight());
			}
		}
	}

	if (value == 3 || value == 4)
	{
		for (int i = 0; i < 3; i++)
		{
			sprintf_s(str, "%s%d%d", secondEquipmentName, value, i);
			_second.image[i] = IMAGEMANAGER->findImage(str);
			if (i == 2) // 착용 이미지 일때
			{
				_second.isFrame = true;
				if (_second.isFrame)
				{
					if (i == 2)
					{
						_second.rc[i] = RectMakeCenter(_second.x + i * 100, _second.y, _second.image[i]->getFrameWidth(),
							_second.image[i]->getFrameHeight());
					}
					else
					{
						_second.rc[i] = RectMakeCenter(_second.x + i * 100, _second.y , _second.image[i]->getWidth(),
							_second.image[i]->getHeight());
					}
				}
			}
			else
			{
				_second.rc[i] = RectMakeCenter(_second.x + i * 100, _second.y, _second.image[i]->getWidth(),
					_second.image[i]->getHeight());
			}
		}
	}

	if (value == 1) // 블레스 
	{
		_second.grade = RARE;				// 레어등급
		_second.attackSpeed = 3.3f;			// 공격속도  
		_second.evasionPersent = 3.0f;		// 회피율
		_second.ad = 5;						// 공격력
		_second.price = 7000;				// 가격

	}

	if (value == 2) // 블러드음료
	{
		_second.grade = RARE;				// 무기는 노말
		_second.attackSpeed = 3.3f;			// 공격속도  
		_second.criticalPersent = 3.0f;		// 크리율
		_second.evasionPersent = 3.0f;		// 회피율
		_second.price = 7000;				// 가격


	}

	if (value == 3) // 날개
	{
		_second.grade = LEGENDARY;			// 전설 등급
		_second.attackSpeed = 3.3f;			// 공격속도  
		_second.criticalPersent = 30.0f;	// 크리율
		_second.evasionPersent = 10.0f;		// 회피율
		_second.addMaxHp = 30;				// 최대HP;
		_second.moveMentSpeed = 30.0f;		// 이동속도
		_second.price = 15000;				// 가격
	}

	if (value == 4) // 호랑이기운
	{

		_second.grade = LEGENDARY;			// 전설등급
		_second.attackSpeed = 5.3f;			// 공격속도  
		_second.criticalPersent = 50.0f;	// 크리율
		_second.evasionPersent = 30.0f;		// 회피율
		_second.ad = 20;					// 공격력
		_second.def = 20;					// 방어력
		_second.moveMentSpeed = 30.0f;		// 이동속도
		_second.addMaxHp = 50;				// 최대HP
		_second.price = 20000;				// 가격
	}


}
