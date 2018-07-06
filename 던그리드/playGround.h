#pragma once
#include "gameNode.h"
#include "MapTool.h"
#include "titleScene.h"
#include "dunGeonScene.h"
#include "DialogWeapon.h"
#include "Player.h"
#include "DialogTownStore.h"
#include "DialogElder.h"
#include "DialogStore.h"
#include "DialogTraining.h"
#include "Dialog.h"
#include "dungeon2Scene.h"
#include "dungeon3Scene.h"
#include "dungeon4Scene.h"
#include "dungeon5Scene.h"
#include "dungeon6Scene.h"
#include "dungeon7Scene.h"
#include "dungeon8Scene.h"
#include "itemManager.h"
#include "introScene.h"
#include "mapSelectScene.h"

enum changeMode { ����, Ÿ��Ʋ, ���̾�α�, ����, �÷��̾�, ������, ��Ʈ��, ����2, ����3, ����4, ����5, ����6, ����7, ����8, �ʼ���, ��Ÿ�߰��ϼ� };

class playGround : public gameNode
{
private:
	MapTool * _mapTool;
	Player *  _player;
	changeMode mode;
	itemManager* _im;
	titleScene* _title;

public:
	virtual HRESULT init(void);
	virtual HRESULT Image_init(void);
	virtual HRESULT Sound_init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);



	playGround();
	~playGround();
};

