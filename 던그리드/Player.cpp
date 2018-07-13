#include "stdafx.h" 
#include "Player.h"
#include "dungeonScene.h"

Player::Player(){}
Player::~Player() {}

HRESULT Player::init()
{
	_inven = new inven;
	_inven->init();

	_hpbar = new progressBar;
	_hpbar->init(170,56, 294,60,"hp","hpb", BAR_PLAYER);

	imageDC = new image;
	//imageDC = IMAGEMANAGER->addImage("asd", 500, 500);
	_pb = new playerBullet;
	_pb->init("�Ѿ�0", "�Ѿ�1", "�Ѿ�2", "�Ѿ�3" , "ȭ��");
	_player			= IMAGEMANAGER->findImage("�⺻�÷��̾�");
	_playerHand[0]  = IMAGEMANAGER->findImage("�÷��̾��");
	_playerHand[1]  = IMAGEMANAGER->findImage("�÷��̾��");
	itemInfo();
	_x = WINSIZEX / 2; _y = WINSIZEY / 2 -100;
	_attackEffect = IMAGEMANAGER->findImage("��1ȿ��");
	
	_level = 1;
	_dashCount = 0, _attackCount = 0;
	_mouseAngle = 0;
	_currentDash = 1024 , _maxDash = 1024;
	//_currentDash = 2 , _maxDash =2;
	_currentFullNess = 0; _maxFullNess = 100;
	_jumpPower = 12.0f;
	_moveMentSpeed = 10.0f;
	_direction = RIGHT_STOP;
	_jumpMax = 1; _jumpCount = 0;
	_locusX = 0 , _locusY = 0;
	_weaponAngle = 0;
	_weaponAttackAngle = 0;
	_fixedDamage = 0;
	_youUsingCount = 0;
	_bulletType = 0;
	_currentHp = 100;
	_maxHp = 100;
	_frameX = 0, _frameY = 0;

	_isDashing = false;
	_isAttacking = false;
	_isGun = false;
	_attackSpeedCheckCount = false;
	_isAlive = true;
	

	int rightStop[] = { 0,1,2,3,4 };
	KEYANIMANAGER->addArrayFrameAnimation("�����ʺ����ֱ�", "�⺻�÷��̾�", rightStop, 5, 10, true);
	int rightRun[] = { 8 ,9 ,10 ,11 ,12 ,13 ,14 ,15 };
	KEYANIMANAGER->addArrayFrameAnimation("�����ʶٱ�", "�⺻�÷��̾�", rightRun, 8, 10, true);
	int rightJump[] = { 5 };
	KEYANIMANAGER->addArrayFrameAnimation("����������", "�⺻�÷��̾�", rightJump, 1, 10, true);
	int rightDie[] = { 6,7 };
	KEYANIMANAGER->addArrayFrameAnimation("����������", "�⺻�÷��̾�", rightDie, 2, 10, true);

	int leftStop[] = { 19, 20 ,21 ,22 ,23 };
	KEYANIMANAGER->addArrayFrameAnimation("���ʺ����ֱ�", "�⺻�÷��̾�", leftStop, 5, 10, true);
	int leftRun[] = { 24, 25 ,26 ,27 ,28 ,29 ,30 , 31 };
	KEYANIMANAGER->addArrayFrameAnimation("���ʶٱ�", "�⺻�÷��̾�", leftRun, 8, 10, true);
	int leftJump[] = { 18 };
	KEYANIMANAGER->addArrayFrameAnimation("��������", "�⺻�÷��̾�", leftJump, 1, 10, true);
	int leftDie[] = { 16 ,17 };
	KEYANIMANAGER->addArrayFrameAnimation("��������", "�⺻�÷��̾�", leftDie, 2, 10, true);

	_playerAnimation = KEYANIMANAGER->findAnimation("�����ʺ����ֱ�");
	
	_collisionRc = RectMakeCenter(_x, _y, _player->getFrameWidth(), _player->getFrameHeight());
	RECT rc = RectMake(0, 0, _playerWeapon->getWidth() * 2, _playerWeapon->getHeight());
	imageDC->rotateInit(rc.right - rc.left, rc.bottom - rc.top, true, RGB(0, 0, 0), false);
	return S_OK;
}

void Player::release() {}

