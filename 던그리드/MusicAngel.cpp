#include "stdafx.h"
#include "MusicAngel.h"


MusicAngel::MusicAngel()
{
}


MusicAngel::~MusicAngel()
{
}

HRESULT MusicAngel::init(float x, float y)
{
	_x = x;
	_y = y;

	_img = IMAGEMANAGER->findImage("bansheeIdleAttack");

	_musicAngelDirection = MUSICANGEL_LEFT_MOVE;
	//_musicAngelDirection = MUSICANGEL_RIGHT_MOVE;

	//MOVE
	KEYANIMANAGER->addCoordinateFrameAnimation("musicAngelRightMove", "bansheeIdleAttack", 0, 5, 4, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("musicAngelLeftMove", "bansheeIdleAttack", 6, 11, 4, false, true);
	
	//ATTACK
	KEYANIMANAGER->addCoordinateFrameAnimation("musicAngelRightAttack", "bansheeIdleAttack", 12, 17, 2, false, false, rightAttack, this);
	KEYANIMANAGER->addCoordinateFrameAnimation("musicAngelLeftAttack", "bansheeIdleAttack", 18, 23, 2, false, false, leftAttack, this);

	//DIE
	KEYANIMANAGER->addCoordinateFrameAnimation("musicAngelDie", "dieEffect", 2, 10, 5, false, false);

	_musicAngelMotion = KEYANIMANAGER->findAnimation("musicAngelLeftMove");
	//_musicAngelMotion = KEYANIMANAGER->findAnimation("musicAngelRightMove");
	_musicAngelMotion->start();

	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

	//음표요정 체력 초기화
	_progressBar = new progressBar;
	_progressBar->init(_x - 30, _y + 50, 70, 10, "음표요정앞", "음표요정뒤", BAR_MONSTER);
	_currentHP = _maxHP = 100;

	return S_OK;
}

void MusicAngel::release()
{
}

void MusicAngel::update()
{
	//음표요정 체력 업데이트
	_progressBar->setX(_x - 30);
	_progressBar->setY(_y + 50);
	_progressBar->setGauge(_currentHP, _maxHP);
	_progressBar->update();

	attackMove();

	//////////////////////DIE 테스트///////////////////////
	if (KEYMANAGER->isOnceKeyDown(VK_F7))
	{
		{
			if (_musicAngelDirection == MUSICANGEL_RIGHT_MOVE || _musicAngelDirection == MUSICANGEL_LEFT_MOVE)
				_img = IMAGEMANAGER->findImage("musicAngelDie");
			changeAnimation(MUSICANGEL_DIE);
		}
	}
	/*if (KEYMANAGER->isOnceKeyUp(VK_F7))
	{
		if (_musicAngelDirection == MUSICANGEL_DIE)
		{
			_img = IMAGEMANAGER->findImage("musicAngelDie");
			changeAnimation(MUSICANGEL_RIGHT_MOVE);
		}
	}*/
	////////////////////▲▲▲▲▲▲▲▲▲▲▲▲//////////////////////

	//KEYANIMANAGER->update();
	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
}

void MusicAngel::render()
{
	if (KEYMANAGER->isToggleKey('V'))
	{
		Rectangle(DC, _rc.left, _rc.top, _rc.right, _rc.bottom);
	}
	_progressBar->render();
	_img->aniRender(DC, _rc.left, _rc.top, _musicAngelMotion);
}

void MusicAngel::attackMove()
{
	_count++;
	if (!(_count % 200))
	{
		if (_musicAngelDirection == MUSICANGEL_RIGHT_MOVE)
			changeAnimation(MUSICANGEL_RIGHT_ATTACK);
		if (_musicAngelDirection == MUSICANGEL_LEFT_MOVE)
			changeAnimation(MUSICANGEL_LEFT_ATTACK);

		_count = 0;
	}
}

void MusicAngel::rightAttack(void * obj)
{
	MusicAngel* ma = (MusicAngel*)obj;

	ma->_img = IMAGEMANAGER->findImage("bansheeIdleAttack");
	ma->setMusicAngelDirection(MUSICANGEL_RIGHT_MOVE);
	ma->setMusicAngelMotion(KEYANIMANAGER->findAnimation("musicAngelRightMove"));
	ma->getMusicAngelMotion()->start();
}

void MusicAngel::leftAttack(void * obj)
{
	MusicAngel* ma = (MusicAngel*)obj;

	ma->_img = IMAGEMANAGER->findImage("bansheeIdleAttack");
	ma->setMusicAngelDirection(MUSICANGEL_LEFT_MOVE);
	ma->setMusicAngelMotion(KEYANIMANAGER->findAnimation("musicAngelLeftMove"));
	ma->getMusicAngelMotion()->start();
}

void MusicAngel::changeAnimation(MUSICANGELDIRECTION musicAngelDirection)
{
	switch (musicAngelDirection)
	{
	case MUSICANGEL_RIGHT_MOVE:
		_img = IMAGEMANAGER->findImage("bansheeIdleAttack");
		_musicAngelDirection = MUSICANGEL_RIGHT_MOVE;
		_musicAngelMotion = KEYANIMANAGER->findAnimation("musicAngelRightMove");
		_musicAngelMotion->start();
		_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	case MUSICANGEL_LEFT_MOVE:
		_img = IMAGEMANAGER->findImage("bansheeIdleAttack");
		_musicAngelDirection = MUSICANGEL_LEFT_MOVE;
		_musicAngelMotion = KEYANIMANAGER->findAnimation("musicAngelLeftMove");
		_musicAngelMotion->start();
		_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	case MUSICANGEL_RIGHT_ATTACK:
		_img = IMAGEMANAGER->findImage("bansheeIdleAttack");
		_musicAngelDirection = MUSICANGEL_RIGHT_ATTACK;
		_musicAngelMotion = KEYANIMANAGER->findAnimation("musicAngelRightAttack");
		_musicAngelMotion->start();
		_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	case MUSICANGEL_LEFT_ATTACK:
		_img = IMAGEMANAGER->findImage("bansheeIdleAttack");
		_musicAngelDirection = MUSICANGEL_LEFT_ATTACK;
		_musicAngelMotion = KEYANIMANAGER->findAnimation("musicAngelLeftAttack");
		_musicAngelMotion->start();
		_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	case MUSICANGEL_DIE:
		_img = IMAGEMANAGER->findImage("dieEffect");
		_musicAngelDirection = MUSICANGEL_DIE;
		_musicAngelMotion = KEYANIMANAGER->findAnimation("musicAngelDie");
		_musicAngelMotion->start();
		_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
		break;
	}
}

void MusicAngel::playerCollision()
{
}

void MusicAngel::hitDamage(float damage)
{
	_currentHP -= damage;
}
