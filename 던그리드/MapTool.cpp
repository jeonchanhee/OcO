#include "stdafx.h"
#include "MapTool.h"


HRESULT MapTool::init()
{
	IMAGEMANAGER->addFrameImage("map", "image/map/Map(2208x2496,23x26).bmp", 0, 0, 2208, 2496, SAMPLETILEX, SAMPLETILEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("map2", "image/map/Map2(736x832,23x26).bmp", 0, 0, 736, 832, SAMPLETILEX, SAMPLETILEY, true, RGB(255, 0, 255));

	setup();

	// 버튼 렉트
	for (int i = 0; i < 5; i++)
	{
			_rc[i] = RectMakeCenter((WINSIZEX / 2 + 300) + i * 125, WINSIZEY / 2 + 400, 120, 50);
	}
	
	return S_OK;
}

void MapTool::release(){}

void MapTool::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))setmap();

	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		POINT mouse = getMemDCPoint();

		if (_ptMouse.x < CAMERAX && _ptMouse.y < CAMERAY)
		{
			for (int i = 0; i < TILEX * TILEY; i++)
			{
				if (PtInRect(&_tiles[i].rc, mouse))
				{
					_tiles[i].objFrameX = NULL;
					_tiles[i].objFrameY = NULL;

					_tiles[i].object = OBJ_NONE;

					InvalidateRect(_hWnd, NULL, false);
					break;
				}
			}
		}
	}

	if (KEYMANAGER->isOnceKeyDown('Y'))
	{
		for (int i = 0; i < TILEX * TILEY; i++)
		{
			_tiles[i].terrainFrameX = _currentTile.x;
			_tiles[i].terrainFrameY = _currentTile.y;

			_tiles[i].terrain = terrainSelect(_currentTile.x, _currentTile.y);
		}
	}
}

