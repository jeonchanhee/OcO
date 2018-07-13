#pragma once
#include "gameNode.h"

class Player;
class itemManager;

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

	bool _isFin;

	Player* _player;
	itemManager* _im;

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

	bool getIsFin() { return _isFin; }
	void setIsFin(bool isFin) { _isFin = isFin; }

	Dialog();
	~Dialog();
};

