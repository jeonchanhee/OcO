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
	//������ �ٸ��� �Լ�() �ڿ� ��ȣ�� ������ �ʴ´�
	_btnSceneChange = new button;
	_btnSceneChange->init("��ư", WINSIZEX / 2, WINSIZEY / 2,
		PointMake(0, 1), PointMake(0, 0), cbSceneChange);



	return S_OK;
}

void selectScene::release()
{
}

void selectScene::update()
{
	//if (KEYMANAGER->isOnceKeyDown(VK_F1)) SCENEMANAGER->changeScene("��Ÿ��");
	_btnSceneChange->update();
}

void selectScene::render()
{
	char str[128];
	sprintf_s(str, "����Ʈ ������������");
	TextOut(getMemDC(), WINSIZEX / 2 + 150, WINSIZEY / 2 - 200, str, strlen(str));

	_btnSceneChange->render();
}

void selectScene::cbSceneChange()
{
	SCENEMANAGER->changeScene("��Ÿ��");
}
