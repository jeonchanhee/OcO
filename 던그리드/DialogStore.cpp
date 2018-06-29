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
	_name = "ȣ����ī";

	_store = STORE_MEET;

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
	string str = _dialog[(int)_store][_idY].substr(0, _idX);
	//DrawText(DC, _dialog[(int)_training][_idY].c_str(), strlen(_dialog[(int)_training][_idY].c_str()), &_rc[0], DT_VCENTER);
	DrawText(DC, str.c_str(), strlen(str.c_str()), &_rc[1], DT_VCENTER);
	SelectObject(DC, oldFont);
	DeleteObject(font);

	char str1[128];
	sprintf_s(str1, "size : %d, count : %d", _dialog[(int)_store][_idY].size(), _count / 10);
	TextOut(DC, 300, 100, str1, strlen(str1));

}

void DialogStore::keyControl()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//changeDialog();
		_idX = _dialog[(int)_store][_idY].size() - 1;
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
		if (_idX >= _dialog[(int)_store][_idY].size() && (_idY + 1) < _dialogSize[(int)_store])
		{
			_idY++;
			_idX = 0;
			Sleep(1200);
		}
		else _idX++;
	}
}

void DialogStore::setDialog()
{
	switch (_store)
	{
	case STORE_MEET:
		_dialog[0][0] = "�ȳ��ϼ��� �����ڴ�. ���� ȣ����ī ��� �մϴ�.";
		_dialog[0][1] = "���� ������ ������ å������ �� �����������μ� ����� ���ϱ� ���ؼ�,";
		_dialog[0][2] = "���� ���� �����ڵ鿡�� ������ �����ص帮�� �ֽ��ϴ�.";
		_dialog[0][3] = "��Ḧ �����ؼ� ����� ������, �ε� ���� ����ּ���.";
		_dialogSize[0] = 4;
	break;
	case STORE_BUY:
		_dialog[1][0] = "������ � �丮�� ��÷� ���̳���?";
		_dialogSize[1] = 1;
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
