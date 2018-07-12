#include "stdafx.h"
#include "Item.h"



Item::Item(){} Item::~Item(){}



HRESULT Item::init(ITEMTYPE type, const char * itemName, int value, POINT position)
{
	_item.type = type;
	_item.name = itemName;
	_item.value = value;
	_item.x = position.x;
	_item.y = position.y;

	CreateItem(type, itemName, value);
	return S_OK;
}




void Item::release()
{

}



void Item::update()
{

	_count++;

	if (_item.isFrame)
	{
		if (_count % 10 == 0)
		{
			if (_item.frameX >= _item.image[2]->getMaxFrameX()) _item.frameX = 0;
			_item.image[2]->setFrameX(_item.frameX);
			_item.frameX++;
			_count = 0;
		}
	}
}


void Item::render() // 아이템을 렌더
{
	if (_item.type == SWORD || _item.type == BOW || _item.type == HAMMER  ||
		_item.type == GUN || _item.type == SHIELD || _item.type == FOOD)
	{
		if (_item.isFrame)
		{
			for (int i = 0; i < 3; i++)
			{
				if (i == 2)
				{
					_item.image[i]->frameRender(DC, _item.rc[i].left, _item.rc[i].top, _item.frameX, _item.frameY);
				}
				else
				{
					_item.image[i]->render(DC, _item.rc[i].left, _item.rc[i].top);
				}
			}
		}
		else
		{
			for (int i = 0; i < 3; i++)
			{
				_item.image[i]->render(DC, _item.rc[i].left, _item.rc[i].top);
			}
		}

	}

	if (_item.type == ACCESSORY || _item.type == ARMOR)
	{
		for (int i = 0; i < 2; i++)
		{
	
			_item.image[i]->render(DC, _item.rc[i].left, _item.rc[i].top);
			
		}
	}

	if (_item.type == SECOND_EQUIPMENT)
	{
		if (_item.isFrame)
		{
			for (int i = 0; i < 3; i++)
			{
				if (i == 2)
				{
					_item.image[i]->frameRender(DC, _item.rc[i].left, _item.rc[i].top, _item.frameX, _item.frameY);
				}
				else
				{
					_item.image[i]->render(DC, _item.rc[i].left, _item.rc[i].top);
				}
			}
		}

		if (!_item.isFrame)
		{
			for (int i = 0; i < 2; i++)
			{
				_item.image[i]->render(DC, _item.rc[i].left, _item.rc[i].top);
			}
		}
	}


}

void Item::invenRender(HDC hdc, int x, int y)
{	
	_item.image[1]->render(UIDC, x , y);
}





void Item::CreateItem(ITEMTYPE type, const char * itemName, int value) // 아이템 만듬
{

	switch (type)
	{
		case SWORD:
			setSword(itemName, value);
		break;
		case HAMMER:
			setHammer(itemName, value);
		break;
		case GUN:
			setGun(itemName, value);
		break;
		case BOW:
			setBow(itemName, value);
		break;
		case ARMOR:
			setArmor(itemName, value);
		break;
		case SHIELD:
			setShield(itemName, value);
		break;
		case ACCESSORY:
			setAccessory(itemName, value);
		break;
		case FOOD:
			setFood(itemName, value);

		case SECOND_EQUIPMENT:
			setEquip(itemName, value);
		break;
	}
}


