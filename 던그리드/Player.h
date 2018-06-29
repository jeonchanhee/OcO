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
	bool _isGun;													 //���� ���Ÿ� �������� üũ 
	bool _isAlive;													 //�ڳ� �������ΰ� ????
	bool _isJumping;													 //�������ΰ� ?
	// int 
	int _currentHp, _maxHp;											 //���� , ��ü ü�� 
	int _armor;														 //����
	int _currentDash , _maxDash;									 //��� Ƚ�� 
	int _attackMinDamage , _attackMaxDamage, _attackPower;			 //�ּ� ~ �ִ� ������ , ���� ()
	int _fixedDamage;												 //���������� 
	int _jumpCount , _jumpMax;										 // ���� ī��Ʈ , �ƽ� ���� 
	// inven
	int  _mainWeapon[2], _assistWeapon[2];							 //���� �������� ���� , ���� ����� 
	int  _inventory[15];											 //��ü�κ��丮 15ĭ 
	int  _gold;														 //��
	int  _count;													 //ī��Ʈ �� 



	//float 
	float _x, _y;													 //player x,y 
	float _attackSpeed , _reloadSpeed;								 //���� �������ӵ� 
	float _evasionPersent, _guardPersent;							 //ȸ��Ȯ�� , ����Ȯ��  	
	float _moveMentSpeed;											 //�̵��ӵ� 
	float _criticalPercent, _criticalAttackDamage;					 //ũ��Ƽ�� Ȯ�� , ũ��Ƽ�� ������ ������ 
	float _dashDamage;												 //����Ҷ� ������ . !!!! 
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




	//������ (get)      
	bool getIsGun()			   { return _isGun; }						     //���Ÿ� �������� ?
	bool getIsAlive()		   { return _isAlive; }							 //���� ?

	int getCurrentHp()		   { return _currentHp; }						 //���� hp
	int getMaxHp()			   { return _maxHp; }							//��ühp
	int getArmor()			   { return _armor; }							 // ����
	int getCurrentDash()	   { return _currentDash; }						// �����ü�
	int getMaxDash()		   { return _maxDash; }								// ��ü ��ü� 
	int getAttackMinD()		   { return _attackMinDamage; }			         //�ּ� ������
	int getAttackMaxD()		   { return _attackMaxDamage; }					//�ִ� �����
	int getAttackPower()	   { return _attackPower; }				    	//����
	int getMainWeapon(int i)   { return _mainWeapon[i]; }					// �ֹ��� �迭 2��
	int getAssistWeapon(int i) { return _assistWeapon[i]; }					 // ��������迭 2��
	int getInventory(int i)    { return _inventory[i]; }					 // �κ��丮 �迭 15��
	int getGold()			   { return _gold; }							  // ����		�� �� �� 

	float getPlayerX()		   { return _x; }								 // �÷��̾� x ��ǥ
	float getPlayerY()		   { return _y; }								 // �÷��̾� y��ǥ
	float getAttackSpeed()	   { return _attackSpeed; }						  // ���ݼӵ�
	float getreloadSpeed()     { return _reloadSpeed; }						  // �������ӵ�
	float getDashDamage()	   { return _dashDamage; }						  // ��� ������ 
	float getMoveMentSpeed()   { return _moveMentSpeed; }				 	 // �̵��ӵ�
	float getEvasionPer()	   { return _evasionPersent; }				 	// ȸ���� Ȯ�� 
	float getGuardPer()		   { return _guardPersent; }					 // ����� Ȯ�� 
	float getCriticalPer()	   { return _criticalPercent; }				    //ũ��Ƽ�� Ȯ�� 
	float getCritiacalDPer()   { return _criticalAttackDamage; }			 // ũ��Ƽ�� ������ ������ 

	

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



	Player();
	~Player();
};

