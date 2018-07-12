#include "stdafx.h"
#include "inven.h"


HRESULT inven::init()
{
	_onInven = false , _onMouseInven = false, _onMouseAc = false, _onMouseMain = false, _onMouseAs =false , _onInven =false;
	for (int i = 0; i < 15; ++i)
	{
		_image[i] = IMAGEMANAGER->findImage("invenRectOff");
	}

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			_selectRect[(i * 5) + j] = RectMake(WINSIZEX / 2 + 293 + j * 132,
				WINSIZEY / 2 - 12 + i * 132, 114, 114);
		}
	}
	for (int i = 0; i < 2; ++i)
	{
		_mainWeaponRect[i] = RectMake(WINSIZEX /2 + 340 + i * 310, WINSIZEY/2 - 340, 114, 114);
		_assistWeaponRect[i] = RectMake(WINSIZEX / 2 + 470 + i * 310 , WINSIZEY / 2 - 340, 114, 114);
	}
	for (int i = 0; i < 4; ++i)
	{
		_accessarryRect[i] = RectMake(WINSIZEX / 2 + 363 + i * 129 , WINSIZEY / 2 -180, 114, 114);
	}
	_isSelect = 1;
	_index = 0;
	_index2 = 0;
	_onMouseInven = false;
	_halfW = (_selectRect[0].right - _selectRect[0].left) / 2; 
	_halfH = (_selectRect[0].bottom - _selectRect[0].top) / 2;
	return S_OK;
}

void inven::release()
{
}

void inven::update()
{
	if (_onInven)
	{
		for (int i = 0; i < 15; ++i)
		{
			if (PtInRect(&_selectRect[i], _ptMouse))
			{
				_index = i;
				_onMouseInven = true;
				if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) mount();
				break;
			}
			else _onMouseInven = false;
		}
		for (int i = 0; i < 4; ++i)
		{
			if (PtInRect(&_accessarryRect[i], _ptMouse))
			{
				_index = i;
				_onMouseAc = true;
				break;
			}
			else _onMouseAc = false;
		}
		for (int i = 0; i < 2; ++i)
		{
			if (PtInRect(&_mainWeaponRect[i], _ptMouse))
			{
				_index = i;
				_onMouseMain = true;
				break;
			}
			else _onMouseMain = false;

			if (PtInRect(&_assistWeaponRect[i], _ptMouse))
			{
				_index = i;
				_onMouseAs = true;
				break;
			}
			else _onMouseAs = false;

		}
	}
}

void inven::render()
{
	if (_onInven)
	{
		{
			IMAGEMANAGER->findImage("inven")->render(UIDC, WINSIZEX - IMAGEMANAGER->findImage("inven")->getWidth()
				, 0);
			if (_isSelect == 0)
				IMAGEMANAGER->findImage("inven0")->render(UIDC, WINSIZEX / 2 + 328, WINSIZEY / 2 - 385);
			if (_isSelect == 1)
				IMAGEMANAGER->findImage("inven0")->render(UIDC, WINSIZEX / 2 + 638, WINSIZEY / 2 - 385);
			for (int i = 0; i < 15; ++i)
			{
				_image[i]->render(UIDC, _selectRect[i].left, _selectRect[i].top);
				//Rectangle(UIDC, _selectRect[i].left, _selectRect[i].top, _selectRect[i].right, _selectRect[i].bottom);
			}
			if (_onMouseInven) IMAGEMANAGER->findImage("invenRectOn")->render(UIDC, _selectRect[_index].left, _selectRect[_index].top);
			else if (_onMouseAc) IMAGEMANAGER->findImage("invenRectOnAc")->render(UIDC, _accessarryRect[_index].left, _accessarryRect[_index].top);
			else if (_onMouseMain) IMAGEMANAGER->findImage("mouseOnMain")->render(UIDC, _mainWeaponRect[_index].left, _mainWeaponRect[_index].top);
			else if (_onMouseAs) IMAGEMANAGER->findImage("mouseOnAs")->render(UIDC, _assistWeaponRect[_index].left, _assistWeaponRect[_index].top);
			for (int i = 0; i < _vItem.size(); ++i)
			{
				_vItem[i]->invenRender(UIDC, _selectRect[i].left + _halfW, _selectRect[i].top + _halfH);
			}
			for (int i = 0; i < _vMainWeapon.size(); ++i)
			{
				_vMainWeapon[i]->invenRender(UIDC, _mainWeaponRect[i].left + _halfW, _mainWeaponRect[i].top + _halfH);
			}
			for (int i = 0; i < _vAssistWeapon.size(); ++i)
			{
				_vAssistWeapon[i]->invenRender(UIDC, _assistWeaponRect[i].left + _halfW, _assistWeaponRect[i].top + _halfH);
			}
			for (int i = 0; i < _vAccessary.size(); ++i)
			{
				_vAccessary[i]->invenRender(UIDC, _accessarryRect[i].left + _halfW, _accessarryRect[i].top + _halfH);
			}
		}
		if (KEYMANAGER->isToggleKey(VK_F6))
		{
			for (int i = 0; i < 2; ++i)
			{
				Rectangle(UIDC, _mainWeaponRect[i].left, _mainWeaponRect[i].top, _mainWeaponRect[i].right, _mainWeaponRect[i].bottom);
				Rectangle(UIDC, _assistWeaponRect[i].left, _assistWeaponRect[i].top, _assistWeaponRect[i].right, _assistWeaponRect[i].bottom);
			}
			for (int i = 0; i < 4; ++i)
			{
				Rectangle(UIDC, _accessarryRect[i].left, _accessarryRect[i].top, _accessarryRect[i].right, _accessarryRect[i].bottom);
			}
		}
	}
}


void inven::dismantItem()
{
}
//SWORD, HAMMER, GUN, BOW,	// 검, 해머 ,총 , 활
//ARMOR,						// 아머
//SHIELD,						// 방패
//SECOND_EQUIPMENT,			// 보조장비 
//ACCESSORY,					// 액세서리
//FOOD,						// 음식
void inven::mount()
{
	if(_vItem[_index]->getItemType() == SWORD
	|| _vItem[_index]->getItemType() == HAMMER
	|| _vItem[_index]->getItemType() == GUN
	|| _vItem[_index]->getItemType() == BOW)
	{
		if (_vMainWeapon.size() > 1) return;
		_vMainWeapon.push_back(_vItem[_index]);
		_vItem.erase(_vItem.begin() + _index);
	}
	else if (_vItem[_index]->getItemType() == ARMOR
	|| _vItem[_index]->getItemType() == ACCESSORY)
	{
		if (_vAccessary.size() > 3) return;
		_vAccessary.push_back(_vItem[_index]);
		_vItem.erase(_vItem.begin() + _index);
	}
	else if(_vItem[_index]->getItemType() == SHIELD
		 || _vItem[_index]->getItemType() == SECOND_EQUIPMENT)
	{
		_vAssistWeapon.push_back(_vItem[_index]);
		_vItem.erase(_vItem.begin() + _index);
	}
}

void inven::pickUpItem(ITEMTYPE type, const char * weaponName, int value)
{
	if (_vItem.size() >= 15) return;
	Item * item;
	item = new Item;
	item->init(type, weaponName, value, PointMake(500, 500));

	_vItem.push_back(item);
}



void inven::deleteItem(int i)
{
}

inven::inven(){}
inven::~inven(){}
