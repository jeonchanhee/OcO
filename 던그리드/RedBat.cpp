#include "stdafx.h"
#include "RedBat.h"


RedBat::RedBat()
{
}


RedBat::~RedBat()
{
}

HRESULT RedBat::init()
{
	_x = WINSIZEX / 2;
	_y = 200;
	_startX = WINSIZEX / 2;
	_startY = WINSIZEY / 2;
	_angle = 0;
	_speed = 300.0f;

	_redBatDirection = RIGHT_MOVE;

	_img = IMAGEMANAGER->findImage("redBatMoveAttackDie");
	
	//오른쪽 이동
	KEYANIMANAGER->addCoordinateFrameAnimation("redBatRightMove", "redBatMoveAttackDie", 0, 7, 10, false, true);
	//왼쪽 이동
	KEYANIMANAGER->addCoordinateFrameAnimation("redBatLeftMove", "redBatMoveAttackDie", 8, 15, 10, false, true);
	//오른쪽 공격
	KEYANIMANAGER->addCoordinateFrameAnimation("redBatRightAttack", "redBatMoveAttackDie", 16, 23, 10, false, false);
	//왼쪽 공격
	KEYANIMANAGER->addCoordinateFrameAnimation("redBatLeftAttack", "redBatMoveAttackDie", 24, 31, 10, false, true);
	//오른쪽 죽음
	int rightDie[] = { 32 };
	KEYANIMANAGER->addArrayFrameAnimation("redBatRightDie", "redBatMoveAttackDie", rightDie, 1, 6, false);
	//왼쪽 죽음
	int leftDie[] = { 33 };
	KEYANIMANAGER->addArrayFrameAnimation("redBatLeftDie", "redBatMoveAttackDie", leftDie, 1, 6, false);

	_redBatMotion = KEYANIMANAGER->findAnimation("redBatRightMove");
	_redBatMotion->start();

	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

	return S_OK;
}

void RedBat::release()
{
}

void RedBat::update()
{
	move();
	KEYANIMANAGER->update();
	
	/////////////////////////테스트/////////////////////////////
	//공격모션
	if (KEYMANAGER->isOnceKeyDown(VK_F4))
	{
		if (_redBatDirection == RIGHT_MOVE)
		{
			changeAnimation(RIGHT_ATTACK);
		}
		if (_redBatDirection == LEFT_MOVE)
		{
			changeAnimation(LEFT_ATTACK);
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_F4))
	{
		if (_redBatDirection == RIGHT_ATTACK)
		{
			changeAnimation(RIGHT_MOVE);
		}
		if (_redBatDirection == LEFT_ATTACK)
		{
			changeAnimation(LEFT_MOVE);
		}
	}

	//죽는모션
	if (KEYMANAGER->isOnceKeyDown(VK_F5))
	{
		if (_redBatDirection == RIGHT_MOVE)
		{
			changeAnimation(RIGHT_DIE);
		}
		if (_redBatDirection == LEFT_MOVE)
		{
			changeAnimation(LEFT_DIE);
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_F5))
	{
		if (_redBatDirection == RIGHT_DIE)
		{
			changeAnimation(RIGHT_MOVE);
		}
		if (_redBatDirection == LEFT_DIE)
		{
			changeAnimation(LEFT_MOVE);
		}
	}

	////////////////////////▲▲▲▲▲▲//////////////////////////////

}

void RedBat::render()
{
	_img->aniRender(DC, _rc.left, _rc.top, _redBatMotion);
}

void RedBat::move()
{
	switch (_redBatDirection)
	{
		case RIGHT_MOVE:
			rightMove();
		break;
		case LEFT_MOVE:
			leftMove();
		break;
		default:
			_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	}

}

void RedBat::rightMove()
{
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

void RedBat::leftMove()
{
	_count++;
	if (_count % 10 == 0)
	{
		_angle += PI2 / 36;

		_count = 0;
	}

	_x = cosf(_angle)*_speed + _startX;
	_y = -sinf(_angle)*_speed + _startY;

	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

}


void RedBat::changeAnimation(REDBATDIRECTION direction)
{
	switch (direction)
	{
	case RIGHT_MOVE:
		_img = IMAGEMANAGER->findImage("redBatMoveAttackDie");
		_redBatDirection = RIGHT_MOVE;
		_redBatMotion = KEYANIMANAGER->findAnimation("redBatRightMove");
		_redBatMotion->start();
		break;
	case LEFT_MOVE:
		_img = IMAGEMANAGER->findImage("redBatMoveAttackDie");
		_redBatDirection = LEFT_MOVE;
		_redBatMotion = KEYANIMANAGER->findAnimation("redBatLeftMove");
		_redBatMotion->start();
		break;
	case RIGHT_ATTACK:
		_img = IMAGEMANAGER->findImage("redBatMoveAttackDie");
		_redBatDirection = RIGHT_ATTACK;
		_redBatMotion = KEYANIMANAGER->findAnimation("redBatRightAttack");
		_redBatMotion->start();
		break;
	case LEFT_ATTACK:
		_img = IMAGEMANAGER->findImage("redBatMoveAttackDie");
		_redBatDirection = LEFT_ATTACK;
		_redBatMotion = KEYANIMANAGER->findAnimation("redBatLeftAttack");
		_redBatMotion->start();
		break;
	case RIGHT_DIE:
		_img = IMAGEMANAGER->findImage("redBatMoveAttackDie");
		_redBatDirection = RIGHT_DIE;
		_redBatMotion = KEYANIMANAGER->findAnimation("redBatRightDie");
		_redBatMotion->start();
		break;
	case LEFT_DIE:
		_img = IMAGEMANAGER->findImage("redBatMoveAttackDie");
		_redBatDirection = LEFT_DIE;
		_redBatMotion = KEYANIMANAGER->findAnimation("redBatLeftDie");
		_redBatMotion->start();
		break;
	}
}


/*

switch (direction)
{
case RIGHT_MOVE:
break;
case LEFT_MOVE:
break;
case RIGHT_ATTACK:
break;
case LEFT_ATTACK:
break;
case RIGHT_DIE:
break;
case LEFT_DIE:
break;
default:
break;
}

*/