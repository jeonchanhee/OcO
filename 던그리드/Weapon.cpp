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

		if (value == 4 && i == 2 || value == 5 && i == 2) // ���� �̹��� �϶�
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

	if (value == 1) // �⺻����
	{
		_weapon.grade = NORMAL;		// �븻���
		_weapon.minimumAtt = 8;		// �ּ� ������ 8
		_weapon.MaxAtt = 10;		// �ִ� ������ 10
		_weapon.fixedDamage = 8;	// ���������� 8
		_weapon.attackSpeed = 3.3f;	// ���ݼӵ�  
		_weapon.sellBan = true;		// �Ǹű���

	}

	if (value == 2) // ���󸶻�
	{
		_weapon.grade = RARE;				// ������
		_weapon.minimumAtt = 20;			// �ּ� ������ 10
		_weapon.MaxAtt = 30;				// �ִ� ������ 15
		_weapon.fixedDamage = 10;			// ���������� 10
		_weapon.attackSpeed = 5.2f;			// ���ݼӵ�  
		_weapon.criticalPersent = 30.0f;	// ũ����
		_weapon.price = 7000;				// ����

	}

	if (value == 3) // ȭ�� �л���
	{
		_weapon.grade = RARE;				// ����� �븻
		_weapon.minimumAtt = 30;			// �ּ� ������ 30
		_weapon.MaxAtt = 40;				// �ִ� ������ 40
		_weapon.fixedDamage = 8;			// ���������� 30
		_weapon.attackSpeed = 3.3f;			// ���ݼӵ�  
		_weapon.criticalPersent = 30.0f;	// ũ����
		_weapon.evasionPersent = 3.0f;		// ȸ����
		_weapon.price = 7000;				// ����


	}

	if (value == 4) // ����
	{
		_weapon.grade = LEGENDARY;			// ���� ���
		_weapon.minimumAtt = 40;			// �ּ� ������ 40
		_weapon.MaxAtt = 70;				// �ִ� ������ 50
		_weapon.fixedDamage = 8;			// ���������� 40
		_weapon.attackSpeed = 2.3f;			// ���ݼӵ�  
		_weapon.criticalPersent = 30.0f;	// ũ����
		_weapon.evasionPersent = 8.0f;		// ȸ����
		_weapon.addMaxHp = 20;				// �ִ�HP;
		_weapon.price = 12000;				// ����
	}

	if (value == 5) // �ڽ���
	{
		_weapon.grade = LEGENDARY;			// �������
		_weapon.minimumAtt = 30;			// �ּ� ������ 30
		_weapon.MaxAtt = 55;				// �ִ� ������ 45
		_weapon.fixedDamage = 30;			// ���������� 30
		_weapon.attackSpeed = 3.3f;			// ���ݼӵ�  
		_weapon.criticalPersent = 30.0f;	// ũ����
		_weapon.evasionPersent = 5.0f;		// ȸ����
		_weapon.addMaxHp = 10;				// �ִ�HP
		_weapon.price = 15000;				// ����

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

	if (value == 1) // ������ ��ġ
	{
		_weapon.grade = NORMAL;				// �븻
		_weapon.minimumAtt = 15;			// �ּ� ������ 15
		_weapon.MaxAtt = 20;				// �ִ� ������ 20
		_weapon.fixedDamage = 15;			// ���������� 15
		_weapon.attackSpeed = 1.3f;			// ���ݼӵ�  
		_weapon.moveMentSpeed = -20.0f;		// �̵��ӵ�
		_weapon.addMaxHp = 5;				// �ִ�HP;
		_weapon.price = 1000;				// ����
	}

	if (value == 2) //�巡�� �ظ�
	{
		_weapon.grade = RARE;				// ����
		_weapon.minimumAtt = 40;			// �ּ� ������ 40
		_weapon.MaxAtt = 50;				// �ִ� ������ 50
		_weapon.fixedDamage = 40;			// ���������� 40
		_weapon.attackSpeed = 1.3f;			// ���ݼӵ�  
		_weapon.criticalPersent = 30.0f;	// ũ����
		_weapon.moveMentSpeed = -20.0f;		// �̵��ӵ�
		_weapon.addMaxHp = 20;				// �ִ�HP;
		_weapon.price = 12000;				// ����
	}
}




