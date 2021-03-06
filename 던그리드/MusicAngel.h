#pragma once
#include "Enemy.h"
#include "Bullet.h"

enum MUSICANGELDIRECTION
{
	MUSICANGEL_RIGHT_MOVE,
	MUSICANGEL_LEFT_MOVE,
	MUSICANGEL_RIGHT_ATTACK,
	MUSICANGEL_LEFT_ATTACK,
	MUSICANGEL_DIE
};

class MusicAngel : public Enemy
{
private:
	MUSICANGELDIRECTION _musicAngelDirection;
	animation* _musicAngelMotion;
	Bullet* _bullet;

	bool _diedie;
	int _diecount;
	
public:
	MusicAngel();
	~MusicAngel();

	HRESULT init(float x, float y);
	void release();
	void update();
	void render();

	void attackMove();
	static void rightAttack(void* obj);
	static void leftAttack(void* obj);
	static void dieMotion(void* obj);

	void changeAnimation(MUSICANGELDIRECTION musicAngelDirection);


	//�ݹ� �Լ�
	MUSICANGELDIRECTION getMusicAngelDirection() { return _musicAngelDirection; }
	void setMusicAngelDirection(MUSICANGELDIRECTION direction) { _musicAngelDirection = direction; }

	animation* getMusicAngelMotion() { return _musicAngelMotion; }
	void setMusicAngelMotion(animation* ani) { _musicAngelMotion = ani; }

	void hitDamage();

	bool getDieDie() { return _diedie; }
};

