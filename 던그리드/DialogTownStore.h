#pragma once
#include "gameNode.h"

enum TOWNSTORE_NPC { TOWNSTORE_RESCUE };
class DialogTownStore : public gameNode
{
	string _name, _dialog[1][5];
	TOWNSTORE_NPC _townStore;
	RECT _rc[3];
	RECT _button[3];
	int _count, _idX, _idY;
	int _dialogSize[1];

	RECT _click;
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