void Item::setSword(const char * weaponName, int value)
{
	char str[128];

	for (int i = 0; i < 3; i++)
	{
		sprintf_s(str, "%s%d%d", weaponName, value, i);
		_item.image[i] = IMAGEMANAGER->findImage(str);
		
		_item.rc[i] = RectMake(_item.x + i * 100, _item.y, _item.image[i]->getWidth(),
				_item.image[i]->getHeight());
		
	}

	

	if (value == 1) // 기본무기
	{
		_item.grade = NORMAL;		// 노말등급
		_item.minimumAtt = 8;		// 최소 데미지 8
		_item.MaxAtt = 10;		// 최대 데미지 10
		_item.fixedDamage = 8;	// 고정데미지 8
		_item.attackSpeed = 3.3f;	// 공격속도  
		_item.sellBan = true;		// 판매금지

	}

	if (value == 2) // 무라마사
	{
		_item.grade = RARE;				// 레어등급
		_item.minimumAtt = 20;			// 최소 데미지 10
		_item.MaxAtt = 30;				// 최대 데미지 15
		_item.fixedDamage = 10;			// 고정데미지 10
		_item.attackSpeed = 5.2f;			// 공격속도  
		_item.criticalPersent = 30.0f;	// 크리율
		_item.price = 7000;				// 가격

	}

	if (value == 3) // 화룡 학살자
	{
		_item.grade = RARE;				// 무기는 노말
		_item.minimumAtt = 30;			// 최소 데미지 30
		_item.MaxAtt = 40;				// 최대 데미지 40
		_item.fixedDamage = 8;			// 고정데미지 30
		_item.attackSpeed = 3.3f;			// 공격속도  
		_item.criticalPersent = 30.0f;	// 크리율
		_item.evasionPersent = 3.0f;		// 회피율
		_item.price = 7000;				// 가격


	}

	if (value == 4) // 데몬
	{
		_item.grade = LEGENDARY;			// 전설 등급
		_item.minimumAtt = 40;			// 최소 데미지 40
		_item.MaxAtt = 70;				// 최대 데미지 50
		_item.fixedDamage = 8;			// 고정데미지 40
		_item.attackSpeed = 2.3f;			// 공격속도  
		_item.criticalPersent = 30.0f;	// 크리율
		_item.evasionPersent = 8.0f;		// 회피율
		_item.addMaxHp = 20;				// 최대HP;
		_item.price = 12000;				// 가격
	}

	if (value == 5) // 코스모스
	{
		_item.grade = LEGENDARY;			// 전설등급
		_item.minimumAtt = 30;			// 최소 데미지 30
		_item.MaxAtt = 55;				// 최대 데미지 45
		_item.fixedDamage = 30;			// 고정데미지 30
		_item.attackSpeed = 3.3f;			// 공격속도  
		_item.criticalPersent = 30.0f;	// 크리율
		_item.evasionPersent = 5.0f;		// 회피율
		_item.addMaxHp = 10;				// 최대HP
		_item.price = 15000;				// 가격

	}

	if (value == 6) // 코스모스
	{
		_item.grade = LEGENDARY;			// 전설등급
		_item.minimumAtt = 30;			// 최소 데미지 30
		_item.MaxAtt = 55;				// 최대 데미지 45
		_item.fixedDamage = 30;			// 고정데미지 30
		_item.attackSpeed = 3.3f;			// 공격속도  
		_item.criticalPersent = 30.0f;	// 크리율
		_item.evasionPersent = 5.0f;		// 회피율
		_item.addMaxHp = 10;				// 최대HP
		_item.price = 15000;				// 가격
	}

	if (value == 7) // 코스모스
	{
		_item.grade = LEGENDARY;			// 전설등급
		_item.minimumAtt = 30;			// 최소 데미지 30
		_item.MaxAtt = 55;				// 최대 데미지 45
		_item.fixedDamage = 30;			// 고정데미지 30
		_item.attackSpeed = 3.3f;			// 공격속도  
		_item.criticalPersent = 30.0f;	// 크리율
		_item.evasionPersent = 5.0f;		// 회피율
		_item.addMaxHp = 10;				// 최대HP
		_item.price = 15000;				// 가격
	}

	if (value == 8) // 코스모스
	{
		_item.grade = LEGENDARY;			// 전설등급
		_item.minimumAtt = 30;			// 최소 데미지 30
		_item.MaxAtt = 55;				// 최대 데미지 45
		_item.fixedDamage = 30;			// 고정데미지 30
		_item.attackSpeed = 3.3f;			// 공격속도  
		_item.criticalPersent = 30.0f;	// 크리율
		_item.evasionPersent = 5.0f;		// 회피율
		_item.addMaxHp = 10;				// 최대HP
		_item.price = 15000;				// 가격
	}

	if (value == 9) // 코스모스
	{
		_item.grade = LEGENDARY;			// 전설등급
		_item.minimumAtt = 30;			// 최소 데미지 30
		_item.MaxAtt = 55;				// 최대 데미지 45
		_item.fixedDamage = 30;			// 고정데미지 30
		_item.attackSpeed = 3.3f;			// 공격속도  
		_item.criticalPersent = 30.0f;	// 크리율
		_item.evasionPersent = 5.0f;		// 회피율
		_item.addMaxHp = 10;				// 최대HP
		_item.price = 15000;				// 가격
	}

	if (value == 10) // 코스모스
	{
		_item.grade = LEGENDARY;			// 전설등급
		_item.minimumAtt = 30;			// 최소 데미지 30
		_item.MaxAtt = 55;				// 최대 데미지 45
		_item.fixedDamage = 30;			// 고정데미지 30
		_item.attackSpeed = 3.3f;			// 공격속도  
		_item.criticalPersent = 30.0f;	// 크리율
		_item.evasionPersent = 5.0f;		// 회피율
		_item.addMaxHp = 10;				// 최대HP
		_item.price = 15000;				// 가격
	}


}


















