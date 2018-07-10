#include "stdafx.h" 
#include "Player.h"
Player::Player(){}
Player::~Player() {}

HRESULT Player::init()
{
	_pb = new playerBullet;
	_pb->init("총알0", "총알1", "총알2", "총알3");
	_player			= IMAGEMANAGER->findImage("기본플레이어");
	_playerHand[0]  = IMAGEMANAGER->findImage("플레이어손");
	_playerHand[1]  = IMAGEMANAGER->findImage("플레이어손");
	_playerWeapon   = IMAGEMANAGER->findImage("검10");
	_x = WINSIZEX / 2; _y = WINSIZEY / 2 -100;
	_attackEffect = IMAGEMANAGER->findImage("검쓰르륵");
	_count = 0;  _mouseAngle = 0;
	_attackEffectCount = 0;
	_gravity = GRAVITY;
	_currentHp = 80; _maxHp = 80;
	_currentDash = 2; _maxDash = 2;
	_armor = 0;
	_currentDash = 1024 , _maxDash = 1024;
	_currentFullNess = 0; _maxFullNess = 100;
	_jumpPower = 12.0f;
	_moveMentSpeed = 10.0f;
	_direction = RIGHT_STOP;
	_gold = 0;
	_jumpMax = 1; _jumpCount = 0;
	_locusX = 0 , _locusY = 0;
	_weaponAngle = 0;
	_weaponAttackAngle = 0;
	_fixedDamage = 0;
	_youUsingCount = 0;
	_isDashing = false;
	_isAttacking = false;
	_isGun = true;
	_attackSpeedCheckCount = false;
	

	int rightStop[] = { 0,1,2,3,4 };
	KEYANIMANAGER->addArrayFrameAnimation("오른쪽보고서있기", "기본플레이어", rightStop, 5, 10, true);
	int rightRun[] = { 8 ,9 ,10 ,11 ,12 ,13 ,14 ,15 };
	KEYANIMANAGER->addArrayFrameAnimation("오른쪽뛰기", "기본플레이어", rightRun, 8, 10, true);
	int rightJump[] = { 5 };
	KEYANIMANAGER->addArrayFrameAnimation("오른쪽점프", "기본플레이어", rightJump, 1, 10, true);
	int rightDie[] = { 6,7 };
	KEYANIMANAGER->addArrayFrameAnimation("오른쪽죽음", "기본플레이어", rightDie, 2, 10, true);

	int leftStop[] = { 19, 20 ,21 ,22 ,23 };
	KEYANIMANAGER->addArrayFrameAnimation("왼쪽보고서있기", "기본플레이어", leftStop, 5, 10, true);
	int leftRun[] = { 24, 25 ,26 ,27 ,28 ,29 ,30 , 31 };
	KEYANIMANAGER->addArrayFrameAnimation("왼쪽뛰기", "기본플레이어", leftRun, 8, 10, true);
	int leftJump[] = { 18 };
	KEYANIMANAGER->addArrayFrameAnimation("왼쪽점프", "기본플레이어", leftJump, 1, 10, true);
	int leftDie[] = { 16 ,17 };
	KEYANIMANAGER->addArrayFrameAnimation("왼쪽죽음", "기본플레이어", leftDie, 2, 10, true);

	_playerAnimation = KEYANIMANAGER->findAnimation("오른쪽보고서있기");
	
	//equipment
	_mainWeapon[0] = 2;
	_mainWeapon[1] = 0;
	for (int i = 0; i < 15; ++i)
	{
		_inventory[i] = 0;
	}
	for (int i = 0; i < 4; ++i)
	{
		_accessory[i] = 0;
	}
	
	_collisionRc = RectMakeCenter(_x, _y, _player->getFrameWidth(), _player->getFrameHeight());
	return S_OK;
}

void Player::release() {}

void Player::update()
{
	keyInput();
	move();
	mouseControl();
	effect();
	attack();
	KEYANIMANAGER->update();
	EFFECTMANAGER->update();
	cameraSetting();
	tileCollision();
	_collisionRc = RectMakeCenter(_x, _y, _player->getFrameWidth(), _player->getFrameHeight());
	pixelCollision();
	_pb->update();
}

