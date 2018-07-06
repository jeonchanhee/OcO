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
	///*���⼭ ���͸� �߰��� ������ �����Ű��� ? ? ;
	//�ٵ���
	//	���ʹ� �Ŵ����� �ֳ���
	//	����
	//	�׷�����
	//	�ٵ�
	//	���鿡��
	//	������ ������
	//	�Ȼ�����µ�
	//	��� �ؾߵǳ���
	//	����
	//	�׷�����
	//	�ƹ�ư
	//	�׷��ٰ� �մϴ�
	//	���⼭
	//	�����ϴ�
	//	�Լ���
	//	�����صΰ�

	//	����
	//	���Ϳ� ���
	//	���ͱ�
	//	������
	//	����� 0�̵ȴٸ�
	//	�ش� ����
	//	Ŭ�����ѰŰ���
	//	�װŴ�
	//	���ڸ���
	//	����
	//	ģ����
	//	�����ٲ�����
	//	ȿ���̿�
	//	�ƹ�ư
	//	���ʹ� �Ŵ�����
	//	������
	//	��
	//	�����ߵɲ�������
	//	��*/
}


