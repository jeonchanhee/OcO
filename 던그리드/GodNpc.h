#pragma once
#include "gameNode.h"
#include "DialogWeapon.h"
#include "DialogStore.h"
#include "Player.h"


enum NPC_CONDITION
{
	NPC_LEFT_STOP,
	NPC_RIGHT_STOP
};

enum NPC_TYPE
{
	WEAPON_NPC,
	FOOD_NPC
};

class GodNpc : public gameNode
{

protected:

	NPC_CONDITION _condition;	// 엔피시 상태
	NPC_TYPE _type;				// 엔피시 타입
	image* _img[2];				// 엔피시 이미지
	RECT _rc;					// 엔피시 렉트
	bool _npcCollision;			// 엔피시와 플레이어 충돌 여부
	const char* _npcName;		// 엔피시 이름
	float _npcX, _npcY;			// 엔피시 x, y 좌표
	int _value;					// 무슨 엔피시 인지
	int _frameX, _frameY;		// 프레임 X, Y 
	int _count;					// 프레임 카운트 받을거임
	bool _leftStop;				// 왼쪽으로 멈춰있냐 
	bool _rightStop;			// 오른쪽으로 멈춰있냐
	Player* _player;

	bool _yesDialog;

public:
	GodNpc();
	~GodNpc();

	HRESULT init(NPC_CONDITION condition, NPC_TYPE type, const char* npcName, int value, POINT position);
	void update();
	void release();
	void render();
	
	void npcCreate(NPC_CONDITION condition, NPC_TYPE type, const char* npcName, int value);
	void setWeaponNpc(const char* npcName, int value);
	void setFoodNpc(const char* npcName, int value);
	void collision();
};

