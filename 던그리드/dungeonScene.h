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

class RandomDungeon1;

enum DOOR_STATE { DOOR_OPEN, DOOR_IDLE, DOOR_CLOSE };
enum DOOR_DIR { DOOR_LEFT, DOOR_RIGHT, DOOR_UPDOWN };

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
	int frameX, frameY;
	int count;
	DOOR_STATE state;
	DOOR_DIR dir;
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

	torch	_torch;		// È¶ºÒ
	//Door	_door;		// ¹®
	vector<Door> _door;
	Portal	_portal;	// Æ÷Å»
	string _mapName;
	int _randNum;
	int _dungeonNum;
	int _temp;
	string _mapValue[11];

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

	void setDoor();

	void doorRender();

	dungeonScene();
	~dungeonScene();

	void setDogBone(int idX, int idY); //°³»À
	void setBigBone(int idX, int idY, int index); //Å«Ä®»À
	void setArrow(int idX, int idY); //È°ÀïÀÌ
	void setBat(int idX, int idY); //ÀÛº¸¹Ú
	void setRedBat(int idX, int idY); //ÀÛ»¡¹Ú
	void setBigBat(int idX, int idY); //Å«º¸¹Ú
	void setBigRedBat(int idX, int idY); //Å«»¡¹Ú
	void setMusicAngel(int idX, int idY); //À½Ç¥¿äÁ¤
	void setCow(int idX, int idY); //¼Ò
	void setBoss(); //º¸½º

	void setRandomDungeonLink(RandomDungeon1* random) { _random = random; }
};

