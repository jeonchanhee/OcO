#pragma once
#include "gameNode.h"
#include "playerBullet.h"

#define DASHSPEED 33
#define PUNCHSPEED 6.0f
#define GRAVITY 0.3
#define ONE_HUNDRED 100
#define ONE_HUNDRED_HALF 50
#define TEN 10

enum DIRECTION
{
	LEFT_STOP, LEFT_RUN, RIGHT_STOP, RIGHT_RUN
};

class Player : public gameNode
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

private:
	playerBullet * _pb;
	RECT _collisionRc; //충돌렉트 
	image* _player;
	image* _playerHand[2];
	image* _playerWeapon;
	image* imageDC;
	image* _attackEffect;

	DIRECTION _direction;
	animation* _playerAnimation;

	infoPlayer	_infoPlayer;

	//bool 
	bool _isGun;						//bool이지금 1
	bool _isAlive;						//bool이지금 2					
	bool _isJumping;					//bool이지금 3							
	bool _isDashing;					//bool이지금 4							
	bool _isAttacking;					//bool이지금 5							
	bool _isLeftAttack;					//bool이지금 6						    
	bool _isChap;						//bool이지금 7							
	bool _showAttackEffect;				//bool이지금 8							
	bool _attackSpeedCheckCount;		//bool이지금 9							
	bool _goDownJump;					//bool이지금 10  

	// int  
	int _currentHp, _maxHp;											 //현재 , 전체 체력 
	int _armor;														 //방어력
	int _currentDash, _maxDash;										 //대시 횟수 
	int _attackMinDamage, _attackMaxDamage, _attackPower;			 //최소 ~ 최대 데미지 , 위력 ()
	int _fixedDamage;												 //고정데미지 
	int _jumpCount, _jumpMax;										 // 점프 카운트 , 맥스 점프 
						
	// inven
	int  _mainWeapon[2], _assistWeapon[2];							 //현재 장착중인 메인 , 보조 무기들
	int  _accessory[4];												 //악쎄사리
	int  _inventory[15];											 //전체인벤토리 15칸 
	int  _gold;														 //돈
	int  _count;													 //카운트 값 
	int  _currentExp, _maxExp;										 //현재 , 최대 경험치  
	int  _currentFullNess , _maxFullNess;							 //현재 , 최대 만복도 
	int  _youUsingCount;											 // 1번무기 장착중인지 2번무기 장착중ㅇ인지 배열이라 0과 1값을 받게됨 ;
	int	 _attackEffectCount;										 //
	
	//float 
	float _x, _y , _leftHandX, _leftHandY, _rightHandX, _rightHandY; //player x,y 
	float _attackSpeed, _reloadSpeed;								 //공속 재장전속도 
	float _evasionPersent, _guardPersent;							 //회피확률 , 막을확률  	
	float _moveMentSpeed;											 //이동속도 
	float _criticalPercent, _criticalAttackDamage;					 //크리티컬 확률 , 크리티컬 데미지 증가율 
	float _dashDamage , _dashSpeed;									 //대시할때 데미지 , 스피드
	float _gravity, _jumpPower , _jump;								 //중력 , 플레이어의 점프력 , 지금받고있는 점프파워
	float _angle;													 //대시할때의 각도 
	float _mouseAngle,_ptMouseX,_ptMouseY;							 //플레이어와 마우스 의 getAngle  , 카메라에서 마우스 x좌표 y좌표
	float _punchSpeed;												 //펀치 스피드임
	float _locusX, _locusY;											 //플레이어의 xy좌표 저장
	float _weaponAngle, _weaponAttackAngle;							 // 무기 angle

 
	//test
	int xIndex, yIndex;
	int leftRightCheck[2], _downStateCheck[2], _upStateCheck[2], _leftCheck[2], _rightCheck[2];
