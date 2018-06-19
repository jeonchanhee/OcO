#pragma once
#include "gameNode.h"
#include "button.h"

class selectScene : public gameNode
{
private:
	//씬 변환에 사용될 버튼
	button* _btnSceneChange;

public:
	selectScene();
	~selectScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	//콜백에 사용될 함수
	static void cbSceneChange();
};

