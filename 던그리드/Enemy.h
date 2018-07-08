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

	float _jumpPower;		//�����Ŀ�
	float _gravity;			//�߷�
	bool _isJumping;		//�������̳� �ƴϳ�

public:

	Enemy();
	~Enemy();

	HRESULT init(const char* imageName, float x, float y, float angle, float speed);
	void release();
	void update();
	void render();

	void changeFrame();//�����Ӻ�ȭ �Լ�
	void move();//�����̴� �Լ�
	bool bulletCountFire(); //�Ѿ� �߻� �Լ�
	inline RECT getRect() { return _rc; } //��Ʈ ��ȯ �Լ�

	void setAngle(float angle); //���� �ٲٴ� �Լ�
	//float getAngle();			//���� �޴� �Լ�
	void setPoint(float x, float y);	//��ǥ �ٲٴ� �Լ�

	float getX() { return _x; }
	float getY() { return _y; }
};

