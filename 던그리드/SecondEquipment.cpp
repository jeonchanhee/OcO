#include "stdafx.h"
#include "SecondEquipment.h"


SecondEquipment::SecondEquipment(){} SecondEquipment::~SecondEquipment(){}

HRESULT SecondEquipment::init()
{

	for (int i = 0; i < 3; i++)
	{
		if (_second.isFrame)
		{
			if (i == 2)
			{
				_second.rc[i] = RectMakeCenter(_second.x + i * 50, _second.y, _second.image[i]->getFrameWidth(),
					_second.image[i]->getFrameHeight());
			}
		}
		else // ������ �̹����� �ƴϸ� 
		{
			_second.rc[i] = RectMakeCenter(_second.x + i * 50, _second.y, _second.image[i]->getWidth(),
				_second.image[i]->getHeight());
		}

	}

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
	else
	{
		for (int i = 0; i < 3; i++)
		{
			_second.image[i]->render(DC, _second.rc[i].left, _second.rc[i].top);
		}
	}
}

void SecondEquipment::CreateEquipment(ITEMTYPE type, const char * secondEquipmentName, int value, POINT position)
{
	_second.x = position.x;
	_second.y = position.y;

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
	for (int i = 0; i < 3; i++)
	{
		sprintf_s(str, "%s%d%d", secondEquipmentName, value, i);
		_second.image[i] = IMAGEMANAGER->findImage(str);

		if (i == 2) // ���� �̹��� �϶�
		{
			_second.isFrame = true;
			if (_second.isFrame) // ������ �̹��� �̸�
			{
				init(); // init ���� ������ �̹����̸�
				render(); // ������ ����
			}
		}
		else
		{
			init();
			render();
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