void Player::render()
{
	//여윽시 희진누나 작품 !!
	char strGun[128]; 
	if (_isLeftAttack) sprintf_s(strGun, "총10좌"); else if (!_isLeftAttack) sprintf_s(strGun, "총10우");
	RECT rc = RectMake(0,0,IMAGEMANAGER->findImage(strGun)->getWidth() * 2, IMAGEMANAGER->findImage(strGun)->getHeight());
	imageDC = IMAGEMANAGER->addRotateImage("rotateimage", rc.right - rc.left, rc.bottom - rc.top ,true,RGB(0,0,0), false);
	IMAGEMANAGER->findImage(strGun)->render(imageDC->getMemDC(), IMAGEMANAGER->findImage(strGun)->getWidth(),
		0,0,0, IMAGEMANAGER->findImage(strGun)->getWidth(), IMAGEMANAGER->findImage(strGun)->getHeight());
		
	// ===================
	EFFECTMANAGER->render();
	if (_direction == LEFT_RUN || _direction == LEFT_STOP)
	{
		_playerHand[0]->rotateRender(DC, _leftHandX , _leftHandY , _mouseAngle);
		_playerHand[1]->render(DC, _rightHandX , _rightHandY);
		
	}
	if (_direction == RIGHT_RUN || _direction == RIGHT_STOP)
	{
		 _playerHand[0]->render(DC, _leftHandX , _leftHandY	);
		 _playerHand[1]->rotateRender(DC, _rightHandX , _rightHandY , _mouseAngle);
	}

	//무기의 분기점
	if (_isGun)
	{
		if (_isLeftAttack && _mainWeapon[_youUsingCount] != 0)
			imageDC->rotateRender(DC, _leftHandX + TEN, _leftHandY, _weaponAngle);
		else if (!_isLeftAttack && _mainWeapon[_youUsingCount] != 0)
			imageDC->rotateRender(DC, _rightHandX  - TEN, _rightHandY, _weaponAngle);
		_player->aniRender(DC, _collisionRc.left, _collisionRc.top, _playerAnimation);
	}
	if (!_isGun)
	{
		if (_isLeftAttack && _mainWeapon[_youUsingCount] != 0)
		imageDC->rotateRender(DC, _leftHandX, _leftHandY, _weaponAngle + 1.8f);
		else if (!_isLeftAttack && _mainWeapon[_youUsingCount] != 0)
		imageDC->rotateRender(DC, _rightHandX, _rightHandY, _weaponAngle + 1.8f);
		_player->aniRender(DC, _x, _collisionRc.top, _playerAnimation);
	}
	if (_showAttackEffect)
	{
		_attackEffect->rotateFrameRender(DC, _collisionRc.left + (cosf(_angle) * ONE_HUNDRED) + _player->getFrameWidth() / 2 , _collisionRc.top + (-sinf(_angle) * ONE_HUNDRED) + _player->getFrameHeight() / 2, _angle - 1.8);
	}
	//text !
	char str[128]; sprintf_s(str, "Weapon Index : %d", _youUsingCount);
	if (_isJumping)  sprintf_s(str, "점프 : true");
	else if (!_isJumping) sprintf_s(str, "점프 : false");
	TextOut(DC, _collisionRc.left - 50 , _collisionRc.top - 150, str, strlen(str));
	//// tile check 
	sprintf(str, "x 좌표 : %f", _x);
	TextOut(DC, _x-300, _y - 200, str, strlen(str));
	sprintf(str, "y 좌표 : %f", _y);
	TextOut(DC, _x- 300, _y - 300, str, strlen(str)); 
	sprintf(str, "체크타일 %d,%d", leftRightCheck[0], leftRightCheck[1]);
	TextOut(DC, _x - 10, _collisionRc.top , str, strlen(str));
	sprintf(str, "위에 타일 %d,%d", _upStateCheck[0] , _upStateCheck[1]);
	TextOut(DC, _x - 10, _collisionRc.top - 50, str, strlen(str));
	sprintf(str, "아래 타일 %d,%d", _downStateCheck[0], _downStateCheck[1]);
	TextOut(DC, _x - 10, _collisionRc.top - 100, str, strlen(str));

	//pb
	_pb->render();
	for (int i = 0; i < 30; ++i)
	{
		for (int j = 0; j < 30; ++j)
		{
		if(KEYMANAGER->isToggleKey(VK_F1))	Rectangle(DC, _tiles[j + i * 30].rc.left, _tiles[j + i * 30].rc.top, _tiles[j + i * 30].rc.right, _tiles[j + i * 30].rc.bottom);
		}
	}
	if (KEYMANAGER->isToggleKey(VK_F1)) Rectangle(DC,_collisionRc.left , _collisionRc.top , _collisionRc.right, _collisionRc.bottom);
}

