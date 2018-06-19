#include "stdafx.h"
#include "enemyManager.h"
#include "spaceShip.h"

enemyManager::enemyManager()
{
}


enemyManager::~enemyManager()
{

}

HRESULT enemyManager::init()
{
	_bullet = new bullet;
	_bullet->init("bullet", 30, 700);

	return S_OK;
}

void enemyManager::release()
{

}

void enemyManager::update()	
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->update();
	}
	minionBulletFire();
	_bullet->update();

	collision();
}

void enemyManager::render()	
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->render();
	}

	_bullet->render();
}


//적 생성함수
void enemyManager::setMinion(void)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			enemy* ufo;
			ufo = new minion;
			ufo->init("enemy", PointMake(80 + j * 80, 80 + i * 100));

			_vMinion.push_back(ufo);
		}
	}
}

//적이 총알을 발사하게 하는 함수
void enemyManager::minionBulletFire()
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		//발사 시점이 되었으면
		if ((*_viMinion)->bulletCountFire())
		{
			RECT rc = (*_viMinion)->getRect();
			/*
			_bullet->bulletFire(rc.left + (rc.right - rc.left) / 2,
				rc.bottom + 5, -(PI / 2), 7.0f);
			*/

			_bullet->bulletFire(rc.left + (rc.right - rc.left) / 2,
				rc.bottom + 5,
				getAngle(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.bottom - rc.top) / 2,
					_ship->getShipImage()->getCenterX(),
					_ship->getShipImage()->getCenterY()), 11.0f);

		}
	}
}

void enemyManager::removeMinion(int arrNum)
{
	SAFE_DELETE(_vMinion[arrNum]);
	_vMinion.erase(_vMinion.begin() + arrNum);
}

void enemyManager::collision()
{
	for (int i = 0; i < _bullet->getVBullet().size(); i++)
	{
		RECT rc;
		if(IntersectRect(&rc, &_bullet->getVBullet()[i].rc, 
			&_ship->getShipImage()->boundingBox()))
		{
			_ship->hitDamage(10.0f);
			_bullet->removeBullet(i);
			break;
		}
		
	}
}

