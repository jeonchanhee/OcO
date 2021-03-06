#include "stdafx.h"
#include "Cow.h"
#include "Player.h"

Cow::Cow()
{
}


Cow::~Cow()
{
}

HRESULT Cow::init(float x, float y)
{
	static int a = 0;
	a += 1;
	_index = a;

	_hit = false;
	_x = x;
	_y = y;

	_img = IMAGEMANAGER->findImage("cowIdleChargeAttack");
	//_cowDirection = COW_LEFT_MOVE;
	_cowDirection = COW_RIGHT_MOVE;

	//MOVE
	KEYANIMANAGER->addCoordinateFrameAnimation("cowRightMove", "cowIdleChargeAttack", 0, 5, 5, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("cowLeftMove", "cowIdleChargeAttack", 8, 13, 5, false, true);

	//CHARGE
	char str[50];
	sprintf_s(str, "cowRightCharge%d", _index);
	KEYANIMANAGER->addCoordinateFrameAnimation(str, "cowIdleChargeAttack", 16, 23, 5, false, false, rightCharge, this);
	sprintf_s(str, "cowLeftCharge%d", _index);
	KEYANIMANAGER->addCoordinateFrameAnimation(str, "cowIdleChargeAttack", 24, 31, 5, false, false, leftCharge, this);

	//ATTACK
	sprintf_s(str, "cowRightAttack%d", _index);
	KEYANIMANAGER->addCoordinateFrameAnimation(str, "cowIdleChargeAttack", 32, 38, 5, false, false, rightAttack, this);
	sprintf_s(str, "cowLeftAttack%d", _index);
	KEYANIMANAGER->addCoordinateFrameAnimation(str, "cowIdleChargeAttack", 40, 46, 5, false, false, leftAttack, this);

	//DIE
	//KEYANIMANAGER->addCoordinateFrameAnimation("cowDie", "dieEffect", 2, 10, 5, false, false);
	int cowDie[] = { 47};
	sprintf_s(str, "cowDie%d", _index);
	KEYANIMANAGER->addArrayFrameAnimation(str, "cowIdleChargeAttack", cowDie, 1, 5, false, dieMotion,this);

	//_cowMotion = KEYANIMANAGER->findAnimation("cowLeftMove");
	_cowMotion = KEYANIMANAGER->findAnimation("cowRightMove");
	_cowMotion->start();

	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

	//소 체력바 초기화
	_progressBar = new progressBar;
	_progressBar->init(_x - 70, _y + 110, 70, 10, "소앞", "소뒤", BAR_MONSTER);
	_currentHP = _maxHP = 100;

	_isDie = false;
	
	return S_OK;
}

void Cow::release()
{
}

void Cow::update()
{
	//소 체력바 
	_progressBar->setX(_x - 70);
	_progressBar->setY(_y + 110);
	_progressBar->setGauge(_currentHP, _maxHP);
	_progressBar->update();

	_count++;
	if (!(_count % 250) && !_diedie)
	{
		if (_cowDirection == COW_RIGHT_MOVE)
			changeAnimation(COW_RIGHT_CHARGE);
		if (_cowDirection == COW_LEFT_MOVE)
			changeAnimation(COW_LEFT_CHARGE);
	}
	if (!(_count % 300) && !_diedie)
	{
		if (_cowDirection == COW_RIGHT_MOVE)
			changeAnimation(COW_RIGHT_ATTACK);
		if (_cowDirection == COW_LEFT_MOVE)
			changeAnimation(COW_LEFT_ATTACK);
	}

	move();
	changeDirection();
	playerCollision();
	hitDamage();

	if (_diedie)
	{
		_dieCount++;
		if (_dieCount > 120)
		{
			_isDie = true;
		}
	}

	///////////////////////DIE 테스트///////////////////////////
	if (KEYMANAGER->isOnceKeyDown(VK_F8))
	{
		if (_cowDirection == COW_RIGHT_MOVE || _cowDirection == COW_LEFT_MOVE)
			changeAnimation(COW_DIE);
	}
	/*if (KEYMANAGER->isOnceKeyUp(VK_F8))
	{
		if (_cowDirection == COW_DIE)
			changeAnimation(COW_RIGHT_MOVE);
	}*/
	///////////////////////▲▲▲▲▲▲▲▲▲///////////////////////////

	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
}

void Cow::render()
{
	if (KEYMANAGER->isToggleKey('C'))
	{
		Rectangle(DC, _rc.left, _rc.top, _rc.right, _rc.bottom);
	}
	_img->aniRender(DC, _rc.left, _rc.top, _cowMotion);
	_progressBar->render();
}

void Cow::move()
{
	if (_diedie) return;
	RECT rcCollision;

	int tileIndex[2];
	int tileX, tileY;
	rcCollision = _rc;

	switch (_cowDirection)
	{
	case COW_RIGHT_CHARGE:
		_x += COWSPEED;
		rcCollision = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	case COW_LEFT_CHARGE:
		_x -= COWSPEED;
		rcCollision = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	default:
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

	switch (_cowDirection)
	{
	case COW_RIGHT_CHARGE:
		tileIndex[0] = (tileX + tileY * VARIABLE_SIZEX[_dungeonNum]) + 2;
		tileIndex[1] = (tileX + (1 + tileY) *  VARIABLE_SIZEX[_dungeonNum]) + 2;
		break;
	case COW_LEFT_CHARGE:
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
			switch (_cowDirection)
			{
			case COW_RIGHT_CHARGE: 
				_rc.right = _tiles[tileIndex[i]].rc.left;
				_rc.left = _rc.right - 230;
				_x = _rc.left + (_rc.right - _rc.left) / 2;
				changeAnimation(COW_LEFT_MOVE);
				break;
			case COW_LEFT_CHARGE:
				_rc.left = _tiles[tileIndex[i]].rc.right;
				_rc.right = _rc.left + 230;
				_x = _rc.left + (_rc.right - _rc.left) / 2;
				changeAnimation(COW_RIGHT_MOVE);
				break;
			}
			return;
		}
	}
	rcCollision = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
	_rc = rcCollision;
}

void Cow::changeDirection()
{
	//if (_cowDirection == COW_RIGHT_CHARGE)
	//	_x += COWSPEED;
	//if (_cowDirection == COW_LEFT_CHARGE)
	//	_x -= COWSPEED;

	//방향 전환
	//if (_x <= 255)
	//{
	//	_x = 260;
	//	changeAnimation(COW_RIGHT_MOVE);
	//	//_x += COWSPEED;
	//}
	//if (_x >= WINSIZEX - _img->getFrameWidth())
	//{
	//	_x = WINSIZEX - _img->getFrameWidth() - 5;
	//	changeAnimation(COW_LEFT_MOVE);
	//}
}

void Cow::rightCharge(void * obj)
{
	Cow* c = (Cow*)obj;

	c->_img = IMAGEMANAGER->findImage("cowIdleChargeAttack");
	if (_dungeonNum == 6)
	{
		c->setCowDirection(COW_LEFT_MOVE);
		c->setCowMotion(KEYANIMANAGER->findAnimation("cowLeftMove"));
	}
	else
	{
		c->setCowDirection(COW_RIGHT_MOVE);
		c->setCowMotion(KEYANIMANAGER->findAnimation("cowRightMove"));
	}
	c->getCowMotion()->start();
}

void Cow::leftCharge(void * obj)
{
	Cow* c = (Cow*)obj;
	if (c->_diedie) return;
	c->_img = IMAGEMANAGER->findImage("cowIdleChargeAttack");
	if (_dungeonNum == 6)
	{
		c->setCowDirection(COW_RIGHT_MOVE);
		c->setCowMotion(KEYANIMANAGER->findAnimation("cowRightMove"));
	}
	else
	{
		c->setCowDirection(COW_LEFT_MOVE);
		c->setCowMotion(KEYANIMANAGER->findAnimation("cowLeftMove"));
	}
	c->getCowMotion()->start();
}

void Cow::rightAttack(void * obj)
{
	Cow* c = (Cow*)obj;
	if (c->_diedie) return;
	c->_img = IMAGEMANAGER->findImage("cowIdleChargeAttack");
	c->setCowDirection(COW_RIGHT_MOVE);
	c->setCowMotion(KEYANIMANAGER->findAnimation("cowRightMove"));
	c->getCowMotion()->start();
}

void Cow::leftAttack(void * obj)
{
	Cow* c = (Cow*)obj;
	if (c->_diedie)return;
	c->_img = IMAGEMANAGER->findImage("cowIdleChargeAttack");
	c->setCowDirection(COW_LEFT_MOVE);
	c->setCowMotion(KEYANIMANAGER->findAnimation("cowLeftMove"));
	c->getCowMotion()->start();

}

void Cow::dieMotion(void* obj)
{
	Cow* c = (Cow*)obj;
	c->_diedie = true;
}

void Cow::changeAnimation(COWDIRECTION cowDirection)
{
	switch (cowDirection)
	{
	case COW_RIGHT_MOVE:
		_img = IMAGEMANAGER->findImage("cowIdleChargeAttack");
		_cowDirection = COW_RIGHT_MOVE;
		_cowMotion->stop();
		_hit = false;
		_cowMotion = KEYANIMANAGER->findAnimation("cowRightMove");
		_cowMotion->start();
		_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	case COW_LEFT_MOVE:
		_img = IMAGEMANAGER->findImage("cowIdleChargeAttack");
		_cowDirection = COW_LEFT_MOVE;
		_cowMotion->stop();
		_hit = false;
		_cowMotion = KEYANIMANAGER->findAnimation("cowLeftMove");
		_cowMotion->start();
		_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	case COW_RIGHT_CHARGE:
		_img = IMAGEMANAGER->findImage("cowIdleChargeAttack");
		_cowDirection = COW_RIGHT_CHARGE;
		_cowMotion->stop();
		_hit = false;
		char str[50];
		sprintf_s(str, "cowRightCharge%d", _index);
		_cowMotion = KEYANIMANAGER->findAnimation(str);
		_cowMotion->start();
		_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	case COW_LEFT_CHARGE:
		_img = IMAGEMANAGER->findImage("cowIdleChargeAttack");
		_cowDirection = COW_LEFT_CHARGE;
		_cowMotion->stop();
		_hit = false;
		sprintf_s(str, "cowLeftCharge%d", _index);
		_cowMotion = KEYANIMANAGER->findAnimation(str);
		_cowMotion->start();
		_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	case COW_RIGHT_ATTACK:
		_img = IMAGEMANAGER->findImage("cowIdleChargeAttack");
		_cowDirection = COW_RIGHT_ATTACK;
		_cowMotion->stop();
		_hit = false;
		sprintf_s(str, "cowRightAttack%d", _index);
		_cowMotion = KEYANIMANAGER->findAnimation(str);
		_cowMotion->start();
		_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	case COW_LEFT_ATTACK:
		_img = IMAGEMANAGER->findImage("cowIdleChargeAttack");
		_cowDirection = COW_LEFT_ATTACK;
		_cowMotion->stop();
		_hit = false;
		sprintf_s(str, "cowLeftAttack%d", _index);
		_cowMotion = KEYANIMANAGER->findAnimation(str);
		_cowMotion->start();
		_rc = RectMakeCenter(_x,_y,_img->getFrameWidth(),_img->getFrameHeight());
		break;
	case COW_DIE:
		_img = IMAGEMANAGER->findImage("cowIdleChargeAttack");
		_cowDirection = COW_DIE;
		_cowMotion->stop();
		sprintf_s(str, "cowDie%d", _index);
		_cowMotion = KEYANIMANAGER->findAnimation(str);
		_cowMotion->start();
		_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	default:
		break;
	}
}

void Cow::playerCollision()
{
	RECT temp;

	if (IntersectRect(&temp, &_rc, &_player->getPlayerRect()))
	{
		if (!_hit)
		{
			_player->hitDamage(3);
			EFFECTMANAGER->play("bossCollisionBullet", (_player->getPlayerRect().right + _player->getPlayerRect().left) / 2, (_player->getPlayerRect().bottom + _player->getPlayerRect().top) / 2);
			_hit = true;
		}
	}
}

void Cow::hitDamage()
{
	if (_currentHP <= 0)
	{
		changeAnimation(COW_DIE);
	}
}
