#include "stdafx.h"
#include "dungeonScene.h"
#include "tileNode.h"
#include "Player.h"


dungeonScene::dungeonScene() {}

dungeonScene::~dungeonScene() {}

HRESULT dungeonScene::init(void)
{
	_player = SCENEMANAGER->getPlayerAddressLink();
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
	if (KEYMANAGER->isToggleKey(VK_F3))
	{
		for (int i = (CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2) / 96; i < (CAMERAMANAGER->getCameraCenter().y + WINSIZEY / 2) / 96 + 1; ++i)
		{
			for (int j = (CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2) / 96; j < (CAMERAMANAGER->getCameraCenter().x + WINSIZEX / 2) / 96 + 1; ++j)
			{
				IMAGEMANAGER->frameRender("map", DC, _tiles[i * _temp + j].rc.left, _tiles[i * _temp + j].rc.top, _tiles[i * _temp + j].terrainFrameX, _tiles[i * _temp + j].terrainFrameY);
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
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		for (int i = (CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2) / 96; i < (CAMERAMANAGER->getCameraCenter().y + WINSIZEY / 2) / 96 + 1; ++i)
		{
			for (int j = (CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2) / 96; j < (CAMERAMANAGER->getCameraCenter().x + WINSIZEX / 2) / 96 + 1; ++j)
			{
				char str[128];
				sprintf_s(str, "%d", i * _temp + j);
				TextOut(DC, _tiles[i * _temp + j].rc.left, _tiles[i * _temp + j].rc.top, str, strlen(str));
			}
		}
	}

	for (int i = 0; i < _vDoor.size(); i++)
	{
		//Rectangle(DC, _vDoor[i].rc.left, _vDoor[i].rc.top, _vDoor[i].rc.right, _vDoor[i].rc.bottom);
		//_vDoor[i].img->frameRender(DC, _vDoor[i].rc.left, _vDoor[i].rc.top);
	}

	for (int i = 0; i < _vTorch.size(); i++)
	{
		_vTorch[i].img->aniRender(DC, _vTorch[i].x, _vTorch[i].y, _vTorch[i].ani);
		//_vTorch[0].img->render(DC, _vTorch[0].x, _vTorch[0].y);
	}

	portalRender();


	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->render();
	}

	//	RECT rc;
	//	rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 100, 100);
	//	Rectangle(DC, rc.left, rc.top, rc.right, rc.bottom);
		//if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && PtInRect(&rc, getMemDCPoint()))
		//{
		//	_mapValue[_dungeonNum] = "T";
		//}
	char str[128];
	sprintf_s(str, "�� : %d, ��� : %d", _dungeonNum, _player->getGold());
	TextOut(DC, 100, 100, str, strlen(str));
	_count++;
	_enemyBullet->render();
	for (int i = 0; i < 20; i++)
	{
		_bigRadBatBullet[i]->render();
	}

	doorRender();
}

void dungeonScene::doorInit(void)
{
}

void dungeonScene::torchInit(int x, int y)
{
	torch torch;
	torch.img = IMAGEMANAGER->findImage("torch");
	torch.ani = KEYANIMANAGER->findAnimation("torchAni");
	torch.x = x * TILESIZE;
	torch.y = y * TILESIZE;
	torch.ani->start();
	_vTorch.push_back(torch);
}

void dungeonScene::portalInit(float x, float y)
{
	Portal portal;
	portal.x = x * TILESIZE;
	portal.y = y * TILESIZE;
	portal.img = IMAGEMANAGER->findImage("portal");
	portal.frameX = 8;
	portal.frameY = portal.count = 0;
	_vPortal.push_back(portal);
}



void dungeonScene::setRandMapNum(void)
{
}


void dungeonScene::mapload()
{
	HANDLE   file;
	DWORD   load;

	ZeroMemory(&_tiles, sizeof(tagTile) * TILEX * TILEY);

	file = CreateFile(_mapName.c_str(), GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &load, NULL);

	//�������� �ٲ� ���� ������ /
	for (int i = 0; i < TILEX; ++i)
	{
		for (int j = 0; j < TILEY; ++j)
		{
			//������ ó�� 
			if (_tiles[i * TILEX + j].terrainFrameX == 1 && _tiles[i * TILEX + j].terrainFrameY == 3) _tiles[i* TILEX + j].object = OBJ_CULUMN;
			//���� 
			if (_tiles[i * TILEX + j].objFrameX == 0 && _tiles[i * TILEX + j].objFrameY == 2) _tiles[i* TILEX + j].object = OBJ_CEILING;
			if (_tiles[i * TILEX + j].objFrameX == 1 && _tiles[i * TILEX + j].objFrameY == 2) _tiles[i* TILEX + j].object = OBJ_CEILING;
			if (_tiles[i * TILEX + j].objFrameX == 2 && _tiles[i * TILEX + j].objFrameY == 2) _tiles[i* TILEX + j].object = OBJ_CEILING;
			if (_tiles[i * TILEX + j].objFrameX == 0 && _tiles[i * TILEX + j].objFrameY == 6) _tiles[i* TILEX + j].object = OBJ_CEILING;
			if (_tiles[i * TILEX + j].objFrameX == 1 && _tiles[i * TILEX + j].objFrameY == 6) _tiles[i* TILEX + j].object = OBJ_CEILING;
			if (_tiles[i * TILEX + j].objFrameX == 2 && _tiles[i * TILEX + j].objFrameY == 6) _tiles[i* TILEX + j].object = OBJ_CEILING;

			////�� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� 
			if (_tiles[i* TILEX + j].objFrameX == 8 && _tiles[i* TILEX + j].objFrameY == 0) _tiles[i* TILEX + j].object = OBJ_DIAGONAL_LEFT;
			if (_tiles[i* TILEX + j].objFrameX == 9 && _tiles[i* TILEX + j].objFrameY == 0) _tiles[i* TILEX + j].object = OBJ_DIAGONAL_RIGHT;
			if (_tiles[i* TILEX + j].objFrameX == 11 && _tiles[i* TILEX + j].objFrameY == 0) _tiles[i* TILEX + j].object = OBJ_DIAGONAL_RIGHT;
			if (_tiles[i* TILEX + j].objFrameX == 11 && _tiles[i* TILEX + j].objFrameY == 21) _tiles[i* TILEX + j].object = OBJ_DIAGONAL;
			if (_tiles[i* TILEX + j].objFrameX == 13 && _tiles[i* TILEX + j].objFrameY == 0) _tiles[i* TILEX + j].object = OBJ_DIAGONAL_LEFT;
			//	if (_tiles[i* TILEX + j].objFrameX == 5 && _tiles[i* TILEX + j].objFrameY == 3) _tiles[i* TILEX + j].object  = OBJ_DIAGONAL;
			if (_tiles[i* TILEX + j].objFrameX == 7 && _tiles[i* TILEX + j].objFrameY == 3) _tiles[i* TILEX + j].object = OBJ_DIAGONAL_RIGHT;
			if (_tiles[i* TILEX + j].objFrameX == 8 && _tiles[i* TILEX + j].objFrameY == 3) _tiles[i* TILEX + j].object = OBJ_DIAGONAL_LEFT;
			if (_tiles[i* TILEX + j].objFrameX == 10 && _tiles[i* TILEX + j].objFrameY == 3) _tiles[i* TILEX + j].object = OBJ_DIAGONAL;
		}
	}

	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (_tiles[i].terrainFrameX == 17 && _tiles[i].terrainFrameY == 1)  _tiles[i].object = OBJ_CULUMN;
		if (_tiles[i].terrainFrameX == 16 && _tiles[i].terrainFrameY == 1)  _tiles[i].object = OBJ_CULUMN;
		if (_tiles[i].terrainFrameX == 12 && _tiles[i].terrainFrameY == 25) _tiles[i].object = OBJ_CULUMN;

	}
	CloseHandle(file);

	_enemyBullet = new Bullet;
	_enemyBullet->init(3000);

	for (int i = 0; i < 20; i++)
	{
		_bigRadBatBullet[i] = new Bullet2;
		_bigRadBatBullet[i]->init(1000);
	}
}

