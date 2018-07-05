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


	_count++;
	if (_item.isFrame)
	{
		if (_count %10 == 0)
		{
			for (int i = 0; i < 3; i++)
			{
				if (_item.frameX >= _item.image[i]->getMaxFrameX()) _item.frameX = 0;
				_item.image[i]->setFrameX(_item.frameX);
				_item.frameX++;
				_count = 0;
				break;
			}
		}
	}
	else
	{
		return;
	}
}


void Item::render() // �������� ����
{

	if (_item.isFrame) // �������̹��� �϶�
	{
		_item.image[0]->frameRender(DC, _item.x, _item.y, _item.frameX, _item.frameY);
		_item.image[1]->frameRender(DC, _item.x, _item.y, _item.frameX, _item.frameY);
		_item.image[2]->frameRender(DC, _item.x, _item.y, _item.frameX, _item.frameY);
	}
	else // ������ �̹����� �ƴҶ�
	{
		_item.image[0]->render(DC, _item.x, _item.y);
		_item.image[1]->render(DC, _item.x, _item.y);
		_item.image[2]->render(DC, _item.x, _item.y);
	}
}

void Item::createItem(ITEMTYPE type, IMAGETYPE type2, const char* itemName, int value, int num, bool frame) // ������ ����
{
	switch (type)
	{
		case SHORT_DISTANCE_WEAPON:
			ShortDistanceWeapon(itemName, value, num);
		break;
		case LONG_DISTANCE_WEAPON:
			LongDistanceWeapon(itemName, value, num);
		break;
		case DEFENCE_MECHANISM:
			DefenceMechanism(itemName, value, num);
		break;
		case SECOND_EQUIPMENT:
			SecondEquipment(itemName, value, num);
		break;
		case ACCESSORY:
			Accessory(itemName, value, num);
		break;
		case CONSUME:
			Consume(itemName, value, num);
		break;
		case HEALING:
			Healing(itemName, value, num);
		break;
		case TREASUREBOX:
			TreasureBox(itemName, value, num);
		break;
		case GOLD:
			Gold(itemName, value, num);
		break;
	}
	_item.type = type;
	_num = num;
	_item.isFrame = frame;
	_item.imageName = itemName;
	if (frame)
	{
		_item.frameX = _item.frameY = 0;
	}
	_item.image[0] = IMAGEMANAGER->findImage("��10");
}


///////////////////////// ���Ÿ� ���� ////////////////////////////////////

void Item::LongDistanceWeapon(const char* imageName, int value, int num)
{
	for (int i = 0; i < 3; ++i)	
	{
		char str[128];
		sprintf_s(str, "%s%d%d", imageName, value, num);
		_item.image[i] = IMAGEMANAGER->findImage(str);
	}

	if (value == 1) // ù��° ���Ÿ� ����
	{
		_item.ad = 10;
		_item.attackSpeed = 10.0f;
		_item.criticalPersent = 10.0f;
		_item.fixedDamage = 5;
		_item.imagetype = ����;

	}

	if (value == 1 && imageName == "Ȱ") // ù��° ���Ÿ� ����
	{
		_item.ad = 10;
		_item.attackSpeed = 10.0f;
		_item.criticalPersent = 10.0f;
		_item.fixedDamage = 5;
		_item.imagetype = ������;
	}

	if (value == 2) // �ι�° ���Ÿ� ����
	{
		_item.ad = 15;
		_item.attackSpeed = 15.0f;
		_item.criticalPersent = 15.0f;
		_item.fixedDamage = 10;
		_item.imagetype = ����;
	}

	if (value == 2 && imageName == "Ȱ") // �ι�° ���Ÿ� ����
	{
		_item.ad = 15;
		_item.attackSpeed = 15.0f;
		_item.criticalPersent = 15.0f;
		_item.fixedDamage = 10;
		_item.imagetype = ������;
	}

	if (value == 3) // ����° ���Ÿ� ����
	{
		_item.ad = 20;
		_item.attackSpeed = 20.0f;
		_item.criticalPersent = 20.0f;
		_item.fixedDamage = 15;
		_item.imagetype = ����;
	}

	if (value == 3 && imageName == "Ȱ")
	{
		_item.ad = 30;
		_item.attackSpeed = 30.0f;
		_item.criticalPersent = 30.0f;
		_item.fixedDamage = 25;
		_item.imagetype = ������;
	}

	if (value == 4) // �׹�° ���Ÿ� ����
	{
		_item.ad = 30;
		_item.attackSpeed = 30.0f;
		_item.criticalPersent = 30.0f;
		_item.fixedDamage = 25;
		_item.imagetype = ������;
		
	}


}
////////////////////////////// ���Ÿ� ���� //////////////////////////////




