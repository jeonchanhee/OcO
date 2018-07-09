#include "stdafx.h"
#include "Arrow.h"


Arrow::Arrow()
{
}


Arrow::~Arrow()
{
}

HRESULT Arrow::init(float x, float y)
{
	static int a = 0;
	++a;
	_index = a;
	char str[50];
	sprintf_s(str, "skeletonBow%d", _index);
	char str2[50];
	sprintf_s(str2, "skeletonArcher%d", _index);

	//_arrow[0].img = IMAGEMANAGER->findImage("skeletonArcher");
	_arrow[0].img = IMAGEMANAGER->addFrameImage(str2, "image/enemy/skeletonArcher(100X80,2X1).bmp", 0, 0, 100, 80, 2, 1, true, RGB(255, 0, 255));
	_arrow[1].img = IMAGEMANAGER->addRotateFrameImage(str, "image/enemy/skeletonBow2(150X25,6X1).bmp", 150, 25, 6, 1, true, RGB(255, 0, 255));
	_arrow[2].img = IMAGEMANAGER->findImage("arrow");

	_arrow[0].x = x;
	//_arrow[1].x = _arrow[0].x + 70;
	_arrow[1].x = _arrow[0].x + 40;
	_arrow[2].x = _arrow[1].x - _arrow[2].img->getFrameWidth() / 2 ;

	_arrow[0].y = y;
	_arrow[1].y = _arrow[0].y + 50;
	_arrow[2].y = _arrow[1].y - 2;

	_bowCenter.x = _arrow[1].x;
	_bowCenter.y = _arrow[1].y;

	for (int i = 0; i < 3; i++)
	{
		_arrow[i].rc = RectMake(_arrow[i].x, _arrow[i].y, _arrow[i].img->getFrameWidth(), _arrow[i].img->getFrameHeight());
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
	shootArrow();
	frameMove();
	fireArrow();

	//if (!(_count % 100))
	//{
	//	_arrow[1].img->setFrameX(0);
	//}

	for (int i = 0; i < 3; i++)
		_arrow[i].rc = RectMake(_arrow[i].x, _arrow[i].y, _arrow[i].img->getFrameWidth(), _arrow[i].img->getFrameHeight());
	
}

void Arrow::render()
{	
	_arrow[0].img->frameRender(DC, _arrow[0].x, _arrow[0].y);
	_arrow[2].img->rotateRender(DC, _arrow[2].x, _arrow[2].y, _angle);
	_arrow[1].img->rotateFrameRender(DC, _arrow[1].x, _arrow[1].y, _angle);

	if(KEYMANAGER->isToggleKey(VK_SPACE))
		Rectangle(DC, _arrow[0].rc.left, _arrow[0].rc.top, _arrow[0].rc.right, _arrow[0].rc.bottom);
}

void Arrow::frameMove()
{
	if (_isShoot)
	{
		//오른쪽 방향
		if (_arrow[0].x < PTMOUSE_X)
		{
			_arrow[2].x += cosf(_angle)*_speed;
			_arrow[2].y += -sinf(_angle)*_speed;
		}
		//왼쪽 방향
		if(_arrow[0].x > PTMOUSE_X)
		{
			_arrow[2].x += cosf(_angle) *_speed ;
			_arrow[2].y += -sinf(_angle) * _speed;
		}
		
		//_speed += 10;
	}

	if (!(_count % 10))
	{		
		//오른쪽 방향 이미지 설정
		if (_arrow[0].x < PTMOUSE_X)
		{
			_arrow[0].img->setFrameX(0);
		}
		//왼쪽 방향 이미지 설정
		if (_arrow[0].x > PTMOUSE_X)
		{
			_arrow[0].img->setFrameX(1);
		}

		if (_arrow[1].img->getFrameX() >= _arrow[1].img->getMaxFrameX())
		{
			_isShoot = false;
			_arrow[1].img->setFrameX(0);
		}
		else
		{
			_arrow[1].img->setFrameX(_arrow[1].img->getFrameX() + 1);
		}
	}
}

void Arrow::shootArrow()
{
	if (_isShoot) return;

	_angle = GetAngle( _arrow[0].x, _arrow[0].y, PTMOUSE_X, PTMOUSE_Y);
	
	//오른쪽 방향
	if (_arrow[0].x + _arrow[0].img->getFrameWidth() / 2 < PTMOUSE_X)
	{
		_arrow[1].x = _arrow[0].x + 40;
		_arrow[1].y = _arrow[0].y + 50;
		_arrow[2].x = _arrow[1].x - _arrow[2].img->getFrameWidth() / 2;
		_arrow[2].y = _arrow[1].y - 2;
	}
	//왼쪽 방향
	if (_arrow[0].x + _arrow[0].img->getFrameWidth() / 2 > PTMOUSE_X)
	{
		_arrow[1].x = _arrow[0].x + 10;
		_arrow[1].y = _arrow[0].y + 50;
		_arrow[2].x = _arrow[1].x;
		_arrow[2].y = _arrow[1].y - 3;
	}
}

//활쟁이가 마우스방향으로 활쏘게 하는 내용
void Arrow::fireArrow() 
{
	if (_isShoot) return;

	/*if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		_angle = GetAngle(_arrow[0].x, _arrow[0].y, PTMOUSE_X, PTMOUSE_Y);

		_speed = _arrow[1].img->getFrameWidth() / 2;

		_isShoot = true;
	}*/

	if (!(_count % 100))
	{
		_angle = GetAngle( _arrow[0].x, _arrow[0].y, PTMOUSE_X, PTMOUSE_Y);

		_speed = _arrow[1].img->getFrameWidth() / 2;

		_isShoot = true;
	}

}
