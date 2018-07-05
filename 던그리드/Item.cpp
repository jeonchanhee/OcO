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


void Item::render() // 아이템을 렌더
{

	if (_item.isFrame) // 프레임이미지 일때
	{
		_item.image[0]->frameRender(DC, _item.x, _item.y, _item.frameX, _item.frameY);
		_item.image[1]->frameRender(DC, _item.x, _item.y, _item.frameX, _item.frameY);
		_item.image[2]->frameRender(DC, _item.x, _item.y, _item.frameX, _item.frameY);
	}
	else // 프레임 이미지가 아닐때
	{
		_item.image[0]->render(DC, _item.x, _item.y);
		_item.image[1]->render(DC, _item.x, _item.y);
		_item.image[2]->render(DC, _item.x, _item.y);
	}
}

void Item::createItem(ITEMTYPE type, IMAGETYPE type2, const char* itemName, int value, int num, bool frame) // 아이템 만듬
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
	_item.image[0] = IMAGEMANAGER->findImage("검10");
}


///////////////////////// 원거리 무기 ////////////////////////////////////

void Item::LongDistanceWeapon(const char* imageName, int value, int num)
{
	for (int i = 0; i < 3; ++i)	
	{
		char str[128];
		sprintf_s(str, "%s%d%d", imageName, value, num);
		_item.image[i] = IMAGEMANAGER->findImage(str);
	}

	if (value == 1) // 첫번째 원거리 무기
	{
		_item.ad = 10;
		_item.attackSpeed = 10.0f;
		_item.criticalPersent = 10.0f;
		_item.fixedDamage = 5;
		_item.imagetype = 단일;

	}

	if (value == 1 && imageName == "활") // 첫번째 원거리 무기
	{
		_item.ad = 10;
		_item.attackSpeed = 10.0f;
		_item.criticalPersent = 10.0f;
		_item.fixedDamage = 5;
		_item.imagetype = 프레임;
	}

	if (value == 2) // 두번째 원거리 무기
	{
		_item.ad = 15;
		_item.attackSpeed = 15.0f;
		_item.criticalPersent = 15.0f;
		_item.fixedDamage = 10;
		_item.imagetype = 단일;
	}

	if (value == 2 && imageName == "활") // 두번째 원거리 무기
	{
		_item.ad = 15;
		_item.attackSpeed = 15.0f;
		_item.criticalPersent = 15.0f;
		_item.fixedDamage = 10;
		_item.imagetype = 프레임;
	}

	if (value == 3) // 세번째 원거리 무기
	{
		_item.ad = 20;
		_item.attackSpeed = 20.0f;
		_item.criticalPersent = 20.0f;
		_item.fixedDamage = 15;
		_item.imagetype = 단일;
	}

	if (value == 3 && imageName == "활")
	{
		_item.ad = 30;
		_item.attackSpeed = 30.0f;
		_item.criticalPersent = 30.0f;
		_item.fixedDamage = 25;
		_item.imagetype = 프레임;
	}

	if (value == 4) // 네번째 원거리 무기
	{
		_item.ad = 30;
		_item.attackSpeed = 30.0f;
		_item.criticalPersent = 30.0f;
		_item.fixedDamage = 25;
		_item.imagetype = 프레임;
		
	}


}
////////////////////////////// 원거리 무기 //////////////////////////////




//////////////////////////// 근접 무기 //////////////////////////////////

