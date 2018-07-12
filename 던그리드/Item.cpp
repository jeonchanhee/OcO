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


void Item::render() // �������� ����
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





void Item::CreateItem(ITEMTYPE type, const char * itemName, int value) // ������ ����
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

	

	if (value == 1) // �⺻����
	{
		_item.grade = NORMAL;		// �븻���
		_item.minimumAtt = 8;		// �ּ� ������ 8
		_item.MaxAtt = 10;		// �ִ� ������ 10
		_item.fixedDamage = 8;	// ���������� 8
		_item.attackSpeed = 3.3f;	// ���ݼӵ�  
		_item.sellBan = true;		// �Ǹű���

	}

	if (value == 2) // ���󸶻�
	{
		_item.grade = RARE;				// ������
		_item.minimumAtt = 20;			// �ּ� ������ 10
		_item.MaxAtt = 30;				// �ִ� ������ 15
		_item.fixedDamage = 10;			// ���������� 10
		_item.attackSpeed = 5.2f;			// ���ݼӵ�  
		_item.criticalPersent = 30.0f;	// ũ����
		_item.price = 7000;				// ����

	}

	if (value == 3) // ȭ�� �л���
	{
		_item.grade = RARE;				// ����� �븻
		_item.minimumAtt = 30;			// �ּ� ������ 30
		_item.MaxAtt = 40;				// �ִ� ������ 40
		_item.fixedDamage = 8;			// ���������� 30
		_item.attackSpeed = 3.3f;			// ���ݼӵ�  
		_item.criticalPersent = 30.0f;	// ũ����
		_item.evasionPersent = 3.0f;		// ȸ����
		_item.price = 7000;				// ����


	}

	if (value == 4) // ����
	{
		_item.grade = LEGENDARY;			// ���� ���
		_item.minimumAtt = 40;			// �ּ� ������ 40
		_item.MaxAtt = 70;				// �ִ� ������ 50
		_item.fixedDamage = 8;			// ���������� 40
		_item.attackSpeed = 2.3f;			// ���ݼӵ�  
		_item.criticalPersent = 30.0f;	// ũ����
		_item.evasionPersent = 8.0f;		// ȸ����
		_item.addMaxHp = 20;				// �ִ�HP;
		_item.price = 12000;				// ����
	}

	if (value == 5) // �ڽ���
	{
		_item.grade = LEGENDARY;			// �������
		_item.minimumAtt = 30;			// �ּ� ������ 30
		_item.MaxAtt = 55;				// �ִ� ������ 45
		_item.fixedDamage = 30;			// ���������� 30
		_item.attackSpeed = 3.3f;			// ���ݼӵ�  
		_item.criticalPersent = 30.0f;	// ũ����
		_item.evasionPersent = 5.0f;		// ȸ����
		_item.addMaxHp = 10;				// �ִ�HP
		_item.price = 15000;				// ����

	}

	if (value == 6) // �ڽ���
	{
		_item.grade = LEGENDARY;			// �������
		_item.minimumAtt = 30;			// �ּ� ������ 30
		_item.MaxAtt = 55;				// �ִ� ������ 45
		_item.fixedDamage = 30;			// ���������� 30
		_item.attackSpeed = 3.3f;			// ���ݼӵ�  
		_item.criticalPersent = 30.0f;	// ũ����
		_item.evasionPersent = 5.0f;		// ȸ����
		_item.addMaxHp = 10;				// �ִ�HP
		_item.price = 15000;				// ����
	}

	if (value == 7) // �ڽ���
	{
		_item.grade = LEGENDARY;			// �������
		_item.minimumAtt = 30;			// �ּ� ������ 30
		_item.MaxAtt = 55;				// �ִ� ������ 45
		_item.fixedDamage = 30;			// ���������� 30
		_item.attackSpeed = 3.3f;			// ���ݼӵ�  
		_item.criticalPersent = 30.0f;	// ũ����
		_item.evasionPersent = 5.0f;		// ȸ����
		_item.addMaxHp = 10;				// �ִ�HP
		_item.price = 15000;				// ����
	}

	if (value == 8) // �ڽ���
	{
		_item.grade = LEGENDARY;			// �������
		_item.minimumAtt = 30;			// �ּ� ������ 30
		_item.MaxAtt = 55;				// �ִ� ������ 45
		_item.fixedDamage = 30;			// ���������� 30
		_item.attackSpeed = 3.3f;			// ���ݼӵ�  
		_item.criticalPersent = 30.0f;	// ũ����
		_item.evasionPersent = 5.0f;		// ȸ����
		_item.addMaxHp = 10;				// �ִ�HP
		_item.price = 15000;				// ����
	}

	if (value == 9) // �ڽ���
	{
		_item.grade = LEGENDARY;			// �������
		_item.minimumAtt = 30;			// �ּ� ������ 30
		_item.MaxAtt = 55;				// �ִ� ������ 45
		_item.fixedDamage = 30;			// ���������� 30
		_item.attackSpeed = 3.3f;			// ���ݼӵ�  
		_item.criticalPersent = 30.0f;	// ũ����
		_item.evasionPersent = 5.0f;		// ȸ����
		_item.addMaxHp = 10;				// �ִ�HP
		_item.price = 15000;				// ����
	}

	if (value == 10) // �ڽ���
	{
		_item.grade = LEGENDARY;			// �������
		_item.minimumAtt = 30;			// �ּ� ������ 30
		_item.MaxAtt = 55;				// �ִ� ������ 45
		_item.fixedDamage = 30;			// ���������� 30
		_item.attackSpeed = 3.3f;			// ���ݼӵ�  
		_item.criticalPersent = 30.0f;	// ũ����
		_item.evasionPersent = 5.0f;		// ȸ����
		_item.addMaxHp = 10;				// �ִ�HP
		_item.price = 15000;				// ����
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

	if (value == 1) // ������ ��ġ
	{
		_item.grade = NORMAL;				// �븻
		_item.minimumAtt = 15;			// �ּ� ������ 15
		_item.MaxAtt = 20;				// �ִ� ������ 20
		_item.fixedDamage = 15;			// ���������� 15
		_item.attackSpeed = 1.3f;			// ���ݼӵ�  
		_item.moveMentSpeed = -20.0f;		// �̵��ӵ�
		_item.addMaxHp = 5;				// �ִ�HP;
		_item.price = 1000;				// ����
	}

	if (value == 2) //�巡�� �ظ�
	{
		_item.grade = RARE;				// ����
		_item.minimumAtt = 40;			// �ּ� ������ 40
		_item.MaxAtt = 50;				// �ִ� ������ 50
		_item.fixedDamage = 40;			// ���������� 40
		_item.attackSpeed = 1.3f;			// ���ݼӵ�  
		_item.criticalPersent = 30.0f;	// ũ����
		_item.moveMentSpeed = -20.0f;		// �̵��ӵ�
		_item.addMaxHp = 20;				// �ִ�HP;
		_item.price = 12000;				// ����
	}

}



