void Player::update()
{
	//die
	if (_currentHp <= 0)_currentHp = 0;
	
	if (KEYMANAGER->isOnceKeyDown(VK_F5)) _inven->pickUpItem(BOW , "Ȱ", 2);
	if (KEYMANAGER->isOnceKeyDown(VK_F6)) _inven->pickUpItem(SWORD, "��", 5);
	if (KEYMANAGER->isOnceKeyDown(VK_F7)) _inven->pickUpItem(ACCESSORY, "�Ǽ�", 1);
	if (KEYMANAGER->isOnceKeyDown(VK_F8)) _currentHp -= 20;
	
	if (_canMove == true && _isAlive)
	{
		keyInput();
		mouseControl();
		attack();
		effect();
		move();
	}
	KEYANIMANAGER->update();
	cameraSetting();
	tileCollision();
	_collisionRc = RectMakeCenter(_x, _y, _player->getFrameWidth(), _player->getFrameHeight());
	pixelCollision();
	_pb->update();
	_inven->update();
	_hpbar->setGauge(_currentHp, _maxHp);
	_hpbar->update();
	itemInfo();

}

void Player::render()
{
	//������ �������� ��ǰ !! 
	 if(_inven->getMainWeapon()[_youUsingCount]->getItem().isFrame)
		 _playerWeapon->frameRender(imageDC->getMemDC(), _playerWeapon->getWidth(),
		 0, 0, 0, _playerWeapon->getFrameWidth(), _playerWeapon->getFrameHeight() , _frameX , _frameY);
	 else 
	_playerWeapon->render(imageDC->getMemDC(), _playerWeapon->getWidth(),
		0, 0, 0, _playerWeapon->getWidth(), _playerWeapon->getHeight());
	// ===================
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

	//������ �б���

	if (_isGun)
	{
		if (_isLeftAttack 
			&& _inven->getMainWeapon().size() != 0
			&& _inven->getMainWeapon().size() > _youUsingCount
			&& _isAlive)
			imageDC->rotateRender(DC, _leftHandX + TEN, _leftHandY, _weaponAngle);
		else if (!_isLeftAttack 
			&& _inven->getMainWeapon().size() != 0
			&& _inven->getMainWeapon().size() > _youUsingCount
			&& _isAlive)
			imageDC->rotateRender(DC, _rightHandX  - TEN, _rightHandY, _weaponAngle);
			_player->aniRender(DC, _collisionRc.left, _collisionRc.top, _playerAnimation);
	}
	if (!_isGun)
	{
		if (_isLeftAttack 
			&& _inven->getMainWeapon().size() != 0
			&& _inven->getMainWeapon().size() > _youUsingCount
			&& _isAlive)
		imageDC->rotateRender(DC, _leftHandX, _leftHandY, _weaponAngle + 1.8f);
		else if (!_isLeftAttack 
			&& _inven->getMainWeapon().size() != 0
			&& _inven->getMainWeapon().size() > _youUsingCount
			&& _isAlive)
		imageDC->rotateRender(DC, _rightHandX, _rightHandY, _weaponAngle + 1.8f);
		_player->aniRender(DC, _collisionRc.left, _collisionRc.top, _playerAnimation);
	}
	if (_showAttackEffect )
	{
		_attackEffect->setX(_collisionRc.left + (cosf(_angle) * ONE_HUNDRED) + _player->getFrameWidth() / 2), _attackEffect->setY(_collisionRc.top + (-sinf(_angle) * ONE_HUNDRED) + _player->getFrameHeight() / 2);
		_attackEffect->rotateFrameRender(DC, _attackEffect->getX() , _attackEffect->getY(), _angle - 1.8);
	}
	//text !
	char str[128]; sprintf_s(str, "vector sizzE : %d", _inven->getItem().size());
	TextOut(DC, _collisionRc.left - 50, _collisionRc.top - 350, str, strlen(str));
	if (_isJumping)  sprintf_s(str, "���� : true");
	else if (!_isJumping) sprintf_s(str, "���� : false");
	TextOut(DC, _collisionRc.left - 50 , _collisionRc.top - 150, str, strlen(str));
	//// tile check 
	sprintf(str, "������ Ÿ�� : %d", _inven->getMainWeapon()[_youUsingCount]->getItemType());
	TextOut(DC, _x-300, _y - 200, str, strlen(str));
	sprintf(str, "y ��ǥ : %f", _y);
	TextOut(DC, _x- 300, _y - 300, str, strlen(str)); 
	sprintf(str, "currentHP : %d maxHP : %d", _currentHp, _maxHp);
	TextOut(DC, _x - 10, _collisionRc.top , str, strlen(str));

	//pb
	_pb->render();
	//inven
	_inven->render();
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		for (int i = 0; i < 30; ++i)
		{
			for (int j = 0; j < 30; ++j)
			{
				Rectangle(DC, _tiles[j + i * 30].rc.left, _tiles[j + i * 30].rc.top, _tiles[j + i * 30].rc.right, _tiles[j + i * 30].rc.bottom);
			}
		}
		Rectangle(DC, _collisionRc.left, _collisionRc.top, _collisionRc.right, _collisionRc.bottom);
		Rectangle(DC, _attackEffect->effectCheckBox().left, _attackEffect->effectCheckBox().top,
		_attackEffect->effectCheckBox().right, _attackEffect->effectCheckBox().bottom);
	}

	if (_start != 3)
	{
		IMAGEMANAGER->findImage("hpBar")->render(UIDC, 20, 20);
		IMAGEMANAGER->findImage("dashBar")->frameRender(UIDC, 35, 150);
		if (_currentDash > 0)
			IMAGEMANAGER->findImage("dash")->render(UIDC, 47, 162);
		if (_currentDash > 1)
			IMAGEMANAGER->findImage("dash")->render(UIDC, 101, 162);
		_hpbar->render();
	
	

	HFONT font, oldFont;
	font = CreateFont(50, 0, 0, 0, 100, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("�Ҿ߹ٸ�9"));
	oldFont = (HFONT)SelectObject(UIDC, font);
	SetTextColor(UIDC, RGB(255, 255, 255));
	SetBkMode(UIDC, TRANSPARENT);

	sprintf(str, "%d", _level);
	TextOut(UIDC, 80, 62, str, strlen(str));
	sprintf(str, "%d/%d", _currentHp, _maxHp);
	TextOut(UIDC, 250, 62, str, strlen(str));
	SelectObject(UIDC, oldFont);
	DeleteObject(font);
	}
}

