#pragma once
#include "gameNode.h"

class itemManager;

struct tagData
{
	int idx;
	int hour, min;
	int floor;
	int gold;
	int dash;
};

class titleScene : public gameNode
{
	itemManager* _im;

	float _loop0, _loop1;
	POINT _bird0, _bird1;
	image* _birdImg0, *_birdImg1;
	image* _img;
	animation* _abird0, *_abird1;
	animation* _suck;
	RECT _button[3];

	RECT _rc = RectMake(686, 210, 42, 432);
	bool _scroll;
	long _currentScroll;
	long _mouseY;
	

	vector<tagData> _vData;
	bool _clickData;
	RECT _chooseRect[3];
	RECT _deleteRect[3];

	int _select;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void training();

	void shop();

	void inven();

	void restaurant();

	void reward();

	void loadData();
	void saveData();

	void drawData();

	void selectData();

	void setImLink(itemManager* im) { _im = im; }

	titleScene();
	~titleScene();
};

