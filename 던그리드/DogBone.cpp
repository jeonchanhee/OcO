#include "stdafx.h"
#include "DogBone.h"


DogBone::DogBone()
{
}


DogBone::~DogBone()
{
}

HRESULT DogBone::init(float x, float y)
{
	_dogBoneDirection = DOGBONE_LEFT_MOVE;
	_x = x;
	_y = _startY = y;
	_jumpPower = 5.0f;
	_gravity = 0.15f;

	//IDLE상태
	_img = IMAGEMANAGER->findImage("skelDogMoveDie");

	int leftIdle[] = { 5,6,7,8,9 };
	KEYANIMANAGER->addArrayFrameAnimation("dogBoneLeftStop", "skelDogIdle", leftIdle, 5, 6, true);
	int rightIdle[] = { 0,1,2,3,4 };
	KEYANIMANAGER->addArrayFrameAnimation("dogBoneRightStop", "skelDogIdle", rightIdle, 5, 6, true);

	int rightMove[] = { 0,1,2,3,4,5,6 };
	KEYANIMANAGER->addArrayFrameAnimation("dogBoneRightMove", "skelDogMoveDie", rightMove, 7, 15, true);
	//KEYANIMANAGER->addCoordinateFrameAnimation("dogBoneRightMove", "skelDogMoveDie", 0, 6, 10, false, true);

	int leftMove[] = { 7,8,9,10,11,12,13 };
	KEYANIMANAGER->addArrayFrameAnimation("dogBoneLeftMove", "skelDogMoveDie", leftMove, 7, 15, true);
	int rightDie[] = { 14 };
	KEYANIMANAGER->addArrayFrameAnimation("dogBoneRightDie", "skelDogMoveDie", rightDie, 1, 6, false);
	int leftDie[] = { 15 };
	KEYANIMANAGER->addArrayFrameAnimation("dogBoneLeftDie", "skelDogMoveDie", leftDie, 1, 6, false);

	_dogBoneMotion = KEYANIMANAGER->findAnimation("dogBoneLeftStop");
	_dogBoneMotion->start();

	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

	_count = 0;

	_isJumping = false;

	return S_OK;
}

void DogBone::release()
{
}

void DogBone::update()
{
	changeDirection();
	move();

	if (_isJumping && _y > _startY)//초기 위치보다 크면 초기위치에서 멈춤 (_startY)
	{
		_isJumping = false;
		_y = _startY;
		_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		if (_dogBoneDirection == DOGBONE_LEFT_JUMP)
			_dogBoneDirection = DOGBONE_LEFT_MOVE;
		else if (_dogBoneDirection == DOGBONE_RIGHT_JUMP)
			_dogBoneDirection = DOGBONE_RIGHT_MOVE;
	}

	//KEYANIMANAGER->update();


	////////////////////DIE테스트임///////////////////////////
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		if (_dogBoneDirection == DOGBONE_RIGHT_MOVE || _dogBoneDirection == DOGBONE_RIGHT_IDLE || _dogBoneDirection == DOGBONE_RIGHT_JUMP)
		{
			//_dogBoneDirection = RIGHT_DIE;
			changeAnimation(DOGBONE_RIGHT_DIE);
		}
		else if (_dogBoneDirection == DOGBONE_LEFT_MOVE || _dogBoneDirection == DOGBONE_LEFT_IDLE || _dogBoneDirection == DOGBONE_LEFT_JUMP)
		{
			//_dogBoneDirection = LEFT_DIE;
			changeAnimation(DOGBONE_LEFT_DIE);
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_F1))
	{
		if (_dogBoneDirection == DOGBONE_RIGHT_DIE)
		{
			changeAnimation(DOGBONE_RIGHT_MOVE);
		}
		else if (_dogBoneDirection == DOGBONE_LEFT_DIE)
		{
			changeAnimation(DOGBONE_LEFT_MOVE);
		}
	}
	////////////////////▲▲▲▲▲▲▲▲///////////////////
}

void DogBone::render()
{
	_img->aniRender(DC, _rc.left, _rc.top, _dogBoneMotion);
}

