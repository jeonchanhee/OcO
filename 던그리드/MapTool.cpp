#include "stdafx.h"
#include "MapTool.h"


HRESULT MapTool::init()
{
	IMAGEMANAGER->addFrameImage("map", "Map.bmp", 0, 0, 3072, 1440, SAMPLETILEX, SAMPLETILEY, true, RGB(255, 0, 255));

	setup();

	// 버튼 렉트
	for (int i = 0; i < 5; i++)
	{
			if (i <= 3)	_rc[i] = RectMakeCenter((WINSIZEX / 2 + 500) + i * 125, WINSIZEY / 2 + 50, 120, 50);
			else
			{
				_rc[i] = RectMakeCenter((WINSIZEX / 2 + 500), (WINSIZEY / 2 + 50) + 100, 120, 50);
			}
	}
	

	return S_OK;
}

void MapTool::release(){}

void MapTool::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) setmap();
}

void MapTool::render()
{
	IMAGEMANAGER->render("map", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("map")->getWidth(), 0);
	
	// 버튼 렉트
	for (int i = 0; i < 7; i++)
	{
		Rectangle(getMemDC(), _rc[i].left, _rc[i].top, _rc[i].right, _rc[i].bottom);
	}

	// 폰트

	SetTextColor(getMemDC(), RGB(0, 0, 0));

	HFONT font, oldFont;
	
	font = CreateFont(30, 0, 0, 0, 100, 0, 0, 0, DEFAULT_CHARSET,
		OUT_STRING_PRECIS, CLIP_CHARACTER_PRECIS, PROOF_QUALITY,
		DEFAULT_PITCH | FF_SWISS, TEXT("Bernard MT Condensed"));
	oldFont = (HFONT)SelectObject(getMemDC(), font);
	DrawText(getMemDC(), TEXT("저장"), strlen("저장"), &_rc[0], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	DrawText(getMemDC(), TEXT("불러오기"), strlen("불러오기"), &_rc[1], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	DrawText(getMemDC(), TEXT("지형"), strlen("지형"), &_rc[2], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	DrawText(getMemDC(), TEXT("오브젝트"), strlen("오브젝트"), &_rc[3], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	DrawText(getMemDC(), TEXT("지우개"), strlen("지우개"), &_rc[4], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);


	// 지형
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		IMAGEMANAGER->frameRender("map", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
	}

	// 오브젝트
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		// 오브젝트 속성이 아니면 그리지마
		if (_tiles[i].object == OBJ_NONE) continue;
		
		IMAGEMANAGER->frameRender("map", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
	}

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		for (int i = 0; i < TILEX * TILEY; i++)
		{
			Rectangle(getMemDC(),_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].rc.right, _tiles[i].rc.bottom);
		}
	}
}

void MapTool::save()
{
	HANDLE	file;
	DWORD	save;

	file = CreateFile("mapTool.map", GENERIC_READ, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &save, NULL);

	CloseHandle(file);
}

void MapTool::load()
{
	HANDLE	file;
	DWORD	load;

	file = CreateFile("mapTool.map", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &load, NULL);

	CloseHandle(file);
}

void MapTool::setup()
{
	//_select = TRRAINDRAW;

	// 샘플타일셋	
		
	for (int i = 0; i < SAMPLETILEY; ++i)
	{
		for (int j = 0; j < SAMPLETILEX; ++j)
		{
			_sampleTile[i * SAMPLETILEX + j].terrainFrameX = j;
			_sampleTile[i * SAMPLETILEX + j].terrainFrameY = i;

			SetRect(&_sampleTile[i * SAMPLETILEX + j].rctile,
				(WINSIZEX - IMAGEMANAGER->findImage("map")->getWidth()) + j * TILESIZE,
				i * TILESIZE,
				(WINSIZEX - IMAGEMANAGER->findImage("map")->getWidth()) + j * TILESIZE + TILESIZE,
				i * TILESIZE + TILESIZE);
		}
	}

	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEY; j++)
		{
			SetRect(&_tiles[i * TILEX + j].rc, j * TILESIZE, i * TILESIZE, j* TILESIZE + TILESIZE, i * TILESIZE + TILESIZE);
		}
	}

}

void MapTool::setmap()
{
	for (int i = 0; i < 7; i++)
	{
		if (PtInRect(&_rc[i], _ptMouse))
		{
			if (i == 0)
			{
				save();
				break;
			}
			else if (i == 1)
			{
				load();
				break;
			}
			else 
			{
				if (i == 2) _select = TRRAINDRAW;
				if (i == 3) _select = OBJDRAW;
				if (i == 4) _select = ERASER;
				break;
			}
		}
	}

	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
	{
		if (PtInRect(&_sampleTile[i].rctile, _ptMouse))
		{
			_tiles[i].terrainFrameX = _currentTile.x;
			_tiles[i].terrainFrameY = _currentTile.y;
			break;
		}
	}

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (PtInRect(&_tiles[i].rc, _ptMouse))
		{
			if (PtInRect(&_tiles[i].rc, _ptMouse))
			{
				if (_select == TRRAINDRAW)
				{
					_tiles[i].terrainFrameX = _currentTile.x;
					_tiles[i].terrainFrameY = _currentTile.y;

					_tiles[i].terrain = terrainSelect(_currentTile.x, _currentTile.y);
				}
				else if (_select == OBJDRAW)
				{
					_tiles[i].objFrameX = _currentTile.x;
					_tiles[i].objFrameY = _currentTile.y;

					_tiles[i].object = objSelect(_currentTile.x, _currentTile.y);
				}
				else if (_select == ERASER)
				{
					_tiles[i].objFrameX = NULL;
					_tiles[i].objFrameY = NULL;

					_tiles[i].object = OBJ_NONE;
				}

				InvalidateRect(_hWnd, NULL, false);
				break;
			}
		}
	}
}

TERRAIN MapTool::terrainSelect(int FrameX, int FrameY)
{
	if(FrameX == 1 && FrameY == 0) return TR_ICE;
	if (FrameX == 2 && FrameY == 0) return TR_SOIL;
	if (FrameX == 3 && FrameY == 0) return TR_GRASS;
	if (FrameX == 4 && FrameY == 0) return TR_DUNGEON;
	return TR_GRASS;
}

OBJECT MapTool::objSelect(int FrameX, int FrameY)
{
	return OBJECT();
}

MapTool::MapTool(){}

MapTool::~MapTool(){}
