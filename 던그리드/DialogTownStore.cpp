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
	_name = "�и���";
	
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
	font = CreateFont(80, 0, 0, 0, 100, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("�Ҿ߹ٸ�9"));
	oldFont = (HFONT)SelectObject(DC, font);
	SetTextColor(DC, RGB(255, 94, 0));
	//DrawText(DC, _dialog[(int)_training][_idY].c_str(), strlen(_dialog[(int)_training][_idY].c_str()), &_rc[0], DT_VCENTER);
	DrawText(DC, _name.c_str(), strlen(_name.c_str()), &_rc[0], DT_VCENTER);
	SelectObject(DC, oldFont);
	DeleteObject(font);

	font = CreateFont(50, 0, 0, 0, 100, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("�Ҿ߹ٸ�9"));
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
		_dialog[0][0] = "�����ּż� �����մϴ�. �� �̸��� �и���. �� �������� ������ ��ϰ� �־�����.";
		_dialog[0][1] = "���� �����, ������ ���� ������ �� ������ �������� �����ŵ� �ǿ�!";
		_dialog[0][2] = "��? ������ ��� ���ϳı���? �׷� �� �������� �ʾƵ� �ȴ�ϴ�. ���ο���";
		_dialog[0][3] = "������ ����� �ְŵ��.";
		_dialog[0][4] = "������ �� ��Ź�帱�Կ�!";
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
