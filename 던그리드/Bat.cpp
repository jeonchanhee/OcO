#include "stdafx.h"
#include "Bat.h"


Bat::Bat()
{
}


Bat::~Bat()
{
}

HRESULT Bat::init(float x, float y)
{
	_batDirection = BAT_RIGHT_MOVE;

	_x = x;
	_y = y;
	//_y = 200;

	_startX = x;
	_startY = y;

	_angle = 0;
	_speed = 300.0f;

	_img = IMAGEMANAGER->findImage("batMoveDie");

	//오른쪽 이동
	KEYANIMANAGER->addCoordinateFrameAnimation("batRightMove", "batMoveDie", 0, 5, 10, false, true);
	//왼쪽 이동
	KEYANIMANAGER->addCoordinateFrameAnimation("batLeftMove", "batMoveDie", 7, 12, 10, false, true);
	//오른쪽 죽음
	int rightDie[] = { 6 };
	KEYANIMANAGER->addArrayFrameAnimation("batRightDie", "batMoveDie", rightDie, 1, 6, false);
	//왼쪽 죽음
	int leftDie[] = { 13 };
	KEYANIMANAGER->addArrayFrameAnimation("batLeftDie", "batMoveDie", leftDie, 1, 6, false);

	_batMotion = KEYANIMANAGER->findAnimation("batRightMove");
	_batMotion->start();

	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

	//작보박 체력바 초기화
	_progressBar = new progressBar;
	_progressBar->init(_x - 20, _y + 30, 70 , 10, "작보박앞", "작보박뒤", BAR_MONSTER);
	_currentHP = _maxHP = 100;

	randNum = RND->getInt(8);
	

	return S_OK;
}

void Bat::release()
{
}

void Bat::update()
{
	//체력바 업데이트
	_progressBar->setX(_x - 20);
	_progressBar->setY(_y + 30);
	_progressBar->setGauge(_currentHP, _maxHP);
	_progressBar->update();

	move();

	///////////////////DIE테스트////////////////////
	if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		if (_batDirection == BAT_RIGHT_MOVE)
		{
			changeAnimation(BAT_RIGHT_DIE);
		}
		if (_batDirection == BAT_LEFT_MOVE)
		{
			changeAnimation(BAT_LEFT_DIE);
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_F3))
	{
		if (_batDirection == BAT_RIGHT_DIE)
		{
			changeAnimation(BAT_RIGHT_MOVE);
		}
		if (_batDirection == BAT_LEFT_DIE)
		{
			changeAnimation(BAT_LEFT_MOVE);
		}
	}
	///////////////////▲▲▲▲▲▲▲▲////////////////////
	//KEYANIMANAGER->update();
	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
}

void Bat::render()
{
	_progressBar->render();
	_img->aniRender(DC, _rc.left, _rc.top, _batMotion);
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(DC, rcCollision.left, rcCollision.top, rcCollision.right, rcCollision.bottom);
	}
}

void Bat::move()
{
	_moveCount++;

	int tileIndex[2];
	int tileX = _x / TILESIZE, tileY = _y / TILESIZE;

	if (!(_moveCount % 100))
	{
		randNum = RND->getInt(8);
		_moveCount = 0;
	}

	if (randNum == 0) _batDirection = BAT_RIGHT_MOVE;
	if (randNum == 1) _batDirection = BAT_LEFT_MOVE;
	if (randNum == 2) _batDirection = BAT_RIGHT_UP_MOVE;
	if (randNum == 3) _batDirection = BAT_LEFT_UP_MOVE;
	if (randNum == 4) _batDirection = BAT_RIGHT_DOWN_MOVE;
	if (randNum == 5) _batDirection = BAT_LEFT_DOWN_MOVE;
	if (randNum == 6) _batDirection = BAT_UP_MOVE;
	if (randNum == 7) _batDirection = BAT_DOWN_MOVE;

	switch (_batDirection)
	{
	case BAT_RIGHT_MOVE:
		tileIndex[0] = (tileX + 1) + tileY * VARIABLE_SIZEX[_dungeonNum];
		tileIndex[1] = (tileX + VARIABLE_SIZEX[_dungeonNum])  + tileY * VARIABLE_SIZEX[_dungeonNum];
		rcCollision = RectMake(_rc.right, _rc.top, 4, 80);	
		break;
	case BAT_LEFT_MOVE:
		tileIndex[0] = tileX + tileY * VARIABLE_SIZEX[_dungeonNum];
		tileIndex[1] = tileX + (tileY + 1) * VARIABLE_SIZEX[_dungeonNum];
		rcCollision = RectMake(_rc.left - 4, _rc.top + 4, 4, 80);
		break;
	case BAT_RIGHT_UP_MOVE:
		tileIndex[0] = tileX + tileY * VARIABLE_SIZEX[_dungeonNum];
		tileIndex[1] = (tileX + 1) + (tileY - 1) * VARIABLE_SIZEX[_dungeonNum];
		rcCollision = RectMake(_rc.right + 5, _rc.top - 10, 30, 30);
		break;
	case BAT_LEFT_UP_MOVE:
		tileIndex[0] = tileX + tileY * VARIABLE_SIZEX[_dungeonNum];
		tileIndex[1] = (tileX - 1) + (tileY - 1) * VARIABLE_SIZEX[_dungeonNum];
		rcCollision = RectMake(_rc.left - 10, _rc.top - 10, 30, 30);
		break;
	case BAT_RIGHT_DOWN_MOVE:
		tileIndex[0] = tileX + tileY * VARIABLE_SIZEX[_dungeonNum];
		tileIndex[1] = (tileX + 1) + (tileY + 1) * VARIABLE_SIZEX[_dungeonNum];
		rcCollision = RectMake(_rc.right + 10, _rc.bottom + 10, 30, 30);
		break;
	case BAT_LEFT_DOWN_MOVE:
		tileIndex[0] = tileX + tileY * VARIABLE_SIZEX[_dungeonNum];
		tileIndex[1] = tileX + (tileY + 1) * VARIABLE_SIZEX[_dungeonNum];
		rcCollision = RectMake(_rc.left - 10, _rc.bottom + 10, 30, 30);
		break;
	case BAT_UP_MOVE:
		tileIndex[0] = tileX + tileY * VARIABLE_SIZEX[_dungeonNum];
		tileIndex[1] = (tileX + 1) + tileY * VARIABLE_SIZEX[_dungeonNum];
		rcCollision = RectMake(_rc.left + 10, _rc.top - 4, 150, 4);
		break;
	case BAT_DOWN_MOVE:
		tileIndex[0] = tileX + (tileY + 1) * VARIABLE_SIZEX[_dungeonNum];
		tileIndex[1] = (tileX + 1) + (tileY + 1) * VARIABLE_SIZEX[_dungeonNum];
		rcCollision = RectMake(_rc.left + 4, _rc.bottom, 150, 4);
		break;
	}

	RECT temp;
	for (int i = 0; i < 2; i++)
	{
		if (IntersectRect(&temp, &rcCollision, &_tiles[tileIndex[i]].rc) && _tiles[tileIndex[i]].object != OBJ_NONE)//(_tiles[tileIndex[i]].object == OBJ_GROUND || _tiles[tileIndex[i]].object == OBJ_CEILING))
		{
			return;
		}
	}

	switch (_batDirection)
	{
	case BAT_RIGHT_MOVE:
		_x += SPEED;
		break;
	case BAT_LEFT_MOVE:
		_x -= SPEED;
		break;
	case BAT_RIGHT_UP_MOVE:
		_x += SPEED;
		_y -= SPEED;
		break;
	case BAT_LEFT_UP_MOVE:
		_x -= SPEED;
		_y -= SPEED;
		break;
	case BAT_RIGHT_DOWN_MOVE:
		_x += SPEED;
		_y += SPEED;
		break;
	case BAT_LEFT_DOWN_MOVE:
		_x -= SPEED;
		_y += SPEED;
		break;
	case BAT_UP_MOVE:
		_y -= SPEED;
		break;
	case BAT_DOWN_MOVE:
		_y += SPEED;
		break;
	}

	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
}

