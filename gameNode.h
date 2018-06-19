#pragma once
#include "image.h"

//����� ����
static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);

enum CTRL
{
	CTRL_SAVE,			//���̺� ��ư
	CTRL_LOAD,			//�ε� ��ư
	CTRL_TERRAINDRAW,	//���� ��ư
	CTRL_OBJDRAW,		//������Ʈ ��ư
	CTRL_ERASER,		//���찳 ��ư
	CTRL_END
};

class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;	//�Ŵ����� �ʱ�ȭ �Ҳ��� ����

public:
	int _ctrSelect;		//��Ʈ�� ��ư 

	virtual HRESULT init(void);
	virtual HRESULT init(bool managerInit);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	//�� ���� ���� �Լ�
	virtual void setMap();

	virtual void save();
	virtual void load();

	//�� �����߳�
	void setCtrlSelect(int num) { _ctrSelect = num; }

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	image* getBackBuffer() { return _backBuffer; }

	//DC ������
	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }

	gameNode();
	virtual ~gameNode();
};