void Item::setHammer(const char * weaponName, int value)
{
	char str[128];
	for (int i = 0; i < 3; i++)
	{
		sprintf_s(str, "%s%d%d", weaponName, value, i);
		_item.image[i] = IMAGEMANAGER->findImage(str);
		_item.rc[i] = RectMake(_item.x + i * 100, _item.y, _item.image[i]->getWidth(),
			_item.image[i]->getHeight());

	}

	if (value == 1) // 조선족 망치
	{
		_item.grade = NORMAL;				// 노말
		_item.minimumAtt = 15;			// 최소 데미지 15
		_item.MaxAtt = 20;				// 최대 데미지 20
		_item.fixedDamage = 15;			// 고정데미지 15
		_item.attackSpeed = 1.3f;			// 공격속도  
		_item.moveMentSpeed = -20.0f;		// 이동속도
		_item.addMaxHp = 5;				// 최대HP;
		_item.price = 1000;				// 가격
	}

	if (value == 2) //드래곤 해머
	{
		_item.grade = RARE;				// 레어
		_item.minimumAtt = 40;			// 최소 데미지 40
		_item.MaxAtt = 50;				// 최대 데미지 50
		_item.fixedDamage = 40;			// 고정데미지 40
		_item.attackSpeed = 1.3f;			// 공격속도  
		_item.criticalPersent = 30.0f;	// 크리율
		_item.moveMentSpeed = -20.0f;		// 이동속도
		_item.addMaxHp = 20;				// 최대HP;
		_item.price = 12000;				// 가격
	}

}



















