#pragma once
#include "gameNode.h"
#include <vector>


struct tagBullet
{
	image*	bulletImage;		//�Ѿ��� �̹���
	RECT	rc;					//�Ѿ� ��Ʈ
	float	x, y;				//�Ѿ� ��ǥ
	float	angle;				//�Ѿ� ����
	float	radius;				//�Ѿ� ������
	float	speed;				//�Ѿ� ���ǵ�
	float	fireX, fireY;		//�Ѿ� �߻���ġ ���庯��
	bool	isFire;				//�߻��ߴ�?
	int		count;				//������ �̹��� ��!
};

//������ ����� �� �ִ� �Ѿ�
class bullet : public gameNode
{
private:
	vector<tagBullet>			_vBullet;
	vector<tagBullet>::iterator _viBullet;

	const char* _imageName;
	float _range;
	int _bulletMax;

public:
	bullet();
	~bullet();

	HRESULT init(const char* imageName, int bulletMax, float range);
	void release(); 
	void update(); 
	void render();

	void bulletFire(float x, float y, float angle, float speed);

	void bulletMove();

	void removeBullet(int arrNum);

	//���ʹ� �淿 ���� ������
	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getVIBullet() { return _viBullet; }


};



//�����س��� �߻��ϴ� �̜X~
class missile : public gameNode
{
private:
	vector<tagBullet>				_vBullet;
	vector<tagBullet>::iterator		_viBullet;

	float _range;	//��Ÿ� ����

public:
	missile();
	~missile();

	HRESULT init(int bulletMax, float range);	//�Ѿ˸,��Ÿ���
	void release(void);
	void update(void);
	void render(void);

	//�Ѿ� �߻� �Լ� (�Ѿ� ������ġ x, y)
	void fire(float x, float y);

	void move(void);
};

//�߻��Ҷ� �����ؼ� ��� �̜X~
class minho : public gameNode
{
private:
	vector<tagBullet>			_vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range;		//��Ÿ� ����
	int _bulletMax;		//�ִ� ��ź ��
public:
	minho();
	~minho();

	HRESULT init(int missileMax, float range);
	void release();
	void update();
	void render();

	void fire(float x, float y);

	void move();

	void removeMinho(int arrNum);

	//��ȣ�̜X ������
	vector<tagBullet> getVMinho() { return _vBullet; }
	vector<tagBullet>::iterator getVIMinho() { return _viBullet; }

};