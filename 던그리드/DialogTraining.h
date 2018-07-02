#pragma once
#include "Dialog.h"

enum TRAINING_NPC { TRAINING_RESCUE, TRAINING_AFTER_RESCUE, TRAINING_BUILD, TRAINING_BUILDING, TRAINING_DIALOG };
class DialogTraining : public Dialog
{
	TRAINING_NPC _training;
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
