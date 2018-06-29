#include "stdafx.h"
#include "Player.h"


HRESULT Player::init()
{

	_player = IMAGEMANAGER->findImage("�⺻�÷��̾�");
	
	_x = WINSIZEX / 2; _y = WINSIZEY / 2;
	_count = 0;
	_moveMentSpeed = 3.0f;
	_jumpPower = 5.0f;
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
}

void Player::render() 
{
	_player->aniRender(CAMERAMANAGER->getCameraDC()->getMemDC(), _x, _y, _playerAnimation);
}



void Player::keyAnimation()
{

}

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
		_gravity = 0.05f;
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
}

void Player::move()
{
	_jump -= _gravity;  	_y -= _jump;
	if (_isJumping == false)
	{		
		_jump = 0;
		_gravity = 0.1;
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

Player::Player(){}

Player::~Player(){}