void dungeonScene::setCamera(void)
{
	CAMERAMANAGER->setCameraCenter(PointMake(0, 0));
}

void dungeonScene::selectSize(int idx)
{
	if (idx == 0)
		_temp = 80;
	if (idx == 1)
		_temp = 29;
	if (idx == 2)
		_temp = 29;
	if (idx == 3)
		_temp = 100;
	if (idx == 4)
		_temp = 30;
	if (idx == 5)
		_temp = 25;
	if (idx == 6) //�̻�...
		_temp = 50;
	if (idx == 7)
		_temp = 25;
	if (idx == 8)
		_temp = 20;
	if (idx == 9)
		_temp = 50;
	if (idx == 10)
		_temp = 50;
	if (idx == 11)
		_temp = 25;
}

void dungeonScene::chooseMap(int idx)
{
	if (idx == 0)
		_mapName = "map/townmap(80x25).map";
	if (idx == 1)
		_mapName = "map/Dungeon1(28x11).map";
	if (idx == 2)
		_mapName = "map/Dungeon2(28x13).map";
	if (idx == 3)
		_mapName = "map/Dungeon3(20x13).map";
	if (idx == 4)
		_mapName = "map/Dungeon4(29X16).map";
	if (idx == 5)
		_mapName = "map/Dungeon5(25x16).map";
	if (idx == 6)
		_mapName = "map/Dungeon6(49x28).map";
	if (idx == 7)
		_mapName = "map/Dungeon7(25x30).map";
	if (idx == 8)
		_mapName = "map/Dungeon8(20x39).map";
	if (idx == 9)
		_mapName = "map/Dungeon9(20x11).map";
	if (idx == 10)
		_mapName = "map/bossMap(21,18).map";
	if (idx == 11)
		_mapName = "map/weaponsStore(25x15).map";

	_tileX = TILEVALUE[idx][0], _tileY = TILEVALUE[idx][1];
}

