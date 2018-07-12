#pragma once
#include "GodNpc.h"
#include "DialogWeapon.h"


class WeaponNpc : public GodNpc
{
private:
	DialogWeapon* _wDialog;		// 무기상점 엔피시 대사
public:
	WeaponNpc();
	~WeaponNpc();


	HRESULT init(NPC_CONDITION condition, NPC_TYPE type, const char* npcName, int value, POINT position);
	void release();
	void update();
	void render();

	void collision();

};

