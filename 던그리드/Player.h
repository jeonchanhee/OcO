#pragma once
#include "gameNode.h"
enum DIRECTION
{
	LEFT_STOP,
	LEFT_RUN,
	RIGHT_STOP,
	RIGHT_RUN
};

class Player :	public gameNode
{
private:
	
	image * _player;
	image * _playerHand[2];
	image * _playerWeapon;

	DIRECTION _direction;

	animation * _playerAnimation;
	//bool 
	bool _isGun;													 //현재 원거리 무기인지 체크 
	bool _isAlive;													 //자네 생존중인가 ????
	bool _isJumping;													 //점프중인가 ?
	// int 
	int _currentHp, _maxHp;											 //현재 , 전체 체력 
	int _armor;														 //방어력
	int _currentDash , _maxDash;									 //대시 횟수 
	int _attackMinDamage , _attackMaxDamage, _attackPower;			 //최소 ~ 최대 데미지 , 위력 ()
	int _fixedDamage;												 //고정데미지 
	int _jumpCount , _jumpMax;										 // 점프 카운트 , 맥스 점프 
	// inven
	int  _mainWeapon[2], _assistWeapon[2];							 //현재 장착중인 메인 , 보조 무기들 
	int  _inventory[15];											 //전체인벤토리 15칸 
	int  _gold;														 //돈
	int  _count;													 //카운트 값 



	//float 
	float _x, _y;													 //player x,y 
	float _attackSpeed , _reloadSpeed;								 //공속 재장전속도 
	float _evasionPersent, _guardPersent;							 //회피확률 , 막을확률  	
	float _moveMentSpeed;											 //이동속도 
	float _criticalPercent, _criticalAttackDamage;					 //크리티컬 확률 , 크리티컬 데미지 증가율 
	float _dashDamage;												 //대시할때 데미지 . !!!! 
	float _gravity, _jumpPower , _jump;
 
public:

	HRESULT init();
	void release();
	void update();
	void render();


	void keyAnimation();
	void keyInput();
	void move();
	void keyMouse();
	void leftJump(void * obj);
	void rightJump(void * obj);




	//접근자 (get)      
	bool getIsGun()			   { return _isGun; }						     //원거리 무기장착 ?
	bool getIsAlive()		   { return _isAlive; }							 //생존 ?

	int getCurrentHp()		   { return _currentHp; }						 //현재 hp
	int getMaxHp()			   { return _maxHp; }							//전체hp
	int getArmor()			   { return _armor; }							 // 방어력
	int getCurrentDash()	   { return _currentDash; }						// 현재대시수
	int getMaxDash()		   { return _maxDash; }								// 전체 대시수 
	int getAttackMinD()		   { return _attackMinDamage; }			         //최소 데미지
	int getAttackMaxD()		   { return _attackMaxDamage; }					//최대 대미지
	int getAttackPower()	   { return _attackPower; }				    	//위력
	int getMainWeapon(int i)   { return _mainWeapon[i]; }					// 주무기 배열 2개
	int getAssistWeapon(int i) { return _assistWeapon[i]; }					 // 보조무기배열 2개
	int getInventory(int i)    { return _inventory[i]; }					 // 인벤토리 배열 15개
	int getGold()			   { return _gold; }							  // 가진		돈 돈 돈 

	float getPlayerX()		   { return _x; }								 // 플레이어 x 좌표
	float getPlayerY()		   { return _y; }								 // 플레이어 y좌표
	float getAttackSpeed()	   { return _attackSpeed; }						  // 공격속도
	float getreloadSpeed()     { return _reloadSpeed; }						  // 재장전속도
	float getDashDamage()	   { return _dashDamage; }						  // 대시 데미지 
	float getMoveMentSpeed()   { return _moveMentSpeed; }				 	 // 이동속도
	float getEvasionPer()	   { return _evasionPersent; }				 	// 회피할 확률 
	float getGuardPer()		   { return _guardPersent; }					 // 방어할 확률 
	float getCriticalPer()	   { return _criticalPercent; }				    //크리티컬 확률 
	float getCritiacalDPer()   { return _criticalAttackDamage; }			 // 크리티컬 데미지 증가율 

	

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



	Player();
	~Player();
};

