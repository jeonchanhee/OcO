#include "stdafx.h"
#include "playGround.h"


playGround::playGround(){}
playGround::~playGround(){}


HRESULT playGround::init(void)	
{
	mode = �ʼ���;				//������ �����ϴ� �κ����� �̳ѿ� �߰��ϰ� �����ؼ� ����ϱ�!!


	gameNode::init(true);
	Image_init();
	Sound_init();
	
	_mapTool = new MapTool;
	_mapTool->init();
	_player = new Player;
	_player->init();


	SCENEMANAGER->addScene("Ÿ��Ʋ", new titleScene);
	SCENEMANAGER->addScene("����", new dungeonScene);
	SCENEMANAGER->addScene("��", new EnemyManager);
	SCENEMANAGER->addScene("����", new Dialog);
	SCENEMANAGER->addScene("�����۾�", new itemManager);
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
		SCENEMANAGER->changeScene("�����۾�");
		break;

	case ��Ʈ��:
		SCENEMANAGER->changeScene("��Ʈ��");
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

	_mapTool->update();
	_player->update();
	SCENEMANAGER->update();
	
	/*
	if (KEYMANAGER->isStayKeyDown('D') && CAMERAMANAGER->getCameraRc2().right<BACKGROUNDSIZEX) CAMERAMANAGER->setCameraX2(CAMERAMANAGER->getCameraX2() + 50);
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


	if (KEYMANAGER->isStayKeyDown('D'))							CAMERAMANAGER->setCameraX(CAMERAMANAGER->getCameraX() + 50);
	if (KEYMANAGER->isStayKeyDown('S'))							CAMERAMANAGER->setCameraY(CAMERAMANAGER->getCameraY() + 50);
	if (KEYMANAGER->isStayKeyDown('A'))							CAMERAMANAGER->setCameraX(CAMERAMANAGER->getCameraX() - 50);
	if (KEYMANAGER->isStayKeyDown('W'))							CAMERAMANAGER->setCameraY(CAMERAMANAGER->getCameraY() - 50);

	if (CAMERAMANAGER->getCameraX() < 0)						CAMERAMANAGER->setCameraX(0);
	if (CAMERAMANAGER->getCameraY() < 0)						CAMERAMANAGER->setCameraY(0);
	if (CAMERAMANAGER->getCameraX() + WINSIZEX > 96 * _tileX)	CAMERAMANAGER->setCameraX(96 * _tileX - WINSIZEX);
	if (CAMERAMANAGER->getCameraY() + WINSIZEY > 96 * _tileY)	CAMERAMANAGER->setCameraY(96 * _tileY - WINSIZEY);


}

void playGround::render(void)
{
	
	//�����ȭ�� �� �� ��Ƶд�
	PatBlt(DC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS); // ī�޶� �Ŵ��� DC -> getMemDC �� �ٲپ����ϴ�.
	
	//============== �� ���δ� �ǵ帮�� ���� ==============
	
	switch (mode)
	{
	case ����:
		PatBlt(DC2, 0, 0, BACKGROUNDSIZEX, BACKGROUNDSIZEY, WHITENESS);
		_mapTool->render();
		CAMERAMANAGER->getCameraDC2()->render(DC, 0, 0, CAMERAMANAGER->getCameraRc2().left, CAMERAMANAGER->getCameraRc2().top, CAMERA2X, CAMERA2Y);
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
	case �ʼ���:
		SCENEMANAGER->render();
		break;

	case ��Ÿ�߰��ϼ�:
		break;
	default:
		break;
	}


	//================�� �����ε� �ǵ帮�� ���� =============
	
	IMAGEMANAGER->render("cursor", DC, _ptMouse.x, _ptMouse.y);
	CAMERAMANAGER->getCameraDC()->render(getHDC() , 0 , 0 , CAMERAMANAGER->getCameraRc().left, CAMERAMANAGER->getCameraRc().top, CAMERAMANAGER->getCameraRc().right, CAMERAMANAGER->getCameraRc().bottom); 
	
	// �Ǹ��������� ī�޶� �Ŵ��� �� DC�� �׷��ݴϴ�.
	// CAMERAMANAGER->setCameraX()  CAMERAMANAGER->setCameraY() �� �̿��ϸ�   X ,Y ��  WINSIZEX , WINSIZEY ��ŭ ȭ�鿡 �׷��ְ��ִ� ��Ʈ�� �̵���ų �� ���� .
	// �׸��� ��� ������ hdc �� CAMERAMANAGER->getCameraDC()->getMemDC() �� ���־���� !~~!!$!$!#��!#��!$!$#@$!@#@!
}
 