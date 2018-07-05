#include "stdafx.h"
#include "Accessory.h"


Accessory::Accessory(){} Accessory::~Accessory(){}

HRESULT Accessory::init(POINT position)
{
	_accessory.x = position.x;
	_accessory.y = position.y;
	for (int i = 0; i < 3; i++)
	{
		_accessory.rc[i] = RectMakeCenter(_accessory.x, _accessory.y, _accessory.image[i]->getWidth(),
			_accessory.image[i]->getHeight());
	}

	return S_OK;
}

void Accessory::release()
{
}

void Accessory::update()
{
}

void Accessory::render()
{
	for (int i = 0; i < 3; i++)
	{
		_accessory.image[i]->render(DC, _accessory.rc[i].left, _accessory.rc[i].top);
	}
}

void Accessory::CreateAccessory(ITEMTYPE type, const char* ArmorName, int value, POINT position)
{
	switch (type)
	{
	case ARMOR:
		setAccessory(ArmorName, value);
		break;
	}

}

void Accessory::setAccessory(const char* ArmorName, int value)
{
	char str[128];
	for (int i = 0; i < 3; i++)
	{
		sprintf_s(str, "%s%d%d", ArmorName, value, i);
		_accessory.image[i] = IMAGEMANAGER->findImage(str);
	}

	if (value == 1) // 블러드스톤링
	{
		_accessory.grade = NORMAL;				// 아이템 등급
		_accessory.def = 3;						// 방어력
		_accessory.addMaxHp = 5;				// 체력	
		_accessory.price = 1500;				// 가격

	}

	if (value == 2) // 아뮬렛
	{
		_accessory.grade = RARE;				// 아이템 등급
		_accessory.attackSpeed = 5.0f;			// 공속
		_accessory.evasionPersent = 8.0f;		// 회피율 
		_accessory.price = 3000;				// 가격
	}

	if (value == 3) // 프로스트 목걸이
	{
		_accessory.grade = RARE;				// 아이템 등급
		_accessory.attackSpeed = 5.0f;			// 공속
		_accessory.criticalPersent = 8.0f;		// 크리율
		_accessory.price = 3000;				// 가격
	}

	if (value == 4) // 게르베라 링
	{
		_accessory.grade = RARE;				// 아이템 등급
		_accessory.def = 6;						// 방어력
		_accessory.addMaxHp = 10;				// hp증가
		_accessory.price = 3000;				// 가격
	}

}
