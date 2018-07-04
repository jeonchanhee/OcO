#include "stdafx.h"
#include "Boss2.h"


Boss2::Boss2()
{
}


Boss2::~Boss2()
{
}

HRESULT Boss2::init()
{
	_boss[0].img = IMAGEMANAGER->findImage("bossHand");
	_boss[1].img = IMAGEMANAGER->findImage("bossIdleAttackDie");
	_boss[2].img = IMAGEMANAGER->findImage("bossHand");

	for (int i = 0; i < 3; i++) 
	{
		_boss[i].x = WINSIZEX / 4 + (i * WINSIZEX / 4);
		_boss[i].y = WINSIZEY / 2;
		_boss[i].rc = RectMakeCenter(_boss[i].x, _boss[i].y, _boss[i].img->getFrameWidth(), _boss[i].img->getFrameHeight());
	}
	

	_bossLeftDirection = LEFT_IDLE;
	_bossHeadDirection = HEAD_IDLE;

	//=======LEFT (IDLE,MOVE,LASER)========
	KEYANIMANAGER->addCoordinateFrameAnimation("leftIdle", "bossHand", 18, 27, 5, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("leftMove", "bossHand", 18, 27, 5, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("leftLaser", "bossHand", 54, 71, 5, false, false);

	_bossMotion[0] = KEYANIMANAGER->findAnimation("leftIdle");
	_bossMotion[0]->start();

	//=======HEAD (IDLE,ATTACK,DIE)========
	KEYANIMANAGER->addCoordinateFrameAnimation("headIdle", "bossIdleAttackDie", 0, 9, 5, false, true);
	int headAttack[] = { 14,15,16,17,18,19,20 };
	KEYANIMANAGER->addArrayFrameAnimation("headAttack", "bossIdleAttackDie", headAttack, 7, 10, false);
	//KEYANIMANAGER->addCoordinateFrameAnimation("headAttack", "bossIdleAttackDie", 11, 20, 1, false, false, headAttack, this);
	int headDie[] = { 21 };
	KEYANIMANAGER->addArrayFrameAnimation("headDie", "bossIdleAttackDie", headDie, 1, 10, false);

	_bossMotion[1] = KEYANIMANAGER->findAnimation("headIdle");
	_bossMotion[1]->start();


	//=======RIGHT (IDLE,MOVE,LASER)========

	return S_OK;
}

void Boss2::release()
{
}

void Boss2::update()
{
	///////////////HEAD DIE TEST/////////////////
	/*if (KEYMANAGER->isOnceKeyDown(VK_F9))
	{
		if (_bossHeadDirection == HEAD_IDLE || _bossHeadDirection == HEAD_ATTACK)
		{
			changeHeadDirection(HEAD_DIE);
		}	
	}
	if (_bossHeadDirection == HEAD_DIE)
	{
		if (_y < 1000) _y += BOSSSPEED;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_F9))
	{
		if (_bossHeadDirection == HEAD_DIE)
		{
			changeHeadDirection(HEAD_IDLE);
		}
	}*/
	/////////////////////////////////////////////////
	_count++;
	leftMove();
	headMove();

	KEYANIMANAGER->update();
	for (int i = 0; i < 3; i++)
		_boss[i].rc = RectMakeCenter(_boss[i].x, _boss[i].y, _boss[i].img->getFrameWidth(), _boss[i].img->getFrameHeight());
}

void Boss2::render()
{
	for (int i = 0; i < 2; i++)
	{
		//_boss[i].img->aniRender(DC, _boss[i].rc.left, _boss[i].rc.top, _bossMotion[i]);
		_boss[i].img->aniRender(DC, _boss[i].rc.left, _boss[i].rc.top, _bossMotion[i]);
	}
}


//¿Þ¼Õ²Ù¶ô
void Boss2::leftMove()
{
	if (!(_count % 150))
	{
		changeLeftDirection(LEFT_MOVE);
	}
	if (!(_count % 200))
	{
		changeLeftDirection(LEFT_IDLE);
	}

	if (_bossLeftDirection == LEFT_MOVE)
	{
		/*if (_boss[0].y > 30)
			_boss[0].y -= BOSSSPEED;
		if (_boss[0].y <= WINSIZEY - 300)
			_boss[0].y += BOSSSPEED;*/
		if (_boss[0].y > WINSIZEX / 2)
			_boss[0].y -= BOSSSPEED;
		if (_boss[0].y < WINSIZEX / 2)
			_boss[0].y += BOSSSPEED;
		
	}
		/*if (_bossLeftDirection == LEFT_IDLE && _boss[0].y < WINSIZEY - 100)
		{
			changeLeftDirection(LEFT_MOVE);
			_boss[0].y += BOSSSPEED;
		}
		if (_bossLeftDirection == LEFT_IDLE && _boss[0].y > 100)
		{
			changeLeftDirection(LEFT_MOVE);
			_boss[0].y -= BOSSSPEED;
		}
	}

	if (!(_count % 200))
	{
		if (_bossLeftDirection == LEFT_MOVE)
			changeLeftDirection(LEFT_IDLE);
	}*/
}

void Boss2::changeLeftDirection(BOSSLEFTDIRECTION leftDirection)
{
	switch (leftDirection)
	{
	case LEFT_IDLE:
		_boss[0].img = IMAGEMANAGER->findImage("bossHand");
		_bossLeftDirection = LEFT_IDLE;
		_bossMotion[0] = KEYANIMANAGER->findAnimation("leftIdle");
		_bossMotion[0]->start();
		_boss[0].rc = RectMakeCenter(_boss[0].x, _boss[0].y, _boss[0].img->getFrameWidth(), _boss[0].img->getFrameHeight());
		break;
	case LEFT_MOVE:
		_boss[0].img = IMAGEMANAGER->findImage("bossHand");
		_bossLeftDirection = LEFT_MOVE;
		_bossMotion[0] = KEYANIMANAGER->findAnimation("leftMove");
		_bossMotion[0]->start();
		_boss[0].rc = RectMakeCenter(_boss[0].x, _boss[0].y, _boss[0].img->getFrameWidth(), _boss[0].img->getFrameHeight());
		break;
	case LEFT_LASER:
		_boss[0].img = IMAGEMANAGER->findImage("bossHand");
		_bossLeftDirection = LEFT_LASER;
		_bossMotion[0] = KEYANIMANAGER->findAnimation("leftLaser");
		_bossMotion[0]->start();
		_boss[0].rc = RectMakeCenter(_boss[0].x, _boss[0].y, _boss[0].img->getFrameWidth(), _boss[0].img->getFrameHeight());
		break;
	default:
		_boss[0].rc = RectMakeCenter(_boss[0].x, _boss[0].y, _boss[0].img->getFrameWidth(), _boss[0].img->getFrameHeight());
		break;
	}
}

void Boss2::CBleftAttack(void * obj)
{
	Boss2* bb = (Boss2*)obj;

	bb->_boss[0].img = IMAGEMANAGER->findImage("bossHand");
	bb->setLeftDirection(LEFT_IDLE);
	bb->setLeftMotion0(KEYANIMANAGER->findAnimation("leftIdle"));
	bb->getLeftMotion0()->start();
}


//¸Ó¸®ÅÖ
void Boss2::headMove()
{
	if (!(_count % 100))
	{
		if(_bossHeadDirection == HEAD_IDLE)
			changeHeadDirection(HEAD_ATTACK);
		
	}
	if (!(_count % 500))
	{
		if(_bossHeadDirection == HEAD_ATTACK)
			changeHeadDirection(HEAD_IDLE);
		_count = 0;
	}
}

void Boss2::changeHeadDirection(BOSSHEADDIRECTION headDirection)
{
	switch (headDirection)
	{
	case HEAD_IDLE:
		_boss[1].img = IMAGEMANAGER->findImage("bossIdleAttackDie");
		_bossHeadDirection = HEAD_IDLE;
		_bossMotion[1] = KEYANIMANAGER->findAnimation("headIdle");
		_bossMotion[1]->start();
		_boss[1].rc = RectMakeCenter(_boss[1].x, _boss[1].y, _boss[1].img->getFrameWidth(), _boss[1].img->getFrameHeight());
		break;
	case HEAD_ATTACK:
		_boss[1].img = IMAGEMANAGER->findImage("bossIdleAttackDie");
		_bossHeadDirection = HEAD_ATTACK;
		_bossMotion[1] = KEYANIMANAGER->findAnimation("headAttack");
		_bossMotion[1]->start();
		_boss[1].rc = RectMakeCenter(_boss[1].x, _boss[1].y, _boss[1].img->getFrameWidth(), _boss[1].img->getFrameHeight());
		break;
	case HEAD_DIE:
		_boss[1].img = IMAGEMANAGER->findImage("bossIdleAttackDie");
		_bossHeadDirection = HEAD_DIE;
		_bossMotion[1] = KEYANIMANAGER->findAnimation("headDie");
		_bossMotion[1]->start();
		_boss[1].rc = RectMakeCenter(_boss[1].x, _boss[1].y, _boss[1].img->getFrameWidth(), _boss[1].img->getFrameHeight());
		break;
	default:
		_boss[1].rc = RectMakeCenter(_boss[1].x, _boss[1].y, _boss[1].img->getFrameWidth(), _boss[1].img->getFrameHeight());
		break;
	}
}

void Boss2::CBheadAttack(void * obj)
{
	Boss2* bb = (Boss2*)obj;

	bb->_boss[1].img = IMAGEMANAGER->findImage("bossIdleAttackDie");
	bb->setHeadDirection(HEAD_IDLE);
	bb->setHeadMotion1(KEYANIMANAGER->findAnimation("headIdle"));
	bb->getHeadMotion1()->start();
}
