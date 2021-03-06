#pragma once
#define MAX_BULLET 20
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
#include "minimap.h"
#include "effect.h"
#include "itemManager.h"


class Player;

enum DOOR_STATE { DOOR_OPEN, DOOR_IDLE, DOOR_CLOSE };
enum DOOR_DIR { DOOR_LEFT, DOOR_RIGHT, DOOR_UPDOWN };


struct torch
{
	image* img;
	animation* ani;
	float x, y;
};

struct Door
{
	image* img;
	RECT rc;
	int x, y;
	int frameX, frameY;
	int count;
	DOOR_STATE state;
	DOOR_DIR dir;
};

struct Portal
{
	image* img;
	int x, y;
	int frameX, frameY, count;
};

struct minimapIcon
{
	image* img;
	float x, y;
	RECT rc;
	int dungeonNum;
};

class dungeonScene : public gameNode
{
protected:
	vector<Enemy*>					_vEnemy;
	vector<Enemy*>::iterator		_viEnemy;

	vector<int> _route;
	
	Player* _player;
	BigBat*		_bigbat;
	BigRedBat*	_bigRedBat;
	RedBat*		_redBat;
	MusicAngel* _musicAngel; //음표요정
	Boss2* _boss;			 //보스
	int _bossLaserHitCount[2];
	bool _bossLaserHit[2];

	Bullet* _enemyBullet;
	Bullet* _bigBatBullet;
	Bullet2* _bigRadBatBullet[MAX_BULLET];
	Bullet2* _radBatBullet;

	effect* _effect;

	itemManager* _item;

	vector<Door> _vDoor; //문
	vector<torch> _vTorch; //횃불
	vector<Portal> _vPortal; //포탈
	
	string _mapName;
	int _randNum;
	int _temp;
	string _mapValue[11];

	int _count;
	int _count2;
	int _count3;
	int _count4;
	int  j;
	int _start;
	int _start2;

	int _swordCount;

	minimap* _minimap;
	image*	_tabMap;
	minimapIcon _minimapIcon[11];
	minimapIcon _miniPortal[4];
	float _movePortal[2][2];
	bool _isClickPortal;
	string _floorName;

	bool _diecount2;
	
	image* _img;
	animation* _suck;
	bool _suckFin;
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	virtual void doorInit(void);
	virtual void torchInit(int x, int y);
	void portalInit(float x, float y);
	virtual void setRandMapNum(void);

	void mapload();

	void setMinimap();

	void setMinimapXY();

	void setDoorMinimap();

	void setCamera(void);

	void selectSize(int idx);

	void chooseMap(int idx);

	void minimapIconRender();

	void nextTest();

	void load();
	void save();

	
	void setDoor();
	void doorRender();
	void portalRender();

	void collision();
	void musicAngelBulletCollision();
	void bossBulletCollision();
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

	void setRandomDungeonLink(Player* player) { _player = player; }

	//몬스터 총알 생성 함수
	void MusicAngelBulletFire(); //음표요정 총알 발사 함수
	void BossBulletFire();		 //보스 총알 발사 함수
	void bigbatbulletFire();
	void bigRadbatbulletFire();
	void redBatBullet();

	// 몬스터 총알 충돌 함수
	void bigbatBulletCollision();
	void bigRadbatBulletCollision();
	void redBatBulletCollision();
	void playerDie();
	void reward();
};

