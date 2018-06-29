#pragma once
#include "gameNode.h"
#include "DialogWeapon.h"

class playGround : public gameNode
{
private:
	

public:
	virtual HRESULT init(void);
	virtual HRESULT Image_init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);


	playGround();
	~playGround();
};

