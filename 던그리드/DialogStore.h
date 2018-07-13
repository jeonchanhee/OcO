#pragma once
#include "Dialog.h"
enum STORE_NPC {STORE_MEET, STORE_BUY };
class DialogStore : public Dialog
{
	STORE_NPC _store;

public:
	image * _restImg;
	animation * _rest;
	RECT _rrc;
	bool _scroll;
	long _currentScroll;
	long _mouseY;
	bool _open;


	DialogStore();
	~DialogStore();

	HRESULT init();
	void release();
	void update();
	void render();

	void keyControl();

	void setFrame();

	void setDialog();
	void changeDialog();
	void clickButton();

	void restaurant();

};

