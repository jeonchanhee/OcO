#pragma once
#include "gameNode.h"
#include <vector>

enum FRAMEXY
{
	WIDTH,
	HEIGHT
};

struct tagBullet
{
	image*	img;			// 총알이미지
	RECT	rc;				// 렉트
	float	x, y;			// 총알 좌표
	float	angle;			// 총알각도
	float	speed;			// 총알 스피드
	float	radius;			// 총알 반지름
	float	fireX, fireY;	// 발사위치
	bool	isFire;			// 발사여부
	float   range;
	bool	isFrame;
	FRAMEXY frameXY;
	int		frameIndex;
	int		frameX, frameY;
	int		bulletNum;		// 원형이동인지 체크
	int		swordIdx;
};

class Bullet : public gameNode
{
private:
	vector<tagBullet>			_vBullet;
	vector<tagBullet>::iterator	_viBullet;

	tagBullet bullet;

	int			_bulletMax;		// 최대 총알 갯수
	int			_index;			// 프레임 인덱스값
	int			_count;

public:
	Bullet();
	~Bullet();

	HRESULT init(int bullletMax);
	void	release();
	void	update();
	void	render();

	void	bulletFire(const char* imgName, float x, float y, float angle, float speed, float range, bool isFrame = false, FRAMEXY frameXY = WIDTH, int swordNum = -1);		// 발사
	void	swordRender();
	void	changeSpeedAndAngle(float x, float y);
	void	bulletMove();												// 이동
	void	bulletFrameX(void);												// 총알 프레임
	void	bulletFrameY(void);
	void	removeBullet(int arrNum);									// 총알 지워줄때
	void	bulletframe(const char* imgName);

	// 총알 벡터 접근자
	vector<tagBullet>			getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator	getVIBullet() { return _viBullet; }

	FRAMEXY getFrameXY(int i) { return _vBullet[i].frameXY; }
};

class Bullet2 : public gameNode
{
private:
	vector<tagBullet>			_vBullet2;
	vector<tagBullet>::iterator	_viBullet2;

	tagBullet bullet2;

	int			_bulletMax;		// 최대 총알 갯수
	int			_index;			// 프레임 인덱스값
	int			_count2;
	int			_count;
	int			j;
	int			start;
public:
	Bullet2();
	~Bullet2();

	HRESULT init(int bullletMax);
	void	release();
	void	update();
	void	render();

	void	bulletFire(const char* imgName, float x, float y, float angle, float speed, float range);
	void	bulletMove();												// 이동
	void	removeBullet(int arrNum);									// 총알 지워줄때
	void	bulletframe(const char* imgName);

	// 총알 벡터 접근자
	vector<tagBullet>			getVBullet() { return _vBullet2; }
	vector<tagBullet>::iterator	getVIBullet() { return _viBullet2; }

	tagBullet getbullet2() { return bullet2; }

};