void Item::setGun(const char * weaponName, int value)
{
	char str[128];
	for (int i = 0; i < 3; i++)
	{
		sprintf_s(str, "%s%d%d", weaponName, value, i);
		_item.image[i] = IMAGEMANAGER->findImage(str);

		if (value == 4 && i == 2) // 착용 이미지 일때
		{
			_item.isFrame = true;
			if (_item.isFrame)
			{
				_item.rc[i] = RectMake(_item.x + i * 100, _item.y, _item.image[i]->getFrameWidth(),
					_item.image[i]->getFrameHeight());
			}
			else
			{
				_item.isFrame = false;
			}
		}
		else
		{
			_item.rc[i] = RectMake(_item.x + i * 100, _item.y, _item.image[i]->getWidth(),
				_item.image[i]->getHeight());
		}

	}

	if (value == 1) // 기본총
	{
		_item.grade = NORMAL;		// 노말등급
		_item.minimumAtt = 8;		// 최소 데미지 8
		_item.MaxAtt = 10;		// 최대 데미지 10
		_item.fixedDamage = 8;	// 고정데미지 8
		_item.attackSpeed = 1.3f;	// 공격속도  
		_item.price = 500;		// 가격

	}

	if (value == 2) // 데들리건
	{
		_item.grade = RARE;				// 레어등급
		_item.minimumAtt = 20;			// 최소 데미지 20
		_item.MaxAtt = 30;				// 최대 데미지 30
		_item.fixedDamage = 20;			// 고정데미지 20
		_item.attackSpeed = 3.2f;			// 공격속도  
		_item.criticalPersent = 30.0f;	// 크리율
		_item.price = 7000;				// 가격

	}

	if (value == 3) // 플레임건
	{
		_item.grade = RARE;				// 레어 등급
		_item.minimumAtt = 40;			// 최소 데미지 40
		_item.MaxAtt = 50;				// 최대 데미지 50
		_item.fixedDamage = 8;			// 고정데미지 40
		_item.attackSpeed = 1.3f;			// 공격속도  
		_item.criticalPersent = 10.0f;	// 크리율
		_item.price = 7000;				// 가격


	}

	if (value == 4) // 레일건
	{
		_item.grade = LEGENDARY;			// 전설 등급
		_item.minimumAtt = 40;			// 최소 데미지 40
		_item.MaxAtt = 70;				// 최대 데미지 70
		_item.fixedDamage = 8;			// 고정데미지 40
		_item.attackSpeed = 4.3f;			// 공격속도  
		_item.criticalPersent = 30.0f;	// 크리율
		_item.evasionPersent = 8.0f;		// 회피율
		_item.addMaxHp = 20;				// 최대HP;
		_item.price = 12000;				// 가격
	}


}


















void Item::setBow(const char * weaponName, int value)
{
	char str[128];
	for (int i = 0; i < 3; i++)
	{
		sprintf_s(str, "%s%d%d", weaponName, value, i);
		_item.image[i] = IMAGEMANAGER->findImage(str);

		if (value == 1 && i == 2 || value == 2 && i == 2 || value == 3 && i == 2) // 착용 이미지 일때
		{
			_item.isFrame = true;
			if (_item.isFrame)
			{
				_item.rc[i] = RectMake(_item.x + i * 100, _item.y, _item.image[i]->getFrameWidth(),
					_item.image[i]->getFrameHeight());
			}
			else
			{
				_item.isFrame = false;
			}
		}
		else
		{
			_item.rc[i] = RectMake(_item.x + i * 100, _item.y, _item.image[i]->getWidth(),
				_item.image[i]->getHeight());
		}
	}

	if (value == 1) // 크로스보우
	{
		_item.grade = NORMAL;		// 노말등급
		_item.minimumAtt = 10;	// 최소 데미지 10
		_item.MaxAtt = 15;		// 최대 데미지 15
		_item.fixedDamage = 8;	// 고정데미지 10
		_item.attackSpeed = 3.3f;	// 공격속도  
		_item.price = 1500;		// 가격

	}

	if (value == 2) // 다크보우
	{
		_item.grade = RARE;				// 레어등급
		_item.minimumAtt = 20;			// 최소 데미지 20
		_item.MaxAtt = 30;				// 최대 데미지 30
		_item.fixedDamage = 10;			// 고정데미지 20
		_item.attackSpeed = 4.2f;			// 공격속도  
		_item.criticalPersent = 30.0f;	// 크리율
		_item.price = 5000;				// 가격

	}

	if (value == 3) // 라이트브링거보우
	{
		_item.grade = LEGENDARY;			// 전설 등급
		_item.minimumAtt = 45;			// 최소 데미지 45
		_item.MaxAtt = 60;				// 최대 데미지 60
		_item.fixedDamage = 8;			// 고정데미지 45
		_item.attackSpeed = 2.3f;			// 공격속도  
		_item.criticalPersent = 30.0f;	// 크리율
		_item.evasionPersent = 1.0f;		// 회피율
		_item.addMaxHp = 20;				// 최대체력 증가
		_item.price = 12000;				// 가격


	}


}












