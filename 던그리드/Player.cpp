#include "stdafx.h"
#include "Player.h"



Player::Player()
{

}
Player::~Player() {}

HRESULT Player::init()
{

	_player = IMAGEMANAGER->findImage("�⺻�÷��̾�");
	_playerHand[0] = IMAGEMANAGER->findImage("�÷��̾��");
	_playerHand[1] = IMAGEMANAGER->findImage("�÷��̾��");
	_playerWeapon = IMAGEMANAGER->findImage("�����÷��̾�");

	_x = WINSIZEX / 2; _y = WINSIZEY / 2;
	_count = 0;
	_mouseAngle = 0;

	_jumpPower = 12.0f;
	_moveMentSpeed = 3.0f;
	_direction = RIGHT_STOP;

	int rightStop[] = { 0,1,2,3,4 };
	KEYANIMANAGER->addArrayFrameAnimation("�����ʺ����ֱ�", "�⺻�÷��̾�", rightStop, 5, 10, true);
	int rightRun[] = { 8 ,9 ,10 ,11 ,12 ,13 ,14 ,15 }; 
	KEYANIMANAGER->addArrayFrameAnimation("�����ʶٱ�", "�⺻�÷��̾�", rightRun, 8, 10, true);
	int rightJump[] = { 5 };
	KEYANIMANAGER->addArrayFrameAnimation("����������", "�⺻�÷��̾�", rightJump, 1, 10, true);
	int rightDie[] = { 6,7 };
	KEYANIMANAGER->addArrayFrameAnimation("����������", "�⺻�÷��̾�", rightDie, 2, 10, true);

	int leftStop[] = {19, 20 ,21 ,22 ,23};
	KEYANIMANAGER->addArrayFrameAnimation("���ʺ����ֱ�", "�⺻�÷��̾�", leftStop, 5, 10, true);
	int leftRun[] = { 24, 25 ,26 ,27 ,28 ,29 ,30 , 31 };
	KEYANIMANAGER->addArrayFrameAnimation("���ʶٱ�", "�⺻�÷��̾�", leftRun, 8, 10, true);
	int leftJump[] = { 18 };
	KEYANIMANAGER->addArrayFrameAnimation("��������", "�⺻�÷��̾�", leftJump, 1, 10, true);
	int leftDie[] = { 16 ,17 };
	KEYANIMANAGER->addArrayFrameAnimation("��������", "�⺻�÷��̾�", leftDie, 2, 10, true);

	_playerAnimation = KEYANIMANAGER->findAnimation("�����ʺ����ֱ�");
	_direction = RIGHT_STOP;
	return S_OK;
}

void Player::release(){}

void Player::update()
{
	keyInput();
	move();
	mouseControl();
}

void Player::render() 
{
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
	
}



void Player::keyAnimation(){}

void Player::keyInput()
{
	KEYANIMANAGER->update();

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
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		_dashSpeed = DASHSPEED;
		_isDashing = true;
		_dashX = _ptMouse.x, _dashY = _ptMouse.y;
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
	}

	if (_isDashing)
	{
		_dashSpeed -= 2.0f;
		_x += cosf(getAngle(_x, _y, _dashX, _dashY)) * _dashSpeed;
		_y += -sinf(getAngle(_x, _y, _dashX, _dashY)) * _dashSpeed;
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
}

void Player::keyMouse()
{
}

void Player::leftJump(void * obj)
{
}

void Player::rightJump(void * obj)
{
}

