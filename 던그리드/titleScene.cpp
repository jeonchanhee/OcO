#include "stdafx.h"
#include "titleScene.h"


HRESULT titleScene::init(void)
{
	_birdImg0 = IMAGEMANAGER->addFrameImage("T_bird", "image/UI/Bird(800x58,8x1).bmp", 0, 0, 800, 58, 8, 1, true, RGB(255, 0, 255));
	_birdImg1 = IMAGEMANAGER->addFrameImage("T_bird1", "image/UI/Bird(800x58,8x1).bmp", 0, 0, 800, 58, 8, 1, true, RGB(255, 0, 255));
	_bird0 = { RND->getFromIntTo(-200,-50),RND->getFromIntTo(500,900) };
	_bird1 = { RND->getFromIntTo(-700,-500),RND->getFromIntTo(200,500) };
	_loop0= _loop1 = 0;
	int bird[] = { 0,1,2,3,4,5,6,7 };
	KEYANIMANAGER->addArrayFrameAnimation("bird0", "T_bird", bird, 8, 7, true);
	int bird1[] = { 6,7,0,1,2,3,4,5 };
	KEYANIMANAGER->addArrayFrameAnimation("bird1", "T_bird1", bird, 8, 7, true);
	_abird0 = KEYANIMANAGER->findAnimation("bird0");
	_abird1 = KEYANIMANAGER->findAnimation("bird1");
	_abird0->start();
	_abird1->start();
	return S_OK;
}

void titleScene::release(void)
{

}

void titleScene::update(void)
{
	_loop0 -= 0.5;
	_loop1 -= 1;
	_bird0.x += 3;
	_bird1.x += 2;
	if (_loop0 > 3840)
		_loop0 = 0;
	if (_loop1 > 4300)
		_loop1 = 0;
	if (_bird0.x > WINSIZEX + 900)
	{
		_bird0 = { RND->getFromIntTo(-700,-400),RND->getFromIntTo(100,900) };
		_abird0->start();
	}
	if (_bird1.x > WINSIZEX + 900)
	{
		_bird1 = { RND->getFromIntTo(-900,-600),RND->getFromIntTo(100,900) };
		_abird1->start();
	}

	KEYANIMANAGER->update();
}

void titleScene::render(void)
{
	IMAGEMANAGER->render("T_back", getMemDC(),0, 0);
	IMAGEMANAGER->loopRender("T_cloud0", getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), _loop0, 0);
	IMAGEMANAGER->loopRender("T_cloud1", getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), _loop1, 0);
	_birdImg0->aniRender(getMemDC(), _bird0.x, _bird0.y, _abird0);
	_birdImg1->aniRender(getMemDC(), _bird1.x, _bird1.y, _abird1);
	IMAGEMANAGER->frameRender("T_start", getMemDC(),850, 700);
	IMAGEMANAGER->frameRender("T_option", getMemDC(),850, 800);
	IMAGEMANAGER->frameRender("T_exit", getMemDC(),850, 900);
	IMAGEMANAGER->render("title", getMemDC(),0, 0);
}

titleScene::titleScene()
{
}


titleScene::~titleScene()
{
}
