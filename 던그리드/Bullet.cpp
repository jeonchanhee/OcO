#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet(){}

Bullet::~Bullet(){}

HRESULT Bullet::init(int bulletMax)
{
	_bulletMax	= bulletMax;
	_index = _count = 0;
	return S_OK;
}

void Bullet::release(){}

void Bullet::update()
{
	bulletMove();
}

void Bullet::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); _viBullet++)
	{
		_viBullet->img->frameRender(DC, _viBullet->rc.left, _viBullet->rc.top);
	}
}

void Bullet::bulletFire(const char* imgName, float x, float y, float angle, float speed, float range)
{
	if (_bulletMax < _vBullet.size()) return;

	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.img = IMAGEMANAGER->findImage(imgName);
	bullet.speed = speed;
	bullet.radius = bullet.img->getWidth() / 2;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.angle = angle;
	bullet.range = range;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.img->getWidth(), bullet.img->getHeight());

	_vBullet.push_back(bullet);
}

void Bullet::bulletMove()
{

	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle)* _viBullet->speed;

		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->img->getWidth(), _viBullet->img->getHeight());

		if (_viBullet->range < getDistance(_viBullet->x, _viBullet->y, _viBullet->fireX, _viBullet->fireY))
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else _viBullet++;
	}
}

void Bullet::removeBullet(int arrNum)
{
	_viBullet = _vBullet.begin() + arrNum;
	_vBullet.erase(_viBullet);
}

void Bullet::bulletframe(const char * imgName)
{
	_count++;

	bullet.img = IMAGEMANAGER->findImage(imgName);
	bullet.img->setFrameY(0);
	if (_index > bullet.img->getMaxFrameX()) _index = 0;

	bullet.img->setFrameX(_index);
	if(_count % 2 == 0) _index++;
}


Bullet2::Bullet2(){}

Bullet2::~Bullet2(){}

HRESULT Bullet2::init(int bulletMax)
{
	_bulletMax = bulletMax;
	_index = _count2 = 0;
	return S_OK;
}

void Bullet2::release()
{
}

void Bullet2::update()
{
	bulletMove();
}

void Bullet2::render()
{
	for (_viBullet2 = _vBullet2.begin(); _viBullet2 != _vBullet2.end(); _viBullet2++)
	{
		_viBullet2->img->frameRender(DC, _viBullet2->rc.left, _viBullet2->rc.top);
	}
}

void Bullet2::bulletFire(const char * imgName, float x, float y, float angle, float speed, float range)
{
	if (_bulletMax < _vBullet2.size()) return;

	ZeroMemory(&bullet2, sizeof(tagBullet));
	bullet2.img = IMAGEMANAGER->findImage(imgName);
	bullet2.speed = speed;
	bullet2.radius = bullet2.img->getWidth() / 2;
	bullet2.x = bullet2.fireX = x;
	bullet2.y = bullet2.fireY = y;
	bullet2.angle = angle;
	bullet2.range = range;
	bullet2.rc = RectMakeCenter(bullet2.x, bullet2.y, bullet2.img->getWidth(), bullet2.img->getHeight());

	_vBullet2.push_back(bullet2);
}

void Bullet2::bulletMove()
{

	for (_viBullet2 = _vBullet2.begin(); _viBullet2 != _vBullet2.end();)
	{
		_viBullet2->x += cosf(_viBullet2->angle) * _viBullet2->speed;
		_viBullet2->y += -sinf(_viBullet2->angle)* _viBullet2->speed;

		_viBullet2->rc = RectMakeCenter(_viBullet2->x, _viBullet2->y, _viBullet2->img->getWidth(), _viBullet2->img->getHeight());

		if (_viBullet2->range < getDistance(_viBullet2->x, _viBullet2->y, _viBullet2->fireX, _viBullet2->fireY))
		{
			_viBullet2 = _vBullet2.erase(_viBullet2);
		}
		else _viBullet2++;
	}
}

void Bullet2::removeBullet(int arrNum)
{
	_viBullet2 = _vBullet2.begin() + arrNum;
	_vBullet2.erase(_viBullet2);
}

void Bullet2::bulletframe(const char * imgName)
{
	_count2++;

	bullet2.img = IMAGEMANAGER->findImage(imgName);
	bullet2.img->setFrameY(0);
	if (_index > bullet2.img->getMaxFrameX()) _index = 0;

	bullet2.img->setFrameX(_index);
	if (_count2 % 2 == 0) _index++;
}
