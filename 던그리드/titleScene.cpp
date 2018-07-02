#include "stdafx.h"
#include "titleScene.h"


HRESULT titleScene::init(void)
{
	_birdImg0 = IMAGEMANAGER->addFrameImage("T_bird", "image/UI/Bird(800x58,8x1).bmp", 0, 0, 800, 58, 8, 1, true, RGB(255, 0, 255), true);
	_birdImg1 = IMAGEMANAGER->addFrameImage("T_bird1", "image/UI/Bird(800x58,8x1).bmp", 0, 0, 800, 58, 8, 1, true, RGB(255, 0, 255), true);
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

	_clickData = false;
	for (int i = 0; i < 3; i++)
	{
		_deleteRect[i] = RectMake(220 + i * 610, 150, IMAGEMANAGER->findImage("T_delete")->getWidth(), IMAGEMANAGER->findImage("T_delete")->getHeight());
	}
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
	
	deleteData();

	KEYANIMANAGER->update();
}

void titleScene::render(void)
{
	IMAGEMANAGER->render("T_back", DC, 0, 0);
	IMAGEMANAGER->loopRender("T_cloud0", DC, &RectMake(0, 0, WINSIZEX, WINSIZEY), _loop0, 0);
	IMAGEMANAGER->loopRender("T_cloud1", DC, &RectMake(0, 0, WINSIZEX, WINSIZEY), _loop1, 0);
	_birdImg0->aniRender(DC, _bird0.x, _bird0.y, _abird0);
	_birdImg1->aniRender(DC, _bird1.x, _bird1.y, _abird1);
	
	
	if (!_clickData)
	{
		if (PtInRect(&_button[0], _ptMouse))
		{
			IMAGEMANAGER->frameRender("T_start", DC, 850, 700, 1, 0);
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				//SCENEMANAGER->changeScene("던전");
				loadData();
			}
		}
		else
			IMAGEMANAGER->frameRender("T_start", DC, 850, 700, 0, 0);
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
		IMAGEMANAGER->render("title", DC, 0, 0);
	}
	else
	{
		drawData();
	}

	if(KEYMANAGER->isToggleKey(VK_TAB))
	{
		for(int i=0;i<3;i++)
		Rectangle(DC,_button[i].left, _button[i].top, _button[i].right, _button[i].bottom);
	}
}

void titleScene::loadData()
{
	if (_clickData) return;

	_clickData = true;

	vector<string> vStr = TXTDATA->txtLoad("data.txt");

	_vData.clear();
	_vData.resize(3);

	for (int i = 0; i < 3; i++)
	{
		_vData[i].idx = -1;
	}

	for (int i = 0; i < vStr.size() / 6; i++)
	{
		int idx = atoi(vStr[i * 6].c_str());
		_vData[idx].idx = idx;
		_vData[idx].hour = atoi(vStr[i * 6 + 1].c_str());
		_vData[idx].min = atoi(vStr[i * 6 + 2].c_str());
		_vData[idx].floor = atoi(vStr[i * 6 + 3].c_str());
		_vData[idx].gold = atoi(vStr[i * 6 + 4].c_str());
		_vData[idx].dash = atoi(vStr[i * 6 + 5].c_str());
	}
}

void titleScene::drawData()
{
	IMAGEMANAGER->alphaRender("black", DC, 0, 0, 100);

	for (int i = 0; i < 3; i++)
	{
		IMAGEMANAGER->frameRender("T_textBack", DC, 50 + i * 610, 90, 0, 0);
		IMAGEMANAGER->frameRender("T_text", DC, 220 + i * 610, 180, i, 0);
		IMAGEMANAGER->render("T_delete", DC, 150 + i * 610, 730);

		if (_vData[i].idx != -1)
		{
			HFONT font, oldFont;
			font = CreateFont(40, 0, 0, 0, 40, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("소야바른9"));
			oldFont = (HFONT)SelectObject(DC, font);
			SetBkMode(DC, TRANSPARENT);
			char str[128];
			sprintf_s(str, "<플레이 시간>");
			TextOut(DC, 230 + i * 610, 300, str, strlen(str));
			sprintf_s(str, "%02dH %02dM", _vData[i].hour, _vData[i].min);
			TextOut(DC, 250 + i * 610, 350, str, strlen(str));
			sprintf_s(str, "<도달한 층>");
			TextOut(DC, 240 + i * 610, 440, str, strlen(str));
			sprintf_s(str, "%5dF", _vData[i].floor);
			TextOut(DC, 250 + i * 610, 490, str, strlen(str));
			sprintf_s(str, "<소지금>");
			TextOut(DC, 260 + i * 610, 580, str, strlen(str));
			sprintf_s(str, "%5dG", _vData[i].gold);
			TextOut(DC, 260 + i * 610, 630, str, strlen(str));
			SelectObject(DC, oldFont);
			DeleteObject(font);
		}
	}
}

void titleScene::deleteData()
{
	if(!_clickData) return;

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < 3; i++)
		{
			if (PtInRect(&_deleteRect[i], _ptMouse))
			{
				tagData temp;
				ZeroMemory(&temp, sizeof(tagData));
				_vData[i] = temp;
				_vData[i].idx = -1;
			}
		}
	}
}

titleScene::titleScene()
{
}


titleScene::~titleScene()
{
}
