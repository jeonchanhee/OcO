#include "stdafx.h"
#include "Dialog.h"


Dialog::Dialog() {}
Dialog::~Dialog() {}

HRESULT Dialog::init()
{
	_training = TRAINING_RESCUE;
	for (int i = 0; i < 3; i++)
	{
		_rc[i] = RectMake(100, WINSIZEY - 500 + i*100, 1800, 100);
		_button[i] = RectMake(1100, WINSIZEY - 900 + i * 100, 100, 100);
	}
	_click = RectMakeCenter(100, 100, 100, 100);
	_count = _idX = _idY = 0;
	setDialog();
	return S_OK;
}

void Dialog::release()
{

}

void Dialog::update()
{
	_count++;
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//changeDialog();
		_idX = _dialog[(int)_training][_idY].size() - 1;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		changeDialog();
	}

	clickButton();

	if (!(_count % 3))
	{
		if (_idX >= _dialog[(int)_training][_idY].size() && (_idY + 1) < _dialogSize[(int)_training])
		{
			_idY++;
			_idX = 0;
			if (!((int)_training == 4 && _idY == 1))
			Sleep(1200);
		}
		else _idX++;
		//_count = 0;
	}
}

void Dialog::render()
{
	Rectangle(DC, _click.left, _click.top, _click.right, _click.bottom);

	for (int i = 0; i < 3; i++)
	{
		Rectangle(DC, _rc[i].left, _rc[i].top, _rc[i].right, _rc[i].bottom);
		Rectangle(DC, _button[i].left, _button[i].top, _button[i].right, _button[i].bottom);
	}

	HFONT font, oldFont;
	font = CreateFont(50, 0, 0, 0, 100, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("소야바른9"));
	oldFont = (HFONT)SelectObject(DC, font);
	if ((int)_training == 4 && _idY == 1)
		DrawText(DC, _dialog[4][0].c_str(), strlen(_dialog[4][0].c_str()), &_rc[0], DT_VCENTER);
	string str = _dialog[(int)_training][_idY].substr(0, _idX);
	//DrawText(DC, _dialog[(int)_training][_idY].c_str(), strlen(_dialog[(int)_training][_idY].c_str()), &_rc[0], DT_VCENTER);
	if ((int)_training == 4 && _idY == 1)
		DrawText(DC, str.c_str(), strlen(str.c_str()), &_rc[1], DT_VCENTER);
	else
		DrawText(DC, str.c_str(), strlen(str.c_str()), &_rc[0], DT_VCENTER);
	SelectObject(DC, oldFont);
	DeleteObject(font);

	char str1[128];
	sprintf_s(str1, "size : %d, count : %d", _dialog[(int)_training][_idY].size(), _count/10);
	TextOut(DC, 300, 100, str1, strlen(str1));
}

void Dialog::setDialog()
{
	switch (_training)
	{
	case TRAINING_RESCUE:
		_dialog[0][0] = "자네는..모험가인가? 옛날에 기사 훈련을 하면서 자네같은 모험가를 많이 보았지.";
		_dialog[0][1] = "그 목걸이... 생각해보니 그런 방법이 있었군. 일단 마을에서 보도록 하지!";
		_dialogSize[0] = 2;
	break;
	case TRAINING_AFTER_RESCUE:
		_dialog[1][0] = "마을! 드디어!";
		_dialog[1][1] = "지금까지 마을지도를 가지고 다녀서 괜찮았건만..!";
		_dialog[1][2] = "주섬주섬 (꾸깃꾸깃한 지도를 꺼냈다. 지도를 거꾸로 보고 있는 것 같다)";
		_dialog[1][3] = "이곳도 새로 지도를 그려야 하는가. 아 참, 내 이름은 카블로비나.";
		_dialog[1][4] = "이 마을에서 마을 경비대의 훈련을 맡고 있지. 잘 부탁하네!";
		_dialogSize[1] = 5;
	break;
	case TRAINING_BUILD:
		_dialog[2][0] = "훈련장을 지어줬군! 고맙네!";
		_dialog[2][1] = "자네의 능력을 훈련하고 싶으면 언제든지 내게로 오게나. 마을 서쪽에 있으니!";
		_dialogSize[2] = 2;
	break;
	case TRAINING_BUILDING:
		_dialog[3][0] = "자네 왔군! 훈련할 텐가?";
		_dialogSize[3] = 1;
	break;
	case TRAINING_DIALOG:
		_dialog[4][0] = "율포드님에게 말씀드려서, 건물들을 원래 있던 자리에 다시 세워달라고 말씀드렸는데,";
		_dialog[4][1] = "거절하셨네.";
		_dialog[4][2] = "재건하는 사람들이 다른 곳을 느껴보고 싶다나..훈련장만이 예전 위치 그대로라네.";
		_dialogSize[4] = 3;
	break;
	}
}

void Dialog::changeDialog()
{
	switch (_training)
	{
	case TRAINING_RESCUE:
		_training = TRAINING_AFTER_RESCUE;
		break;
	case TRAINING_AFTER_RESCUE:
		_training = TRAINING_BUILD;
		break;
	case TRAINING_BUILD:
		_training = TRAINING_BUILDING;
		break;
	case TRAINING_DIALOG:
		_training = TRAINING_AFTER_RESCUE;
		break;
	}
	_count = _idX = _idY = 0;
	setDialog();
}
void Dialog::clickButton()
{
	if (_training != TRAINING_BUILDING) return;

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < 3; i++)
		{
			if (PtInRect(&_button[i], _ptMouse))
			{
				if (i == 1)
				{
					_training = TRAINING_DIALOG;
					_count = _idX = _idY = 0;
					setDialog();
				}
				break;
			}
		}
	}
}