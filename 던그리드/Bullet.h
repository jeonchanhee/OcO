#pragma once
#include "gameNode.h"
#include <vector>

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
};

class Bullet : public gameNode
{
private:
	vector<tagBullet>			_vBullet;
	vector<tagBullet>::iterator	_viBullet;

	const char* _imgName;		// 찾을 이미지
	float		_range;			// 총알 사거리
	int			_bulletMax;		// 최대 총알 갯수
public:
	Bullet();
	~Bullet();

	HRESULT init(const char* imageName, float range, int bullletMax);
	void	release();
	void	update();
	void	render();

	void	bulletFire(float x, float y, float angle, float speed);		// 발사
	void	bulletMove();												// 이동
	void	removeBullet(int arrNum);									// 총알 지워줄때

	// 총알 벡터 접근자
	vector<tagBullet>			getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator	getVIBullet() { return _viBullet; }

};

