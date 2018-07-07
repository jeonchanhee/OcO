#include "stdafx.h"
#include "BigRedBat.h"

BigRedBat::BigRedBat()
{
}


BigRedBat::~BigRedBat()
{
}

HRESULT BigRedBat::init(float x, float y)
{
	_x = x;
	_y = y;

	_bigRedBatDirection = BIGREDBAT_RIGHT_MOVE;
	_img = IMAGEMANAGER->findImage("giantRedBatIdleDie");

	//Move
	KEYANIMANAGER->addCoordinateFrameAnimation("bigRedBatRightMove", "giantRedBatIdleDie", 0, 6, 5, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("bigRedBatLeftMove", "giantRedBatIdleDie", 7, 13, 5, false, true);
	//Attack
	KEYANIMANAGER->addCoordinateFrameAnimation("bigRedBatRightAttack", "giantRedBatAttack", 0, 9, 5, false, false, rightAttack, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("bigRedBatLeftAttack", "giantRedBatAttack", 10, 19, 5, false, false, leftAttack, this);

	
	//Die
	int rightDie[] = { 14 };
	KEYANIMANAGER->addArrayFrameAnimation("bigRedBatRightDie", "giantRedBatIdleDie", rightDie, 1, 5, false);
	int leftDie[] = { 15 };
	KEYANIMANAGER->addArrayFrameAnimation("bigRedBatLeftDie", "giantRedBatIdleDie", leftDie, 1, 5, false);

	_bigRedBatMotion = KEYANIMANAGER->findAnimation("bigRedBatRightMove");
	_bigRedBatMotion->start();

	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
	

	return S_OK;
}

void BigRedBat::release()
{
}

void BigRedBat::update()
{
	attackMove();

	/////////////////DIE ┼╫╜║╞о////////////////////
	if (KEYMANAGER->isOnceKeyDown(VK_F6))
	{
		if (_bigRedBatDirection == BIGREDBAT_RIGHT_MOVE)
			changeAnimation(BIGREDBAT_RIGHT_DIE);
		if (_bigRedBatDirection == BIGREDBAT_LEFT_MOVE)
			changeAnimation(BIGREDBAT_LEFT_DIE);
	}
	if (KEYMANAGER->isOnceKeyUp(VK_F6))
	{
		if (_bigRedBatDirection == BIGREDBAT_RIGHT_DIE)
			changeAnimation(BIGREDBAT_RIGHT_MOVE);
		if (_bigRedBatDirection == BIGREDBAT_LEFT_DIE)
			changeAnimation(BIGREDBAT_LEFT_MOVE);
	}
	/////////////////бубубубубубубубубу////////////////////


	//KEYANIMANAGER->update();
	_rc = RectMakeCenter(_x, _y, _img->getFrameHeight(), _img->getFrameHeight());
}

void BigRedBat::render()
{
	_img->aniRender(DC, _rc.left, _rc.top, _bigRedBatMotion);
}

void BigRedBat::attackMove()
{
	_count++;
	if (!(_count % 150))
	{
		if (_bigRedBatDirection == BIGREDBAT_RIGHT_MOVE)
			changeAnimation(BIGREDBAT_RIGHT_ATTACK);
		if (_bigRedBatDirection == BIGREDBAT_LEFT_MOVE)
			changeAnimation(BIGREDBAT_LEFT_ATTACK);
	
		_count = 0;
	}
}

void BigRedBat::rightAttack(void * obj)
{
	BigRedBat*  brb = (BigRedBat*)obj;

	brb->_img = IMAGEMANAGER->findImage("giantRedBatIdleDie");
	brb->setBigRedBatDirection(BIGREDBAT_RIGHT_MOVE);
	brb->setBigRedBatMotion(KEYANIMANAGER->findAnimation("bigRedBatRightMove"));
	brb->getBigRedBatMotion()->start();
}

void BigRedBat::leftAttack(void * obj)
{
	BigRedBat* brb = (BigRedBat*)obj;

	brb->_img = IMAGEMANAGER->findImage("giantRedBatIdleDie");
	brb->setBigRedBatDirection(BIGREDBAT_LEFT_MOVE);
	brb->setBigRedBatMotion(KEYANIMANAGER->findAnimation("bigRedBatLeftMove"));
	brb->getBigRedBatMotion()->start();
}

void BigRedBat::changeAnimation(BIGREDBATDIRECTION bigRedBatDirection)
{
	switch (bigRedBatDirection)
	{
	case BIGREDBAT_RIGHT_MOVE:
		_img = IMAGEMANAGER->findImage("giantRedBatIdleDie");
		_bigRedBatDirection = BIGREDBAT_RIGHT_MOVE;
		_bigRedBatMotion = KEYANIMANAGER->findAnimation("bigRedBatRightMove");
		_bigRedBatMotion->start();
		_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	case BIGREDBAT_LEFT_MOVE:
		_img = IMAGEMANAGER->findImage("giantRedBatIdleDie");
		_bigRedBatDirection = BIGREDBAT_LEFT_MOVE;
		_bigRedBatMotion = KEYANIMANAGER->findAnimation("bigRedBatLeftMove");
		_bigRedBatMotion->start();
		_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	case BIGREDBAT_RIGHT_ATTACK:
		_img = IMAGEMANAGER->findImage("giantRedBatAttack");
		_bigRedBatDirection = BIGREDBAT_RIGHT_ATTACK;
		_bigRedBatMotion = KEYANIMANAGER->findAnimation("bigRedBatRightAttack");
		_bigRedBatMotion->start();
		_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	case BIGREDBAT_LEFT_ATTACK:
		_img = IMAGEMANAGER->findImage("giantRedBatAttack");
		_bigRedBatDirection = BIGREDBAT_LEFT_ATTACK;
		_bigRedBatMotion = KEYANIMANAGER->findAnimation("bigRedBatLeftAttack");
		_bigRedBatMotion->start();
		_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	case BIGREDBAT_RIGHT_DIE:
		_img = IMAGEMANAGER->findImage("giantRedBatIdleDie");
		_bigRedBatDirection = BIGREDBAT_RIGHT_DIE;
		_bigRedBatMotion = KEYANIMANAGER->findAnimation("bigRedBatRightDie");
		_bigRedBatMotion->start();
		_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	case BIGREDBAT_LEFT_DIE:
		_img = IMAGEMANAGER->findImage("giantRedBatIdleDie");
		_bigRedBatDirection = BIGREDBAT_LEFT_DIE;
		_bigRedBatMotion = KEYANIMANAGER->findAnimation("bigRedBatLeftDie");
		_bigRedBatMotion->start();
		_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	default:
		_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	}
}