void MapTool::render()
{
	IMAGEMANAGER->render("map2", UIDC, WINSIZEX - IMAGEMANAGER->findImage("map2")->getWidth(), 0);
	
	// 버튼 렉트
	for (int i = 0; i < 5; i++)
	{
		Rectangle(UIDC, _rc[i].left, _rc[i].top, _rc[i].right, _rc[i].bottom);
	}

	// 폰트

	SetTextColor(UIDC, RGB(0, 0, 0));

	HFONT font, oldFont;
	
	font = CreateFont(30, 0, 0, 0, 100, 0, 0, 0, DEFAULT_CHARSET,
		OUT_STRING_PRECIS, CLIP_CHARACTER_PRECIS, PROOF_QUALITY,
		DEFAULT_PITCH | FF_SWISS, TEXT("Bernard MT Condensed"));
	oldFont = (HFONT)SelectObject(DC, font);
	DrawText(UIDC, TEXT("저장"), strlen("저장"), &_rc[0], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	DrawText(UIDC, TEXT("불러오기"), strlen("불러오기"), &_rc[1], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	DrawText(UIDC, TEXT("지형"), strlen("지형"), &_rc[2], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	DrawText(UIDC, TEXT("오브젝트"), strlen("오브젝트"), &_rc[3], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	DrawText(UIDC, TEXT("지우개"), strlen("지우개"), &_rc[4], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	SelectObject(DC, oldFont);
	DeleteObject(font);


	// 지형
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		IMAGEMANAGER->frameRender("map", DC, _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
		//if(i == 444)

	}

	// 오브젝트
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		// 오브젝트 속성이 아니면 그리지마
		if (_tiles[i].object == OBJ_NONE) continue;
		
		IMAGEMANAGER->frameRender("map", DC, _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
	}

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		for (int i = 0; i < TILEX * TILEY; i++)
		{
			Rectangle(DC,_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].rc.right, _tiles[i].rc.bottom);
			char str[128];
			sprintf_s(str, "%d", i);
			TextOut(DC, _tiles[i].rc.left, _tiles[i].rc.top, str, strlen(str));
		}

		for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
		{
			Rectangle(UIDC, _sampleTile[i].rctile.left, _sampleTile[i].rctile.top, _sampleTile[i].rctile.right, _sampleTile[i].rctile.bottom);
			char str[128];
			sprintf_s(str, "%d", i);
			TextOut(UIDC, _sampleTile[i].rctile.left, _sampleTile[i].rctile.top, str, strlen(str));
		}
	}
}

void MapTool::save()
{
	HANDLE	file;
	DWORD	save;

	file = CreateFile(MAPNAME, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &save, NULL);

	CloseHandle(file);
}

void MapTool::load()
{
	HANDLE	file;
	DWORD	load;

	ZeroMemory(&_tiles, sizeof(tagTile) * TILEX * TILEY);

	file = CreateFile(MAPNAME, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &load, NULL);

	for (int i = 0; i < TILESIZEX; ++i)
	{
		for (int j = 0; j < TILESIZEY; ++j)
		{
			//텬댱 
			if (_tiles[i * TILESIZEX + j].objFrameX == 0 && _tiles[i * TILESIZEX + j].objFrameY == 2) _tiles[i* TILESIZEX + j].object = OBJ_CEILING;
			if (_tiles[i * TILESIZEX + j].objFrameX == 1 && _tiles[i * TILESIZEX + j].objFrameY == 2) _tiles[i* TILESIZEX + j].object = OBJ_CEILING;
			if (_tiles[i * TILESIZEX + j].objFrameX == 2 && _tiles[i * TILESIZEX + j].objFrameY == 2) _tiles[i* TILESIZEX + j].object = OBJ_CEILING;
			if (_tiles[i * TILESIZEX + j].objFrameX == 0 && _tiles[i * TILESIZEX + j].objFrameY == 6) _tiles[i* TILESIZEX + j].object = OBJ_CEILING;
			if (_tiles[i * TILESIZEX + j].objFrameX == 1 && _tiles[i * TILESIZEX + j].objFrameY == 6) _tiles[i* TILESIZEX + j].object = OBJ_CEILING;
			if (_tiles[i * TILESIZEX + j].objFrameX == 2 && _tiles[i * TILESIZEX + j].objFrameY == 6) _tiles[i* TILESIZEX + j].object = OBJ_CEILING;

			//양학선 급 대각선 

		}
	}

	CloseHandle(file);

	
	/*for (int i = 353; i < TILEX*TILEY; i++)
	{
		_tiles[i].terrainFrameX = 596%22;
		_tiles[i].terrainFrameY = 596/22;
		_tiles[i].objFrameX = 0;
		_tiles[i].objFrameY = 0;
		_tiles[i].terrain = terrainSelect(_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
		_tiles[i].object = OBJ_NONE;
	}*/
}

void MapTool::setup()
{
	
	for (int i = 0; i < SAMPLETILEY; ++i)
	{
		for (int j = 0; j < SAMPLETILEX; ++j)
		{
			_sampleTile[i * SAMPLETILEX + j].terrainFrameX = j;
			_sampleTile[i * SAMPLETILEX + j].terrainFrameY = i;

			SetRect(&_sampleTile[i * SAMPLETILEX + j].rctile,
				(WINSIZEX - IMAGEMANAGER->findImage("map2")->getWidth()) + j * TILESIZE /3,
				i * TILESIZE /3,
				(WINSIZEX - IMAGEMANAGER->findImage("map2")->getWidth()) + j * TILESIZE /3 + TILESIZE /3,
				i * TILESIZE /3 + TILESIZE /3);
		}
	}

	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			SetRect(&_tiles[i * TILEX + j].rc, j * TILESIZE, i * TILESIZE, j* TILESIZE + TILESIZE, i * TILESIZE + TILESIZE);
		}
	}

	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		_tiles[i].terrainFrameX = 0;
		_tiles[i].terrainFrameY = 0;
		_tiles[i].objFrameX = 0;
		_tiles[i].objFrameY = 0;
		_tiles[i].terrain = terrainSelect(_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
		_tiles[i].object = OBJ_NONE;
	}
}

void MapTool::setmap()
{
	POINT mouse = getMemDCPoint();
	for (int i = 0; i < 5; i++)
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
			_currentTile.x = _sampleTile[i].terrainFrameX;
			_currentTile.y = _sampleTile[i].terrainFrameY;
			break;
		}
	}

	//if (_ptMouse.x < CAMERAX&&_ptMouse.y < CAMERAY)
	{
		for (int i = 0; i < TILEX * TILEY; i++)
		{
			if (PtInRect(&_tiles[i].rc, mouse))
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
	for (int i = 15; i < 19; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (FrameX == i && FrameY == j) return TR_WALL;
		}
	}

	for (int i = 19; i < 24; i++)
	{
		for (int j = 0; j < 18; j++)
		{
			if (FrameX == i && FrameY == j) return TR_WALL;
		}
	}

	return TR_WALL;
}