//���� ���� �Լ�
//����
void dungeonScene::setDogBone(int idX, int idY)
{
	DogBone* dogBone;
	dogBone = new DogBone;
	float x = TILESIZE * idX;
	float y = TILESIZE * idY;
	y += TILESIZE / 2 + 15;
	dogBone->init(x, y);
	_vEnemy.push_back(dogBone);
}
//ūĮ��
void dungeonScene::setBigBone(int idX, int idY, int index)
{
	BigBone* bigBone;
	bigBone = new BigBone;
	float x = TILESIZE * idX;
	float y = TILESIZE * idY;
	y -= 20;
	bigBone->init(x, y, index);
	_vEnemy.push_back(bigBone);
}
//Ȱ����
void dungeonScene::setArrow(int idX, int idY)
{
	Arrow* arrow;
	arrow = new Arrow;
	float x = TILESIZE * idX;
	float y = TILESIZE * idY;
	y += 15;
	arrow->init(x, y);
	_vEnemy.push_back(arrow);
}
//�ۺ���
void dungeonScene::setBat(int idX, int idY)
{
	Bat* bat;
	bat = new Bat;
	float x = TILESIZE * idX;
	float y = TILESIZE * idY;
	bat->init(x, y);
	_vEnemy.push_back(bat);
}
//�ۻ���
void dungeonScene::setRedBat(int idX, int idY)
{
	RedBat* redBat;
	redBat = new RedBat;
	float x = TILESIZE * idX;
	float y = TILESIZE * idY;
	redBat->init(x, y);
	_vEnemy.push_back(redBat);
}

void dungeonScene::setBigBat(int idX, int idY)
{
	_bigbat = new BigBat;
	float x = TILESIZE * idX;
	float y = TILESIZE * idY;
	_bigbat->init(x, y);
	_vEnemy.push_back(_bigbat);
}

void dungeonScene::setBigRedBat(int idX, int idY)
{

	_bigRedBat = new BigRedBat;
	float x = TILESIZE * idX;
	float y = TILESIZE * idY;
	_bigRedBat->init(x, y);
	_vEnemy.push_back(_bigRedBat);
}

void dungeonScene::setMusicAngel(int idX, int idY)
{

	_musicAngel = new MusicAngel;
	float x = TILESIZE * idX;
	float y = TILESIZE * idY;
	_musicAngel->init(x, y);
	_vEnemy.push_back(_musicAngel);
}

void dungeonScene::setCow(int idX, int idY)
{
	Cow* cow;
	cow = new Cow;
	float x = TILESIZE * idX;
	float y = TILESIZE * idY;
	x += 50;
	y -= 15;
	cow->init(x, y);
	_vEnemy.push_back(cow);
}

void dungeonScene::setBoss()
{
	_boss = new Boss2;
	_boss->init();
	_vEnemy.push_back(_boss);
}

