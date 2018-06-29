#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy() {}

Enemy::~Enemy() {}

HRESULT Enemy::init()
{
	return S_OK;
}

HRESULT Enemy::init(const char* imageName, POINT position, float angle, float speed)
{
	_frameX = _frameY = 0;
	_count = _fireCount = _rndFireCount = 0;

	_x = position.x;
	_y = position.y;
	_angle = angle;
	_speed = speed;

	_img = IMAGEMANAGER->findImage(imageName);
	_rc = RectMake(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

	return S_OK;
}

void Enemy::release()
{
}

void Enemy::update()
{

}

void Enemy::render()
{
}

