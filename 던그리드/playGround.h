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
#include "EnemyManager.h"
#include "itemManager.h"
#include "introScene.h"
#include "mapSelectScene.h"

enum changeMode { 맵툴, 타이틀, 다이얼로그, 도그본, 플레이어, 아이템, 인트로, 던전, 맵선택, 기타추가하셈 , 알게뜸};

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

	void load();
	void printMap();


	playGround();
	~playGround();
};

