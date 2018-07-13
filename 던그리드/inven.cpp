#include "stdafx.h"
#include "inven.h"
#include "itemManager.h"


HRESULT inven::init()
{
	
	_onInven = false , _onMouseInven = false, _onMouseAc = false, _onMouseMain = false, _onMouseAs =false , _onInven =false;
	_gold = 0;
	_moneyRect = RectMake(WINSIZEX / 2 + 800, WINSIZEY / 2 + 427, 300, 50);
	for (int i = 0; i < INVENSIZE; ++i)
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
		_mainWeaponRect[i] = RectMake(WINSIZEX / 2 + 340 + i * 311, WINSIZEY/2 - 340, 114, 114);
		_assistWeaponRect[i] = RectMake(WINSIZEX / 2 + 470 + i * 311 , WINSIZEY / 2 - 340, 114, 114);
	}
	for (int i = 0; i < 4; ++i)
	{
		_accessarryRect[i] = RectMake(WINSIZEX / 2 + 363 + i * 129 , WINSIZEY / 2 -180, 114, 114);
	}
	_isSelect = 0;
	_index = 0;
	_halfW = (_selectRect[0].right - _selectRect[0].left) / 2; 
	_halfH = (_selectRect[0].bottom - _selectRect[0].top) / 2;
	pickUpItem(SWORD, "검", 1);
	mount();
	return S_OK;
}

void inven::release(){}

void inven::update()
{

	if (KEYMANAGER->isOnceKeyDown('I')) _onInven == false ? _onInven = true : _onInven = false;
	if (_onInven)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT)) _gold += 100;
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT)) _gold += 10000;
		int value=0;
		if (_gold > 999999) value = 5;
		else if (_gold > 99999) value = 4;
		else if (_gold > 9999) value = 3;
		else if (_gold > 999) value = 2; 
		else if (_gold > 99) value = 1;
		
		
		

		_moneyRect = RectMake(WINSIZEX / 2 + 800 - (value * 30), WINSIZEY / 2 + 427, 300, 50);
		for (int i = 0; i < INVENSIZE; ++i)
		{
			if (PtInRect(&_selectRect[i], _ptMouse))
			{
				_index = i;
				_onMouseInven = true;
				//장착 
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
				//해체 악세사리 
				if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) dismantAccessarry();
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
				//해체 
				if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))  dismantWeapon();
				break;
			}
			else _onMouseMain = false;
		}
		for (int i = 0; i < 2; ++i)
		{
			if (PtInRect(&_assistWeaponRect[i], _ptMouse))
			{
				_index = i;
				_onMouseAs = true;
				//해체 
				if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) dismantAs();
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
			for (int i = 0; i < INVENSIZE; ++i)
			{
				_image[i]->render(UIDC, _selectRect[i].left, _selectRect[i].top);
				//Rectangle(UIDC, _selectRect[i].left, _selectRect[i].top, _selectRect[i].right, _selectRect[i].bottom);
			}
			if (_onMouseInven) IMAGEMANAGER->findImage("invenRectOn")->render(UIDC, _selectRect[_index].left, _selectRect[_index].top);
			else if (_onMouseAc) IMAGEMANAGER->findImage("invenRectOnAc")->render(UIDC, _accessarryRect[_index].left, _accessarryRect[_index].top);
			else if (_onMouseMain) IMAGEMANAGER->findImage("mouseOnMain")->render(UIDC, _mainWeaponRect[_index].left , _mainWeaponRect[_index].top);
			else if (_onMouseAs) IMAGEMANAGER->findImage("mouseOnAs")->render(UIDC, _assistWeaponRect[_index].left, _assistWeaponRect[_index].top);
			for (int i = 0; i < _vItem.size(); ++i)
			{
				if(_vItem[i]->getItemType() == ACCESSORY)_vItem[i]->invenRender(UIDC, _selectRect[i].left + 25, _selectRect[i].top + _halfH / 2 - 10);
				else _vItem[i]->invenRender(UIDC, _selectRect[i].left + _halfW - 10, _selectRect[i].top + _halfH / 2 - 10);
			}
			for (int i = 0; i < _vMainWeapon.size(); ++i)
			{
				_vMainWeapon[i]->invenRender(UIDC, _mainWeaponRect[i].left + _halfW - 10, _mainWeaponRect[i].top + _halfH / 2 - 10);
			}
			for (int i = 0; i < _vAssistWeapon.size(); ++i)
			{
				_vAssistWeapon[i]->invenRender(UIDC, _assistWeaponRect[i].left + _halfW - 10, _assistWeaponRect[i].top + _halfH / 2 - 10);
			}
			for (int i = 0; i < _vAccessary.size(); ++i)
			{
				_vAccessary[i]->invenRender(UIDC, _accessarryRect[i].left + 25 , _accessarryRect[i].top + _halfH / 2 - 10);
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
		char str[256];
		sprintf_s(str, "%d", _gold);
		HFONT font, oldFont;
		font = CreateFont(50, 0, 0, 0, 100, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("소야바른9"));
		oldFont = (HFONT)SelectObject(UIDC, font);
		SetTextColor(UIDC, RGB(250, 250, 0));
		SetBkMode(UIDC, TRANSPARENT);
		DrawText(UIDC, str, strlen(str), &_moneyRect, DT_VCENTER);
		SelectObject(UIDC, oldFont);
		DeleteObject(font);
		//Rectangle(UIDC, _moneyRect.left, _moneyRect.top, _moneyRect.right, _moneyRect.bottom);
	}
}


