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
	_button[0]=RectMake(850,700,210,62);
	_button[1]=RectMake(912,800,92,62);
	_button[2]=RectMake(907,900,102,62);

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
	IMAGEMANAGER->render("T_back", DC,0, 0);
	IMAGEMANAGER->loopRender("T_cloud0", DC, &RectMake(0, 0, WINSIZEX, WINSIZEY), _loop0, 0);
	IMAGEMANAGER->loopRender("T_cloud1", DC, &RectMake(0, 0, WINSIZEX, WINSIZEY), _loop1, 0);
	_birdImg0->aniRender(DC, _bird0.x, _bird0.y, _abird0);
	_birdImg1->aniRender(DC, _bird1.x, _bird1.y, _abird1);
	if (PtInRect(&_button[0], _ptMouse))
	{
		IMAGEMANAGER->frameRender("T_start", DC, 850, 700, 1, 0);
		if(KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			SCENEMANAGER->changeScene("´øÀü");
	}
	else
		IMAGEMANAGER->frameRender("T_start", DC,850, 700,0,0);
	if (PtInRect(&_button[1], _ptMouse))
	{
		IMAGEMANAGER->frameRender("T_option", DC, 850, 800, 1, 0);
	}
	else
		IMAGEMANAGER->frameRender("T_option", DC, 850, 800, 0, 0);
	if (PtInRect(&_button[2], _ptMouse))
	{
		IMAGEMANAGER->frameRender("T_exit", DC, 850, 900, 1, 0);
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			PostMessage(_hWnd, WM_DESTROY, 0, 0);
	}
	else
		IMAGEMANAGER->frameRender("T_exit", DC, 850, 900, 0, 0);
	IMAGEMANAGER->render("title", DC,0, 0);
	if(KEYMANAGER->isToggleKey(VK_TAB))
	{
		for(int i=0;i<3;i++)
		Rectangle(DC,_button[i].left, _button[i].top, _button[i].right, _button[i].bottom);
	}
}

titleScene::titleScene()
{
}


titleScene::~titleScene()
{
}
