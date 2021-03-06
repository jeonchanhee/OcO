#include "stdafx.h"
#include "townScene.h"
#include "Player.h"
#include "itemManager.h"


HRESULT townScene::init()
{
	SOUNDMANAGER->play("town");
	_player = SCENEMANAGER->getPlayerAddressLink();
	//�Ƚ�  =\=======

	_pixel = IMAGEMANAGER->addImage("pixelTown", 7680, 2400);
	HPEN pen, oldPen;
	pen = CreatePen(BS_SOLID, 20, RGB(0, 255, 0));
	oldPen = (HPEN)SelectObject(_pixel->getMemDC(), pen);

	LineMake(_pixel->getMemDC(), 1050, 1170, 1800, 1920);
	LineMake(_pixel->getMemDC(), 2220, 1920, 2980, 1170);
	LineMake(_pixel->getMemDC(), 4420, 1165, 5170, 1910);
	LineMake(_pixel->getMemDC(), 5580, 1925, 6336, 1175);

	SelectObject(_pixel->getMemDC(), oldPen);
	//����  ===== 
	DeleteObject(oldPen);
	DeleteObject(pen);

	_trainer = IMAGEMANAGER->findImage("NƮ���̳�");
	_shop = IMAGEMANAGER->findImage("N������");
	_suckImg = IMAGEMANAGER->findImage("suck");
	int trainer[] = { 0,1,2,3,4,5 };
	int shop[] = { 15,16,17,18,19,20 };
	int suck[] = { 0,1,2,3,4,5,6,7,8,26,27,28,29,30 };
	int suck2[] = { 31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51 };
	KEYANIMANAGER->addArrayFrameAnimation("trainer", "NƮ���̳�", trainer, 6, 5, true);
	KEYANIMANAGER->addArrayFrameAnimation("shop", "N������", shop, 6, 5, true);
	KEYANIMANAGER->addArrayFrameAnimation("suck", "suck", suck, 14, 20, false, suckDungeon,this);
	KEYANIMANAGER->addArrayFrameAnimation("suck2", "suck", suck2, 21, 20, false, moveDungeon,this);
	_training = KEYANIMANAGER->findAnimation("trainer");
	_shopping = KEYANIMANAGER->findAnimation("shop");
	_suck = KEYANIMANAGER->findAnimation("suck");
	_training->start();
	_shopping->start();
	//_suck->start();
	
	_ui[0] =false;
	_ui[1] =false;
	_ui[2] =false;
	_canMove = true;
	_sucking = false;
	_mapName = "map/townmap(80x25).map";
	_temp = 80;
	_tileX = 80, _tileY = 25;
	_dungeonNum = 11;
	mapload();
	setMinimap();
	_floorNum = 1;
	_count = 0;

	for (int i = 0; i < 6; i++)
		_trainStat[i] = 0;

	resetShop();


	return S_OK;
}

void townScene::resetShop()
{
	//2~33
	int rand;
	for (int i = 0; i < 5; i++)
	{
		_itemNum[i] = 0;
		while (1)
		{
			rand = RND->getFromIntTo(2, 33);
			if (_itemNum[0] != rand && _itemNum[1] != rand && _itemNum[2] != rand && _itemNum[3] != rand && _itemNum[4] != rand)
			{
				_itemNum[i] = rand;
				break;
			}
		}
	}
}

void townScene::release()
{
}

void townScene::update()
{
	//if(_canMove==true)
	_player->update();
	_minimap->setPlayerXY(((400*_player->getPlayerX()) / (_tileX * TILESIZE)), ((200*_player->getPlayerY()) / (_tileY * TILESIZE)));
	dungeonGo();
	if (_start==2)
	{
		_randMap = new RandomDungeon1;
		_randMap->init();
	}
}

