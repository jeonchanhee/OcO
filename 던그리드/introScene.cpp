#include "stdafx.h"
#include "introScene.h"


introScene::introScene()
{
}


introScene::~introScene()
{
}

HRESULT introScene::init()
{
	SOUNDMANAGER->play("intro");
	return S_OK;
}

void introScene::release()
{
}

void introScene::update()
{
	if(!SOUNDMANAGER->isPlaySound("intro"))
		SCENEMANAGER->changeScene("Å¸ÀÌÆ²");
}

void introScene::render()
{
	IMAGEMANAGER->render("black", DC, 0, 0);
}
