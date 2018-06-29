#pragma once
#include "gameNode.h"

class titleScene : public gameNode
{
	float _loop0, _loop1;
	POINT _bird0, _bird1;
	image* _birdImg0, *_birdImg1;
	animation* _abird0, *_abird1;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	titleScene();
	~titleScene();
};

