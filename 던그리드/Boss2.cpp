#include "stdafx.h"
#include "Boss2.h"
#include "Player.h"

Boss2::Boss2()
{
}


Boss2::~Boss2()
{
}

HRESULT Boss2::init()
{	
	//칼새끼 초기호ㅏ
	for (int i = 0; i < 5; i++)
	{
		_sword[i].img = new image;
		_sword[i].img->init("image/enemy/sword(126x390,1x1).bmp", 126, 390, true, RGB(255, 0, 255));
		_sword[i].x = 400 + i * 300;
		_sword[i].y = 300;
		_sword[i].count = 0;
		_sword[i].isShoot = _sword[i].isAppear = false;
		_sword[i].rc = RectMakeCenter(_sword[i].x, _sword[i].y, _sword[i].img->getWidth(), _sword[i].img->getHeight());
	}
	//_isShoot = false;
	_hit = false;
	_swordCount = 0;
	////////////////////////////////////////////////////////////////////////
	// 보스 대갈 손들 초기화
	_boss[0].img = IMAGEMANAGER->findImage("bossHand");
	_boss[1].img = IMAGEMANAGER->findImage("bossIdleAttackDie");
	_boss[2].img = IMAGEMANAGER->findImage("bossHand");
	//_boss[3].img = IMAGEMANAGER->findImage("bossSword");

	for (int i = 0; i < 3; i++) 
	{
		_boss[i].x = WINSIZEX / 4 + (i * WINSIZEX / 4);
		_boss[i].y = WINSIZEY / 2 + 400;
		_boss[2].y = WINSIZEY / 2 + 395;

		_boss[i].rc = RectMakeCenter(_boss[i].x, _boss[i].y, _boss[i].img->getFrameWidth(), _boss[i].img->getFrameHeight());
	}

	_bossLeftDirection = LEFT_IDLE;
	_bossHeadDirection = HEAD_IDLE;
	_bossRightDirection = RIGHT_IDLE;

	//=======LEFT (IDLE,MOVE,LASER)========
	KEYANIMANAGER->addCoordinateFrameAnimation("leftIdle", "bossHand", 10, 19, 5, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("leftUpMove", "bossHand", 10, 19, 5, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("leftDownMove", "bossHand", 10, 19, 5, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("leftLaser", "bossHand", 30, 39, 5, false, false, CBleftAttack, this);

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
	KEYANIMANAGER->addCoordinateFrameAnimation("rightIdle", "bossHand", 0, 9, 5, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("rightUpMove", "bossHand", 0, 9, 5, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("rightDownMove", "bossHand", 0, 9, 5, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("rightLaser", "bossHand", 20, 29, 5, false, false, CBrightAttack, this);

	_bossMotion[2] = KEYANIMANAGER->findAnimation("rightIdle");
	_bossMotion[2]->start();
	x = (_boss[1].rc.right + _boss[1].rc.left) / 2;
	y = (_boss[1].rc.bottom + _boss[1].rc.top) / 2;

	_count2 = _count3 = 0;

	//보스 체력바 초기화
	_progressBar = new progressBar;
	//_progressBar->init(500, WINSIZEY - 100, 1000, 100, "보스앞", "보스뒤", BAR_BOSS);
	_progressBar->init(500, WINSIZEY - 120, 1000, 100, "보스앞", "보스뒤", BAR_BOSS);
	_currentHP = _maxHP = 100;

	return S_OK;
}

void Boss2::release()
{
}

void Boss2::update()
{
	//보스 체력바 업데이트
	_progressBar->setX(500);
	_progressBar->setY(WINSIZEY - 120);
	_progressBar->setGauge(_currentHP, _maxHP);
	_progressBar->update();
	
	///////////////HEAD DIE TEST/////////////////
	if (KEYMANAGER->isOnceKeyDown(VK_F9))
	{
		if (_bossHeadDirection == HEAD_IDLE || _bossHeadDirection == HEAD_ATTACK)
		{
			changeHeadDirection(HEAD_DIE);
		}	
	}
	if (_bossHeadDirection == HEAD_DIE)
	{
		if (_boss[1].y < 1000) _boss[1].y += BOSSSPEED;
	}
	/*if (KEYMANAGER->isOnceKeyUp(VK_F9))
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
	rightMove();

	fireSword();
	shootSword();

	//playerCollision();

	//KEYANIMANAGER->update();
	for (int i = 0; i < 3; i++)
		_boss[i].rc = RectMakeCenter(_boss[i].x, _boss[i].y, _boss[i].img->getFrameWidth(), _boss[i].img->getFrameHeight());
	//for(int i= 0;i<5;i++)
	//	_sword[i].rc = RectMakeCenter(_sword[i].x, _sword[i].y, _sword[i].img->getFrameWidth(), _sword[i].img->getFrameHeight());
	
}

void Boss2::render()
{
	if (KEYMANAGER->isToggleKey('X'))
	{
		//Rectangle(DC, _boss[1].rc.left, _boss[1].rc.top, _boss[1].rc.right, _boss[1].rc.bottom);
	}

	_progressBar->render();

	for (int i = 0; i < 3; i++)
	{
		//_boss[i].img->aniRender(DC, _boss[i].rc.left, _boss[i].rc.top, _bossMotion[i]);
		_boss[i].img->aniRender(DC, _boss[i].rc.left, _boss[i].rc.top, _bossMotion[i]);
	}
	POINT temp = PointMake(-1, -1);
	for (int i = 0; i < 5; i++)
	{
		if (_sword[i].isAppear)
		{
			if (_sword[i].isShoot)
			{
				_sword[i].img->rotateRender(DC, _sword[i].rc.left, _sword[i].rc.top, _sword[i].angle);
			//	temp = _sword[i].img->getRotateCenter();
			//	_sword[i].collisionRC = RectMakeCenter(temp.x, temp.y, 70, 70);
			}
			else
				_sword[i].img->render(DC, _sword[i].rc.left, _sword[i].rc.top);
		}
	}

	//Rectangle(DC, _boss[1].rc.left, _boss[1].rc.top, _boss[1].rc.right, _boss[1].rc.bottom);
		//RectangleMake(DC, _boss[1].x, _boss[1].y, _boss[1].img->getFrameWidth(), _boss[1].img->getFrameHeight());
	//RectangleMakeCenter(DC, (_boss[1].rc.right + _boss[1].rc.left) / 2, (_boss[1].rc.bottom + _boss[1].rc.top) / 2, 10, 10);
	char str[128];
	//sprintf_s(str, "%f %f", _boss[1].x, _boss[1].y);
	//TextOut(DC, 100, 100, str, strlen(str));
	for (int i = 0; i < 5; i++)
	{
		sprintf_s(str, "%f %f", _sword[i].x, _sword[i].y);
		TextOut(DC, 100, 400 + i*100, str, strlen(str));
	}
	for (int i = 0; i < 5; i++)
	{
		if (KEYMANAGER->isToggleKey('M'))
		{
			if (_sword[i].isShoot)
				Rectangle(DC, _sword[i].collisionRC.left, _sword[i].collisionRC.top, _sword[i].collisionRC.right, _sword[i].collisionRC.bottom);
				//RectangleMake(DC, temp.x, temp.y, 90, 70);
			//Rectangle(DC, _sword[i].rc.left, _sword[i].rc.top, _sword[i].rc.right, _sword[i].rc.bottom);
			
			//RectangleMake(DC, _sword[i].x, _sword[i].y, 10, 10);
		}
	}
}

void Boss2::frameMove()
{
	//for (int i = 0; i < 5; i++)
	//{
	//	if (_isShoot)
	//	{
	//		//오른쪽 방향
	//		if (_sword[i].x < _player->getPlayerX())
	//		{
	//			_sword[i].x += cosf(_angle)*_speed;
	//			_sword[i].y += -sinf(_angle)*_speed;
	//		}
	//		//왼쪽 방향
	//		if (_sword[i].x > _player->getPlayerX())
	//		{
	//			_sword[i].x += cosf(_angle)*_speed;
	//			_sword[i].y += -sinf(_angle)*_speed;
	//		}
	//	}
	//}
}

void Boss2::shootSword()
{
	int cnt = 0;
	for (int i = 0; i < 5; i++)
	{
		if (!_sword[i].isShoot) continue;

		if (_sword[i].x <= _player->getPlayerX())
		{
			_sword[i].x += cosf(_sword[i].angle)*_sword[i].speed;
			_sword[i].y += -sinf(_sword[i].angle)*_sword[i].speed;
			//_sword[i].rcX = _sword[i].x - cosf(_sword[i].angle)*(_sword[i].img->getWidth() / 2);
			//_sword[i].rcY = _sword[i].y + sinf(_sword[i].angle)*(_sword[i].img->getHeight() / 2);
			_sword[i].rcX = _sword[i].x - cosf(_sword[i].angle)*(_sword[i].img->getWidth());
			_sword[i].rcY = _sword[i].y + sinf(_sword[i].angle)*(_sword[i].img->getHeight());
		}
		else if (_sword[i].x > _player->getPlayerX())
		{
			_sword[i].x += cosf(_sword[i].angle)*_sword[i].speed;
			_sword[i].y += -sinf(_sword[i].angle)*_sword[i].speed;
			_sword[i].rcX = _sword[i].x + cosf(_sword[i].angle)*(_sword[i].img->getWidth()) - 80;
			_sword[i].rcY = _sword[i].y - sinf(_sword[i].angle)*(_sword[i].img->getHeight()) - 40;

		}
		//_sword[i].collisionRC = RectMake(_sword[i].rcX, _sword[i].rcY, 30, 30);
		
		if (getDistance(_sword[i].x, _sword[i].y, _sword[i].fireX, _sword[i].fireY) > WINSIZEY)
		{
			//_sword[i].isShoot = false;
			_sword[i].isAppear = false;
			cnt++;
		}
	}
	if (cnt == 5)
	{
		_swordCount = 0;
		for (int i = 0; i < 5; i++)
		//for(int i=0;i<5;i++)
		{
			_sword[i].isShoot = false;
			_sword[i].img->init("image/enemy/sword(126x390,1x1).bmp", 126, 390, true, RGB(255, 0, 255));
			_sword[i].x = 400 + i * 300;
			_sword[i].y = 300;
		}
	}
}

void Boss2::fireSword()
{
	_swordCount++;
	if (_swordCount == 300)
	{
		for (int i = 0; i < 5; i++)
		{
			_sword[i].isAppear = true;
		}
	}

	if (_swordCount > 300 && !(_swordCount % 50))
	{
		for (int i = 0; i < 5; i++)
		{
			if (_sword[i].isShoot) continue;

			_sword[i].isShoot = true;
			_sword[i].img->rotateInit("image/enemy/sword(390x126,1x1).bmp", 390, 126, true, RGB(255, 0, 255));
			_sword[i].speed = 10;
			_sword[i].fireX = _sword[i].x;
			_sword[i].fireY = _sword[i].y;
			_sword[i].angle = getAngle(_sword[i].x, _sword[i].y, _player->getPlayerX(), _player->getPlayerY());
			break;
		}
	}

	for (int i = 0; i < 5; i++)
	{
		_sword[i].rc = RectMakeCenter(_sword[i].x, _sword[i].y, _sword[i].img->getWidth(), _sword[i].img->getHeight());
	}
}

void Boss2::playerCollision()
{
	RECT temp;

	for (int i = 0; i < 5; i++)
	{
		if (IntersectRect(&temp, &_player->getPlayerRect(), &_sword[i].collisionRC))
		{
			if(!_hit)
			{	
				_player->hitDamage(3.0f);
				EFFECTMANAGER->play("bossCollisionBullet", (_player->getPlayerRect().right + _player->getPlayerRect().left) / 2, (_player->getPlayerRect().bottom + _player->getPlayerRect().top) / 2);
				_hit = true;
			}
		}
	}
}

//===============================================================================
//									왼손꾸락
//===============================================================================
//왼손꾸락
void Boss2::leftMove()
{
	//위아래로 움직이다 멈춤
	if (!(_count % 100))
	{
		if (_bossLeftDirection == LEFT_UP_MOVE)
			changeLeftDirection(LEFT_LASER);
		else if (_bossLeftDirection == LEFT_DOWN_MOVE)
			changeLeftDirection(LEFT_LASER);
	}

	//범위지정해서 위아래로 움직임
	if (!(_count % 350))
	{
		if (_bossLeftDirection == LEFT_IDLE)
		{
			//if (_boss[0].y < WINSIZEY / 2)
			if (_boss[0].y < WINSIZEY / 2 + 395)
				changeLeftDirection(LEFT_DOWN_MOVE);
			else
				changeLeftDirection(LEFT_UP_MOVE);
		}
	}

	//위 범위 지정
	if (_boss[0].y < 300)
	{
		changeLeftDirection(LEFT_IDLE);
		_boss[0].y = _boss[0].y;
	}
	//아래 범위 지정
	if (_boss[0].y > WINSIZEY - 100)
	{
		changeLeftDirection(LEFT_IDLE);
		_boss[0].y = WINSIZEY - 100;
	}
	//움직임 속도 지정
	if (_bossLeftDirection == LEFT_DOWN_MOVE)
		_boss[0].y += BOSSSPEED;
	if (_bossLeftDirection == LEFT_UP_MOVE)
		_boss[0].y -= BOSSSPEED;

	if (_bossLeftDirection == LEFT_LASER_OFF)
	{
		_count2 -= 1;
		if (_count2 <= 0) changeLeftDirection(LEFT_IDLE);
	}
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
	case LEFT_UP_MOVE:
		_boss[0].img = IMAGEMANAGER->findImage("bossHand");
		_bossLeftDirection = LEFT_UP_MOVE;
		_bossMotion[0] = KEYANIMANAGER->findAnimation("leftUpMove");
		_bossMotion[0]->start();
		_boss[0].rc = RectMakeCenter(_boss[0].x, _boss[0].y, _boss[0].img->getFrameWidth(), _boss[0].img->getFrameHeight());
		break;
	case LEFT_DOWN_MOVE:
		_boss[0].img = IMAGEMANAGER->findImage("bossHand");
		_bossLeftDirection = LEFT_DOWN_MOVE;
		_bossMotion[0] = KEYANIMANAGER->findAnimation("leftDownMove");
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
	case LEFT_LASER_ON:
		_bossLeftDirection = LEFT_LASER_ON;
		break;
	case LEFT_LASER_OFF:
		_bossLeftDirection = LEFT_LASER_OFF;
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
	bb->setLeftDirection(LEFT_LASER_ON);
	bb->setCount2(100);
	bb->setLeftMotion0(KEYANIMANAGER->findAnimation("leftIdle"));
	bb->getLeftMotion0()->start();
}


//===============================================================================
//								머리통
//===============================================================================
//머리텅
void Boss2::headMove()
{
	//입 총알 발사하게 함
	if (!(_count % 500))
	{
		if(_bossHeadDirection == HEAD_IDLE)
			changeHeadDirection(HEAD_ATTACK);
		
	}
	//입 다물게 함
	if (!(_count % 800))
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

//===============================================================================
//									오른손꾸락
//===============================================================================
//오른손꾸락
void Boss2::rightMove()
{
	if (!(_count % 100))
	{
		if (_bossRightDirection == RIGHT_UP_MOVE)
			changeRightDirection(RIGHT_LASER);
		else if (_bossRightDirection == RIGHT_DOWN_MOVE)
			changeRightDirection(RIGHT_LASER);
	}

	if (!(_count % 350))
	{
		if (_bossRightDirection == RIGHT_IDLE)
		{
			//if (_boss[2].y < WINSIZEY / 2)
			if (_boss[2].y < WINSIZEY / 2 + 400)
				changeRightDirection(RIGHT_DOWN_MOVE);
				//changeRightDirection(RIGHT_UP_MOVE);
			else
				changeRightDirection(RIGHT_UP_MOVE);
				//changeRightDirection(RIGHT_DOWN_MOVE);
		}
	}

	if (_boss[2].y < 300)
	{
		changeRightDirection(RIGHT_IDLE);
		_boss[2].y = _boss[2].y;
	}
	if (_boss[2].y > WINSIZEY - 100)
	{
		changeRightDirection(RIGHT_IDLE);
		_boss[2].y = WINSIZEY - 100;
	}

	if (_bossRightDirection == RIGHT_DOWN_MOVE)
		_boss[2].y += BOSSSPEED;
	if (_bossRightDirection == RIGHT_UP_MOVE)
		_boss[2].y -= BOSSSPEED;

	if (_bossRightDirection == RIGHT_LASER_OFF)
	{
		_count3 -= 1;
		if (_count3 <= 0) changeRightDirection(RIGHT_IDLE);
	}
}

void Boss2::changeRightDirection(BOSSRIGHTDIRECTION rightDirection)
{
	switch (rightDirection)
	{
	case RIGHT_IDLE:
		_boss[2].img = IMAGEMANAGER->findImage("bossHand");
		_bossRightDirection = RIGHT_IDLE;
		_bossMotion[2] = KEYANIMANAGER->findAnimation("rightIdle");
		_bossMotion[2]->start();
		_boss[2].rc = RectMakeCenter(_boss[2].x, _boss[2].y, _boss[2].img->getFrameWidth(), _boss[2].img->getFrameHeight());
		break;
	case RIGHT_UP_MOVE:
		_boss[2].img = IMAGEMANAGER->findImage("bossHand");
		_bossRightDirection = RIGHT_UP_MOVE;
		_bossMotion[2] = KEYANIMANAGER->findAnimation("rightUpMove");
		_bossMotion[2]->start();
		_boss[2].rc = RectMakeCenter(_boss[2].x, _boss[2].y, _boss[2].img->getFrameWidth(), _boss[2].img->getFrameHeight());
		break;
	case RIGHT_DOWN_MOVE:
		_boss[2].img = IMAGEMANAGER->findImage("bossHand");
		_bossRightDirection = RIGHT_DOWN_MOVE;
		_bossMotion[2] = KEYANIMANAGER->findAnimation("rightDownMove");
		_bossMotion[2]->start();
		_boss[2].rc = RectMakeCenter(_boss[2].x, _boss[2].y, _boss[2].img->getFrameWidth(), _boss[2].img->getFrameHeight());
		break;
	case RIGHT_LASER:
		_boss[2].img = IMAGEMANAGER->findImage("bossHand");
		_bossRightDirection = RIGHT_LASER;
		_bossMotion[2] = KEYANIMANAGER->findAnimation("rightLaser");
		_bossMotion[2]->start();
		_boss[2].rc = RectMakeCenter(_boss[2].x, _boss[2].y, _boss[2].img->getFrameWidth(), _boss[2].img->getFrameHeight());
		break;
	case RIGHT_LASER_ON:
		_bossRightDirection = RIGHT_LASER_ON;
		break;
	case RIGHT_LASER_OFF:
		_bossRightDirection = RIGHT_LASER_OFF;
		break;
	default:
		_boss[2].rc = RectMakeCenter(_boss[2].x, _boss[2].y, _boss[2].img->getFrameWidth(), _boss[2].img->getFrameHeight());
		break;
	}
}

void Boss2::CBrightAttack(void * obj)
{
	Boss2* bb = (Boss2*)obj;

	bb->_boss[2].img = IMAGEMANAGER->findImage("bossHand");
	bb->setRightDirection(RIGHT_LASER_ON);
	bb->setCount3(100);
	bb->setRightMotion2(KEYANIMANAGER->findAnimation("rightIdle"));
	bb->getRightMotion2()->start();
}


void Boss2::hitDamage(float damage)
{
	_currentHP -= damage;
}
