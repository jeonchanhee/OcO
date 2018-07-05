#pragma once
#include "gameNode.h"

//저은방 서은언
class animation;

class effect : public gameNode
{
protected:
	int _x;
	int _y;

	image*		_effectImage;
	animation*	_effectAnimation;
	BOOL		_isRunning;
	float		_elapsedTime;
	float		_angle;
	bool		_isRotate;

public:
	effect();
	~effect();

	virtual HRESULT init(image* effectImage, int frameW, int frameH, int fps, float elapsedTime);
	virtual void release();
	virtual void update();
	virtual void render();

	void rotateRender(float angle);
	void startEffect(int x, int y);
	

	virtual void killEffect();

	BOOL getIsRunning() { return _isRunning; }
	BOOL getIsRotate() { return _isRotate; }

	float getAngle() { return _angle; }

	void setAngle(float angle) { _angle = angle; }
	void setRotate(bool isRotate) { _isRotate = isRotate; }

};

