#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet(){}

Bullet::~Bullet(){}

HRESULT Bullet::init(int bulletMax)
{
	_bulletMax	= bulletMax;
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

	tagBullet bullet;
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
		_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;

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
