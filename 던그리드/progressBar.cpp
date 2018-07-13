#include "stdafx.h"
#include "progressBar.h"


progressBar::progressBar()
{
}


progressBar::~progressBar()
{
}

HRESULT progressBar::init(int x, int y, int width, int height, const char* frontName, const char* bottomName, BARTYPE barType)
{
	_x = x;
	_y = y;

	_rcProgress = RectMake(x, y, width, height);

	string imageName1, imageName2;

	_frontName = frontName;
	_bottomName = bottomName;
	_barType = barType;
	//가로크기는 이미지의 가로크기로!
	
	_barType = barType;

	switch (barType)
	{
	case BAR_PLAYER:
		break;
	case BAR_MONSTER:
		imageName1 = "image/enemy/monsterRedBar(80x10,1x1).bmp";
		imageName2 = "image/enemy/monsterHPBar(80x10,1x1).bmp";
		break;
	case BAR_BOSS:
		imageName1 = "image/enemy/bossRedBar(750x100,1x1).bmp";
		imageName2 = "image/enemy/bossHPBar(750x100,1x1).bmp";
		break;
	}

	_progressBarTop = IMAGEMANAGER->addImage(frontName, imageName1.c_str(), x, y, width, height, true, RGB(255, 0, 255));
	_progressBarBottom = IMAGEMANAGER->addImage(bottomName, imageName2.c_str(), x, y, width, height, true, RGB(255, 0, 255));

	_width = _progressBarTop->getWidth();


	return S_OK;
}

void progressBar::release()
{
}

void progressBar::update()
{
	_rcProgress = RectMakeCenter(_x, _y, _width, _progressBarTop->getHeight());
}

void progressBar::render()
{
	if (_barType == BAR_BOSS)
	{
		//그려줄땐 뒤에 게이지부터 먼저 그린다
		IMAGEMANAGER->render(_bottomName, UIDC,
			_x,
			_y, 0, 0,
			_progressBarBottom->getWidth(), _progressBarBottom->getHeight());

		//앞에 게이지는 가로크기 혹은 세로크기가 변해야하기때문에 변수가 크기값에 들어간다
		IMAGEMANAGER->render(_frontName, UIDC,
			_x,
			_y, 0, 0,
			_width, _progressBarBottom->getHeight());
	}
	else if (_barType == BAR_PLAYER)
	{
			//그려줄땐 뒤에 게이지부터 먼저 그린다
			IMAGEMANAGER->render(_bottomName, UIDC,
				_x,
				_y, 0, 0,
				_progressBarBottom->getWidth(), _progressBarBottom->getHeight());

			//앞에 게이지는 가로크기 혹은 세로크기가 변해야하기때문에 변수가 크기값에 들어간다
			IMAGEMANAGER->render(_frontName, UIDC,
				_x,
				_y, 0, 0,
				_width, _progressBarBottom->getHeight());
	}
	else if(_barType == BAR_MONSTER)
	{
		//그려줄땐 뒤에 게이지부터 먼저 그린다
		IMAGEMANAGER->render(_bottomName, DC,
			_x,
			_y + _progressBarBottom->getHeight() / 2, 0, 0,
			_progressBarBottom->getWidth(), _progressBarBottom->getHeight());

		//앞에 게이지는 가로크기 혹은 세로크기가 변해야하기때문에 변수가 크기값에 들어간다
		IMAGEMANAGER->render(_frontName, DC,
			//_rcProgress.left + _progressBarBottom->getWidth() / 2
			_x,
			_y + _progressBarBottom->getHeight() / 2, 0, 0,
			_width, _progressBarBottom->getHeight());
	}
}

void progressBar::setGauge(float currentGauge, float maxGauge)
{
	_width = (currentGauge / maxGauge) * _progressBarBottom->getWidth();
}