void townScene::render()
{
	//if(KEYMANAGER->isToggleKey(VK_F3))
	
	
	IMAGEMANAGER->findImage("BackSky")->render(DC,CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2, CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2);
	IMAGEMANAGER->findImage("BackMountain")->render(DC, CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2, CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2, (CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2)/12,0,WINSIZEX,WINSIZEY);
	IMAGEMANAGER->findImage("BackForest")->render(DC, CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2, WINSIZEY*5/6+50, (CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2)/3.5,0,WINSIZEX,WINSIZEY);
	//IMAGEMANAGER->findImage("BackSky")->render(DC,0,0);
	mapRender();
	IMAGEMANAGER->findImage("floor1")->render(DC, -23 * 96, 12 * 96);
	IMAGEMANAGER->findImage("floor2")->render(DC, 22 * 96, 12 * 96);
	IMAGEMANAGER->findImage("floor1")->render(DC, 57 * 96, 12 * 96);
	IMAGEMANAGER->findImage("floor0")->render(DC, 30 * 96, 17 * 96);
	IMAGEMANAGER->findImage("floor0")->render(DC, 36 * 96, 15 * 96);
	IMAGEMANAGER->findImage("school")->render(DC, 1 * 96, 16* 96+24);
	IMAGEMANAGER->findImage("shop")->render(DC, 67 * 96-50, 4* 96-24);
	_trainer->aniRender(DC, 10 * 96, 20 * 96, _training);
	_shop->aniRender(DC, 72 * 96-20, 11* 96+10, _shopping);

	
	_minimap->render();
	dungeonGo();
	NPC();
	if (_ui[0] == true)
	{
		//RECT rc = RectMake(50, 220, 100, 100);
		//IMAGEMANAGER->findImage("inven")->render(UIDC, WINSIZEX - IMAGEMANAGER->findImage("inven")->getWidth(), 0);

		//_im->getItem()[0]->getItem().image[0]->render(UIDC, rc.left, rc.top);
	}
	if (_ui[1] == true)
	{
		shop();
	}
	if (_ui[2] == true)
	{
		training();
		_trainStat[0] = _player->getLv() * 2 - _trainStat[1] - _trainStat[2] - _trainStat[3] - _trainStat[4] - _trainStat[5];
	}
}

void townScene::mapload()
{
	HANDLE file;
	DWORD load;

	ZeroMemory(&_tiles, sizeof(tagTile) * TILEX * TILEY);

	file = CreateFile(_mapName.c_str(), GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &load, NULL);


	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].terrain == TOWN_GROUND) continue;
		if (_tiles[i].object == OBJ_DIAGONAL) continue;
		if (_tiles[i].objFrameX == 17 && _tiles[i].objFrameY == 1)  _tiles[i].terrain = TOWN_GROUND;
		if (_tiles[i].objFrameX == 16 && _tiles[i].objFrameY == 1)  _tiles[i].terrain = TOWN_GROUND;
		if (_tiles[i].objFrameX == 12 && _tiles[i].objFrameY == 25) _tiles[i].terrain = TOWN_GROUND;
		if (_tiles[i].objFrameX == 19 && _tiles[i].objFrameY == 18) _tiles[i].terrain = TOWN_GROUND;
		if (_tiles[i].objFrameX == 12 && _tiles[i].objFrameY == 25) _tiles[i].terrain = TOWN_GROUND;
		if (_tiles[i].objFrameX == 4  && _tiles[i].objFrameY == 0) _tiles[i].terrain = TOWN_GROUND;
		if (_tiles[i].objFrameX == 10 && _tiles[i].objFrameY == 1) _tiles[i].terrain = TOWN_GROUND;
		if (_tiles[i].objFrameX == 15 && _tiles[i].objFrameY == 18) _tiles[i].terrain = TOWN_GROUND;
		if (_tiles[i].objFrameX == 19 && _tiles[i].objFrameY == 1) _tiles[i].terrain = TOWN_GROUND;
		if (_tiles[i].objFrameX == 15 && _tiles[i].objFrameY == 1) _tiles[i].terrain = TOWN_GROUND;
		if (_tiles[i].objFrameX == 10 && _tiles[i].objFrameY == 25) _tiles[i].terrain = TOWN_GROUND;
		if (_tiles[i].objFrameX == 11 && _tiles[i].objFrameY == 25) _tiles[i].terrain = TOWN_GROUND;
		if (_tiles[i].objFrameX == 12 && _tiles[i].objFrameY == 0) _tiles[i].terrain = TOWN_GROUND;
		if (_tiles[i].objFrameX == 18 && _tiles[i].objFrameY == 1) _tiles[i].terrain = TOWN_GROUND;
		//�밢
		if (_tiles[i].objFrameX == 7 && _tiles[i].objFrameY == 17) _tiles[i].object = OBJ_DIAGONAL;
		if (_tiles[i].objFrameX == 11 && _tiles[i].objFrameY == 0) _tiles[i].object = OBJ_DIAGONAL;
	}
	CloseHandle(file);

	CAMERAMANAGER->setCameraCenter(PointMake(0, 0));
}

