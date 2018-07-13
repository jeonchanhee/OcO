#include "stdafx.h"
#include "BigBat.h"


BigBat::BigBat()
{
}


BigBat::~BigBat()
{
}

HRESULT BigBat::init(float x, float y)
{
	static int b = 0;
	b += 1;
	_index = b;
	_x = x;
	_y = y;
	
	_bigBatDirection = BIGBAT_RIGHT_MOVE;

	_img = IMAGEMANAGER->findImage("giantBat");

	//Move
	int rightMove[] = { 0,1,2,3,5,6 };
	KEYANIMANAGER->addArrayFrameAnimation("bigBatRightMove", "giantBat", rightMove, 6, 5, true);
	int leftMove[] = { 21,22,24,25,26,27 };
	KEYANIMANAGER->addArrayFrameAnimation("bigBatLeftMove", "giantBat", leftMove, 6, 5, true);
	
	char str[50];
	sprintf_s(str, "bigBatRightAttack%d",b);
	//Attack
	int rightAtt[] = { 7,8,9,10,11,12,13,15,16 };
	KEYANIMANAGER->addArrayFrameAnimation(str, "giantBat", rightAtt, 9, 5, false, rightAttack, this);
	sprintf_s(str, "bigBatLeftAttack%d", b);
	int leftAtt[] = {28,29,30,31,32,33,34,35,36};
	KEYANIMANAGER->addArrayFrameAnimation(str, "giantBat", leftAtt, 9, 5, false,leftAttack,this);
	
	//Die
	int rightDie[] = { 17 };
	sprintf_s(str, "bigBatRightDie%d", b);
	KEYANIMANAGER->addArrayFrameAnimation(str, "giantBat", rightDie, 1, 5, false,bigbatDieMotion, this);
	int leftDie[] = { 38 };
	sprintf_s(str, "bigBatLeftDie%d", b);
	KEYANIMANAGER->addArrayFrameAnimation(str, "giantBat", leftDie, 1, 5, false, bigbatDieMotion, this);

	_bigBatMotion = KEYANIMANAGER->findAnimation("bigBatRightMove");
	_bigBatMotion->start();

	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

	//큰보박 체력바 초기화
	_progressBar = new progressBar;
	_progressBar->init(_x, _y + 50, 70, 10, "큰보박앞", "큰보박뒤", BAR_MONSTER);
	_currentHP = _maxHP = 100;

	return S_OK;
}

void BigBat::release()
{
}

void BigBat::update()
{
	//체력바 업데이트
	_progressBar->setX(_x);
	_progressBar->setY(_y + 50);
	_progressBar->setGauge(_currentHP, _maxHP);
	_progressBar->update();

	attackMove();

	if (!_diedie)
		hitDamage();

	if (_diedie)
	{
		_dieCount++;
		if (_dieCount > 90)
		{
			_isDie = true;
		}
	}

	////////////////////DIE 테스트///////////////////////
	if (KEYMANAGER->isOnceKeyDown(VK_F5))
	{
		_currentHP -= 5;
	}
	//if (KEYMANAGER->isOnceKeyUp(VK_F5))
	//{
	//	if (_bigBatDirection == BIGBAT_RIGHT_DIE)
	//		changeAnimation(BIGBAT_RIGHT_MOVE);
	//	if (_bigBatDirection == BIGBAT_LEFT_DIE)
	//		changeAnimation(BIGBAT_LEFT_MOVE);
	//}
	////////////////////▲▲▲▲▲▲▲▲▲//////////////////////////

	bulletfire();
	//KEYANIMANAGER->update();



	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
}

void BigBat::render()
{
	_progressBar->render();
	_img->aniRender(DC, _rc.left, _rc.top, _bigBatMotion);
	/*if (KEYMANAGER->isToggleKey(VK_LMENU))
	{
		Rectangle(DC, _rc.left, _rc.top, _rc.right, _rc.bottom);
	}*/
}

