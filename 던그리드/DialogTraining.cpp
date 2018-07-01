#include "stdafx.h"
#include "DialogTraining.h"


DialogTraining::DialogTraining() {}
DialogTraining::~DialogTraining() {}

HRESULT DialogTraining::init()
{
	Dialog::init();

	_ansBack = new image;
	_ansBack->init("image/UI/UIdias(400x250).bmp", 400, 320, true, RGB(255, 0, 255));

	_name = "카블로비나";
	_training = TRAINING_RESCUE;

	_vButton.resize(4);
	_vButtonDialog.resize(4);
	_vDialog.resize(5);

	for (int i = 0; i < _vButton.size(); i++)
	{
		_vButton[i] = RectMake(WINSIZEX - 180, WINSIZEY - 600 + i * 50, 200, 50);
	}
	_vButtonDialog[0] = "훈련장";
	_vButtonDialog[1] = "이야기하기";
	_vButtonDialog[2] = "초기화";
	_vButtonDialog[3] = "아무것도";

	setDialog();
	return S_OK;
}

void DialogTraining::release()
{

}

void DialogTraining::update()
{
	keyControl();
	clickButton();
	setFrame();
}

void DialogTraining::render()
{
	Dialog::render();

	_ansBack->render(DC, WINSIZEX - 200, WINSIZEY - 650);

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
	if ((int)_training == 4 && _idY == 1)
		DrawText(DC, _vDialog[4][0].c_str(), strlen(_vDialog[4][0].c_str()), &_rc[1], DT_VCENTER);
	string str = _vDialog[(int)_training][_idY].substr(0, _idX);
	if ((int)_training == 4 && _idY == 1)
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

void DialogTraining::keyControl()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && PtInRect(&_uiBack->boundingBox(), _ptMouse))
	{
		//changeDialog();
		if (_idX < _vDialog[(int)_training][_idY].size() - 1)
			_idX = _vDialog[(int)_training][_idY].size() - 1;
		else if ((_idY + 1) < _vDialog[(int)_training].size())
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

void DialogTraining::setFrame()
{
	_count++;

	if (!(_count % 3))
	{
		_count = 0;
		if (_idX < _vDialog[(int)_training][_idY].size())
		{
			_idX++;
		}
	}
}

void DialogTraining::setDialog()
{
	switch (_training)
	{
	case TRAINING_RESCUE:
		if (_vDialog[0].size() == 0) _vDialog[0].resize(2);
		else return;
		_vDialog[0][0] = "자네는..모험가인가? 옛날에 기사 훈련을 하면서 자네같은 모험가를 많이 보았지.";
		_vDialog[0][1] = "그 목걸이... 생각해보니 그런 방법이 있었군. 일단 마을에서 보도록 하지!";
	break;
	case TRAINING_AFTER_RESCUE:
		if (_vDialog[1].size() == 0) _vDialog[1].resize(5);
		else return;
		_vDialog[1][0] = "마을! 드디어!";
		_vDialog[1][1] = "지금까지 마을지도를 가지고 다녀서 괜찮았건만..!";
		_vDialog[1][2] = "주섬주섬 (꾸깃꾸깃한 지도를 꺼냈다. 지도를 거꾸로 보고 있는 것 같다)";
		_vDialog[1][3] = "이곳도 새로 지도를 그려야 하는가. 아 참, 내 이름은 카블로비나.";
		_vDialog[1][4] = "이 마을에서 마을 경비대의 훈련을 맡고 있지. 잘 부탁하네!";
	break;
	case TRAINING_BUILD:
		if (_vDialog[2].size() == 0) _vDialog[2].resize(2);
		else return;
		_vDialog[2][0] = "훈련장을 지어줬군! 고맙네!";
		_vDialog[2][1] = "자네의 능력을 훈련하고 싶으면 언제든지 내게로 오게나. 마을 서쪽에 있으니!";
	break;
	case TRAINING_BUILDING:
		if (_vDialog[3].size() == 0) _vDialog[3].resize(1);
		else return;
		_vDialog[3][0] = "자네 왔군! 훈련할 텐가?";
	break;
	case TRAINING_DIALOG:
		if (_vDialog[4].size() == 0) _vDialog[4].resize(3);
		else return;
		_vDialog[4][0] = "율포드님에게 말씀드려서, 건물들을 원래 있던 자리에 다시 세워달라고 말씀드렸는데,";
		_vDialog[4][1] = "거절하셨네.";
		_vDialog[4][2] = "재건하는 사람들이 다른 곳을 느껴보고 싶다나..훈련장만이 예전 위치 그대로라네.";
	break;
	}
}

void DialogTraining::changeDialog()
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
void DialogTraining::clickButton()
{
	if (_training != TRAINING_BUILDING) return;

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < _vButton.size(); i++)
		{
			if (PtInRect(&_vButton[i], _ptMouse))
			{
				if (i == 1)
				{
					_training = TRAINING_DIALOG;
					_count = _idX = _idY = 0;
					setDialog();
				}
			}
		}
	}
}