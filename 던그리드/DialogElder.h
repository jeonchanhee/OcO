#pragma once
#include "Dialog.h"
enum ELDER_NPC {ELDER_BUILD, ELDER_DIALOG };

class DialogElder : public Dialog
{
	ELDER_NPC _elder;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	void keyControl();

	void setFrame();

	void setDialog();
	void changeDialog();
	void clickButton();

	DialogElder();
	~DialogElder();
};

