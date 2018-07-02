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
	Dialog::init();

	_ansBack = IMAGEMANAGER->findImage("ansBack");

	_name = "밀리아";
	_townStore = TOWNSTORE_RESCUE;

	_vButton.resize(3);
	_vButtonDialog.resize(3);
	_vDialog.resize(3);

	for (int i = 0; i < _vButton.size(); i++)
	{
		_vButton[i] = RectMake(WINSIZEX - 180, WINSIZEY - 550 + i * 50, 200, 50);
	}
	_vButtonDialog[0] = "상점";
	_vButtonDialog[1] = "이야기하기";
	_vButtonDialog[2] = "아무것도";

	setDialog();

	return S_OK;
}

void DialogTownStore::release()
{
}

void DialogTownStore::update()
{
	Dialog::update();
}

void DialogTownStore::render()
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
	font = CreateFont(50, 0, 0, 0, 100, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("소야바른9"));
	oldFont = (HFONT)SelectObject(DC, font);
	SetTextColor(DC, RGB(255, 255, 255));
	SetBkMode(DC, TRANSPARENT);
	if ((int)_townStore == 0 && _idY == 3)
		DrawText(DC, _vDialog[0][2].c_str(), strlen(_vDialog[0][2].c_str()), &_rc[1], DT_VCENTER);
	string str = _vDialog[(int)_townStore][_idY].substr(0, _idX);
	//DrawText(DC, _dialog[(int)_training][_idY].c_str(), strlen(_dialog[(int)_training][_idY].c_str()), &_rc[0], DT_VCENTER);
	if ((int)_townStore == 0 && _idY == 3)
		DrawText(DC, str.c_str(), strlen(str.c_str()), &_rc[2], DT_VCENTER);
	else
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

void DialogTownStore::keyControl()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && PtInRect(&_uiBack->boundingBox(), _ptMouse))
	{
		//changeDialog();
		if(_idX < _vDialog[(int)_townStore][_idY].size() - 1)
			_idX = _vDialog[(int)_townStore][_idY].size() - 1;
		else if ((_idY + 1) < _vDialog[(int)_townStore].size())
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

void DialogTownStore::setFrame()
{
	_count++;

	if (!(_count % 3))
	{
		_count = 0;
		if (_idX < _vDialog[(int)_townStore][_idY].size())
		{
			_idX++;
		}
	}
}

void DialogTownStore::setDialog()
{
	switch (_townStore)
	{
	case TOWNSTORE_RESCUE:
		if (_vDialog[0].size() == 0) _vDialog[0].resize(5);
		else return;
		_vDialog[0][0] = "구해주셔서 감사합니다. 제 이름은 밀리아. 이 마을에서 상점을 운영하고 있었지요.";
		_vDialog[0][1] = "아직 어리지만, 물건의 질은 보장할 수 있으니 걱정하지 않으셔도 되요!";
		_vDialog[0][2] = "응? 장비들을 어떻게 구하냐구요? 그런 건 걱정하지 않아도 된답니다. 상인에겐";
		_vDialog[0][3] = "상인의 방법이 있거든요.";
		_vDialog[0][4] = "앞으로 잘 부탁드릴게요!";
	break;
	case TOWNSTORE_BUILD:
		if (_vDialog[1].size() == 0) _vDialog[1].resize(2);
		else return;
		_vDialog[1][0] = "상점을 지어주셨군요. 제가 생각하던 모습 그대로에요!";
		_vDialog[1][1] = "물건을 사실 때 가격을 깎아드릴테니, 자주 들러주세요!";
	break;
	case TOWNSTORE_NORMAL:
		if (_vDialog[2].size() == 0) _vDialog[2].resize(1);
		else return;
		_vDialog[2][0] = "안녕하세요! 좋은 물건 많이 있어요!";
	break;
	}
}

void DialogTownStore::changeDialog()
{
	switch (_townStore)
	{
	case TOWNSTORE_RESCUE:
		_townStore = TOWNSTORE_BUILD;
	break;
	case TOWNSTORE_BUILD:
		_townStore = TOWNSTORE_NORMAL;
	break;
	case TOWNSTORE_NORMAL:
		_townStore = TOWNSTORE_RESCUE;
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
		for (int i = 0; i < _vButton.size(); i++)
		{
			if (PtInRect(&_vButton[i], _ptMouse))
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