//////////////////////////// ���� ���� //////////////////////////////////

void Item::ShortDistanceWeapon(const char* imageName, int value, int num)
{
	for (int i = 0; i < 3; i++)
	{	
		char str[128];
		sprintf_s(str, "%s%d%d", imageName, value, num);
		_item.image[i] = IMAGEMANAGER->findImage(str);
	}

	if (value == 1) //�⺻����(ó���� ����� ���ҵ�)
	{
		_item.ad = 5;
		_item.attackSpeed = 5.0f;
		_item.criticalPersent = 5.0f;
		_item.fixedDamage = 5;
		_item.imagetype = ����;

	}

	if (value == 2) // ù��° ����
	{
		_item.ad = 10;
		_item.attackSpeed = 10.0f;
		_item.criticalPersent = 10.0f;
		_item.fixedDamage = 7;
		_item.imagetype = ����;
	}

	if (value == 3) // �ι�° ����
	{
		_item.ad = 15;
		_item.attackSpeed = 15.0f;
		_item.criticalPersent = 15.0f;
		_item.fixedDamage = 10;
		_item.imagetype = ����;
	}

	if (value == 4) // ����° ����
	{
		_item.ad = 20;
		_item.attackSpeed = 20.0f;
		_item.criticalPersent = 20.0f;
		_item.fixedDamage = 15;
		_item.imagetype = ������;
	}

	if (value == 5) // �׹�° ����
	{
		_item.ad = 30;
		_item.attackSpeed = 30.0f;
		_item.criticalPersent = 30.0f;
		_item.fixedDamage = 25;
		_item.imagetype = ������;
	}

}

//////////////////////////// ���� ���� //////////////////////////////////



//////////////////////////// �� ////////////////////////////////////
void Item::DefenceMechanism(const char * imageName, int value, int num)
{
	for (int i = 0; i < 3; i++)
	{
		char str[128];
		sprintf_s(str, "%s%d%d", imageName, value, num);
		_item.image[i] = IMAGEMANAGER->findImage(str);

	}

	if (value == 1) // ù��° ��
	{
		_item.armor = 10;				// ����
		_item.evasionPersent = 10.0f;	// ȸ����.
		_item.imagetype = ����;
	}
	
	if (value == 2) // �ι�° ��
	{
		_item.armor = 15;				// ����
		_item.evasionPersent = 15.0f;	// ȸ����.
		_item.imagetype = ����;

	}

	if (value == 2 && imageName == "����")
	{
		_item.armor = 30;				// ����
		_item.evasionPersent = 30.0f;	// ȸ����.
		_item.imagetype = ����;
	}


	if (value == 3) // ����° ��
	{
		_item.addMaxHp = 10;			// �ִ�ü�� ����
		_item.armor = 20;				// ����
		_item.evasionPersent = 20.0f;	// ȸ����.
		_item.imagetype = ����;
	}

	if (value == 4) // �׹�° �� 
	{
		_item.armor = 30;					// ����
		_item.addMaxHp = 30;				// ü������
		_item.attackSpeed = 30.0f;			// ����
		_item.evasionPersent = 30.0f;		// ȸ����.
		_item.criticalPersent = 30.0f;		// ũ��Ƽ��
		_item.imagetype = ����;
	}

}
//////////////////////////// �� //////////////////////////////////




//////////////////////////// ���� ��� ///////////////////////////////

void Item::SecondEquipment(const char* imageName, int value, int num)
{
	for (int i = 0; i < 3; i++)
	{
		char str[128];
		sprintf_s(str, "%s%d%d", imageName, value, num);
		_item.image[i] = IMAGEMANAGER->findImage(str);
	}

	if (value == 1)
	{
		_item.addMaxHp = 10;		// �ִ�ü�� ����
		_item.dashPower = 10.0f;	// �뽬���ݷ� ���� 
		_item.evasionPersent = 10;	// ȸ����
		_item.imagetype = ����;
	}

	if (value == 2)
	{
		_item.armor = 30;				// ����
		_item.addMaxHp = 30;			// �ִ� ü��
		_item.moveMentSpeed = -20.f;	// �̵��ӵ� 
		_item.imagetype = ����;
	}

	if (value == 3)
	{
		_item.ad = 10;				// ���ݷ�
		_item.attackSpeed = 10.0f;	// ���ݼӵ�
		_item.criticalPersent = 10;	// ũ��Ƽ��
		_item.imagetype = ����;

	}

	if (value == 4)
	{
		_item.isfly = true;
		// � Ű�� �������� ���� �ö��̰� Ʈ�簡 �ǰ� �ϰ�
		// ĳ���Ͱ� ���߿� �������� �Ѵ�. 
		_item.imagetype = ������;
	}

	if (value == 5)
	{
		_item.ad = 30;				// ���ݷ�
		_item.attackSpeed = 30.0f;	// ���ݼӵ�
		_item.criticalPersent = 30;	// ũ��Ƽ��
		_item.imagetype = ������;

	}

}
//////////////////////////// ���� ��� //////////////////////////////////




