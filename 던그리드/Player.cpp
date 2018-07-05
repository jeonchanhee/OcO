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
	_x = WINSIZEX / 2; _y = WINSIZEY / 2;
	_attackEffect = IMAGEMANAGER->findImage("검쓰르륵");
	_count = 0;  _mouseAngle = 0;
	_attackEffectCount = 0;

	_currentHp = 80; _maxHp = 80;
	_currentDash = 2; _maxDash = 2;
	_armor = 0;
	_currentDash = 2 , _maxDash = 2;
	_currentFullNess = 0; _maxFullNess = 100;
	_jumpPower = 12.0f;
	_moveMentSpeed = 3.0f;
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
	_pb->update();
}

void Player::render()
{
	char strGun[128]; 
	if (_isLeftAttack) sprintf_s(strGun, "총10좌"); else if (!_isLeftAttack) sprintf_s(strGun, "총10우");
	//여윽시 희진누나 작품 !!
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
			imageDC->rotateRender(DC, _leftHandX + 5, _leftHandY, _weaponAngle);
		else if (!_isLeftAttack && _mainWeapon[_youUsingCount] != 0)
			imageDC->rotateRender(DC, _rightHandX  - 5, _rightHandY, _weaponAngle);
		_player->aniRender(DC, _x, _y, _playerAnimation);
	}
	if (!_isGun)
	{
		if (_isLeftAttack && _mainWeapon[_youUsingCount] != 0)
			imageDC->rotateRender(DC, _leftHandX, _leftHandY, _weaponAngle + 1.8f);
		else if (!_isLeftAttack && _mainWeapon[_youUsingCount] != 0)
			imageDC->rotateRender(DC, _rightHandX, _rightHandY, _weaponAngle + 1.8f);
		_player->aniRender(DC, _x, _y, _playerAnimation);
	}
	if (_showAttackEffect)
	{
		_attackEffect->rotateFrameRender(DC, _x + (cosf(_angle) * ONE_HUNDRED) + _player->getFrameWidth() / 2 , _y + (-sinf(_angle) * ONE_HUNDRED) + _player->getFrameHeight() / 2, _angle - 1.8);
	}
	//text !
	char str[128]; sprintf_s(str, "Weapon Index : %d", _youUsingCount);
	TextOut(DC, _x -50 , _y - 50, str, strlen(str));
	sprintf_s(str, "Current Dash : %d", _currentDash);
	TextOut(DC, _x - 50, _y - 100, str, strlen(str));
	sprintf_s(str, "Max Dash : %d", _maxDash);
	TextOut(DC, _x  + 100, _y - 100, str, strlen(str));
	if (_isAttacking) sprintf_s(str, "Attacking : true");
	else sprintf_s(str, "Attacking : false");
	TextOut(DC, _x + 100, _y - 50, str, strlen(str));
	if (_isJumping)  sprintf_s(str, "점프 : true");
	else if (!_isJumping) sprintf_s(str, "점프 : false");
	TextOut(DC, _x - 50 , _y - 150, str, strlen(str));
	if (_isDashing)sprintf_s(str, "dashing???  : true");
	else if (!_isDashing)sprintf_s(str, "dashing???  : false");
	TextOut(DC, _x + 60, _y - 150, str, strlen(str));
	sprintf_s(str, "main Weapon[count] : %d", _mainWeapon[_youUsingCount]);
	TextOut(DC, _x -10, _y - 30, str, strlen(str));
	sprintf_s(str, "마우스와 플레이어의 각 : %f", _mouseAngle);
	TextOut(DC, _x - 10, _y + 100, str, strlen(str));
	sprintf(str, "무기의 각 : %f", _weaponAngle);
	TextOut(DC, _x - 10, _y + 150, str, strlen(str));
	sprintf(str, "무기의 공격 각 : %f", _weaponAttackAngle);
	TextOut(DC, _x - 10, _y + 200, str, strlen(str));

	//pb
	_pb->render();
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
	else if (KEYMANAGER->isOnceKeyUp('A'))
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
	else if (KEYMANAGER->isOnceKeyUp('D'))
	{
		_direction = RIGHT_STOP;
		_playerAnimation = KEYANIMANAGER->findAnimation("오른쪽보고서있기");
		_playerAnimation->start();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		if (_jumpCount < _jumpMax)
		{
			_jumpCount++;
			_jump = _jumpPower;
			_isJumping = true;
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
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (!_isAttacking)
		{
			_punchSpeed = PUNCHSPEED;
			_angle = getAngle(_x + _player->getFrameWidth() / 2, _y + _player->getFrameHeight() / 2, PTMOUSE_X, PTMOUSE_Y);
			_isAttacking = true;

		}
		_pb->bulletFire(_x, _y, _angle, 500, 10.0f, 0);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{	
		if (_currentDash > 0)
		{
			_currentDash--;
			_dashSpeed = DASHSPEED;
			_isDashing = true;
			_angle = getAngle(_x + _player->getFrameWidth() / 2, _y + _player->getFrameHeight() / 2, PTMOUSE_X, PTMOUSE_Y);
		}
	}
}

void Player::mouseControl()
{
	//마우스가 왼쪽에있는지 오른쪽에있는지 설정
	if (_x + _player->getFrameWidth() / 2 > PTMOUSE_X) _isLeftAttack = true;
	else _isLeftAttack = false;
	//마우스 앵글 
	_mouseAngle = getAngle(_x + _player->getFrameWidth() / 2, _y + _player->getFrameHeight() / 2 , PTMOUSE_X, PTMOUSE_Y);
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
	if (_isJumping)
	{
		_jump -= GRAVITY;
		_y -= _jump;
	}
	else if (!_isJumping)
	{
		_jump = 0;
	}
	if (_jump <= -11.7)
	{
		_isJumping = false;
		_jumpCount = 0;
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
	else if (_direction == RIGHT_RUN)
	{
		_x += _moveMentSpeed;
	}
	if (!_isAttacking)
	{
		if (_direction ==  LEFT_RUN || _direction ==  LEFT_STOP)
		{
			_leftHandX = _x + 15, _leftHandY = _y + 60;
			_rightHandX = _x + 60, _rightHandY = _y + 60;
		}
		if (_direction == RIGHT_RUN || _direction == RIGHT_STOP)
		{
			_leftHandX = _x + 10, _leftHandY = _y + 60;
			_rightHandX = _x + 65, _rightHandY = _y + 60;
		}
	}
}

void Player::attack()
{
	if(_isAttacking)
	{
		_punchSpeed -= 0.7;
		//punch
		if (_mainWeapon[_youUsingCount] == 0)
		{
			if (_isLeftAttack)
			{
				_locusX +=  cosf(_angle) * _punchSpeed; 
				_locusY += -sinf(_angle) * _punchSpeed;
				_leftHandX = _x + 15 + _locusX , _leftHandY = _y + 60 + _locusY;
				_rightHandX = _x + 60, _rightHandY = _y + 60;
			}
			if (!_isLeftAttack)
			{
				_locusX += cosf(_angle) * _punchSpeed;
				_locusY += -sinf(_angle) * _punchSpeed;
				_leftHandX = _x + 10, _leftHandY = _y + 60;
				_rightHandX = _x + 65 + _locusX, _rightHandY = _y + 60 + _locusY;
			}
		}
		else if (_mainWeapon[_youUsingCount] == 1)
		{
			if (_isChap)_weaponAttackAngle += (PI / 180) * 200;
			else if (!_isChap)_weaponAttackAngle -= (PI / 180) * 200;

			if (_isLeftAttack)
			{
				(_isChap == false ? _isChap = true : _isChap = false);
				_leftHandX = _x + 15, _leftHandY = _y + 60;
				_rightHandX = _x + 60, _rightHandY = _y + 60;
				_isAttacking = false;
			}
			else if (!_isLeftAttack)
			{
				(_isChap == false ? _isChap = true : _isChap = false);
				_leftHandX = _x + 10, _leftHandY = _y + 60;
				_rightHandX = _x + 65 , _rightHandY = _y + 60 ;
				_isAttacking = false;
			}
		}
		else if (_mainWeapon[_youUsingCount] == 2)
		{

		}
	}
	if (_punchSpeed < -PUNCHSPEED)
	{
		_isAttacking = false;
		_locusX = 0, _locusY = 0;
	}

}

void Player::effect()
{
		
	//if(_showAttackEffect)CAMERAMANAGER->cameraShaking();
	if (!_isJumping)
	{
		if (KEYMANAGER->isStayKeyDown('A')) EFFECTMANAGER->play("왼쪽걸을때", _x + 70, _y + 70);
		if (KEYMANAGER->isStayKeyDown('D')) EFFECTMANAGER->play("오른쪽걸을때", _x, _y + 70);
	}
	if (_isDashing) ++_count;
	if (_count > 5)
	{
		_count = 0;
		if (_x > PTMOUSE_X)
		{
			EFFECTMANAGER->play("대시왼쪽", _x + 30 , _y +10 + _player->getFrameWidth() / 2);
		}
		else if (_x < PTMOUSE_X)
		{
			EFFECTMANAGER->play("대시오른쪽", _x + 20, _y + 10 +_player->getFrameWidth() / 2);
		}
	}	

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (_mainWeapon[_youUsingCount] == 1)
		{
			_showAttackEffect = true;
			_attackEffect->setFrameX(0);  _attackEffect->setFrameY(0);
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