#pragma once
#include "Enemy.h"

#define DOGBONESPEED 5.0f

enum DOGBONEDIRECTION
{
	RIGHT_IDLE,
	LEFT_IDLE,
	RIGHT_MOVE,
	LEFT_MOVE,
	RIGHT_DIE,
	LEFT_DIE,
	RIGHT_JUMP,
	LEFT_JUMP
};

class DogBone : public Enemy
{
private:
	DOGBONEDIRECTION _dogBoneDirection;
	animation* _dogBoneMotion;
	
public:
	DogBone();
	~DogBone();

	HRESULT init();
	void release();
	void update();
	void render();

	void move();
};

