#pragma once
#include "gameNode.h"


enum ITEMTYPE // �������� Ÿ��
{
	WEAPON, DEFENCE, // ���� , ��(�Ǽ��縮 ����)
	FOOD, TREASURE  // ����(���� ����), ����, ����
};

struct tagItem		//��� ���̵��� �� ������ ������~~			
{
	image*		image;			// �������� �̹���
	ITEMTYPE	itemtype;		// ������ Ÿ��
	RECT		rc;				// �������� ��Ʈ
	float		x;				// ������ x��ǥ~
	float		y;				// ������ y��ǥ~
	bool		itemCreate;		// �������� ���� �Ǿ��� �ȵǾ��� Ȯ��.
	int			count;			// ������ ī��Ʈ��~
	int			currentFrameX;	// ������ �̹����� �����̱� ���� �ʿ�~
	int			currentFrameY;	// �ꉥ ���������� ����
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



