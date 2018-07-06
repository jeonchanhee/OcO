#include "stdafx.h"
#include "dungeonScene.h"
#include "tileNode.h"


dungeonScene::dungeonScene() {}

dungeonScene::~dungeonScene() {}


HRESULT dungeonScene::init(void)
{
	return S_OK;
}

void dungeonScene::release(void)
{
}

void dungeonScene::update(void)
{
	KEYANIMANAGER->update();
}

void dungeonScene::render(void)
{
	for (int i = (CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2) / 96; i < (CAMERAMANAGER->getCameraCenter().y + WINSIZEY / 2) / 96 + 1; ++i)
	{
		for (int j = (CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2) / 96; j < (CAMERAMANAGER->getCameraCenter().x + WINSIZEX / 2) / 96 + 1; ++j)
		{
			//if (i >= _tileX || j >= _tileY) continue;

			IMAGEMANAGER->frameRender("map", DC, _tiles[i * _temp + j].rc.left, _tiles[i * _temp + j].rc.top, _tiles[i * _temp + j].terrainFrameX, _tiles[i * _temp + j].terrainFrameY);

			//char str[128];
			//sprintf_s(str, "%d", i * _temp + j);
			//TextOut(DC, _tiles[i * _temp + j].rc.left, _tiles[i * _temp + j].rc.top, str, strlen(str));
		}
	}

	for (int i = (CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2) / 96; i < (CAMERAMANAGER->getCameraCenter().y + WINSIZEY / 2) / 96 + 1; ++i)
	{
		for (int j = (CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2) / 96; j < (CAMERAMANAGER->getCameraCenter().x + WINSIZEX / 2) / 96 + 1; ++j)
		{
			if (_tiles[i * _temp + j].object == OBJ_NONE) continue;

			IMAGEMANAGER->frameRender("map", DC, _tiles[i * _temp + j].rc.left, _tiles[i * _temp + j].rc.top, _tiles[i * _temp + j].objFrameX, _tiles[i * _temp + j].objFrameY);
		}
	}
}

void dungeonScene::mapload()
{
	HANDLE   file;
	DWORD   load;
	ZeroMemory(&_tiles, sizeof(tagTile) * TILEX * TILEY);

	file = CreateFile(_mapName.c_str(), GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &load, NULL);

	CloseHandle(file);
	///*여기서 몬스터를 추가할 생각은 없으신가요 ? ? ;
	//근데왜
	//	에너미 매니저가 있나요
	//	아하
	//	그렇군요
	//	근데
	//	깃헙에서
	//	삭제를 눌러도
	//	안사라지는데
	//	어떻게 해야되나요
	//	아하
	//	그렇군요
	//	아무튼
	//	그렇다고 합니다
	//	여기서
	//	생성하는
	//	함수를
	//	설정해두고

	//	만들어서
	//	백터에 담고
	//	백터긔
	//	백터의
	//	사이즈가 0이된다면
	//	해당 방을
	//	클리어한거겠죠
	//	그거는
	//	이자리에
	//	앉은
	//	친구가
	//	잘해줄꺼에요
	//	효원이요
	//	아무튼
	//	에너미 매니저는
	//	빠르게
	//	좀
	//	지워야될꺼같은데
	//	어*/
}