void Player::keyInput()
{
	if (KEYMANAGER->isOnceKeyDown('1'))		 _youUsingCount = 0;
	else if (KEYMANAGER->isOnceKeyDown('2')) _youUsingCount = 1;

	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		_direction = LEFT_RUN;
		_playerAnimation = KEYANIMANAGER->findAnimation("왼쪽뛰기");
		_playerAnimation->start();

	}
	else if (KEYMANAGER->isOnceKeyUp('A')&&_direction!=RIGHT_RUN)
	{
		_direction = LEFT_STOP;
		_playerAnimation = KEYANIMANAGER->findAnimation("왼쪽보고서있기");
		_playerAnimation->start();
	}

	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		_direction = RIGHT_RUN;
		_playerAnimation = KEYANIMANAGER->findAnimation("오른쪽뛰기");
		_playerAnimation->start();

	}
	else if (KEYMANAGER->isOnceKeyUp('D') && _direction != LEFT_RUN)
	{
		_direction = RIGHT_STOP;
		_playerAnimation = KEYANIMANAGER->findAnimation("오른쪽보고서있기");
		_playerAnimation->start();
	}

	if (KEYMANAGER->isStayKeyDown('S') 
	&& KEYMANAGER->isOnceKeyDown(VK_SPACE)
	&& _goDownJump) _y += 100;
	else if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_jumpCount++;
		_isJumping = true;
		_gravity = GRAVITY;
		_jump = _jumpPower;
		
		if (_direction == LEFT_RUN || _direction == LEFT_STOP)
		{
			_playerAnimation = KEYANIMANAGER->findAnimation("왼쪽점프");
			_playerAnimation->start();
		}
		else if (_direction == RIGHT_RUN || _direction == RIGHT_STOP)
		{
			_playerAnimation = KEYANIMANAGER->findAnimation("오른쪽점프");
			_playerAnimation->start();
		}
		if (_jumpCount == 1) EFFECTMANAGER->play("점프야압", _x + 50 , _y + 50);
		if (_jumpCount == 2) EFFECTMANAGER->play("이건이단점프야압", _x + 50, _y + 50);	
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (!_isAttacking && !_attackSpeedCheckCount)
		{
			if (_mainWeapon[_youUsingCount] == 0) _punchSpeed = PUNCHSPEED;
			_angle = getAngle(_collisionRc.left + _player->getFrameWidth() / 2, _collisionRc.top + _player->getFrameHeight() / 2, PTMOUSE_X, PTMOUSE_Y);
			_isAttacking = true;
		}
		
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{	
		if (_currentDash > 0)
		{
			_currentDash--;
			_dashSpeed = DASHSPEED;
			_isDashing = true;
			_angle = getAngle(_collisionRc.left + _player->getFrameWidth() / 2, _collisionRc.top + _player->getFrameHeight() / 2, PTMOUSE_X, PTMOUSE_Y);
		}
	}
}

