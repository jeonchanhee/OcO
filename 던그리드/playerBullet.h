#pragma once
#include "gameNode.h"

struct PBULLET
{
	image * bulletImage;
	RECT rc;
	float fireX,x;
	float fireY,y;
	float angle;
	float speed;
	float range;
	int type;
	int frameX, frameY;
	int frameCount;
	bool isAlive;
};
class playerBullet : public gameNode
{
private:
	vector<PBULLET> _vPBullet;
	vector<PBULLET>::iterator _viPBullet;

	const char * _iN0;
	const char * _iN1;
	const char * _iN2;
	const char * _iN3;

	unsigned int _count;

public:
	HRESULT init(const char * in0 , const char * in1, const char * in2, const char * in3 );
	
	void release();
	void update();
	void render();
	
	void bulletFire(float x, float y, float angle, float range ,float speed, int type);
	void move();
	void removeBullet(int i);
	
	vector<PBULLET> getvPBullet() { return _vPBullet; }
	vector<PBULLET>::iterator getviPBullet() { return _viPBullet; }
	playerBullet();
	~playerBullet();
};

