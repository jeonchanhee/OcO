#include "stdafx.h"
#include "playGround.h"


playGround::playGround(){}
playGround::~playGround(){}


HRESULT playGround::init(void)	
{
	mode = 던전2;				//본인이 편집하는 부분으로 이넘에 추가하고 수정해서 사용하기!!
//	rectRotate(IMAGEMANAGER->findImage("검01"), 100, 100);


	gameNode::init(true);
	Image_init();
//	Sound_init();
	
	_mapTool = new MapTool;
	_mapTool->init();
	_player = new Player;
	_player->init();
	_im = new itemManager;
	_im->init();

	_title = new titleScene;
	_title->setImLink(_im);

	SCENEMANAGER->addScene("타이틀", _title);
	SCENEMANAGER->addScene("던전2", new dungeon2Scene);
	SCENEMANAGER->addScene("대사씬", new Dialog);
	SCENEMANAGER->addScene("아이템씬", new itemManager);
	SCENEMANAGER->addScene("인트로", new introScene);
	SCENEMANAGER->addScene("맵선택", new mapSelectScene);
	SCENEMANAGER->addScene("던전3", new dungeon3Scene);
	SCENEMANAGER->addScene("던전4", new dungeon4Scene);
	SCENEMANAGER->addScene("던전5", new dungeon5Scene);
	SCENEMANAGER->addScene("던전6", new dungeon6Scene);
	SCENEMANAGER->addScene("던전7", new dungeon7Scene);
	SCENEMANAGER->addScene("던전8", new dungeon8Scene);

	SCENEMANAGER->addScene("랜덤맵1", new RandomDungeon1);
	
	_randomScene1 = new RandomDungeon1;

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
	case 몬스터:
		SCENEMANAGER->changeScene("적");
		break;
	case 플레이어:
		break;
	case 아이템:
		SCENEMANAGER->changeScene("아이템씬");
		break;
	
	case 인트로:
		SCENEMANAGER->changeScene("인트로");
		break;
	case 던전2:
		SCENEMANAGER->changeScene("던전2");
		break;
	case 던전3:
		SCENEMANAGER->changeScene("던전3");
		break;
	case 던전4:
		SCENEMANAGER->changeScene("던전4");
		break;
	case 던전5:
		SCENEMANAGER->changeScene("던전5");
		break;
	case 던전6:
		SCENEMANAGER->changeScene("던전6");
		break;
	case 던전7:
		SCENEMANAGER->changeScene("던전7");
		break;
	case 던전8:
		SCENEMANAGER->changeScene("던전8");
		break;

	case 랜덤맵1:
		//SCENEMANAGER->changeScene("랜덤맵1");
		_randomScene1->init();
		break;

	case 맵선택:
		SCENEMANAGER->changeScene("맵선택");
		
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

	//_mapTool->update();
	_player->update();
	SCENEMANAGER->update();
	
	
	/*if (KEYMANAGER->isStayKeyDown('D') && CAMERAMANAGER->getCameraRc2().right<BACKGROUNDSIZEX) CAMERAMANAGER->setCameraX2(CAMERAMANAGER->getCameraX2() + 50);
	if (KEYMANAGER->isStayKeyDown('S') && CAMERAMANAGER->getCameraRc2().bottom<BACKGROUNDSIZEY) CAMERAMANAGER->setCameraY2(CAMERAMANAGER->getCameraY2() + 50);
	if (KEYMANAGER->isStayKeyDown('A') && CAMERAMANAGER->getCameraRc2().left>0) CAMERAMANAGER->setCameraX2(CAMERAMANAGER->getCameraX2() - 50);
	if (KEYMANAGER->isStayKeyDown('W') && CAMERAMANAGER->getCameraRc2().top>0) CAMERAMANAGER->setCameraY2(CAMERAMANAGER->getCameraY2() - 50);*/

	/*if (KEYMANAGER->isStayKeyDown('D') && CAMERAMANAGER->getCameraRc().right<96 * _tileX) CAMERAMANAGER->setCameraX(CAMERAMANAGER->getCameraX() + 50);
	if (KEYMANAGER->isStayKeyDown('S') && CAMERAMANAGER->getCameraRc().bottom<96 * _tileY) CAMERAMANAGER->setCameraY(CAMERAMANAGER->getCameraY() + 50);
	if (KEYMANAGER->isStayKeyDown('A') && CAMERAMANAGER->getCameraRc().left>0) CAMERAMANAGER->setCameraX(CAMERAMANAGER->getCameraX() - 50);
	if (KEYMANAGER->isStayKeyDown('W') && CAMERAMANAGER->getCameraRc().top>0) CAMERAMANAGER->setCameraY(CAMERAMANAGER->getCameraY() - 50);*/

	/*if (KEYMANAGER->isStayKeyDown('D') && CAMERAMANAGER->getCameraRc().right<96 * BACKGROUNDSIZEX) CAMERAMANAGER->setCameraX(CAMERAMANAGER->getCameraX() + 50);
	if (KEYMANAGER->isStayKeyDown('S') && CAMERAMANAGER->getCameraRc().bottom<96 * BACKGROUNDSIZEY) CAMERAMANAGER->setCameraY(CAMERAMANAGER->getCameraY() + 50);
	if (KEYMANAGER->isStayKeyDown('A') && CAMERAMANAGER->getCameraRc().left>0) CAMERAMANAGER->setCameraX(CAMERAMANAGER->getCameraX() - 50);
	if (KEYMANAGER->isStayKeyDown('W') && CAMERAMANAGER->getCameraRc().top>0) CAMERAMANAGER->setCameraY(CAMERAMANAGER->getCameraY() - 50);
*/


	if (KEYMANAGER->isStayKeyDown('D'))//&& CAMERAMANAGER->getCameraCenter().x+WINSIZEX/2<BACKGROUNDSIZEX)
		CAMERAMANAGER->setCameraCenter(PointMake(CAMERAMANAGER->getCameraCenter().x + 50, CAMERAMANAGER->getCameraCenter().y));
	if (KEYMANAGER->isStayKeyDown('S'))// && CAMERAMANAGER->getCameraCenter().y + WINSIZEY / 2<BACKGROUNDSIZEY)
		CAMERAMANAGER->setCameraCenter(PointMake(CAMERAMANAGER->getCameraCenter().x , CAMERAMANAGER->getCameraCenter().y + 50));
	if (KEYMANAGER->isStayKeyDown('A'))// && CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2>0)
		CAMERAMANAGER->setCameraCenter(PointMake(CAMERAMANAGER->getCameraCenter().x  - 50, CAMERAMANAGER->getCameraCenter().y));
	if (KEYMANAGER->isStayKeyDown('W'))// && CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2>0)
		CAMERAMANAGER->setCameraCenter(PointMake(CAMERAMANAGER->getCameraCenter().x , CAMERAMANAGER->getCameraCenter().y - 50));
	//
	//if (CAMERAMANAGER->getCameraX() < 0)						CAMERAMANAGER->setCameraX(0);
	//if (CAMERAMANAGER->getCameraY() < 0)						CAMERAMANAGER->setCameraY(0);
	//if (CAMERAMANAGER->getCameraX() + WINSIZEX > 96 * _tileX)	CAMERAMANAGER->setCameraX(96 * _tileX - WINSIZEX);
	//if (CAMERAMANAGER->getCameraY() + WINSIZEY > 96 * _tileY)	CAMERAMANAGER->setCameraY(96 * _tileY - WINSIZEY);
}