void Player::keyInput()
{
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		_youUsingCount = 0;
		_inven->setIsSelect(_youUsingCount);
		
	}
	else if (KEYMANAGER->isOnceKeyDown('2'))
	{
		_youUsingCount = 1;
		_inven->setIsSelect(_youUsingCount);
	}

	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		_direction = LEFT_RUN;
		_playerAnimation = KEYANIMANAGER->findAnimation("���ʶٱ�");
		_playerAnimation->start();

	}
	else if (KEYMANAGER->isOnceKeyUp('A') && _direction!=RIGHT_RUN)
	{
		leftStop();
	}

	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		_direction = RIGHT_RUN;
		_playerAnimation = KEYANIMANAGER->findAnimation("�����ʶٱ�");
		_playerAnimation->start();

	}
	else if (KEYMANAGER->isOnceKeyUp('D') && _direction != LEFT_RUN)
	{
		rightStop();
	}

	if (KEYMANAGER->isStayKeyDown('S')
		&& KEYMANAGER->isOnceKeyDown(VK_SPACE)
		&& _goDownJump) _y += 90 , _goDownJump = false;
	else if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		SOUNDMANAGER->play("��������");
		_jumpCount++;
		_isJumping = true;
		_gravity = GRAVITY;
		_jump = _jumpPower;
		
		if (_direction == LEFT_RUN || _direction == LEFT_STOP)
		{
			_playerAnimation = KEYANIMANAGER->findAnimation("��������");
			_playerAnimation->start();
		}
		else if (_direction == RIGHT_RUN || _direction == RIGHT_STOP)
		{
			_playerAnimation = KEYANIMANAGER->findAnimation("����������");
			_playerAnimation->start();
		}
		if (_jumpCount == 1) EFFECTMANAGER->play("�����߾�", _x + 50 , _y + 50);
		if (_jumpCount == 2) EFFECTMANAGER->play("�̰��̴������߾�", _x + 50, _y + 50);	
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (!_isAttacking && !_attackSpeedCheckCount)
		{
			 _punchSpeed = PUNCHSPEED;
			_angle = getAngle(_collisionRc.left + _player->getFrameWidth() / 2, _collisionRc.top + _player->getFrameHeight() / 2, PTMOUSE_X, PTMOUSE_Y);
			_isAttacking = true;
			if(_inven->getMainWeapon().size() > _youUsingCount 
			&& _inven->getMainWeapon()[_youUsingCount]->getItemType() == SWORD) SOUNDMANAGER->play("Į����");
		}
		
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{	
		if (_currentDash > 0)
		{
			SOUNDMANAGER->play("��û���");
			_currentDash--;
			_dashSpeed = DASHSPEED;
			_isDashing = true;
			_jump = 0;
			_angle = getAngle(_collisionRc.left + _player->getFrameWidth() / 2, _collisionRc.top + _player->getFrameHeight() / 2, PTMOUSE_X, PTMOUSE_Y);
		}
	}
}

