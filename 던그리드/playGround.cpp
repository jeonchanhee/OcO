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


	SCENEMANAGER->addScene("타이틀", new titleScene);
	SCENEMANAGER->addScene("던전", new dungeonScene);

	SCENEMANAGER->changeScene("타이틀");

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
	
	//흰색도화지 한 장 깔아둔다
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//============== 이 위로는 건드리지 말자 ==============
	
	
	//SCENEMANAGER->render();
	
	_mapTool->render();
	
	//================이 밑으로도 건드리지 말자 =============
	this->getBackBuffer()->render(getHDC(), 0, 0);
	IMAGEMANAGER->render("cursor", getHDC(), _ptMouse.x, _ptMouse.y);
}

