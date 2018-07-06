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
			if (i == 2) // ���� �̹��� �϶�
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

	if (value == 1) // ���� 
	{
		_second.grade = RARE;				// ������
		_second.attackSpeed = 3.3f;			// ���ݼӵ�  
		_second.evasionPersent = 3.0f;		// ȸ����
		_second.ad = 5;						// ���ݷ�
		_second.price = 7000;				// ����

	}

	if (value == 2) // ��������
	{
		_second.grade = RARE;				// ����� �븻
		_second.attackSpeed = 3.3f;			// ���ݼӵ�  
		_second.criticalPersent = 3.0f;		// ũ����
		_second.evasionPersent = 3.0f;		// ȸ����
		_second.price = 7000;				// ����


	}

	if (value == 3) // ����
	{
		_second.grade = LEGENDARY;			// ���� ���
		_second.attackSpeed = 3.3f;			// ���ݼӵ�  
		_second.criticalPersent = 30.0f;	// ũ����
		_second.evasionPersent = 10.0f;		// ȸ����
		_second.addMaxHp = 30;				// �ִ�HP;
		_second.moveMentSpeed = 30.0f;		// �̵��ӵ�
		_second.price = 15000;				// ����
	}

	if (value == 4) // ȣ���̱��
	{

		_second.grade = LEGENDARY;			// �������
		_second.attackSpeed = 5.3f;			// ���ݼӵ�  
		_second.criticalPersent = 50.0f;	// ũ����
		_second.evasionPersent = 30.0f;		// ȸ����
		_second.ad = 20;					// ���ݷ�
		_second.def = 20;					// ����
		_second.moveMentSpeed = 30.0f;		// �̵��ӵ�
		_second.addMaxHp = 50;				// �ִ�HP
		_second.price = 20000;				// ����
	}


}
