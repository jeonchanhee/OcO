#include "stdafx.h"
#include "inGameScene.h"


inGameScene::inGameScene()
{
}


inGameScene::~inGameScene()
{
}

HRESULT inGameScene::init()
{
	return S_OK;
}

void inGameScene::release()
{
}

void inGameScene::update()
{
}

void inGameScene::render()
{
	IMAGEMANAGER->render("�ΰ���", getMemDC(), 0, 0);
}
