#include "stdafx.h"
#include "GodNpc.h"


GodNpc::GodNpc(){} GodNpc::~GodNpc(){}

HRESULT GodNpc::init(NPC_TYPE type, NPC_CONDITION condition, const char* npcName, int value, POINT position)
{
	_type = type;
	_condition = condition;
	_npcName = npcName;
	_npcX = position.x;
	_npcY = position.y;

	npcCreate(type, condition, npcName, value);
	return S_OK;
}

void GodNpc::update()
{
	_count++;

	if (WEAPON_NPC_RIGHT_STOP)
	{
		if (_count % 10 == 0)
		{
			if (_frameX >= _img->getMaxFrameX()) _frameX = 0;

			_img->setFrameX(_frameX);
			_img->setFrameY(_frameY);
			_frameY = 0;
			_frameX++;
			_count = 0;
		}
	}

	if (WEAPON_NPC_LEFT_STOP)
	{
		if (_count % 10 == 0)
		{
			if (_frameX >= _img->getMaxFrameX()) _frameX = 0;

			_img->setFrameX(_frameX);
			_img->setFrameY(_frameY);
			_frameY = 1;
			_frameX++;
			_count = 0;
		}
	}


}

void GodNpc::release()
{
}

void GodNpc::render()
{
	_img->frameRender(DC, _npcX, _npcY, _img->getFrameWidth(),
		_img->getFrameHeight());
}


void GodNpc::npcCreate(NPC_TYPE type, NPC_CONDITION condition, const char* npcName, int value)
{
	switch (type)
	{
		case WEAPON_NPC:
			WeaponNpc(condition, npcName, value);
		break;
		case FOOD_NPC:
		
		break;
	}
}


void GodNpc::WeaponNpc(NPC_CONDITION condition, const char* npcName, int value)
{

	switch (condition)
	{
		char str[128];

		case WEAPON_NPC_LEFT_STOP:
			sprintf_s(str, "%s%d", npcName, value);
			_img = IMAGEMANAGER->findImage(str);
			_rc = RectMake(_npcX, _npcY, _img->getFrameWidth(),
				_img->getFrameHeight());
			

		break;
		
		case WEAPON_NPC_RIGHT_STOP:
			sprintf_s(str, "%s%d", npcName, value);
			_img = IMAGEMANAGER->findImage(str);
			_rc = RectMake(_npcX, _npcY, _img->getFrameWidth(),
				_img->getFrameHeight());
		break;
	}
	
}


void GodNpc::FoodNpc()
{


}
