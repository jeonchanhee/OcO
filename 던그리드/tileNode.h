#pragma once

#ifndef _TILE_H_
#define _TILE_H_

// Ÿ�� ����(50,50)�� ���� �⺻�Դϴ�~~, �����ϸ� Ŀ���� �ٲ㼭 �÷��ּ���~~
#define TILEX 80
#define TILEY 50
//(80,25)�� Ÿ����Դϴ�
//#define TILEX 80
//#define TILEY 25

// ��ü �� ������ �Դϴ�   ���� �ο�Ź �帳�ϴ�
#define BACKGROUNDSIZEX TILEX*96
#define BACKGROUNDSIZEY TILEY*96

//���� ī�޶� ������
#define CAMERAX 1100
#define CAMERAY 1080

// Ÿ�� �԰�
#define TILESIZE 96
#define TILESIZE2 32


//#define TILEX 28
//#define TILEY 12

// Ÿ�� �� ������
#define TILESIZEX TILESIZE * TILEX
#define TILESIZEY TILESIZE * TILEY

// Ÿ�ϼ� ����
#define SAMPLETILEX 23
#define SAMPLETILEY 26

// ���̸�
#define MAPNAME "map/Dungeon9(20x11).map"

// ����	
enum TERRAIN
{
	//������ ������ �� �ִ� ��� ����
	TR_WALL, TOWN_GROUND, TR_NULL
};

// ������Ʈ
enum OBJECT
{
	//�������	���������¶�		�Ʒ������� �������¶�		���������� �� ���	�̴��̹�			����		      õ��        �밢���� ���� �������������������������������������������� ��¦
	OBJ_NONE, 	OBJ_GROUND,			OBJ_GOGROUND,		 OBJ_CULUMN,		OBJ_vDoor,    OBJ_THORN,  OBJ_CEILING ,  OBJ_DIAGONAL,  OBJ_DIAGONAL_LEFT , OBJ_DIAGONAL_RIGHT, OBJ_DOOR
};

// ������ ����
enum POS
{
	//������ �� �÷��̾� ������ ��(��������)	�÷��̾� ����� ����		������ ����		��������
	POS_PLAYER, POS_ENEMY1, POS_ENEMY2, POS_TREASURE
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

extern tagTile	_tiles[TILEX * TILEY];

extern int TILEVALUE[12][2]; //0: ����, 1,3~9: ����, 10: ����, 2,11:����

extern int _tileX, _tileY;

extern int VARIABLE_SIZEX[12];

extern bool _canMove;

extern int _dungeonNum;

#endif 