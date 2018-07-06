#include "stdafx.h"
#include "Shield.h"


Shield::Shield(){} Shield::~Shield(){}

HRESULT Shield::init(ITEMTYPE type, const char* ShieldName, int value, POINT position)
{
	_shield.type = type;
	_ShieldName = ShieldName;
	_value = value;
	_shield.x = position.x;
	_shield.y = position.y;

	CreateShield(type, ShieldName, value);
	return S_OK;
}

void Shield::release()
{
}

void Shield::update()
{

}

void Shield::CreateShield(ITEMTYPE type, const char * ShieldName, int value)
{



	switch (type)
	{
	case SHIELD:
		setShield(ShieldName, value);
		break;
	}
}

void Shield::setShield(const char * ShieldName, int value)
{
	char str[128];
	for (int i = 0; i < 3; i++)
	{
		sprintf_s(str, "%s%d%d", ShieldName, value, i);
		_shield.image[i] = IMAGEMANAGER->findImage(str);
		_shield.rc[i] = RectMake(_shield.x + i * 100, _shield.y + i * 100, _shield.image[i]->getWidth(),
			_shield.image[i]->getHeight());
		
	}

	if (value == 1)
	{
		_shield.grade = NORMAL;	// 방패 등급
		_shield.def = 10;		// 방어력
		_shield.price = 1500;	// 가격
	}

	if (value == 2)
	{
		_shield.grade = RARE;			// 방패 등급
		_shield.def = 30;				// 방어력
		_shield.addMaxHp = 100;			// 체력증가
		_shield.evasionPersent = 10.0f; // 회피율
		_shield.dashPower = 50.0f;		// 대쉬공격 증가
	}

	
}


void Shield::render()
{
	for (int i = 0; i < 3; i++)
	{
		_shield.image[i]->render(DC, _shield.rc[i].left, _shield.rc[i].top);
	}

}




