#include "stdafx.h"
#include "DialogWeapon.h"


DialogWeapon::DialogWeapon()
{
}


DialogWeapon::~DialogWeapon()
{
}

HRESULT DialogWeapon::init()
{
	Dialog::init();

	_ansBack = new image;
	_ansBack->init("image/UI/UIdias(400x250).bmp", 400, 180, true, RGB(255, 0, 255));

	_name = "크록";

	_vButton.resize(2);
	_vButtonDialog.resize(2);
	_vDialog.resize(1);



	_vDialog[0].push_back("반갑다. 좋은것들 가져왔다.");

	for (int i = 0; i < _vButton.size(); i++)
	{
		_vButton[i] = RectMake(WINSIZEX - 280, WINSIZEY - 520 + i * 50, 200, 50);
	}
	_vButtonDialog[0] = "상점";
	_vButtonDialog[1] = "아무것도";

	setDialog();
	return S_OK;
}

void DialogWeapon::release()
{
}

void DialogWeapon::update()
{
	keyControl();
	clickButton();
	setFrame();
}

void DialogWeapon::render()
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
	string str = _vDialog[0][0].substr(0, _idX);
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
}

void DialogWeapon::keyControl()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_idX = _vDialog[0][0].size() - 1;
	}

}

void DialogWeapon::setFrame()
{
	_count++;

	if (!(_count % 3))
	{
		if (_idX < _vDialog[0][0].size())
			_idX++;
	}
}

void DialogWeapon::clickButton()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < _vButton.size(); i++)
		{
			if (PtInRect(&_vButton[i], _ptMouse))
			{
				if (i == 1)
				{
					_isFin = true;
				}
			}
		}
	}
}
