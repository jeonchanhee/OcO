#include "stdafx.h"
#include "Bat.h"


Bat::Bat()
{
}


Bat::~Bat()
{
}

HRESULT Bat::init()
{
	_batDirection = BAT_LEFT_MOVE;

	_x = WINSIZEX / 2;
	_y = 200;

	_startX = WINSIZEX / 2;
	_startY = WINSIZEY / 2;

	_angle = 0;
	_speed = 300.0f;

	_img = IMAGEMANAGER->findImage("batMoveDie");

	//오른쪽 이동
	KEYANIMANAGER->addCoordinateFrameAnimation("batRightMove", "batMoveDie", 0, 5, 10, false, true);
	//왼쪽 이동
	KEYANIMANAGER->addCoordinateFrameAnimation("batLeftMove", "batMoveDie", 7, 12, 10, false, true);
	//오른쪽 죽음
	int rightDie[] = { 6 };
	KEYANIMANAGER->addArrayFrameAnimation("batRightDie", "batMoveDie", rightDie, 1, 6, false);
	//왼쪽 죽음
	int leftDie[] = { 13 };
	KEYANIMANAGER->addArrayFrameAnimation("batLeftDie", "batMoveDie", leftDie, 1, 6, false);

	_batMotion = KEYANIMANAGER->findAnimation("batLeftMove");
	_batMotion->start();

	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());


	return S_OK;
}

void Bat::release()
{
}

void Bat::update()
{
	move();

	///////////////////DIE테스트////////////////////
	if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		if (_batDirection == BAT_RIGHT_MOVE)
		{
			changeAnimation(BAT_RIGHT_DIE);
		}
		if (_batDirection == BAT_LEFT_MOVE)
		{
			changeAnimation(BAT_LEFT_DIE);
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_F3))
	{
		if (_batDirection == BAT_RIGHT_DIE)
		{
			changeAnimation(BAT_RIGHT_MOVE);
		}
		if (_batDirection == BAT_LEFT_DIE)
		{
			changeAnimation(BAT_LEFT_MOVE);
		}
	}
	///////////////////▲▲▲▲▲▲▲▲////////////////////
	KEYANIMANAGER->update();
}

void Bat::render()
{
	_img->aniRender(DC, _rc.left, _rc.top, _batMotion);
}

void Bat::move()
{
	switch (_batDirection)
	{
		case BAT_RIGHT_MOVE:
			rightMove();
		break;
		case BAT_LEFT_MOVE:
			leftMove();
		break;
		default:
			_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	}

}

void Bat::changeAnimation(BATDIRECTION direction)
{
	switch (direction)
	{
	case BAT_RIGHT_MOVE:
		_img = IMAGEMANAGER->findImage("batMoveDie");
		_batDirection = BAT_RIGHT_MOVE;
		_batMotion = KEYANIMANAGER->findAnimation("batRightMove");
		_batMotion->start();
		break;
	case BAT_LEFT_MOVE:
		_img = IMAGEMANAGER->findImage("batMoveDie");
		_batDirection = BAT_LEFT_MOVE;
		_batMotion = KEYANIMANAGER->findAnimation("batLeftMove");
		_batMotion->start();
		break;
	case BAT_RIGHT_DIE:
		_img = IMAGEMANAGER->findImage("batMoveDie");
		_batDirection = BAT_LEFT_DIE;
		_batMotion = KEYANIMANAGER->findAnimation("batRightDie");
		_batMotion->start();
		break;
	case BAT_LEFT_DIE:
		_img = IMAGEMANAGER->findImage("batMoveDie");
		_batDirection = BAT_LEFT_DIE;
		_batMotion = KEYANIMANAGER->findAnimation("batLeftDie");
		_batMotion->start();
		break;
	}
}

void Bat::rightMove()
{
	//방향 전환
	_count++;
	if (_count % 10 == 0)
	{
		_angle -= PI2 / 36;
		
		_count = 0;
	}

	_x = cosf(_angle)*_speed + _startX;
	_y = -sin(_angle)*_speed + _startY;

	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

}

void Bat::leftMove()
{
	//방향 전환
	_count++;
	if (_count % 10 == 0)
	{
		_angle += PI2 / 36;

		_count = 0;
	}

	_x = cosf(_angle)*_speed + _startX;
	_y = -sin(_angle)*_speed + _startY;

	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

}