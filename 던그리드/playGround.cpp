#include "stdafx.h"
#include "playGround.h"


playGround::playGround(){}
playGround::~playGround(){}


HRESULT playGround::init(void)	
{
	vector<string> vStr;
	vStr.resize(4);
	vStr = { "F","F","F","F" };
	TXTDATA->txtSave("random.txt", vStr);
	mode = ����2;		//������ �����ϴ� �κ����� �̳ѿ� �߰��ϰ� �����ؼ� ����ϱ�!!

	gameNode::init(true);
	Image_init();
	Sound_init();
	
	if (mode == ����)
	{
		_mapTool = new MapTool;
		_mapTool->init();
	}
	_player = new Player;
	_player->init();
	_im = new itemManager;
	_im->init();

	_town = new townScene;
	_title = new titleScene;
	_town->setImLink(_im);
	_title->setImLink(_im);

	SCENEMANAGER->setPlayerAddressLink(_player);

	SCENEMANAGER->addScene("Ÿ��Ʋ", _title);
	SCENEMANAGER->addScene("����2", new dungeon2Scene);
	SCENEMANAGER->addScene("����", new Dialog);
	SCENEMANAGER->addScene("�����۾�", new itemManager);
	SCENEMANAGER->addScene("��Ʈ��", new introScene);
	SCENEMANAGER->addScene("�ʼ���", new mapSelectScene);
	SCENEMANAGER->addScene("����3", new dungeon3Scene);
	SCENEMANAGER->addScene("����4", new dungeon4Scene);
	SCENEMANAGER->addScene("����5", new dungeon5Scene);
	SCENEMANAGER->addScene("����6", new dungeon6Scene);
	SCENEMANAGER->addScene("����7", new dungeon7Scene);
	SCENEMANAGER->addScene("����8", new dungeon8Scene);
	SCENEMANAGER->addScene("����",_town);
	SCENEMANAGER->addScene("����", new weaponScene);
	SCENEMANAGER->addScene("Ǫ��", new foodScene);
	SCENEMANAGER->addScene("����", new bossScene);

//	
	//_randomScene1 = new RandomDungeon1;
	//SCENEMANAGER->addScene("������1", _randomScene1);
	//_randomScene1->init();
//	_randomScene1->init();
//
//	
//	_randomScene1->init();
//
	switch (mode)
	{
	case ����:
		break;
	case Ÿ��Ʋ:
		SCENEMANAGER->changeScene("Ÿ��Ʋ");
		break;
	case ���̾�α�:
		SCENEMANAGER->changeScene("����");
		break;
	case ����:
		SCENEMANAGER->changeScene("��");
		break;
	case �÷��̾�:
		break;
	case ������:
		SCENEMANAGER->changeScene("�����۾�");
		break;
	
	case ��Ʈ��:
		SCENEMANAGER->changeScene("��Ʈ��");
		break;
	case ����2:
		SCENEMANAGER->changeScene("����2");
		break;
	case ����3:
		SCENEMANAGER->changeScene("����3");
		break;
	case ����4:
		SCENEMANAGER->changeScene("����4");
		break;
	case ����5:
		SCENEMANAGER->changeScene("����5");
		break;
	case ����6:
		SCENEMANAGER->changeScene("����6");
		break;
	case ����7:
		SCENEMANAGER->changeScene("����7");
		break;
	case ����8:
		SCENEMANAGER->changeScene("����8");
		break;
	case ����:
		SCENEMANAGER->changeScene("����");
		break;
	case Ǫ��:
		SCENEMANAGER->changeScene("Ǫ��");
		break;
	case ������1:
		//SCENEMANAGER->changeScene("������1");
		//_randomScene1->init();
		break;

		break;	
	case ����:
		SCENEMANAGER->changeScene("����");
		break;
	case ����:
		SCENEMANAGER->changeScene("����");
		break;
	case �ʼ���:
		SCENEMANAGER->changeScene("�ʼ���");
		break;
	case ��Ÿ�߰��ϼ�:
		break;
	default:
		break;
	}
	
	return S_OK;
}

void playGround::release(void)	
{
	gameNode::release();

	
}

