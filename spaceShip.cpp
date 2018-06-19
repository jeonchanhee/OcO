#include "stdafx.h"
#include "spaceShip.h"
#include "enemyManager.h"

spaceShip::spaceShip()
{
}


spaceShip::~spaceShip()
{
}

HRESULT spaceShip::init()
{
	_ship = IMAGEMANAGER->addImage("우주선", "rocket.bmp", 52, 64, true, RGB(255, 0, 255));
	_ship->setX(WINSIZEX / 2);			//우주선 X좌표 셋팅
	_ship->setY(WINSIZEY / 2 + 200);	//우주선 Y좌표 셋팅

	_missile = new missile;
	_missile->init(20, 400);

	_hoooo = new minho;
	_hoooo->init(3000, 500);

	_hpBar = new progressBar;
	_hpBar->init(_ship->getX(), _ship->getY() - 10, _ship->getWidth(), 10);
	_currentHP = _maxHP = 100;

	_alphaValue = 255;

	return S_OK;
}

void spaceShip::release()
{
}

void spaceShip::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _ship->getX() > 0)
	{
		_ship->setX(_ship->getX() - 5);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _ship->getX() + _ship->getWidth() < WINSIZEX)
	{
		_ship->setX(_ship->getX() + 5);
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP) && _ship->getY() > 0)
	{
		_ship->setY(_ship->getY() - 5);
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _ship->getY() + _ship->getHeight() < WINSIZEY)
	{
		_ship->setY(_ship->getY() + 5);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_missile->fire(_ship->getCenterX(), _ship->getCenterY() - 20);
	}

	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		_hoooo->fire(_ship->getCenterX(), _ship->getCenterY() - 20);
	}

	_missile->update();
	_hoooo->update();

	_hpBar->setX(_ship->getX());
	_hpBar->setY(_ship->getY() - 20);
	_hpBar->setGauge(_currentHP, _maxHP);

	_hpBar->update();
	collision();

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		char temp[128];
		vector<string> vStr;

		vStr.push_back(itoa(_currentHP, temp, 10));
		vStr.push_back(itoa(_maxHP, temp, 10));
		vStr.push_back(itoa(_ship->getX(), temp, 10));
		vStr.push_back(itoa(_ship->getY(), temp, 10));

		TXTDATA->txtSave("세이브테스트.txt", vStr);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		vector<string> vStr;

		vStr = TXTDATA->txtLoad("세이브테스트.txt");

		_currentHP = (atoi(vStr[0].c_str()));
		_maxHP = (atoi(vStr[1].c_str()));
		_ship->setX(atoi(vStr[2].c_str()));
		_ship->setY(atoi(vStr[3].c_str()));
	}

	_alphaValue--;

	if (_alphaValue < 55) _alphaValue = 55;


}

void spaceShip::render()
{
	_ship->alphaRender(getMemDC(), _ship->getX(), _ship->getY(), _alphaValue);

	_missile->render();
	_hoooo->render();

	_hpBar->render();
}

void spaceShip::collision()
{
	for (int i = 0; i < _hoooo->getVMinho().size(); i++)
	{
		for (int j = 0; j < _em->getVMinion().size(); j++)
		{
			RECT rc;
			if (IntersectRect(&rc, &_hoooo->getVMinho()[i].rc, &_em->getVMinion()[j]->getRect()))
			{
				_hoooo->removeMinho(i);
				_em->removeMinion(j);
				break;
			}
		}
	}
}

void spaceShip::hitDamage(float damage)
{
	_currentHP -= damage;
}
