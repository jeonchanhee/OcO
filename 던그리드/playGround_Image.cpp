#include "stdafx.h"
#include "playGround.h"


HRESULT playGround::Image_init(void)
{
	//player
	IMAGEMANAGER->addFrameImage("�⺻�÷��̾�", "image/player/normalPlayer(640x360,8x4).bmp", 640, 360, 8, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�����÷��̾�", "image/player/princessPlayer(480x320,6x4).bmp", 480, 320, 6, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�÷��̾��", "image/player/hand(8x8,1x1).bmp", 8, 8, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("ü�¹�", "image/player/hpBar(50x50,1x1).bmp", 50, 50, false, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("ü�¹��ⷷ�ⷷ", "image/player/hpBarWave(120x50,6x1).bmp", 120, 50, 6, 1, true, RGB(255, 0, 255));

	 
	return S_OK;
}