void Item::setArmor(const char * ArmorName, int value)
{
	char str[128];
	for (int i = 0; i < 2; i++)
	{
		sprintf_s(str, "%s%d%d", ArmorName, value, i);
		_item.image[i] = IMAGEMANAGER->findImage(str);
		_item.rc[i] = RectMakeCenter(_item.x + i * 100, _item.y, _item.image[i]->getWidth(),
			_item.image[i]->getHeight());
	}

	if (value == 1) //헝겊 갑옷
	{
		_item.grade = NORMAL;				// 아이템 등급
		_item.def = 3;						// 방어력
		_item.price = 700;					// 가격

	}

	if (value == 2) // 가죽갑옷
	{
		_item.grade = NORMAL;				// 아이템 등급
		_item.def = 5;						// 방어력
		_item.price = 900;					// 가격
	}

	if (value == 3) // 소가죽 갑옷
	{
		_item.grade = NORMAL;				// 아이템 등급
		_item.def = 8;						// 방어력
		_item.price = 1200;				// 가격
	}

	if (value == 4) // 체인아머
	{
		_item.grade = NORMAL;				// 아이템 등급
		_item.def = 12;					// 방어력
		_item.price = 1500;				// 가격
	}
}













void Item::setShield(const char * ShieldName, int value)
{
	char str[128];
	for (int i = 0; i < 3; i++)
	{
		sprintf_s(str, "%s%d%d", ShieldName, value, i);
		_item.image[i] = IMAGEMANAGER->findImage(str);
		_item.rc[i] = RectMake(_item.x + i * 100, _item.y, _item.image[i]->getWidth(),
			_item.image[i]->getHeight());

	}

	if (value == 1)
	{
		_item.grade = NORMAL;	// 방패 등급
		_item.def = 10;		// 방어력
		_item.price = 1500;	// 가격
	}

	if (value == 2)
	{
		_item.grade = RARE;			// 방패 등급
		_item.def = 30;				// 방어력
		_item.addMaxHp = 100;			// 체력증가
		_item.evasionPersent = 10.0f; // 회피율
		_item.dashPower = 50.0f;		// 대쉬공격 증가
	}
}












void Item::setEquip(const char * secondEquipmentName, int value)
{
	char str[128];

	if (value == 1 || value == 2)
	{
		for (int i = 0; i < 2; i++)
		{
			{
				sprintf_s(str, "%s%d%d", secondEquipmentName, value, i);
				_item.image[i] = IMAGEMANAGER->findImage(str);
				_item.rc[i] = RectMake(_item.x + i * 100, _item.y, _item.image[i]->getWidth(),
					_item.image[i]->getHeight());
			}
		}
	}

	if (value == 3 || value == 4)
	{
		for (int i = 0; i < 3; i++)
		{
			sprintf_s(str, "%s%d%d", secondEquipmentName, value, i);
			_item.image[i] = IMAGEMANAGER->findImage(str);
			if (i == 2) // 착용 이미지 일때
			{
				_item.isFrame = true;
				if (_item.isFrame)
				{
					if (i == 2)
					{
						_item.rc[i] = RectMakeCenter(_item.x + i * 100, _item.y, _item.image[i]->getFrameWidth(),
							_item.image[i]->getFrameHeight());
					}
					else
					{
						_item.rc[i] = RectMakeCenter(_item.x + i * 100, _item.y, _item.image[i]->getWidth(),
							_item.image[i]->getHeight());
					}
				}
			}
			else
			{
				_item.rc[i] = RectMakeCenter(_item.x + i * 100, _item.y, _item.image[i]->getWidth(),
					_item.image[i]->getHeight());
			}
		}
	}

	if (value == 1) // 블레스 
	{
		_item.grade = RARE;				// 레어등급
		_item.attackSpeed = 3.3f;			// 공격속도  
		_item.evasionPersent = 3.0f;		// 회피율
		_item.ad = 5;						// 공격력
		_item.price = 7000;				// 가격

	}

	if (value == 2) // 블러드음료
	{
		_item.grade = RARE;				// 무기는 노말
		_item.attackSpeed = 3.3f;			// 공격속도  
		_item.criticalPersent = 3.0f;		// 크리율
		_item.evasionPersent = 3.0f;		// 회피율
		_item.price = 7000;				// 가격


	}

	if (value == 3) // 날개
	{
		_item.grade = LEGENDARY;			// 전설 등급
		_item.attackSpeed = 3.3f;			// 공격속도  
		_item.criticalPersent = 30.0f;	// 크리율
		_item.evasionPersent = 10.0f;		// 회피율
		_item.addMaxHp = 30;				// 최대HP;
		_item.moveMentSpeed = 30.0f;		// 이동속도
		_item.price = 15000;				// 가격
	}

	if (value == 4) // 호랑이기운
	{

		_item.grade = LEGENDARY;			// 전설등급
		_item.attackSpeed = 5.3f;			// 공격속도  
		_item.criticalPersent = 50.0f;	// 크리율
		_item.evasionPersent = 30.0f;		// 회피율
		_item.ad = 20;					// 공격력
		_item.def = 20;					// 방어력
		_item.moveMentSpeed = 30.0f;		// 이동속도
		_item.addMaxHp = 50;				// 최대HP
		_item.price = 20000;				// 가격
	}

}