void townScene::setMinimap()
{
	_minimap = new minimap;
	_minimap->init(false);

	image* tempImg;
	tempImg = IMAGEMANAGER->addImage("��Ǫ", _tileX*TILESIZE, _tileY * TILESIZE);
	PatBlt(tempImg->getMemDC(), 0, 0, _tileX * TILESIZE, _tileY * TILESIZE, BLACKNESS);

	for (int i = 0; i < _tileY; i++)
	{
		for (int j = 0; j < _tileX; j++)
		{
			if (_tiles[i * _temp + j].object == OBJ_NONE) continue;
			IMAGEMANAGER->frameRender("map", tempImg->getMemDC(), _tiles[i * _temp + j].rc.left, _tiles[i * _temp + j].rc.top, _tiles[i * _temp + j].objFrameX, _tiles[i * _temp + j].objFrameY);
		}
	}
	_minimap->setMinimap(tempImg->getMemDC());
	_minimap->setPlayerXY(((400*_player->getPlayerX()) / (_tileX * TILESIZE)), ((200*_player->getPlayerY()) / (_tileY * TILESIZE)));
	_minimap->setNPCXY(0, ((400 * (10 * 96)) / (_tileX*TILESIZE)), ((200 * (20 * 96)) / (_tileY*TILESIZE)));
	_minimap->setNPCXY(1, ((400 * (72 * 96 - 20)) / (_tileX*TILESIZE)), ((200 * (11 * 96 + 10)) / (_tileY*TILESIZE)));
}
void townScene::mapRender()
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
		Rectangle(DC,_player->getRc().left, _player->getRc().top, _player->getRc().right, _player->getRc().bottom);
	}
}

void townScene::NPC()
{
	RECT rc;
	if (IntersectRect(&rc, &RectMake(10 * 96, 20 * 96, _trainer->getFrameWidth(), _trainer->getFrameHeight()), &_player->getRc()))
	{
		IMAGEMANAGER->findImage("keyIcon")->frameRender(DC, _player->getPlayerX()-40, _player->getPlayerY()-150,2,0);
		if (KEYMANAGER->isOnceKeyDown('F'))
		{
			if (_ui[2] == true)
			{
				_ui[2] = false;
				_canMove = true;
			}
			else
			{
				_ui[2] = true;
				_canMove = false;
			}
		}
	}
	if (IntersectRect(&rc, &RectMake(72 * 96 - 20, 11 * 96 + 10, _shop->getFrameWidth(), _shop->getFrameHeight()), &_player->getRc()))
	{
		IMAGEMANAGER->findImage("keyIcon")->frameRender(DC, _player->getPlayerX()-40, _player->getPlayerY()-150, 2, 0);
		if (KEYMANAGER->isOnceKeyDown('F'))
		{
			if (_ui[1] == false)
			{
				_ui[1] = true;
				_player->getInven()->setOnInven(true);
				_canMove = false;
			}
			else
			{
				_ui[1] = false;
				_player->getInven()->setOnInven(false);
				_canMove = true;
			}
		}
	}
}

void townScene::training()
{
	IMAGEMANAGER->findImage("gray")->alphaRender(DC, CAMERAMANAGER->getCameraCenter().x - WINSIZEX/2, CAMERAMANAGER->getCameraCenter().y - WINSIZEY/2, 450);
	IMAGEMANAGER->findImage("training")->render(UIDC, 0, 0);
	for (int j = 0; j < 15; j += 3)
	{
		for (int i = 0; i < 3; i++)
			IMAGEMANAGER->findImage("trainI")->frameRender(UIDC, 110 + (i * 72) + (j * 124), 720, j, i);
	}
	for (int i = 0; i < 5; i++)
		IMAGEMANAGER->findImage("trainB")->frameRender(UIDC, 165 + (i * 371), 810, i, 1);
	RECT rc[6];
	rc[0] = RectMake(1764, 50, 120, 115);
	rc[1] = RectMake( 174, 822, 90, 90);
	rc[2] = RectMake( 545, 822, 90, 90);
	rc[3] = RectMake( 916, 822, 90, 90);
	rc[4] = RectMake( 1287, 822, 90, 90);
	rc[5] = RectMake( 1658, 822, 90, 90);
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(UIDC, rc[0].left, rc[0].top, rc[0].right, rc[0].bottom);
	}

	char str[128];
	HFONT font, oldFont;
	font = CreateFont(50, 0, 0, 0, 100, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("�Ҿ߹ٸ�9"));
	oldFont = (HFONT)SelectObject(UIDC, font);
	SetTextColor(UIDC, RGB(255, 255, 255));
	SetBkMode(UIDC, TRANSPARENT);

	for (int i = 1; i < 6; i++)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && PtInRect(&rc[i], _ptMouse) && _trainStat[0] > 0)
		{
			_trainStat[0]--;
			_trainStat[i]++;
		}
		sprintf(str, "%d", _trainStat[i]);
		TextOut(UIDC, rc[i].left+35, rc[i].top-300, str, strlen(str));
	}
	sprintf(str, "%d", _trainStat[0]);
	TextOut(UIDC, 1815, 975, str, strlen(str));

	SelectObject(UIDC, oldFont);
	DeleteObject(font);

	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		_trainStat[1] = _trainStat[2] = _trainStat[3] = _trainStat[4] = _trainStat[5] = 0;
		_trainStat[0] = _player->getLv()*2 - _trainStat[1] - _trainStat[2] - _trainStat[3] - _trainStat[4] - _trainStat[5];
	}
}

