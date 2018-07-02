#include "stdafx.h"
#include "Player.h"



Player::Player()
{

}
Player::~Player() {}


HRESULT Player::init()
{
	_player			= IMAGEMANAGER->findImage("�⺻�÷��̾�");
	_playerHand[0]  = IMAGEMANAGER->findImage("�÷��̾��");
	_playerHand[1]  = IMAGEMANAGER->findImage("�÷��̾��");
	_playerWeapon   = IMAGEMANAGER->findImage("�����÷��̾�");
	_x = WINSIZEX / 2; _y = WINSIZEY / 2;
	_count = 0;  _mouseAngle = 0;

	_currentHp = 80; _maxHp = 80;
	_currentDash = 2; _maxDash = 2;
	_armor = 0;
	_currentFullNess = 0; _maxFullNess = 100;
	_jumpPower = 12.0f;
	_moveMentSpeed = 3.0f;
	_direction = RIGHT_STOP;
	_gold = 0;
	_jumpMax = 1; _jumpCount = 0;
	_fixedDamage = 0;
	_youUsingCount = 0;

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
	
	//equipment
	for (int i = 0; i < 2; ++i)
	{
		_mainWeapon[i] = 0;
		_assistWeapon[i] = 0;
	}
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
	KEYANIMANAGER->update();
	EFFECTMANAGER->update();
}

void Player::render()
{
	EFFECTMANAGER->render();
	if (_direction == LEFT_RUN || _direction == LEFT_STOP)
	{
		_playerHand[0]->rotateRender(DC, _x + 15 , _y + 60 , _mouseAngle);
		_playerHand[1]->render(DC, _x + 60 , _y + 60);
	}
	if (_direction == RIGHT_RUN || _direction == RIGHT_STOP)
	{
		 _playerHand[0]->render(DC, _x + 10 , _y + 60);
		 _playerHand[1]->rotateRender(DC, _x + 65 , _y + 60 , _mouseAngle);
	}
	_player->aniRender(CAMERAMANAGER->getCameraDC()->getMemDC(), _x, _y, _playerAnimation);
	char str[128]; sprintf_s(str, "���� �����ִ� �����ε��� : %d", _youUsingCount);
	TextOut(DC, _x -50 , _y - 50, str, strlen(str));
}

void Player::keyInput()
{
	if (KEYMANAGER->isOnceKeyDown('1')) _youUsingCount = 0;
	else if (KEYMANAGER->isOnceKeyDown('2')) _youUsingCount = 1;


	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		_direction = LEFT_RUN;
		_playerAnimation = KEYANIMANAGER->findAnimation("���ʶٱ�");
		_playerAnimation->start();

	}
	else if (KEYMANAGER->isOnceKeyUp('A'))
	{
		_direction = LEFT_STOP;
		_playerAnimation = KEYANIMANAGER->findAnimation("���ʺ����ֱ�");
		_playerAnimation->start();
	}

	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		_direction = RIGHT_RUN;
		_playerAnimation = KEYANIMANAGER->findAnimation("�����ʶٱ�");
		_playerAnimation->start();

	}
	else if (KEYMANAGER->isOnceKeyUp('D'))
	{
		_direction = RIGHT_STOP;
		_playerAnimation = KEYANIMANAGER->findAnimation("�����ʺ����ֱ�");
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
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		attack();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{	
		_dashSpeed = DASHSPEED;
		_isDashing = true;
		_angle = getAngle(_x, _y, CAMERAMANAGER->getCameraX() + _ptMouseX, CAMERAMANAGER->getCameraY() + _ptMouseY);
	}
	
}

void Player::mouseControl()
{
	_ptMouseX = CAMERAMANAGER->getCameraX() + _ptMouse.x, _ptMouseY = CAMERAMANAGER->getCameraY() + _ptMouse.y;
	_mouseAngle = getAngle(_x, _y, _ptMouse.x, _ptMouse.y);
	//ptmouse ��ǥ������ ������������ �������� ������ ���� 
	if (_x > _ptMouseX)
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
	else if (_x < _ptMouseX)
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

	}
}

void Player::attack()
{
	if (_mainWeapon[_youUsingCount] == 0)
	{
		if (_direction == LEFT_STOP || _direction == LEFT_RUN)
		{
			
		}
 	}
	
}

void Player::effect()
{
	if (KEYMANAGER->isStayKeyDown('A')) EFFECTMANAGER->play("���ʰ�����", _x + 70, _y + 70);
	if (KEYMANAGER->isStayKeyDown('D')) EFFECTMANAGER->play("�����ʰ�����", _x  , _y + 70);
	if (_isDashing) ++_count;
	if (_count > 5)
	{
		_count = 0;
		if (_x > _ptMouseX)
		{
			EFFECTMANAGER->play("��ÿ���", _x + 30 , _y +10 + _player->getFrameWidth() / 2);
		}
		else if (_x < _ptMouseX)
		{
			EFFECTMANAGER->play("��ÿ�����", _x + 20, _y + 10 +_player->getFrameWidth() / 2);
		}
	}
}



