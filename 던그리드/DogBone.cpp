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
	_dogBoneDirection = DOGBONE_LEFT_JUMP;
	_x = x;
	_y = _startY = y;
	
	_gravity = 0.15f;

	_jumpPower = 0;
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

	_count = 80;

	_isJumping = false;

	//개뼈 체력 초기화
	_progressBar = new progressBar;
	_progressBar->init(_x - 30, _y + 30, 70, 10, "개뼈앞", "개뼈뒤", BAR_MONSTER);
	_currentHP = _maxHP = 100;

	return S_OK;
}

void DogBone::release()
{
}

void DogBone::update()
{
	//개뼈 체력 업데이트
	_progressBar->setX(_x - 30);
	_progressBar->setY(_y + 30);
	_progressBar->setGauge(_currentHP, _maxHP);
	_progressBar->update();

	//move();
	changeDirection();
	

	//if (_isJumping && _y > _startY)//초기 위치보다 크면 초기위치에서 멈춤 (_startY)
	//{
	//	_isJumping = false;
	//	_y = _startY;
	//	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
	//	if (_dogBoneDirection == DOGBONE_LEFT_JUMP)
	//		_dogBoneDirection = DOGBONE_LEFT_MOVE;
	//	else if (_dogBoneDirection == DOGBONE_RIGHT_JUMP)
	//		_dogBoneDirection = DOGBONE_RIGHT_MOVE;
	//}

	//KEYANIMANAGER->update();
	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

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
	_progressBar->render();
	_img->aniRender(DC, _rc.left, _rc.top, _dogBoneMotion);
	if (KEYMANAGER->isToggleKey('T'))
	{
		Rectangle(DC, _rcCollision.left, _rcCollision.top, _rcCollision.right, _rcCollision.bottom);
		TextOut(DC, 200, 200, _str.c_str(), strlen(_str.c_str()));
	}
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
		//rightMove();
		_x += DOGBONESPEED;
		rcCollision = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	case DOGBONE_LEFT_MOVE:
		//leftMove();
		_x -= DOGBONESPEED;
		rcCollision = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	case DOGBONE_RIGHT_JUMP:
		//rightJump();
		_x += DOGBONESPEED;
		_y -= _jumpPower;
		_jumpPower -= _gravity;
		rcCollision = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	case DOGBONE_LEFT_JUMP:
		//leftJump();
		_x -= DOGBONESPEED;
		_y -= _jumpPower;
		_jumpPower -= _gravity;
		rcCollision = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	default:
		_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		return;
		break;
	}
	_y -= _jumpPower;
	_jumpPower -= _gravity;

	rcCollision.left += 2;
	rcCollision.top += 2;
	rcCollision.right += 100;
	rcCollision.bottom -= 2;

	_rcCollision = rcCollision;

	tileX = rcCollision.left / TILESIZE;
	tileY = rcCollision.top / TILESIZE;

	int tempY = (rcCollision.bottom - 20) / TILESIZE;
	int temp2 = (rcCollision.right - 110) / TILESIZE;
	
	int index;
	switch (_dogBoneDirection)
	{
	case DOGBONE_RIGHT_MOVE: case DOGBONE_RIGHT_JUMP:
		tileIndex[0] = (tileX + (tileY) * VARIABLE_SIZEX[_dungeonNum]) + 1;
		
		index = (temp2 + tempY * VARIABLE_SIZEX[_dungeonNum]);
		break;
	case DOGBONE_LEFT_MOVE: case DOGBONE_LEFT_JUMP:
		tileIndex[0] = tileX + (tileY) * VARIABLE_SIZEX[_dungeonNum];
		index = (tileX + tempY * VARIABLE_SIZEX[_dungeonNum]);
		break;
	}
	_str = to_string(tileIndex[0]) + "," + to_string(tileIndex[1]);

	if (_tiles[index].object == OBJ_DIAGONAL)
	{
		if(_dogBoneDirection == DOGBONE_RIGHT_MOVE || _dogBoneDirection == DOGBONE_RIGHT_JUMP)
			_y = _tiles[index].rc.bottom - (_rc.right - _tiles[index].rc.left) - _img->getFrameHeight() / 2;  // 오른쪽
		if (_dogBoneDirection == DOGBONE_LEFT_MOVE || _dogBoneDirection == DOGBONE_LEFT_JUMP)
			_y = _tiles[index].rc.bottom - (_tiles[index].rc.right - _rc.left) - _img->getFrameHeight() / 2;//왼쪽
	}

	if (_tiles[index].object == OBJ_DIAGONAL_RIGHT)
	{
		if (_dogBoneDirection == DOGBONE_RIGHT_MOVE || _dogBoneDirection == DOGBONE_RIGHT_JUMP)
			_y = _tiles[index].rc.bottom - (_rc.right - _tiles[index].rc.left) - _img->getFrameHeight() / 2;  // 오른쪽
		if (_dogBoneDirection == DOGBONE_LEFT_MOVE || _dogBoneDirection == DOGBONE_LEFT_JUMP)
			_y = _tiles[index].rc.bottom - (_tiles[index].rc.right - _rc.left) - _img->getFrameHeight() / 2;//왼쪽
	}

	if (_tiles[index].object == OBJ_DIAGONAL_LEFT)
	{
		if(_dogBoneDirection == DOGBONE_LEFT_MOVE || _dogBoneDirection == DOGBONE_LEFT_JUMP)
			_y = _tiles[index].rc.bottom - (_tiles[index].rc.right - _rc.left) - _img->getFrameHeight() / 2; // 왼쪽
		if(_dogBoneDirection == DOGBONE_RIGHT_MOVE || _dogBoneDirection == DOGBONE_RIGHT_JUMP)
			_y = _tiles[index].rc.bottom - (_rc.right - _tiles[index].rc.left) - _img->getFrameHeight() / 2;  // 오른쪽
	}

	


		if (_dungeonNum == 1 && !(tileIndex[0] % 100))
		{
			changeAnimation(DOGBONE_RIGHT_MOVE);
			return;
		}

		if (_dungeonNum == 2 && !(tileIndex[0] % 30))
		{
			changeAnimation(DOGBONE_RIGHT_MOVE);
			return;
		}

		if (_dungeonNum == 6 && (tileIndex[0] % 20 == 19))
		{
			changeAnimation(DOGBONE_LEFT_MOVE);
			return;
		}

		RECT temp;
		
		if ((_tiles[tileIndex[0]].object == OBJ_CULUMN) && IntersectRect(&temp, &_tiles[tileIndex[0]].rc, &rcCollision))
		{
			switch (_dogBoneDirection)
			{
			case DOGBONE_RIGHT_MOVE: 
				_rc.right = _tiles[tileIndex[0]].rc.left;
				_rc.left = _rc.right - 100;
				_x = _rc.left + (_rc.right - _rc.left) / 2;
				changeAnimation(DOGBONE_LEFT_MOVE);
				break;
			case DOGBONE_RIGHT_JUMP:
				_rc.right = _tiles[tileIndex[0]].rc.left;
				_rc.left = _rc.right - 100;
				_x = _rc.left + (_rc.right - _rc.left) / 2;
				changeAnimation(DOGBONE_LEFT_JUMP);
				break;
			case DOGBONE_LEFT_MOVE:
				_rc.left = _tiles[tileIndex[0]].rc.right;
				_rc.right = _rc.left + 100;
				_x = _rc.left + (_rc.right - _rc.left) / 2;
				changeAnimation(DOGBONE_RIGHT_MOVE);
				break;
			case DOGBONE_LEFT_JUMP:
				_rc.left = _tiles[tileIndex[0]].rc.right;
				_rc.right = _rc.left + 100;
				_x = _rc.left + (_rc.right - _rc.left) / 2;
				changeAnimation(DOGBONE_RIGHT_JUMP);
				break;
			}
			return;
		}

		rcCollision.left += 2;
		rcCollision.top += 2;
		rcCollision.right -= 102;
		rcCollision.bottom -= 20;

		switch (_dogBoneDirection)
		{
		case DOGBONE_RIGHT_MOVE: case DOGBONE_RIGHT_JUMP:
			tileIndex[0] = (tileX + (tileY + 1)* VARIABLE_SIZEX[_dungeonNum]);
			tileIndex[1] = (tileX + (tileY + 1)* VARIABLE_SIZEX[_dungeonNum]) + 1;
			break;
		case DOGBONE_LEFT_MOVE: case DOGBONE_LEFT_JUMP:
			tileIndex[0] = (tileX + (tileY + 1)* VARIABLE_SIZEX[_dungeonNum]) - 1;
			tileIndex[1] = (tileX + (tileY + 1)* VARIABLE_SIZEX[_dungeonNum]);
			break;
		}

		_str = to_string(tileIndex[0]) + "," + to_string(tileIndex[1]);
		
		for (int i = 0; i < 2; i++)
		{
			if (tileIndex[i] == 1205)
				int a = 0;
			if ((_tiles[tileIndex[i]].object == OBJ_CULUMN || _tiles[tileIndex[i]].object == OBJ_GOGROUND) && IntersectRect(&temp, &_tiles[tileIndex[i]].rc, &rcCollision))
			{
				/*switch (_dogBoneDirection)
				{
				case DOGBONE_RIGHT_MOVE:
					_rc.right = _tiles[tileIndex[0]].rc.left;
					_rc.left = _rc.right - 100;
					_x = _rc.left + (_rc.right - _rc.left) / 2;
					changeAnimation(DOGBONE_LEFT_MOVE);
					break;
				case DOGBONE_RIGHT_JUMP:
					break;
				case DOGBONE_LEFT_MOVE:
					_rc.left = _tiles[tileIndex[0]].rc.right;
					_rc.right = _rc.left + 100;
					_x = _rc.left + (_rc.right - _rc.left) / 2;
					changeAnimation(DOGBONE_RIGHT_MOVE);
					break;
				case DOGBONE_LEFT_JUMP:
					break;
				}
				return;*/
			//	if (_y > _tiles[tileIndex[i]].rc.top - 30)
				{
					_jumpPower = 0;
					_y = _tiles[tileIndex[i]].rc.top - 30;
					_isJumping = false;
				}
				return;
			}
		}

		//if (_tiles[index].object == OBJ_DIAGONAL_LEFT && 
		//	(_dogBoneDirection == DOGBONE_LEFT_MOVE || _dogBoneDirection == DOGBONE_LEFT_JUMP))
		//{
		//	_y -= 4;
		//}
		//
		//if (_tiles[index].object == OBJ_DIAGONAL_RIGHT &&
		//	(_dogBoneDirection == DOGBONE_RIGHT_MOVE || _dogBoneDirection == DOGBONE_RIGHT_JUMP))
		//{
		//	_y -= 4;
		//}
		
		


	rcCollision = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
	_rc = rcCollision;

}
/*
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
*/