void Player::mouseControl()
{
	//마우스가 왼쪽에있는지 오른쪽에있는지 설정
	if (_collisionRc.left + _player->getFrameWidth() / 2 > PTMOUSE_X) _isLeftAttack = true;
	else _isLeftAttack = false;
	//마우스 앵글 
	_mouseAngle = getAngle(_collisionRc.left + _player->getFrameWidth() / 2, _collisionRc.top + _player->getFrameHeight() / 2 , PTMOUSE_X, PTMOUSE_Y);
	// 무기앵글 = 마우스앵글 + 무기공격각도 
	if (_isGun)
	{
		_weaponAngle = _mouseAngle + _weaponAttackAngle;
	}
	else
	{
		if (_isLeftAttack)_weaponAngle = _mouseAngle + _weaponAttackAngle - (PI + 0.4);
		else if (!_isLeftAttack)_weaponAngle = _mouseAngle + _weaponAttackAngle;
	}
		if (_weaponAngle > PI2) _weaponAngle -= PI2;
	
	//ptmouse 좌표에따라 왼쪽을볼건지 오른쪽을 볼건지 설정 
	if (_isLeftAttack)
	{
		if (_direction == RIGHT_STOP)
		{
			_playerAnimation = KEYANIMANAGER->findAnimation("왼쪽보고서있기");
			_direction = LEFT_STOP;
		}
		else if (_direction == RIGHT_RUN || _direction == LEFT_RUN)
		{
			_playerAnimation = KEYANIMANAGER->findAnimation("왼쪽뛰기");
		}
	}
	else if (!_isLeftAttack)
	{
		if (_direction == LEFT_STOP)
		{
			_playerAnimation = KEYANIMANAGER->findAnimation("오른쪽보고서있기");
			_direction = RIGHT_STOP;
		}
		else if (_direction == LEFT_RUN || _direction == RIGHT_RUN)
		{
			_playerAnimation = KEYANIMANAGER->findAnimation("오른쪽뛰기");
		}
	}
}

void Player::move()
{
	static int count;
	count++;
	if (count > 100)
	{
		count = 0;
		if(!(_currentDash >= _maxDash)) _currentDash++;
	}
	
	// isJUMPING
	if (_isJumping)
	{
		_jump -= _gravity;
		_y -= _jump;
	}

	
	if (_isDashing)
	{
		_dashSpeed -= 2.0f;
		_x +=  cosf(_angle) * _dashSpeed;
		_y += -sinf(_angle) * _dashSpeed;
	}
	if (_dashSpeed < 0)
	{
		_dashSpeed = 0;
		_isDashing = false;
		
	}
	if (_direction == LEFT_RUN)
	{
		_x -= _moveMentSpeed;
	}
	else if (_direction == RIGHT_RUN )
	{
		_x += _moveMentSpeed;
	}
	if (!_isAttacking)
	{
		if (_direction ==  LEFT_RUN || _direction ==  LEFT_STOP)
		{
			_leftHandX = _collisionRc.left + 15, _leftHandY = _collisionRc.top + 60;
			_rightHandX = _collisionRc.left + 60, _rightHandY = _collisionRc.top + 60;
		}
		if (_direction == RIGHT_RUN || _direction == RIGHT_STOP)
		{
			_leftHandX = _collisionRc.left + 10, _leftHandY = _collisionRc.top + 60;
			_rightHandX = _collisionRc.left + 65, _rightHandY = _collisionRc.top + 60;
		}
	}
}