void playGround::render(void)
{
	PatBlt(getMemDC(), CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2, CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2, WINSIZEX, WINSIZEY, BLACKNESS);
	PatBlt(CAMERAMANAGER->getCameraDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);

	/////////////////////////////////////////////////////////////////////////////////////////////
	// 이 위로는 건들지 마시오
	switch (mode)
	{
	case 맵툴:
		//PatBlt(UIDC, 0, 0, BACKGROUNDSIZEX, BACKGROUNDSIZEY, BLACKNESS);

		/*
		_mapTool->render();
		if(KEYMANAGER->isToggleKey(VK_TAB))
		{
			IMAGEMANAGER->findImage("floor1")->render(DC, -23 * 96, 12 * 96);
			IMAGEMANAGER->findImage("floor2")->render(DC, 22 * 96, 12 * 96);
			IMAGEMANAGER->findImage("floor1")->render(DC, 57 * 96, 12 * 96);
			IMAGEMANAGER->findImage("floor0")->render(DC, 30 * 96, 17 * 96);
			IMAGEMANAGER->findImage("floor0")->render(DC, 36 * 96, 15 * 96);
		}
		*/
		break;
	case 타이틀:
		SCENEMANAGER->render();
		break;
	case 다이얼로그:
		SCENEMANAGER->render();
		break;
	case 몬스터:
		SCENEMANAGER->render();
		break;
	case 플레이어:
		_player->render();
		break;
	case 아이템:
		SCENEMANAGER->render();
		break;
	case 던전2: case 던전3: case 던전4: case 던전5: case 던전6: case 던전7: case 던전8:
	case 랜덤맵1:
		SCENEMANAGER->render();
		break;
	case 맵선택:
		SCENEMANAGER->render();
		break;
	
	case 기타추가하셈:
		break;
	default:
		break;
	}
	//SCENEMANAGER->render();

	//char str[128];
	//sprintf_s(str, "%d, %d", CAMERAMANAGER->getCameraCenter().x + WINSIZEX / 2, CAMERAMANAGER->getCameraCenter().y + WINSIZEY / 2);
	//TextOut(UIDC, 100, 100, str, strlen(str));
	//
	//char str2[128];
	//sprintf_s(str2, "%d %d /// %d, %d", _tileX, _tileY, _tileX * 96, _tileY * 96);
	//TextOut(UIDC, 100, 150, str2, strlen(str2));

	// 이 아래로도 건들지 마시오
	/////////////////////////////////////////////////////////////////////////////////////////////
	IMAGEMANAGER->render("cursor", UIDC, _ptMouse.x, _ptMouse.y);
	TIMEMANAGER->render(UIDC);

	IMAGEMANAGER->findImage("카메라DC")->render(DC, 54,240,CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, 600, 670);

	CAMERAMANAGER->render(this->getBackBuffer());
	this->getBackBuffer()->render(getHDC(), 0, 0, CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2, CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2, WINSIZEX, WINSIZEY);
	//IMAGEMANAGER->render("cursor", getHDC(), _ptMouse.x, _ptMouse.y);

	//흰색도화지 한 장 깔아둔다
	//PatBlt(DC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS); // 카메라 매니저 DC -> getMemDC 로 바꾸었습니다.
	
	//============== 이 위로는 건드리지 말자 ==============
	
	//switch (mode)
	//{
	//case 맵툴:
	//	PatBlt(UIDC, 0, 0, BACKGROUNDSIZEX, BACKGROUNDSIZEY, WHITENESS);
	//	//_mapTool->render();
	//	break;
	//case 타이틀:
	//	SCENEMANAGER->render();
	//	break;
	//case 다이얼로그:
	//	SCENEMANAGER->render();
	//	break;
	//case 도그본:
	//	SCENEMANAGER->render();
	//	break;
	//case 플레이어:
	//	_player->render();
	//	break;
	//case 아이템:
	//	SCENEMANAGER->render();
	//	break;
	//case 던전:
	//	SCENEMANAGER->render();
	//	break;
	//case 맵선택:
	//	SCENEMANAGER->render();
	//	break;
	//
	//case 기타추가하셈:
	//	break;
	//default:
	//	break;
	//}

	//TIMEMANAGER->render(DC);
	//
	////================이 밑으로도 건드리지 말자 =============
	//
	
	
	
	// 맨마지막으로 카메라 매니저 의 DC를 그려줍니다.
	// CAMERAMANAGER->setCameraX()  CAMERAMANAGER->setCameraY() 를 이용하면   X ,Y 에  WINSIZEX , WINSIZEY 만큼 화면에 그려주고있는 렉트를 이동시킬 수 있음 .
	// 그리고 모든 렌더의 hdc 는 CAMERAMANAGER->getCameraDC()->getMemDC() 로 해주어야함 !~~!!$!$!#ㄸ!#ㄸ!$!$#@$!@#@!
}
 