void Item::ShortDistanceWeapon(const char* imageName, int value, int num)
{
	for (int i = 0; i < 3; i++)
	{	
		char str[128];
		sprintf_s(str, "%s%d%d", imageName, value, num);
		_item.image[i] = IMAGEMANAGER->findImage(str);
	}

	if (value == 1) //기본무기(처음에 사용할 숏소드)
	{
		_item.ad = 5;
		_item.attackSpeed = 5.0f;
		_item.criticalPersent = 5.0f;
		_item.fixedDamage = 5;
		_item.imagetype = 단일;

	}

	if (value == 2) // 첫번째 무기
	{
		_item.ad = 10;
		_item.attackSpeed = 10.0f;
		_item.criticalPersent = 10.0f;
		_item.fixedDamage = 7;
		_item.imagetype = 단일;
	}

	if (value == 3) // 두번째 무기
	{
		_item.ad = 15;
		_item.attackSpeed = 15.0f;
		_item.criticalPersent = 15.0f;
		_item.fixedDamage = 10;
		_item.imagetype = 단일;
	}

	if (value == 4) // 세번째 무기
	{
		_item.ad = 20;
		_item.attackSpeed = 20.0f;
		_item.criticalPersent = 20.0f;
		_item.fixedDamage = 15;
		_item.imagetype = 프레임;
	}

	if (value == 5) // 네번째 무기
	{
		_item.ad = 30;
		_item.attackSpeed = 30.0f;
		_item.criticalPersent = 30.0f;
		_item.fixedDamage = 25;
		_item.imagetype = 프레임;
	}

}

//////////////////////////// 근접 무기 //////////////////////////////////



//////////////////////////// 방어구 ////////////////////////////////////
void Item::DefenceMechanism(const char * imageName, int value, int num)
{
	for (int i = 0; i < 3; i++)
	{
		char str[128];
		sprintf_s(str, "%s%d%d", imageName, value, num);
		_item.image[i] = IMAGEMANAGER->findImage(str);

	}

	if (value == 1) // 첫번째 방어구
	{
		_item.armor = 10;				// 방어력
		_item.evasionPersent = 10.0f;	// 회피율.
		_item.imagetype = 단일;
	}
	
	if (value == 2) // 두번째 방어구
	{
		_item.armor = 15;				// 방어력
		_item.evasionPersent = 15.0f;	// 회피율.
		_item.imagetype = 단일;

	}

	if (value == 2 && imageName == "방패")
	{
		_item.armor = 30;				// 방어력
		_item.evasionPersent = 30.0f;	// 회피율.
		_item.imagetype = 단일;
	}


	if (value == 3) // 세번째 방어구
	{
		_item.addMaxHp = 10;			// 최대체력 증가
		_item.armor = 20;				// 방어력
		_item.evasionPersent = 20.0f;	// 회피율.
		_item.imagetype = 단일;
	}

	if (value == 4) // 네번째 방어구 
	{
		_item.armor = 30;					// 방어력
		_item.addMaxHp = 30;				// 체력증가
		_item.attackSpeed = 30.0f;			// 공속
		_item.evasionPersent = 30.0f;		// 회피율.
		_item.criticalPersent = 30.0f;		// 크리티컬
		_item.imagetype = 단일;
	}

}
//////////////////////////// 방어구 //////////////////////////////////




//////////////////////////// 보조 장비 ///////////////////////////////

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
		_item.addMaxHp = 10;		// 최대체력 증가
		_item.dashPower = 10.0f;	// 대쉬공격력 증가 
		_item.evasionPersent = 10;	// 회피율
		_item.imagetype = 단일;
	}

	if (value == 2)
	{
		_item.armor = 30;				// 방어력
		_item.addMaxHp = 30;			// 최대 체력
		_item.moveMentSpeed = -20.f;	// 이동속도 
		_item.imagetype = 단일;
	}

	if (value == 3)
	{
		_item.ad = 10;				// 공격력
		_item.attackSpeed = 10.0f;	// 공격속도
		_item.criticalPersent = 10;	// 크리티컬
		_item.imagetype = 단일;

	}

	if (value == 4)
	{
		_item.isfly = true;
		// 어떤 키를 눌렀을때 이즈 플라이가 트루가 되게 하고
		// 캐릭터가 공중에 떠오르게 한다. 
		_item.imagetype = 프레임;
	}

	if (value == 5)
	{
		_item.ad = 30;				// 공격력
		_item.attackSpeed = 30.0f;	// 공격속도
		_item.criticalPersent = 30;	// 크리티컬
		_item.imagetype = 프레임;

	}

}
//////////////////////////// 보조 장비 //////////////////////////////////




