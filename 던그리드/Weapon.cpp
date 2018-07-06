#include "stdafx.h"
#include "Weapon.h"


Weapon::Weapon(){} Weapon::~Weapon(){}

HRESULT Weapon::init(ITEMTYPE type, const char* weaponName, int value, POINT position)
{
	_weapon.type = type;
	_weaponName = weaponName;
	_value = value;
	_weapon.x = position.x;
	_weapon.y = position.y;


	CreateWeapon(type, weaponName, value);

	_count = 0;


	return S_OK;
}

void Weapon::release()
{
}

void Weapon::update()
{
	_count++;

	if (_weapon.isFrame)
	{
		if (_count % 10 == 0)
		{
			if (_weapon.frameX >= _weapon.image[2]->getMaxFrameX()) _weapon.frameX = 0;
			_weapon.image[2]->setFrameX(_weapon.frameX);
			_weapon.frameX++;
			_count = 0;
		}
	}
}



void Weapon::CreateWeapon(ITEMTYPE type, const char* weaponName, int value)
{
	switch (type)
	{
	case SWORD:
		setSword(weaponName, value);
		break;
	case HAMMER:
		setHammer(weaponName, value);
		break;
	case GUN:
		setGun(weaponName, value);
		break;
	case BOW:
		setBow(weaponName, value);
		break;
	}

}

void Weapon::setSword(const char * weaponName, int value)
{
	char str[128];
	for (int i = 0; i < 3; i++)
	{
		sprintf_s(str, "%s%d%d", weaponName, value, i);
		_weapon.image[i] = IMAGEMANAGER->findImage(str);

		if (value == 4 && i == 2 || value == 5 && i == 2) // 착용 이미지 일때
		{
			_weapon.isFrame = true;
			if (_weapon.isFrame)
			{
				_weapon.rc[i] = RectMake(_weapon.x + i * 50, _weapon.y, _weapon.image[i]->getFrameWidth(),
					_weapon.image[i]->getFrameHeight());
			}
			else
			{
				_weapon.isFrame = false;
			}
		}
		else
		{
			_weapon.rc[i] = RectMake(_weapon.x + i * 50, _weapon.y, _weapon.image[i]->getWidth(),
				_weapon.image[i]->getHeight());
		}

	}

	if (value == 1) // 기본무기
	{
		_weapon.grade = NORMAL;		// 노말등급
		_weapon.minimumAtt = 8;		// 최소 데미지 8
		_weapon.MaxAtt = 10;		// 최대 데미지 10
		_weapon.fixedDamage = 8;	// 고정데미지 8
		_weapon.attackSpeed = 3.3f;	// 공격속도  
		_weapon.sellBan = true;		// 판매금지

	}

	if (value == 2) // 무라마사
	{
		_weapon.grade = RARE;				// 레어등급
		_weapon.minimumAtt = 20;			// 최소 데미지 10
		_weapon.MaxAtt = 30;				// 최대 데미지 15
		_weapon.fixedDamage = 10;			// 고정데미지 10
		_weapon.attackSpeed = 5.2f;			// 공격속도  
		_weapon.criticalPersent = 30.0f;	// 크리율
		_weapon.price = 7000;				// 가격

	}

	if (value == 3) // 화룡 학살자
	{
		_weapon.grade = RARE;				// 무기는 노말
		_weapon.minimumAtt = 30;			// 최소 데미지 30
		_weapon.MaxAtt = 40;				// 최대 데미지 40
		_weapon.fixedDamage = 8;			// 고정데미지 30
		_weapon.attackSpeed = 3.3f;			// 공격속도  
		_weapon.criticalPersent = 30.0f;	// 크리율
		_weapon.evasionPersent = 3.0f;		// 회피율
		_weapon.price = 7000;				// 가격


	}

	if (value == 4) // 데몬
	{
		_weapon.grade = LEGENDARY;			// 전설 등급
		_weapon.minimumAtt = 40;			// 최소 데미지 40
		_weapon.MaxAtt = 70;				// 최대 데미지 50
		_weapon.fixedDamage = 8;			// 고정데미지 40
		_weapon.attackSpeed = 2.3f;			// 공격속도  
		_weapon.criticalPersent = 30.0f;	// 크리율
		_weapon.evasionPersent = 8.0f;		// 회피율
		_weapon.addMaxHp = 20;				// 최대HP;
		_weapon.price = 12000;				// 가격
	}

	if (value == 5) // 코스모스
	{
		_weapon.grade = LEGENDARY;			// 전설등급
		_weapon.minimumAtt = 30;			// 최소 데미지 30
		_weapon.MaxAtt = 55;				// 최대 데미지 45
		_weapon.fixedDamage = 30;			// 고정데미지 30
		_weapon.attackSpeed = 3.3f;			// 공격속도  
		_weapon.criticalPersent = 30.0f;	// 크리율
		_weapon.evasionPersent = 5.0f;		// 회피율
		_weapon.addMaxHp = 10;				// 최대HP
		_weapon.price = 15000;				// 가격

	}



}