void Player::attack()
{
	float _cosValue = cosf(_angle) * ONE_HUNDRED - 40, _sinValue = -sinf(_angle) * ONE_HUNDRED - 40;
	static unsigned int attackSpeedCheckCount = 0;
	if(_attackSpeedCheckCount)++attackSpeedCheckCount;
	if(_isAttacking)
	{
	
		if (_isGun && _isLeftAttack) _weaponAngle -= PI / 100;
		else if (_isGun && !_isLeftAttack) _weaponAngle += PI / 100;
		if(_mainWeapon[_youUsingCount] == 0)_punchSpeed -= 0.7;
		//punch
		if (_mainWeapon[_youUsingCount] == 0)
		{
			if (_isLeftAttack)
			{
				_locusX +=  cosf(_angle) * _punchSpeed; 
				_locusY += -sinf(_angle) * _punchSpeed;
				_leftHandX = _collisionRc.left + 15 + _locusX , _leftHandY = _collisionRc.top + 60 + _locusY;
				_rightHandX = _collisionRc.left + 60, _rightHandY = _collisionRc.top + 60;
			}

			if (!_isLeftAttack)
			{
				_locusX += cosf(_angle) * _punchSpeed;
				_locusY += -sinf(_angle) * _punchSpeed;
				_leftHandX = _collisionRc.left + 10, _leftHandY = _collisionRc.top + 60;
				_rightHandX = _collisionRc.left + 65 + _locusX, _rightHandY = _collisionRc.top + 60 + _locusY;
			}
		}
		else if (_mainWeapon[_youUsingCount] == 1)
		{
			if (_isChap)_weaponAttackAngle += (PI / 180) * 200;
			else if (!_isChap)_weaponAttackAngle -= (PI / 180) * 200;

			if (_isLeftAttack)
			{
				(_isChap == false ? _isChap = true : _isChap = false);
				_leftHandX = _collisionRc.left + 15, _leftHandY = _collisionRc.top + 60;
				_rightHandX = _collisionRc.left + 60, _rightHandY = _collisionRc.top + 60;
				_isAttacking = false;
			}
			else if (!_isLeftAttack)
			{
				(_isChap == false ? _isChap = true : _isChap = false);
				_leftHandX = _collisionRc.left + 10, _leftHandY = _collisionRc.top + 60;
				_rightHandX = _collisionRc.left + 65 , _rightHandY = _collisionRc.top + 60 ;
				_isAttacking = false;
			}
		}
		else if (_isGun)
		{
			if (_isLeftAttack)
			{
				_attackSpeedCheckCount = true;
				_pb->bulletFire(_leftHandX + _cosValue, _leftHandY + _sinValue, _angle, 500, 10.0f,0);
				_weaponAttackAngle -= PI / 10;
				_leftHandX = _collisionRc.left + 15, _leftHandY = _collisionRc.top + 60;
				_rightHandX = _collisionRc.left + 60, _rightHandY = _collisionRc.top + 60;
				_isAttacking = false;
			}
			else if (!_isLeftAttack)
			{
				_attackSpeedCheckCount = true;
				_pb->bulletFire(_rightHandX + _cosValue, _rightHandY + _sinValue, _angle, 500, 10.0f, 0);
				_weaponAttackAngle += PI / 10;
				_leftHandX = _collisionRc.left + 10, _leftHandY = _collisionRc.top + 60;
				_rightHandX = _collisionRc.left + 65, _rightHandY = _collisionRc.top + 60;
				_isAttacking = false;
			}
		}
	}
	if (_punchSpeed < -PUNCHSPEED)
	{
		_isAttacking = false;
		_locusX = 0, _locusY = 0;
	}
	if (attackSpeedCheckCount > 30)
	{
		attackSpeedCheckCount = 0;
		_attackSpeedCheckCount = false;
		if (_isGun) _weaponAttackAngle = 0;
	}
}

void Player::effect()
{
	//if(_showAttackEffect)CAMERAMANAGER->cameraShaking();
	if (!_isJumping)
	{
		if (KEYMANAGER->isStayKeyDown('A')) EFFECTMANAGER->play("왼쪽걸을때", _collisionRc.left + 70, _collisionRc.top + 70);
		if (KEYMANAGER->isStayKeyDown('D')) EFFECTMANAGER->play("오른쪽걸을때", _collisionRc.left, _collisionRc.top + 70);
	}
	if (_isDashing) ++_count;
	if (_count > 5)
	{
		_count = 0;
		if (_collisionRc.left > PTMOUSE_X)
		{
			EFFECTMANAGER->play("대시왼쪽", _collisionRc.left + 30 , _collisionRc.top +10 + _player->getFrameWidth() / 2);
		}
		else if (_collisionRc.left < PTMOUSE_X)
		{
			EFFECTMANAGER->play("대시오른쪽", _collisionRc.left + 20, _collisionRc.top + 10 +_player->getFrameWidth() / 2);
		}
	}	

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (_mainWeapon[_youUsingCount] == 1)
		{
			_showAttackEffect = true;
			_attackEffect->setFrameX(0) , _attackEffect->setFrameY(0);
		}
	}
	++_attackEffectCount;
	if (_attackEffectCount > 3)
	{
		_attackEffectCount = 0; 
		_attackEffect->setFrameX(_attackEffect->getFrameX() + 1);
		if (_attackEffect->getFrameX() >= _attackEffect->getMaxFrameX()) _showAttackEffect = false;
	}

}

