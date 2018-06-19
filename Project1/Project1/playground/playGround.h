#pragma once
#include "gameNode.h"

//한 타일의 규격은 32 x 32로 한다
#define TILESIZE 32

//타일 갯수 X 20, Y 20
#define TILEX 20
#define TILEY 20

//타일 총 사이즈 640 x 640
#define TILESIZEX TILESIZE * TILEX
#define TILESIZEY TILESIZE * TILEY

//타일셋 (맵툴에서의 샘플타일) 갯수
#define SAMPLETILEX 20
#define SAMPLETILEY 9

//터레인 == 지형
enum TERRAIN
{
	TR_CEMENT, TR_DESERT, TR_GRASS, TR_WATER, TR_END
};

//오브젝트 
enum OBJECT
{
	OBJ_BLOCK1, OBJ_BLOCK3, OBJ_BLOCKS,	//벽돌 오브젝트
	OBJ_FLAG1, OBJ_FLAG2,				//진영 별 깃발
	OBJ_TANK1, OBJ_TANK2,				//탱크 리스폰위치
	OBJ_NONE							
};

//포지션에 대한 정의
enum POS
{
	POS_FLAG1, POS_FLAG2,	//깃발 위치(타일)
	POS_TANK1, POS_TANK2	//탱크 위치(타일)
};

//타일에 대한 구조체
struct tagTile
{
	TERRAIN terrain;			//지형 이넘문
	OBJECT	obj;				//오브젝트 이넘문
	RECT	rc;					//렉트
	int		terrainFrameX;		//지형 프레임 번호(이미지)
	int		terrainFrameY;		//지형 프레임 번호
	int		objFrameX;			//오브젝트 프레임 번호
	int		objFrameY;			//오브젝트 프레임 번호
};

//타일셋 구조체
struct tagSampleTile
{
	RECT rcTile;		//타일셋 렉트
	int terrainFrameX;	//타일셋 프레임 번호
	int terrainFrameY;	//타일셋 프레임 번호
};

//현재 타일 == 내가 현재 클릭한 타일에 대한 정보 저장용 구조체
struct tagCurrentTile
{
	int x;
	int y;
};

class playGround : public gameNode
{
private:
	HWND _btnSave;			//저장 버튼
	HWND _btnLoad;			//불러오기 버튼
	HWND _btnTerrainDraw;	//지형 그리기 버튼
	HWND _btnObjectDraw;	//오브젝트 그리기 버튼
	HWND _btnEraser;		//지우개 버튼

	tagCurrentTile	_currentTile;
	tagSampleTile	_sampleTile[SAMPLETILEX * SAMPLETILEY];
	tagTile			_tiles[TILEX * TILEY];

	int _pos[2];
	

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void setup();
	virtual void setMap();
	virtual void save();
	virtual void load();

	//어떤 지형, 어떤 오브젝트를 선택했는지 여부를 반환하는 함수
	TERRAIN terrainSelect(int frameX, int frameY);
	OBJECT objSelect(int frameX, int frameY);

	playGround();
	~playGround();
};

