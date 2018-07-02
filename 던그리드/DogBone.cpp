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
	_dogBoneDirection = LEFT_IDLE;
	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2;

	//IDLE상태
	_img = IMAGEMANAGER->findImage("skelDogIdle");
	
	int leftIdle[] = { 5,6,7,8,9 };
	KEYANIMANAGER->addArrayFrameAnimation("dogBoneLeftStop", "skelDogIdle", leftIdle, 5, 10, true);
	int rightIdle[] = { 0,1,2,3,4 };
	KEYANIMANAGER->addArrayFrameAnimation("dogBoneRightStop", "skelDogIdle", rightIdle, 5, 10, true);

	//MOVE & DIE상태
	IMAGEMANAGER->findImage("skelDogMoveDie");

	int rightMove[] = { 0,1,2,3,4,5,6 };
	KEYANIMANAGER->addArrayFrameAnimation("dogBoneRightMove", "skelDogMoveDie", rightMove, 7, 10, true);
	int leftMove[] = { 7,8,9,10,11,12,13 };
	KEYANIMANAGER->addArrayFrameAnimation("dogBoneLeftMove", "skelDogMoveDie", leftMove, 7, 10, true);
	int rightDie[] = { 13 };
	KEYANIMANAGER->addArrayFrameAnimation("dogBoneRightDie", "skelDogMoveDie", rightDie, 1, 6, true);
	int leftDie[] = { 14 };
	KEYANIMANAGER->addArrayFrameAnimation("dogBoneLeftDie", "skelDogMoveDie", leftDie, 1, 6, true);

	_dogBoneMotion = KEYANIMANAGER->findAnimation("leftIdle");

	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

	return S_OK;
}

void DogBone::release()
{
}

void DogBone::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_dogBoneDirection = RIGHT_MOVE;
		_dogBoneMotion = KEYANIMANAGER->findAnimation("dogBoneRightMove");
		_dogBoneMotion->start();
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_dogBoneDirection = RIGHT_IDLE;
		_dogBoneMotion = KEYANIMANAGER->findAnimation("dogBoneRightStop");
		_dogBoneMotion->start();
	}


	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_dogBoneDirection = LEFT_MOVE;
		_dogBoneMotion = KEYANIMANAGER->findAnimation("dogBoneLeftMove");
		_dogBoneMotion->start();
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_dogBoneDirection = LEFT_IDLE;
		_dogBoneMotion = KEYANIMANAGER->findAnimation("dogBoneLEftStop");
		_dogBoneMotion->start();
	}


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
		default:
			_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	}

}

void DogBone::render()
{
	_img->aniRender(DC, _rc.left, _rc.top, _dogBoneMotion);
}


