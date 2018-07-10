#pragma once
#include "gameNode.h"

enum BARTYPE
{
	BAR_PLAYER,
	BAR_MONSTER,
	BAR_BOSS
};


class progressBar : public gameNode
{
private:
	BARTYPE _barType;	//누구의 HP바인지 고르기위한 enum문~!
	RECT _rcProgress;	//프로그레스 바 렉트
	int _x, _y;			//좌표~
	float _width;		//프로그레스 바 가로크기

	const char* _frontName;
	const char* _bottomName;

	image* _progressBarTop;
	image* _progressBarBottom;

public:
	progressBar();
	~progressBar();

	HRESULT init(int x, int y, int width, int height, const char* frontName, const char* bottomName, BARTYPE barType);
	void release();
	void update();
	void render();

	void setGauge(float currentGauge, float maxGauge);

	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }

};

