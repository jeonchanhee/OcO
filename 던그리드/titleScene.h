#pragma once
#include "gameNode.h"

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
	float _loop0, _loop1;
	POINT _bird0, _bird1;
	image* _birdImg0, *_birdImg1;
	animation* _abird0, *_abird1;
	RECT _button[3];

	int _alpha;
	vector<tagData> _vData;
	bool _clickData;
	RECT _deleteRect[3];

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void loadData();

	void drawData();

	void deleteData();

	titleScene();
	~titleScene();
};

