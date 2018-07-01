#pragma once
#include "Dialog.h"
enum STORE_NPC {STORE_MEET, STORE_BUY };
class DialogStore : public Dialog
{
	STORE_NPC _store;

public:
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

};