void dungeonScene::nextTest()
{
	//if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && _mapValue[_dungeonNum] == "T")
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < _vDoor.size(); i++)
		{
			if (PtInRect(&_vDoor[i].rc, getMemDCPoint()))
			{
				string str = "������";
				char temp[128];
				str += itoa(_route[i], temp, 10);
				save();
				SCENEMANAGER->changeScene(str);
			}
		}
	}
}

void dungeonScene::load()
{
	vector<string> vStr = TXTDATA->txtLoad("infoDungeon.txt");
	if (vStr.size() != 0)
	{
		_randNum = atoi(vStr[0].c_str());
		for (int i = 0; i < 11; i++)
		{
			_mapValue[i] = vStr[i + 1];
		}
	}
}

void dungeonScene::save()
{
	vector<string> vStr;
	char str[128];
	vStr.push_back(itoa(_randNum, str, 10));
	for (int i = 0; i < 11; i++)
	{
		vStr.push_back(_mapValue[i]);
	}

	TXTDATA->txtSave("infoDungeon.txt", vStr);
}

void dungeonScene::savePlayer()
{
	//int currentHp, maxHp;											 //���� , ��ü ü�� 
	//int armor;														 //����
	//int currentDash, maxDash;										 //��� Ƚ�� 
	//int attackMinDamage, attackMaxDamage, attackPower;			 //�ּ� ~ �ִ� ������ , ���� ()
	//int fixedDamage;												 //���������� 
	//																 // inven
	//int  mainWeapon[2], assistWeapon[2];							 //���� �������� ���� , ���� �����
	//int  accessory[4];												 //�ǽ�縮
	//int  inventory[15];											 //��ü�κ��丮 15ĭ 
	//int  gold;														 //��
	//int  currentExp, maxExp;										 //���� , �ִ� ����ġ  
	//int  currentFullNess, maxFullNess;							 //���� , �ִ� ������ 
	//int  youUsingCount;											 // 1������ ���������� 2������ �����ߤ����� �迭�̶� 0�� 1���� �ްԵ� ;

	//															 //float 
	//float attackSpeed, reloadSpeed;								 //���� �������ӵ� 
	//float evasionPersent, guardPersent;							 //ȸ��Ȯ�� , ����Ȯ��  	
	//float moveMentSpeed;											 //�̵��ӵ� 
	//float criticalPercent, criticalAttackDamage;					 //ũ��Ƽ�� Ȯ�� , ũ��Ƽ�� ������ ������ 
	//float dashDamage, dashSpeed;									 //����Ҷ� ������ , ���ǵ�
	//float punchSpeed;
	//_infoPlayer.currentHp = ;
	//_infoPlayer.maxHp = ;
	//_infoPlayer.armor = ;
	//_infoPlayer.currentDash = ;
	//_infoPlayer.maxDash = ;
	//_infoPlayer.attackMinDamage = ;
	//_infoPlayer.attackMaxDamage = ;
	//_infoPlayer.attackPower = ;
	//_infoPlayer.fixedDamage = ;
	//_infoPlayer.mainWeapon = ;
	//_infoPlayer.assistWeapon = ;
	//_infoPlayer.accessory = ;
	//_infoPlayer.inventory = ;
	//_infoPlayer.g
}
void dungeonScene::loadPlayer()
{

}

void dungeonScene::setDoor()
{
	for (int i = 0; i < _vDoor.size(); i++)
	{
		_vDoor[i].state = DOOR_OPEN;

		if (_vDoor[i].dir == DOOR_RIGHT)
		{
			_vDoor[i].frameX = 3, _vDoor[i].frameY = 0;
		}
		else
		{
			_vDoor[i].frameX = _vDoor[i].frameY = 0;
		}
	}
}

