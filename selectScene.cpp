#include "stdafx.h"
#include "selectScene.h"


selectScene::selectScene()
{
}


selectScene::~selectScene()
{
}

HRESULT selectScene::init()
{
	//기존과 다르게 함수() 뒤에 괄호를 붙이지 않는다
	_btnSceneChange = new button;
	_btnSceneChange->init("버튼", WINSIZEX / 2, WINSIZEY / 2,
		PointMake(0, 1), PointMake(0, 0), cbSceneChange);



	return S_OK;
}

void selectScene::release()
{
}

void selectScene::update()
{
	//if (KEYMANAGER->isOnceKeyDown(VK_F1)) SCENEMANAGER->changeScene("스타씬");
	_btnSceneChange->update();
}

void selectScene::render()
{
	char str[128];
	sprintf_s(str, "셀렉트 씨이이이이인");
	TextOut(getMemDC(), WINSIZEX / 2 + 150, WINSIZEY / 2 - 200, str, strlen(str));

	_btnSceneChange->render();
}

void selectScene::cbSceneChange()
{
	SCENEMANAGER->changeScene("스타씬");
}
