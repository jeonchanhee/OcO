#pragma once
#include "gameNode.h"

//�� Ŭ���� 
class enemy : public gameNode
{
protected:
	//������� �������� ������Ƽ��(��Ӱ��迡���� �����Ҽ��ִ�)
	image*	_imageName;			//�� �̹���
	RECT	_rc;				//�� ��Ʈ

	int		_currentFrameX;		//������ �̹��� ������ ���� �����ӹ�ȣ
	int		_currentFrameY;

	int		_count;				//������	ī��Ʈ
	int		_fireCount;			//�߻�	ī��Ʈ
	int		_rndFireCount;		//�����ϰ� �߻��� ī��Ʈ

public:
	enemy();
	~enemy();

	HRESULT init();
	HRESULT init(const char* imageName, POINT position);
	void release();
	void update();
	void render();

	void move();		//������ �Լ�
	void draw();		//�׷��ִ� �Լ�

	bool bulletCountFire();		//�Ѿ� �߻� �Լ�

	inline RECT getRect() { return _rc; }
	
};