//////////////////////////// 악세사리 //////////////////////////////////

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
		_item.price = 3000;			// 가격
		_item.addMaxHp = 10;		// 체력증가
		_item.armor = 5;			// 방어력
		_item.imagetype = 단일;


	}
	if (value == 2)
	{
		_item.price = 3000;			// 가격
		_item.ad = 5;				// 공격력
		_item.addMaxHp = 5;			// 최대 체력증가
		_item.imagetype = 단일;

	}
	if (value == 3)
	{
		_item.price = 4000;				// 가격
		_item.attackSpeed = 10.0f;		// 공격속도
		_item.criticalPersent = 10.0f;	// 크리 확률
		_item.evasionPersent = 10.0f;	// 회피율
		_item.imagetype = 단일;
	}
	if (value == 4)
	{
		_item.price = 5000;				// 가격
		_item.ad = 10;					// 공격력
		_item.armor = 10;				// 방어력
		_item.moveMentSpeed = 10.0f;	// 이동속도
		_item.attackSpeed = 10.0f;		// 공격속도
		_item.dashPower = 10.0f;		// 대쉬공격력
		_item.criticalPersent = 10.0f;	// 크리 확률
		_item.evasionPersent = 10.0f;	// 회피율
		_item.imagetype = 프레임;
	}

}
//////////////////////////// 악세사리 //////////////////////////////////





//////////////////////////// 음식 /////////////////////////////////////

