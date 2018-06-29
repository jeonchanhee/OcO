#include "stdafx.h"
#include "playGround.h"


HRESULT playGround::Image_init(void)
{
	IMAGEMANAGER->addImage("cursor", "image/UI/Cursor(61,70).bmp", 0, 0, 61, 70, true, RGB(255, 0, 255));
	//==========타이틀이미지==========
	IMAGEMANAGER->addImage("title", "image/UI/Title(1920x1080).bmp", 0, 0, 1920,1080, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("T_back", "image/UI/Blue(1920x1080).bmp", 0, 0, 1920,1080, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("T_cloud0", "image/UI/BackCloud0(3840x1080).bmp", 0, 0, 3840,1080, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("T_cloud1", "image/UI/BackCloud1(4300x1080).bmp", 0, 0, 4300,1080, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("T_start", "image/UI/B_start(420x70,2x1).bmp", 0, 0, 420,70, 2,1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("T_option", "image/UI/B_option(420x70,2x1).bmp", 0, 0, 420,70, 2,1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("T_exit", "image/UI/B_exit(420x70,2x1).bmp", 0, 0, 420,70, 2,1, true, RGB(255, 0, 255));





	return S_OK;
}