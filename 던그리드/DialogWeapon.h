#pragma once
#include "Dialog.h"
class DialogWeapon : public Dialog
{
public:
	DialogWeapon();
	~DialogWeapon();

	HRESULT init();
	void release();
	void update();
	void render();

	void keyControl();
	void setFrame();
	void clickButton();
};

