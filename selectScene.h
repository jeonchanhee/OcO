#pragma once
#include "gameNode.h"
#include "button.h"

class selectScene : public gameNode
{
private:
	//�� ��ȯ�� ���� ��ư
	button* _btnSceneChange;

public:
	selectScene();
	~selectScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	//�ݹ鿡 ���� �Լ�
	static void cbSceneChange();
};

