#pragma once
#include "gameNode.h"

class Dialog :	public gameNode
{
protected:
	//부모에서 정의
	image * _uiBack, *_ansBack, *_ansCur, *_uiNext;
	int _count, _idX, _idY;
	RECT _rc[3];

	//자식에서 정의
	string _name;
	//다이얼로그마다 버튼과 대사가 달라서 벡터로 처리 
	vector<RECT> _vButton;
	vector<string> _vButtonDialog;
	vector<vector<string>> _vDialog;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	 
	virtual void setDialog();
	virtual void changeDialog();
	virtual void clickButton();

	virtual void keyControl();
	virtual void setFrame();

	Dialog();
	~Dialog();
};

