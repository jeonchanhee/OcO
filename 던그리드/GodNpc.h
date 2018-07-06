#pragma once
#include "gameNode.h"

enum NPC_CONDITION
{
	WEAPON_NPC_LEFT_STOP, 
	WEAPON_NPC_RIGHT_STOP,
	FOOD_NPC_LEFT_STOP, 
	FOOD_NPC_RIGHT_STOP
};

enum NPC_TYPE
{
	WEAPON_NPC,
	FOOD_NPC
};

class GodNpc : public gameNode
{
private:

	NPC_CONDITION _condition;	// 엔피시 상태
	NPC_TYPE _type;				// 엔피시 타입
	image* _img;				// 엔피시 이미지
	RECT _rc;					// 엔피시 렉트
	const char* _npcName;		// 엔피시 이름
	float _npcX, _npcY;			// 엔피시 x, y 좌표
	int _value;					// 무슨 엔피시 인지
	int _frameX, _frameY;		// 프레임 X, Y 
	int _count;					// 프레임 카운트 받을거임


public:
	GodNpc();
	~GodNpc();

	HRESULT init(NPC_TYPE type, NPC_CONDITION condition, const char* npcName, int value, POINT position);
	void update();
	void release();
	void render();

	void npcCreate(NPC_TYPE type, NPC_CONDITION condition, const char* npcName, int value);
	void WeaponNpc(NPC_CONDITION condition, const char* npcName, int value);
	void FoodNpc();
};

