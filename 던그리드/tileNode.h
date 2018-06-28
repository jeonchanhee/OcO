#pragma once

// Ÿ�� �԰�
#define TILESIZE 96
#define TILESIZE2 32

// Ÿ�� ����
#define TILEX 10
#define TILEY 10

// Ÿ�� �� ������
#define TILESIZEX TILESIZE * TILEX
#define TILESIZEY TILESIZE * TILEY

// Ÿ�ϼ� ����
#define SAMPLETILEX 23
#define SAMPLETILEY 26

// ����	
enum TERRAIN
{
	// 
	TR_WALL,  TR_GROUND, TR_GOGROUND,	TR_THORN
};

// ������Ʈ
enum OBJECT
{
	OBJ_NONE
};

// ������ ����
enum POS
{
	POS_PLAYER, POS_ENEMY1, POS_ENEMY2
};

// Ÿ�� ����ü
struct tagTile
{
	TERRAIN terrain;			// ����
	OBJECT	object;				// ������Ʈ
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