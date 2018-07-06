#include "stdafx.h"
#include "dungeon7Scene.h"


dungeon7Scene::dungeon7Scene()
{
}


dungeon7Scene::~dungeon7Scene()
{
}

HRESULT dungeon7Scene::init()
{
	_isMapSet = true;
	chooseMap(8);
	selectSize(8);
	mapload();
	setCamera();
	setMonster();
	return S_OK;
}

void dungeon7Scene::update()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->update();
	}
}

void dungeon7Scene::setMonster()
{
	//»∞¿Ô¿Ã
	int id[4][2];
	id[0][0] = 630 % _temp, id[0][1] = 630 / _temp;
	id[1][0] = 495 % _temp, id[1][1] = 495 / _temp;
	id[2][0] = 484 % _temp, id[2][1] = 484 / _temp;
	id[3][0] = 209 % _temp, id[3][1] = 209 / _temp;
	for (int i = 0; i < 4; i++)
	{
		setArrow(id[i][0], id[i][1]);
	}

	//≈´∫∏π⁄
	setBigBat(555 % _temp, 555 / _temp);

	//¿Ω«•ø‰¡§
	setMusicAngel(530 % _temp, 530 / _temp);

	//º“
	setCow(346 % _temp, 346 / _temp);
	
	//∞≥ª¿
	id[2][0];
	id[0][0] = 142 % _temp, id[0][1] = 142 / _temp;
	id[1][0] = 159 % _temp, id[1][1] = 159 / _temp;
	for (int i = 0; i < 2; i++)
	{
		setDogBone(id[i][0], id[i][1]);
	}

	//¿€∫∏π⁄
	setBat(105 % _temp, 105 / _temp);

	//¿€ª°π⁄
	setRedBat(115 % _temp, 115 / _temp);

	//≈´ƒÆª¿
	id[4][0];
	id[0][0] = 743 % _temp, id[0][1] = 743 / _temp;
	id[1][0] = 756 % _temp, id[1][1] = 756 / _temp;
	id[2][0] = 747 % _temp, id[2][1] = 747 / _temp;
	id[3][0] = 750 % _temp, id[3][1] = 750 / _temp;
	for (int i = 0; i < 4; i++)
	{
		setBigBone(id[i][0], id[i][1], i);
	}

}
