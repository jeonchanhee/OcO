#include "stdafx.h"
#include "WeaponNpc.h"


WeaponNpc::WeaponNpc(){}
WeaponNpc::~WeaponNpc(){}

HRESULT WeaponNpc::init(NPC_CONDITION condition, NPC_TYPE type, const char* npcName, int value, POINT position)
{
	GodNpc::init(condition, type, npcName, value, position);

	_wDialog = new DialogWeapon;
	_wDialog->init();
	return S_OK;
}

void WeaponNpc::release()
{
	GodNpc::release();
}

void WeaponNpc::update()
{
	GodNpc::update();
	_wDialog->update();
	if (_wDialog->getIsFin())
	{
		_yesDialog = false;
		_wDialog->setIsFin(false);
	}
}

void WeaponNpc::render()
{
	GodNpc::render();
	if (_yesDialog)
		_wDialog->render();
}

