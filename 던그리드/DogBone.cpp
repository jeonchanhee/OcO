#include "stdafx.h"
#include "DogBone.h"


DogBone::DogBone()
{
}


DogBone::~DogBone()
{
}

HRESULT DogBone::init()
{
	_dogBoneDirection = LEFT_MOVE;
	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2;
	_jumpPower = 3.0f;
	_gravity = 0.04f;

	//IDLE»óÅÂ
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
	int rightDie[] = { 13 };
	KEYANIMANAGER->addArrayFrameAnimation("dogBoneRightDie", "skelDogMoveDie", rightDie, 1, 6, true);
	int leftDie[] = { 14 };
	KEYANIMANAGER->addArrayFrameAnimation("dogBoneLeftDie", "skelDogMoveDie", leftDie, 1, 6, true);

	_dogBoneMotion = KEYANIMANAGER->findAnimation("dogBoneLeftStop");
	_dogBoneMotion->start();

	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

	return S_OK;
}

void DogBone::release()
{
}

void DogBone::update()
{
	/*if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_img = IMAGEMANAGER->findImage("skelDogMoveDie");
		_dogBoneDirection = RIGHT_MOVE;
		_dogBoneMotion = KEYANIMANAGER->findAnimation("dogBoneRightMove");
		_dogBoneMotion->start();
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_img = IMAGEMANAGER->findImage("skelDogIdle");
		_dogBoneDirection = RIGHT_IDLE;
		_dogBoneMotion = KEYANIMANAGER->findAnimation("dogBoneRightStop");
		_dogBoneMotion->start();
	} 


	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_img = IMAGEMANAGER->findImage("skelDogMoveDie");
		_dogBoneDirection = LEFT_MOVE;
		_dogBoneMotion = KEYANIMANAGER->findAnimation("dogBoneLeftMove");
		_dogBoneMotion->start();
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		_img = IMAGEMANAGER->findImage("skelDogIdle");
		_dogBoneDirection = LEFT_IDLE;
		_dogBoneMotion = KEYANIMANAGER->findAnimation("dogBoneLeftStop");
		_dogBoneMotion->start();
	}*/

	move();

	switch (_dogBoneDirection)
	{
		case RIGHT_MOVE:
			_x += DOGBONESPEED;
			_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
		case LEFT_MOVE:
			_x -= DOGBONESPEED;
			_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
		case RIGHT_JUMP:
				_y -= _jumpPower;
				_jumpPower -= _gravity;
				_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
		case LEFT_JUMP:
				_y -= _jumpPower;
				_jumpPower -= _gravity;
				_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
		default:
			_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	}
	
	KEYANIMANAGER->update();
}

void DogBone::render()
{
	_img->aniRender(DC, _rc.left, _rc.top, _dogBoneMotion);
}

void DogBone::move()
{

	if (_x - _img->getFrameWidth() / 2 < 0)
	{
		_img = IMAGEMANAGER->findImage("skelDogMoveDie");
		_dogBoneDirection = RIGHT_MOVE;
		_dogBoneMotion = KEYANIMANAGER->findAnimation("dogBoneRightMove");
		_dogBoneMotion->start();

	}
	if (_x + _img->getFrameWidth() / 2 > WINSIZEX)
	{
		_img = IMAGEMANAGER->findImage("skelDogMoveDie");
		_dogBoneDirection = LEFT_MOVE;
		_dogBoneMotion = KEYANIMANAGER->findAnimation("dogBoneLeftMove");
		_dogBoneMotion->start();
		//_x -= DOGBONESPEED;
	}
	if (_x == WINSIZEX / 4 || _x == WINSIZEX / 2 || _x == WINSIZEX * 3 / 4)
	{
		if (_dogBoneDirection == LEFT_MOVE || _dogBoneDirection == LEFT_IDLE)
		{
			_img = IMAGEMANAGER->findImage("skelDogMoveDie");
			_dogBoneDirection = LEFT_JUMP;
			_dogBoneMotion = KEYANIMANAGER->findAnimation("dogBoneRightMove");
			_dogBoneMotion->start();
		}
		if (_dogBoneDirection == RIGHT_MOVE || _dogBoneDirection == RIGHT_IDLE)
		{
			_img = IMAGEMANAGER->findImage("skelDogMoveDie");
			_dogBoneDirection = RIGHT_JUMP;
			_dogBoneMotion = KEYANIMANAGER->findAnimation("dogBoneLeftMove");
			//_dogBoneDirection
			
		}
	}
}