void Item::setAccessory(const char * AccessoryName, int value)
{
	char str[128];
	for (int i = 0; i < 2; i++)
	{
		sprintf_s(str, "%s%d%d", AccessoryName, value, i);
		_item.image[i] = IMAGEMANAGER->findImage(str);
		_item.rc[i] = RectMakeCenter(_item.x + i * 100, _item.y, _item.image[i]->getWidth(),
			_item.image[i]->getHeight());
	}

	if (value == 1) // 블러드스톤링
	{
		_item.grade = NORMAL;				// 아이템 등급
		_item.def = 3;						// 방어력
		_item.addMaxHp = 5;				// 체력	
		_item.price = 1500;				// 가격

	}

	if (value == 2) // 아뮬렛
	{
		_item.grade = RARE;				// 아이템 등급
		_item.attackSpeed = 5.0f;			// 공속
		_item.evasionPersent = 8.0f;		// 회피율 
		_item.price = 3000;				// 가격
	}

	if (value == 3) // 프로스트 목걸이
	{
		_item.grade = RARE;				// 아이템 등급
		_item.attackSpeed = 5.0f;			// 공속
		_item.criticalPersent = 8.0f;		// 크리율
		_item.price = 3000;				// 가격
	}

	if (value == 4) // 게르베라 링
	{
		_item.grade = RARE;				// 아이템 등급
		_item.def = 6;						// 방어력
		_item.addMaxHp = 10;				// hp증가
		_item.price = 3000;				// 가격
	}
}





