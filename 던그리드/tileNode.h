#pragma once

// 타일 규격
#define TILESIZE 96

// 타일 갯수
#define TILEX 10
#define TILEY 10

// 타일 총 사이즈
#define TILESIZEX TILESIZE * TILEX
#define TILESIZEY TILESIZE * TILEY

// 타일셋 갯수
#define SAMPLETILEX 32
#define SAMPLETILEY 15

// 지형	
enum TERRAIN
{
	// 얼음	 흙			풀			던전				가시
	TR_ICE,  TR_SOIL,	TR_GRASS,	TR_DUNGEON,		TR_THORN
};

// 오브젝트
enum OBJECT
{
	OBJ_NONE
};

// 포지션 정의
enum POS
{
	POS_PLAYER, POS_ENEMY
};

// 타일 구조체
struct tagTile
{
	TERRAIN terrain;			// 지형
	OBJECT	object;				// 오브젝트
	RECT	rc;					// 렉트
	int		terrainFrameX;		// 지형 프레임 번호
	int		terrainFrameY;		// 지형 프레임 번호
	int		objFrameX;			// 오브젝트 프레임 번호
	int		objFrameY;			// 오브젝트 프레임 번호
};

// 타일셋 구조체
struct tagSampleTile
{
	RECT rctile;				// 타일셋 렉트
	int terrainFrameX;			// 타일셋 프레임 번호
	int terrainFrameY;			// 타일셋 프레임 번호
};

// 선택한 파일
struct tagCurrentTile
{
	int x;
	int y;
};