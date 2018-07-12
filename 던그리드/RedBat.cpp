#include "stdafx.h"
#include "RedBat.h"


RedBat::RedBat()
{
}


RedBat::~RedBat()
{
}

HRESULT RedBat::init(float x, float y)
{
	//_x = WINSIZEX / 2;
	//_y = 200;
	_x = x;
	_y = y;
	_startX = x;
	_startY = y;
	_angle = 0;
	_speed = 300.0f;

	_redBatDirection = REDBAT_LEFT_MOVE;

	_img = IMAGEMANAGER->findImage("redBatMoveAttackDie");
	
	//Move
	KEYANIMANAGER->addCoordinateFrameAnimation("redBatRightMove", "redBatMoveAttackDie", 0, 7, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("redBatLeftMove", "redBatMoveAttackDie", 8, 15, 10, false, true);
	//Attack
	KEYANIMANAGER->addCoordinateFrameAnimation("redBatRightAttack", "redBatMoveAttackDie", 16, 23, 10, false, false, rightAttack, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("redBatLeftAttack", "redBatMoveAttackDie", 24, 31, 10, false, false , leftAttack, this);
	//Die
	int rightDie[] = { 32 };
	KEYANIMANAGER->addArrayFrameAnimation("redBatRightDie", "redBatMoveAttackDie", rightDie, 1, 6, false);
	int leftDie[] = { 33 };
	KEYANIMANAGER->addArrayFrameAnimation("redBatLeftDie", "redBatMoveAttackDie", leftDie, 1, 6, false);

	_redBatMotion = KEYANIMANAGER->findAnimation("redBatLeftMove");
	_redBatMotion->start();

	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

	//�ۻ��� ü�� �ʱ�ȭ
	_progressBar = new progressBar;
	_progressBar->init(_x - 30, _y + 20, 70, 10, "�ۻ��ھ�", "�ۺ��ڵ�", BAR_MONSTER);
	_currentHP = _maxHP = 100;

	return S_OK;
}

void RedBat::release()
{
}

void RedBat::update()
{
	//�ۻ��� ü�� ������Ʈ
	_progressBar->setX(_x - 30);
	_progressBar->setY(_y + 20);
	_progressBar->setGauge(_currentHP, _maxHP);
	_progressBar->update();

	_count++;

	move();
	Attack();
	//KEYANIMANAGER->update();
	
	/////////////////////////�׽�Ʈ/////////////////////////////
	//�״¸��
	if (KEYMANAGER->isOnceKeyDown(VK_F4))
	{
		if (_redBatDirection == REDBAT_RIGHT_MOVE)
		{
			changeAnimation(REDBAT_RIGHT_DIE);
		}
		if (_redBatDirection == REDBAT_LEFT_MOVE)
		{
			changeAnimation(REDBAT_LEFT_DIE);
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_F4))
	{
		if (_redBatDirection == REDBAT_RIGHT_DIE)
		{
			changeAnimation(REDBAT_RIGHT_MOVE);
		}
		if (_redBatDirection == REDBAT_LEFT_DIE)
		{
			changeAnimation(REDBAT_LEFT_MOVE);
		}
	}

	////////////////////////�������//////////////////////////////

}

void RedBat::render()
{
	_img->aniRender(DC, _rc.left, _rc.top, _redBatMotion);
	_progressBar->render();
	if (KEYMANAGER->isToggleKey('B'))
	{
		Rectangle(DC, _rc.left, _rc.top, _rc.right, _rc.bottom);
	}
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(DC, rcCollision.left, rcCollision.top, rcCollision.right, rcCollision.bottom);
	}
}

void RedBat::move()
{

	_moveCount++;

	int tileIndex[2];
	int tileX = _x / TILESIZE, tileY = _y / TILESIZE;

	if (!(_moveCount % 100))
	{
		randNum = RND->getInt(8);
		_moveCount = 0;
	}

	if (randNum == 0) _redBatDirection = REDBAT_RIGHT_MOVE;
	if (randNum == 1) _redBatDirection = REDBAT_LEFT_MOVE;
	if (randNum == 2) _redBatDirection = REDBAT_RIGHT_UP_MOVE;
	if (randNum == 3) _redBatDirection = REDBAT_LEFT_UP_MOVE;
	if (randNum == 4) _redBatDirection = REDBAT_RIGHT_DOWN_MOVE;
	if (randNum == 5) _redBatDirection = REDBAT_LEFT_DOWN_MOVE;
	if (randNum == 6) _redBatDirection = REDBAT_UP_MOVE;
	if (randNum == 7) _redBatDirection = REDBAT_DOWN_MOVE;

	switch (_redBatDirection)
	{
	case REDBAT_RIGHT_MOVE:
		tileIndex[0] = (tileX + 1) + tileY * VARIABLE_SIZEX[_dungeonNum];
		tileIndex[1] = (tileX + VARIABLE_SIZEX[_dungeonNum]) + tileY * VARIABLE_SIZEX[_dungeonNum];
		rcCollision = RectMake(_rc.right, _rc.top, 4, 80);
		break;
	case REDBAT_LEFT_MOVE:
		tileIndex[0] = tileX + tileY * VARIABLE_SIZEX[_dungeonNum];
		tileIndex[1] = tileX + (tileY + 1) * VARIABLE_SIZEX[_dungeonNum];
		rcCollision = RectMake(_rc.left - 4, _rc.top + 4, 4, 80);
		break;
	case REDBAT_RIGHT_UP_MOVE:
		tileIndex[0] = tileX + tileY * VARIABLE_SIZEX[_dungeonNum];
		tileIndex[1] = (tileX + 1) + (tileY - 1) * VARIABLE_SIZEX[_dungeonNum];
		rcCollision = RectMake(_rc.right + 5, _rc.top - 10, 30, 30);
		break;
	case REDBAT_LEFT_UP_MOVE:
		tileIndex[0] = tileX + tileY * VARIABLE_SIZEX[_dungeonNum];
		tileIndex[1] = (tileX - 1) + (tileY - 1) * VARIABLE_SIZEX[_dungeonNum];
		rcCollision = RectMake(_rc.left - 10, _rc.top - 10, 30, 30);
		break;
	case REDBAT_RIGHT_DOWN_MOVE:
		tileIndex[0] = tileX + tileY * VARIABLE_SIZEX[_dungeonNum];
		tileIndex[1] = (tileX + 1) + (tileY + 1) * VARIABLE_SIZEX[_dungeonNum];
		rcCollision = RectMake(_rc.right + 10, _rc.bottom + 10, 30, 30);
		break;
	case REDBAT_LEFT_DOWN_MOVE:
		tileIndex[0] = tileX + tileY * VARIABLE_SIZEX[_dungeonNum];
		tileIndex[1] = tileX + (tileY + 1) * VARIABLE_SIZEX[_dungeonNum];
		rcCollision = RectMake(_rc.left - 10, _rc.bottom + 10, 30, 30);
		break;
	case REDBAT_UP_MOVE:
		tileIndex[0] = tileX + tileY * VARIABLE_SIZEX[_dungeonNum];
		tileIndex[1] = (tileX + 1) + tileY * VARIABLE_SIZEX[_dungeonNum];
		rcCollision = RectMake(_rc.left + 10, _rc.top - 4, 150, 4);
		break;
	case REDBAT_DOWN_MOVE:
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

	switch (_redBatDirection)
	{
	case REDBAT_RIGHT_MOVE:
		_x += SPEED;
		break;
	case REDBAT_LEFT_MOVE:
		_x -= SPEED;
		break;
	case REDBAT_RIGHT_UP_MOVE:
		_x += SPEED;
		_y -= SPEED;
		break;
	case REDBAT_LEFT_UP_MOVE:
		_x -= SPEED;
		_y -= SPEED;
		break;
	case REDBAT_RIGHT_DOWN_MOVE:
		_x += SPEED;
		_y += SPEED;
		break;
	case REDBAT_LEFT_DOWN_MOVE:
		_x -= SPEED;
		_y += SPEED;
		break;
	case REDBAT_UP_MOVE:
		_y -= SPEED;
		break;
	case REDBAT_DOWN_MOVE:
		_y += SPEED;
		break;
	}

	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
}

void RedBat::rightMove()
{
	if (_count % 10 == 0)
	{
		_angle -= PI2 / 36;
	
	}

	_x = cosf(_angle)*_speed + _startX;
	_y = -sin(_angle)*_speed + _startY;

	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
}

void RedBat::leftMove()
{
	if (_count % 10 == 0)
	{
		_angle += PI2 / 36;

	}

	_x = cosf(_angle)*_speed + _startX;
	_y = -sinf(_angle)*_speed + _startY;

	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
}

void RedBat::Attack()
{
	if (!(_count % 141))
	{
		if (_redBatDirection == REDBAT_RIGHT_MOVE)
			changeAnimation(REDBAT_RIGHT_ATTACK);
		if (_redBatDirection == REDBAT_LEFT_MOVE)
			changeAnimation(REDBAT_LEFT_ATTACK);
		_isAtteck = true;
		_count = 0;
	}
}


void RedBat::changeAnimation(REDBATDIRECTION direction)
{
	switch (direction)
	{
	case REDBAT_RIGHT_MOVE:
		_img = IMAGEMANAGER->findImage("redBatMoveAttackDie");
		_redBatDirection = REDBAT_RIGHT_MOVE;
		_redBatMotion = KEYANIMANAGER->findAnimation("redBatRightMove");
		_redBatMotion->start();
		break;
	case REDBAT_LEFT_MOVE:
		_img = IMAGEMANAGER->findImage("redBatMoveAttackDie");
		_redBatDirection = REDBAT_LEFT_MOVE;
		_redBatMotion = KEYANIMANAGER->findAnimation("redBatLeftMove");
		_redBatMotion->start();
		break;
	case REDBAT_RIGHT_ATTACK:
		_img = IMAGEMANAGER->findImage("redBatMoveAttackDie");
		_redBatDirection = REDBAT_RIGHT_ATTACK;
		_redBatMotion = KEYANIMANAGER->findAnimation("redBatRightAttack");
		_redBatMotion->start();
		break;
	case REDBAT_LEFT_ATTACK:
		_img = IMAGEMANAGER->findImage("redBatMoveAttackDie");
		_redBatDirection = REDBAT_LEFT_ATTACK;
		_redBatMotion = KEYANIMANAGER->findAnimation("redBatLeftAttack");
		_redBatMotion->start();
		break;
	case REDBAT_RIGHT_DIE:
		_img = IMAGEMANAGER->findImage("redBatMoveAttackDie");
		_redBatDirection = REDBAT_RIGHT_DIE;
		_redBatMotion = KEYANIMANAGER->findAnimation("redBatRightDie");
		_redBatMotion->start();
		break;
	case REDBAT_LEFT_DIE:
		_img = IMAGEMANAGER->findImage("redBatMoveAttackDie");
		_redBatDirection = REDBAT_LEFT_DIE;
		_redBatMotion = KEYANIMANAGER->findAnimation("redBatLeftDie");
		_redBatMotion->start();
		break;
	}
}

void RedBat::rightAttack(void * obj)
{
	RedBat* rb = (RedBat*)obj;

	rb->_img = IMAGEMANAGER->findImage("redBatMoveAttackDie");
	rb->setRedBatDirection(REDBAT_RIGHT_MOVE);
	rb->setRedBatMotion(KEYANIMANAGER->findAnimation("redBatRightMove"));
	rb->getRedBatMotion()->start();
}
void RedBat::leftAttack(void * obj)
{
	RedBat* rb = (RedBat*)obj;

	rb->_img = IMAGEMANAGER->findImage("redBatMoveAttackDie");
	rb->setRedBatDirection(REDBAT_LEFT_MOVE);
	rb->setRedBatMotion(KEYANIMANAGER->findAnimation("redBatLeftMove"));
	rb->getRedBatMotion()->start();
}

void RedBat::playerCollision()
{
}

void RedBat::hitDamage(float damage)
{
	_currentHP -= damage;
}
