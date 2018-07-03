#include "stdafx.h"
#include "BigBat.h"


BigBat::BigBat()
{
}


BigBat::~BigBat()
{
}

HRESULT BigBat::init()
{
	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2;
	
	_bigBatDirection = LEFT_MOVE;

	_img = IMAGEMANAGER->findImage("giantBat");

	//오른쪽 움직임
	KEYANIMANAGER->addCoordinateFrameAnimation("bigBatRightMove", "giantBat", 0, 6, 10, false, true);
	//왼쪽 움직임
	KEYANIMANAGER->addCoordinateFrameAnimation("bigBatLeftMove", "giantBat", 21, 27, 10, true, true);

	//오른쪽 공격
	KEYANIMANAGER->addCoordinateFrameAnimation("bigBatRightAttack", "giantBat", 7, 16, 10, true, false);
	//왼쪽 공격
	KEYANIMANAGER->addCoordinateFrameAnimation("bigBatLeftAttack", "giantBat", 28, 37, 10, true, false);

	//오른쪽 죽음
	int rightDie[] = { 38 };
	KEYANIMANAGER->addArrayFrameAnimation("bigBatRightDie", "giantBat", rightDie, 1, 6, false);
	//왼쪽 죽음
	int leftDie[] = { 39 };
	KEYANIMANAGER->addArrayFrameAnimation("bigBatLeftDie", "giantBat", leftDie, 1, 6, false);

	return S_OK;
}

void BigBat::release()
{
}

void BigBat::update()
{
	KEYANIMANAGER->update();
}

void BigBat::render()
{
	_img->aniRender(DC, _rc.left, _rc.top, _bigBatMotion);
}

void BigBat::move()
{

}

void BigBat::changeAnimation(BIGBATDIRECTION direction)
{
	switch (direction)
	{
	case RIGHT_MOVE:
		_img = IMAGEMANAGER->findImage("giantBat");
		_bigBatDirection = RIGHT_MOVE;
		_bigBatMotion = KEYANIMANAGER->findAnimation("bigBatRightMove");
		_bigBatMotion->start();
		break;
	case LEFT_MOVE:
		_img = IMAGEMANAGER->findImage("giantBat");
		_bigBatDirection = LEFT_MOVE;
		_bigBatMotion = KEYANIMANAGER->findAnimation("bigBatLeftMove");
		_bigBatMotion->start();
		break;
	case RIGHT_ATTACK:
		_img = IMAGEMANAGER->findImage("giantBat");
		_bigBatDirection = RIGHT_ATTACK;
		_bigBatMotion = KEYANIMANAGER->findAnimation("bigBatRightAttack");
		_bigBatMotion->start();
		break;
	case LEFT_ATTACK:
		_img = IMAGEMANAGER->findImage("giantBat");
		_bigBatDirection = LEFT_ATTACK;
		_bigBatMotion = KEYANIMANAGER->findAnimation("bigBat");
		break;
	case RIGHT_DIE:
		break;
	case LEFT_DIE:
		break;
	default:
		break;
	}
}