void DogBone::move()
{
	RECT rcCollision;
	int tileIndex[2];
	int tileX, tileY;
	rcCollision = _rc;

	switch (_dogBoneDirection)
	{
	case DOGBONE_RIGHT_MOVE:
		rightMove();
		break;
	case DOGBONE_LEFT_MOVE:
		leftMove();
		break;
	case DOGBONE_RIGHT_JUMP:
		rightJump();
		break;
	case DOGBONE_LEFT_JUMP:
		leftJump();
		break;
	default:
		//_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
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

	switch (_dogBoneDirection)
	{
	case DOGBONE_RIGHT_MOVE: case DOGBONE_RIGHT_JUMP:
		tileIndex[0] = (tileX + tileY * VARIABLE_SIZEX[_dungeonNum]) + 1;
		tileIndex[1] = (tileX + (1 + tileY) *  VARIABLE_SIZEX[_dungeonNum]) + 1;
		break;
	case DOGBONE_LEFT_MOVE: case DOGBONE_LEFT_JUMP:
		tileIndex[0] = tileX + tileY * VARIABLE_SIZEX[_dungeonNum];
		tileIndex[1] = tileX + (tileY + 1)*VARIABLE_SIZEX[_dungeonNum];
		break;
	}
	for (int i = 0; i < 2; i++)
	{
		RECT temp;
		if ((_tiles[tileIndex[i]].object == OBJ_CULUMN) && 
			IntersectRect(&temp, &_tiles[tileIndex[i]].rc, &rcCollision))
		{
			switch (_dogBoneDirection)
			{
			case DOGBONE_RIGHT_MOVE: case DOGBONE_RIGHT_JUMP:
				_rc.right = _tiles[tileIndex[i]].rc.left;
				_rc.left = _rc.right - 100;
				_x = _rc.left + (_rc.right - _rc.left) / 2;
				changeAnimation(DOGBONE_LEFT_IDLE);
				break;
			case DOGBONE_LEFT_MOVE: case DOGBONE_LEFT_JUMP:
				_rc.left = _tiles[tileIndex[i]].rc.right;
				_rc.right = _rc.left + 100;
				_x = _rc.left + (_rc.right - _rc.left) / 2;
				changeAnimation(DOGBONE_RIGHT_IDLE);
				break;
			}
			return;
		}
	}
	rcCollision = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
	_rc = rcCollision;

}
void DogBone::rightMove()
{
	_x += DOGBONESPEED;
	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
}

void DogBone::leftMove()
{
	_x -= DOGBONESPEED;
	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
}

void DogBone::rightJump()
{
	_x += DOGBONESPEED;
	_y -= _jumpPower;
	_jumpPower -= _gravity;
	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
}

void DogBone::leftJump()
{
	_x -= DOGBONESPEED;
	_y -= _jumpPower;
	_jumpPower -= _gravity;
	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
}

void DogBone::changeDirection()
{
	//이동 가능 범위(방향전환)
	if (_x - _img->getFrameWidth() / 2 < 0)
	{
		if (_dogBoneDirection == DOGBONE_LEFT_JUMP) changeAnimation(DOGBONE_RIGHT_JUMP);
		else changeAnimation(DOGBONE_RIGHT_MOVE);
	}
	if (_x + _img->getFrameWidth() / 2 > WINSIZEX)
	{
		if (_dogBoneDirection == DOGBONE_RIGHT_JUMP) changeAnimation(DOGBONE_LEFT_JUMP);
		else changeAnimation(DOGBONE_LEFT_MOVE);
	}

	//점프
	_count++;
	
	if (!(_count % 100) && !_isJumping)
	{
		_count = 0;
		_isJumping = true;
		_jumpPower = 5.0f;
		_gravity = 0.15f;

		if (_dogBoneDirection == DOGBONE_RIGHT_MOVE)
		{
			changeAnimation(DOGBONE_RIGHT_JUMP);
		}
		if (_dogBoneDirection == DOGBONE_LEFT_MOVE)
		{
			changeAnimation(DOGBONE_LEFT_JUMP);
		}
	}
}

void DogBone::changeAnimation(DOGBONEDIRECTION dogBoneDirection)
{
	switch (dogBoneDirection)
	{
	case DOGBONE_RIGHT_MOVE:
		_img = IMAGEMANAGER->findImage("skelDogMoveDie");
		_dogBoneDirection = DOGBONE_RIGHT_MOVE;
		_dogBoneMotion = KEYANIMANAGER->findAnimation("dogBoneRightMove");
		_dogBoneMotion->start();
		break;
	case DOGBONE_LEFT_MOVE:
		_img = IMAGEMANAGER->findImage("skelDogMoveDie");
		_dogBoneDirection = DOGBONE_LEFT_MOVE;
		_dogBoneMotion = KEYANIMANAGER->findAnimation("dogBoneLeftMove");
		_dogBoneMotion->start();
		break;
	case DOGBONE_RIGHT_JUMP:
		_img = IMAGEMANAGER->findImage("skelDogMoveDie");
		_dogBoneDirection = DOGBONE_RIGHT_JUMP;
		_dogBoneMotion = KEYANIMANAGER->findAnimation("dogBoneRightMove");
		_dogBoneMotion->start();
		break;
	case DOGBONE_LEFT_JUMP:
		_img = IMAGEMANAGER->findImage("skelDogMoveDie");
		_dogBoneDirection = DOGBONE_LEFT_JUMP;
		_dogBoneMotion = KEYANIMANAGER->findAnimation("dogBoneLeftMove");
		_dogBoneMotion->start();
		break;
	case DOGBONE_RIGHT_DIE:
		_img = IMAGEMANAGER->findImage("skelDogMoveDie");
		_dogBoneDirection = DOGBONE_RIGHT_DIE;
		_dogBoneMotion = KEYANIMANAGER->findAnimation("dogBoneRightDie");
		_dogBoneMotion->start();
		break;
	case DOGBONE_LEFT_DIE:
		_img = IMAGEMANAGER->findImage("skelDogMoveDie");
		_dogBoneDirection = DOGBONE_LEFT_DIE;
		_dogBoneMotion = KEYANIMANAGER->findAnimation("dogBoneLeftDie");
		_dogBoneMotion->start();
		break;
	default:
		_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	}
}