public:

	HRESULT init();
	void release();
	void update();
	void render();

	void keyInput();
	void mouseControl();
	void move();
	void attack();
	void effect();
	void cameraSetting();
	void tileCollision();


	//접근자 (get)      
	bool getIsGun()						    { return _isGun; }						     //원거리 무기장착 ?
	bool getIsAlive()					    { return _isAlive; }						 //생존 ?
										   
	int getCurrentHp()					    { return _currentHp; }						 //현재 hp
	int getMaxHp()						    { return _maxHp; }							 //전체hp
	int getArmor()						    { return _armor; }							 // 방어력
	int getCurrentDash()				    { return _currentDash; }					 // 현재대시수
	int getMaxDash()					    { return _maxDash; }						 // 전체 대시수 
	int getAttackMinD()					    { return _attackMinDamage; }			     //최소 데미지
	int getAttackMaxD()					    { return _attackMaxDamage; }				 //최대 대미지
	int getAttackPower()				    { return _attackPower; }				     //위력
	int getMainWeapon(int i)			    { return _mainWeapon[i]; }					 // 주무기 배열 2개
	int getAssistWeapon(int i)			    { return _assistWeapon[i]; }				 // 보조무기배열 2개
	int getInventory(int i)				    { return _inventory[i]; }					 // 인벤토리 배열 15개
	int getGold()						    { return _gold; }							 // 가진		돈 돈 돈  
	int getCurrentExp()						{ return _currentExp; }						 //현재경험치
	int getMaxExp()							{ return _maxExp; }
	int getCurrentFullNess()				{ return _currentFullNess; }				 //현재 만복도 
	int getMaxFullNess()				    { return _maxFullNess; }					 //최대 만복도
	int getYouUsingCount()				    { return _youUsingCount; }					 // 사용중인 무기 1번인가 2번인가 ?

										   
	float getPlayerX()					    { return _x; }								 // 플레이어 x 좌표
	float getPlayerY()					    { return _y; }								 // 플레이어 y좌표
	float getAttackSpeed()				    { return _attackSpeed; }					 // 공격속도
	float getreloadSpeed()				    { return _reloadSpeed; }					 // 재장전속도
	float getDashDamage()				    { return _dashDamage; }						 // 대시 데미지 
	float getMoveMentSpeed()			    { return _moveMentSpeed; }				 	 // 이동속도
	float getEvasionPer()				    { return _evasionPersent; }				 	 // 회피할 확률 
	float getGuardPer()					    { return _guardPersent; }					 // 방어할 확률 
	float getCriticalPer()				    { return _criticalPercent; }				 //크리티컬 확률 
	float getCritiacalDPer()			    { return _criticalAttackDamage; }			 // 크리티컬 데미지 증가율 



	//설정자 (set) 
	void setIsGun(bool isGun)				{ _isGun = isGun; }
	void setIsAlive(bool isAlive)			{ _isAlive = isAlive; }
	void setCurrentHp(int currentHp)		{ _currentHp = currentHp; }
	void setMaxHp(int maxHp)				{ _maxHp = maxHp; }
	void setArmor(int armor)				{ _armor = armor; }
	void setMaxDash(int dash)				{ _maxDash = dash; }
	void setAttackMinD(int attackMinD)		{ _attackMinDamage = attackMinD; }
	void setAttackMaxD(int attackMaxD)		{ _attackMaxDamage = attackMaxD; }
	void setMainWeapon(int arr, int val)	{ _mainWeapon[arr] = val; }
	void setAssistWeapon(int arr, int val)	{ _assistWeapon[arr] = val; }
	void setInvenTory(int arr, int val)		{ _inventory[arr] = val; }
	void setPlayerX(float x)				{ _x = x; }
	void setPlayerY(float y)				{ _y = y; }
	void setAttackSpeed(float speed)		{ _attackSpeed = speed; }
	void setreloadSpeed(float speed)		{ _reloadSpeed = speed; }
	void setDashDamage(float damage)		{ _dashDamage = damage; }
	void setMoveMentSpeed(float speed)		{ _moveMentSpeed = speed; }
	void setEvasionPer(float per)			{ _evasionPersent = per; }
	void setGuardPer(float per)				{ _guardPersent = per; }
	void setCriticalPer(float per)			{ _criticalPercent = per; }
	void setCriticalDPer(float per)			{ _criticalAttackDamage = per; }
	void setGold(int gold)					{ _gold = gold; }
	void setCurrentFullNess(int fullNess)	{ _currentFullNess = fullNess; }
	void setMaxFullNess(int fullNess)		{ _maxFullNess = fullNess; }
	void setCurrentExp(int exp)				{ _currentExp = exp; }
	void setMaxExp(int exp)				    { _maxExp = exp; }

	Player();
	~Player();
};

