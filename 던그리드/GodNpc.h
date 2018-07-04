#pragma once
#include "gameNode.h"

enum NPCTYPE
{
	WEAPON_NPC_LEFT, WEAPON_NPC_RIGHT,
	FOOD_NPC_LEFT, FOOD_NPC_RIGHT
};

class GodNpc : public gameNode
{
private:

	NPCTYPE _type;		// 엔피시 타입
	image* _image;		// 엔피시 이미지
	RECT _npcInven[10]; // 엔피시 인벤토리
	RECT _rc;			// 엔피시 렉트
	float _npcX, _npcY;	// 엔피시 x, y 좌표
	int _count;			// 프레임 카운트 받을거임

public:
	GodNpc();
	~GodNpc();

	HRESULT init();
	void update();
	void release();
	void render();

	void npcCreate(NPCTYPE type, const char* npcName, POINT position);
	void WeaponNpc();
	void FoodNpc();
};

