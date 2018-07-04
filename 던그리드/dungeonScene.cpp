#include "stdafx.h"
#include "dungeonScene.h"
#include "tileNode.h"


dungeonScene::dungeonScene() {}

dungeonScene::~dungeonScene() {}


HRESULT dungeonScene::init(void)
{
	
	return S_OK;
}

void dungeonScene::release(void)
{

}

void dungeonScene::update(void)
{
	KEYANIMANAGER->update();
}

void dungeonScene::render(void)
{

}

void dungeonScene::mapload()
{
	HANDLE	file;
	DWORD	load;

	
}



