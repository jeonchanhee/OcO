#include "stdafx.h"
#include "playGround.h"


HRESULT playGround::Image_init(void)
{
	//player
	IMAGEMANAGER->addFrameImage("기본플레이어", "image/player/normalPlayer(640x360,8x4).bmp", 640, 360, 8, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("공주플레이어", "image/player/princessPlayer(480x320,6x4).bmp", 480, 320, 6, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("플레이어손", "image/player/hand(8x8,1x1).bmp", 8, 8, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("체력바", "image/player/hpBar(50x50,1x1).bmp", 50, 50, false, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("체력바출렁출렁", "image/player/hpBarWave(120x50,6x1).bmp", 120, 50, 6, 1, true, RGB(255, 0, 255));

	 
	return S_OK;
}