//////////////////////////// �Ǽ��縮 //////////////////////////////////

void Item::Accessory(const char* imageName, int value, int num)
{
	for (int i = 0; i < 3; i++)
	{
		char str[128];
		sprintf_s(str, "%s%d%d", imageName, value, num);
		_item.image[i] = IMAGEMANAGER->findImage(str);

	}

	if (value == 1)
	{
		_item.price = 3000;			// ����
		_item.addMaxHp = 10;		// ü������
		_item.armor = 5;			// ����
		_item.imagetype = ����;


	}
	if (value == 2)
	{
		_item.price = 3000;			// ����
		_item.ad = 5;				// ���ݷ�
		_item.addMaxHp = 5;			// �ִ� ü������
		_item.imagetype = ����;

	}
	if (value == 3)
	{
		_item.price = 4000;				// ����
		_item.attackSpeed = 10.0f;		// ���ݼӵ�
		_item.criticalPersent = 10.0f;	// ũ�� Ȯ��
		_item.evasionPersent = 10.0f;	// ȸ����
		_item.imagetype = ����;
	}
	if (value == 4)
	{
		_item.price = 5000;				// ����
		_item.ad = 10;					// ���ݷ�
		_item.armor = 10;				// ����
		_item.moveMentSpeed = 10.0f;	// �̵��ӵ�
		_item.attackSpeed = 10.0f;		// ���ݼӵ�
		_item.dashPower = 10.0f;		// �뽬���ݷ�
		_item.criticalPersent = 10.0f;	// ũ�� Ȯ��
		_item.evasionPersent = 10.0f;	// ȸ����
		_item.imagetype = ������;
	}

}
//////////////////////////// �Ǽ��縮 //////////////////////////////////





//////////////////////////// ���� /////////////////////////////////////

