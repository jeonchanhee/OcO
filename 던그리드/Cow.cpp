#include "stdafx.h"
#include "Cow.h"


Cow::Cow()
{
}


Cow::~Cow()
{
}

HRESULT Cow::init()
{
	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2;

	_img = IMAGEMANAGER->findImage("cowIdleChargeAttack");
	//_cowDirection = COW_LEFT_MOVE;
	_cowDirection = COW_RIGHT_MOVE;

	//MOVE
	KEYANIMANAGER->addCoordinateFrameAnimation("cowRightMove", "cowIdleChargeAttack", 0, 5, 5, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("cowLeftMove", "cowIdleChargeAttack", 8, 13, 5, false, true);

	//CHARGE
	KEYANIMANAGER->addCoordinateFrameAnimation("cowRightCharge", "cowIdleChargeAttack", 16, 23, 5, false, false, rightCharge, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("cowLeftCharge", "cowIdleChargeAttack", 24, 31, 5, false, false, leftCharge, this);

	//ATTACK
	KEYANIMANAGER->addCoordinateFrameAnimation("cowRightAttack", "cowIdleChargeAttack", 32, 38, 5, false, false, rightAttack, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("cowLeftAttack", "cowIdleChargeAttack", 40, 46, 5, false, false, leftAttack, this);

	//DIE
	KEYANIMANAGER->addCoordinateFrameAnimation("cowDie", "dieEffect", 2, 10, 5, false, false);

	//_cowMotion = KEYANIMANAGER->findAnimation("cowLeftMove");
	_cowMotion = KEYANIMANAGER->findAnimation("cowRightMove");
	_cowMotion->start();

	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

	return S_OK;
}

void Cow::release()
{
}

void Cow::update()
{
	move();
	changeDirection();

	///////////////////////DIE ┼╫╜║╞о///////////////////////////
	if (KEYMANAGER->isOnceKeyDown(VK_F8))
	{
		if (_cowDirection == COW_RIGHT_MOVE || _cowDirection == COW_LEFT_MOVE)
			changeAnimation(COW_DIE);
	}
	/*if (KEYMANAGER->isOnceKeyUp(VK_F8))
	{
		if (_cowDirection == COW_DIE)
			changeAnimation(COW_RIGHT_MOVE);
	}*/
	///////////////////////бубубубубубубубубу///////////////////////////


	KEYANIMANAGER->update();
	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
}

void Cow::render()
{
	_img->aniRender(DC, _rc.left, _rc.top, _cowMotion);
}

void Cow::move()
{
	
	_count++;
	if (!(_count % 250))
	{
		if (_cowDirection == COW_RIGHT_MOVE)
			changeAnimation(COW_RIGHT_CHARGE);
		if (_cowDirection == COW_LEFT_MOVE)
			changeAnimation(COW_LEFT_CHARGE);
	}
	if (!(_count % 300))
	{
		if (_cowDirection == COW_RIGHT_MOVE)
			changeAnimation(COW_RIGHT_ATTACK);
		if (_cowDirection == COW_LEFT_MOVE)
			changeAnimation(COW_LEFT_ATTACK);
	}


}

void Cow::changeDirection()
{
	if (_cowDirection == COW_RIGHT_CHARGE)
		_x += COWSPEED;
	if (_cowDirection == COW_LEFT_CHARGE)
		_x -= COWSPEED;
	if (_x <= _img->getFrameWidth())
	{
		_x = _img->getFrameWidth() + 5;
		changeAnimation(COW_RIGHT_MOVE);
		//_x += COWSPEED;
	}
	if (_x >= WINSIZEX - _img->getFrameWidth())
	{
		_x = WINSIZEX - _img->getFrameWidth() - 5;
		changeAnimation(COW_LEFT_MOVE);
	}
}

void Cow::rightCharge(void * obj)
{
	Cow* c = (Cow*)obj;

	c->_img = IMAGEMANAGER->findImage("cowIdleChargeAttack");
	c->setCowDirection(COW_RIGHT_MOVE);
	c->setCowMotion(KEYANIMANAGER->findAnimation("cowRightMove"));
	c->getCowMotion()->start();
}

void Cow::leftCharge(void * obj)
{
	Cow* c = (Cow*)obj;

	c->_img = IMAGEMANAGER->findImage("cowIdleChargeAttack");
	c->setCowDirection(COW_LEFT_MOVE);
	c->setCowMotion(KEYANIMANAGER->findAnimation("cowLeftMove"));
	c->getCowMotion()->start();
}

void Cow::rightAttack(void * obj)
{
	Cow* c = (Cow*)obj;

	c->_img = IMAGEMANAGER->findImage("cowIdleChargeAttack");
	c->setCowDirection(COW_RIGHT_MOVE);
	c->setCowMotion(KEYANIMANAGER->findAnimation("cowRightMove"));
	c->getCowMotion()->start();
}

void Cow::leftAttack(void * obj)
{
	Cow* c = (Cow*)obj;

	c->_img = IMAGEMANAGER->findImage("cowIdleChargeAttack");
	c->setCowDirection(COW_LEFT_MOVE);
	c->setCowMotion(KEYANIMANAGER->findAnimation("cowLeftMove"));
	c->getCowMotion()->start();

}

void Cow::changeAnimation(COWDIRECTION cowDirection)
{
	switch (cowDirection)
	{
	case COW_RIGHT_MOVE:
		_img = IMAGEMANAGER->findImage("cowIdleChargeAttack");
		_cowDirection = COW_RIGHT_MOVE;
		_cowMotion->stop();
		_cowMotion = KEYANIMANAGER->findAnimation("cowRightMove");
		_cowMotion->start();
		_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	case COW_LEFT_MOVE:
		_img = IMAGEMANAGER->findImage("cowIdleChargeAttack");
		_cowDirection = COW_LEFT_MOVE;
		_cowMotion->stop();
		_cowMotion = KEYANIMANAGER->findAnimation("cowLeftMove");
		_cowMotion->start();
		_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	case COW_RIGHT_CHARGE:
		_img = IMAGEMANAGER->findImage("cowIdleChargeAttack");
		_cowDirection = COW_RIGHT_CHARGE;
		_cowMotion->stop();
		_cowMotion = KEYANIMANAGER->findAnimation("cowRightCharge");
		_cowMotion->start();
		_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	case COW_LEFT_CHARGE:
		_img = IMAGEMANAGER->findImage("cowIdleChargeAttack");
		_cowDirection = COW_LEFT_CHARGE;
		_cowMotion->stop();
		_cowMotion = KEYANIMANAGER->findAnimation("cowLeftCharge");
		_cowMotion->start();
		_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	case COW_RIGHT_ATTACK:
		_img = IMAGEMANAGER->findImage("cowIdleChargeAttack");
		_cowDirection = COW_RIGHT_ATTACK;
		_cowMotion->stop();
		_cowMotion = KEYANIMANAGER->findAnimation("cowRightAttack");
		_cowMotion->start();
		_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	case COW_LEFT_ATTACK:
		_img = IMAGEMANAGER->findImage("cowIdleChargeAttack");
		_cowDirection = COW_LEFT_ATTACK;
		_cowMotion->stop();
		_cowMotion = KEYANIMANAGER->findAnimation("cowLeftAttack");
		_cowMotion->start();
		_rc = RectMakeCenter(_x,_y,_img->getFrameWidth(),_img->getFrameHeight());
		break;
	case COW_DIE:
		_img = IMAGEMANAGER->findImage("dieEffect");
		_cowDirection = COW_DIE;
		_cowMotion->stop();
		_cowMotion = KEYANIMANAGER->findAnimation("cowDie");
		_cowMotion->start();
		_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	default:
		break;
	}
}
