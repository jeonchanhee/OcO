#include "stdafx.h"
#include "FoodNpc.h"


FoodNpc::FoodNpc(){}
FoodNpc::~FoodNpc(){}

HRESULT FoodNpc::init(NPC_CONDITION condition, NPC_TYPE type, const char * npcName, int value, POINT position)
{
	GodNpc::init(condition, type, npcName, value, position);
	_dialog = new DialogStore;
	_dialog->init();
	return S_OK;
}

void FoodNpc::update()
{
	GodNpc::update();
	_dialog->update();
	if (_dialog->getIsFin())
	{
		_yesDialog = false;
		_dialog->setIsFin(false);
	}
}

void FoodNpc::release()
{
}

void FoodNpc::render()
{
	GodNpc::render();
	if (_yesDialog)
		_dialog->render();
}
