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
	changeFrame();
	move();
}

void Enemy::render()
{
	_img->frameRender(DC, _rc.left, _rc.top, _frameX, _frameY);
}

void Enemy::changeFrame()
{
	_count++;
	if (_count % 2 == 0)
	{
		if (_frameX >= _img->getMaxFrameX())
			_frameX = 0;

		_img->setFrameX(_frameX);
		_frameX++;

		_count = 0;
	}
}

void Enemy::move()
{
	_x = cosf(_angle)* _speed;
	_y = -sinf(_angle) * _speed;

	_rc = RectMake(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
}

bool Enemy::bulletCountFire()
{
	_fireCount++;
	if (_fireCount % _rndFireCount == 0)
	{
		_fireCount = 0;
		_rndFireCount = RND->getFromIntTo(1, 1000);

		return true;
	}

	return false;
}

void Enemy::setAngle(float angle)
{
	_angle = angle;
}


void Enemy::setPoint(float x, float y)
{
	_x = x;
	_y = y;
}