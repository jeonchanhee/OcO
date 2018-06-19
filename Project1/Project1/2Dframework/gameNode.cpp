#include "stdafx.h"
#include "gameNode.h"


gameNode::gameNode()
{
}


gameNode::~gameNode()
{

}

// 초기화 함수
HRESULT gameNode::init(void)  
{
	_hdc = GetDC(_hWnd);
	_managerInit = false;
	
	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	//매니져를 사용한다면
	if (_managerInit)
	{
		SetTimer(_hWnd, 1, 10, NULL);
		KEYMANAGER->init();
		IMAGEMANAGER->init();
		TIMEMANAGER->init();
		SOUNDMANAGER->init();
		EFFECTMANAGER->init();
		SCENEMANAGER->init();
		TXTDATA->init();
		INIDATA->init();
	}


	return S_OK;
}

//메모리 해제 함수
void gameNode::release(void)  
{

	if (_managerInit)
	{
		KillTimer(_hWnd, 1);
		KEYMANAGER->releaseSingleton();

		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();

		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();

		SOUNDMANAGER->release();
		SOUNDMANAGER->releaseSingleton();

		EFFECTMANAGER->release();
		EFFECTMANAGER->releaseSingleton();

		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();

		TXTDATA->release();
		TXTDATA->releaseSingleton();

		INIDATA->releaseSingleton();
	}
	//초기화해줄때 GetDC를 사용했으므로 DC해제해준다
	ReleaseDC(_hWnd, _hdc);
}

//연산
void gameNode::update(void)	  
{
	KEYMANAGER->update();
	SOUNDMANAGER->update();
}

//그리기
void gameNode::render(void)
{

}

void gameNode::setMap()
{
}


void gameNode::save()
{
}

void gameNode::load()
{
}

LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;		//조사 한 번 해보시요1
	HDC hdc;

	switch (iMessage)
	{
	case WM_CREATE:
	{
		
	}
	break;
	case WM_PAINT:
	{
		this->render();
	}
	break;
	case WM_TIMER:
		this->update();
	break;
	case WM_LBUTTONDOWN:
		_leftButtonDown = true;
		this->setMap();
	break;
	case WM_LBUTTONUP:
		_leftButtonDown = false;
	break;
	
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
			case CTRL_SAVE:
				this->save();
			break;
			case CTRL_LOAD:
				this->load();
				InvalidateRect(hWnd, NULL, false);
			break;
			default:
				this->setCtrlSelect(LOWORD(wParam));
			break;
		}
	}

	break;

		//맨 처음 윈도우가 생성되면 딱 한 번 실행된다	
	case WM_MOUSEMOVE:
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);

		if (_leftButtonDown) this->setMap();
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