void Player::rightStop()
{
	_direction = RIGHT_STOP;
	_playerAnimation = KEYANIMANAGER->findAnimation("�����ʺ����ֱ�");
	_playerAnimation->start();
}

void Player::leftStop()
{
	_direction = LEFT_STOP;
	_playerAnimation = KEYANIMANAGER->findAnimation("���ʺ����ֱ�");
	_playerAnimation->start();
}

void Player::mouseControl()
{
	//���콺�� ���ʿ��ִ��� �����ʿ��ִ��� ����
	if (_collisionRc.left + _player->getFrameWidth() / 2 > PTMOUSE_X) _isLeftAttack = true;
	else _isLeftAttack = false;
	//���콺 �ޱ� 
	_mouseAngle = getAngle(_collisionRc.left + _player->getFrameWidth() / 2, _collisionRc.top + _player->getFrameHeight() / 2 , PTMOUSE_X, PTMOUSE_Y);
	// ����ޱ� = ���콺�ޱ� + ������ݰ��� 
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
	
	//ptmouse ��ǥ������ ������������ �������� ������ ���� 
	if (_isLeftAttack)
	{
		if (_direction == RIGHT_STOP)
		{
			_playerAnimation = KEYANIMANAGER->findAnimation("���ʺ����ֱ�");
			_direction = LEFT_STOP;
		}
		else if (_direction == RIGHT_RUN || _direction == LEFT_RUN)
		{
			_playerAnimation = KEYANIMANAGER->findAnimation("���ʶٱ�");
		}
	}
	else if (!_isLeftAttack)
	{
		if (_direction == LEFT_STOP)
		{
			_playerAnimation = KEYANIMANAGER->findAnimation("�����ʺ����ֱ�");
			_direction = RIGHT_STOP;
		}
		else if (_direction == LEFT_RUN || _direction == RIGHT_RUN)
		{
			_playerAnimation = KEYANIMANAGER->findAnimation("�����ʶٱ�");
		}
	}
}

