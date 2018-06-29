#include "stdafx.h"
#include "DialogElder.h"


DialogElder::DialogElder()
{
}


DialogElder::~DialogElder()
{
}

HRESULT DialogElder::init()
{
	_name = "������";

	_elder = ELDER_BUILD;

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

void DialogElder::release()
{
}

void DialogElder::update()
{
	keyControl();
	clickButton();
	setFrame();
}

void DialogElder::render()
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
	string str = _dialog[(int)_elder][_idY].substr(0, _idX);
	//DrawText(DC, _dialog[(int)_training][_idY].c_str(), strlen(_dialog[(int)_training][_idY].c_str()), &_rc[0], DT_VCENTER);
	DrawText(DC, str.c_str(), strlen(str.c_str()), &_rc[1], DT_VCENTER);
	SelectObject(DC, oldFont);
	DeleteObject(font);

	char str1[128];
	sprintf_s(str1, "size : %d, count : %d", _dialog[(int)_elder][_idY].size(), _count / 10);
	TextOut(DC, 300, 100, str1, strlen(str1));

}

void DialogElder::keyControl()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//changeDialog();
		_idX = _dialog[(int)_elder][_idY].size() - 1;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		changeDialog();
	}
}

void DialogElder::setFrame()
{
	_count++;

	if (!(_count % 3))
	{
		if (_idX >= _dialog[(int)_elder][_idY].size() && (_idY + 1) < _dialogSize[(int)_elder])
		{
			_idY++;
			_idX = 0;
			Sleep(1200);
		}
		else _idX++;
	}
}

void DialogElder::setDialog()
{
	switch (_elder)
	{
	case ELDER_BUILD:
		_dialog[0][0] = "��, �ڳױ�.";
		_dialogSize[0] = 1;
		break;
	case ELDER_DIALOG:
		_dialog[1][0] = "������ ������ ������ �����ϴ� ����, ������ ���� ���� ��簡 ��Ÿ���ٰ� �ϳ�.";
		_dialog[1][1] = "���ִ� �丮�� ���յ��� ���ϸ� ������Ű�� ���� ������� ����´ٰ� �ϴ���.";
		_dialog[1][2] = "Ȳ���� �̾߱�����, �̾߱Ⱑ ��� å�� �׷��� ������ũ�� ���� ��������������...";
		_dialogSize[1] = 3;
		break;
	}
}

void DialogElder::changeDialog()
{
	switch (_elder)
	{
	case ELDER_BUILD:
		_elder = ELDER_DIALOG;
		break;
	case ELDER_DIALOG:
		_elder = ELDER_BUILD;
		break;
	}
	_count = _idX = _idY = 0;
	setDialog();
}

void DialogElder::clickButton()
{
	if (_elder != ELDER_BUILD) return;

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < 3; i++)
		{
			if (PtInRect(&_button[i], _ptMouse))
			{
				if (i == 1)
				{
					_elder = ELDER_BUILD;
					_count = _idX = _idY = 0;
					setDialog();
				}
			}
		}
	}
}
