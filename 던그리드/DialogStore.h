#pragma once
#include "gameNode.h"
enum STORE_NPC {STORE_MEET, STORE_BUY };
class DialogStore : public gameNode
{
	string _name, _dialog[2][4];
	STORE_NPC _store;
	RECT _rc[3];
	RECT _button[3];
	int _count, _idX, _idY;
	int _dialogSize[2];

	RECT _click;
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

