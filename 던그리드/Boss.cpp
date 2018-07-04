#include "stdafx.h"
#include "Boss.h"


Boss::Boss()
{
}


Boss::~Boss()
{
}

HRESULT Boss::init()
{
	_bossComponent[1].img = IMAGEMANAGER->findImage("bossIdleAttackDie");
	_bossComponent[0].img = IMAGEMANAGER->findImage("bossHand");
	_bossComponent[2].img = IMAGEMANAGER->findImage("bossHand");

	for (int i = 0; i < 3; i++)
	{
		_bossComponent[i].x = WINSIZEX / 4 + (i * (WINSIZEX / 4));
		_bossComponent[i].y = WINSIZEY / 2;
		_bossComponent[i].rc = RectMakeCenter(_bossComponent[i].x, _bossComponent[i].y, _bossComponent[i].img->getFrameWidth(), _bossComponent[i].img->getFrameHeight());
	}

	//BOSS_HEAD
	KEYANIMANAGER->addCoordinateFrameAnimation("bossHeadIdle", "bossIdleAttackDie", 0, 9, 5, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("bossHeadAttack", "bossIdleAttackDie", 11, 20, 5, false, false, headAttack, this);
	int bossHeadDie[] = { 21 };
	KEYANIMANAGER->addArrayFrameAnimation("bossHeadDie", "bossIdleAttackDie", bossHeadDie, 1, 10, false);

	//BOSS_LEFT_HAND
	//KEYANIMANAGER->addCoordinateFrameAnimation("bossLHandIdle", "bossHand", 0, 9, 5, false, true);
	//KEYANIMANAGER->addCoordinateFrameAnimation("bossLHandAttack", "bossHand", 36, 53, 5, false, false, handLeftLaser, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("bossLHandIdle", "bossHand", 18,27, 5, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("bossLHandAttack", "bossHand", 54,71, 5, false, false, handLeftLaser, this);

	//BOSS_RIGHT_HAND
	//KEYANIMANAGER->addCoordinateFrameAnimation("bossRHandIdle", "bossHand", 18, 27, 5, false, true);
	//KEYANIMANAGER->addCoordinateFrameAnimation("bossRHandAttack", "bossHand", 54, 71, 5, false, false, handRightLaser, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("bossRHandIdle", "bossHand", 0,9, 5, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("bossRHandAttack", "bossHand", 36,53, 5, false, false, handRightLaser, this);

	_bossHeadDirection = BOSS_HEAD_IDLE;
	_bossLHandDirection = BOSS_LEFT_IDLE;
	_bossRHandDirection = BOSS_RIGHT_IDLE;

	_bossMotion[0] = KEYANIMANAGER->findAnimation("bossLHandIdle");
	_bossMotion[1] = KEYANIMANAGER->findAnimation("bossHeadIdle");
	_bossMotion[2] = KEYANIMANAGER->findAnimation("bossRHandIdle");

	for (int i = 0; i < 3; i++)
	{
		_bossMotion[i]->start();
	}

	return S_OK;
}

void Boss::release()
{
}

void Boss::update()
{
	_count++;
	leftHandMove();
	headMove();
	rightHandMove();

	KEYANIMANAGER->update();
	for (int i = 0; i < 3; i++)
	{
		_bossComponent[i].rc = RectMakeCenter(_bossComponent[i].x, _bossComponent[i].y, _bossComponent[i].img->getFrameWidth(), _bossComponent[i].img->getFrameHeight());
	}
}

void Boss::render()
{
	for (int i = 0; i < 3; i++)
	{
		_bossComponent[i].img->aniRender(DC, _bossComponent[i].rc.left, _bossComponent[i].rc.top, _bossMotion[i]);
	}
}

void Boss::leftHandMove()
{

	if (_bossLHandDirection == BOSS_LEFT_MOVE)
	{
		if(_bossComponent[0].y < WINSIZEY - 100)
			_bossComponent[0].y += HANDSPEED;
		else
			_bossComponent[0].y -= HANDSPEED;
	}
	/*if (_bossComponent[0].y < 900 && _bossLHandDirection == BOSS_LEFT_MOVE)
	{
		_bossComponent[0].y += HANDSPEED;
	}

	if (_bossComponent[0].y < 100 && _bossLHandDirection == BOSS_LEFT_MOVE)
	{
		_bossComponent[0].y += HANDSPEED;
	}*/

	//if (!(_count % 110) && _bossLHandDirection == BOSS_LEFT_MOVE)
	//{
	//	changeLHandAnimation(BOSS_LEFT_IDLE);
	//}
}

void Boss::headMove()
{
	if (!(_count % 200))
	{
		changeHeadAnimation(BOSS_HEAD_ATTACK);
		if(_bossLHandDirection == BOSS_LEFT_IDLE) 
			changeLHandAnimation(BOSS_LEFT_MOVE);
		else if (_bossLHandDirection == BOSS_LEFT_MOVE) changeLHandAnimation(BOSS_LEFT_IDLE);
	}
}

void Boss::rightHandMove()
{
	if (_bossComponent[2].y > WINSIZEY - 100 && _bossRHandDirection == BOSS_RIGHT_MOVE)
	{
		_bossComponent[2].y += HANDSPEED;
	}
	
	if (_bossComponent[2].y < 100 && _bossRHandDirection == BOSS_RIGHT_MOVE)
	{
		_bossComponent[2].y -= HANDSPEED;
	}

	/*if (!(_count % 170) && _bossRHandDirection == BOSS_RIGHT_MOVE)
	{
		changeRHandAnimation(BOSS_RIGHT_IDLE);
	}*/
}

void Boss::changeHeadAnimation(BOSSHEADDIRECTION head)
{
	switch (head)
	{
	case BOSS_HEAD_IDLE:
		_bossComponent[1].img = IMAGEMANAGER->findImage("bossIdleAttackDie");
		_bossHeadDirection = BOSS_HEAD_IDLE;
		_bossMotion[1] = KEYANIMANAGER->findAnimation("bossHeadIdle");
		_bossMotion[1]->start();
		_bossComponent[1].rc = RectMakeCenter(_bossComponent[1].x, _bossComponent[1].y, _bossComponent[1].img->getFrameWidth(), _bossComponent[1].img->getFrameHeight());
		break;
	case BOSS_HEAD_ATTACK:
		_bossComponent[1].img = IMAGEMANAGER->findImage("bossIdleAttackDie");
		_bossHeadDirection = BOSS_HEAD_ATTACK;
		_bossMotion[1] = KEYANIMANAGER->findAnimation("bossHeadAttack");
		_bossMotion[1]->start();
		_bossComponent[1].rc = RectMakeCenter(_bossComponent[1].x, _bossComponent[1].y, _bossComponent[1].img->getFrameWidth(), _bossComponent[1].img->getFrameHeight());
		break;
	case BOSS_HEAD_DIE:
		_bossComponent[1].img = IMAGEMANAGER->findImage("bossIdleAttackDie");
		_bossHeadDirection = BOSS_HEAD_DIE;
		_bossMotion[1] = KEYANIMANAGER->findAnimation("bossHeadDie");
		_bossMotion[1]->start();
		_bossComponent[1].rc = RectMakeCenter(_bossComponent[1].x, _bossComponent[1].y, _bossComponent[1].img->getFrameWidth(), _bossComponent[1].img->getFrameHeight());
		break;
	}
}

void Boss::changeLHandAnimation(BOSSLHANDDIRECTION LHand)
{
	switch (LHand)
	{
	case BOSS_LEFT_IDLE:
		_bossComponent[0].img = IMAGEMANAGER->findImage("bossHand");
		_bossLHandDirection = BOSS_LEFT_IDLE;
		_bossMotion[0] = KEYANIMANAGER->findAnimation("bossLHandIdle");
		_bossMotion[0]->start();
		_bossComponent[0].rc = RectMakeCenter(_bossComponent[0].x, _bossComponent[0].y, _bossComponent[0].img->getFrameWidth(), _bossComponent[0].img->getFrameHeight());
		break;
	case BOSS_LEFT_MOVE:
		_bossComponent[0].img = IMAGEMANAGER->findImage("bossHand");
		_bossLHandDirection = BOSS_LEFT_MOVE;
		_bossMotion[0] = KEYANIMANAGER->findAnimation("bossLHandIdle");
		_bossMotion[0]->start();
		_bossComponent[0].rc = RectMakeCenter(_bossComponent[0].x, _bossComponent[0].y, _bossComponent[0].img->getFrameWidth(), _bossComponent[0].img->getFrameHeight());
		break;
	case BOSS_LEFT_LASER:
		_bossComponent[0].img = IMAGEMANAGER->findImage("bossHand");
		_bossLHandDirection = BOSS_LEFT_LASER;
		_bossMotion[0] = KEYANIMANAGER->findAnimation("bossLHandAttack");
		_bossMotion[0]->start();
		_bossComponent[0].rc = RectMakeCenter(_bossComponent[0].x, _bossComponent[0].y, _bossComponent[0].img->getFrameWidth(), _bossComponent[0].img->getFrameHeight());
		break;
	}
}

void Boss::changeRHandAnimation(BOSSRHANDDIRECTION RHand)
{
	switch (RHand)
	{
	case BOSS_RIGHT_IDLE:
		_bossComponent[2].img = IMAGEMANAGER->findImage("bossHand");
		_bossRHandDirection = BOSS_RIGHT_IDLE;
		_bossMotion[2] = KEYANIMANAGER->findAnimation("bossRHandIdle");
		_bossMotion[2]->start();
		_bossComponent[2].rc = RectMakeCenter(_bossComponent[2].x, _bossComponent[2].y, _bossComponent[2].img->getFrameWidth(), _bossComponent[2].img->getFrameHeight());
		break;
	case BOSS_RIGHT_MOVE:
		_bossComponent[2].img = IMAGEMANAGER->findImage("bossHand");
		_bossRHandDirection = BOSS_RIGHT_MOVE;
		_bossMotion[2] = KEYANIMANAGER->findAnimation("bossRHandIdle");
		_bossMotion[2]->start();
		_bossComponent[2].rc = RectMakeCenter(_bossComponent[2].x, _bossComponent[2].y, _bossComponent[2].img->getFrameWidth(), _bossComponent[2].img->getFrameHeight());
		break;
	case BOSS_RIGHT_LASER:
		_bossComponent[2].img = IMAGEMANAGER->findImage("bossHand");
		_bossRHandDirection = BOSS_RIGHT_LASER;
		_bossMotion[2] = KEYANIMANAGER->findAnimation("bossRHandAttack");
		_bossMotion[2]->start();
		_bossComponent[2].rc = RectMakeCenter(_bossComponent[2].x, _bossComponent[2].y, _bossComponent[2].img->getFrameWidth(), _bossComponent[2].img->getFrameHeight());
		break;
	}
}

void Boss::headAttack(void * obj)
{
	Boss* bb = (Boss*)obj;
	
	bb->_img = IMAGEMANAGER->findImage("bossIdleAttackDie");
	bb->setBossHeadDirection(BOSS_HEAD_IDLE);
	bb->setBossMotion2(KEYANIMANAGER->findAnimation("bossHeadIdle"));
	bb->getBossMotion2()->start();
}

void Boss::handRightLaser(void * obj)
{
	Boss* bb = (Boss*)obj;
	
	bb->_img = IMAGEMANAGER->findImage("bossHand");
	bb->setBossRHandDirection(BOSS_RIGHT_IDLE);
	bb->setBossMotion3(KEYANIMANAGER->findAnimation("bossRHandIdle"));
	bb->getBossMotion3()->start();
}

void Boss::handLeftLaser(void * obj)
{
	Boss* bb = (Boss*)obj;

	bb->_img = IMAGEMANAGER->findImage("bossHand");
	bb->setBossLHandDirection(BOSS_LEFT_IDLE);
	bb->setBossMotion1(KEYANIMANAGER->findAnimation("bossLHandIdle"));
	bb->getBossMotion1()->start();
}