void Player::cameraSetting()
{
	int cameraX = CAMERAMANAGER->getCameraCenter().x, cameraY = CAMERAMANAGER->getCameraCenter().y;
	int plusCameraMoveValueX = abs(cameraX + 50 - _x), plusCameraMoveValueY = abs(cameraY + 50 - _collisionRc.top);
	int minusCameraMoveValueX = abs(cameraX - 50 - _x), minusCameraMoveValueY = abs(cameraY - 50 - _collisionRc.top);
	// 오른쪽 기
	if(_x > cameraX + 50 && cameraX + WINSIZEX / 2 < BACKGROUNDSIZEX)
		CAMERAMANAGER->setCameraX(cameraX + plusCameraMoveValueX);
	// 왼쪽 기
	if(_x < cameraX - 50 && cameraX - WINSIZEX / 2 > 0) 
		CAMERAMANAGER->setCameraX(cameraX - minusCameraMoveValueX);

	// 위로 기
	if (_collisionRc.top < cameraY - 50 && cameraY - WINSIZEY / 2 > 0)
		CAMERAMANAGER->setCameraY(cameraY - minusCameraMoveValueY);
	// 아래로 기
	if (_collisionRc.top > cameraY + 50 && cameraY + WINSIZEY / 2 < BACKGROUNDSIZEY)
		CAMERAMANAGER->setCameraY(cameraY + plusCameraMoveValueY);
}
// 1. 왼쪽으로갈때 벽있으면 벽에붙음
// 2. 