void Item::setGun(const char * weaponName, int value)
{
	char str[128];
	for (int i = 0; i < 3; i++)
	{
		sprintf_s(str, "%s%d%d", weaponName, value, i);
		_item.image[i] = IMAGEMANAGER->findImage(str);

		if (value == 4 && i == 2) // ���� �̹��� �϶�
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

	if (value == 1) // �⺻��
	{
		_item.grade = NORMAL;		// �븻���
		_item.minimumAtt = 8;		// �ּ� ������ 8
		_item.MaxAtt = 10;		// �ִ� ������ 10
		_item.fixedDamage = 8;	// ���������� 8
		_item.attackSpeed = 1.3f;	// ���ݼӵ�  
		_item.price = 500;		// ����

	}

	if (value == 2) // ���鸮��
	{
		_item.grade = RARE;				// ������
		_item.minimumAtt = 20;			// �ּ� ������ 20
		_item.MaxAtt = 30;				// �ִ� ������ 30
		_item.fixedDamage = 20;			// ���������� 20
		_item.attackSpeed = 3.2f;			// ���ݼӵ�  
		_item.criticalPersent = 30.0f;	// ũ����
		_item.price = 7000;				// ����

	}

	if (value == 3) // �÷��Ӱ�
	{
		_item.grade = RARE;				// ���� ���
		_item.minimumAtt = 40;			// �ּ� ������ 40
		_item.MaxAtt = 50;				// �ִ� ������ 50
		_item.fixedDamage = 8;			// ���������� 40
		_item.attackSpeed = 1.3f;			// ���ݼӵ�  
		_item.criticalPersent = 10.0f;	// ũ����
		_item.price = 7000;				// ����


	}

	if (value == 4) // ���ϰ�
	{
		_item.grade = LEGENDARY;			// ���� ���
		_item.minimumAtt = 40;			// �ּ� ������ 40
		_item.MaxAtt = 70;				// �ִ� ������ 70
		_item.fixedDamage = 8;			// ���������� 40
		_item.attackSpeed = 4.3f;			// ���ݼӵ�  
		_item.criticalPersent = 30.0f;	// ũ����
		_item.evasionPersent = 8.0f;		// ȸ����
		_item.addMaxHp = 20;				// �ִ�HP;
		_item.price = 12000;				// ����
	}


}


















void Item::setBow(const char * weaponName, int value)
{
	char str[128];
	for (int i = 0; i < 3; i++)
	{
		sprintf_s(str, "%s%d%d", weaponName, value, i);
		_item.image[i] = IMAGEMANAGER->findImage(str);

		if (value == 1 && i == 2 || value == 2 && i == 2 || value == 3 && i == 2) // ���� �̹��� �϶�
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

	if (value == 1) // ũ�ν�����
	{
		_item.grade = NORMAL;		// �븻���
		_item.minimumAtt = 10;	// �ּ� ������ 10
		_item.MaxAtt = 15;		// �ִ� ������ 15
		_item.fixedDamage = 8;	// ���������� 10
		_item.attackSpeed = 3.3f;	// ���ݼӵ�  
		_item.price = 1500;		// ����

	}

	if (value == 2) // ��ũ����
	{
		_item.grade = RARE;				// ������
		_item.minimumAtt = 20;			// �ּ� ������ 20
		_item.MaxAtt = 30;				// �ִ� ������ 30
		_item.fixedDamage = 10;			// ���������� 20
		_item.attackSpeed = 4.2f;			// ���ݼӵ�  
		_item.criticalPersent = 30.0f;	// ũ����
		_item.price = 5000;				// ����

	}

	if (value == 3) // ����Ʈ�긵�ź���
	{
		_item.grade = LEGENDARY;			// ���� ���
		_item.minimumAtt = 45;			// �ּ� ������ 45
		_item.MaxAtt = 60;				// �ִ� ������ 60
		_item.fixedDamage = 8;			// ���������� 45
		_item.attackSpeed = 2.3f;			// ���ݼӵ�  
		_item.criticalPersent = 30.0f;	// ũ����
		_item.evasionPersent = 1.0f;		// ȸ����
		_item.addMaxHp = 20;				// �ִ�ü�� ����
		_item.price = 12000;				// ����


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

	if (value == 1) //��� ����
	{
		_item.grade = NORMAL;				// ������ ���
		_item.def = 3;						// ����
		_item.price = 700;					// ����

	}

	if (value == 2) // ���װ���
	{
		_item.grade = NORMAL;				// ������ ���
		_item.def = 5;						// ����
		_item.price = 900;					// ����
	}

	if (value == 3) // �Ұ��� ����
	{
		_item.grade = NORMAL;				// ������ ���
		_item.def = 8;						// ����
		_item.price = 1200;				// ����
	}

	if (value == 4) // ü�ξƸ�
	{
		_item.grade = NORMAL;				// ������ ���
		_item.def = 12;					// ����
		_item.price = 1500;				// ����
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
		_item.grade = NORMAL;	// ���� ���
		_item.def = 10;		// ����
		_item.price = 1500;	// ����
	}

	if (value == 2)
	{
		_item.grade = RARE;			// ���� ���
		_item.def = 30;				// ����
		_item.addMaxHp = 100;			// ü������
		_item.evasionPersent = 10.0f; // ȸ����
		_item.dashPower = 50.0f;		// �뽬���� ����
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
			if (i == 2) // ���� �̹��� �϶�
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

	if (value == 1) // ���� 
	{
		_item.grade = RARE;				// ������
		_item.attackSpeed = 3.3f;			// ���ݼӵ�  
		_item.evasionPersent = 3.0f;		// ȸ����
		_item.ad = 5;						// ���ݷ�
		_item.price = 7000;				// ����

	}

	if (value == 2) // ��������
	{
		_item.grade = RARE;				// ����� �븻
		_item.attackSpeed = 3.3f;			// ���ݼӵ�  
		_item.criticalPersent = 3.0f;		// ũ����
		_item.evasionPersent = 3.0f;		// ȸ����
		_item.price = 7000;				// ����


	}

	if (value == 3) // ����
	{
		_item.grade = LEGENDARY;			// ���� ���
		_item.attackSpeed = 3.3f;			// ���ݼӵ�  
		_item.criticalPersent = 30.0f;	// ũ����
		_item.evasionPersent = 10.0f;		// ȸ����
		_item.addMaxHp = 30;				// �ִ�HP;
		_item.moveMentSpeed = 30.0f;		// �̵��ӵ�
		_item.price = 15000;				// ����
	}

	if (value == 4) // ȣ���̱��
	{

		_item.grade = LEGENDARY;			// �������
		_item.attackSpeed = 5.3f;			// ���ݼӵ�  
		_item.criticalPersent = 50.0f;	// ũ����
		_item.evasionPersent = 30.0f;		// ȸ����
		_item.ad = 20;					// ���ݷ�
		_item.def = 20;					// ����
		_item.moveMentSpeed = 30.0f;		// �̵��ӵ�
		_item.addMaxHp = 50;				// �ִ�HP
		_item.price = 20000;				// ����
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

	if (value == 1) // ���彺�渵
	{
		_item.grade = NORMAL;				// ������ ���
		_item.def = 3;						// ����
		_item.addMaxHp = 5;				// ü��	
		_item.price = 1500;				// ����

	}

	if (value == 2) // �ƹķ�
	{
		_item.grade = RARE;				// ������ ���
		_item.attackSpeed = 5.0f;			// ����
		_item.evasionPersent = 8.0f;		// ȸ���� 
		_item.price = 3000;				// ����
	}

	if (value == 3) // ���ν�Ʈ �����
	{
		_item.grade = RARE;				// ������ ���
		_item.attackSpeed = 5.0f;			// ����
		_item.criticalPersent = 8.0f;		// ũ����
		_item.price = 3000;				// ����
	}

	if (value == 4) // �Ը����� ��
	{
		_item.grade = RARE;				// ������ ���
		_item.def = 6;						// ����
		_item.addMaxHp = 10;				// hp����
		_item.price = 3000;				// ����
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
			_item.addMaxHp = 4;				// �ִ�ü�� ����
			_item.hpRecovery = 4.0f;		// ü��ȸ��
			_item.ad = 4.0f;				// ���ݷ� ����.
			_item.attackSpeed = 4.0f;		// ��������
			_item.price = 250;				// ���� ����
		}

		if (value == 1 && i == 1)
		{
			_item.addMaxHp = 5;				// �ִ�ü�� ����
			_item.hpRecovery = 5.0f;		// ü��ȸ��
			_item.criticalPersent = 5.0f;	// ũ���� ����
			_item.evasionPersent = 5.0f;	// ȸ���� ����
			_item.price = 300;				// ���� ����
		}

		if (value == 1 && i == 2)
		{
			_item.addMaxHp = 6;				// �ִ�ü�� ����
			_item.hpRecovery = 6.0f;		// ü��ȸ��
			_item.attackSpeed = 6.0f;		// ��������
			_item.moveMentSpeed = 6.0f;		// �̵��ӵ� ����
			_item.price = 350;				// ���� ����
		}

		if (value == 2 && i == 0)
		{
			_item.addMaxHp = 7;				// �ִ�ü�� ����
			_item.hpRecovery = 7.0f;		// ü��ȸ��
			_item.evasionPersent = 7.0f;	// ȸ���� ����
			_item.moveMentSpeed = 7.0f;		// �̵��ӵ� ����
			_item.price = 400;				// ���� ����
		}
		if (value == 2 && i == 1)
		{
			_item.addMaxHp = 8;				// �ִ�ü�� ����
			_item.hpRecovery = 8.0f;		// ü��ȸ��
			_item.ad = 8.0f;				// ���ݷ� ����.
			_item.attackSpeed = 8.0f;		// ��������
			_item.criticalPersent = 8.0f;	// ũ���� ����
			_item.price = 450;				// ���� ����
		}
		if (value == 2 && i == 2)
		{
			_item.addMaxHp = 9;				// �ִ�ü�� ����
			_item.hpRecovery = 9.0f;		// ü��ȸ��
			_item.ad = 9.0f;				// ���ݷ� ����.
			_item.attackSpeed = 9.0f;		// ��������
			_item.evasionPersent = 9.0f;	// ȸ���� ����
			_item.price = 500;				// ���� ����
		}
		if (value == 3 && i == 0)
		{
			_item.addMaxHp = 10;			// �ִ�ü�� ����
			_item.hpRecovery = 10.0f;		// ü��ȸ��
			_item.ad = 10.0f;				// ���ݷ� ����.
			_item.attackSpeed = 10.0f;		// ��������
			_item.moveMentSpeed = 10.0f;	// �̵��ӵ� ����
			_item.price = 550;				// ���� ����
		}
		if (value == 3 && i == 1)
		{
			_item.addMaxHp = 10;			// �ִ�ü�� ����
			_item.hpRecovery = 14.0f;		// ü��ȸ��
			_item.ad = 10.0f;				// ���ݷ� ����.
			_item.attackSpeed = 10.0f;		// ��������
			_item.price = 600;				// ���� ����
		}
		if (value == 3 && i == 2)
		{
			_item.addMaxHp = 10;			// �ִ�ü�� ����
			_item.hpRecovery = 10.0f;		// ü��ȸ��
			_item.criticalPersent = 20.0f;	// ũ���� ����
			_item.evasionPersent = 20.0f;	// ȸ���� ����
			_item.moveMentSpeed = 20.0f;	// �̵��ӵ� ����
			_item.price = 650;				// ���� ����
		}
		if (value == 4 && i == 0)
		{
			_item.addMaxHp = 10;			// �ִ�ü�� ����
			_item.hpRecovery = 10.0f;		// ü��ȸ��
			_item.ad = 5.0f;				// ���ݷ� ����.
			_item.attackSpeed = 5.0f;		// ��������
			_item.criticalPersent = 5.0f;	// ũ���� ����
			_item.evasionPersent = 5.0f;	// ȸ���� ����
			_item.moveMentSpeed = 5.0f;		// �̵��ӵ� ����
			_item.price = 700;				// ���� ����
		}
		if (value == 4 && i == 1)
		{
			_item.addMaxHp = 10;			// �ִ�ü�� ����
			_item.hpRecovery = 10.0f;		// ü��ȸ��
			_item.ad = 5.0f;				// ���ݷ� ����.
			_item.attackSpeed = 5.0f;		// ��������
			_item.criticalPersent = 5.0f;	// ũ���� ����
			_item.evasionPersent = 5.0f;	// ȸ���� ����
			_item.moveMentSpeed = 5.0f;		// �̵��ӵ� ����
			_item.price = 750;				// ���� ����
		}
		if (value == 4 && i == 2)
		{
			_item.addMaxHp = 10;			// �ִ�ü�� ����
			_item.hpRecovery = 10.0f;		// ü��ȸ��
			_item.ad = 5.0f;				// ���ݷ� ����.
			_item.attackSpeed = 5.0f;		// ��������
			_item.criticalPersent = 5.0f;	// ũ���� ����
			_item.evasionPersent = 5.0f;	// ȸ���� ����
			_item.moveMentSpeed = 5.0f;		// �̵��ӵ� ����
			_item.price = 800;				// ���� ����
		}
	}
}