void playGround::update(void)	
{
	gameNode::update();
	if(mode == ����) _mapTool->update();
	//_player->update();
	SCENEMANAGER->update();
	EFFECTMANAGER->update();
	KEYANIMANAGER->update();

	
	/*if (KEYMANAGER->isStayKeyDown('D') && CAMERAMANAGER->getCameraRc2().right<BACKGROUNDSIZEX) CAMERAMANAGER->setCameraX2(CAMERAMANAGER->getCameraX2() + 50);
	if (KEYMANAGER->isStayKeyDown('S') && CAMERAMANAGER->getCameraRc2().bottom<BACKGROUNDSIZEY) CAMERAMANAGER->setCameraY2(CAMERAMANAGER->getCameraY2() + 50);
	if (KEYMANAGER->isStayKeyDown('A') && CAMERAMANAGER->getCameraRc2().left>0) CAMERAMANAGER->setCameraX2(CAMERAMANAGER->getCameraX2() - 50);
	if (KEYMANAGER->isStayKeyDown('W') && CAMERAMANAGER->getCameraRc2().top>0) CAMERAMANAGER->setCameraY2(CAMERAMANAGER->getCameraY2() - 50);*/

	/*if (KEYMANAGER->isStayKeyDown('D') && CAMERAMANAGER->getCameraRc().right<96 * _tileX) CAMERAMANAGER->setCameraX(CAMERAMANAGER->getCameraX() + 50);
	if (KEYMANAGER->isStayKeyDown('S') && CAMERAMANAGER->getCameraRc().bottom<96 * _tileY) CAMERAMANAGER->setCameraY(CAMERAMANAGER->getCameraY() + 50);
	if (KEYMANAGER->isStayKeyDown('A') && CAMERAMANAGER->getCameraRc().left>0) CAMERAMANAGER->setCameraX(CAMERAMANAGER->getCameraX() - 50);
	if (KEYMANAGER->isStayKeyDown('W') && CAMERAMANAGER->getCameraRc().top>0) CAMERAMANAGER->setCameraY(CAMERAMANAGER->getCameraY() - 50);*/

	/*if (KEYMANAGER->isStayKeyDown('D') && CAMERAMANAGER->getCameraRc().right<96 * BACKGROUNDSIZEX) CAMERAMANAGER->setCameraX(CAMERAMANAGER->getCameraX() + 50);
	if (KEYMANAGER->isStayKeyDown('S') && CAMERAMANAGER->getCameraRc().bottom<96 * BACKGROUNDSIZEY) CAMERAMANAGER->setCameraY(CAMERAMANAGER->getCameraY() + 50);
	if (KEYMANAGER->isStayKeyDown('A') && CAMERAMANAGER->getCameraRc().left>0) CAMERAMANAGER->setCameraX(CAMERAMANAGER->getCameraX() - 50);
	if (KEYMANAGER->isStayKeyDown('W') && CAMERAMANAGER->getCameraRc().top>0) CAMERAMANAGER->setCameraY(CAMERAMANAGER->getCameraY() - 50);
*/

	if (mode == ����)
	{
		if (KEYMANAGER->isStayKeyDown('D'))//&& CAMERAMANAGER->getCameraCenter().x+WINSIZEX/2<BACKGROUNDSIZEX)
			CAMERAMANAGER->setCameraCenter(PointMake(CAMERAMANAGER->getCameraCenter().x + 50, CAMERAMANAGER->getCameraCenter().y));
		if (KEYMANAGER->isStayKeyDown('S'))// && CAMERAMANAGER->getCameraCenter().y + WINSIZEY / 2<BACKGROUNDSIZEY)
			CAMERAMANAGER->setCameraCenter(PointMake(CAMERAMANAGER->getCameraCenter().x, CAMERAMANAGER->getCameraCenter().y + 50));
		if (KEYMANAGER->isStayKeyDown('A'))// && CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2>0)
			CAMERAMANAGER->setCameraCenter(PointMake(CAMERAMANAGER->getCameraCenter().x - 50, CAMERAMANAGER->getCameraCenter().y));
		if (KEYMANAGER->isStayKeyDown('W'))//&& CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2>0)
			CAMERAMANAGER->setCameraCenter(PointMake(CAMERAMANAGER->getCameraCenter().x, CAMERAMANAGER->getCameraCenter().y - 50));
	}
	
	//if (CAMERAMANAGER->getCameraX() < 0)						CAMERAMANAGER->setCameraX(0);
	//if (CAMERAMANAGER->getCameraY() < 0)						CAMERAMANAGER->setCameraY(0);
	//if (CAMERAMANAGER->getCameraX() + WINSIZEX > 96 * _tileX)	CAMERAMANAGER->setCameraX(96 * _tileX - WINSIZEX);
	//if (CAMERAMANAGER->getCameraY() + WINSIZEY > 96 * _tileY)	CAMERAMANAGER->setCameraY(96 * _tileY - WINSIZEY);
}

