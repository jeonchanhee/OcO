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
	LEFT_STOP,
	LEFT_RUN,
	RIGHT_STOP,
	RIGHT_RUN
};

class Player : public gameNode
{
private:
	struct infoPlayer
	{
		int currentHp, maxHp;											 //ÇöÀç , ÀüÃ¼ Ã¼·Â 
		int armor;														 //¹æ¾î·Â
		int currentDash, maxDash;										 //´ë½Ã È½¼ö 
		int attackMinDamage, attackMaxDamage, attackPower;			 //ÃÖ¼Ò ~ ÃÖ´ë µ¥¹ÌÁö , À§·Â ()
		int fixedDamage;												 //°íÁ¤µ¥¹ÌÁö 
																		 // inven
		int  mainWeapon[2], assistWeapon[2];							 //ÇöÀç ÀåÂøÁßÀÎ ¸ŞÀÎ , º¸Á¶ ¹«±âµé
		int  accessory[4];												 //¾Ç½ê»ç¸®
		int  inventory[15];											 //ÀüÃ¼ÀÎº¥Åä¸® 15Ä­ 
		int  gold;														 //µ·
		int  currentExp, maxExp;										 //ÇöÀç , ÃÖ´ë °æÇèÄ¡  
		int  currentFullNess, maxFullNess;							 //ÇöÀç , ÃÖ´ë ¸¸º¹µµ 
		int  youUsingCount;											 // 1¹ø¹«±â ÀåÂøÁßÀÎÁö 2¹ø¹«±â ÀåÂøÁß¤·ÀÎÁö ¹è¿­ÀÌ¶ó 0°ú 1°ªÀ» ¹Ş°ÔµÊ ;

		//float 
		float attackSpeed, reloadSpeed;								 //°ø¼Ó ÀçÀåÀü¼Óµµ 
		float evasionPersent, guardPersent;							 //È¸ÇÇÈ®·ü , ¸·À»È®·ü  	
		float moveMentSpeed;											 //ÀÌµ¿¼Óµµ 
		float criticalPercent, criticalAttackDamage;					 //Å©¸®Æ¼ÄÃ È®·ü , Å©¸®Æ¼ÄÃ µ¥¹ÌÁö Áõ°¡À² 
		float dashDamage, dashSpeed;									 //´ë½ÃÇÒ¶§ µ¥¹ÌÁö , ½ºÇÇµå
		float punchSpeed;												 //ÆİÄ¡ ½ºÇÇµåÀÓ
	};

private:
	playerBullet * _pb;
	RECT _collisionRc; //Ãæµ¹·ºÆ® 
	image* _player;
	image* _playerHand[2];
	image* _playerWeapon;
	image* imageDC;
	image* _attackEffect;

	DIRECTION _direction;
	animation* _playerAnimation;

	infoPlayer	_infoPlayer;

	//bool 
	bool _isGun;						//boolÀÌÁö±İ 1							//ÇöÀç ¿ø°Å¸® ¹«±âÀÎÁö Ã¼Å© 
	bool _isAlive;						//boolÀÌÁö±İ 2							//ÀÚ³× »ıÁ¸ÁßÀÎ°¡ ????
	bool _isJumping;					//boolÀÌÁö±İ 3							//Á¡ÇÁÁßÀÎ°¡ ?
	bool _isDashing;					//boolÀÌÁö±İ 4							//´ë½ÃÁß?
	bool _isAttacking;					//boolÀÌÁö±İ 5							//¶§¸®´ÂÁß ?
	bool _isLeftAttack;					//boolÀÌÁö±İ 6						    //¿ŞÂÊ¶§·Ç´Ï 
	bool _isChap;						//boolÀÌÁö±İ 7							//°¡¹ö¸®³ª???
	bool _showAttackEffect;				//boolÀÌÁö±İ 8							//°ø°İÀÌÆåÆ®!
	bool _attackSpeedCheckCount;		//boolÀÌÁö±İ 9							//°ø°İ½ºÇÇµåÃéÄí ÄÉÄùÄùÄù®c®cÃßÄÉÃßÄÉÃßÄÉÃßÄÉÃßÄÉÃßÄÉÃß±P¤»
	bool _goDownJump;					//boolÀÌÁö±İ 10			¶Ç¶§ÂÅ ûıÀÌ ¸î°³´Ï

	// int  
	int _currentHp, _maxHp;											 //ÇöÀç , ÀüÃ¼ Ã¼·Â 
	int _armor;														 //¹æ¾î·Â
	int _currentDash, _maxDash;										 //´ë½Ã È½¼ö 
	int _attackMinDamage, _attackMaxDamage, _attackPower;			 //ÃÖ¼Ò ~ ÃÖ´ë µ¥¹ÌÁö , À§·Â ()
	int _fixedDamage;												 //°íÁ¤µ¥¹ÌÁö 
	int _jumpCount, _jumpMax;										 // Á¡ÇÁ Ä«¿îÆ® , ¸Æ½º Á¡ÇÁ 
						
	// inven
	int  _mainWeapon[2], _assistWeapon[2];							 //ÇöÀç ÀåÂøÁßÀÎ ¸ŞÀÎ , º¸Á¶ ¹«±âµé
	int  _accessory[4];												 //¾Ç½ê»ç¸®
	int  _inventory[15];											 //ÀüÃ¼ÀÎº¥Åä¸® 15Ä­ 
	int  _gold;														 //µ·
	int  _count;													 //Ä«¿îÆ® °ª 
	int  _currentExp, _maxExp;										 //ÇöÀç , ÃÖ´ë °æÇèÄ¡  
	int  _currentFullNess , _maxFullNess;							 //ÇöÀç , ÃÖ´ë ¸¸º¹µµ 
	int  _youUsingCount;											 // 1¹ø¹«±â ÀåÂøÁßÀÎÁö 2¹ø¹«±â ÀåÂøÁß¤·ÀÎÁö ¹è¿­ÀÌ¶ó 0°ú 1°ªÀ» ¹Ş°ÔµÊ ;
	int	 _attackEffectCount;										 //
	
