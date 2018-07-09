#include "stdafx.h"
#include "GodNpc.h"


GodNpc::GodNpc(){} 
GodNpc::~GodNpc(){}

HRESULT GodNpc::init(NPC_CONDITION condition, NPC_TYPE type, const char* npcName, int value, POINT position)
{
	_condition = condition;
	_type = type;
	_npcName = npcName;
	_npcX = position.x;
	_npcY = position.y;
	_frameX = _frameY = 0;
	npcCreate(condition, type, npcName, value);
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
					if (_frameX >= _img->getMaxFrameX()) _frameX = 0;
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
					if (_frameX >= _img->getMaxFrameX()) _frameX = 0;
					else _frameX++;
					
					_count = 0;
			}
		}
	}
	else
	{
		_leftStop = false;
	}

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
	_img = IMAGEMANAGER->findImage(str);
	_rc = RectMake(_npcX, _npcY, _img->getFrameWidth(),
		_img->getFrameHeight());
}


void GodNpc::setFoodNpc(const char* npcName, int value)
{	
	char str[128];
	sprintf_s(str, "%s%d", npcName, value);
	_img = IMAGEMANAGER->findImage(str);
	_rc = RectMake(_npcX, _npcY, _img->getFrameWidth(),
		_img->getFrameHeight());
}


void GodNpc::render()
{
	_img->frameRender(DC, _npcX, _npcY, _frameX, _frameY);
}

