#pragma once
#include "Dialog.h"

enum TOWNSTORE_NPC { TOWNSTORE_RESCUE, TOWNSTORE_BUILD, TOWNSTORE_NORMAL };
class DialogTownStore : public Dialog
{
	TOWNSTORE_NPC _townStore;
	
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

	DialogTownStore();
	~DialogTownStore();
};

