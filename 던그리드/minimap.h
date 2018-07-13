#pragma once
#include "gameNode.h"


class minimap : public gameNode
{
private:
	struct tagIcon
	{
		image* img;
		float x, y;
		bool die;
	};
private:
	image* _minimap;
	tagIcon _playerIcon;
	tagIcon _npcIcon[2];
	tagIcon _portalIcon;
	bool _isDungeon;
	int _mapX, _mapY;

	vector<tagIcon> _vEnemyIcon;
	vector<tagIcon> _vDoorIcon;

public:
	minimap();
	~minimap();

	HRESULT init(bool isDungeon);
	void release();
	void render();
	void update();
	void setMinimap(HDC dc);
	void setPlayerXY(float x, float y);
	void setNPCXY(int idx, float x, float y);
	void setPortalXY(float x, float y);

	void setEnemyXY(float x, float y);
	void changeEnemyXY(int idx, float x, float y);

	void setDieMonster();

	bool getEnemySize();

	void setDoorXY(float x, float y, bool height);
};

