#pragma once

// Ÿ�� �԰�
#define TILESIZE 96

// Ÿ�� ����
#define TILEX 10
#define TILEY 10

// Ÿ�� �� ������
#define TILESIZEX TILESIZE * TILEX
#define TILESIZEY TILESIZE * TILEY

// Ÿ�ϼ� ����
#define SAMPLETILEX 32
#define SAMPLETILEY 15

// ����	
enum TERRAIN
{
	// ����	 ��			Ǯ			����				����
	TR_ICE,  TR_SOIL,	TR_GRASS,	TR_DUNGEON,		TR_THORN
};

// ������Ʈ
enum OBJECT
{
	OBJ_NONE
};

// ������ ����
enum POS
{
	POS_PLAYER, POS_ENEMY
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