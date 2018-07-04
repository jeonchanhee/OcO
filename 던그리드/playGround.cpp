#include "stdafx.h"
#include "playGround.h"


playGround::playGround(){}
playGround::~playGround(){}


HRESULT playGround::init(void)	
{
	mode = �÷��̾�;				//������ �����ϴ� �κ����� �̳ѿ� �߰��ϰ� �����ؼ� ����ϱ�!!


	gameNode::init(true);
	Image_init();
	Sound_init();
	
	/*_mapTool = new MapTool;
	_mapTool->init();*/
	_player = new Player;
	_player->init();


	SCENEMANAGER->addScene("Ÿ��Ʋ", new titleScene);
	SCENEMANAGER->addScene("����", new dungeonScene);
	SCENEMANAGER->addScene("��", new EnemyManager);
	SCENEMANAGER->addScene("����", new Dialog);
	//SCENEMANAGER->addScene("�����۾�", new itemManager);
	SCENEMANAGER->addScene("��Ʈ��", new introScene);
	SCENEMANAGER->addScene("�ʼ���", new mapSelectScene);
	
	switch (mode)
	{
	case ����:
	
		break;
	case Ÿ��Ʋ:
		SCENEMANAGER->changeScene("Ÿ��Ʋ");
		break;
	case ���̾�α�:
		SCENEMANAGER->changeScene("����");
		break;
	case ���׺�:
		SCENEMANAGER->changeScene("��");
		break;
	case �÷��̾�:
		break;
	case ������:
	//	SCENEMANAGER->changeScene("�����۾�");
		break;
	
	case ��Ʈ��:
		SCENEMANAGER->changeScene("��Ʈ��");
		break;
	
	case ����:
		SCENEMANAGER->changeScene("����");
		break;
	
	case �ʼ���:
		SCENEMANAGER->changeScene("�ʼ���");
		break;
	
	case ��Ÿ�߰��ϼ�:
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

	/*_mapTool->update();*/
	_player->update();
	SCENEMANAGER->update();
	
	
	/*if (KEYMANAGER->isStayKeyDown('D') && CAMERAMANAGER->getCameraRc2().right<BACKGROUNDSIZEX) CAMERAMANAGER->setCameraX2(CAMERAMANAGER->getCameraX2() + 50);
	if (KEYMANAGER->isStayKeyDown('S') && CAMERAMANAGER->getCameraRc2().bottom<BACKGROUNDSIZEY) CAMERAMANAGER->setCameraY2(CAMERAMANAGER->getCameraY2() + 50);
	if (KEYMANAGER->isStayKeyDown('A') && CAMERAMANAGER->getCameraRc2().left>0) CAMERAMANAGER->setCameraX2(CAMERAMANAGER->getCameraX2() - 50);
	if (KEYMANAGER->isStayKeyDown('W') && CAMERAMANAGER->getCameraRc2().top>0) CAMERAMANAGER->setCameraY2(CAMERAMANAGER->getCameraY2() - 50);*/

	//if (KEYMANAGER->isStayKeyDown('D') && CAMERAMANAGER->getCameraRc().right<96 * _tileX) CAMERAMANAGER->setCameraX(CAMERAMANAGER->getCameraX() + 50);
	//if (KEYMANAGER->isStayKeyDown('S') && CAMERAMANAGER->getCameraRc().bottom<96 * _tileY) CAMERAMANAGER->setCameraY(CAMERAMANAGER->getCameraY() + 50);
	//if (KEYMANAGER->isStayKeyDown('A') && CAMERAMANAGER->getCameraRc().left>0) CAMERAMANAGER->setCameraX(CAMERAMANAGER->getCameraX() - 50);
	//if (KEYMANAGER->isStayKeyDown('W') && CAMERAMANAGER->getCameraRc().top>0) CAMERAMANAGER->setCameraY(CAMERAMANAGER->getCameraY() - 50);

	/*if (KEYMANAGER->isStayKeyDown('D') && CAMERAMANAGER->getCameraRc().right<96 * BACKGROUNDSIZEX) CAMERAMANAGER->setCameraX(CAMERAMANAGER->getCameraX() + 50);
	if (KEYMANAGER->isStayKeyDown('S') && CAMERAMANAGER->getCameraRc().bottom<96 * BACKGROUNDSIZEY) CAMERAMANAGER->setCameraY(CAMERAMANAGER->getCameraY() + 50);
	if (KEYMANAGER->isStayKeyDown('A') && CAMERAMANAGER->getCameraRc().left>0) CAMERAMANAGER->setCameraX(CAMERAMANAGER->getCameraX() - 50);
	if (KEYMANAGER->isStayKeyDown('W') && CAMERAMANAGER->getCameraRc().top>0) CAMERAMANAGER->setCameraY(CAMERAMANAGER->getCameraY() - 50);
*/


	//if (KEYMANAGER->isStayKeyDown('D'))		CAMERAMANAGER->setCameraCenter(PointMake(CAMERAMANAGER->getCameraCenter().x + 50, CAMERAMANAGER->getCameraCenter().y));
	//if (KEYMANAGER->isStayKeyDown('S'))		CAMERAMANAGER->setCameraCenter(PointMake(CAMERAMANAGER->getCameraCenter().x , CAMERAMANAGER->getCameraCenter().y + 50));
	//if (KEYMANAGER->isStayKeyDown('A'))		CAMERAMANAGER->setCameraCenter(PointMake(CAMERAMANAGER->getCameraCenter().x  - 50, CAMERAMANAGER->getCameraCenter().y));
	//if (KEYMANAGER->isStayKeyDown('W'))		CAMERAMANAGER->setCameraCenter(PointMake(CAMERAMANAGER->getCameraCenter().x , CAMERAMANAGER->getCameraCenter().y - 50));
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
	// �� ���δ� �ǵ��� ���ÿ�
	//_player->render();
	switch (mode)
	{
	case ����:
		//PatBlt(UIDC, 0, 0, BACKGROUNDSIZEX, BACKGROUNDSIZEY, WHITENESS);
		//_mapTool->render();
		break;
	case Ÿ��Ʋ:
		SCENEMANAGER->render();
		break;
	case ���̾�α�:
		SCENEMANAGER->render();
		break;
	case ���׺�:
		SCENEMANAGER->render();
		break;
	case �÷��̾�:
		_player->render();
		break;
	case ������:
		SCENEMANAGER->render();
		break;
	case ����:
		SCENEMANAGER->render();
		break;
	case �ʼ���:
		SCENEMANAGER->render();
		break;
	
	case ��Ÿ�߰��ϼ�:
		break;
	default:
		break;
	}

	//char str[128];
	//sprintf_s(str, "%d, %d", CAMERAMANAGER->getCameraCenter().x + WINSIZEX / 2, CAMERAMANAGER->getCameraCenter().y + WINSIZEY / 2);
	//TextOut(UIDC, 100, 100, str, strlen(str));
	//
	//char str2[128];
	//sprintf_s(str2, "%d %d /// %d, %d", _tileX, _tileY, _tileX * 96, _tileY * 96);
	//TextOut(UIDC, 100, 150, str2, strlen(str2));


	IMAGEMANAGER->render("cursor", UIDC, _ptMouse.x, _ptMouse.y);
	TIMEMANAGER->render(UIDC);
	//RectangleMake(UIDC, WINSIZEX - 100, 0, 100, 100);
	//RectangleMake(DC, CAMERAMANAGER->getCameraCenter().x - 20, CAMERAMANAGER->getCameraCenter().y - 20, 40, 40);
	// �� �Ʒ��ε� �ǵ��� ���ÿ�
	/////////////////////////////////////////////////////////////////////////////////////////////
	CAMERAMANAGER->render(this->getBackBuffer());
	this->getBackBuffer()->render(getHDC(), 0, 0, CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2, CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2, WINSIZEX, WINSIZEY);

	

	//�����ȭ�� �� �� ��Ƶд�
	//PatBlt(DC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS); // ī�޶� �Ŵ��� DC -> getMemDC �� �ٲپ����ϴ�.
	
	//============== �� ���δ� �ǵ帮�� ���� ==============
	
	//switch (mode)
	//{
	//case ����:
	//	PatBlt(UIDC, 0, 0, BACKGROUNDSIZEX, BACKGROUNDSIZEY, WHITENESS);
	//	//_mapTool->render();
	//	break;
	//case Ÿ��Ʋ:
	//	SCENEMANAGER->render();
	//	break;
	//case ���̾�α�:
	//	SCENEMANAGER->render();
	//	break;
	//case ���׺�:
	//	SCENEMANAGER->render();
	//	break;
	//case �÷��̾�:
	//	_player->render();
	//	break;
	//case ������:
	//	SCENEMANAGER->render();
	//	break;
	//case ����:
	//	SCENEMANAGER->render();
	//	break;
	//case �ʼ���:
	//	SCENEMANAGER->render();
	//	break;
	//
	//case ��Ÿ�߰��ϼ�:
	//	break;
	//default:
	//	break;
	//}

	//TIMEMANAGER->render(DC);
	//
	////================�� �����ε� �ǵ帮�� ���� =============
	//
	
	//CAMERAMANAGER->getCameraDC()->render(getHDC() , 0 , 0 , CAMERAMANAGER->getCameraRc().left, CAMERAMANAGER->getCameraRc().top, CAMERAMANAGER->getCameraRc().right, CAMERAMANAGER->getCameraRc().bottom); 
	
	// �Ǹ��������� ī�޶� �Ŵ��� �� DC�� �׷��ݴϴ�.
	// CAMERAMANAGER->setCameraX()  CAMERAMANAGER->setCameraY() �� �̿��ϸ�   X ,Y ��  WINSIZEX , WINSIZEY ��ŭ ȭ�鿡 �׷��ְ��ִ� ��Ʈ�� �̵���ų �� ���� .
	// �׸��� ��� ������ hdc �� CAMERAMANAGER->getCameraDC()->getMemDC() �� ���־���� !~~!!$!$!#��!#��!$!$#@$!@#@!
}
 