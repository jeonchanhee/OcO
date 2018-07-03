#include "stdafx.h"
#include "EnemyManager.h"


EnemyManager::EnemyManager()
{
}


EnemyManager::~EnemyManager()
{
}

HRESULT EnemyManager::init()
{
	//Enemy* dogBone;
	//dogBone = new DogBone;
	//dogBone->init();
	//_vMonster.push_back(dogBone);

	//Enemy* bigBone;
	//bigBone = new BigBone;
	//bigBone->init();
	//_vMonster.push_back(bigBone);

	//Enemy* bat;
	//bat = new Bat;
	//bat->init();
	//_vMonster.push_back(bat);

	//Enemy* redBat;
	//redBat = new RedBat;
	//redBat->init();
	//_vMonster.push_back(redBat);

	//Enemy* bigBat;
	//bigBat = new BigBat;
	//bigBat->init();
	//_vMonster.push_back(bigBat);

	Enemy* bigRedBat;
	bigRedBat = new BigRedBat;
	bigRedBat->init();
	_vMonster.push_back(bigRedBat);


	return S_OK;
}

void EnemyManager::release()
{
}

void EnemyManager::update()
{
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		(*_viMonster)->update();
	}
}

void EnemyManager::render()
{
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		(*_viMonster)->render();
	}
}

void EnemyManager::setMonster()
{
}