void Item::Consume(const char* imageName, int value, int num) // ���� 12����
{
	for (int i = 0; i < 3; i++)
	{
		char str[128];
		sprintf_s(str, "%s%d%d", imageName, value, num);
		_item.image[i] = IMAGEMANAGER->findImage(str);
	}

	if (value == 1)
	{
		_item.price = 500;			// ����
		_item.ad = 5;				// ���ݷ�
		_item.armor = 5;			// ����
		_item.heal = 10;			// ü��ȸ��
		_item.fullNess = 60;		// ������
		_item.imagetype = ����;
	}

	if (value == 2)
	{
		_item.price = 600;				// ����
		_item.moveMentSpeed = 5.0f;		// �̵��ӵ�
		_item.attackSpeed = 5.0f;		// ���ݼӵ�
		_item.heal = 12;				// ü��ȸ��
		_item.fullNess = 60;			// ������
		_item.imagetype = ����;
	}	

	if (value == 3)
	{
		_item.price = 650;			// ����
		_item.ad = 5;				// ���ݷ�
		_item.dashPower = 5.0f;		// �뽬���ݷ�
		_item.heal = 13;			// ü��ȸ��
		_item.fullNess = 60;		// ������
		_item.imagetype = ����;
	}	

	if (value == 4)
	{
		_item.price = 650;					// ����
		_item.criticalPersent = 5.0f;		// ũ�� Ȯ��
		_item.evasionPersent = 5.0f;		// ȸ����
		_item.heal = 13;					// ü��ȸ��
		_item.fullNess = 60;				// ������
		_item.imagetype = ����;
	}	

	if (value == 5)
	{
		_item.price = 800;			// ����
		_item.ad = 10;				// ���ݷ�
		_item.armor = 10;			// ����
		_item.heal = 15;			// ü��ȸ��
		_item.fullNess = 70;		// ������
		_item.imagetype = ����;
	}	

	if (value == 6)
	{
		_item.price = 850;				// ����
		_item.moveMentSpeed = 10.0f;	// �̵��ӵ�
		_item.attackSpeed = 10.0f;		// ���ݼӵ�
		_item.heal = 15;				// ü��ȸ��
		_item.fullNess = 70;			// ������
		_item.imagetype = ����;
	}	

	if (value == 7)
	{
		_item.price = 900;			// ����
		_item.ad = 10;				// ���ݷ�
		_item.dashPower = 10.0f;	// �뽬���ݷ�
		_item.heal = 17;			// ü��ȸ��
		_item.fullNess = 70;		// ������
		_item.imagetype = ����;
	}	

	if (value == 8)
	{
		_item.price = 1000;					// ����
		_item.criticalPersent = 10.0f;		// ũ�� Ȯ��
		_item.evasionPersent = 10.0f;		// ȸ����
		_item.heal = 20;					// ü��ȸ��
		_item.fullNess = 70;				// ������
		_item.imagetype = ����;
	}	

	if (value == 9)
	{
		_item.price = 2000;				// ����
		_item.ad = 10;					// ���ݷ�
		_item.armor = 10;				// ����
		_item.moveMentSpeed = 10.0f;	// �̵��ӵ�
		_item.attackSpeed = 10.0f;		// ���ݼӵ�
		_item.dashPower = 10.0f;		// �뽬���ݷ�
		_item.criticalPersent = 10.0f;	// ũ�� Ȯ��
		_item.evasionPersent = 10.0f;	// ȸ����
		_item.heal = 25;				// ü��ȸ��
		_item.fullNess = 80;			// ������
		_item.imagetype = ����;
	}	

	if (value == 10)
	{
		_item.price =					3000;	// ����
		_item.ad =						15;		// ���ݷ�
		_item.armor =					15;		// ����
		_item.moveMentSpeed =			15.0f;	// �̵��ӵ�
		_item.attackSpeed =				15.0f;	// ���ݼӵ�
		_item.dashPower =				15.0f;	// �뽬���ݷ�
		_item.criticalPersent =			15.0f;	// ũ�� Ȯ��
		_item.evasionPersent =			15.0f;	// ȸ����
		_item.heal =					30;		// ü��ȸ��
		_item.fullNess =				85;		// ������
		_item.imagetype = ����;
	}	

	if (value == 11)
	{
		_item.price =			 4000;		// ����
		_item.ad =				 20;		// ���ݷ�
		_item.armor =			 20;		// ����
		_item.moveMentSpeed =	 20.0f;		// �̵��ӵ�
		_item.attackSpeed =		 20.0f;		// ���ݼӵ�
		_item.dashPower =		 20.0f;		// �뽬���ݷ�
		_item.criticalPersent =  20.0f;		// ũ�� Ȯ��
		_item.evasionPersent =	 20.0f;		// ȸ����
		_item.heal =			 25;		// ü��ȸ��
		_item.fullNess =		 80;		// ������
		_item.imagetype = ����;
	}	

	if (value == 12)
	{
		_item.price = 1000;			// ����
		_item.ad = 10;				// ���ݷ�
		_item.armor = 10;			// ����
		_item.moveMentSpeed = 10;	// �̵��ӵ�
		_item.attackSpeed = 10;		// ���ݼӵ�
		_item.dashPower = 10;		// �뽬���ݷ�
		_item.criticalPersent = 10;	// ũ�� Ȯ��
		_item.evasionPersent = 10;	// ȸ����
		_item.fullNess = 50;		// ������
		_item.imagetype = ����;
	}
}

void Item::Healing(const char* imageName, int value, int num)
{
	for (int i = 0; i < 2; i++)
	{
		char str[128];
		sprintf_s(str, "%s%d%d", imageName, value, num);
		_item.image[i] = IMAGEMANAGER->findImage(str);

	}

	if (value == 1)
	{
		_item.heal = 10;
		_item.imagetype = ������;
	}

	if (value == 2)
	{
		_item.heal = 20;
		_item.imagetype = ������;
	}
}

void Item::TreasureBox(const char* imageName, int value, int num)
{
	for (int i = 0; i < 3; i++)
	{
		char str[128];
		sprintf_s(str, "%s%d%d", imageName, value, num);
		_item.image[i] = IMAGEMANAGER->findImage(str);


	}

	if (value == 1) // ��������
	{
		// ���� �󸶳� ���ðŴ� ����.(���� ���� 3~8);
		// �����۵� Ȯ���� ������ ����( ��� �������� ���´� ��������) �ȳ��� ���� ����.
		_item.imagetype = ������;
	}

	if (value == 2) // �Ϲ� ����
	{
		// ���� �󸶳� ���ð��� ����( ���� ���� 3~8);
		// �������� 1�� ���� 3�� ������ ������ �Ѵ�.
		_item.imagetype = ������;

	}
}

void Item::Gold(const char* imageName, int value, int num)
{
	for (int i = 0; i < 3; i++)
	{
		char str[128];
		sprintf_s(str, "%s%d%d", imageName, value, num);
		_item.image[i] = IMAGEMANAGER->findImage(str);

	}

	if (value == 1) // ����
	{
		// 1 ~ 10��� ���� ����
		_item.gold = RND->getFromIntTo(1, 10);
		_item.imagetype = ������;
	}

	if (value == 2) // ���
	{
		// 10 ~ 20 ��� ���� ����
		_item.gold = RND->getFromIntTo(10, 20);
		_item.imagetype = ������;
	}
}