void Player::move()
{
	//DIE === 
	if (_currentHp <= 0)_currentHp = 0, _isAlive = false;
	if (!_isAlive)
	{
		if (_direction == LEFT_STOP ||
			_direction == LEFT_RUN) _playerAnimation = KEYANIMANAGER->findAnimation("��������");
		if (_direction == RIGHT_STOP ||
			_direction == RIGHT_RUN) _playerAnimation = KEYANIMANAGER->findAnimation("����������");
		_playerAnimation->start();
	}
	// == DASH
	static int count;
	count++;
	if (count > 100)
	{
		count = 0;
		if(!(_currentDash >= _maxDash)) _currentDash++;
	}
	
	// isJUMPING
	// == JUMP
	if (_isJumping == false) _jumpCount = 0;
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
	
	if(_isAttacking && _attackCount == 0 )
	{
		if (_isGun && _isLeftAttack) _weaponAngle -= PI / 100;
		else if (_isGun && !_isLeftAttack) _weaponAngle += PI / 100;
		if(_inven->getMainWeapon().size() <= _youUsingCount)_punchSpeed -= 0.7;
		//punch
		if (_inven->getMainWeapon().size() <= _youUsingCount)
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
		else if (_inven->getMainWeapon()[_youUsingCount]->getItemType() == SWORD
			|| _inven->getMainWeapon()[_youUsingCount]->getItemType() == HAMMER 
			&&_inven->getMainWeapon().size() > _youUsingCount)
		{
			_attackCount+=2;
			_attackSpeedCheckCount = true, _showAttackEffect = true;
			if (_isChap)_weaponAttackAngle += (PI / 180) * 200;
			else if (!_isChap)_weaponAttackAngle -= (PI / 180) * 200;

			if (_isLeftAttack)
			{
				(_isChap == false ? _isChap = true : _isChap = false);
				_leftHandX = _collisionRc.left + 15, _leftHandY = _collisionRc.top + 60;
				_rightHandX = _collisionRc.left + 60, _rightHandY = _collisionRc.top + 60;
			
			}
			else if (!_isLeftAttack)
			{
				(_isChap == false ? _isChap = true : _isChap = false);
				_leftHandX = _collisionRc.left + 10, _leftHandY = _collisionRc.top + 60;
				_rightHandX = _collisionRc.left + 65 , _rightHandY = _collisionRc.top + 60 ;
			
			}
		}
		else if (_inven->getMainWeapon()[_youUsingCount]->getItemType() == GUN
		|| _inven->getMainWeapon()[_youUsingCount]->getItemType() == BOW)
		{
			_attackSpeedCheckCount = true, _showAttackEffect = true;
			if (_isLeftAttack)
			{
				_pb->bulletFire(_leftHandX + _cosValue, _leftHandY + _sinValue, _angle, _weaponAngle, 1500, 20.0f , _bulletType);
				_weaponAttackAngle -= PI / 10;
				_leftHandX = _collisionRc.left + 15, _leftHandY = _collisionRc.top + 60;
				_rightHandX = _collisionRc.left + 60, _rightHandY = _collisionRc.top + 60;
				_isAttacking = false;
			}
			else if (!_isLeftAttack)
			{
				_pb->bulletFire(_rightHandX + _cosValue, _rightHandY + _sinValue, _angle, _weaponAngle, 1500, 20.0f, _bulletType);
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
	int interval = 0;

	if (_inven->getMainWeapon().size() > _youUsingCount)
	{
		if (_inven->getMainWeapon()[_youUsingCount]->getItemType() == SWORD) interval = 1;
		else interval = 30;
	}
	else interval = 30;

	if (attackSpeedCheckCount > interval)
	{
		attackSpeedCheckCount = 0;
		_attackSpeedCheckCount = false;
		if (_isGun) _weaponAttackAngle = 0;
	}
	if (_attackCount > 0)
	{
		_attackCount = 0;
		_isAttacking = false;
	}
}

void Player::effect()
{
	if(_showAttackEffect)CAMERAMANAGER->cameraShaking();
	if (!_isJumping)
	{
		if (KEYMANAGER->isStayKeyDown('A')) EFFECTMANAGER->play("���ʰ�����", _collisionRc.left + 70, _collisionRc.top + 70);
		if (KEYMANAGER->isStayKeyDown('D')) EFFECTMANAGER->play("�����ʰ�����", _collisionRc.left, _collisionRc.top + 70);
	}
	if (_isDashing) ++_dashCount;
	if (_dashCount > 5)
	{
		_dashCount = 0;
		if (_collisionRc.left > PTMOUSE_X)
		{
			EFFECTMANAGER->play("��ÿ���", _collisionRc.left + 42 , _collisionRc.top +10 + _player->getFrameWidth() / 2);
		}
		else if (_collisionRc.left < PTMOUSE_X)
		{
			EFFECTMANAGER->play("��ÿ�����", _collisionRc.left + 42, _collisionRc.top + 10 +_player->getFrameWidth() / 2);
		}
	}	

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
	
		if (_inven->getMainWeapon().size() <= _youUsingCount) return;
		
		if (_inven->getMainWeapon()[_youUsingCount]->getItemType() == SWORD)
		{
		 
			_attackEffect->setFrameX(0) , _attackEffect->setFrameY(0);
		}
	}
	if(_showAttackEffect)++_attackEffectCount;
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
	// ������ ��
	if(_x > cameraX + 50 && cameraX + WINSIZEX / 2 < BACKGROUNDSIZEX)
		CAMERAMANAGER->setCameraX(cameraX + plusCameraMoveValueX);
	// ���� ��
	if(_x < cameraX - 50 && cameraX - WINSIZEX / 2 > 0) 
		CAMERAMANAGER->setCameraX(cameraX - minusCameraMoveValueX);

	// ���� ��
	if (_collisionRc.top < cameraY - 50 && cameraY - WINSIZEY / 2 > 0)
		CAMERAMANAGER->setCameraY(cameraY - minusCameraMoveValueY);
	// �Ʒ��� ��
	if (_collisionRc.top > cameraY + 50 && cameraY + WINSIZEY / 2 < BACKGROUNDSIZEY)
		CAMERAMANAGER->setCameraY(cameraY + plusCameraMoveValueY);
}

void Player::tileCollision()
{
	_collisionRc.left += 3, _collisionRc.top += 3, _collisionRc.right -= 3, _collisionRc.bottom -= 3;

	xIndex = (_collisionRc.left / TILESIZE) , yIndex = (_collisionRc.top / TILESIZE);
	_downStateCheck[0] = xIndex + (VARIABLE_SIZEX[_dungeonNum] * (yIndex + 1)), _downStateCheck[1] = xIndex + (VARIABLE_SIZEX[_dungeonNum] * (yIndex + 1)) + 1;
	_upStateCheck[0] = xIndex + (VARIABLE_SIZEX[_dungeonNum] * (yIndex )), _upStateCheck[1] = xIndex + (VARIABLE_SIZEX[_dungeonNum] * (yIndex )) + 1;

	_leftCheck[0] = (yIndex * VARIABLE_SIZEX[_dungeonNum]) + xIndex , _leftCheck[1] = ((yIndex + 1)  * VARIABLE_SIZEX[_dungeonNum]) + xIndex;
	_rightCheck[0] = (yIndex  * VARIABLE_SIZEX[_dungeonNum]) + xIndex + 1 , _rightCheck[1] = ((yIndex + 1)  * VARIABLE_SIZEX[_dungeonNum]) + xIndex + 1;

	int val = 0;
	if (_jump > 0) val = 2;
	else if (_jump <= 0) val = 1;

	for (int i = 0; i < val; ++i)
	{
		if (_tiles[_leftCheck[i]].object == OBJ_CULUMN)
		{
			RECT temp;

			if (IntersectRect(&temp, &_tiles[_leftCheck[i]].rc, &_collisionRc))
			{
				long rcSize = _collisionRc.right - _collisionRc.left;
				_collisionRc.left = _tiles[_leftCheck[i]].rc.right;
				_collisionRc.right = _collisionRc.left + rcSize;
				_x = _collisionRc.right - rcSize / 2;
			}
		}
		else if (_tiles[_rightCheck[i]].object == OBJ_CULUMN)
		{
			RECT temp;

			if (IntersectRect(&temp, &_tiles[_rightCheck[i]].rc, &_collisionRc))
			{

				long rcSize = _collisionRc.right - _collisionRc.left;
				_collisionRc.right = _tiles[_rightCheck[i]].rc.left;
				_collisionRc.left = _collisionRc.right - rcSize;
				_x = _collisionRc.left + rcSize / 2;
			}
		}
	}

	for (int i = 0; i < 2; ++i)
	{
		//õ��
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
		//�� üũ :upStateCheck
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

		//�Ʒ� üũ :downStateCheck
		if (_tiles[_downStateCheck[i]].object != OBJ_CULUMN
			&& (_tiles[_downStateCheck[i]].object != OBJ_GOGROUND)
			&& (_tiles[_downStateCheck[i]].object != OBJ_GROUND)
			&& (_tiles[_downStateCheck[i]].terrain != TOWN_GROUND))
			
		{
			_goDownJump = false;
			_isJumping = true;
			_gravity = GRAVITY;
		}
		else if(_tiles[_downStateCheck[i]].object == OBJ_CULUMN
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
					_goDownJump = false;

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
					_goDownJump = false;
				}
			 }

		}
	
		if ((_tiles[_downStateCheck[i]].object == OBJ_GOGROUND))
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
					_goDownJump = true;
				}
			}
		}
		if (_tiles[_downStateCheck[i]].object == OBJ_GROUND)
		{
			if (_dungeonNum == 11)
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
						_goDownJump = true;

					}
				}
			}
			else
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
						_goDownJump = false;

					}
				}
				else
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
						_goDownJump = false;
					}
				}
			}
		}
	}
}

