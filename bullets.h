#pragma once
#include "gameNode.h"
#include <vector>


struct tagBullet
{
	image*	bulletImage;		//총알의 이미지
	RECT	rc;					//총알 렉트
	float	x, y;				//총알 좌표
	float	angle;				//총알 각도
	float	radius;				//총알 붼지름
	float	speed;				//총알 스피드
	float	fireX, fireY;		//총알 발사위치 저장변수
	bool	isFire;				//발사했늬?
	int		count;				//프레임 이미지 용!
};

//누구나 사용할 수 있는 총알
class bullet : public gameNode
{
private:
	vector<tagBullet>			_vBullet;
	vector<tagBullet>::iterator _viBullet;

	const char* _imageName;
	float _range;
	int _bulletMax;

public:
	bullet();
	~bullet();

	HRESULT init(const char* imageName, int bulletMax, float range);
	void release(); 
	void update(); 
	void render();

	void bulletFire(float x, float y, float angle, float speed);

	void bulletMove();

	void removeBullet(int arrNum);

	//에너미 뷸렛 벡터 접근자
	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getVIBullet() { return _viBullet; }


};



//생성해놓고 발사하는 미쏼~
class missile : public gameNode
{
private:
	vector<tagBullet>				_vBullet;
	vector<tagBullet>::iterator		_viBullet;

	float _range;	//사거리 변수

public:
	missile();
	~missile();

	HRESULT init(int bulletMax, float range);	//총알몇개,사거리얼마
	void release(void);
	void update(void);
	void render(void);

	//총알 발사 함수 (총알 나갈위치 x, y)
	void fire(float x, float y);

	void move(void);
};

//발사할때 생성해서 쏘는 미쏼~
class minho : public gameNode
{
private:
	vector<tagBullet>			_vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range;		//사거리 변수
	int _bulletMax;		//최대 장탄 수
public:
	minho();
	~minho();

	HRESULT init(int missileMax, float range);
	void release();
	void update();
	void render();

	void fire(float x, float y);

	void move();

	void removeMinho(int arrNum);

	//민호미쏼 접근자
	vector<tagBullet> getVMinho() { return _vBullet; }
	vector<tagBullet>::iterator getVIMinho() { return _viBullet; }

};