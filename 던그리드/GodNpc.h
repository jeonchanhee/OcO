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

	NPC_CONDITION _condition;	// ���ǽ� ����
	NPC_TYPE _type;				// ���ǽ� Ÿ��
	image* _img;				// ���ǽ� �̹���
	RECT _rc;					// ���ǽ� ��Ʈ
	const char* _npcName;		// ���ǽ� �̸�
	float _npcX, _npcY;			// ���ǽ� x, y ��ǥ
	int _value;					// ���� ���ǽ� ����
	int _frameX, _frameY;		// ������ X, Y 
	int _count;					// ������ ī��Ʈ ��������


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

