#pragma once
#include "Enemy.h"

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

	void changeAnimation(MUSICANGELDIRECTION musicAngelDirection);


	//콜백 함수
	MUSICANGELDIRECTION getMusicAngelDirection() { return _musicAngelDirection; }
	void setMusicAngelDirection(MUSICANGELDIRECTION direction) { _musicAngelDirection = direction; }

	animation* getMusicAngelMotion() { return _musicAngelMotion; }
	void setMusicAngelMotion(animation* ani) { _musicAngelMotion = ani; }
};

