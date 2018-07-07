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

	MusicAngel* _musicAngel;
	BigBat*		_bigbat;
	BigRedBat*	_bigRedBat;

	Bullet* _enemyBullet;
	Bullet2* _enemtBullet2;
	torch	_torch;		// ȶ��
	//Door	_door;		// ��
	vector<Door> _door;
	Portal	_portal;	// ��Ż
	string _mapName;
	int _randNum;
	int _dungeonNum;
	int _temp;
	string _mapValue[11];

	int _count;
	int _count2;

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

	//���� ���� �Լ�
	void setDogBone(int idX, int idY); //����
	void setBigBone(int idX, int idY, int index); //ūĮ��
	void setArrow(int idX, int idY); //Ȱ����
	void setBat(int idX, int idY); //�ۺ���
	void setRedBat(int idX, int idY); //�ۻ���
	void setBigBat(int idX, int idY); //ū����
	void setBigRedBat(int idX, int idY); //ū����
	void setMusicAngel(int idX, int idY); //��ǥ����
	void setCow(int idX, int idY); //��
	void setBoss(); //����

	void setRandomDungeonLink(RandomDungeon1* random) { _random = random; }

	//���� �Ѿ� ���� �Լ�
	void MusicAngelBulletFire(); //��ǥ���� �Ѿ� �߻� �Լ�
	//void ArrowBulletFire();		 //Ȱ���� �Ѿ� �߻� �Լ�
	void BossBulletFire();		 //���� �Ѿ� �߻� �Լ�
	void bigbatbulletFire();
	void bigRadbatbulletFire();
};