void Weapon::setHammer(const char * weaponName, int value)
{
	char str[128];
	for (int i = 0; i < 3; i++)
	{
		sprintf_s(str, "%s%d%d", weaponName, value, i);
		_weapon.image[i] = IMAGEMANAGER->findImage(str);
		_weapon.rc[i] = RectMake(_weapon.x, _weapon.y + i * 100, _weapon.image[i]->getWidth(),
			_weapon.image[i]->getHeight());

	}

	if (value == 1) // 조선족 망치
	{
		_weapon.grade = NORMAL;				// 노말
		_weapon.minimumAtt = 15;			// 최소 데미지 15
		_weapon.MaxAtt = 20;				// 최대 데미지 20
		_weapon.fixedDamage = 15;			// 고정데미지 15
		_weapon.attackSpeed = 1.3f;			// 공격속도  
		_weapon.moveMentSpeed = -20.0f;		// 이동속도
		_weapon.addMaxHp = 5;				// 최대HP;
		_weapon.price = 1000;				// 가격
	}

	if (value == 2) //드래곤 해머
	{
		_weapon.grade = RARE;				// 레어
		_weapon.minimumAtt = 40;			// 최소 데미지 40
		_weapon.MaxAtt = 50;				// 최대 데미지 50
		_weapon.fixedDamage = 40;			// 고정데미지 40
		_weapon.attackSpeed = 1.3f;			// 공격속도  
		_weapon.criticalPersent = 30.0f;	// 크리율
		_weapon.moveMentSpeed = -20.0f;		// 이동속도
		_weapon.addMaxHp = 20;				// 최대HP;
		_weapon.price = 12000;				// 가격
	}
}




void Weapon::setGun(const char * weaponName, int value)
{
	char str[128];
	for (int i = 0; i < 3; i++)
	{
		sprintf_s(str, "%s%d%d", weaponName, value, i);
		_weapon.image[i] = IMAGEMANAGER->findImage(str);

		if (value == 4 && i == 2 ) // 착용 이미지 일때
		{
			_weapon.isFrame = true;
			if (_weapon.isFrame)
			{
				_weapon.rc[i] = RectMake(_weapon.x + i * 50, _weapon.y, _weapon.image[i]->getFrameWidth(),
					_weapon.image[i]->getFrameHeight());
			}
			else
			{
				_weapon.isFrame = false;
			}
		}
		else
		{
			_weapon.rc[i] = RectMake(_weapon.x + i * 50, _weapon.y, _weapon.image[i]->getWidth(),
				_weapon.image[i]->getHeight());
		}

	}

	if (value == 1) // 기본총
	{
		_weapon.grade = NORMAL;		// 노말등급
		_weapon.minimumAtt = 8;		// 최소 데미지 8
		_weapon.MaxAtt = 10;		// 최대 데미지 10
		_weapon.fixedDamage = 8;	// 고정데미지 8
		_weapon.attackSpeed = 1.3f;	// 공격속도  
		_weapon.price = 500;		// 가격

	}

	if (value == 2) // 데들리건
	{
		_weapon.grade = RARE;				// 레어등급
		_weapon.minimumAtt = 20;			// 최소 데미지 20
		_weapon.MaxAtt = 30;				// 최대 데미지 30
		_weapon.fixedDamage = 20;			// 고정데미지 20
		_weapon.attackSpeed = 3.2f;			// 공격속도  
		_weapon.criticalPersent = 30.0f;	// 크리율
		_weapon.price = 7000;				// 가격

	}

	if (value == 3) // 플레임건
	{
		_weapon.grade = RARE;				// 레어 등급
		_weapon.minimumAtt = 40;			// 최소 데미지 40
		_weapon.MaxAtt = 50;				// 최대 데미지 50
		_weapon.fixedDamage = 8;			// 고정데미지 40
		_weapon.attackSpeed = 1.3f;			// 공격속도  
		_weapon.criticalPersent = 10.0f;	// 크리율
		_weapon.price = 7000;				// 가격


	}

	if (value == 4) // 레일건
	{
		_weapon.grade = LEGENDARY;			// 전설 등급
		_weapon.minimumAtt = 40;			// 최소 데미지 40
		_weapon.MaxAtt = 70;				// 최대 데미지 70
		_weapon.fixedDamage = 8;			// 고정데미지 40
		_weapon.attackSpeed = 4.3f;			// 공격속도  
		_weapon.criticalPersent = 30.0f;	// 크리율
		_weapon.evasionPersent = 8.0f;		// 회피율
		_weapon.addMaxHp = 20;				// 최대HP;
		_weapon.price = 12000;				// 가격
	}

}




