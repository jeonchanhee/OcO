#include "stdafx.h"
#include "RandomDungeon1.h"


RandomDungeon1::RandomDungeon1()
{
}


RandomDungeon1::~RandomDungeon1()
{
}

HRESULT RandomDungeon1::init()
{
	save();

	SCENEMANAGER->addScene("������1", new dungeon1Scene);
	SCENEMANAGER->addScene("������2", new dungeon2Scene);
	SCENEMANAGER->addScene("������3", new dungeon3Scene);
	SCENEMANAGER->addScene("������4", new dungeon4Scene);
	SCENEMANAGER->addScene("������5", new dungeon5Scene);
	SCENEMANAGER->addScene("������6", new dungeon6Scene);
	SCENEMANAGER->addScene("������7", new dungeon7Scene);
	SCENEMANAGER->addScene("������8", new dungeon8Scene);
	SCENEMANAGER->addScene("������9", new bossScene);
	SCENEMANAGER->addScene("������10", new foodScene);
	SCENEMANAGER->addScene("������11", new weaponScene);

	SCENEMANAGER->changeScene("������1");
	return S_OK;
}

void RandomDungeon1::update()
{
}

void RandomDungeon1::render()
{
}

void RandomDungeon1::release()
{
}

void RandomDungeon1::keyControl()
{
}

void RandomDungeon1::save()
{
	vector<string> vStr;
	char str[128] = "";
	vStr.push_back(itoa(1, str, 10));
	for (int i = 0; i < 11; i++)
	{
		if (i == 0 || i == 1 || i == 2 || i == 3 || i == 6 || i == 7)
			vStr.push_back("F");
		else
			vStr.push_back("N");
	}
	/*vStr.push_back(itoa(2, str, 10));
	for (int i = 0; i < 11; i++)
	{
	if (i == 0 || i == 5 || i == 6 || i == 7 || i == 10)
	vStr.push_back("F");
	else
	vStr.push_back("N");
	}*/
	//vStr.push_back(itoa(3, str, 10));
	//for (int i = 0; i < 11; i++)
	//{
	//if (i == 0 || i == 2 || i == 4 || i == 6 || i == 7 || i == 10)
	//	vStr.push_back("F");
	//else
	//	vStr.push_back("N");
	//}
	/*vStr.push_back(itoa(4, str, 10));
	for (int i = 0; i < 11; i++)
	{
		if (i == 0 || i == 2 || i == 4 || i == 5 || i == 6 || i == 7 || i == 9 || i == 10)
			vStr.push_back("F");
		else
			vStr.push_back("N");
	}*/
	TXTDATA->txtSave("infoDungeon.txt",vStr);
}