void DogBone::changeDirection()
{
	//이동 가능 범위(방향전환)
	//if (_x - _img->getFrameWidth() / 2 < 0)
	//{
	//	if (_dogBoneDirection == DOGBONE_LEFT_JUMP) changeAnimation(DOGBONE_RIGHT_JUMP);
	//	else changeAnimation(DOGBONE_RIGHT_MOVE);
	//}
	//if (_x + _img->getFrameWidth() / 2 > WINSIZEX)
	//{
	//	if (_dogBoneDirection == DOGBONE_RIGHT_JUMP) changeAnimation(DOGBONE_LEFT_JUMP);
	//	else changeAnimation(DOGBONE_LEFT_MOVE);
	//}

	////마우스가 개보다 더 오른쪽에 있으면
	//if (_x <= PTMOUSE_X)
	//{
	//	if (_dogBoneDirection == DOGBONE_LEFT_JUMP) changeAnimation(DOGBONE_RIGHT_JUMP);
	//	else changeAnimation(DOGBONE_RIGHT_MOVE);
	//}
	////마우스가 개보다 더 왼쪽에 있으면
	//if (_x > PTMOUSE_X)
	//{
	//	if (_dogBoneDirection == DOGBONE_RIGHT_JUMP) changeAnimation(DOGBONE_LEFT_JUMP);
	//	else changeAnimation(DOGBONE_LEFT_MOVE);
	//}
	////마우스가 개보다 더 아래에 있으면
	//if (_y < PTMOUSE_Y)
	//{
	//	//_y = PTMOUSE_Y;
	//	if (_dogBoneDirection == DOGBONE_LEFT_MOVE)
	//	{
	//		changeAnimation(DOGBONE_LEFT_JUMP);
	//	}
	//	if (_dogBoneDirection == DOGBONE_RIGHT_MOVE)
	//	{
	//		changeAnimation(DOGBONE_RIGHT_JUMP);
	//	}
	//}

	//점프
	_count++;
	if (!(_count % 100))
	{
		int a = 0;
	}
	if (!(_count % 100) && !_isJumping)
	{
		_count = 0;
		_isJumping = true;
		_jumpPower = 6.0f;
		if (_dogBoneDirection == DOGBONE_RIGHT_MOVE)
		{
			_y -= 100;
			changeAnimation(DOGBONE_RIGHT_JUMP);
		}
		if (_dogBoneDirection == DOGBONE_LEFT_MOVE)
		{
			_y -= 100;
			changeAnimation(DOGBONE_LEFT_JUMP);
		}
		
	}
}

void DogBone::changeAnimation(DOGBONEDIRECTION dogBoneDirection)
{
	switch (dogBoneDirection)
	{
	case DOGBONE_RIGHT_MOVE:
		_isJumping = false;
		_img = IMAGEMANAGER->findImage("skelDogMoveDie");
		_dogBoneDirection = DOGBONE_RIGHT_MOVE;
		_dogBoneMotion = KEYANIMANAGER->findAnimation("dogBoneRightMove");
		_dogBoneMotion->start();
		break;
	case DOGBONE_LEFT_MOVE:
		_isJumping = false;
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
	/*default:
		_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;*/
	}
}

void DogBone::playerCollision()
{
}

void DogBone::hitDamage(float damage)
{
	_currentHP -= damage;
}