void Weapon::setGun(const char * weaponName, int value)
{
	char str[128];
	for (int i = 0; i < 3; i++)
	{
		sprintf_s(str, "%s%d%d", weaponName, value, i);
		_weapon.image[i] = IMAGEMANAGER->findImage(str);

		if (value == 4 && i == 2 ) // ���� �̹��� �϶�
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

	if (value == 1) // �⺻��
	{
		_weapon.grade = NORMAL;		// �븻���
		_weapon.minimumAtt = 8;		// �ּ� ������ 8
		_weapon.MaxAtt = 10;		// �ִ� ������ 10
		_weapon.fixedDamage = 8;	// ���������� 8
		_weapon.attackSpeed = 1.3f;	// ���ݼӵ�  
		_weapon.price = 500;		// ����

	}

	if (value == 2) // ���鸮��
	{
		_weapon.grade = RARE;				// ������
		_weapon.minimumAtt = 20;			// �ּ� ������ 20
		_weapon.MaxAtt = 30;				// �ִ� ������ 30
		_weapon.fixedDamage = 20;			// ���������� 20
		_weapon.attackSpeed = 3.2f;			// ���ݼӵ�  
		_weapon.criticalPersent = 30.0f;	// ũ����
		_weapon.price = 7000;				// ����

	}

	if (value == 3) // �÷��Ӱ�
	{
		_weapon.grade = RARE;				// ���� ���
		_weapon.minimumAtt = 40;			// �ּ� ������ 40
		_weapon.MaxAtt = 50;				// �ִ� ������ 50
		_weapon.fixedDamage = 8;			// ���������� 40
		_weapon.attackSpeed = 1.3f;			// ���ݼӵ�  
		_weapon.criticalPersent = 10.0f;	// ũ����
		_weapon.price = 7000;				// ����


	}

	if (value == 4) // ���ϰ�
	{
		_weapon.grade = LEGENDARY;			// ���� ���
		_weapon.minimumAtt = 40;			// �ּ� ������ 40
		_weapon.MaxAtt = 70;				// �ִ� ������ 70
		_weapon.fixedDamage = 8;			// ���������� 40
		_weapon.attackSpeed = 4.3f;			// ���ݼӵ�  
		_weapon.criticalPersent = 30.0f;	// ũ����
		_weapon.evasionPersent = 8.0f;		// ȸ����
		_weapon.addMaxHp = 20;				// �ִ�HP;
		_weapon.price = 12000;				// ����
	}

}




void Weapon::setBow(const char * weaponName, int value)
{
	char str[128];
	for (int i = 0; i < 3; i++)
	{
		sprintf_s(str, "%s%d%d", weaponName, value, i);
		_weapon.image[i] = IMAGEMANAGER->findImage(str);

		if (value == 1 && i == 2 || value == 2 && i == 2 || value == 3 && i == 2) // ���� �̹��� �϶�
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

	if (value == 1) // ũ�ν�����
	{
		_weapon.grade = NORMAL;		// �븻���
		_weapon.minimumAtt = 10;	// �ּ� ������ 10
		_weapon.MaxAtt = 15;		// �ִ� ������ 15
		_weapon.fixedDamage = 8;	// ���������� 10
		_weapon.attackSpeed = 3.3f;	// ���ݼӵ�  
		_weapon.price = 1500;		// ����

	}

	if (value == 2) // ��ũ����
	{
		_weapon.grade = RARE;				// ������
		_weapon.minimumAtt = 20;			// �ּ� ������ 20
		_weapon.MaxAtt = 30;				// �ִ� ������ 30
		_weapon.fixedDamage = 10;			// ���������� 20
		_weapon.attackSpeed = 4.2f;			// ���ݼӵ�  
		_weapon.criticalPersent = 30.0f;	// ũ����
		_weapon.price = 5000;				// ����

	}

	if (value == 3) // ����Ʈ�긵�ź���
	{
		_weapon.grade = LEGENDARY;			// ���� ���
		_weapon.minimumAtt = 45;			// �ּ� ������ 45
		_weapon.MaxAtt = 60;				// �ִ� ������ 60
		_weapon.fixedDamage = 8;			// ���������� 45
		_weapon.attackSpeed = 2.3f;			// ���ݼӵ�  
		_weapon.criticalPersent = 30.0f;	// ũ����
		_weapon.evasionPersent = 1.0f;		// ȸ����
		_weapon.addMaxHp = 20;				// �ִ�ü�� ����
		_weapon.price = 12000;				// ����


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
