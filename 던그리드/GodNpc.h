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

	NPCTYPE _type;		// ���ǽ� Ÿ��
	image* _image;		// ���ǽ� �̹���
	RECT _npcInven[10]; // ���ǽ� �κ��丮
	RECT _rc;			// ���ǽ� ��Ʈ
	float _npcX, _npcY;	// ���ǽ� x, y ��ǥ
	int _count;			// ������ ī��Ʈ ��������

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

