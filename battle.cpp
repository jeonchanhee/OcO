#include "stdafx.h"
#include "battle.h"


battle::battle()
{
}


battle::~battle()
{
}

HRESULT battle::init(const char * imageName, int x, int y)
{
	ship::init(imageName, x, y);

	return S_OK;
}

void battle::release()
{
}

void battle::update()
{
	ship::update();

	keyControl();
}

void battle::render()
{
	ship::render();

}

void battle::keyControl()
{
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		if (_angle >= PI2) _angle -= PI2;
		
		_angle += 0.04f;
	}

	if (KEYMANAGER->isStayKeyDown('D'))
	{
		if (_angle <= 0) _angle += PI2;
		_angle -= 0.04f;
	}

	if (KEYMANAGER->isStayKeyDown('W')) _speed += 0.04f;
	if (KEYMANAGER->isStayKeyDown('S')) _speed -= 0.04f;
}
