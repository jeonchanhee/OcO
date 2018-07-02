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
	Dialog::init();

	_ansBack = IMAGEMANAGER->findImage("ansBack");

	_name = "������";
	_elder = ELDER_BUILD;

	_vButton.resize(3);
	_vButtonDialog.resize(3);
	_vDialog.resize(2);

	for (int i = 0; i < _vButton.size(); i++)
	{
		_vButton[i] = RectMake(WINSIZEX - 180, WINSIZEY - 550 + i * 50, 200, 50);
	}
	_vButtonDialog[0] = "�Ǽ�";
	_vButtonDialog[1] = "�̾߱��ϱ�";
	_vButtonDialog[2] = "�ƹ��͵�";

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
	Dialog::render();

	_ansBack->render(DC, WINSIZEX - 200, WINSIZEY - 600);

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		for (int i = 0; i < _vButton.size(); i++)
		{
			Rectangle(DC, _vButton[i].left, _vButton[i].top, _vButton[i].right, _vButton[i].bottom);
		}
	}
	HFONT font, oldFont;
	font = CreateFont(50, 0, 0, 0, 100, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("�Ҿ߹ٸ�9"));
	oldFont = (HFONT)SelectObject(DC, font);
	SetTextColor(DC, RGB(255, 255, 255));
	SetBkMode(DC, TRANSPARENT);
	string str = _vDialog[(int)_elder][_idY].substr(0, _idX);
	//DrawText(DC, _dialog[(int)_training][_idY].c_str(), strlen(_dialog[(int)_training][_idY].c_str()), &_rc[0], DT_VCENTER);
	DrawText(DC, str.c_str(), strlen(str.c_str()), &_rc[1], DT_VCENTER);
	SelectObject(DC, oldFont);
	DeleteObject(font);

	font = CreateFont(50, 0, 0, 0, 100, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("�Ҿ߹ٸ�9"));
	oldFont = (HFONT)SelectObject(DC, font);
	for (int i = 0; i < _vButton.size(); i++)
	{
		DrawText(DC, _vButtonDialog[i].c_str(), strlen(_vButtonDialog[i].c_str()), &_vButton[i], DT_VCENTER | DT_CENTER);
	}
	SelectObject(DC, oldFont);
	DeleteObject(font);
}

void DialogElder::keyControl()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && PtInRect(&_uiBack->boundingBox(), _ptMouse))
	{
		//changeDialog();
		if (_idX < _vDialog[(int)_elder][_idY].size() - 1)
			_idX = _vDialog[(int)_elder][_idY].size() - 1;
		else if ((_idY + 1) < _vDialog[(int)_elder].size())
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

void DialogElder::setFrame()
{
	_count++;

	if (!(_count % 3))
	{
		_count = 0;
		if (_idX < _vDialog[(int)_elder][_idY].size())
		{
			_idX++;
		}
	}
}

void DialogElder::setDialog()
{
	switch (_elder)
	{
	case ELDER_BUILD:
		if (_vDialog[0].size() == 0) _vDialog[0].resize(1);
		else return;
		_vDialog[0][0] = "��, �ڳױ�.";
		break;
	case ELDER_DIALOG:
		if (_vDialog[1].size() == 0) _vDialog[1].resize(3);
		else return;
		_vDialog[1][0] = "������ ������ ������ �����ϴ� ����, ������ ���� ���� ��簡 ��Ÿ���ٰ� �ϳ�.";
		_vDialog[1][1] = "���ִ� �丮�� ���յ��� ���ϸ� ������Ű�� ���� ������� ����´ٰ� �ϴ���.";
		_vDialog[1][2] = "Ȳ���� �̾߱�����, �̾߱Ⱑ ��� å�� �׷��� ������ũ�� ���� ��������������...";
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
		for (int i = 0; i < _vButton.size(); i++)
		{
			if (PtInRect(&_vButton[i], _ptMouse))
			{
				if (i == 1)
				{
					_elder = ELDER_DIALOG;
					_count = _idX = _idY = 0;
					setDialog();
				}
			}
		}
	}
}
