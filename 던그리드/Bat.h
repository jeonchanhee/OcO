#pragma once
#include "Enemy.h"
#include "progressBar.h"

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
	progressBar* _progressBar;
	float _currentHP, _maxHP;

	BATDIRECTION _batDirection;
	animation* _batMotion;
	RECT			_detectionrc;		// Ÿ�� ���� ��Ʈ

	int		_detectionX, _detectionY;
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

	void playerCollision();
	void hitDamage(float damage);

	void tileDetection();	// Ÿ�� ����
};

