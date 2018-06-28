#pragma once
#include "tileNode.h"
#include "gameNode.h"

enum SELECT
{
	TRRAINDRAW,
	OBJDRAW,
	ERASER
};


class MapTool :	public gameNode
{
private:
	tagTile		_tiles[TILEX * TILEY];
	tagCurrentTile	_currentTile;
	tagSampleTile	_sampleTile[SAMPLETILEX * SAMPLETILEY];
	DWORD		_attribute[TILEX * TILEY];				// Ÿ�� �Ӽ�	

	RECT		_rc[5];									// ��ư ��Ʈ
	SELECT		_select;

	int			_pos[2];
public:

	HRESULT init();
	void release();
	void update();
	void render();
		
	void setup();
	virtual void save();											// ���̺�
	virtual void load();											// �ε�
	virtual void setmap();

	//TERRAIN		terrainSelect(int FrameX, int FrameY);		// � ������ �����ߴ���
	OBJECT		objSelect(int FrameX, int FrameY);			// ��� ������Ʈ�� �����ߴ���

	tagTile*	getTiles()		{ return _tiles; }			// Ÿ�� ������
	DWORD*		getAttribute()	{ return _attribute; }		// Ÿ�� �Ӽ� ������

	MapTool();
	~MapTool();
};