void dungeonScene::doorRender()
{
	for (int i = 0; i < _vDoor.size(); i++)
	{
		_vDoor[i].count++;
		if (!(_vDoor[i].count % 10))
		{
			if (_vDoor[i].state == DOOR_OPEN)
			{
				if (_vDoor[i].dir == DOOR_RIGHT)
				{
					if (_vDoor[i].frameY == 5)
						_vDoor[i].state = DOOR_IDLE;
					else
						_vDoor[i].frameY++;
				}
				if (_vDoor[i].dir == DOOR_LEFT)
				{
					if (_vDoor[i].frameY == 5)
						_vDoor[i].state = DOOR_IDLE;
					else
						_vDoor[i].frameY++;
				}
				if (_vDoor[i].dir == DOOR_UPDOWN)
				{
					if (_vDoor[i].frameX == 5)
						_vDoor[i].state = DOOR_IDLE;
					else
						_vDoor[i].frameX++;
				}
			}
			else if (_vDoor[i].state == DOOR_IDLE)
			{
				if (_vDoor[i].dir == DOOR_RIGHT)
				{
					if (_vDoor[i].frameX == 3 && _vDoor[i].frameY == 5)
						_vDoor[i].frameX = 2, _vDoor[i].frameY = 0;
					else if (_vDoor[i].frameX == 2 && _vDoor[i].frameY == 5)
						_vDoor[i].frameX = 1, _vDoor[i].frameY = 0;
					else if (_vDoor[i].frameX == 1 && _vDoor[i].frameY == 5)
						_vDoor[i].frameX = 3, _vDoor[i].frameY = 5;
					else
						_vDoor[i].frameY++;
				}
				else if (_vDoor[i].dir == DOOR_LEFT)
				{
					if (_vDoor[i].frameX == 0 && _vDoor[i].frameY == 5)
						_vDoor[i].frameX = 1, _vDoor[i].frameY = 0;
					else if (_vDoor[i].frameX == 1 && _vDoor[i].frameY == 5)
						_vDoor[i].frameX = 2, _vDoor[i].frameY = 0;
					else if (_vDoor[i].frameX == 2 && _vDoor[i].frameY == 5)
						_vDoor[i].frameX = 1, _vDoor[i].frameY = 5;
					else
						_vDoor[i].frameY++;
				}
				else if (_vDoor[i].dir == DOOR_UPDOWN)
				{
					if (_vDoor[i].frameY == 0 && _vDoor[i].frameX == 5)
						_vDoor[i].frameY = 1, _vDoor[i].frameX = 0;
					else if (_vDoor[i].frameY == 1 && _vDoor[i].frameX == 5)
						_vDoor[i].frameY = 2, _vDoor[i].frameX = 0;
					else if (_vDoor[i].frameY == 2 && _vDoor[i].frameX == 5)
						_vDoor[i].frameY = 1, _vDoor[i].frameX = 5;
					else
						_vDoor[i].frameX++;
				}
			}
			else if (_vDoor[i].state == DOOR_CLOSE)
			{
				if (_vDoor[i].dir == DOOR_RIGHT)
				{
					if (_vDoor[i].frameY < _vDoor[i].img->getMaxFrameY())
						_vDoor[i].frameY++;
				}
				if (_vDoor[i].dir == DOOR_LEFT)
				{
					if (_vDoor[i].frameY < _vDoor[i].img->getMaxFrameY())
						_vDoor[i].frameY++;
				}
				if (_vDoor[i].dir == DOOR_UPDOWN)
				{
					if (_vDoor[i].frameX < _vDoor[i].img->getMaxFrameX())
						_vDoor[i].frameX++;
				}
			}
		}
		_vDoor[i].img->frameRender(DC, _vDoor[i].rc.left, _vDoor[i].rc.top, _vDoor[i].frameX, _vDoor[i].frameY);
		if (_mapValue[_dungeonNum] == "T" && _vDoor[i].state != DOOR_CLOSE)
		{
			if (_vDoor[i].dir == DOOR_RIGHT)
			{
				if (_vDoor[i].frameX == 1 && _vDoor[i].frameY == 5)
				{
					_vDoor[i].state = DOOR_CLOSE;
					_vDoor[i].frameX = 0, _vDoor[i].frameY = 0;
				}
			}
			if (_vDoor[i].dir == DOOR_LEFT)
			{
				if (_vDoor[i].frameX == 2 && _vDoor[i].frameY == 5)
				{
					_vDoor[i].state = DOOR_CLOSE;
					_vDoor[i].frameX = 3, _vDoor[i].frameY = 0;
				}
			}
			if (_vDoor[i].dir == DOOR_UPDOWN)
			{
				if (_vDoor[i].frameY == 2 && _vDoor[i].frameX == 5)
				{
					_vDoor[i].state = DOOR_CLOSE;
					_vDoor[i].frameY = 3, _vDoor[i].frameX = 0;
				}
			}
		}
	}
}

