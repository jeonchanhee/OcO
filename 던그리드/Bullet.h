#pragma once
#include "gameNode.h"
#include <vector>

struct tagBullet
{
	image*	img;			// �Ѿ��̹���
	RECT	rc;				// ��Ʈ
	float	x, y;			// �Ѿ� ��ǥ
	float	angle;			// �Ѿ˰���
	float	speed;			// �Ѿ� ���ǵ�
	float	radius;			// �Ѿ� ������
	float	fireX, fireY;	// �߻���ġ
	bool	isFire;			// �߻翩��
};

class Bullet : public gameNode
{
private:
	vector<tagBullet>			_vBullet;
	vector<tagBullet>::iterator	_viBullet;

	const char* _imgName;		// ã�� �̹���
	float		_range;			// �Ѿ� ��Ÿ�
	int			_bulletMax;		// �ִ� �Ѿ� ����
public:
	Bullet();
	~Bullet();

	HRESULT init(const char* imageName, float range, int bullletMax);
	void	release();
	void	update();
	void	render();

	void	bulletFire(float x, float y, float angle, float speed);		// �߻�
	void	bulletMove();												// �̵�
	void	removeBullet(int arrNum);									// �Ѿ� �����ٶ�

	// �Ѿ� ���� ������
	vector<tagBullet>			getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator	getVIBullet() { return _viBullet; }

};

