#pragma once
#include "gameNode.h"

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

private:

	NPC_CONDITION _condition;	// ���ǽ� ����
	NPC_TYPE _type;				// ���ǽ� Ÿ��
	image* _img;				// ���ǽ� �̹���
	RECT _rc;				// ���ǽ� ��Ʈ
	const char* _npcName;		// ���ǽ� �̸�
	float _npcX, _npcY;			// ���ǽ� x, y ��ǥ
	int _value;					// ���� ���ǽ� ����
	int _frameX, _frameY;		// ������ X, Y 
	int _count;					// ������ ī��Ʈ ��������
	bool _leftStop;				// �������� �����ֳ� 
	bool _rightStop;			// ���������� �����ֳĤ�

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
};

