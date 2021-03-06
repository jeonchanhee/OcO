#include "stdafx.h"
#include "titleScene.h"
#include "itemManager.h"


HRESULT titleScene::init(void)
{
	SOUNDMANAGER->play("title");
	_birdImg0 = IMAGEMANAGER->addFrameImage("T_bird", "image/UI/Bird(800x58,8x1).bmp", 0, 0, 800, 58, 8, 1, true, RGB(255, 0, 255), true);
	_birdImg1 = IMAGEMANAGER->addFrameImage("T_bird1", "image/UI/Bird(800x58,8x1).bmp", 0, 0, 800, 58, 8, 1, true, RGB(255, 0, 255), true);
	_bird0 = { RND->getFromIntTo(-500,-300),RND->getFromIntTo(500,900) };
	_bird1 = { RND->getFromIntTo(-1000,-700),RND->getFromIntTo(200,500) };
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

	_select = 0;
	_clickData = false;


	for (int i = 0; i < 3; i++)
	{
		_chooseRect[i] = RectMake(50 + i * 610, 90, 576, 858);
		_deleteRect[i] = RectMake(150 + i * 610, 730, IMAGEMANAGER->findImage("T_delete")->getWidth(), IMAGEMANAGER->findImage("T_delete")->getHeight());
	}

	_titleType = TITLE_MENU;
	_soundX = 1500, _soundY = 490;
	_soundX2 = 1500, _soundY2 = 640;
	_soundRC = RectMakeCenter(_soundX, _soundY, 100, 100);
	_soundRC2 = RectMakeCenter(_soundX2, _soundY2, 100, 100);
	_bgmBack = RectMake(600, 470, 900, 50);
	_sfxBack = RectMake(600, 620, 900, 50);

	
	/*int suck[51];
	for (int i = 0; i<51; i++)
		suck[i] = i;
	KEYANIMANAGER->addArrayFrameAnimation("suck", "suck", suck, 51, 3, true);*/
	//KEYANIMANAGER->addDefaultFrameAnimation("suck", "suck", 3, false, false);

	//KEYANIMANAGER->addCoordinateFrameAnimation("suck", "suck", 49, 50, 3, false, false);

	return S_OK;
}

void titleScene::release(void)
{

}

void titleScene::update(void)
{
	_loop0 -= 0.2;
	_loop1 -= 0.5;
	_bird0.x += 2;
	_bird1.x += 1;
	if (_loop0 > 3840)
		_loop0 = 0;
	if (_loop1 > 4300)
		_loop1 = 0;
	if (_bird0.x > WINSIZEX + 900)
	{
		_bird0 = { RND->getFromIntTo(-800,-500),RND->getFromIntTo(100,900) };
		_abird0->start();
	}
	if (_bird1.x > WINSIZEX + 900)
	{
		_bird1 = { RND->getFromIntTo(-1000,-700),RND->getFromIntTo(100,900) };
		_abird1->start();
	}
	
	selectData();

	if (_titleType == TITLE_SET)
	{
		drawSetting();
	}
	//KEYANIMANAGER->update();
}

