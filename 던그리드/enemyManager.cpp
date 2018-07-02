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
	Enemy* dogBone;
	dogBone = new DogBone;
	dogBone->init();

	_vMonster.push_back(dogBone);

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
