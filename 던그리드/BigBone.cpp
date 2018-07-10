#include "stdafx.h"
#include "BigBone.h"


BigBone::BigBone()
{
}


BigBone::~BigBone()
{
}

HRESULT BigBone::init(float x, float y, int index)
{
	_index = index;

	_bigBoneDirection = BIGBONE_LEFT_MOVE;
	_x = x;
	_y = y;
	_count = 0;
	
	_img = IMAGEMANAGER->findImage("bigWhiteSkelIdleMove");
	
	//IDLE상태
	KEYANIMANAGER->addCoordinateFrameAnimation("bigBoneRightIdle", "bigWhiteSkelIdleMove", 0, 5, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("bigBoneLeftIdle", "bigWhiteSkelIdleMove", 6, 11, 10, false, true);
	//MOVE상태
	KEYANIMANAGER->addCoordinateFrameAnimation("bigBoneRightMove", "bigWhiteSkelIdleMove", 12, 17, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("bigBoneLeftMove", "bigWhiteSkelIdleMove", 18, 23, 10, false, true);

	//ATTACK상태
	char str[50];
	sprintf_s(str, "bigBoneRightAttack%d", _index);
	KEYANIMANAGER->addCoordinateFrameAnimation(str, "bigWhiteSkelAttack", 0, 11, 10, false, false, rightAttack, this);

	sprintf_s(str, "bigBoneLeftAttack%d", _index);
	KEYANIMANAGER->addCoordinateFrameAnimation(str, "bigWhiteSkelAttack", 12, 23, 10, false, false, leftAttack, this);
	
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
	/*if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		
	}
	if (KEYMANAGER->isOnceKeyUp(VK_F2))
	{
	
	}*/
	///////////▲▲▲▲▲▲▲▲▲▲▲///////////////

	//KEYANIMANAGER->update();

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
		_img->aniRender(DC, _x  - 45, _y - 125 + 5 -60, _bigBoneMotion);
		break;
	case BIGBONE_LEFT_ATTACK:
		_img->aniRender(DC, _x - 90 - 45, _y - 85 - 50 + 15-60, _bigBoneMotion);
		break;
	}

	
	///////////테스트
	if (KEYMANAGER->isToggleKey('Q')) RectangleMakeCenter(DC, _x, _y, _img->getFrameWidth(), _img->getFrameHeight());

	if (KEYMANAGER->isToggleKey('T'))
	{
		Rectangle(DC, _rcCollision.left, _rcCollision.top, _rcCollision.right, _rcCollision.bottom);
	}

}

void BigBone::move()
{
	RECT rcCollision;

	int tileIndex[2];
	int tileX, tileY;
	rcCollision = _rc;

	switch (_bigBoneDirection)
	{
		case BIGBONE_RIGHT_MOVE: 
			//rightMove();
			_x += BIGBONESPEED;
			rcCollision = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
		case BIGBONE_LEFT_MOVE: 
			//leftMove();
			_x -= BIGBONESPEED;
			rcCollision = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
		default:
		//	rcCollision = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
			return;
		break;
	}

	rcCollision.left += 2;
	rcCollision.top += 2;
	rcCollision.right -= 2;
	rcCollision.bottom -= 2;

	_rcCollision = rcCollision;

	
	tileX = rcCollision.left / TILESIZE;
	tileY = rcCollision.top / TILESIZE;

	switch (_bigBoneDirection)
	{
		case BIGBONE_RIGHT_MOVE: 
			tileIndex[0] = (tileX + tileY * VARIABLE_SIZEX[_dungeonNum]) + 2;
			tileIndex[1] = (tileX + (1 + tileY) *  VARIABLE_SIZEX[_dungeonNum]) + 2;
		break;
		case BIGBONE_LEFT_MOVE: 
			tileIndex[0] = tileX + tileY * VARIABLE_SIZEX[_dungeonNum];
			tileIndex[1] = tileX + (tileY + 1)*VARIABLE_SIZEX[_dungeonNum];
		break;
	}
	if (tileIndex[0] == 1003 || tileIndex[1] == 1003)
		int a = 0;
	for (int i = 0; i < 2; i++)
	{
		if (_dungeonNum == 4 && tileIndex[i] >= 327)
		{
			changeAnimation(BIGBONE_LEFT_MOVE);
			break;
		}
		RECT temp;
		if ((_tiles[tileIndex[i]].object == OBJ_DIAGONAL_LEFT || _tiles[tileIndex[i]].object == OBJ_DIAGONAL_RIGHT || _tiles[tileIndex[i]].object == OBJ_DIAGONAL || _tiles[tileIndex[i]].object == OBJ_CULUMN) &&
			IntersectRect(&temp, &_tiles[tileIndex[i]].rc, &rcCollision))
		{
			switch (_bigBoneDirection)
			{
			case BIGBONE_RIGHT_MOVE:
				_rc.right = _tiles[tileIndex[i]].rc.left;
				_rc.left = _rc.right - 130;
				_x = _rc.left + (_rc.right - _rc.left) / 2;
				changeAnimation(BIGBONE_LEFT_MOVE);
				break;
			case BIGBONE_LEFT_MOVE:
				_rc.left = _tiles[tileIndex[i]].rc.right;
				_rc.right = _rc.left + 130;
				_x = _rc.left + (_rc.right - _rc.left) / 2;
				changeAnimation(BIGBONE_RIGHT_MOVE);
				break;
			}
			return;
		}
	}
	rcCollision = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
	_rc = rcCollision;
}

/*void BigBone::rightMove()
{
	_x += BIGBONESPEED;
	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
}

void BigBone::leftMove()
{
	_x -= BIGBONESPEED;
	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
}*/

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
	/*if (_x - 100 < 0 && _bigBoneDirection == BIGBONE_LEFT_MOVE)
	{
		changeAnimation(BIGBONE_RIGHT_MOVE);
	}
	if (_x + 100 > WINSIZEX && _bigBoneDirection == BIGBONE_RIGHT_MOVE)
	{
		changeAnimation(BIGBONE_LEFT_MOVE);
	}*/

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
			char str[50];
			sprintf_s(str, "bigBoneRightAttack%d", _index);
			_bigBoneMotion = KEYANIMANAGER->findAnimation(str);
			_bigBoneMotion->start();
			_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
		case BIGBONE_LEFT_ATTACK:
			_img = IMAGEMANAGER->findImage("bigWhiteSkelAttack");
			_bigBoneDirection = BIGBONE_LEFT_ATTACK;
			sprintf_s(str, "bigBoneLeftAttack%d", _index);
			_bigBoneMotion = KEYANIMANAGER->findAnimation(str);
			_bigBoneMotion->start();
			_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
		default:
			_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	}
}

