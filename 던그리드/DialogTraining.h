#pragma once
#include "gameNode.h"

enum TRAINING_NPC { TRAINING_RESCUE, TRAINING_AFTER_RESCUE, TRAINING_BUILD, TRAINING_BUILDING, TRAINING_DIALOG };
class DialogTraining : public gameNode
{
	string _name, _dialog[5][5];
	TRAINING_NPC _training;
	RECT _rc[3];
	RECT _button[3];
	int _count, _idX, _idY;
	int _dialogSize[4];

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

	DialogTraining();
	~DialogTraining();
};
