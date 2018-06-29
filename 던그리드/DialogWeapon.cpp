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
	_name = "ũ��";

	_dialog = "�ݰ���. �����͵� �����Դ�.";

	for (int i = 0; i < 3; i++)
	{
		_rc[i] = RectMake(100, WINSIZEY - 500 + i * 100, 1800, 100);
		_button[i] = RectMake(1100, WINSIZEY - 900 + i * 100, 100, 100);
	}
	_click = RectMakeCenter(100, 100, 100, 100);
	_count = _idX = _idY = 0;

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
	Rectangle(getMemDC(), _click.left, _click.top, _click.right, _click.bottom);

	for (int i = 0; i < 3; i++)
	{
		Rectangle(getMemDC(), _rc[i].left, _rc[i].top, _rc[i].right, _rc[i].bottom);
		Rectangle(getMemDC(), _button[i].left, _button[i].top, _button[i].right, _button[i].bottom);
	}

	HFONT font, oldFont;
	font = CreateFont(80, 0, 0, 0, 100, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("�Ҿ߹ٸ�9"));
	oldFont = (HFONT)SelectObject(getMemDC(), font);
	SetTextColor(getMemDC(), RGB(255, 94, 0));
	//DrawText(getMemDC(), _dialog[(int)_training][_idY].c_str(), strlen(_dialog[(int)_training][_idY].c_str()), &_rc[0], DT_VCENTER);
	DrawText(getMemDC(), _name.c_str(), strlen(_name.c_str()), &_rc[0], DT_VCENTER);
	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);

	font = CreateFont(50, 0, 0, 0, 100, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("�Ҿ߹ٸ�9"));
	oldFont = (HFONT)SelectObject(getMemDC(), font);
	SetTextColor(getMemDC(), RGB(0, 0, 0));
	string str = _dialog.substr(0, _idX);
	//DrawText(getMemDC(), _dialog[(int)_training][_idY].c_str(), strlen(_dialog[(int)_training][_idY].c_str()), &_rc[0], DT_VCENTER);
	DrawText(getMemDC(), str.c_str(), strlen(str.c_str()), &_rc[1], DT_VCENTER);
	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);

	char str1[128];
	sprintf_s(str1, "size : %d, count : %d", _dialog.size(), _count / 10);
	TextOut(getMemDC(), 300, 100, str1, strlen(str1));

}

void DialogWeapon::keyControl()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//changeDialog();
		_idX = _dialog.size() - 1;
	}
}

void DialogWeapon::setFrame()
{
	_count++;

	if (!(_count % 3))
	{
		if (_idX < _dialog.size())
			_idX++;
	}
}

void DialogWeapon::clickButton()
{
	return;

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < 3; i++)
		{
			if (PtInRect(&_button[i], _ptMouse))
			{
				if (i == 1)
				{
					_count = _idX = _idY = 0;
				}
			}
		}
	}
}
