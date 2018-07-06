#pragma once
#include "Enemy.h"

enum BATDIRECTION
{
	BAT_RIGHT_MOVE,
	BAT_LEFT_MOVE,
	BAT_RIGHT_DIE,
	BAT_LEFT_DIE
};

//���ݾ��ϰ� ���ƴٴϱ⸸�ϴ� ����
class Bat : public Enemy
{
private:
	BATDIRECTION _batDirection;
	animation* _batMotion;

	float _startX, _startY;//���� �̵� ������

public:
	Bat();
	~Bat();

	HRESULT init(float x, float y);
	void release();
	void update();
	void render();
	
	void move();//������ �Լ�
	void changeAnimation(BATDIRECTION direction); //�ִϸ��̼� ��ȯ �Լ�
	//void changeDirection(); //������ȯ �Լ�
	void rightMove();
	void leftMove();

};

