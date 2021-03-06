#pragma once
#include "singletonBase.h"
#include <map>

//���� ���� ���ӳ�� ���漱��
class gameNode;
class Player;
class itemManager;

class sceneManager : public singletonBase<sceneManager>
{
public:
	typedef map<string, gameNode*>				mapSceneList;
	typedef map<string, gameNode*>::iterator	mapSceneIter;

private:
	static gameNode*	_currentScene;	//���� ��
	mapSceneList		_mSceneList;

	Player* _player;
	itemManager* _im;

public:
	sceneManager();
	~sceneManager();

	HRESULT init();
	void release();
	void update();
	void render();

	//�� �߰� �Լ�
	gameNode* addScene(string sceneName, gameNode* scene);

	//�� ����
	HRESULT changeScene(string sceneName);

	void setPlayerAddressLink(Player* player) { _player = player; }
	Player* getPlayerAddressLink() { return _player; }

	void setIMAddressLink(itemManager* im) { _im = im; }
	itemManager* getIMAddressLink() { return _im; }
};

