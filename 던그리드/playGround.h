#pragma once
#include "gameNode.h"
#include "MapTool.h"

class playGround : public gameNode
{
private:
	MapTool * _mapTool;

public:
	virtual HRESULT init(void);
	virtual HRESULT Image_init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);


	playGround();
	~playGround();
};

