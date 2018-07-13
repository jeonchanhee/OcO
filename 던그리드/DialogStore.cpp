#include "stdafx.h"
#include "DialogStore.h"
#include "itemManager.h"
#include "Player.h"


DialogStore::DialogStore()
{
}


DialogStore::~DialogStore()
{
}

HRESULT DialogStore::init()
{
	Dialog::init();

	_ansBack = new image;
	_ansBack->init("image/UI/UIdias(400x250).bmp", 400, 180, true, RGB(255, 0, 255));

	_name = "호레리카";
	_store = STORE_BUY;

	_vButton.resize(2);
	_vButtonDialog.resize(2);
	_vDialog.resize(2);

	for (int i = 0; i < _vButton.size(); i++)
	{
		_vButton[i] = RectMake(WINSIZEX - 280, WINSIZEY - 520 + i * 50, 200, 50);
	}
	_vButtonDialog[0] = "음식점";
	_vButtonDialog[1] = "아무것도";

	setDialog();

	_restImg = IMAGEMANAGER->findImage("rest");
	_scroll = false;
	_currentScroll = 0;
	_rrc = RectMake(686, 210, 42, 432);

	_open = false;

	int rest[] = { 0,1,2 };
	KEYANIMANAGER->addArrayFrameAnimation("rest", "rest", rest, 3, 7, true);
	_rest = KEYANIMANAGER->findAnimation("rest");
	_rest->start();

	return S_OK;
}

void DialogStore::release()
{
}

void DialogStore::update()
{
	keyControl();
	clickButton();
	setFrame();
}

void DialogStore::render()
{
	Dialog::render();

	_ansBack->render(UIDC, WINSIZEX - 350, WINSIZEY - 550);

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(UIDC, _uiBack->boundingBox().left, _uiBack->boundingBox().top, _uiBack->boundingBox().right, _uiBack->boundingBox().bottom);
		for (int i = 0; i < _vButton.size(); i++)
		{
			Rectangle(UIDC, _vButton[i].left, _vButton[i].top, _vButton[i].right, _vButton[i].bottom);
		}
	}
	HFONT font, oldFont;
	font = CreateFont(50, 0, 0, 0, 100, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("소야바른9"));
	oldFont = (HFONT)SelectObject(UIDC, font);
	SetTextColor(UIDC, RGB(255, 255, 255));
	SetBkMode(UIDC, TRANSPARENT);
	string str = _vDialog[(int)_store][_idY].substr(0, _idX);
	//DrawText(DC, _dialog[(int)_training][_idY].c_str(), strlen(_dialog[(int)_training][_idY].c_str()), &_rc[0], DT_VCENTER);
	DrawText(UIDC, str.c_str(), strlen(str.c_str()), &_rc[1], DT_VCENTER);
	SelectObject(UIDC, oldFont);
	DeleteObject(font);

	font = CreateFont(50, 0, 0, 0, 100, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("소야바른9"));
	oldFont = (HFONT)SelectObject(UIDC, font);
	for (int i = 0; i < _vButton.size(); i++)
	{
		DrawText(UIDC, _vButtonDialog[i].c_str(), strlen(_vButtonDialog[i].c_str()), &_vButton[i], DT_VCENTER | DT_CENTER);
	}
	SelectObject(UIDC, oldFont);
	DeleteObject(font);

	if (_open == true)
	{
		restaurant();
	}
}

void DialogStore::keyControl()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && PtInRect(&_uiBack->boundingBox(), _ptMouse))
	{
		//changeDialog();
		if (_idX < _vDialog[(int)_store][_idY].size() - 1)
			_idX = _vDialog[(int)_store][_idY].size() - 1;
		else if ((_idY + 1) < _vDialog[(int)_store].size())
		{
			_idY++;
			_idX = 0;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		changeDialog();
	}
	if (KEYMANAGER->isOnceKeyDown('F'))
	{
		_open = false;
		IMAGEMANAGER->findImage("black")->render(UIDC2, 0, 0);
	}
}

void DialogStore::setFrame()
{
	_count++;

	if (!(_count % 3))
	{
		_count = 0;
		if (_idX < _vDialog[(int)_store][_idY].size())
		{
			_idX++;
		}
	}
}

void DialogStore::setDialog()
{
	switch (_store)
	{
	case STORE_MEET:
		if (_vDialog[0].size() == 0) _vDialog[0].resize(4);
		else return;
		_vDialog[0][0] = "안녕하세요 여행자님. 저는 호레리카 라고 합니다.";
		_vDialog[0][1] = "저는 던전의 낭만을 책임져야 할 여관주인으로서 사명을 다하기 위해서,";
		_vDialog[0][2] = "여기 오는 여행자들에게 음식을 대접해드리고 있습니다.";
		_vDialog[0][3] = "재료를 엄선해서 만들고 있으니, 부디 자주 들려주세요.";
	break;
	case STORE_BUY:
		if (_vDialog[1].size() == 0) _vDialog[1].resize(1);
		_vDialog[1][0] = "오늘은 어떤 요리를 드시러 오셨나요?";
	break;
	}
}

void DialogStore::changeDialog()
{
	switch (_store)
	{
	case STORE_MEET:
		_store = STORE_BUY;
		break;
	case STORE_BUY:
		_store = STORE_MEET;
		break;
	}
	_count = _idX = _idY = 0;
	setDialog();
}

