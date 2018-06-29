#pragma once
#include "gameNode.h"
class DialogWeapon : public gameNode
{
	string _name, _dialog;
	RECT _rc[3];
	RECT _button[3];
	int _count, _idX, _idY;
	int _dialogSize;

	RECT _click;
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

