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
	LEFT_LASER, //������ ��� ��
	LEFT_LASER_ON, //������ ��°�
	LEFT_LASER_OFF
};

//�����ղٶ� ����
enum BOSSRIGHTDIRECTION
{
	RIGHT_IDLE,
	RIGHT_UP_MOVE,
	RIGHT_DOWN_MOVE,
	RIGHT_LASER,
	RIGHT_LASER_ON,
	RIGHT_LASER_OFF
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
	//SWORDDIRECTION		_swordDirection;

	//animation* _bossMotion[4]; //0�޼�.1�Ӹ�.2������.3Į
	animation* _bossMotion[3]; //0�޼�.1�Ӹ�.2������

	int x;
	int y;
	int _count2, _count3;
	
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
	float getLeftX() { return _boss[0].x; }
	float getLeftY() { return _boss[0].y; }
	BOSSLEFTDIRECTION getLDirection() { return _bossLeftDirection; }
	void setCount2(int count2) { _count2 = _count; }

	//�Ӹ���
	void headMove(); //�Ӹ��� �����̰� �ϴ� �Լ�
	void changeHeadDirection(BOSSHEADDIRECTION headDirection); //����ٲ��ִ� �Լ�
	static void CBheadAttack(void* obj); 
	float getHeadX() { return (_boss[1].rc.right + _boss[1].rc.left) / 2; }
	float getHeadY() { return (_boss[1].rc.bottom + _boss[1].rc.top) / 2; }
	bool isAttack(void) { if (_bossHeadDirection == HEAD_ATTACK) return true; else return false; }


	//������
	void rightMove(); //������ �����̰� �ϴ� �Լ�
	void changeRightDirection(BOSSRIGHTDIRECTION rightDirection); //����ٲ��ִ� �Լ�
	static void CBrightAttack(void* obj);
	float getRightX() { return _boss[2].x; }
	float getRightY() { return _boss[2].y; }
	void setCount3(int count3) { _count3 = count3; }


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

	void playerCollision();
	void hitDamage(float damage);

	RECT  getBossRect() { return _boss[1].rc; } //rc
};

