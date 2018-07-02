#include "stdafx.h"
#include "playGround.h"


playGround::playGround(){}
playGround::~playGround(){}


HRESULT playGround::init(void)	
{
	mode = 맵툴;				//본인이 편집하는 부분으로 이넘에 추가하고 수정해서 사용하기!!


	gameNode::init(true);
	//Image_init();
	//Sound_init();
	//_mapTool = new MapTool;
	//_mapTool->init();
	//_player  = new Player;
	//_player->init();
	_im = new itemManager;
	_im->init();


	SCENEMANAGER->addScene("타이틀", new titleScene);
	SCENEMANAGER->addScene("던전", new dungeonScene);
	SCENEMANAGER->addScene("도그본", new EnemyManager);
	SCENEMANAGER->addScene("대사씬", new Dialog);
	
	switch (mode)
	{
	case 맵툴:

		break;
	case 타이틀:
		SCENEMANAGER->changeScene("타이틀");
		break;
	case 다이얼로그:
		SCENEMANAGER->changeScene("대사씬");
		break;
	case 도그본:
		SCENEMANAGER->changeScene("도그본");
		break;
	case 플레이어:
		break;
	case 아이템:
		break;

	case 기타추가하셈:
		break;
	default:
		break;
	}

	return S_OK;
}

void playGround::release(void)	
{
	gameNode::release();

	
}

void playGround::update(void)	
{
	gameNode::update();

	_mapTool->update();
	_player->update();
	SCENEMANAGER->update();

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SOUNDMANAGER->play("title");
	}

	if (KEYMANAGER->isStayKeyDown('D') && CAMERAMANAGER->getCameraRc2().right<BACKGROUNDSIZEX) CAMERAMANAGER->setCameraX2(CAMERAMANAGER->getCameraX2() + 50);
	if (KEYMANAGER->isStayKeyDown('S') && CAMERAMANAGER->getCameraRc2().bottom<BACKGROUNDSIZEY) CAMERAMANAGER->setCameraY2(CAMERAMANAGER->getCameraY2() + 50);
	if (KEYMANAGER->isStayKeyDown('A') && CAMERAMANAGER->getCameraRc2().left>0) CAMERAMANAGER->setCameraX2(CAMERAMANAGER->getCameraX2() - 50);
	if (KEYMANAGER->isStayKeyDown('W') && CAMERAMANAGER->getCameraRc2().top>0) CAMERAMANAGER->setCameraY2(CAMERAMANAGER->getCameraY2() - 50);

}

void playGround::render(void)
{
	
	//흰색도화지 한 장 깔아둔다
	//PatBlt(DC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS); // 카메라 매니저 DC -> getMemDC 로 바꾸었습니다.
	PatBlt(DC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS); // 카메라 매니저 DC -> getMemDC 로 바꾸었습니다.
	
	//============== 이 위로는 건드리지 말자 ==============
	
	switch (mode)
	{
	case 맵툴:
		PatBlt(DC2, 0, 0, BACKGROUNDSIZEX, BACKGROUNDSIZEY, WHITENESS);
		_mapTool->render();
		CAMERAMANAGER->getCameraDC2()->render(DC, 0, 0, CAMERAMANAGER->getCameraRc2().left, CAMERAMANAGER->getCameraRc2().top, CAMERA2X, CAMERA2Y);
		break;
	case 타이틀:
		SCENEMANAGER->render();
		break;
	case 다이얼로그:
		SCENEMANAGER->render();
		break;
	case 도그본:
		SCENEMANAGER->render();
		break;
	case 플레이어:
		_player->render();
		break;
	case 아이템:
		_im->render();
		break;

	case 기타추가하셈:
		break;
	default:
		break;
	}

	//================이 밑으로도 건드리지 말자 =============
	
	IMAGEMANAGER->render("cursor", DC, _ptMouse.x, _ptMouse.y);
	CAMERAMANAGER->getCameraDC()->render(getHDC() , 0 , 0 , CAMERAMANAGER->getCameraRc().left, CAMERAMANAGER->getCameraRc().top, CAMERAMANAGER->getCameraRc().right, CAMERAMANAGER->getCameraRc().bottom); 
	
	// 맨마지막으로 카메라 매니저 의 DC를 그려줍니다.
	// CAMERAMANAGER->setCameraX()  CAMERAMANAGER->setCameraY() 를 이용하면   X ,Y 에  WINSIZEX , WINSIZEY 만큼 화면에 그려주고있는 렉트를 이동시킬 수 있음 .
	// 그리고 모든 렌더의 hdc 는 CAMERAMANAGER->getCameraDC()->getMemDC() 로 해주어야함 !~~!!$!$!#ㄸ!#ㄸ!$!$#@$!@#@!
}
 