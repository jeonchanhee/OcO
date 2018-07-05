#include "stdafx.h"
#include "Arrow.h"


Arrow::Arrow()
{
}


Arrow::~Arrow()
{
}

HRESULT Arrow::init()
{
	_arrow[0].img = IMAGEMANAGER->findImage("skeletonArcher");
	_arrow[1].img = IMAGEMANAGER->findImage("skeletonBow");
	_arrow[2].img = IMAGEMANAGER->findImage("arrow");

	_arrow[0].x = WINSIZEX / 2; 
	_arrow[1].x = _arrow[0].x + 70;
	_arrow[2].x = _arrow[1].x - _arrow[2].img->getFrameWidth() / 2;

	_arrow[0].y = WINSIZEY / 2;
	_arrow[1].y = _arrow[0].y + 60;
	_arrow[2].y = _arrow[1].y - 5;

	_bowCenter.x = _arrow[1].x;
	_bowCenter.y = _arrow[1].y;

	for (int i = 0; i < 3; i++)
	{
		_arrow[i].rc = RectMakeCenter(_arrow[i].x, _arrow[i].y, _arrow[i].img->getFrameWidth(), _arrow[i].img->getFrameHeight());
	}

	_angle =  0;
	_speed = _arrow[1].img->getFrameWidth() / 2;

	_isShoot = false;

	return S_OK;
}

void Arrow::release()
{
}

void Arrow::update()
{
	_count++;

	move();
	shootArrow();
	fireArrow();

	if (!(_count % 100))
	{
		_arrow[1].img->setFrameX(0);
	}

	for (int i = 0; i < 3; i++)
		_arrow[i].rc = RectMakeCenter(_arrow[i].x, _arrow[i].y, _arrow[i].img->getFrameWidth(), _arrow[i].img->getFrameHeight());
	
}

void Arrow::render()
{	
	_arrow[0].img->frameRender(DC, _arrow[0].x, _arrow[0].y);
	_arrow[1].img->rotateFrameRender(DC, _arrow[1].x, _arrow[1].y, _angle);
	_arrow[2].img->rotateRender(DC, _arrow[2].x, _arrow[2].y, _angle);
}

void Arrow::move()
{
	if (_isShoot)
	{
		_arrow[2].x = cosf(_angle)*_speed + _bowCenter.x;
		_arrow[2].y = -sinf(_angle)*_speed + _bowCenter.y;
		_speed += 10;
	}

	if (!(_count % 10))
	{		
		if (_arrow[1].img->getFrameX() == _arrow[1].img->getMaxFrameX())
		{
			_isShoot = false;
			_arrow[1].img->setFrameX(0);
		}
		else _arrow[1].img->setFrameX(_arrow[1].img->getFrameX() + 1);
	}
}

void Arrow::shootArrow()
{
	if (_isShoot) return;

	_angle = GetAngle( _arrow[0].x, _arrow[0].y, PTMOUSE_X, PTMOUSE_Y);
	
	_arrow[1].x = _arrow[0].x + 70;
	_arrow[1].y = _arrow[0].y + 60;
	
}

void Arrow::fireArrow()
{
	if (_isShoot) return;

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		_angle = GetAngle(_arrow[0].x, _arrow[0].y, PTMOUSE_X, PTMOUSE_Y);

		_speed = _arrow[1].img->getFrameWidth() / 2;

		_isShoot = true;
	}
}
