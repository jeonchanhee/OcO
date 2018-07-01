#include "stdafx.h"
#include "DialogStore.h"


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
	_store = STORE_MEET;

	_vButton.resize(2);
	_vButtonDialog.resize(2);
	_vDialog.resize(2);

	for (int i = 0; i < _vButton.size(); i++)
	{
		_vButton[i] = RectMake(WINSIZEX - 180, WINSIZEY - 520 + i * 50, 200, 50);
	}
	_vButtonDialog[0] = "음식점";
	_vButtonDialog[1] = "아무것도";

	setDialog();

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

	_ansBack->render(DC, WINSIZEX - 200, WINSIZEY - 550);

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(DC, _uiBack->boundingBox().left, _uiBack->boundingBox().top, _uiBack->boundingBox().right, _uiBack->boundingBox().bottom);
		for (int i = 0; i < _vButton.size(); i++)
		{
			Rectangle(DC, _vButton[i].left, _vButton[i].top, _vButton[i].right, _vButton[i].bottom);
		}
	}
	HFONT font, oldFont;
	font = CreateFont(50, 0, 0, 0, 100, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("소야바른9"));
	oldFont = (HFONT)SelectObject(DC, font);
	SetTextColor(DC, RGB(255, 255, 255));
	SetBkMode(DC, TRANSPARENT);
	string str = _vDialog[(int)_store][_idY].substr(0, _idX);
	//DrawText(DC, _dialog[(int)_training][_idY].c_str(), strlen(_dialog[(int)_training][_idY].c_str()), &_rc[0], DT_VCENTER);
	DrawText(DC, str.c_str(), strlen(str.c_str()), &_rc[1], DT_VCENTER);
	SelectObject(DC, oldFont);
	DeleteObject(font);

	font = CreateFont(50, 0, 0, 0, 100, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("소야바른9"));
	oldFont = (HFONT)SelectObject(DC, font);
	for (int i = 0; i < _vButton.size(); i++)
	{
		DrawText(DC, _vButtonDialog[i].c_str(), strlen(_vButtonDialog[i].c_str()), &_vButton[i], DT_VCENTER | DT_CENTER);
	}
	SelectObject(DC, oldFont);
	DeleteObject(font);
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
	//return;

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < _vButton.size(); i++)
		{
			if (PtInRect(&_vButton[i], _ptMouse))
			{
				if (i == 0)
				{
					_store = STORE_MEET;
					_count = _idX = _idY = 0;
					setDialog();
				}
			}
		}
	}
}
