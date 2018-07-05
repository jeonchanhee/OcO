#pragma once
#include "Enemy.h"

#define BOSSSPEED 3.0f

//���� �Ӹ��� ����
enum BOSSHEADDIRECTION
{
	HEAD_IDLE,
	HEAD_ATTACK,
	HEAD_DIE
};

//�޼ղٶ� ����
enum BOSSLEFTDIRECTION
{
	LEFT_IDLE,
	LEFT_UP_MOVE,
	LEFT_DOWN_MOVE,
	LEFT_LASER
};

//�����ղٶ� ����
enum BOSSRIGHTDIRECTION
{
	RIGHT_IDLE,
	RIGHT_UP_MOVE,
	RIGHT_DOWN_MOVE,
	RIGHT_LASER
};

//������ ����ü
struct tagBoss
{
	RECT rc;
	image* img;
	float x, y;
};

class Boss2 : public Enemy
{
private:
	tagBoss _boss[3]; //������ �Ӹ�,�޼�,�������� �ִ� ����ü����
	
	BOSSHEADDIRECTION _bossHeadDirection;
	BOSSLEFTDIRECTION _bossLeftDirection;
	BOSSRIGHTDIRECTION _bossRightDirection;

	animation* _bossMotion[3]; //0�޼�.1�Ӹ�.2������
	

public:
	Boss2();
	~Boss2();

	HRESULT init();
	void release();
	void update();
	void render();

	//�޼�
	void leftMove(); //�޼� �����̰� �ϴ� �Լ�
	void changeLeftDirection(BOSSLEFTDIRECTION leftDirection); //����ٲ��ִ� �Լ�
	static void CBleftAttack(void* obj); 

	//�Ӹ���
	void headMove(); //�Ӹ��� �����̰� �ϴ� �Լ�
	void changeHeadDirection(BOSSHEADDIRECTION headDirection); //����ٲ��ִ� �Լ�
	static void CBheadAttack(void* obj); 

	//������
	void rightMove(); //������ �����̰� �ϴ� �Լ�
	void changeRightDirection(BOSSRIGHTDIRECTION rightDirection); //����ٲ��ִ� �Լ�
	static void CBrightAttack(void* obj);


	//�ݹ��Լ�
	
	//�޼�
	BOSSLEFTDIRECTION getLeftDirection() { return _bossLeftDirection; }
	void setLeftDirection(BOSSLEFTDIRECTION leftDirection) { _bossLeftDirection = leftDirection; }

	animation* getLeftMotion0() { return _bossMotion[0]; }
	void setLeftMotion0(animation* ani) { _bossMotion[0] = ani; }

	//�Ӹ���
	BOSSHEADDIRECTION getHeadDirection() { return _bossHeadDirection; }
	void setHeadDirection(BOSSHEADDIRECTION headDirection) { _bossHeadDirection = headDirection; }

	animation* getHeadMotion1() { return _bossMotion[1]; }
	void setHeadMotion1(animation* ani) { _bossMotion[1] = ani; }

	//������
	BOSSRIGHTDIRECTION getRightDirection() { return _bossRightDirection; };
	void setRightDirection(BOSSRIGHTDIRECTION rightDirection) { _bossRightDirection = rightDirection; }

	animation* getRightMotion2() { return _bossMotion[2]; }
	void setRightMotion2(animation* ani) { _bossMotion[2] = ani; }
};

