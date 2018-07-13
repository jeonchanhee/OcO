#include "stdafx.h"
#include "GodNpc.h"


GodNpc::GodNpc(){} 
GodNpc::~GodNpc(){}

HRESULT GodNpc::init(NPC_CONDITION condition, NPC_TYPE type, const char* npcName, int value, POINT position)
{
	_player = SCENEMANAGER->getPlayerAddressLink();

	_condition = condition;
	_type = type;
	_npcName = npcName;
	_npcX = position.x;
	_npcY = position.y;
	_frameX = _frameY = 0;

	npcCreate(condition, type, npcName, value);

	if (_npcCollision)
	{
		_img[1] = IMAGEMANAGER->findImage("f버튼");
	}

	_yesDialog = false;

	return S_OK;
}

void GodNpc::update()
{
	_count++;

	if (_condition == NPC_RIGHT_STOP)
	{
		
		_rightStop = true;
		if (_rightStop)
		{
			if (_count % 10 == 0)
			{
				if (_frameX >= _img[0]->getMaxFrameX()) _frameX = 0;
				else _frameX++;
				_frameY = 0;
				_count = 0;
			}
		}
	}
	else
	{
		_rightStop = false;
	}

	if (_condition ==  NPC_LEFT_STOP)
	{
		_leftStop = true;
		_frameY = 1;
		if (_leftStop)
		{
			if (_count % 10 == 0)
			{
				if (_frameX >= _img[0]->getMaxFrameX()) _frameX = 0;
				else _frameX++;
				_count = 0;
			}
		}
	}
	else
	{
		_leftStop = false;
	}

	RECT temp;
	if (IntersectRect(&temp, &_player->getRc(), &_rc))
	{
		_npcCollision = true;
		if (KEYMANAGER->isOnceKeyDown('F'))
			_yesDialog = true;
	}
	else
		_npcCollision = false;
}

void GodNpc::release()
{
}



void GodNpc::npcCreate(NPC_CONDITION condition, NPC_TYPE type,const char* npcName, int value)
{
	switch (condition)
	{
	case NPC_LEFT_STOP:
		switch (type)
		{
		case WEAPON_NPC:
			setWeaponNpc(npcName, value);
			break;
		case FOOD_NPC:
			setFoodNpc(npcName, value);
			break;
		}
	break;
	case NPC_RIGHT_STOP: 
		switch (type)
		{
		case WEAPON_NPC:
			setWeaponNpc(npcName, value);
			break;
		case FOOD_NPC:
			setFoodNpc(npcName, value);
			break;
		}
		break;
	}
}


void GodNpc::setWeaponNpc(const char* npcName, int value)
{
	char str[128];
	sprintf_s(str, "%s%d", npcName, value); // 엔피시이름 / 숫자
	_img[0] = IMAGEMANAGER->findImage(str);
	_rc = RectMake(_npcX, _npcY, _img[0]->getFrameWidth(),
		_img[0]->getFrameHeight());
}


void GodNpc::setFoodNpc(const char* npcName, int value)
{	
	char str[128];
	sprintf_s(str, "%s%d", npcName, value);
	_img[0] = IMAGEMANAGER->findImage(str);
	_rc = RectMake(_npcX, _npcY, _img[0]->getFrameWidth(),
		_img[0]->getFrameHeight());
}

void GodNpc::collision()
{
	
	RECT temp;

	_player = new Player;

	if (IntersectRect(&temp, &_rc, &_player->getPlayerRect()))
	{
		_npcCollision = true;

		if (_type == WEAPON_NPC);

		if (_type == FOOD_NPC);

	}

}


void GodNpc::render()
{
	_img[0]->frameRender(DC, _npcX, _npcY, _frameX, _frameY);

	if (_npcCollision)
	{
		IMAGEMANAGER->render("f버튼", DC, _npcX, _npcY - 50);
	}

}