void titleScene::render(void)
{
	IMAGEMANAGER->render("T_back", DC, 0, 0);
	IMAGEMANAGER->loopRender("T_cloud0", DC, &RectMake(0, 0, WINSIZEX, WINSIZEY), _loop0, 0);
	IMAGEMANAGER->loopRender("T_cloud1", DC, &RectMake(0, 0, WINSIZEX, WINSIZEY), _loop1, 0);
	_birdImg0->aniRender(DC, _bird0.x, _bird0.y, _abird0);
	_birdImg1->aniRender(DC, _bird1.x, _bird1.y, _abird1);
	
	
	//if (!_clickData)
	if(_titleType == TITLE_MENU)
	{
		if (PtInRect(&_button[0], _ptMouse))
		{
			IMAGEMANAGER->frameRender("T_start", DC, 850, 700, 1, 0);
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				//SCENEMANAGER->changeScene("던전");
				_titleType = TITLE_START;
				loadData();
				
				/*int suck[52];
				for (int i = 0; i<52; i++)
					suck[i] = i;
				KEYANIMANAGER->addArrayFrameAnimation("suck", "suck", suck, 52, 3, false);
				_img = IMAGEMANAGER->findImage("suck");
				_suck = KEYANIMANAGER->findAnimation("suck");
				_suck->start();*/
			}
		}
		else
			IMAGEMANAGER->frameRender("T_start", DC, 850, 700, 0, 0);
		if (PtInRect(&_button[1], _ptMouse))
		{
			IMAGEMANAGER->frameRender("T_option", DC, 850, 800, 1, 0);
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_titleType = TITLE_SET;
				_setData = true;
				_exitRect = RectMake(WINSIZEX - 130, 50,100,100);
			}
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
		//reward();
		//restaurant();
		//drawData();
	}
	drawData();
	setting();

	if (_select != 0)
	{
		IMAGEMANAGER->findImage("edge")->render(DC, _chooseRect[_select-1].left+6, _chooseRect[_select-1].top-91);
	}

	if(KEYMANAGER->isToggleKey(VK_TAB))
	{
		for (int i = 0; i < 3; i++)
		{
			Rectangle(DC, _button[i].left, _button[i].top, _button[i].right, _button[i].bottom);
			Rectangle(DC, _chooseRect[i].left, _chooseRect[i].top, _chooseRect[i].right, _chooseRect[i].bottom);
			Rectangle(DC, _deleteRect[i].left, _deleteRect[i].top, _deleteRect[i].right, _deleteRect[i].bottom);
		}
	}
}

//void titleScene::inven()
//{
//	IMAGEMANAGER->findImage("inven")->render(DC, WINSIZEX - IMAGEMANAGER->findImage("inven")->getWidth(), 0);
//	IMAGEMANAGER->findImage("inven0")->render(DC, 1288, 155);
//	//IMAGEMANAGER->findImage("inven0")->render(DC, 1598, 155);
//	RECT rc[4];
//	rc[0] = RectMake(1310, 205, 100, 100);
//	rc[1] = RectMake(1435 , 205, 100, 100);
//	rc[2] = RectMake(1620 , 205, 100, 100);
//	rc[3] = RectMake(1745 , 205, 100, 100);
//	if (KEYMANAGER->isToggleKey(VK_TAB))
//	{
//		for (int i = 0; i<4; i++)
//		Rectangle(DC, rc[i].left, rc[i].top, rc[i].right, rc[i].bottom);
//	}
//	//_im->getItem()[0]->getItem().image[0]->render(DC, rc[0].left, rc[0].top);
//}


void titleScene::reward()
{
	IMAGEMANAGER->findImage("reward")->render(DC, 0, 0);
	IMAGEMANAGER->findImage("expBar")->render(DC, 0, WINSIZEY- IMAGEMANAGER->findImage("expBar")->getHeight());
	//IMAGEMANAGER->findImage("suck")->frameRender(DC, 780, 546);

	//_img->aniRender(DC, 740, 546, _suck);
	//KEYANIMANAGER->update();

}

void titleScene::loadData()
{
	//if (_clickData) return;
	if (_titleType != TITLE_START) return;

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
	if (_titleType == TITLE_START)
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
				SetTextColor(DC, RGB(255, 255, 255));
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
			else
			{
				HFONT font, oldFont;
				font = CreateFont(40, 0, 0, 0, 40, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("소야바른9"));
				oldFont = (HFONT)SelectObject(DC, font);
				SetBkMode(DC, TRANSPARENT);
				char str[128];
				sprintf_s(str, "데이터 없음");
				TextOut(DC, 250 + i * 610, 350, str, strlen(str));
				SelectObject(DC, oldFont);
				DeleteObject(font);
			}
		}
	}
}

void titleScene::selectData()
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
				saveData();
			}
			else if (PtInRect(&_chooseRect[i], _ptMouse))
			{
				if (_select == i + 1)
				{
					_fileNum = i;
					_start = 0;
					SOUNDMANAGER->stop("title");
					SCENEMANAGER->changeScene("마을");
					break;
				}
				_select = i + 1;
			}
		}
	}
}

