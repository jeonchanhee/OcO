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

	SCENEMANAGER->addScene("����", new DialogWeapon);
	SCENEMANAGER->changeScene("����");
	return S_OK;
}

void playGround::release(void)	
{
	gameNode::release();

	
}

void playGround::update(void)	
{
	gameNode::update();
	SCENEMANAGER->update();
}

void playGround::render(void)
{
	
	//�����ȭ�� �� �� ��Ƶд�
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//============== �� ���δ� �ǵ帮�� ���� ==============
	
	SCENEMANAGER->render();
	
	//================�� �����ε� �ǵ帮�� ���� =============
	this->getBackBuffer()->render(getHDC(), 0, 0);

}