void DialogStore::clickButton()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < _vButton.size(); i++)
		{
			if (PtInRect(&_vButton[i], getCameraPoint()))
			{
				if (i == 0)
				{
					//_isFin = true;
					_store = STORE_MEET;
					_count = _idX = _idY = 0;
					setDialog();
					_open = true;
					
				}
				if (i == 1)
					_isFin = true;
			}
		}
	}
}

void DialogStore::restaurant()
{
	IMAGEMANAGER->findImage("restaurant")->render(UIDC, 0, 0);
	/*IMAGEMANAGER->findImage("rest")->frameRender(UIDC, 744, 216);
	*/
	IMAGEMANAGER->findImage("reslot")->render(UIDC2, 0, 0);
	IMAGEMANAGER->findImage("reslot")->render(UIDC2, 0, 270);
	IMAGEMANAGER->findImage("reslot")->render(UIDC2, 0, 540);
	IMAGEMANAGER->findImage("reslot")->render(UIDC2, 0, 810);
	if (PtInRect(&_rrc, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_scroll = true;
		_mouseY = _ptMouse.y;
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		_scroll = false;
		_currentScroll = _rrc.top - 210;
	}
	if (_scroll == true)
	{
		_rrc = RectMake(686, 210 + _ptMouse.y - _mouseY + _currentScroll, 42, 432);
	}
	if (_rrc.top <= 210)
		_rrc = RectMake(686, 210, 42, 432);
	if (_rrc.bottom >= 932)
		_rrc = RectMake(686, 500, 42, 432);
	if (_rrc.top >= 210 && _rrc.bottom <= 932)
		CAMERAMANAGER->setCameraPoint(PointMake(0,0+(_rrc.top + 1 - 210)*1.4));

	IMAGEMANAGER->findImage("scroll")->render(UIDC, 686, _rrc.top);

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(UIDC, _rrc.left, _rrc.top, _rrc.right, _rrc.bottom);
	}

	_restImg->aniRender(UIDC, 744, 216, _rest);

	//28~31
	char str[128];
	RECT rrc = RectMake(1720, 1000, 200, 50);

	RECT rc = RectMake(35, 35, 100, 50);
	RECT rc2 = RectMake(35, 305, 100, 50);
	RECT rc3 = RectMake(35, 575, 100, 50);
	RECT rc4 = RectMake(35, 845, 100, 50);

	RECT brc = RectMake(455, 165, 100, 50);
	RECT brc2 = RectMake(455, 435, 100, 50);
	RECT brc3 = RectMake(455, 705, 100, 50);
	RECT brc4 = RectMake(455, 975, 100, 50);

	RECT bbrc = RectMake(455, 215, 100, 50);
	RECT bbrc2 = RectMake(455, 485, 100, 50);
	RECT bbrc3 = RectMake(455, 755, 100, 50);
	RECT bbrc4 = RectMake(455, 1025, 100, 50);

	_im->getItem()[34]->getItem().image[0]->render(UIDC, 1120, 540);

	HFONT font, oldFont;
	font = CreateFont(40, 0, 0, 0, 100, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("소야바른9"));
	oldFont = (HFONT)SelectObject(UIDC2, font);
	oldFont = (HFONT)SelectObject(UIDC, font);
	SetTextColor(UIDC2, RGB(255, 255, 255));
	SetTextColor(UIDC, RGB(255, 255, 255));
	SetBkMode(UIDC2, TRANSPARENT);
	SetBkMode(UIDC, TRANSPARENT);
	DrawText(UIDC2, _im->getItem()[33]->getItem().name, strlen(_im->getItem()[33]->getItem().name), &rc, DT_VCENTER);
	DrawText(UIDC2, _im->getItem()[34]->getItem().name, strlen(_im->getItem()[34]->getItem().name), &rc2, DT_VCENTER);
	DrawText(UIDC2, _im->getItem()[35]->getItem().name, strlen(_im->getItem()[35]->getItem().name), &rc3, DT_VCENTER);
	DrawText(UIDC2, _im->getItem()[36]->getItem().name, strlen(_im->getItem()[36]->getItem().name), &rc4, DT_VCENTER);

	DrawText(UIDC2, "20", strlen("20"), &brc, DT_VCENTER);
	DrawText(UIDC2, "30", strlen("30"), &brc2, DT_VCENTER);
	DrawText(UIDC2, "40", strlen("20"), &brc3, DT_VCENTER);
	DrawText(UIDC2, "50", strlen("20"), &brc4, DT_VCENTER);

	DrawText(UIDC2, "500", strlen("500"), &bbrc, DT_VCENTER);
	DrawText(UIDC2, "1000", strlen("1000"), &bbrc2, DT_VCENTER);
	DrawText(UIDC2, "1500", strlen("2000"), &bbrc3, DT_VCENTER);
	DrawText(UIDC2, "2000", strlen("2000"), &bbrc4, DT_VCENTER);

	DrawText(UIDC, itoa(_player->getInven()->getGold(),str,10), strlen(itoa(_player->getInven()->getGold(), str, 10)), &rrc, DT_VCENTER);
	SelectObject(UIDC2, oldFont);
	SelectObject(UIDC, oldFont);
	DeleteObject(font);

	//Rectangle(UIDC, 35, 160, 600, 160);
	//Rectangle(UIDC, 35, 330, 600, 160);
}