void BigBat::attackMove()
{
	_count++;
	if(!(_count % 170)) _isAttack = true;
	if (!(_count % 200))
	{
		if (_bigBatDirection == BIGBAT_RIGHT_MOVE)
			changeAnimation(BIGBAT_RIGHT_ATTACK);
		if (_bigBatDirection == BIGBAT_LEFT_MOVE)
			changeAnimation(BIGBAT_LEFT_ATTACK);
		_count = 0;
	}
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
		_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	case BIGBAT_LEFT_MOVE:
		_img = IMAGEMANAGER->findImage("giantBat");
		_bigBatDirection = BIGBAT_LEFT_MOVE;
		_bigBatMotion = KEYANIMANAGER->findAnimation("bigBatLeftMove");
		_bigBatMotion->start();
		_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	case BIGBAT_RIGHT_ATTACK:
		_img = IMAGEMANAGER->findImage("giantBat");
		_bigBatDirection = BIGBAT_RIGHT_ATTACK;
		char str[50];
		sprintf_s(str, "bigBatRightAttack%d", _index);
		_bigBatMotion = KEYANIMANAGER->findAnimation(str);
		_bigBatMotion->start();
		_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	case BIGBAT_LEFT_ATTACK:
		_img = IMAGEMANAGER->findImage("giantBat");
		_bigBatDirection = BIGBAT_LEFT_ATTACK;
		sprintf_s(str, "bigBatLeftAttack%d", _index);
		_bigBatMotion = KEYANIMANAGER->findAnimation(str);
		_bigBatMotion->start();
		_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	case BIGBAT_RIGHT_DIE:
		_img = IMAGEMANAGER->findImage("giantBat");

		_bigBatDirection = BIGBAT_RIGHT_DIE;
		_bigBatMotion->stop();
		sprintf_s(str, "bigBatRightDie%d", _index);
		_bigBatMotion = KEYANIMANAGER->findAnimation(str);
		_bigBatMotion->start();
		_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	case BIGBAT_LEFT_DIE:
		_img = IMAGEMANAGER->findImage("giantBat");
		_bigBatDirection = BIGBAT_LEFT_DIE;
		_bigBatMotion->stop();
		sprintf_s(str, "bigBatLeftDie%d", _index);
		_bigBatMotion = KEYANIMANAGER->findAnimation(str);
		_bigBatMotion->start();
		_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	default:
		_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	}
}

void BigBat::bulletfire()
{
	/*RECT rc = _rc;
	float angle = PI2 / 4;
	int count = 0;
	count++;
	if (count % 50 == 0)
	{
		_bullet->bulletFire("fatherBatBullet",rc.left + (rc.right - rc.left) / 2, rc.bottom + 10, angle, 5.0f, 100);
	}*/

}

void BigBat::rightAttack(void* obj)
{
	BigBat* bb = (BigBat*)obj;

	bb->setBigBatDirection(BIGBAT_RIGHT_MOVE);
	bb->setBigBatMotion(KEYANIMANAGER->findAnimation("bigBatRightMove"));
	bb->getBigBatMotion()->start();
}

void BigBat::leftAttack(void* obj)
{
	BigBat* bb = (BigBat*)obj;

	bb->setBigBatDirection(BIGBAT_LEFT_MOVE);
	bb->setBigBatMotion(KEYANIMANAGER->findAnimation("bigBatLeftMove"));
	bb->getBigBatMotion()->start();
}

void BigBat::playerCollision()
{
}

void BigBat::hitDamage()
{
	if (_currentHP <= 0)
	{
		die();
	}

}

void BigBat::die()
{
	//_bigBatMotion->stop();
	SOUNDMANAGER->play("bat3");
	if (_bigBatDirection == BIGBAT_RIGHT_ATTACK || _bigBatDirection == BIGBAT_RIGHT_MOVE)
		changeAnimation(BIGBAT_RIGHT_DIE);
	if (_bigBatDirection == BIGBAT_LEFT_ATTACK || _bigBatDirection == BIGBAT_LEFT_MOVE)
		changeAnimation(BIGBAT_LEFT_DIE);
}

void BigBat::bigbatDieMotion(void * obj)
{
	BigBat* c = (BigBat*)obj;
	c->_diedie = true;
}