void Player::pixelCollision()
{
	for (int j = _y + 20; j < _y + 70; ++j)
	{	COLORREF color = RGB(0,0,0);

		if(_dungeonNum == 1) color = GetPixel(IMAGEMANAGER->findImage("����2�ȼ�")->getMemDC(), _x, j);
		if(_dungeonNum == 4) color = GetPixel(IMAGEMANAGER->findImage("����5�ȼ�")->getMemDC(), _x, j);
		if (_dungeonNum == 10) color = GetPixel(IMAGEMANAGER->findImage("����10�ȼ�")->getMemDC(), _x, j);
		if(_dungeonNum == 11) color = GetPixel(IMAGEMANAGER->findImage("pixelTown")->getMemDC(), _x, j);
		
		if (_dungeonNum == 11)
		{
			if (!_isDashing)
			{
				int r = GetRValue(color), g = GetGValue(color), b = GetBValue(color);

				if (r == 0 && g == 255 && b == 0)
				{
					if (KEYMANAGER->isOnceKeyDown(VK_SPACE))_isJumping = true;
					else
					{
						_y = j - 50;
						_isJumping = false;
						_goDownJump = true;
					}
					break;
				}
			}
		}
		else
		{
			int r = GetRValue(color), g = GetGValue(color), b = GetBValue(color);

			if (r == 0 && g == 255 && b == 0)
			{
				if (KEYMANAGER->isOnceKeyDown(VK_SPACE))_isJumping = true;
				else
				{
					_y = j - 50;
					_isJumping = false;
					_goDownJump = false;
				}
				break;
			}

		}
	}
}

