#include "stdafx.h"
#include "DialogWeapon.h"
#include "itemManager.h"
#include "Player.h"


DialogWeapon::DialogWeapon()
{
}


DialogWeapon::~DialogWeapon()
{
}

HRESULT DialogWeapon::init()
{
	Dialog::init();

	_ansBack = new image;
	_ansBack->init("image/UI/UIdias(400x250).bmp", 400, 180, true, RGB(255, 0, 255));

	_name = "크록";

	_vButton.resize(2);
	_vButtonDialog.resize(2);
	_vDialog.resize(1);



	_vDialog[0].push_back("반갑다. 좋은것들 가져왔다.");

	for (int i = 0; i < _vButton.size(); i++)
	{
		_vButton[i] = RectMake(WINSIZEX - 280, WINSIZEY - 520 + i * 50, 200, 50);
	}
	_vButtonDialog[0] = "상점";
	_vButtonDialog[1] = "아무것도";

	setDialog();

	_open = false;
	_reset = false;

	_isWeapon = false;

	return S_OK;
}

void DialogWeapon::release()
{
}

void DialogWeapon::update()
{
	keyControl();
	clickButton();
	setFrame();
	
}

void DialogWeapon::render()
{
	if (_open == false)
	{

	Dialog::render();

	
		_ansBack->render(UIDC, WINSIZEX - 350, WINSIZEY - 550);

		if (KEYMANAGER->isToggleKey(VK_TAB))
		{
			Rectangle(UIDC, _uiBack->boundingBox().left, _uiBack->boundingBox().top, _uiBack->boundingBox().right, _uiBack->boundingBox().bottom);
			for (int i = 0; i < _vButton.size(); i++)
			{
				Rectangle(UIDC, _vButton[i].left, _vButton[i].top, _vButton[i].right, _vButton[i].bottom);
			}
		}
		HFONT font, oldFont;
		font = CreateFont(50, 0, 0, 0, 100, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("소야바른9"));
		oldFont = (HFONT)SelectObject(UIDC, font);
		SetTextColor(UIDC, RGB(255, 255, 255));
		SetBkMode(UIDC, TRANSPARENT);
		string str = _vDialog[0][0].substr(0, _idX);
		DrawText(UIDC, str.c_str(), strlen(str.c_str()), &_rc[1], DT_VCENTER);
		SelectObject(UIDC, oldFont);
		DeleteObject(font);

		font = CreateFont(50, 0, 0, 0, 100, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("소야바른9"));
		oldFont = (HFONT)SelectObject(UIDC, font);
		for (int i = 0; i < _vButton.size(); i++)
		{
			DrawText(UIDC, _vButtonDialog[i].c_str(), strlen(_vButtonDialog[i].c_str()), &_vButton[i], DT_VCENTER | DT_CENTER);
		}
		SelectObject(UIDC, oldFont);
		DeleteObject(font);
		_start = 1;
	}

	if (_open == true)
	{
		if (_reset == false)
		{
			resetShop();
			_reset = true;
		}
		shop();
		_start = 3;
	}
}

void DialogWeapon::keyControl()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_idX = _vDialog[0][0].size() - 1;
	}
	if (KEYMANAGER->isOnceKeyDown('F'))
	{
		_open = false;
		_player->getInven()->setOnInven(false);
		_canMove = true;
	}
}

void DialogWeapon::setFrame()
{
	_count++;

	if (!(_count % 3))
	{
		if (_idX < _vDialog[0][0].size())
			_idX++;
	}
}

void DialogWeapon::clickButton()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < _vButton.size(); i++)
		{
			if (PtInRect(&_vButton[i], _ptMouse))
			{
				if (i == 0)
				{
					_open = true;
					_player->getInven()->setOnInven(true);
					_canMove = false;
					_isWeapon = true;
					
				}
				if (i == 1)
				{
					_isFin = true;
					_start = 0;
				}
			}
		}
	}
}

void DialogWeapon::shop()
{
	char str[128];
	RECT rc[5], rc1[5], rc2[5], rc3[5];
	IMAGEMANAGER->findImage("shopUI")->render(UIDC, 0, 0);
	for (int i = 0; i < 5; i++)
	{
		rc1[i] = RectMake(165, 180 + 170 * i, 493, 126);
		IMAGEMANAGER->findImage("slot")->render(UIDC, 165, 180 + 170 * i);
	}
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		for (int i = 0; i < 5; i++)
			Rectangle(UIDC, rc1[i].left, rc1[i].top, rc1[i].right, rc1[i].bottom);
	}

	HFONT font, oldFont;
	font = CreateFont(40, 0, 0, 0, 100, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("소야바른9"));
	oldFont = (HFONT)SelectObject(UIDC, font);
	SetTextColor(UIDC, RGB(255, 255, 255));
	SetBkMode(UIDC, TRANSPARENT);
	for (int i = 0; i < 5; i++)
	{
		rc[i] = RectMake(50, 220 + 170 * i, 100, 100);
		rc2[i] = RectMake(200, 200 + 170 * i, 100, 100);
		rc3[i] = RectMake(500, 255 + 170 * i, 100, 100);

		if (_itemNum[i] != 0)
		{
			_im->getItem()[_itemNum[i]]->getItem().image[0]->render(UIDC, rc[i].left, rc[i].top);

			DrawText(UIDC, _im->getItem()[_itemNum[i]]->getItem().name, strlen(_im->getItem()[_itemNum[i]]->getItem().name), &rc2[i], DT_VCENTER);
			DrawText(UIDC, itoa(_im->getItem()[_itemNum[i]]->getItem().price, str, 10), strlen(itoa(_im->getItem()[_itemNum[i]]->getItem().price, str, 10)), &rc3[i], DT_VCENTER);
		}
		else
			IMAGEMANAGER->findImage("thank")->render(UIDC, rc2[i].left, rc2[i].top);
	}

	SelectObject(UIDC, oldFont);
	DeleteObject(font);
	for (int i = 0; i < 5; i++)
	{
		if (PtInRect(&rc1[i], _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_RBUTTON) && _itemNum[i] != 0 && _player->getInven()->getItem().size() < INVENSIZE&&_im->getItem()[_itemNum[i]]->getItem().price <= _player->getInven()->getGold())
		{
			_player->getInven()->setGold(_player->getInven()->getGold() - _im->getItem()[_itemNum[i]]->getItem().price);
			_player->getInven()->buyItem(_itemNum[i]);
			_itemNum[i] = 0;
		}
	}
}

void DialogWeapon::resetShop()
{
	//2~33
	int rand;
	for (int i = 0; i < 5; i++)
	{
		_itemNum[i] = 0;
		while (1)
		{
			rand = RND->getFromIntTo(2, 33);
			if (_itemNum[0] != rand && _itemNum[1] != rand && _itemNum[2] != rand && _itemNum[3] != rand && _itemNum[4] != rand)
			{
				_itemNum[i] = rand;
				break;
			}
		}
	}
}