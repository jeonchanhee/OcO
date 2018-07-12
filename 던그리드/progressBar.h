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
	BARTYPE _barType;	//������ HP������ �������� enum��~!
	RECT _rcProgress;	//���α׷��� �� ��Ʈ
	int _x, _y;			//��ǥ~
	float _width;		//���α׷��� �� ����ũ��

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

