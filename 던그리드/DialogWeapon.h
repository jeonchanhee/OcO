#pragma once
#include "Dialog.h"
class DialogWeapon : public Dialog
{
private:
	bool _isWeapon;

public:
	bool _reset;
	bool _open;
	int _itemNum[5];

	DialogWeapon();
	~DialogWeapon();

	HRESULT init();
	void release();
	void update();
	void render();

	void keyControl();
	void setFrame();
	void clickButton();
	void shop();
	void resetShop();

	bool getIsWeapon() { return _isWeapon; }
};

