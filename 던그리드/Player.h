#pragma once
#include "gameNode.h"
#include "playerBullet.h"
#include "inven.h"
#include "progressBar.h"

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

	class dungeonScene;

private:
	progressBar * _hpbar;
	inven * _inven;
	playerBullet * _pb;
	RECT _collisionRc; //충돌렉트  
	image* _player;
	image* _playerHand[2];
	image* _playerWeapon;
	image* imageDC;
	image* _attackEffect;

	DIRECTION _direction;
	animation* _playerAnimation;

	//bool 
	bool _isGun;												
	bool _isAlive;												
	bool _isJumping;											
	bool _isDashing;											
	bool _isAttacking;											
	bool _isLeftAttack;											
	bool _isChap;												
	bool _showAttackEffect;										
	bool _attackSpeedCheckCount;								
	bool _goDownJump;											

	// int  
	int _level;
	int _currentHp, _maxHp;											 //현재 , 전체 체력 
	int _armor;														 //방어력
	int _currentDash, _maxDash;										 //대시 횟수 
	int _attackMinDamage, _attackMaxDamage, _attackPower;			 //최소 ~ 최대 데미지 , 위력 ()
	int _fixedDamage;												 //고정데미지 
	int _jumpCount, _jumpMax;										 // 점프 카운트 , 맥스 점프 
						


	int  _dashCount , _attackCount;									
	int  _currentExp, _maxExp;										
	int  _currentFullNess , _maxFullNess;							
	int  _youUsingCount;											
	int	 _attackEffectCount;
	int  _bulletType;
	int  _frameX, _frameY;
	
	//float 
	float _x, _y , _leftHandX, _leftHandY, _rightHandX, _rightHandY;
	float _attackSpeed, _reloadSpeed;								
	float _evasionPersent, _guardPersent;							
	float _moveMentSpeed;											
	float _criticalPercent, _criticalAttackDamage;					
	float _dashDamage , _dashSpeed;									
	float _gravity, _jumpPower , _jump;								
	float _angle;													
	float _mouseAngle,_ptMouseX,_ptMouseY;							
	float _punchSpeed;												
	float _locusX, _locusY;											
	float _weaponAngle, _weaponAttackAngle;							

 
	//test
	int xIndex, yIndex;
	int _downStateCheck[2], _upStateCheck[2], _leftCheck[2], _rightCheck[2];

public:

	HRESULT init();
	void release();
	void update();
	void render();
	RECT getRc() { return _collisionRc; }

	void keyInput();
	void rightStop();
	void leftStop();
	void mouseControl();
	void move();
	void attack();
	void effect();
	void cameraSetting();
	void tileCollision();
	void pixelCollision();
	void itemInfo();



	//접근자 (get)      
	bool getIsLeftAttack()					{ return _isLeftAttack; }
	bool getIsGun()						    { return _isGun; }					
	bool getIsAlive()					    { return _isAlive; }				
	bool getIsAttacking()					{ return _isAttacking; }			
	bool getAttackCheck()					{ return _attackSpeedCheckCount; } 


	int getLv()								 { return _level; }
	int getCurrentHp()					    { return _currentHp; }						
	int getMaxHp()						    { return _maxHp; }							
	int getArmor()						    { return _armor; }							
	int getCurrentDash()				    { return _currentDash; }					
	int getMaxDash()					    { return _maxDash; }						
	int getAttackMinD()					    { return _attackMinDamage; }			    
	int getAttackMaxD()					    { return _attackMaxDamage; }				
	int getAttackPower()				    { return _attackPower; }				    
	int getCurrentExp()						{ return _currentExp; }						
	int getMaxExp()							{ return _maxExp; }
	int getCurrentFullNess()				{ return _currentFullNess; }				
	int getMaxFullNess()				    { return _maxFullNess; }					
	int getYouUsingCount()				    { return _youUsingCount; }					
	RECT  getPlayerRect()					{ return _collisionRc; }					
	playerBullet * getPBullet()				{ return _pb; }								
	image * getEffect()						{ return _attackEffect; }					
	inven* getInven()						 { return _inven; }

	float getPlayerX()					    { return _x; }								
	float getPlayerY()					    { return _y; }								
	float getAttackSpeed()				    { return _attackSpeed; }					
	float getreloadSpeed()				    { return _reloadSpeed; }					
	float getDashDamage()				    { return _dashDamage; }						
	float getMoveMentSpeed()			    { return _moveMentSpeed; }				 	
	float getEvasionPer()				    { return _evasionPersent; }				 	
	float getGuardPer()					    { return _guardPersent; }					
	float getCriticalPer()				    { return _criticalPercent; }				
	float getCritiacalDPer()			    { return _criticalAttackDamage; }			



	//설정자 (set) 
	void setLv(bool lv)						{ _level = lv; }
	void setIsGun(bool isGun)				{ _isGun = isGun; }
	void setIsAlive(bool isAlive)			{ _isAlive = isAlive; }
	void setCurrentHp(int currentHp)		{ _currentHp = currentHp; }
	void setMaxHp(int maxHp)				{ _maxHp = maxHp; }
	void setArmor(int armor)				{ _armor = armor; }
	void setMaxDash(int dash)				{ _maxDash = dash; }
	void setAttackMinD(int attackMinD)		{ _attackMinDamage = attackMinD; }
	void setAttackMaxD(int attackMaxD)		{ _attackMaxDamage = attackMaxD; }
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
	void setCurrentFullNess(int fullNess)	{ _currentFullNess = fullNess; }
	void setMaxFullNess(int fullNess)		{ _maxFullNess = fullNess; }
	void setCurrentExp(int exp)				{ _currentExp = exp; }
	void setMaxExp(int exp)				    { _maxExp = exp; }
	
	//gold
	int getGold()							{ return _inven->getGold(); }
	void setGold(int i)						{ _inven->setGold(i); }

	void healing(int heal)				    { _currentHp += heal; if (_currentHp > _maxHp) _currentHp = _maxHp; }
	void hitDamage(int damage)				{ _currentHp -= damage; }

	Player();
	~Player();
};

