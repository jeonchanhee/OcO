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
	static int a = 0;
	a += 1;
	_index = a;

	_x = x;
	_y = y;

	_bigRedBatDirection = BIGREDBAT_RIGHT_MOVE;
	_img = IMAGEMANAGER->findImage("giantRedBatIdleDie");

	//Move
	KEYANIMANAGER->addCoordinateFrameAnimation("bigRedBatRightMove", "giantRedBatIdleDie", 0, 6, 5, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("bigRedBatLeftMove", "giantRedBatIdleDie", 7, 13, 5, false, true);
	//Attack
	char str[50];
	sprintf_s(str, "bigRedBatRightAttack%d", _index);
	KEYANIMANAGER->addCoordinateFrameAnimation(str, "giantRedBatAttack", 0, 9, 5, false, false, rightAttack, this);
	sprintf_s(str, "bigRedBatLeftAttack%d", _index);
	KEYANIMANAGER->addCoordinateFrameAnimation(str, "giantRedBatAttack", 10, 19, 5, false, false, leftAttack, this);

	
	//Die
	int rightDie[] = { 14 };
	sprintf_s(str, "bigRedBatRightDie%d", _index);
	KEYANIMANAGER->addArrayFrameAnimation(str, "giantRedBatIdleDie", rightDie, 1, 5, false, bigRedBatDieMotion, this);
	int leftDie[] = { 15 }; 
	sprintf_s(str, "bigRedBatLeftDie%d", _index);
	KEYANIMANAGER->addArrayFrameAnimation(str, "giantRedBatIdleDie", leftDie, 1, 5, false, bigRedBatDieMotion, this);

	_bigRedBatMotion = KEYANIMANAGER->findAnimation("bigRedBatRightMove");
	_bigRedBatMotion->start();

	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

	//큰빨박 체력바 초기화
	_progressBar = new progressBar;
	_progressBar->init(_x + 30, _y + 30, 70, 10, "큰빨박앞", "큰빨박뒤", BAR_MONSTER);
	_currentHP = _maxHP = 100;

	return S_OK;
}

void BigRedBat::release()
{
}

void BigRedBat::update()
{
	//체력바 업데이트
	_progressBar->setX(_x + 30);
	_progressBar->setY(_y + 30);
	_progressBar->setGauge(_currentHP, _maxHP);
	_progressBar->update();

	attackMove();
	if (!_diedie)
		hitDamage();

	if (_diedie)
	{
		_diecount++;
		if (_diecount > 60)
		{
			_isDie = true;
		}
	}



	/////////////////DIE 테스트////////////////////
	if (KEYMANAGER->isOnceKeyDown(VK_F6))
	{
		_currentHP -= 5;
	}
	/*if (KEYMANAGER->isOnceKeyUp(VK_F6))
	{
		if (_bigRedBatDirection == BIGREDBAT_RIGHT_DIE)
			changeAnimation(BIGREDBAT_RIGHT_MOVE);
		if (_bigRedBatDirection == BIGREDBAT_LEFT_DIE)
			changeAnimation(BIGREDBAT_LEFT_MOVE);
	}*/
	/////////////////▲▲▲▲▲▲▲▲▲////////////////////


	//KEYANIMANAGER->update();
	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
}

void BigRedBat::render()
{
	_progressBar->render();
	_img->aniRender(DC, _rc.left, _rc.top, _bigRedBatMotion);
	if (KEYMANAGER->isToggleKey('Z'))
	{
		Rectangle(DC, _rc.left, _rc.top, _rc.right, _rc.bottom);
	}
}

void BigRedBat::attackMove()
{
	if (!_diedie)
	{
		_count++;
		if (!(_count % 640)) _isAttack = true;
		if (!(_count % 700))
		{
			if (_bigRedBatDirection == BIGREDBAT_RIGHT_MOVE)
				changeAnimation(BIGREDBAT_RIGHT_ATTACK);
			if (_bigRedBatDirection == BIGREDBAT_LEFT_MOVE)
				changeAnimation(BIGREDBAT_LEFT_ATTACK);
			_count = 0;
		}
	}
}

void BigRedBat::rightAttack(void * obj)
{
	BigRedBat*  brb = (BigRedBat*)obj;
	if (brb->_diedie) return;
	brb->_img = IMAGEMANAGER->findImage("giantRedBatIdleDie");
	brb->setBigRedBatDirection(BIGREDBAT_RIGHT_MOVE);
	brb->setBigRedBatMotion(KEYANIMANAGER->findAnimation("bigRedBatRightMove"));
	brb->getBigRedBatMotion()->start();
}

void BigRedBat::leftAttack(void * obj)
{
	BigRedBat* brb = (BigRedBat*)obj;
	if (brb->_diedie) return;
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
		char str[50];
		sprintf_s(str, "bigRedBatRightAttack%d", _index);
		_bigRedBatMotion = KEYANIMANAGER->findAnimation(str);
		_bigRedBatMotion->start();
		_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	case BIGREDBAT_LEFT_ATTACK:
		_img = IMAGEMANAGER->findImage("giantRedBatAttack");
		_bigRedBatDirection = BIGREDBAT_LEFT_ATTACK;
		sprintf_s(str, "bigRedBatLeftAttack%d", _index);
		_bigRedBatMotion = KEYANIMANAGER->findAnimation(str);
		_bigRedBatMotion->start();
		_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	case BIGREDBAT_RIGHT_DIE:
		_img = IMAGEMANAGER->findImage("giantRedBatIdleDie");
		_bigRedBatDirection = BIGREDBAT_RIGHT_DIE;
		_bigRedBatMotion->stop();
		sprintf_s(str, "bigRedBatRightDie%d", _index);
		_bigRedBatMotion = KEYANIMANAGER->findAnimation(str);
		_bigRedBatMotion->start();
		_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	case BIGREDBAT_LEFT_DIE:
		_img = IMAGEMANAGER->findImage("giantRedBatIdleDie");
		_bigRedBatDirection = BIGREDBAT_LEFT_DIE;
		_bigRedBatMotion->stop();
		sprintf_s(str, "bigRedBatLeftDie%d", _index);
		_bigRedBatMotion = KEYANIMANAGER->findAnimation(str);
		_bigRedBatMotion->start();
		_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	default:
		_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	}
}

void BigRedBat::playerCollision()
{
}

void BigRedBat::hitDamage()
{
	if (_currentHP <= 0)
	{
		die();
	}
}

void BigRedBat::die()
{
	SOUNDMANAGER->play("bat3");
	if (_bigRedBatDirection == BIGREDBAT_RIGHT_ATTACK || _bigRedBatDirection == BIGREDBAT_RIGHT_MOVE)
		changeAnimation(BIGREDBAT_RIGHT_DIE);
	if (_bigRedBatDirection == BIGREDBAT_LEFT_ATTACK || _bigRedBatDirection == BIGREDBAT_RIGHT_MOVE)
		changeAnimation(BIGREDBAT_LEFT_DIE);
}

void BigRedBat::bigRedBatDieMotion(void * obj)
{
	BigRedBat* c = (BigRedBat*)obj;
	c->_diedie = true;
}