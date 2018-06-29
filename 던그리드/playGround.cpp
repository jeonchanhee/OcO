#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{

}

HRESULT playGround::init(void)	
{
	gameNode::init(true);
	Image_init();
	_mapTool = new MapTool;
	_mapTool->init();


	SCENEMANAGER->addScene("Ÿ��Ʋ", new titleScene);
	SCENEMANAGER->addScene("����", new dungeonScene);

	SCENEMANAGER->changeScene("Ÿ��Ʋ");

	return S_OK;
}

void playGround::release(void)	
{
	gameNode::release();

	
}

void playGround::update(void)	
{
	gameNode::update();
	//SCENEMANAGER->update();
	_mapTool->update();
}

void playGround::render(void)
{
	
	//�����ȭ�� �� �� ��Ƶд�
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//============== �� ���δ� �ǵ帮�� ���� ==============
	
	
	//SCENEMANAGER->render();
	
	_mapTool->render();
	
	//================�� �����ε� �ǵ帮�� ���� =============
	this->getBackBuffer()->render(getHDC(), 0, 0);
	IMAGEMANAGER->render("cursor", getHDC(), _ptMouse.x, _ptMouse.y);
}

