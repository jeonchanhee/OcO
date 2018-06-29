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
//	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) CAMERAMANAGER->setCameraX(CAMERAMANAGER->getCameraX() - 5);

}

void playGround::render(void)
{
	
	//흰색도화지 한 장 깔아둔다
	PatBlt(DC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS); // 카메라 매니저 DC -> getMemDC 로 바꾸었습니다.
	//============== 이 위로는 건드리지 말자 ==============
	
	_mapTool->render();
	//SCENEMANAGER->render();

	
	//================이 밑으로도 건드리지 말자 =============
	IMAGEMANAGER->render("cursor", DC, _ptMouse.x, _ptMouse.y);
	CAMERAMANAGER->getCameraDC()->render(getHDC() , 0 , 0 , CAMERAMANAGER->getCameraRc().left, CAMERAMANAGER->getCameraRc().top, CAMERAMANAGER->getCameraRc().right, CAMERAMANAGER->getCameraRc().bottom); 
	// 맨마지막으로 카메라 매니저 의 DC를 그려줍니다.
	// CAMERAMANAGER->setCameraX()  CAMERAMANAGER->setCameraY() 를 이용하면   X ,Y 에  WINSIZEX , WINSIZEY 만큼 화면에 그려주고있는 렉트를 이동시킬 수 있음 .
	// 그리고 모든 렌더의 hdc 는 CAMERAMANAGER->getCameraDC()->getMemDC() 로 해주어야함 !~~!!$!$!#ㄸ!#ㄸ!$!$#@$!@#@!
	
	

}
 