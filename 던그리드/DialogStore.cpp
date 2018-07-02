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

	_name = "ȣ����ī";
	_store = STORE_MEET;

	_vButton.resize(2);
	_vButtonDialog.resize(2);
	_vDialog.resize(2);

	for (int i = 0; i < _vButton.size(); i++)
	{
		_vButton[i] = RectMake(WINSIZEX - 180, WINSIZEY - 520 + i * 50, 200, 50);
	}
	_vButtonDialog[0] = "������";
	_vButtonDialog[1] = "�ƹ��͵�";

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
	font = CreateFont(50, 0, 0, 0, 100, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("�Ҿ߹ٸ�9"));
	oldFont = (HFONT)SelectObject(DC, font);
	SetTextColor(DC, RGB(255, 255, 255));
	SetBkMode(DC, TRANSPARENT);
	string str = _vDialog[(int)_store][_idY].substr(0, _idX);
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
		_vDialog[0][0] = "�ȳ��ϼ��� �����ڴ�. ���� ȣ����ī ��� �մϴ�.";
		_vDialog[0][1] = "���� ������ ������ å������ �� �����������μ� ����� ���ϱ� ���ؼ�,";
		_vDialog[0][2] = "���� ���� �����ڵ鿡�� ������ �����ص帮�� �ֽ��ϴ�.";
		_vDialog[0][3] = "��Ḧ �����ؼ� ����� ������, �ε� ���� ����ּ���.";
	break;
	case STORE_BUY:
		if (_vDialog[1].size() == 0) _vDialog[1].resize(1);
		_vDialog[1][0] = "������ � �丮�� ��÷� ���̳���?";
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