void dungeonScene::portalRender()
{
	for (int i = 0; i < _vPortal.size(); i++)
	{
		_vPortal[i].img->frameRender(DC, _vPortal[i].x, _vPortal[i].y, _vPortal[i].frameX, _vPortal[i].frameY);
		_vPortal[i].count++;
		if (!(_vPortal[i].count % 5))
		{

			if (_vPortal[i].frameY == 0)
			{
				if (_vPortal[i].frameX == 0) _vPortal[i].frameY = 1;
				else _vPortal[i].frameX--;
			}
			else if (!(_vPortal[i].count % 10))
			{
				_vPortal[i].count = 0;
				if (_vPortal[i].frameX >= _vPortal[i].img->getMaxFrameX())
					_vPortal[i].frameX = 0;
				else
					_vPortal[i].frameX++;
			}
		}
	}
}


//�Ѿ� ���� �Լ�
//��ǥ���� �Ѿ�
void dungeonScene::MusicAngelBulletFire()
{
	if (!(_count % 200))
	{
		for (int i = 0; i < 12; i++)
		{
			float angle = (PI2 / 12)*i;
			_enemyBullet->bulletFire("bansheeNormalBullet", _musicAngel->getX(), _musicAngel->getY(), angle, 5.0f, 500, true);
		}
		_count = 0;
	}
}

//�����Ѿ�
void dungeonScene::BossBulletFire()
{
	//==========================================================
	//						���� �Ѿ�
	//==========================================================
	//�� �Ѿ� ���� �ϰ���.
	//�� �Ѿ��� �Ӹ��� ������ �������� ��
	static float angle = 0;
	static bool	isCheck = false;		// �̰� ������ �ޱ۰� + OR - ��Ŵ

	if (_boss->getHeadX() < getMemDCPoint().x) isCheck = true;   // ��� ���콺 ��ǥ�� �÷��̾� X ��ǥ�� �ٲٸ� �˴ϴ�.
	else isCheck = false;

	//==========================================================
	//					���� ���� ������
	//==========================================================

	if (_boss->getLeftDirection() == LEFT_LASER_ON)
	{
		_enemyBullet->bulletFire("bossLaser", _boss->getLeftX() + 800, _boss->getLeftY(), 0, 0.0f, 1000, true, HEIGHT);
		_boss->setLeftDirection(LEFT_LASER_OFF);
	}

	//==========================================================
	//					���� ������ ������
	//==========================================================

	if (_boss->getRightDirection() == RIGHT_LASER_ON)
	{
		_enemyBullet->bulletFire("bossRLaser", _boss->getRightX() - 850, _boss->getRightY(), 0, 0.0f, 1000, true, HEIGHT); //������ ������
		_boss->setRightDirection(RIGHT_LASER_OFF);
	}

	if (!_boss->isAttack()) return;

	//���
	if (!isCheck) angle += 0.02; //�Ѿ� ���ư��� �ӵ� ����
	else angle -= 0.02;

	if (!(_count % 7)) //�Ѿ� ������ �ӵ� ����
	{
		for (int i = 0; i < 4; i++)
		{
			angle += (i * PI / 2);
			//float angle = i * PI / 2;
			_enemyBullet->bulletFire("bossBullet", _boss->getHeadX() + 50, _boss->getHeadY() + 120, angle, 9.0f, 800, true); //9.0f�� ���� angle, count �� �����ؼ� �Ѿ� ���� ����
		}
		_count = 0;
	}
}

	void dungeonScene::bigbatbulletFire()
	{
		_count2++;
		if (_bigbat->getcount() % 15 == 0 && _bigbat->getcount() > 100)
		{
			for (int i = 0; i < 3; i++)
			{
				float angle = -(PI2 / 9) * i;
				_enemyBullet->bulletFire("fatherBatBullet2", _bigbat->getX() + 50, _bigbat->getY() + 10, angle, 5.0f, 500);
			}
		}

		if (_count2 > 200)
		{
			_count2 = 0;
			_bulletMove = false;
		}

	}


	void dungeonScene::bigRadbatbulletFire()
	{
		_count3++;
		if (_count3 % 150 == 0)
		{
			for (int i = 0; i < 20; i++)
			{
				float angle2 = PI2 / 20 * i;
				float bulletX = _bigRedBat->getX() + 150;
				float bulletY = _bigRedBat->getY() + 50;
				_bigRadBatBullet[i]->bulletFire("fatherBatBullet2", bulletX + cosf(angle2) * 150, _bigRedBat->getY() + -sinf(angle2) * 150, angle2, 5.0f, 500);

			}
		}

		//if (_count3 > 200) _count3 = 0;
	}