//SWORD, HAMMER, GUN, BOW,	// 검, 해머 ,총 , 활
//ARMOR,						// 아머
//SHIELD,						// 방패
//SECOND_EQUIPMENT,			// 보조장비 
//ACCESSORY,					// 액세서리
//FOOD,						// 음식
void inven::mount()
{
	if (_vItem.size() <= _index) return;
	if(_vItem[_index]->getItemType() == SWORD
	|| _vItem[_index]->getItemType() == HAMMER
	|| _vItem[_index]->getItemType() == GUN
	|| _vItem[_index]->getItemType() == BOW)
	{
		if (_vMainWeapon.size() > 1 || ((_isSelect == 0) && (_vMainWeapon.size() >=1)))
		{
			_vSaveItem.push_back(_vMainWeapon[_isSelect]);							 //1. push weaponData in Save vector  
			_vMainWeapon.erase(_vMainWeapon.begin() + _isSelect);					 //2. erase vMainWeapon select data 
			_vMainWeapon.insert(_vMainWeapon.begin() + _isSelect, _vItem[_index]);   //3. weaponVector insert to inventory item index ;
			_vItem.erase(_vItem.begin() + _index);									 //4. inventory index erase!!!!
			_vItem.insert(_vItem.begin() + _index, _vSaveItem[0]);					 //5. inventory insert to weapon select data
			_vSaveItem.pop_back();													 // 6. save vector erase
			return;
		} 
		else
		{
			_vMainWeapon.push_back(_vItem[_index]);
			_vItem.erase(_vItem.begin() + _index);
		}
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
		if (_vAssistWeapon.size() > 1 
			|| ((_isSelect == 0) && (_vAssistWeapon.size() >= 1)))
		{
			_vSaveItem.push_back(_vAssistWeapon[_isSelect]);							 //1. push weaponData in Save vector  
			_vAssistWeapon.erase(_vAssistWeapon.begin() + _isSelect);					 //2. erase vMainWeapon select data 
			_vAssistWeapon.insert(_vAssistWeapon.begin() + _isSelect, _vItem[_index]);   //3. weaponVector insert to inventory item index ;
			_vItem.erase(_vItem.begin() + _index);									 //4. inventory index erase!!!!
			_vItem.insert(_vItem.begin() + _index, _vSaveItem[0]);					 //5. inventory insert to weapon select data
			_vSaveItem.pop_back();													 // 6. save vector erase
		}
		else
		{
			_vAssistWeapon.push_back(_vItem[_index]);
			_vItem.erase(_vItem.begin() + _index);
		}
	}
}

void inven::pickUpItem(ITEMTYPE type, const char * weaponName, int value)
{
	if (_vItem.size() >= INVENSIZE) return;
	Item * item;
	item = new Item;
	item->init(type, weaponName, value, PointMake(500, 500));

	_vItem.push_back(item);
}

void inven::buyItem(int num)
{
	//if (_vItem.size() >= INVENSIZE) return;
	Item * item;
	item = new Item;
	item->init(_im->getItem()[num]->getItem().type, _im->getItem()[num]->getItem().name, _im->getItem()[num]->getItem().value, PointMake(500, 500));

	_vItem.push_back(item);

}

void inven::deleteItem(int i)
{
	
}

void inven::dismantWeapon()
{
	if (_vItem.size() >= INVENSIZE
		|| _vMainWeapon.size() <= _index) return;
	_vItem.push_back(_vMainWeapon[_index]);
	_vMainWeapon.erase(_vMainWeapon.begin() + _index);
}

void inven::dismantAs()
{
	if (_vItem.size() >= INVENSIZE
		|| _vAssistWeapon.size() <= _index) return;
	_vItem.push_back(_vAssistWeapon[_index]);
	_vAssistWeapon.erase(_vAssistWeapon.begin() + _index);
}

void inven::dismantAccessarry()
{
	if (_vItem.size() >= INVENSIZE
	|| _vAccessary.size() <= _index) return;
	_vItem.push_back(_vAccessary[_index]);
	_vAccessary.erase(_vAccessary.begin() + _index);

}

inven::inven(){}
inven::~inven(){}