void Item::setFood(const char * FoodName, int value)
{
	char str[128];
	for (int i = 0; i < 3; i++)
	{
		sprintf_s(str, "%s%d%d", FoodName, value, i);
		_item.image[i] = IMAGEMANAGER->findImage(str);
		_item.rc[i] = RectMake(_item.x + i * 300, _item.y, _item.image[i]->getWidth(),
			_item.image[i]->getHeight());

		if (value == 1 && i == 0)
		{
			_item.addMaxHp = 4;				// 최대체력 증가
			_item.hpRecovery = 4.0f;		// 체력회복
			_item.ad = 4.0f;				// 공격력 증가.
			_item.attackSpeed = 4.0f;		// 공속증가
			_item.price = 250;				// 음식 가격
		}

		if (value == 1 && i == 1)
		{
			_item.addMaxHp = 5;				// 최대체력 증가
			_item.hpRecovery = 5.0f;		// 체력회복
			_item.criticalPersent = 5.0f;	// 크리율 증가
			_item.evasionPersent = 5.0f;	// 회피율 증가
			_item.price = 300;				// 음식 가격
		}

		if (value == 1 && i == 2)
		{
			_item.addMaxHp = 6;				// 최대체력 증가
			_item.hpRecovery = 6.0f;		// 체력회복
			_item.attackSpeed = 6.0f;		// 공속증가
			_item.moveMentSpeed = 6.0f;		// 이동속도 증가
			_item.price = 350;				// 음식 가격
		}

		if (value == 2 && i == 0)
		{
			_item.addMaxHp = 7;				// 최대체력 증가
			_item.hpRecovery = 7.0f;		// 체력회복
			_item.evasionPersent = 7.0f;	// 회피율 증가
			_item.moveMentSpeed = 7.0f;		// 이동속도 증가
			_item.price = 400;				// 음식 가격
		}
		if (value == 2 && i == 1)
		{
			_item.addMaxHp = 8;				// 최대체력 증가
			_item.hpRecovery = 8.0f;		// 체력회복
			_item.ad = 8.0f;				// 공격력 증가.
			_item.attackSpeed = 8.0f;		// 공속증가
			_item.criticalPersent = 8.0f;	// 크리율 증가
			_item.price = 450;				// 음식 가격
		}
		if (value == 2 && i == 2)
		{
			_item.addMaxHp = 9;				// 최대체력 증가
			_item.hpRecovery = 9.0f;		// 체력회복
			_item.ad = 9.0f;				// 공격력 증가.
			_item.attackSpeed = 9.0f;		// 공속증가
			_item.evasionPersent = 9.0f;	// 회피율 증가
			_item.price = 500;				// 음식 가격
		}
		if (value == 3 && i == 0)
		{
			_item.addMaxHp = 10;			// 최대체력 증가
			_item.hpRecovery = 10.0f;		// 체력회복
			_item.ad = 10.0f;				// 공격력 증가.
			_item.attackSpeed = 10.0f;		// 공속증가
			_item.moveMentSpeed = 10.0f;	// 이동속도 증가
			_item.price = 550;				// 음식 가격
		}
		if (value == 3 && i == 1)
		{
			_item.addMaxHp = 10;			// 최대체력 증가
			_item.hpRecovery = 14.0f;		// 체력회복
			_item.ad = 10.0f;				// 공격력 증가.
			_item.attackSpeed = 10.0f;		// 공속증가
			_item.price = 600;				// 음식 가격
		}
		if (value == 3 && i == 2)
		{
			_item.addMaxHp = 10;			// 최대체력 증가
			_item.hpRecovery = 10.0f;		// 체력회복
			_item.criticalPersent = 20.0f;	// 크리율 증가
			_item.evasionPersent = 20.0f;	// 회피율 증가
			_item.moveMentSpeed = 20.0f;	// 이동속도 증가
			_item.price = 650;				// 음식 가격
		}
		if (value == 4 && i == 0)
		{
			_item.addMaxHp = 10;			// 최대체력 증가
			_item.hpRecovery = 10.0f;		// 체력회복
			_item.ad = 5.0f;				// 공격력 증가.
			_item.attackSpeed = 5.0f;		// 공속증가
			_item.criticalPersent = 5.0f;	// 크리율 증가
			_item.evasionPersent = 5.0f;	// 회피율 증가
			_item.moveMentSpeed = 5.0f;		// 이동속도 증가
			_item.price = 700;				// 음식 가격
		}
		if (value == 4 && i == 1)
		{
			_item.addMaxHp = 10;			// 최대체력 증가
			_item.hpRecovery = 10.0f;		// 체력회복
			_item.ad = 5.0f;				// 공격력 증가.
			_item.attackSpeed = 5.0f;		// 공속증가
			_item.criticalPersent = 5.0f;	// 크리율 증가
			_item.evasionPersent = 5.0f;	// 회피율 증가
			_item.moveMentSpeed = 5.0f;		// 이동속도 증가
			_item.price = 750;				// 음식 가격
		}
		if (value == 4 && i == 2)
		{
			_item.addMaxHp = 10;			// 최대체력 증가
			_item.hpRecovery = 10.0f;		// 체력회복
			_item.ad = 5.0f;				// 공격력 증가.
			_item.attackSpeed = 5.0f;		// 공속증가
			_item.criticalPersent = 5.0f;	// 크리율 증가
			_item.evasionPersent = 5.0f;	// 회피율 증가
			_item.moveMentSpeed = 5.0f;		// 이동속도 증가
			_item.price = 800;				// 음식 가격
		}
	}
}

