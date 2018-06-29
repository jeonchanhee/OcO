#pragma once
#include "gameNode.h"

enum ELDER_NPC {ELDER_BUILD, ELDER_DIALOG };

class DialogElder : public gameNode
{
	string _name, _dialog[2][3];
	ELDER_NPC _elder;
	RECT _rc[3];
	RECT _button[3];
	int _count, _idX, _idY;
	int _dialogSize[2];

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

	DialogElder();
	~DialogElder();
};

