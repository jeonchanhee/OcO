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

	return S_OK;
}

void playGround::release(void)	
{
	gameNode::release();

	
}

void playGround::update(void)	
{
	gameNode::update();

}

void playGround::render(void)
{
	
	//�����ȭ�� �� �� ��Ƶд�
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//============== �� ���δ� �ǵ帮�� ���� ==============
	
	
	
	//================�� �����ε� �ǵ帮�� ���� =============
	this->getBackBuffer()->render(getHDC(), 0, 0);

}

