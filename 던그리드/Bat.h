#pragma once
#include "Enemy.h"
#include "progressBar.h"

enum BATDIRECTION
{
	BAT_RIGHT_MOVE,
	BAT_LEFT_MOVE,
	BAT_RIGHT_UP_MOVE,
	BAT_LEFT_UP_MOVE,
	BAT_RIGHT_DOWN_MOVE,
	BAT_LEFT_DOWN_MOVE,
	BAT_UP_MOVE,
	BAT_DOWN_MOVE,
	BAT_RIGHT_DIE,
	BAT_LEFT_DIE
};

//���ݾ��ϰ� ���ƴٴϱ⸸�ϴ� ����
class Bat : public Enemy
{	
private:
	float _currentHP, _maxHP;

	BATDIRECTION _batDirection;
	animation* _batMotion;
	RECT rcCollision;	// Ÿ�� ���� ��Ʈ

	int		randNum;	// �����̵�
	int		_detectionX, _detectionY;
	int		_moveCount;
	float _startX, _startY;//���� �̵� ������
	bool _diedie;
	int _dieCount;
	//�ӽ�
	int j = 0;

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

	void tileDetection();	// Ÿ�� ����

	void playerCollision();
	void die();
	void hitDamage();

	static void batDieMotion(void * obj);

	RECT  getBatRect() { return _rc; } //rc
};