OBJECT MapTool::objSelect(int FrameX, int FrameY)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (FrameX == i && FrameY == j) return OBJ_CULUMN;
			if (j == 2)
			{
				if (FrameX == i && FrameY == j) return OBJ_CEILING;
			}
			if (j == 4)
			{
				if (FrameX == i && FrameY == j) return OBJ_CEILING;
			}
			if (j == 6)
			{
				if (FrameX == i && FrameY == j) return OBJ_CEILING;
			}
		}
	}

	for (int i = 3; i < 13; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (FrameX == i && FrameY == j) return OBJ_GROUND; 
		}
	}

	for (int i = 3; i < 5; i++)
	{
		if (FrameX == i && FrameY == 3) return OBJ_GROUND;
	}
	
	for (int i = 3; i < 11; i++)
	{
		if (FrameX == i && FrameY == 4) return OBJ_GROUND;
	}
	
	for (int i = 10; i < 19; i++)
	{
		if (FrameX == i && FrameY == 1) return OBJ_GROUND;
	}

	for (int i = 5; i < 10; i++)
	{
		for (int j = 17; j < 18; j++)
		{
			if(FrameX == i && FrameY == j) return OBJ_GROUND;
		}
	}
	
	for (int i = 15; i < 21; i++)
	{
		if (FrameX == i && FrameY == 18) return OBJ_GROUND;
	}

	for (int i = 0; i < 4; i++)
	{
		if (FrameX == i && FrameY == 24) return OBJ_GROUND;
	}

	for (int i = 0; i < 19; i++)
	{
		if (FrameX == i && FrameY == 25) return OBJ_GROUND;
	}

	for (int i = 17; i < 20; i++)
	{
		if (FrameX == i && FrameY == 13) return OBJ_THORN;
	}

	//오브젝트인지 잘 모르겠음
	for (int i = 5; i < 8; i++)
	{
		for (int j = 5; j < 8; j++)
		{
			if (i == 6 && j == 6) continue;
			if (FrameX == i && FrameY == j) return OBJ_GROUND;
		}
	}
	for (int i = 8; i < 11; i++)
	{
		if (FrameX = i && FrameY == 5) return OBJ_GROUND;
	}

	if (FrameX == 8 && FrameY == 6) return OBJ_GROUND;
	//여기까지

	if (FrameX == 11 && FrameY == 0) return OBJ_GROUND;
	if (FrameX == 12 && FrameY == 0) return OBJ_GROUND;
	if (FrameX == 13 && FrameY == 0) return OBJ_GROUND;
	if (FrameX == 7 && FrameY == 3) return OBJ_GROUND;
	if (FrameX == 8 && FrameY == 3) return OBJ_GROUND;
	if (FrameX == 10 && FrameY == 3) return OBJ_GROUND;
	if (FrameX == 11 && FrameY == 18) return OBJ_GROUND;
	if (FrameX == 12 && FrameY == 18) return OBJ_GROUND;
	if (FrameX == 3 && FrameY == 12) return	OBJ_GOGROUND;
	if (FrameX == 6 && FrameY == 24) return OBJ_GROUND;
	if (FrameX == 7 && FrameY == 24) return OBJ_GROUND;
	if (FrameX == 8 && FrameY == 24) return OBJ_GROUND;


	return OBJ_NONE;
}

MapTool::MapTool(){}

MapTool::~MapTool(){}