void Player::itemInfo()
{
	if (_inven->getMainWeapon().size() > _youUsingCount)
	{
		_playerWeapon = _inven->getMainWeapon()[_youUsingCount]->equipmentImage();
		if (_inven->getMainWeapon()[_youUsingCount]->getItemType() == GUN)
		{
			char str1[128];
			if (_isLeftAttack)sprintf_s(str1, "��%d��", _inven->getMainWeapon()[_youUsingCount]->getItemValue());
			else if (!_isLeftAttack)sprintf_s(str1, "��%d��", _inven->getMainWeapon()[_youUsingCount]->getItemValue());
			_playerWeapon = IMAGEMANAGER->findImage(str1);
		}
		
	
		RECT rc = RectMake(0, 0, _playerWeapon->getWidth() * 2, _playerWeapon->getHeight());
		imageDC->rotateInit(rc.right - rc.left, rc.bottom - rc.top, true, RGB(0, 0, 0), false);
		
		
		if (_inven->getMainWeapon()[_youUsingCount]->getItemType() == SWORD)
		{
			_isGun = false;
			if (_inven->getMainWeapon()[_youUsingCount]->getItemValue() == 3)
				_attackEffect = IMAGEMANAGER->findImage("��2ȿ��");
			else if (_inven->getMainWeapon()[_youUsingCount]->getItemValue() == 8)
				_attackEffect = IMAGEMANAGER->findImage("��4ȿ��");
			else if (_inven->getMainWeapon()[_youUsingCount]->getItemValue() == 5)
				_attackEffect = IMAGEMANAGER->findImage("��3ȿ��");
			else _attackEffect = IMAGEMANAGER->findImage("��1ȿ��");
		}
		else if (_inven->getMainWeapon()[_youUsingCount]->getItemType() == GUN
			|| _inven->getMainWeapon()[_youUsingCount]->getItemType() == BOW)
		{
			_isGun = true;
			//�⺻��  ����� �÷��Ӱ� ���ϰ� 
			for (int i = 1; i < 5; ++i)
			{
				if (_inven->getMainWeapon()[_youUsingCount]->getItemValue() == i
					&& _inven->getMainWeapon()[_youUsingCount]->getItemType() == GUN)
				{
					_bulletType = i - 1;
					break;
				}
				else if (_inven->getMainWeapon()[_youUsingCount]->getItemType() == BOW) _bulletType = 4;
			}
		}
		
	}


	//1. �⺻ , 2 . ���󸶻� , 3. ȭ���� , 4.¡�׷��� ����� ,5.���޶����  6. ���ͳ� ������ , 7 . ������ 8. ������ ,9.�����,10 ������
	
																			   

}
