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

	_mapTool = new MapTool;
	_mapTool->init();

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
//	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) CAMERAMANAGER->setCameraX(CAMERAMANAGER->getCameraX() - 5);

}

void playGround::render(void)
{
	
	//�����ȭ�� �� �� ��Ƶд�
	//PatBlt(CAMERAMANAGER->getCameraDC()->getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS); // ī�޶� �Ŵ��� DC -> getMemDC �� �ٲپ����ϴ�.
	//============== �� ���δ� �ǵ帮�� ���� ==============
	
	_mapTool->render();
	
	//================�� �����ε� �ǵ帮�� ���� =============
	//CAMERAMANAGER->getCameraDC()->render(getHDC() , 0 , 0 , CAMERAMANAGER->getCameraRc().left, CAMERAMANAGER->getCameraRc().top, CAMERAMANAGER->getCameraRc().right, CAMERAMANAGER->getCameraRc().bottom); 
	// �Ǹ��������� ī�޶� �Ŵ��� �� DC�� �׷��ݴϴ�.
	// CAMERAMANAGER->setCameraX()  CAMERAMANAGER->setCameraY() �� �̿��ϸ�   X ,Y ��  WINSIZEX , WINSIZEY ��ŭ ȭ�鿡 �׷��ְ��ִ� ��Ʈ�� �̵���ų �� ���� .
	// �׸��� ��� ������ hdc �� CAMERAMANAGER->getCameraDC()->getMemDC() �� ���־���� !~~!!$!$!#��!#��!$!$#@$!@#@!


}

