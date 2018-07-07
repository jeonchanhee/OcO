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

struct torch
{
	image* img;
	int x, y;
};

struct Door
{
	image* img;
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

	MusicAngel* _musicAngel;

	Bullet* _enemyBullet;

	torch	_torch;		// ȶ��
	Door	_door;		// ��
	Portal	_portal;	// ��Ż
	string _mapName;
	int _dungeonNum;
	int _temp;

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

	//���� �Ѿ� ���� �Լ�
	void MusicAngelBulletFire(); //��ǥ���� �Ѿ� �߻� �Լ�
	//void ArrowBulletFire();		 //Ȱ���� �Ѿ� �߻� �Լ�
	void BossBulletFire();		 //���� �Ѿ� �߻� �Լ�
};

