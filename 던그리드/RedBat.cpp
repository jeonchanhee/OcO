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

	_redBatDirection = REDBAT_RIGHT_MOVE;

	_img = IMAGEMANAGER->findImage("redBatMoveAttackDie");
	
	//Move
	KEYANIMANAGER->addCoordinateFrameAnimation("redBatRightMove", "redBatMoveAttackDie", 0, 7, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("redBatLeftMove", "redBatMoveAttackDie", 8, 15, 10, false, true);
	//Attack
	KEYANIMANAGER->addCoordinateFrameAnimation("redBatRightAttack", "redBatMoveAttackDie", 16, 23, 10, false, false, rightAttack, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("redBatLeftAttack", "redBatMoveAttackDie", 24, 31, 10, false, false , leftAttack, this);
	//Die
	int rightDie[] = { 32 };
	KEYANIMANAGER->addArrayFrameAnimation("redBatRightDie", "redBatMoveAttackDie", rightDie, 1, 6, false);
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
	_count++;

	move();
	Attack();
	KEYANIMANAGER->update();
	
	/////////////////////////테스트/////////////////////////////
	//죽는모션
	if (KEYMANAGER->isOnceKeyDown(VK_F4))
	{
		if (_redBatDirection == REDBAT_RIGHT_MOVE)
		{
			changeAnimation(REDBAT_RIGHT_DIE);
		}
		if (_redBatDirection == REDBAT_LEFT_MOVE)
		{
			changeAnimation(REDBAT_LEFT_DIE);
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_F4))
	{
		if (_redBatDirection == REDBAT_RIGHT_DIE)
		{
			changeAnimation(REDBAT_RIGHT_MOVE);
		}
		if (_redBatDirection == REDBAT_LEFT_DIE)
		{
			changeAnimation(REDBAT_LEFT_MOVE);
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
		case REDBAT_RIGHT_MOVE:
			rightMove();
		break;
		case REDBAT_LEFT_MOVE:
			leftMove();
		break;
		default:
			_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	}

}

void RedBat::rightMove()
{
	if (_count % 10 == 0)
	{
		_angle -= PI2 / 36;
	
	}

	_x = cosf(_angle)*_speed + _startX;
	_y = -sin(_angle)*_speed + _startY;

	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
}

void RedBat::leftMove()
{
	if (_count % 10 == 0)
	{
		_angle += PI2 / 36;

	}

	_x = cosf(_angle)*_speed + _startX;
	_y = -sinf(_angle)*_speed + _startY;

	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
}

void RedBat::Attack()
{
	if (!(_count % 141))
	{
		if (_redBatDirection == REDBAT_RIGHT_MOVE)
			changeAnimation(REDBAT_RIGHT_ATTACK);
		if (_redBatDirection == REDBAT_LEFT_MOVE)
			changeAnimation(REDBAT_LEFT_ATTACK);
		
		_count = 0;
	}
}


void RedBat::changeAnimation(REDBATDIRECTION direction)
{
	switch (direction)
	{
	case REDBAT_RIGHT_MOVE:
		_img = IMAGEMANAGER->findImage("redBatMoveAttackDie");
		_redBatDirection = REDBAT_RIGHT_MOVE;
		_redBatMotion = KEYANIMANAGER->findAnimation("redBatRightMove");
		_redBatMotion->start();
		break;
	case REDBAT_LEFT_MOVE:
		_img = IMAGEMANAGER->findImage("redBatMoveAttackDie");
		_redBatDirection = REDBAT_LEFT_MOVE;
		_redBatMotion = KEYANIMANAGER->findAnimation("redBatLeftMove");
		_redBatMotion->start();
		break;
	case REDBAT_RIGHT_ATTACK:
		_img = IMAGEMANAGER->findImage("redBatMoveAttackDie");
		_redBatDirection = REDBAT_RIGHT_ATTACK;
		_redBatMotion = KEYANIMANAGER->findAnimation("redBatRightAttack");
		_redBatMotion->start();
		break;
	case REDBAT_LEFT_ATTACK:
		_img = IMAGEMANAGER->findImage("redBatMoveAttackDie");
		_redBatDirection = REDBAT_LEFT_ATTACK;
		_redBatMotion = KEYANIMANAGER->findAnimation("redBatLeftAttack");
		_redBatMotion->start();
		break;
	case REDBAT_RIGHT_DIE:
		_img = IMAGEMANAGER->findImage("redBatMoveAttackDie");
		_redBatDirection = REDBAT_RIGHT_DIE;
		_redBatMotion = KEYANIMANAGER->findAnimation("redBatRightDie");
		_redBatMotion->start();
		break;
	case REDBAT_LEFT_DIE:
		_img = IMAGEMANAGER->findImage("redBatMoveAttackDie");
		_redBatDirection = REDBAT_LEFT_DIE;
		_redBatMotion = KEYANIMANAGER->findAnimation("redBatLeftDie");
		_redBatMotion->start();
		break;
	}
}

void RedBat::rightAttack(void * obj)
{
	RedBat* rb = (RedBat*)obj;

	rb->_img = IMAGEMANAGER->findImage("redBatMoveAttackDie");
	rb->setRedBatDirection(REDBAT_RIGHT_MOVE);
	rb->setRedBatMotion(KEYANIMANAGER->findAnimation("redBatRightMove"));
	rb->getRedBatMotion()->start();
}
void RedBat::leftAttack(void * obj)
{
	RedBat* rb = (RedBat*)obj;

	rb->_img = IMAGEMANAGER->findImage("redBatMoveAttackDie");
	rb->setRedBatDirection(REDBAT_LEFT_MOVE);
	rb->setRedBatMotion(KEYANIMANAGER->findAnimation("redBatLeftMove"));
	rb->getRedBatMotion()->start();
}