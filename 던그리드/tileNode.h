#pragma once

// ��ü �� ������ �Դϴ�   ���� �ο�Ź �帳�ϴ�
#define BACKGROUNDSIZEX TILEX*96
#define BACKGROUNDSIZEY TILEY*96

//���� ī�޶� ������
#define CAMERA2X 1100
#define CAMERA2Y 1080

// Ÿ�� �԰�
#define TILESIZE 96
#define TILESIZE2 32

// Ÿ�� ����
#define TILEX 25
#define TILEY 16

// Ÿ�� �� ������
#define TILESIZEX TILESIZE * TILEX
#define TILESIZEY TILESIZE * TILEY

// Ÿ�ϼ� ����
#define SAMPLETILEX 23
#define SAMPLETILEY 26

// ���̸�
#define MAPNAME "weaponsStore.map"

// ����	
enum TERRAIN
{
	//������ ������ �� �ִ� ��� ����
	TR_WALL, TR_NULL
};

// ������Ʈ
enum OBJECT
{
	//�������	���������¶�		�Ʒ������� �������¶�		���������� �� ���	�̴��̹�			����
	OBJ_NONE,	 OBJ_GROUND,	OBJ_GOGROUND,			 OBJ_CULUMN,		 OBJ_DOOR,		 OBJ_THORN
};

// ������ ����
enum POS
{
	//������ �� �÷��̾� ������ ��(��������)	�÷��̾� ����� ����		������ ����		��������
	POS_PLAYER,								POS_ENEMY1,				 POS_ENEMY2,	POS_TREASURE
};

// Ÿ�� ����ü
struct tagTile
{
	TERRAIN terrain;			// ����
	OBJECT	object;				// ������Ʈ
	POS		position;			//������
	RECT	rc;					// ��Ʈ
	int		terrainFrameX;		// ���� ������ ��ȣ
	int		terrainFrameY;		// ���� ������ ��ȣ
	int		objFrameX;			// ������Ʈ ������ ��ȣ
	int		objFrameY;			// ������Ʈ ������ ��ȣ
};

// Ÿ�ϼ� ����ü
struct tagSampleTile
{
	RECT rctile;				// Ÿ�ϼ� ��Ʈ
	int terrainFrameX;			// Ÿ�ϼ� ������ ��ȣ
	int terrainFrameY;			// Ÿ�ϼ� ������ ��ȣ
};

// ������ ����
struct tagCurrentTile
{
	int x;
	int y;
};