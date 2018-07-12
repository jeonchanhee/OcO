#include "stdafx.h"
#include "Dialog.h"

Dialog::Dialog() {}
Dialog::~Dialog() {}

HRESULT Dialog::init()
{
	_uiBack = IMAGEMANAGER->findImage("uiBack");
	_ansCur = IMAGEMANAGER->findImage("ansFront");
	_uiNext = IMAGEMANAGER->findImage("uiNext");

	_uiBack->setY(WINSIZEY - 400);
	
	for (int i = 0; i < 3; i++)
	{
		_rc[i] = RectMake(100, WINSIZEY - 300 + i*100, 1800, 100);
	}
	_count = _idX = _idY = 0;
	
	_isFin = false;

	return S_OK;
}

void Dialog::release()
{

}

void Dialog::update()
{
	keyControl();
	clickButton();
	setFrame();
}

void Dialog::render()
{
	_uiBack->render(UIDC, 0, WINSIZEY - 400);
	_uiNext->render(UIDC, WINSIZEX - 100, WINSIZEY - 100);
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		for (int i = 0; i < 3; i++)
		{
			Rectangle(UIDC, _rc[i].left, _rc[i].top, _rc[i].right, _rc[i].bottom);
		}
	}

	HFONT font, oldFont;
	font = CreateFont(80, 0, 0, 0, 100, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("소야바른9"));
	oldFont = (HFONT)SelectObject(UIDC, font);
	SetTextColor(UIDC, RGB(255, 94, 0));
	SetBkMode(UIDC, TRANSPARENT);
	DrawText(UIDC, _name.c_str(), strlen(_name.c_str()), &_rc[0], DT_VCENTER);
	SelectObject(UIDC, oldFont);
	DeleteObject(font);
}

void Dialog::setDialog()
{
}

void Dialog::changeDialog()
{
}
void Dialog::clickButton()
{
}

void Dialog::keyControl()
{
}

void Dialog::setFrame()
{
}