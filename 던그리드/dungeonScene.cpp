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
	//KEYANIMANAGER->update();
}

void dungeonScene::render(void)
{
	RectangleMake(getMemDC(), 1820, 980, 100, 100);

	for (int i = (CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2) / 96; i < (CAMERAMANAGER->getCameraCenter().y + WINSIZEY / 2) / 96 + 1; ++i)
	{
		for (int j = (CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2) / 96; j < (CAMERAMANAGER->getCameraCenter().x + WINSIZEX / 2) / 96 + 1; ++j)
		{
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

	for (int i = 0; i < _door.size(); i++)
	{
		char str[128];
		sprintf_s(str, "num : %d", _dungeonNum);
		TextOut(DC, 100, 100, str, strlen(str));
		Rectangle(DC, _door[i].rc.left, _door[i].rc.top, _door[i].rc.right, _door[i].rc.bottom);
	}

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
	_count++;
	_enemyBullet->render();
}



void dungeonScene::mapload()
{
	HANDLE   file;
	DWORD   load;
	ZeroMemory(&_tiles, sizeof(tagTile) * TILEX * TILEY);

	file = CreateFile(_mapName.c_str(), GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &load, NULL);

	CloseHandle(file);

	_enemyBullet = new Bullet;
	_enemyBullet->init(3000);
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
	if (idx == 6) //이상...
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

//몬스터 생성 함수
//개뼈
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
//큰칼뼈
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
//활쟁이
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
//작보박
void dungeonScene::setBat(int idX, int idY)
{
	Bat* bat;
	bat = new Bat;
	float x = TILESIZE * idX;
	float y = TILESIZE * idY;
	bat->init(x, y);
	_vEnemy.push_back(bat);
}
//작빨박
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
	BigBat* bigBat;
	bigBat = new BigBat;
	float x = TILESIZE * idX;
	float y = TILESIZE * idY;
	bigBat->init(x, y);
	_vEnemy.push_back(bigBat);
}

void dungeonScene::setBigRedBat(int idX, int idY)
{
	BigRedBat* bigRedBat;
	bigRedBat = new BigRedBat;
	float x = TILESIZE * idX;
	float y = TILESIZE * idY;
	bigRedBat->init(x, y);
	_vEnemy.push_back(bigRedBat);
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
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && _mapValue[_dungeonNum] == "T")
	//if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < _door.size(); i++)
		{
			if (PtInRect(&_door[i].rc, getMemDCPoint()))
			{
				string str = "던전맵";
				char temp[128];
				str += itoa(_route[i],temp,10);
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
	vStr.push_back(itoa(_randNum,str,10));
	for (int i = 0; i < 11; i++)
	{
		vStr.push_back(_mapValue[i]);
	}

	TXTDATA->txtSave("infoDungeon.txt", vStr);
}

//총알 생성 함수
//음표요정 총알
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

//보스 총알
void dungeonScene::BossBulletFire()
{
	//==========================================================
	//						보스 총알
	//==========================================================
	//입 총알 먼저 하겠음.
	//입 총알은 머리통 열리는 순간에만 함
	static float angle = 0;
	static bool	isCheck = false;		// 이거 가지고 앵글값 + OR - 시킴

	if (_boss->getHeadX() < getMemDCPoint().x) isCheck = true;   // 요기 마우스 좌표를 플레이어 X 좌표로 바꾸면 됩니다.
	else isCheck = false;

	if (!_boss->isAttack()) return;

	//요기
	if (!isCheck) angle += 0.02; //총알 돌아가는 속도 조절
	else angle -= 0.02;
	
	if (!(_count % 7)) //총알 나가는 속도 조절
	{
		for (int i = 0; i < 4; i++)
		{
			 angle += (i * PI / 2);
			//float angle = i * PI / 2;
			_enemyBullet->bulletFire("bossBullet", _boss->getHeadX() + 50, _boss->getHeadY() + 120, angle, 9.0f, 800, true); //9.0f랑 위에 angle, count 로 조절해서 총알 조절 가능
		}
		_count = 0;
	}

	//==========================================================
	//					보스 왼쪽 레이져
	//==========================================================
	
	if (_boss->getLeftDirection() == LEFT_LASER_ON)
	{
		_enemyBullet->bulletFire("bossLaser", _boss->getLeftX() + 800, _boss->getLeftY(), 0, 0.0f, 1000, true, HEIGHT);
		_boss->setLeftDirection(LEFT_IDLE);
	}

	if (_boss->getRightDirection() == RIGHT_LASER_ON)
	{
		_enemyBullet->bulletFire("bossRLaser", _boss->getRightX() - 850, _boss->getRightY(), 0, 0.0f, 1000, true, HEIGHT); //오른손 레이져
		_boss->setRightDirection(RIGHT_IDLE);
	}
}
