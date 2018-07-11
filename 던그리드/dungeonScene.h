#pragma once
#define MAX_BULLET 20
#include "gameNode.h"
#include "Enemy.h"
#include "Arrow.h"
#include "BigBone.h"
#include "Bat.h"
#include "RedBat.h"
#include "DogBone.h"
#include "BigBat.h"
#include "BigRedBat.h"
#include "MusicAngel.h"
#include "Cow.h"
#include "Boss2.h"
#include "Bullet.h"

class Player;

enum DOOR_STATE { DOOR_OPEN, DOOR_IDLE, DOOR_CLOSE };
enum DOOR_DIR { DOOR_LEFT, DOOR_RIGHT, DOOR_UPDOWN };


struct torch
{
	image* img;
	animation* ani;
	float x, y;
};

struct Door
{
	image* img;
	RECT rc;
	int x, y;
	int frameX, frameY;
	int count;
	DOOR_STATE state;
	DOOR_DIR dir;
};

struct Portal
{
	image* img;
	int x, y;
	int frameX, frameY, count;
};

class dungeonScene : public gameNode
{
private:
	struct infoPlayer
	{
		int currentHp, maxHp;											 //현재 , 전체 체력 
		int armor;														 //방어력
		int currentDash, maxDash;										 //대시 횟수 
		int attackMinDamage, attackMaxDamage, attackPower;			 //최소 ~ 최대 데미지 , 위력 ()
		int fixedDamage;												 //고정데미지 
																		 // inven
		int  mainWeapon[2], assistWeapon[2];							 //현재 장착중인 메인 , 보조 무기들
		int  accessory[4];												 //악쎄사리
		int  inventory[15];											 //전체인벤토리 15칸 
		int  gold;														 //돈
		int  currentExp, maxExp;										 //현재 , 최대 경험치  
		int  currentFullNess, maxFullNess;							 //현재 , 최대 만복도 
		int  youUsingCount;											 // 1번무기 장착중인지 2번무기 장착중ㅇ인지 배열이라 0과 1값을 받게됨 ;

																	 //float 
		float attackSpeed, reloadSpeed;								 //공속 재장전속도 
		float evasionPersent, guardPersent;							 //회피확률 , 막을확률  	
		float moveMentSpeed;											 //이동속도 
		float criticalPercent, criticalAttackDamage;					 //크리티컬 확률 , 크리티컬 데미지 증가율 
		float dashDamage, dashSpeed;									 //대시할때 데미지 , 스피드
		float punchSpeed;												 //펀치 스피드임
	};
protected:
	vector<Enemy*>					_vEnemy;
	vector<Enemy*>::iterator		_viEnemy;

	vector<int> _route;
	
	Player* _player;

	BigBat*		_bigbat;
	BigRedBat*	_bigRedBat;
	MusicAngel* _musicAngel; //음표요정
	Boss2* _boss;			 //보스

	Bullet* _enemyBullet;
	Bullet2* _bigRadBatBullet[MAX_BULLET];
	vector<Door> _vDoor; //문
	vector<torch> _vTorch; //횃불
	vector<Portal> _vPortal; //포탈
	
	string _mapName;
	int _randNum;
	int _temp;
	string _mapValue[11];

	int _count;
	int _count2;
	int _count3;

	bool _bulletMove;
	int _swordCount;

	infoPlayer _infoPlayer;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	virtual void doorInit(void);
	virtual void torchInit(int x, int y);
	void portalInit(float x, float y);
	virtual void setRandMapNum(void);

	void mapload();

	void setCamera(void);

	void selectSize(int idx);

	void chooseMap(int idx);

	void nextTest();

	void load();

	void save();

	void savePlayer();
	void loadPlayer();
	
	void setDoor();
	void doorRender();
	void portalRender();

	void collision();
	dungeonScene();
	~dungeonScene();

	//몬스터 생성 함수
	void setDogBone(int idX, int idY); //개뼈
	void setBigBone(int idX, int idY, int index); //큰칼뼈
	void setArrow(int idX, int idY); //활쟁이
	void setBat(int idX, int idY); //작보박
	void setRedBat(int idX, int idY); //작빨박
	void setBigBat(int idX, int idY); //큰보박
	void setBigRedBat(int idX, int idY); //큰빨박
	void setMusicAngel(int idX, int idY); //음표요정
	void setCow(int idX, int idY); //소
	void setBoss(); //보스

	void setRandomDungeonLink(Player* player) { _player = player; }

	//몬스터 총알 생성 함수
	void MusicAngelBulletFire(); //음표요정 총알 발사 함수
	void BossBulletFire();		 //보스 총알 발사 함수
	void bigbatbulletFire();
	void bigRadbatbulletFire();
};