void titleScene::saveData()
{
	vector<string> vStr;
	for (int i = 0; i < 3; i++)
	{
		if (_vData[i].idx == -1)continue;
		char str[128];
		vStr.push_back(itoa(_vData[i].idx, str, 10));
		vStr.push_back(itoa(_vData[i].hour, str, 10));
		vStr.push_back(itoa(_vData[i].min, str, 10));
		vStr.push_back(itoa(_vData[i].floor, str, 10));
		vStr.push_back(itoa(_vData[i].gold, str, 10));
		vStr.push_back(itoa(_vData[i].dash, str, 10));
	}
	TXTDATA->txtSave("data.txt", vStr);
}

void titleScene::setting()
{
	if (_setData)
	{
		IMAGEMANAGER->render("setting", DC);
		//Rectangle(DC, _exitRect.left, _exitRect.top, _exitRect.right, _exitRect.bottom);
		HFONT font, oldFont;
		font = CreateFont(100, 0, 0, 0, 100, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("소야바른9"));
		oldFont = (HFONT)SelectObject(DC, font);
		SetTextColor(DC, RGB(255, 255, 255));
		SetBkMode(DC, TRANSPARENT);
		TextOut(DC, WINSIZEX / 2 - 100, 280, "사운드", strlen("사운드"));
		TextOut(DC, 200, 450, "음악 볼륨", strlen("음악 볼륨"));
		TextOut(DC, 150, 600, "효과음 볼륨", strlen("효과음 볼륨"));
		TextOut(DC, WINSIZEX / 2 - 100, 750, "컨트롤", strlen("컨트롤"));
		TextOut(DC, 150, 900, "화면 흔들림", strlen("화면 흔들림"));
		SelectObject(DC, oldFont);
		DeleteObject(font);

		IMAGEMANAGER->findImage("soundbar")->render(DC, _bgmBack.left, _bgmBack.top);
		IMAGEMANAGER->findImage("soundbar")->render(DC, _sfxBack.left, _sfxBack.top);

		IMAGEMANAGER->findImage("soundIcon")->frameRender(DC, _soundRC.left, _soundRC.top);
		IMAGEMANAGER->findImage("soundIcon")->frameRender(DC, _soundRC2.left, _soundRC2.top);

		RECT rc = RectMake(900, 900, 100, 100);
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && PtInRect(&rc, _ptMouse))
		{
			if (IMAGEMANAGER->findImage("toggleCheck")->getFrameX() == 0)
				IMAGEMANAGER->findImage("toggleCheck")->setFrameX(1);
			else
				IMAGEMANAGER->findImage("toggleCheck")->setFrameX(0);
		}
		IMAGEMANAGER->findImage("toggleCheck")->frameRender(DC, 900, 900);
		//RectangleMake(DC, 900, 900, 100, 100);

		if (PtInRect(&_exitRect, getMemDCPoint()))
		{
			IMAGEMANAGER->frameRender("exitImage", DC, _exitRect.left, _exitRect.top, 1, 0);
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_setData = false;
				_titleType = TITLE_MENU;
			}
		}
		else
			IMAGEMANAGER->frameRender("exitImage", DC, _exitRect.left, _exitRect.top, 0, 0);
	}
}

void titleScene::drawSetting()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_bgmBack, _ptMouse))
		{
			float pos = _ptMouse.x - 600;
			float volume = pos / 900;
			SOUNDMANAGER->setBGMVolume(volume);
			_soundX = _ptMouse.x;
		}
		if (PtInRect(&_sfxBack, _ptMouse))
		{
			float pos = _ptMouse.x - 600;
			float volume = pos / 900;
			SOUNDMANAGER->setSFXVolume(volume);
			_soundX2 = _ptMouse.x;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_bgmBack, _ptMouse))
		{
			float pos = _ptMouse.x - 600;
			float volume = pos / 900;
			SOUNDMANAGER->setBGMVolume(volume);
			_soundX = _ptMouse.x;
		}
		if (PtInRect(&_sfxBack, _ptMouse))
		{
			float pos = _ptMouse.x - 600;
			float volume = pos / 900;
			SOUNDMANAGER->setSFXVolume(volume);
			_soundX2 = _ptMouse.x;
		}
	}

	_soundRC = RectMakeCenter(_soundX, _soundY, 100, 100);
	_soundRC2 = RectMakeCenter(_soundX2, _soundY2, 100, 100);
}

titleScene::titleScene()
{
}


titleScene::~titleScene()
{
}
