#pragma once
#include "gameNode.h"
#include "MapTool.h"
#include "titleScene.h"
#include "dunGeonScene.h"
#include "DialogWeapon.h"

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

