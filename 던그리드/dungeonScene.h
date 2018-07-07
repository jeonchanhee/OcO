#pragma once
#include "gameNode.h"
#include "Enemy.h"
#include "Arrow.h"
#include "BigBone.h"
#include "Bat.h"
#include "RedBat.h"
#include "DogBone.h"
#include "BigBat.h"
#include "BigRedBat.h"
#include "MusicAngel.h"
#include "Cow.h"
#include "Boss2.h"
#include "Bullet.h"

class RandomDungeon1;

struct torch
{
	image* img;
	int x, y;
};

struct Door
{
	image* img;
	RECT rc;
	int x, y;
};

struct Portal
{
	image* img;
	int x, y;
};

class dungeonScene : public gameNode
{
protected:
	vector<Enemy*>					_vEnemy;
	vector<Enemy*>::iterator		_viEnemy;

	vector<int> _route;
	RandomDungeon1* _random;

	MusicAngel* _musicAngel; //음표요정
	Boss2* _boss;			 //보스

	Bullet* _enemyBullet;

	torch	_torch;		// 횃불
	//Door	_door;		// 문
	vector<Door> _door;
	Portal	_portal;	// 포탈
	string _mapName;
	int _randNum;
	int _dungeonNum;
	int _temp;
	string _mapValue[11];

	int _count;
	

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void mapload();

	void setCamera(void);

	void selectSize(int idx);

	void chooseMap(int idx);

	void nextTest();

	void load();

	void save();

	dungeonScene();
	~dungeonScene();

	//몬스터 생성 함수
	void setDogBone(int idX, int idY); //개뼈
	void setBigBone(int idX, int idY, int index); //큰칼뼈
	void setArrow(int idX, int idY); //활쟁이
	void setBat(int idX, int idY); //작보박
	void setRedBat(int idX, int idY); //작빨박
	void setBigBat(int idX, int idY); //큰보박
	void setBigRedBat(int idX, int idY); //큰빨박
	void setMusicAngel(int idX, int idY); //음표요정
	void setCow(int idX, int idY); //소
	void setBoss(); //보스

	void setRandomDungeonLink(RandomDungeon1* random) { _random = random; }

	//몬스터 총알 생성 함수
	void MusicAngelBulletFire(); //음표요정 총알 발사 함수
	void BossBulletFire();		 //보스 총알 발사 함수
};

