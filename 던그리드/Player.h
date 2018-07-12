#pragma once
#include "gameNode.h"
#include "playerBullet.h"
#include "inven.h"

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
	inven * _inven;
	playerBullet * _pb;
	RECT _collisionRc; //�浹��Ʈ  
	image* _player;
	image* _playerHand[2];
	image* _playerWeapon;
	image* imageDC;
	image* _attackEffect;

	DIRECTION _direction;
	animation* _playerAnimation;

	//bool 
	bool _isGun;													 // bool �� �� �� 1 
	bool _isAlive;													 // bool �� �� �� 2 				
	bool _isJumping;												 // bool �� �� �� 3 						
	bool _isDashing;												 // bool �� �� �� 4 						
	bool _isAttacking;												 // bool �� �� �� 5 						
	bool _isLeftAttack;												 // bool �� �� �� 6 					    
	bool _isChap;													 // bool �� �� �� 7 						
	bool _showAttackEffect;											 // bool �� �� �� 8 						
	bool _attackSpeedCheckCount;									 // bool �� �� �� 9 						
	bool _goDownJump;												 // bool �� �� �� 10 

	// int  
	int _currentHp, _maxHp;											 //���� , ��ü ü�� 
	int _armor;														 //����
	int _currentDash, _maxDash;										 //��� Ƚ�� 
	int _attackMinDamage, _attackMaxDamage, _attackPower;			 //�ּ� ~ �ִ� ������ , ���� ()
	int _fixedDamage;												 //���������� 
	int _jumpCount, _jumpMax;										 // ���� ī��Ʈ , �ƽ� ���� 
						
	// inven
	int  _mainWeapon[2], _assistWeapon[2];							 //���� �������� ���� , ���� �����
	int  _accessory[4];												 //�ǽ�縮
	int  _inventory[15];											 //��ü�κ��丮 15ĭ 
	int  _gold;														 //��
	int  _dashCount , _attackCount;									 //ī��Ʈ �� 
	int  _currentExp, _maxExp;										 //���� , �ִ� ����ġ  
	int  _currentFullNess , _maxFullNess;							 //���� , �ִ� ������ 
	int  _youUsingCount;											 // 1������ ���������� 2������ �����ߤ����� �迭�̶� 0�� 1���� �ްԵ� ;
	int	 _attackEffectCount;										 //
	
	//float 
	float _x, _y , _leftHandX, _leftHandY, _rightHandX, _rightHandY; //player x,y 
	float _attackSpeed, _reloadSpeed;								 //���� �������ӵ� 
	float _evasionPersent, _guardPersent;							 //ȸ��Ȯ�� , ����Ȯ��  	
	float _moveMentSpeed;											 //�̵��ӵ� 
	float _criticalPercent, _criticalAttackDamage;					 //ũ��Ƽ�� Ȯ�� , ũ��Ƽ�� ������ ������ 
	float _dashDamage , _dashSpeed;									 //����Ҷ� ������ , ���ǵ�
	float _gravity, _jumpPower , _jump;								 //�߷� , �÷��̾��� ������ , ���ݹް��ִ� �����Ŀ�
	float _angle;													 //����Ҷ��� ���� 
	float _mouseAngle,_ptMouseX,_ptMouseY;							 //�÷��̾�� ���콺 �� getAngle  , ī�޶󿡼� ���콺 x��ǥ y��ǥ
	float _punchSpeed;												 //��ġ ���ǵ���
	float _locusX, _locusY;											 //�÷��̾��� xy��ǥ ����
	float _weaponAngle, _weaponAttackAngle;							 // ���� angle

 
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



	//������ (get)      
	bool getIsLeftAttack() { return _isLeftAttack; }
	bool getIsGun()						    { return _isGun; }						     //���Ÿ� �������� ?
	bool getIsAlive()					    { return _isAlive; }						 //���� ?
	bool getIsAttacking()					{ return _isAttacking; }				
	bool getAttackCheck()					{ return _attackSpeedCheckCount; } 	//you  attacking ;


	int getCurrentHp()					    { return _currentHp; }						 //���� hp
	int getMaxHp()						    { return _maxHp; }							 //��ühp
	int getArmor()						    { return _armor; }							 // ����
	int getCurrentDash()				    { return _currentDash; }					 // �����ü�
	int getMaxDash()					    { return _maxDash; }						 // ��ü ��ü� 
	int getAttackMinD()					    { return _attackMinDamage; }			     //�ּ� ������
	int getAttackMaxD()					    { return _attackMaxDamage; }				 //�ִ� �����
	int getAttackPower()				    { return _attackPower; }				     //����
	int getMainWeapon(int i)			    { return _mainWeapon[i]; }					 // �ֹ��� �迭 2��
	int getAssistWeapon(int i)			    { return _assistWeapon[i]; }				 // ��������迭 2��
	int getInventory(int i)				    { return _inventory[i]; }					 // �κ��丮 �迭 15��
	int getGold()						    { return _gold; }							 // ����		�� �� ��  
	int getCurrentExp()						{ return _currentExp; }						 //�������ġ
	int getMaxExp()							{ return _maxExp; }
	int getCurrentFullNess()				{ return _currentFullNess; }				 //���� ������ ��
	int getMaxFullNess()				    { return _maxFullNess; }					 //�ִ� ������ ��
	int getYouUsingCount()				    { return _youUsingCount; }					 // ������� ���� �� 
	RECT  getPlayerRect()					{ return _collisionRc; }					 //�浹 rc �� 
	playerBullet * getPBullet()				{ return _pb; }								 //�Ѿ� ��
	image * getEffect()						{ return _attackEffect; }					 //����Ʈ �̹��� �� 


	float getPlayerX()					    { return _x; }								 // �÷��̾� x ��ǥ
	float getPlayerY()					    { return _y; }								 // �÷��̾� y��ǥ
	float getAttackSpeed()				    { return _attackSpeed; }					 // ���ݼӵ�
	float getreloadSpeed()				    { return _reloadSpeed; }					 // �������ӵ�
	float getDashDamage()				    { return _dashDamage; }						 // ��� ������ 
	float getMoveMentSpeed()			    { return _moveMentSpeed; }				 	 // �̵��ӵ�
	float getEvasionPer()				    { return _evasionPersent; }				 	 // ȸ���� Ȯ�� 
	float getGuardPer()					    { return _guardPersent; }					 // ����� Ȯ�� 
	float getCriticalPer()				    { return _criticalPercent; }				 //ũ��Ƽ�� Ȯ�� 
	float getCritiacalDPer()			    { return _criticalAttackDamage; }			 // ũ��Ƽ�� ������ ������ 



	//������ (set) 
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
		
	void healing(int heal)				    { _currentHp += heal; if (_currentHp > _maxHp) _currentHp = _maxHp; }
	void hitDamage(int damage)				{ _currentHp -= damage; }

	Player();
	~Player();
};