void Item::Consume(const char* imageName, int value, int num) // 음식 12가지
{
	for (int i = 0; i < 3; i++)
	{
		char str[128];
		sprintf_s(str, "%s%d%d", imageName, value, num);
		_item.image[i] = IMAGEMANAGER->findImage(str);
	}

	if (value == 1)
	{
		_item.price = 500;			// 가격
		_item.ad = 5;				// 공격력
		_item.armor = 5;			// 방어력
		_item.heal = 10;			// 체력회복
		_item.fullNess = 60;		// 공복도
		_item.imagetype = 단일;
	}

	if (value == 2)
	{
		_item.price = 600;				// 가격
		_item.moveMentSpeed = 5.0f;		// 이동속도
		_item.attackSpeed = 5.0f;		// 공격속도
		_item.heal = 12;				// 체력회복
		_item.fullNess = 60;			// 공복도
		_item.imagetype = 단일;
	}	

	if (value == 3)
	{
		_item.price = 650;			// 가격
		_item.ad = 5;				// 공격력
		_item.dashPower = 5.0f;		// 대쉬공격력
		_item.heal = 13;			// 체력회복
		_item.fullNess = 60;		// 공복도
		_item.imagetype = 단일;
	}	

	if (value == 4)
	{
		_item.price = 650;					// 가격
		_item.criticalPersent = 5.0f;		// 크리 확률
		_item.evasionPersent = 5.0f;		// 회피율
		_item.heal = 13;					// 체력회복
		_item.fullNess = 60;				// 공복도
		_item.imagetype = 단일;
	}	

	if (value == 5)
	{
		_item.price = 800;			// 가격
		_item.ad = 10;				// 공격력
		_item.armor = 10;			// 방어력
		_item.heal = 15;			// 체력회복
		_item.fullNess = 70;		// 공복도
		_item.imagetype = 단일;
	}	

	if (value == 6)
	{
		_item.price = 850;				// 가격
		_item.moveMentSpeed = 10.0f;	// 이동속도
		_item.attackSpeed = 10.0f;		// 공격속도
		_item.heal = 15;				// 체력회복
		_item.fullNess = 70;			// 공복도
		_item.imagetype = 단일;
	}	

	if (value == 7)
	{
		_item.price = 900;			// 가격
		_item.ad = 10;				// 공격력
		_item.dashPower = 10.0f;	// 대쉬공격력
		_item.heal = 17;			// 체력회복
		_item.fullNess = 70;		// 공복도
		_item.imagetype = 단일;
	}	

	if (value == 8)
	{
		_item.price = 1000;					// 가격
		_item.criticalPersent = 10.0f;		// 크리 확률
		_item.evasionPersent = 10.0f;		// 회피율
		_item.heal = 20;					// 체력회복
		_item.fullNess = 70;				// 공복도
		_item.imagetype = 단일;
	}	

	if (value == 9)
	{
		_item.price = 2000;				// 가격
		_item.ad = 10;					// 공격력
		_item.armor = 10;				// 방어력
		_item.moveMentSpeed = 10.0f;	// 이동속도
		_item.attackSpeed = 10.0f;		// 공격속도
		_item.dashPower = 10.0f;		// 대쉬공격력
		_item.criticalPersent = 10.0f;	// 크리 확률
		_item.evasionPersent = 10.0f;	// 회피율
		_item.heal = 25;				// 체력회복
		_item.fullNess = 80;			// 공복도
		_item.imagetype = 단일;
	}	

	if (value == 10)
	{
		_item.price =					3000;	// 가격
		_item.ad =						15;		// 공격력
		_item.armor =					15;		// 방어력
		_item.moveMentSpeed =			15.0f;	// 이동속도
		_item.attackSpeed =				15.0f;	// 공격속도
		_item.dashPower =				15.0f;	// 대쉬공격력
		_item.criticalPersent =			15.0f;	// 크리 확률
		_item.evasionPersent =			15.0f;	// 회피율
		_item.heal =					30;		// 체력회복
		_item.fullNess =				85;		// 공복도
		_item.imagetype = 단일;
	}	

	if (value == 11)
	{
		_item.price =			 4000;		// 가격
		_item.ad =				 20;		// 공격력
		_item.armor =			 20;		// 방어력
		_item.moveMentSpeed =	 20.0f;		// 이동속도
		_item.attackSpeed =		 20.0f;		// 공격속도
		_item.dashPower =		 20.0f;		// 대쉬공격력
		_item.criticalPersent =  20.0f;		// 크리 확률
		_item.evasionPersent =	 20.0f;		// 회피율
		_item.heal =			 25;		// 체력회복
		_item.fullNess =		 80;		// 공복도
		_item.imagetype = 단일;
	}	

	if (value == 12)
	{
		_item.price = 1000;			// 가격
		_item.ad = 10;				// 공격력
		_item.armor = 10;			// 방어력
		_item.moveMentSpeed = 10;	// 이동속도
		_item.attackSpeed = 10;		// 공격속도
		_item.dashPower = 10;		// 대쉬공격력
		_item.criticalPersent = 10;	// 크리 확률
		_item.evasionPersent = 10;	// 회피율
		_item.fullNess = 50;		// 공복도
		_item.imagetype = 단일;
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
		_item.imagetype = 프레임;
	}

	if (value == 2)
	{
		_item.heal = 20;
		_item.imagetype = 프레임;
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

	if (value == 1) // 보스상자
	{
		// 돈은 얼마나 나올거니 설정.(범위 랜덤 3~8);
		// 아이템도 확률로 나오게 설정( 모든 아이템이 나온다 랜덤으로) 안나올 수도 있음.
		_item.imagetype = 프레임;
	}

	if (value == 2) // 일반 상자
	{
		// 돈은 얼마나 나올건지 설정( 범위 랜덤 3~8);
		// 아이템은 1번 부터 3번 까지만 나오게 한다.
		_item.imagetype = 프레임;

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

	if (value == 1) // 코인
	{
		// 1 ~ 10골드 까지 랜덤
		_item.gold = RND->getFromIntTo(1, 10);
		_item.imagetype = 프레임;
	}

	if (value == 2) // 골드
	{
		// 10 ~ 20 골드 까지 랜덤
		_item.gold = RND->getFromIntTo(10, 20);
		_item.imagetype = 프레임;
	}
}
