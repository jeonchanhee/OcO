#include "stdafx.h"
#include "Item.h"


/////////////////////////////////// 무기 ///////////////////////////////////////

Weapon::Weapon() {}Weapon::~Weapon() {}

HRESULT Weapon::init(const char* imageName, POINT position)
{
	_weapon.image = IMAGEMANAGER->findImage(imageName);
	_weapon.x = position.x;
	_weapon.y = position.y;
	_weapon.itemtype = WEAPON;
	_weapon.rc = RectMakeCenter(_weapon.x, _weapon.y, _weapon.image->getWidth(),
		_weapon.image->getHeight());
	
	return S_OK;
}

HRESULT Weapon::init2(const char* imageName, POINT position)
{
	_weapon.image = IMAGEMANAGER->findImage(imageName);
	_weapon.x = position.x;
	_weapon.y = position.y;
	_weapon.itemtype = WEAPON;
	_weapon.rc = RectMakeCenter(_weapon.x, _weapon.y, _weapon.image->getFrameWidth(), 
		_weapon.image->getFrameHeight());

	_weapon.count = 0;
	
	return S_OK;
}

void Weapon::release()
{

}

void Weapon::update()
{


}

void Weapon::render()
{
	

}

////////////////////////////////// 무기 ///////////////////////////////////////////






///////////////////////////////// 음식 ////////////////////////////////////////////

Food::Food(){}Food::~Food(){}



HRESULT Food::init(const char* imageName, POINT position)
{
	_food.image = IMAGEMANAGER->findImage(imageName);
	_food.x = position.x;
	_food.y = position.y;
	_food.itemtype = FOOD;
	_food.rc = RectMakeCenter(_food.x, _food.y, _food.image->getWidth(),
		_food.image->getHeight());

	return S_OK;
}

HRESULT Food::init2(const char * imageName, POINT position)
{
	_food.image = IMAGEMANAGER->findImage(imageName);
	_food.x = position.x;
	_food.y = position.y;
	_food.itemtype = FOOD;
	_food.rc = RectMakeCenter(_food.x, _food.y, _food.image->getFrameWidth(),
		_food.image->getFrameHeight());

	_food.count = 0;
	return S_OK;
}


void Food::release()
{
}

void Food::update()
{

}

void Food::render()
{
	
}

///////////////////////////////// 음식 ////////////////////////////////////////////






///////////////////////////////// 방어구 //////////////////////////////////////////

Defence::Defence(){}Defence::~Defence(){}


HRESULT Defence::init(const char * imageName, POINT position)
{
	_defence.image = IMAGEMANAGER->findImage(imageName);
	_defence.x = position.x;
	_defence.y = position.y;
	_defence.itemtype = DEFENCE;
	_defence.rc = RectMakeCenter(_defence.x, _defence.y, _defence.image->getWidth(),
		_defence.image->getHeight());

	

	return S_OK;
}

HRESULT Defence::init2(const char * imageName, POINT position)
{
	_defence.image = IMAGEMANAGER->findImage(imageName);
	_defence.x = position.x;
	_defence.y = position.y;
	_defence.itemtype = DEFENCE;
	_defence.rc = RectMakeCenter(_defence.x, _defence.y, _defence.image->getFrameWidth(),
		_defence.image->getFrameHeight());
	_defence.count = 0;
	return S_OK;
}

void Defence::release()
{

}

void Defence::update()
{

}

void Defence::render()
{

}


///////////////////////////////// 방어구 //////////////////////////////////////////





///////////////////////////////// 코인/골드 바 ////////////////////////////////////

Treasure::Treasure(){}Treasure::~Treasure(){}

HRESULT Treasure::init(const char* imageName, POINT position)
{
	
	_treasure.image = IMAGEMANAGER->findImage(imageName);
	_treasure.x = position.x;
	_treasure.y = position.y;
	_treasure.itemtype = TREASURE;
	_treasure.rc = RectMakeCenter(_treasure.x, _treasure.y, _treasure.image->getWidth(),
		_treasure.image->getHeight());

	return S_OK;
}

HRESULT Treasure::init2(const char * imageName, POINT position)
{

	_treasure.image = IMAGEMANAGER->findImage(imageName);
	_treasure.x = position.x;
	_treasure.y = position.y;
	_treasure.itemtype = TREASURE;
	_treasure.rc = RectMakeCenter(_treasure.x, _treasure.y, _treasure.image->getFrameWidth(),
		_treasure.image->getFrameHeight());

	_treasure.count = 0;

	return S_OK;
}

void Treasure::release()
{


}

void Treasure::update()
{


}

void Treasure::render()
{


}


///////////////////////////////// 코인/골드 바 ////////////////////////////////////