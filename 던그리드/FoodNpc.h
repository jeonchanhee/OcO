#pragma once
#include "GodNpc.h"
#include "DialogStore.h"

class FoodNpc : public GodNpc
{
private:
	DialogStore* _dialog;

public:
	FoodNpc();
	~FoodNpc();

	HRESULT init(NPC_CONDITION condition, NPC_TYPE type, const char * npcName, int value, POINT position);

	void update();

	void release();

	void render();

	
};