void playGround::render(void)
{
	PatBlt(getMemDC(), CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2, CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2, WINSIZEX, WINSIZEY, WHITENESS);
	PatBlt(CAMERAMANAGER->getCameraDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);

	/////////////////////////////////////////////////////////////////////////////////////////////
	// �� ���δ� �ǵ��� ���ÿ�
	//_mapTool->render();
	switch (mode)
	{
	case ����:
	//	PatBlt(UIDC, 0, 0, BACKGROUNDSIZEX, BACKGROUNDSIZEY, WHITENESS);
		
		
		_mapTool->render();
		if(KEYMANAGER->isToggleKey(VK_TAB))
		{
		
		}
		
		break;
	case Ÿ��Ʋ:
		SCENEMANAGER->render();
		break;
	case ���̾�α�:
		SCENEMANAGER->render();
		break;
	case ����:
		SCENEMANAGER->render();
		break;
	case �÷��̾�:
		_player->render();
		break;
	case ������:
		SCENEMANAGER->render();
		break;
	case ����2: case ����3: case ����4: case ����5: case ����6: case ����7: case ����8:
	case ������1: case ����:  case ����: case Ǫ��:
		SCENEMANAGER->render();
		EFFECTMANAGER->render();
		_player->render();
		break;
	case ����:
		SCENEMANAGER->render();
		EFFECTMANAGER->render();
		//_player->render();
		break;
	case �ʼ���:
		SCENEMANAGER->render();
		break;
	case ��Ÿ�߰��ϼ�:
		break;
	default:
		break;
	}
	

	//SCENEMANAGER->render();

	//char str[128];
	//sprintf_s(str, "%d, %d", CAMERAMANAGER->getCameraCenter().x + WINSIZEX / 2, CAMERAMANAGER->getCameraCenter().y + WINSIZEY / 2);
	//TextOut(UIDC, 100, 100, str, strlen(str));
	//
	//char str2[128];
	//sprintf_s(str2, "%d %d /// %d, %d", _tileX, _tileY, _tileX * 96, _tileY * 96);
	//TextOut(UIDC, 100, 150, str2, strlen(str2));

	// �� �Ʒ��ε� �ǵ��� ���ÿ�
	/////////////////////////////////////////////////////////////////////////////////////////////
	IMAGEMANAGER->render("cursor", UIDC, _ptMouse.x, _ptMouse.y);
	TIMEMANAGER->render(UIDC);

	//if(mode == Ÿ��Ʋ)
		IMAGEMANAGER->findImage("ī�޶�DC")->render(DC, 54,240,CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, 600, 670);

	CAMERAMANAGER->render(this->getBackBuffer());
	this->getBackBuffer()->render(getHDC(), 0, 0, CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2, CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2, WINSIZEX, WINSIZEY);
	//IMAGEMANAGER->render("cursor", getHDC(), _ptMouse.x, _ptMouse.y);

	//�����ȭ�� �� �� ��Ƶд�
	//PatBlt(DC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS); // ī�޶� �Ŵ��� DC -> getMemDC �� �ٲپ����ϴ�.
	
	//============== �� ���δ� �ǵ帮�� ���� ==============
	
	//switch (mode)
	//{
	//case ����:
	//	PatBlt(UIDC, 0, 0, BACKGROUNDSIZEX, BACKGROUNDSIZEY, WHITENESS);
	//	//_mapTool->render();
	//	break;
	//case Ÿ��Ʋ:
	//	SCENEMANAGER->render();
	//	break;
	//case ���̾�α�:
	//	SCENEMANAGER->render();
	//	break;
	//case ���׺�:
	//	SCENEMANAGER->render();
	//	break;
	//case �÷��̾�:
	//	_player->render();
	//	break;
	//case ������:
	//	SCENEMANAGER->render();
	//	break;
	//case ����:
	//	SCENEMANAGER->render();
	//	break;
	//case �ʼ���:
	//	SCENEMANAGER->render();
	//	break;
	//
	//case ��Ÿ�߰��ϼ�:
	//	break;
	//default:
	//	break;
	//}

	//TIMEMANAGER->render(DC);
	//
	////================�� �����ε� �ǵ帮�� ���� =============
	//
	
	
	
	// �Ǹ��������� ī�޶� �Ŵ��� �� DC�� �׷��ݴϴ�.
	// CAMERAMANAGER->setCameraX()  CAMERAMANAGER->setCameraY() �� �̿��ϸ�   X ,Y ��  WINSIZEX , WINSIZEY ��ŭ ȭ�鿡 �׷��ְ��ִ� ��Ʈ�� �̵���ų �� ���� .
	// �׸��� ��� ������ hdc �� CAMERAMANAGER->getCameraDC()->getMemDC() �� ���־���� !~~!!$!$!#��!#��!$!$#@$!@#@!
}
 