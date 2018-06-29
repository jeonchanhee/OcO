#pragma once
#include "gameNode.h"


enum ITEMTYPE // 아이템의 타입
{
	WEAPON, DEFENCE, // 무기 , 방어구(악세사리 포함)
	FOOD, TREASURE  // 음식(힐링 포함), 코인, 골드바
};

struct tagItem		//모든 아이들이 쓸 아이템 구조췌~~			
{
	image*		image;			// 아이템의 이미지
	ITEMTYPE	itemtype;		// 아이템 타입
	RECT		rc;				// 아이템의 렉트
	float		x;				// 아이템 x좌표~
	float		y;				// 아이템 y좌표~
	bool		itemCreate;		// 아이템이 생성 되었나 안되었나 확인.
	int			count;			// 프레임 카운트용~
	int			currentFrameX;	// 프레임 이미지를 움직이기 위해 필요~
	int			currentFrameY;	// 얘돟 마찬가지임 ㅇㅇ
};

class Weapon :	public gameNode
{
private:

	tagItem _weapon;

public:

	Weapon();
	~Weapon();

	HRESULT init(const char* imageName, POINT position);
	HRESULT init2(const char* imageName, POINT position);
	void release();
	void update();
	void render();
	

};


class Food : public gameNode
{
private:

	tagItem _food;

public:

	Food();
	~Food();

	HRESULT init(const char* imageName, POINT position);
	HRESULT init2(const char* imageName, POINT position);
	void release();
	void update();
	void render();
};





class Treasure : public gameNode
{
private:

	tagItem _treasure;

public:

	Treasure();
	~Treasure();

	HRESULT init(const char* imageName, POINT position);
	HRESULT init2(const char* imageName, POINT position);
	void release();
	void update();
	void render();
	
};


 
class Defence: public gameNode
{
private:

	tagItem _defence;

public:

	Defence();
	~Defence();

	HRESULT init(const char* imageName, POINT position);
	HRESULT init2(const char* imageName, POINT position);
	void release();
	void update();
	void render();

};



