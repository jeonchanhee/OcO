#pragma once
#include "gameNode.h"

//�� Ÿ���� �԰��� 32 x 32�� �Ѵ�
#define TILESIZE 32

//Ÿ�� ���� X 20, Y 20
#define TILEX 20
#define TILEY 20

//Ÿ�� �� ������ 640 x 640
#define TILESIZEX TILESIZE * TILEX
#define TILESIZEY TILESIZE * TILEY

//Ÿ�ϼ� (���������� ����Ÿ��) ����
#define SAMPLETILEX 20
#define SAMPLETILEY 9

//�ͷ��� == ����
enum TERRAIN
{
	TR_CEMENT, TR_DESERT, TR_GRASS, TR_WATER, TR_END
};

//������Ʈ 
enum OBJECT
{
	OBJ_BLOCK1, OBJ_BLOCK3, OBJ_BLOCKS,	//���� ������Ʈ
	OBJ_FLAG1, OBJ_FLAG2,				//���� �� ���
	OBJ_TANK1, OBJ_TANK2,				//��ũ ��������ġ
	OBJ_NONE							
};

//�����ǿ� ���� ����
enum POS
{
	POS_FLAG1, POS_FLAG2,	//��� ��ġ(Ÿ��)
	POS_TANK1, POS_TANK2	//��ũ ��ġ(Ÿ��)
};

//Ÿ�Ͽ� ���� ����ü
struct tagTile
{
	TERRAIN terrain;			//���� �̳ѹ�
	OBJECT	obj;				//������Ʈ �̳ѹ�
	RECT	rc;					//��Ʈ
	int		terrainFrameX;		//���� ������ ��ȣ(�̹���)
	int		terrainFrameY;		//���� ������ ��ȣ
	int		objFrameX;			//������Ʈ ������ ��ȣ
	int		objFrameY;			//������Ʈ ������ ��ȣ
};

//Ÿ�ϼ� ����ü
struct tagSampleTile
{
	RECT rcTile;		//Ÿ�ϼ� ��Ʈ
	int terrainFrameX;	//Ÿ�ϼ� ������ ��ȣ
	int terrainFrameY;	//Ÿ�ϼ� ������ ��ȣ
};

//���� Ÿ�� == ���� ���� Ŭ���� Ÿ�Ͽ� ���� ���� ����� ����ü
struct tagCurrentTile
{
	int x;
	int y;
};

class playGround : public gameNode
{
private:
	HWND _btnSave;			//���� ��ư
	HWND _btnLoad;			//�ҷ����� ��ư
	HWND _btnTerrainDraw;	//���� �׸��� ��ư
	HWND _btnObjectDraw;	//������Ʈ �׸��� ��ư
	HWND _btnEraser;		//���찳 ��ư

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

	//� ����, � ������Ʈ�� �����ߴ��� ���θ� ��ȯ�ϴ� �Լ�
	TERRAIN terrainSelect(int frameX, int frameY);
	OBJECT objSelect(int frameX, int frameY);

	playGround();
	~playGround();
};

