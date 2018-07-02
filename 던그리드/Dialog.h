#pragma once
#include "gameNode.h"

class Dialog :	public gameNode
{
protected:
	//�θ𿡼� ����
	image * _uiBack, *_ansBack, *_ansCur, *_uiNext;
	int _count, _idX, _idY;
	RECT _rc[3];

	//�ڽĿ��� ����
	string _name;
	//���̾�α׸��� ��ư�� ��簡 �޶� ���ͷ� ó�� 
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