void Player::tileCollision()
{
	_collisionRc.left += 3, _collisionRc.top += 3, _collisionRc.right -= 3, _collisionRc.bottom -= 3;

	xIndex = (_collisionRc.left / TILESIZE) , yIndex = (_collisionRc.top / TILESIZE);
	_downStateCheck[0] = xIndex + (VARIABLE_SIZEX[_dungeonNum] * (yIndex + 1)), _downStateCheck[1] = xIndex + (VARIABLE_SIZEX[_dungeonNum] * (yIndex + 1)) + 1;
	_upStateCheck[0] = xIndex + (VARIABLE_SIZEX[_dungeonNum] * (yIndex )), _upStateCheck[1] = xIndex + (VARIABLE_SIZEX[_dungeonNum] * (yIndex )) + 1;


	leftRightCheck[0] = (yIndex * VARIABLE_SIZEX[_dungeonNum]) + xIndex;
	leftRightCheck[1] = (yIndex  * VARIABLE_SIZEX[_dungeonNum]) + xIndex +1;




	for (int i = 0; i < 2; ++i)
	{
		//천장
		if (_tiles[_upStateCheck[i]].object == OBJ_CEILING)
		{
			RECT temp;
			if (IntersectRect(&temp, &_tiles[_upStateCheck[i]].rc, &_collisionRc))
			{
				long rcHeight = _collisionRc.bottom - _collisionRc.top;
				_collisionRc.top = _tiles[_upStateCheck[i]].rc.bottom;
				_collisionRc.bottom = _collisionRc.top + rcHeight;
				_jump = -(_jump / 2);
				_y = _collisionRc.top + (rcHeight / 2);
			}
		}

			
		//왼쪽오른쪽 
		if (_tiles[leftRightCheck[i]].object == OBJ_CULUMN)
		{
			RECT temp;

			if (IntersectRect(&temp, &_tiles[leftRightCheck[i]].rc, &_collisionRc))
			{
				if (i == 0)
				{
					long rcSize = _collisionRc.right - _collisionRc.left;
					_collisionRc.left = _tiles[leftRightCheck[i]].rc.right;
					_collisionRc.right = _collisionRc.left + rcSize;
					_x = _collisionRc.right - rcSize / 2;
				}
				else if (i == 1)
				{
					long rcSize = _collisionRc.right - _collisionRc.left;
					_collisionRc.right = _tiles[leftRightCheck[i]].rc.left;
					_collisionRc.left = _collisionRc.right - rcSize;
					_x = _collisionRc.left + rcSize / 2;
				}
			}
		}
		//위 체크 :upStateCheck
		if (_tiles[_upStateCheck[i]].object == OBJ_CULUMN)
		{
			RECT temp;
			if (IntersectRect(&temp, &_tiles[_upStateCheck[i]].rc, &_collisionRc))
			{
				long rcHeight = _collisionRc.bottom - _collisionRc.top;
				_collisionRc.top = _tiles[_upStateCheck[i]].rc.bottom;
				_collisionRc.bottom = _collisionRc.top + rcHeight;
				_y = _collisionRc.top + (rcHeight / 2);
			}
		}

		//아래 체크 :downStateCheck
		if (_tiles[_downStateCheck[i]].object != OBJ_CULUMN
			&& (_tiles[_downStateCheck[i]].object != OBJ_GOGROUND)
			&& (_tiles[_downStateCheck[i]].object != OBJ_GROUND)
			&& (_tiles[_downStateCheck[i]].terrain != TOWN_GROUND))
			
		{
			_isJumping = true;
			_gravity = GRAVITY;
		}
		else if(_tiles[_downStateCheck[i]].object == OBJ_CULUMN
		|| (_tiles[_downStateCheck[i]].object == OBJ_GOGROUND)
		|| (_tiles[_downStateCheck[i]].object == OBJ_GROUND)
		|| (_tiles[_downStateCheck[i]].terrain == TOWN_GROUND))
		{
			 if (!_isDashing)
			 {
				int value = 0;
				if (_jump == 0) value = 1;
				if (_jump > 0) value = 1;
				if (_jump < 0) value = 30;
				if (_collisionRc.left < _tiles[_downStateCheck[i]].rc.right
					&& _collisionRc.right > _tiles[_downStateCheck[i]].rc.left
					&& _collisionRc.top < _tiles[_downStateCheck[i]].rc.top
					&& _collisionRc.bottom > _tiles[_downStateCheck[i]].rc.top
					&& _collisionRc.bottom < _tiles[_downStateCheck[i]].rc.top + value)
				{
					long rcHeight = _collisionRc.bottom - _collisionRc.top;
					_isJumping = false;
					_gravity = 0;
					_jump = 0;
					_collisionRc.bottom = _tiles[_downStateCheck[i]].rc.top;
					_collisionRc.top = _collisionRc.bottom - rcHeight;
					_y = _collisionRc.top + (rcHeight / 2);
					if (_tiles[_downStateCheck[i]].object == OBJ_GOGROUND) _goDownJump = true;
					else _goDownJump = false;
				}
			 }

		  	 else if (_isDashing)
			 {
				RECT temp;
				if (IntersectRect(&temp, &_tiles[_downStateCheck[i]].rc, &_collisionRc))
				{
					long rcHeight = _collisionRc.bottom - _collisionRc.top;
					_isJumping = false;
					_gravity = 0;
					_jump = 0;
					_collisionRc.bottom = _tiles[_downStateCheck[i]].rc.top;
					_collisionRc.top = _collisionRc.bottom - rcHeight;
					_y = _collisionRc.top + (rcHeight / 2);
					if (_tiles[_downStateCheck[i]].object == OBJ_GOGROUND) _goDownJump = true;
					else _goDownJump = false;
				}
			 }

		}
	}
}

void Player::pixelCollision()
{

	for (int j = _y + 20; j < _y + 70; ++j)
	{
		if (!_isDashing)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("pixel")->getMemDC(), _x, j);

			int r = GetRValue(color), g = GetGValue(color), b = GetBValue(color);

			if (r == 0 && g == 255 && b == 0)
			{

				

				if (KEYMANAGER->isOnceKeyDown(VK_SPACE))_isJumping = true;
				else
				{
					_y = j - 50;
					_isJumping = false;
				}
				break;
			}
		}
	}
}