	//float 
	float _x, _y , _leftHandX, _leftHandY, _rightHandX, _rightHandY; //player x,y 
	float _attackSpeed, _reloadSpeed;								 //°ø¼Ó ÀçÀåÀü¼Óµµ 
	float _evasionPersent, _guardPersent;							 //È¸ÇÇÈ®·ü , ¸·À»È®·ü  	
	float _moveMentSpeed;											 //ÀÌµ¿¼Óµµ 
	float _criticalPercent, _criticalAttackDamage;					 //Å©¸®Æ¼ÄÃ È®·ü , Å©¸®Æ¼ÄÃ µ¥¹ÌÁö Áõ°¡À² 
	float _dashDamage , _dashSpeed;									 //´ë½ÃÇÒ¶§ µ¥¹ÌÁö , ½ºÇÇµå
	float _gravity, _jumpPower , _jump;								 //Áß·Â , ÇÃ·¹ÀÌ¾îÀÇ Á¡ÇÁ·Â , Áö±İ¹Ş°íÀÖ´Â Á¡ÇÁÆÄ¿ö
	float _angle;													 //´ë½ÃÇÒ¶§ÀÇ °¢µµ 
	float _mouseAngle,_ptMouseX,_ptMouseY;							 //ÇÃ·¹ÀÌ¾î¿Í ¸¶¿ì½º ÀÇ getAngle  , Ä«¸Ş¶ó¿¡¼­ ¸¶¿ì½º xÁÂÇ¥ yÁÂÇ¥
	float _punchSpeed;												 //ÆİÄ¡ ½ºÇÇµåÀÓ
	float _locusX, _locusY;											 //ÇÃ·¹ÀÌ¾îÀÇ xyÁÂÇ¥ ÀúÀå
	float _weaponAngle, _weaponAttackAngle;							 // ¹«±â angle

 
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


	//Á¢±ÙÀÚ (get)      
	bool getIsGun()						    { return _isGun; }						     //¿ø°Å¸® ¹«±âÀåÂø ?
	bool getIsAlive()					    { return _isAlive; }						 //»ıÁ¸ ?
										   
	int getCurrentHp()					    { return _currentHp; }						 //ÇöÀç hp
	int getMaxHp()						    { return _maxHp; }							 //ÀüÃ¼hp
	int getArmor()						    { return _armor; }							 // ¹æ¾î·Â
	int getCurrentDash()				    { return _currentDash; }					 // ÇöÀç´ë½Ã¼ö
	int getMaxDash()					    { return _maxDash; }						 // ÀüÃ¼ ´ë½Ã¼ö 
	int getAttackMinD()					    { return _attackMinDamage; }			     //ÃÖ¼Ò µ¥¹ÌÁö
	int getAttackMaxD()					    { return _attackMaxDamage; }				 //ÃÖ´ë ´ë¹ÌÁö
	int getAttackPower()				    { return _attackPower; }				     //À§·Â
	int getMainWeapon(int i)			    { return _mainWeapon[i]; }					 // ÁÖ¹«±â ¹è¿­ 2°³
	int getAssistWeapon(int i)			    { return _assistWeapon[i]; }				 // º¸Á¶¹«±â¹è¿­ 2°³
	int getInventory(int i)				    { return _inventory[i]; }					 // ÀÎº¥Åä¸® ¹è¿­ 15°³
	int getGold()						    { return _gold; }							 // °¡Áø		µ· µ· µ·  
	int getCurrentExp()						{ return _currentExp; }						 //ÇöÀç°æÇèÄ¡
	int getMaxExp()							{ return _maxExp; }
	int getCurrentFullNess()				{ return _currentFullNess; }				 //ÇöÀç ¸¸º¹µµ 
	int getMaxFullNess()				    { return _maxFullNess; }					 //ÃÖ´ë ¸¸º¹µµ
	int getYouUsingCount()				    { return _youUsingCount; }					 // »ç¿ëÁßÀÎ ¹«±â 1¹øÀÎ°¡ 2¹øÀÎ°¡ ?

										   
	float getPlayerX()					    { return _x; }								 // ÇÃ·¹ÀÌ¾î x ÁÂÇ¥
	float getPlayerY()					    { return _y; }								 // ÇÃ·¹ÀÌ¾î yÁÂÇ¥
	float getAttackSpeed()				    { return _attackSpeed; }					 // °ø°İ¼Óµµ
	float getreloadSpeed()				    { return _reloadSpeed; }					 // ÀçÀåÀü¼Óµµ
	float getDashDamage()				    { return _dashDamage; }						 // ´ë½Ã µ¥¹ÌÁö 
	float getMoveMentSpeed()			    { return _moveMentSpeed; }				 	 // ÀÌµ¿¼Óµµ
	float getEvasionPer()				    { return _evasionPersent; }				 	 // È¸ÇÇÇÒ È®·ü 
	float getGuardPer()					    { return _guardPersent; }					 // ¹æ¾îÇÒ È®·ü 
	float getCriticalPer()				    { return _criticalPercent; }				 //Å©¸®Æ¼ÄÃ È®·ü 
	float getCritiacalDPer()			    { return _criticalAttackDamage; }			 // Å©¸®Æ¼ÄÃ µ¥¹ÌÁö Áõ°¡À² 



	//¼³Á¤ÀÚ (set) 
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