void Bat::changeAnimation(BATDIRECTION direction)
{
	switch (direction)
	{
	case BAT_RIGHT_MOVE:
		_img = IMAGEMANAGER->findImage("batMoveDie");
		_batDirection = BAT_RIGHT_MOVE;
		_batMotion = KEYANIMANAGER->findAnimation("batRightMove");
		_batMotion->start();
		break;
	case BAT_LEFT_MOVE:
		_img = IMAGEMANAGER->findImage("batMoveDie");
		_batDirection = BAT_LEFT_MOVE;
		_batMotion = KEYANIMANAGER->findAnimation("batLeftMove");
		_batMotion->start();
		break;
	case BAT_RIGHT_UP_MOVE:
		_img = IMAGEMANAGER->findImage("batMoveDie");
		_batDirection = BAT_RIGHT_UP_MOVE;
		_batMotion = KEYANIMANAGER->findAnimation("batRightMove");
		_batMotion->start();
		break;
	case BAT_LEFT_UP_MOVE:
		_img = IMAGEMANAGER->findImage("batMoveDie");
		_batDirection = BAT_LEFT_UP_MOVE;
		_batMotion = KEYANIMANAGER->findAnimation("batLeftMove");
		_batMotion->start();
		break;
	case BAT_RIGHT_DOWN_MOVE:
		_img = IMAGEMANAGER->findImage("batMoveDie");
		_batDirection = BAT_RIGHT_DOWN_MOVE;
		_batMotion = KEYANIMANAGER->findAnimation("batRightMove");
		_batMotion->start();
		break;
	case BAT_LEFT_DOWN_MOVE:
		_img = IMAGEMANAGER->findImage("batMoveDie");
		_batDirection = BAT_LEFT_DOWN_MOVE;
		_batMotion = KEYANIMANAGER->findAnimation("batLeftMove");
		_batMotion->start();
		break;
	case BAT_RIGHT_DIE:
		_img = IMAGEMANAGER->findImage("batMoveDie");
		_batDirection = BAT_LEFT_DIE;
		_batMotion = KEYANIMANAGER->findAnimation("batRightDie");
		_batMotion->start();
		break;
	case BAT_LEFT_DIE:
		_img = IMAGEMANAGER->findImage("batMoveDie");
		_batDirection = BAT_LEFT_DIE;
		_batMotion = KEYANIMANAGER->findAnimation("batLeftDie");
		_batMotion->start();
		break;
	}
}

void Bat::rightMove()
{
	//방향 전환
	_count++;
	if (_count % 10 == 0)
	{
		_angle -= PI2 / 36;
		
		_count = 0;
	}

	_x = cosf(_angle)*_speed + _startX;
	_y = -sin(_angle)*_speed + _startY;

	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

}

void Bat::leftMove()
{
	//방향 전환
	_count++;
	if (_count % 10 == 0)
	{
		_angle += PI2 / 36;

		_count = 0;
	}

	_x = cosf(_angle)*_speed + _startX;
	_y = -sin(_angle)*_speed + _startY;

	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

}

void Bat::playerCollision()
{
	
}

void Bat::hitDamage(float damage)
{
	_currentHP -= damage;
}


void Bat::tileDetection()
{
	int tileX = _x / TILESIZE, tileY = _y / TILESIZE;


}