void townScene::shop()
{
	char str[128];
	RECT rc[5], rc1[5], rc2[5], rc3[5];
	IMAGEMANAGER->findImage("shopUI")->render(UIDC, 0, 0);
	for (int i = 0; i < 5; i++)
	{
		rc1[i] = RectMake(165, 180 + 170 * i, 493,126);
		IMAGEMANAGER->findImage("slot")->render(UIDC, 165, 180 + 170 * i);
	}
	if(KEYMANAGER->isToggleKey(VK_TAB))
	{
		for (int i = 0; i < 5; i++)
			Rectangle(UIDC, rc1[i].left, rc1[i].top, rc1[i].right, rc1[i].bottom);
	}

	HFONT font, oldFont;
	font = CreateFont(40, 0, 0, 0, 100, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("�Ҿ߹ٸ�9"));
	oldFont = (HFONT)SelectObject(UIDC, font);
	SetTextColor(UIDC, RGB(255, 255, 255));
	SetBkMode(UIDC, TRANSPARENT);
	for (int i = 0; i < 5; i++)
	{
		rc[i] = RectMake(50, 220 + 170 * i, 100, 100);
		rc2[i] = RectMake(200, 200 + 170 * i, 100, 100);
		rc3[i] = RectMake(500, 255 + 170 * i, 100, 100);

		if (_itemNum[i] != 0)
		{
			_im->getItem()[_itemNum[i]]->getItem().image[0]->render(UIDC, rc[i].left, rc[i].top);

			DrawText(UIDC, _im->getItem()[_itemNum[i]]->getItem().name, strlen(_im->getItem()[_itemNum[i]]->getItem().name), &rc2[i], DT_VCENTER);
			DrawText(UIDC, itoa(_im->getItem()[_itemNum[i]]->getItem().price, str, 10), strlen(itoa(_im->getItem()[_itemNum[i]]->getItem().price, str, 10)), &rc3[i], DT_VCENTER);
		}
		else
			IMAGEMANAGER->findImage("thank")->render(UIDC, rc2[i].left, rc2[i].top);
	}

	SelectObject(UIDC, oldFont);
	DeleteObject(font);
	for (int i = 0; i < 5; i++)
	{
		if (PtInRect(&rc1[i], _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_RBUTTON) && _itemNum[i] != 0&&_player->getInven()->getItem().size() < INVENSIZE&&_im->getItem()[_itemNum[i]]->getItem().price<= _player->getInven()->getGold())
		{
			_player->getInven()->setGold(_player->getInven()->getGold() - _im->getItem()[_itemNum[i]]->getItem().price);
			_player->getInven()->buyItem(_itemNum[i]);
			_itemNum[i] = 0;
		}
	}
}

void townScene::dungeonGo()
{
	RECT temp;
	RECT rc = RectMake( 2750, 2015, 2000, 30);
	if (_sucking == false)
	{
		if (IntersectRect(&temp, &_player->getRc(), &rc))
		{
			int starttime = TIMEMANAGER->getWorldTime();
			//_suckImg->render(DC, _player->getRc().left, rc.top - 100);
			_suck->start();
			SOUNDMANAGER->play("dungeonIn");
			_sucking = true;
			_canMove = false;
			if (_player->getIsLeftAttack() == true)
				_player->leftStop();
			else
				_player->rightStop();
		}
	}
	else
		_suckImg->aniRender(DC, _player->getRc().left-350,1510,_suck);
	//Rectangle(DC, rc.left, rc.top, rc.right, rc.bottom);
}


void townScene::suckDungeon(void* object)
{
	townScene* T = (townScene*)object;
	//T->resetShop();
	T->_suck->stop();
	T->_suck = KEYANIMANAGER->findAnimation("suck2");
	T->_suck->start();
	_start = 1;
}

 void townScene::moveDungeon(void* object)
{
	 townScene* T = (townScene*)object;
	 T->_sucking = false;
	 _canMove = true;
	 //T->_suck->stop();
	 //T->_training->stop();
	 //T->_shopping->stop();
	// KEYANIMANAGER->deleteAll();
	 //SCENEMANAGER->changeScene("������1");
	/* T->_randMap = new RandomDungeon1;
	 T->_randMap->init();*/
	 _start = 2;
	 T->_player->setPlayerX(650);
	 T->_player->setPlayerY(770);
}

townScene::townScene()
{
}


townScene::~townScene()
{
}
