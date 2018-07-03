#include "stdafx.h"
#include "BigBone.h"


BigBone::BigBone()
{
}


BigBone::~BigBone()
{
}

HRESULT BigBone::init()
{
	_bigBoneDirection = BIGBONE_LEFT_MOVE;
	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2;
	_count = 0;
	//_isAttack = false;
	
	_img = IMAGEMANAGER->findImage("bigWhiteSkelIdleMove");
	
	//IDLE상태
	KEYANIMANAGER->addCoordinateFrameAnimation("bigBoneRightIdle", "bigWhiteSkelIdleMove", 0, 5, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("bigBoneLeftIdle", "bigWhiteSkelIdleMove", 6, 11, 10, false, true);
	//MOVE상태
	KEYANIMANAGER->addCoordinateFrameAnimation("bigBoneRightMove", "bigWhiteSkelIdleMove", 12, 17, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("bigBoneLeftMove", "bigWhiteSkelIdleMove", 18, 23, 10, false, true);

	//ATTACK상태
	KEYANIMANAGER->addCoordinateFrameAnimation("bigBoneRightAttack", "bigWhiteSkelAttack", 0, 11, 10, false, false, rightAttack, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("bigBoneLeftAttack", "bigWhiteSkelAttack", 12, 23, 10, false, false, leftAttack, this);
	
	//DIE상태
	//IMAGEMANAGER->findImage("skelBone");

	_bigBoneMotion = KEYANIMANAGER->findAnimation("bigBoneLeftMove");
	_bigBoneMotion->start();

	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

	_renPoint[0] = PointMake(72, 170);
	_renPoint[1] = PointMake(72, 100);


	return S_OK;
}

void BigBone::release()
{
}

void BigBone::update()
{
	changeDirection();
	move();
	
	///////////die테스트!///////////////////
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		
	}
	if (KEYMANAGER->isOnceKeyUp(VK_F2))
	{
	
	}
	///////////▲▲▲▲▲▲▲▲▲▲▲///////////////

	KEYANIMANAGER->update();

}

void BigBone::render()
{
	switch (_bigBoneDirection)
	{
	case BIGBONE_RIGHT_IDLE:
		break;
	case BIGBONE_LEFT_IDLE:
		break;
	case BIGBONE_RIGHT_MOVE:
		_img->aniRender(DC, _x - 45, _y - 50, _bigBoneMotion);
		break;
	case BIGBONE_LEFT_MOVE:
		//_img->aniRender(DC, _x - 45, _y - 50, _bigBoneMotion);
		_img->aniRender(DC, _x - 45, _y - 50, _bigBoneMotion);
		break;
	case BIGBONE_DIE:
		break;
	case BIGBONE_RIGHT_ATTACK:
		_img->aniRender(DC, _x  - 45, _y - 125 + 5, _bigBoneMotion);
		break;
	case BIGBONE_LEFT_ATTACK:
		_img->aniRender(DC, _x - 90 - 45, _y - 85 - 50 + 15, _bigBoneMotion);
		break;
	}

	
	///////////테스트
	if (KEYMANAGER->isToggleKey('Q')) RectangleMakeCenter(DC, _x, _y, _img->getFrameWidth(), _img->getFrameHeight());

}

void BigBone::move()
{
	switch (_bigBoneDirection)
	{
		case BIGBONE_RIGHT_MOVE: 
			rightMove();
		break;
		case BIGBONE_LEFT_MOVE: 
			leftMove();
		break;
		default:
			_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	}
}

void BigBone::rightMove()
{
	_x += BIGBONESPEED;
	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
}

void BigBone::leftMove()
{
	_x -= BIGBONESPEED;
	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
}

void BigBone::rightAttack(void * obj)
{
	BigBone* b = (BigBone*)obj;

	b->_img = IMAGEMANAGER->findImage("bigWhiteSkelIdleMove");
	b->setBigBoneDirection(BIGBONE_RIGHT_MOVE);
	b->setBigBoneMotion(KEYANIMANAGER->findAnimation("bigBoneRightMove"));
	b->getBigBoneMotion()->start();
}

void BigBone::leftAttack(void * obj)
{
	BigBone* b = (BigBone*)obj;

	b->_img = IMAGEMANAGER->findImage("bigWhiteSkelIdleMove");
	b->setBigBoneDirection(BIGBONE_LEFT_MOVE);
	b->setBigBoneMotion(KEYANIMANAGER->findAnimation("bigBoneLeftMove"));
	b->getBigBoneMotion()->start();
}

void BigBone::changeDirection()
{
	//방향 전환
	if (_x - 100 < 0 && _bigBoneDirection == BIGBONE_LEFT_MOVE)
	{
		changeAnimation(BIGBONE_RIGHT_MOVE);
	}
	if (_x + 100 > WINSIZEX && _bigBoneDirection == BIGBONE_RIGHT_MOVE)
	{
		changeAnimation(BIGBONE_LEFT_MOVE);
	}

	_count++;
	if (!(_count % 100))
	{
		_count = 0;
		//_isAttack = true;

		if (_bigBoneDirection == BIGBONE_RIGHT_MOVE)
		{
			changeAnimation(BIGBONE_RIGHT_ATTACK);
		}
		if (_bigBoneDirection == BIGBONE_LEFT_MOVE)
		{
			changeAnimation(BIGBONE_LEFT_ATTACK);
		}
	}

}

void BigBone::changeAnimation(BIGBONEDIRECTION bigBoneDirection)
{
	switch (bigBoneDirection)
	{
		case BIGBONE_RIGHT_IDLE:
			_img = IMAGEMANAGER->findImage("bigWhiteSkelIdleMove");
			_bigBoneDirection = BIGBONE_RIGHT_IDLE;
			_bigBoneMotion = KEYANIMANAGER->findAnimation("bigBoneRightIdle");
			_bigBoneMotion->start();
			_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
		case BIGBONE_LEFT_IDLE:
			_img = IMAGEMANAGER->findImage("bigWhiteSkelIdleMove");
			_bigBoneDirection = BIGBONE_LEFT_IDLE;
			_bigBoneMotion = KEYANIMANAGER->findAnimation("bigBoneLeftIdle");
			_bigBoneMotion->start();
			_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
		case BIGBONE_RIGHT_MOVE:
			_img = IMAGEMANAGER->findImage("bigWhiteSkelIdleMove");
			_bigBoneDirection = BIGBONE_RIGHT_MOVE;
			_bigBoneMotion = KEYANIMANAGER->findAnimation("bigBoneRightMove");
			_bigBoneMotion->start();
			_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
		case BIGBONE_LEFT_MOVE:
			_img = IMAGEMANAGER->findImage("bigWhiteSkelIdleMove");
			_bigBoneDirection = BIGBONE_LEFT_MOVE;
			_bigBoneMotion = KEYANIMANAGER->findAnimation("bigBoneLeftMove");
			_bigBoneMotion->start();
			_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
		/*case DIE:
			_img = IMAGEMANAGER->findImage("skelBone");
			_bigBoneDirection = DIE;
			//
			_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;*/
		case BIGBONE_RIGHT_ATTACK:
			_img = IMAGEMANAGER->findImage("bigWhiteSkelAttack");
			_bigBoneDirection = BIGBONE_RIGHT_ATTACK;
			_bigBoneMotion = KEYANIMANAGER->findAnimation("bigBoneRightAttack");
			_bigBoneMotion->start();
			_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
		case BIGBONE_LEFT_ATTACK:
			_img = IMAGEMANAGER->findImage("bigWhiteSkelAttack");
			_bigBoneDirection = BIGBONE_LEFT_ATTACK;
			_bigBoneMotion = KEYANIMANAGER->findAnimation("bigBoneLeftAttack");
			_bigBoneMotion->start();
			_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
		default:
			_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	}
}


