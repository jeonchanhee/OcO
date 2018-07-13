#include "stdafx.h"
#include "playerBullet.h"



HRESULT playerBullet::init(const char * in0, const char * in1, const char * in2, const char * in3, const char * iN4)
{
	_iN0 = in0;
	_iN1 = in1;
	_iN2 = in2;
	_iN3 = in3;
	_iN4 = iN4;
	_count = 0;

	return S_OK;
}

void playerBullet::release(){}

void playerBullet::update()
{
	move();

	for (_viPBullet = _vPBullet.begin(); _viPBullet != _vPBullet.end(); ++_viPBullet)
	{
		_viPBullet->frameCount++;
		if (_viPBullet->frameCount > 7)
		{
			_viPBullet->frameCount = 0;
			_viPBullet->frameX += 1;
			if (_viPBullet->frameX >= _viPBullet->bulletImage->getMaxFrameX())
			{
				_viPBullet->frameX = 0;
			}
		}
	}	
}

void playerBullet::render()
{
	for (_viPBullet = _vPBullet.begin(); _viPBullet != _vPBullet.end(); ++_viPBullet)
	{
		if(_viPBullet->type == 4)_viPBullet->bulletImage->render(DC, _viPBullet->x, _viPBullet->y);
		else _viPBullet->bulletImage->rotateFrameRender(DC, _viPBullet->x, _viPBullet->y, _viPBullet->frameX, _viPBullet->frameY , _viPBullet->renderAngle);
	}
}

void playerBullet::bulletFire(float x, float y, float angle, float renderAngle, float range, float speed, int type)
{
	PBULLET bullet;
	if (type == 0)	   bullet.bulletImage = IMAGEMANAGER->findImage(_iN0);
	else if (type == 1)bullet.bulletImage = IMAGEMANAGER->findImage(_iN1);
	else if (type == 2)bullet.bulletImage = IMAGEMANAGER->findImage(_iN2);
	else if (type == 3)bullet.bulletImage = IMAGEMANAGER->findImage(_iN3);
	else if (type == 4)bullet.bulletImage = IMAGEMANAGER->findImage(_iN4);
	bullet.x = bullet.fireX = x,	bullet.y = bullet.fireY = y;
	bullet.angle = angle, bullet.renderAngle = renderAngle , bullet.range = range, bullet.speed = speed;
	bullet.frameX = bullet.frameY = 0;
	bullet.frameCount = 0;
	bullet.bulletImage->setFrameX(0);
	bullet.type = type;

	_vPBullet.push_back(bullet);
}

void playerBullet::move()
{
	for (_viPBullet = _vPBullet.begin(); _viPBullet != _vPBullet.end();)
	{
		_viPBullet->x += cosf(_viPBullet->angle) * _viPBullet->speed;
		_viPBullet->y += -sinf(_viPBullet->angle) * _viPBullet->speed;
		_viPBullet->rc = RectMakeCenter(_viPBullet->x, _viPBullet->y,
		_viPBullet->bulletImage->getFrameWidth(), _viPBullet->bulletImage->getFrameHeight());

		int distance = getDistance(_viPBullet->x, _viPBullet->y, _viPBullet->fireX, _viPBullet->fireY);
		if (distance >= _viPBullet->range)
		{
			_viPBullet = _vPBullet.erase(_viPBullet);
			
		}
		else _viPBullet++;
	}
	
}

void playerBullet::removeBullet(int i)
{
	_vPBullet.erase(_vPBullet.begin() + i);
}


playerBullet::playerBullet(){}
playerBullet::~playerBullet(){}