void Weapon::setBow(const char * weaponName, int value)
{
	char str[128];
	for (int i = 0; i < 3; i++)
	{
		sprintf_s(str, "%s%d%d", weaponName, value, i);
		_weapon.image[i] = IMAGEMANAGER->findImage(str);

		if (value == 1 && i == 2 || value == 2 && i == 2 || value == 3 && i == 2) // 착용 이미지 일때
		{
			_weapon.isFrame = true;
			if (_weapon.isFrame)
			{
				_weapon.rc[i] = RectMake(_weapon.x + i * 50, _weapon.y, _weapon.image[i]->getFrameWidth(),
					_weapon.image[i]->getFrameHeight());
			}
			else
			{
				_weapon.isFrame = false;
			}
		}
		else
		{
			_weapon.rc[i] = RectMake(_weapon.x + i * 50, _weapon.y, _weapon.image[i]->getWidth(),
				_weapon.image[i]->getHeight());
		}
	}

	if (value == 1) // 크로스보우
	{
		_weapon.grade = NORMAL;		// 노말등급
		_weapon.minimumAtt = 10;	// 최소 데미지 10
		_weapon.MaxAtt = 15;		// 최대 데미지 15
		_weapon.fixedDamage = 8;	// 고정데미지 10
		_weapon.attackSpeed = 3.3f;	// 공격속도  
		_weapon.price = 1500;		// 가격

	}

	if (value == 2) // 다크보우
	{
		_weapon.grade = RARE;				// 레어등급
		_weapon.minimumAtt = 20;			// 최소 데미지 20
		_weapon.MaxAtt = 30;				// 최대 데미지 30
		_weapon.fixedDamage = 10;			// 고정데미지 20
		_weapon.attackSpeed = 4.2f;			// 공격속도  
		_weapon.criticalPersent = 30.0f;	// 크리율
		_weapon.price = 5000;				// 가격

	}

	if (value == 3) // 라이트브링거보우
	{
		_weapon.grade = LEGENDARY;			// 전설 등급
		_weapon.minimumAtt = 45;			// 최소 데미지 45
		_weapon.MaxAtt = 60;				// 최대 데미지 60
		_weapon.fixedDamage = 8;			// 고정데미지 45
		_weapon.attackSpeed = 2.3f;			// 공격속도  
		_weapon.criticalPersent = 30.0f;	// 크리율
		_weapon.evasionPersent = 1.0f;		// 회피율
		_weapon.addMaxHp = 20;				// 최대체력 증가
		_weapon.price = 12000;				// 가격


	}

}




void Weapon::render()
{
	if (_weapon.isFrame)
	{
		for (int i = 0; i < 3; i++)
		{
			if (i == 2)
			{
				_weapon.image[i]->frameRender(DC, _weapon.rc[i].left, _weapon.rc[i].top, _weapon.frameX, _weapon.frameY);
			}
			else
			{
				_weapon.image[i]->render(DC, _weapon.rc[i].left, _weapon.rc[i].top);
			}
		}
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			_weapon.image[i]->render(DC, _weapon.rc[i].left, _weapon.rc[i].top);
		}
	}
}
