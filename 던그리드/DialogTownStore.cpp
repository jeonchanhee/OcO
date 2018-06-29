#include "stdafx.h"
#include "DialogTownStore.h"


DialogTownStore::DialogTownStore()
{
}


DialogTownStore::~DialogTownStore()
{
}

HRESULT DialogTownStore::init()
{
	_name = "밀리아";
	
	_townStore = TOWNSTORE_RESCUE;

	for (int i = 0; i < 3; i++)
	{
		_rc[i] = RectMake(100, WINSIZEY - 500 + i * 100, 1800, 100);
		_button[i] = RectMake(1100, WINSIZEY - 900 + i * 100, 100, 100);
	}
	_click = RectMakeCenter(100, 100, 100, 100);
	_count = _idX = _idY = 0;
	setDialog();

	return S_OK;
}

void DialogTownStore::release()
{
}

void DialogTownStore::update()
{
	keyControl();
	clickButton();
	setFrame();
}

void DialogTownStore::render()
{
	Rectangle(DC, _click.left, _click.top, _click.right, _click.bottom);

	for (int i = 0; i < 3; i++)
	{
		Rectangle(DC, _rc[i].left, _rc[i].top, _rc[i].right, _rc[i].bottom);
		Rectangle(DC, _button[i].left, _button[i].top, _button[i].right, _button[i].bottom);
	}

	HFONT font, oldFont;
	font = CreateFont(80, 0, 0, 0, 100, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("소야바른9"));
	oldFont = (HFONT)SelectObject(DC, font);
	SetTextColor(DC, RGB(255, 94, 0));
	//DrawText(DC, _dialog[(int)_training][_idY].c_str(), strlen(_dialog[(int)_training][_idY].c_str()), &_rc[0], DT_VCENTER);
	DrawText(DC, _name.c_str(), strlen(_name.c_str()), &_rc[0], DT_VCENTER);
	SelectObject(DC, oldFont);
	DeleteObject(font);

	font = CreateFont(50, 0, 0, 0, 100, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("소야바른9"));
	oldFont = (HFONT)SelectObject(DC, font);
	SetTextColor(DC, RGB(0, 0, 0));
	if ((int)_townStore == 0 && _idY == 3)
		DrawText(DC, _dialog[0][2].c_str(), strlen(_dialog[0][2].c_str()), &_rc[1], DT_VCENTER);
	string str = _dialog[(int)_townStore][_idY].substr(0, _idX);
	//DrawText(DC, _dialog[(int)_training][_idY].c_str(), strlen(_dialog[(int)_training][_idY].c_str()), &_rc[0], DT_VCENTER);
	if ((int)_townStore == 0 && _idY == 3)
		DrawText(DC, str.c_str(), strlen(str.c_str()), &_rc[2], DT_VCENTER);
	else
		DrawText(DC, str.c_str(), strlen(str.c_str()), &_rc[1], DT_VCENTER);
	SelectObject(DC, oldFont);
	DeleteObject(font);

	char str1[128];
	sprintf_s(str1, "size : %d, count : %d", _dialog[(int)_townStore][_idY].size(), _count / 10);
	TextOut(DC, 300, 100, str1, strlen(str1));
}

void DialogTownStore::keyControl()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//changeDialog();
		_idX = _dialog[(int)_townStore][_idY].size() - 1;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		changeDialog();
	}
}

void DialogTownStore::setFrame()
{
	_count++;

	if (!(_count % 3))
	{
		if (_idX >= _dialog[(int)_townStore][_idY].size() && (_idY + 1) < _dialogSize[(int)_townStore])
		{
			_idY++;
			_idX = 0;
			if (!((int)_townStore == 0 && _idY == 3))
				Sleep(1200);
		}
		else _idX++;
	}
}

void DialogTownStore::setDialog()
{
	switch (_townStore)
	{
	case TOWNSTORE_RESCUE:
		_dialog[0][0] = "구해주셔서 감사합니다. 제 이름은 밀리아. 이 마을에서 상점을 운영하고 있었지요.";
		_dialog[0][1] = "아직 어리지만, 물건의 질은 보장할 수 있으니 걱정하지 않으셔도 되요!";
		_dialog[0][2] = "응? 장비들을 어떻게 구하냐구요? 그런 건 걱정하지 않아도 된답니다. 상인에겐";
		_dialog[0][3] = "상인의 방법이 있거든요.";
		_dialog[0][4] = "앞으로 잘 부탁드릴게요!";
		_dialogSize[0] = 5;
	break;
	}
}

void DialogTownStore::changeDialog()
{
	switch (_townStore)
	{
	case TOWNSTORE_RESCUE:
		
	break;
	}
	_count = _idX = _idY = 0;
	setDialog();
}

void DialogTownStore::clickButton()
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
					setDialog();
				}
			}
		}
	}
}
