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

enum changeMode { 맵툴, 타이틀, 다이얼로그, 몬스터, 플레이어, 아이템, 인트로, 던전2, 던전3, 던전4, 던전5, 던전6, 던전7, 던전8, 맵선택, 기타추가하셈 };

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

