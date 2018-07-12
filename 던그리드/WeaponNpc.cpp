#include "stdafx.h"
#include "WeaponNpc.h"


WeaponNpc::WeaponNpc(){}
WeaponNpc::~WeaponNpc(){}

HRESULT WeaponNpc::init(NPC_CONDITION condition, NPC_TYPE type, const char* npcName, int value, POINT position)
{
	GodNpc::init(condition, type, npcName, value, position);

	//_wDialog = new DialogWeapon;
	//_wDialog->init();
	return S_OK;
}

void WeaponNpc::release()
{

	GodNpc::release();

}

void WeaponNpc::update()
{
	GodNpc::update();

	collision();

	//_wDialog->update();
}

void WeaponNpc::render()
{
	GodNpc::render();
	//_wDialog->render();
	
}


void WeaponNpc::collision()
{
	GodNpc::collision();
	
	RECT temp;
	if (IntersectRect(&temp, &_rc, &_player->getPlayerRect()))
	{
		if (_type == WEAPON_NPC)
		{

			if (KEYMANAGER->isOnceKeyDown('F'))
			{


			}

		}
	}
}


