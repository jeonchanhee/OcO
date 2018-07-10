#pragma once
#include "gameNode.h"

class itemManager;

enum TITLETYPE {TITLE_MENU, TITLE_START, TITLE_SET};

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
	bool _setData;
	RECT _deleteRect[3];
	RECT _exitRect;

	int _select;
	TITLETYPE _titleType;
	RECT _soundRC, _soundRC2, _bgmBack, _sfxBack;
	float _soundX, _soundY, _soundX2, _soundY2;

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

	void setting();

	void drawSetting();

	titleScene();
	~titleScene();
};

