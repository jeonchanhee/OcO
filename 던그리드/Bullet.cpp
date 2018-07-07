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
	bulletFrameX();
	bulletFrameY();
}

void Bullet::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); _viBullet++)
	{
		if (!_viBullet->isFrame) _viBullet->img->frameRender(DC, _viBullet->rc.left, _viBullet->rc.top);
		else _viBullet->img->frameRender(DC, _viBullet->rc.left, _viBullet->rc.top, _viBullet->frameX, _viBullet->frameY);

		if (KEYMANAGER->isToggleKey('E'))RectangleMake(DC, _viBullet->rc.left, _viBullet->rc.top, _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());
	}
}

void Bullet::bulletFire(const char* imgName, float x, float y, float angle, float speed, float range, bool isFrame, FRAMEXY frameXY)
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
	bullet.isFrame = isFrame;
	bullet.frameXY = frameXY;
	bullet.frameIndex = bullet.frameX = bullet.frameY = 0;

	bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.img->getFrameWidth(), bullet.img->getFrameHeight());
	
	_vBullet.push_back(bullet);
}

void Bullet::bulletMove()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;

		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());
				
		if (_viBullet->range < getDistance(_viBullet->x, _viBullet->y, _viBullet->fireX, _viBullet->fireY))
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else _viBullet++;
	}

}

void Bullet::bulletFrameX()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->isFrame) continue;
		if (_viBullet->frameXY != WIDTH) continue;

		_viBullet->frameIndex += 1;

		if (_viBullet->frameIndex % 6 == 0)
		{
			_viBullet->frameX += 1;
			if (_viBullet->frameX > _viBullet->img->getMaxFrameX()) _viBullet->frameX = 0;
			_viBullet->frameIndex = 0;
		}
	}
}

void Bullet::bulletFrameY(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		if (!_viBullet->isFrame || _viBullet->frameXY != HEIGHT)
		{
			_viBullet++;
			continue;
		}
		
		_viBullet->frameIndex += 1;
		if (_viBullet->frameIndex % 10 == 0)
		{
			_viBullet->frameY += 1;
			_viBullet->frameIndex = 0;
		}
		
		if (_viBullet->frameY > _viBullet->img->getMaxFrameY())
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
