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

	return S_OK;
}

void MusicAngel::release()
{
}

void MusicAngel::update()
{
	attackMove();

	//////////////////////DIE ┼╫╜║╞о///////////////////////
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
	////////////////////бубубубубубубубубубубубу//////////////////////

	KEYANIMANAGER->update();
	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
}

void MusicAngel::render()
{
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