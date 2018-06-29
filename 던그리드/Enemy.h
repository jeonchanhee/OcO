#pragma once
#include "gameNode.h"

class Enemy :	public gameNode
{
protected:
	image* _img;				//�� �̹���
	RECT _rc;				//�� ��Ʈ
	int _frameX, _frameY;	//������ ��ȣ

	float _x, _y;			//�� x, y��ǥ
	float _speed, _angle;	//���ǵ�� ����

	int _count;				//������ ī��Ʈ
	int _fireCount;			//�߻� ī��Ʈ
	int _rndFireCount;		//�����ϰ� �߻��� ī��Ʈ


public:

	HRESULT init();
	HRESULT init(const char* imageName, POINT position, float angle, float speed);
	void release();
	void update();
	void render();

	Enemy();
	~Enemy();
};

