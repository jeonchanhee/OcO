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
	
	_bigBatDirection = BIGBAT_LEFT_MOVE;

	_img = IMAGEMANAGER->findImage("giantBat");

	//������ ������
	KEYANIMANAGER->addCoordinateFrameAnimation("bigBatRightMove", "giantBat", 0, 6, 10, false, true);
	//���� ������
	KEYANIMANAGER->addCoordinateFrameAnimation("bigBatLeftMove", "giantBat", 21, 27, 10, true, true);

	//������ ����
	KEYANIMANAGER->addCoordinateFrameAnimation("bigBatRightAttack", "giantBat", 7, 16, 10, true, false);
	//���� ����
	KEYANIMANAGER->addCoordinateFrameAnimation("bigBatLeftAttack", "giantBat", 28, 37, 10, true, false);

	//������ ����
	int rightDie[] = { 17 };
	KEYANIMANAGER->addArrayFrameAnimation("bigBatRightDie", "giantBat", rightDie, 1, 6, false);
	//���� ����
	int leftDie[] = { 38 };
	KEYANIMANAGER->addArrayFrameAnimation("bigBatLeftDie", "giantBat", leftDie, 1, 6, false);

	return S_OK;
}

void BigBat::release()
{
}

void BigBat::update()
{
	move();
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
	case BIGBAT_RIGHT_MOVE:
		_img = IMAGEMANAGER->findImage("giantBat");
		_bigBatDirection = BIGBAT_RIGHT_MOVE;
		_bigBatMotion = KEYANIMANAGER->findAnimation("bigBatRightMove");
		_bigBatMotion->start();
		break;
	case BIGBAT_LEFT_MOVE:
		_img = IMAGEMANAGER->findImage("giantBat");
		_bigBatDirection = BIGBAT_LEFT_MOVE;
		_bigBatMotion = KEYANIMANAGER->findAnimation("bigBatLeftMove");
		_bigBatMotion->start();
		break;
	case BIGBAT_RIGHT_ATTACK:
		_img = IMAGEMANAGER->findImage("giantBat");
		_bigBatDirection = BIGBAT_RIGHT_ATTACK;
		_bigBatMotion = KEYANIMANAGER->findAnimation("bigBatRightAttack");
		_bigBatMotion->start();
		break;
	case BIGBAT_LEFT_ATTACK:
		_img = IMAGEMANAGER->findImage("giantBat");
		_bigBatDirection = BIGBAT_LEFT_ATTACK;
		_bigBatMotion = KEYANIMANAGER->findAnimation("bigBatLeftAttack");
		_bigBatMotion->start();
		break;
	case BIGBAT_RIGHT_DIE:
		_img = IMAGEMANAGER->findImage("giantBat");
		_bigBatDirection = BIGBAT_RIGHT_DIE;
		_bigBatMotion = KEYANIMANAGER->findAnimation("bigBatRightDie");
		_bigBatMotion->start();
		break;
	case BIGBAT_LEFT_DIE:
		_img = IMAGEMANAGER->findImage("giantBat");
		_bigBatDirection = BIGBAT_LEFT_DIE;
		_bigBatMotion = KEYANIMANAGER->findAnimation("bigBatLeftDie");
		_bigBatMotion->start();
		break;
	default:
		_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	}
}

void BigBat::rightAttack(void * obj)
{
	BigBat* bb = (BigBat*)obj;

	bb->setBigBatDirection(BIGBAT_RIGHT_MOVE);
	bb->setBigBatMotion(KEYANIMANAGER->findAnimation("bigBatRightMove"));
	bb->getBigBatMotion()->start();
}

void BigBat::leftAttack(void * obj)
{
}
