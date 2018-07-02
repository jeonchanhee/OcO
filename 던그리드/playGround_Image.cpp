#include "stdafx.h"
#include "playGround.h"


HRESULT playGround::Image_init(void)
{
	IMAGEMANAGER->addImage("cursor", "image/UI/Cursor(61,70).bmp", 0, 0, 61, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("black", "image/UI/Black(1920x1080).bmp", 0, 0, 1920, 1080, true, RGB(255, 0, 255), true);

	//==========타이틀이미지==========
	//데이터 선택할 때 뒷 배경 어둡게 보이게 하려고 알파블렌드 처리했어요! - 0701은지
	IMAGEMANAGER->addImage("title", "image/UI/Title(1920x1080).bmp", 0, 0, 1920,1080, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("T_back", "image/UI/Blue(1920x1080).bmp", 0, 0, 1920,1080, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("T_cloud0", "image/UI/BackCloud0(3840x1080).bmp", 0, 0, 3840,1080, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("T_cloud1", "image/UI/BackCloud1(4300x1080).bmp", 0, 0, 4300,1080, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("T_start", "image/UI/B_start(420x70,2x1).bmp", 0, 0, 420,70, 2,1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("T_option", "image/UI/B_option(420x70,2x1).bmp", 0, 0, 420,70, 2,1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("T_exit", "image/UI/B_exit(420x70,2x1).bmp", 0, 0, 420,70, 2,1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("T_text", "image/UI/slotText(684x72,3x1).bmp", 0, 0, 684, 72, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("T_textBack", "image/UI/slotBase(1152x858).bmp", 0, 0, 1152, 858, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("T_delete", "image/UI/slotDeleteButton(372x102).bmp", 0, 0, 372, 102, true, RGB(255, 0, 255));

	//==========트레이닝==========
	IMAGEMANAGER->addImage("training", "image/UI/UItraning(1920x1080).bmp", 0, 0, 1920, 1080, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("trainB", "image/UI/UItrainB(535x214,5x2).bmp", 0, 0, 535, 214 ,5 ,2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("trainI", "image/UI/Ticon(1080x216,5x3).bmp", 0, 0, 1080, 216 ,5 ,3, true, RGB(255, 0, 255));

	//==========플레이어==========
	IMAGEMANAGER->addFrameImage("기본플레이어", "image/player/normalPlayer(640x360,8x4).bmp", 640, 360, 8, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addRotateFrameImage("공주플레이어", "image/player/princessPlayer(480x320,6x4).bmp", 480, 320, 6, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addRotateImage("플레이어손", "image/player/hand(8x8,1x1).bmp", 15, 15, true, RGB(1, 2, 5));
	IMAGEMANAGER->addImage("체력바", "image/player/hpBar(50x50,1x1).bmp", 50, 50, false, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("체력바출렁출렁", "image/player/hpBarWave(120x50,6x1).bmp", 120, 50, 6, 1, true, RGB(255, 0, 255));
	EFFECTMANAGER->addEffect("대시왼쪽", "image/player/dashManLeft(320x95,4x1).bmp", 320, 95, 80, 95, 1.0f,0.3f, 5);
	EFFECTMANAGER->addEffect("대시오른쪽",  "image/player/dashManRight(320x95,4x1).bmp", 320, 95, 80, 95, 1.0f, 0.3f, 5);
	EFFECTMANAGER->addEffect("왼쪽걸을때",  "image/player/leftRunDust(200x40,5x1).bmp", 250, 50, 50, 50, 1.0f, 0.3f, 1);
	EFFECTMANAGER->addEffect("오른쪽걸을때","image/player/rightRunDust(200x40,5x1).bmp", 250, 50, 50, 50, 1.0f, 0.3f,1);
	EFFECTMANAGER->addEffect("점프야압", "image/player/jumpEffect(350x70,5x1).bmp", 350, 70, 70, 70, 1.0f, 0.3f, 1);
	EFFECTMANAGER->addEffect("이건이단점프야압", "image/player/doubleJumpEffect(420x70,6x1).bmp", 420, 70, 70, 70, 1.0f, 0.3f, 1);


	//==========적=============
	IMAGEMANAGER->addFrameImage("archerIdleMoveAttack", "image/enemy/archerIdleMoveAttack(810x440,9x4).bmp", 0, 0 , 810, 440, 9, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("arrow", "image/enemy/arrow(120x50,1x1).bmp", 0, 0, 120, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("arrowEffect", "image/enemy/arrowEffect(720x370,3x1).bmp", 0, 0, 720, 370, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bansheeBigBullet", "image/enemy/bansheeBigBullet(480x110,6x1).bmp", 0, 0, 480, 110, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bansheeIdleAttack", "image/enemy/bansheeIdleAttack(600x400,6x4).bmp", 0, 0,  600, 400, 6, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bansheeNormalBullet", "image/enemy/bansheeNormalBullet(280x80,4x1).bmp", 0, 0, 280, 80, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bat", "image/enemy/bat(960x90,7x1).bmp", 0, 0, 960, 90, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bigWhiteSkelAttack", "image/enemy/bigWhiteSkelAttack(2160x340,12x2).bmp", 0, 0, 2160, 340, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bigWhiteSkelIdleMove", "image/enemy/bigWhiteSkelIdleMove(1080x680,6x4).bmp", 0, 0, 1080, 680, 6, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BombBatExplosion", "image/enemy/BombBatExplosion(486x27,18x1).bmp", 0, 0, 486, 27, 18, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bossBack", "image/enemy/bossBack(2400x300,8x1).bmp", 0, 0, 2400, 300, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bossBullet", "image/enemy/bossBullet(650x65,10x1).bmp", 0, 0, 650, 65, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bossHandAttack", "image/enemy/bossHandAttack(5940x700,18x2).bmp", 0, 0, 5940, 700, 18, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bossHandIdle", "image/enemy/bossHandIdle(3300x700,10x2).bmp", 0, 0, 3300, 700, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bossHit", "image/enemy/bossHit(1530x132,5x1).bmp", 0, 0, 1530, 132, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bossHPBar", "image/enemy/bossHPBar(750x100,1x1).bmp", 0, 0, 750, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bossIdleAttackDie", "image/enemy/bossIdleAttackDie(4620x1100,11x2).bmp", 0, 0, 4620, 1100, 11, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bossLaser", "image/enemy/bossLaser(1550x2100,1x7).bmp", 0, 0, 1550, 2100, 1, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bossRedBar", "image/enemy/bossRedBar(750x100,1x1),bmp", 0, 0, 750, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bossSword", "image/enemy/bossSword(1260x390,10x1).bmp", 0, 0, 1260, 390, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("cowIdleChargeAttack", "image/enemy/cowIdleChargeAttack(1840x1320,8x6).bmp", 0, 0, 1840, 1320, 8, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("dieEffect", "image/enemy/dieEffect(4224x384,11x1).bmp", 0, 0, 4224, 384, 11, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("fatherBatBullet", "image/enemy/fatherBatBullet(100x20,5x1).bmp", 0, 0, 100, 20, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("fatherBatBulletFX", "image/enemy/fatherBatBulletFX(396x36,11x1).bmp", 0, 0, 396, 36, 11, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("giantBat", "image/enemy/giantBat(2240x1080,7x6).bmp", 0, 0, 2240, 1080, 7, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("giantRedBatAttack", "image/enemy/giantRedBatAttack(3000x400,10x2).bmp", 0, 0, 3000, 400, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("giantRedBatIdleDie", "image/enemy/giantRedBatIdleDie(2100x600,7x3).bmp", 0, 0, 2100, 600, 7, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("monsterHPBar", "image/enemy/monsterHPBar(80x10,1x1).bmp", 0, 0, 80, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("monsterRedBar", "image/enemy/monsterRedBar(80x10,1x1).bmp", 0, 0, 80, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("redBat", "image/enemy/redBat(1280x180,8x3).bmp", 0, 0, 1280, 180, 8, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("skelBone", "image/enemy/skelBone(480x60,8x1).bmp", 0, 0, 480, 60, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("skelDogIdle", "image/enemy/skelDogIdle(500x180,5x2).bmp", 0, 0, 500, 180, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("skelDogMoveDie", "image/enemy/skelDogMoveDie(700x270,7x3).bmp", 0, 0, 700, 270, 7, 3, true, RGB(255, 0, 255));


	//==========다이얼로그=============
	IMAGEMANAGER->addImage("uiBack", "image/UI/UIdia(1920x400).bmp", 1920, 400, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ansBack", "image/UI/UIdias(400x250).bmp", 400, 250, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ansFront", "image/UI/UIdiac(313x63).bmp", 313, 63, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("uiNext", "image/UI/UIdiaTri(50x70).bmp", 50, 70, true, RGB(255, 0, 255));
	

	
	// ===========아이템 이미지 =============

	// 근거리 무기 이미지
	IMAGEMANAGER->addImage("검10", "image/item/weapon/sword/ShortSword(30x81)1x1.bmp", 30, 96, true, RGB(255, 0, 255)); //착용
	IMAGEMANAGER->addImage("검11", "image/item/weapon/sword/ShortSwordDrop(81x30)1x1.bmp", 96, 30, true, RGB(255, 0, 255)); //드랍
	IMAGEMANAGER->addImage("검12", "image/item/weapon/sword/ShortSwordInven(7x19)1x1.bmp", 10, 32, true, RGB(255, 0, 255)); //인벤

	IMAGEMANAGER->addImage("검20", "image/item/weapon/sword/Muramasa(30x96)1x1.bmp", 30, 96, true, RGB(255, 0, 255)); //착용
	IMAGEMANAGER->addImage("검21", "image/item/weapon/sword/MuramasaDrop(96x30)1x1.bmp", 96, 30, true, RGB(255, 0, 255)); //드랍
	IMAGEMANAGER->addImage("검22", "image/item/weapon/sword/MuramasaInven(10x32)1x1.bmp", 10, 32, true, RGB(255, 0, 255)); //인벤

	IMAGEMANAGER->addImage("검30", "image/item/weapon/sword/FireDragonKiller(40x92)1x1.bmp", 30, 96, true, RGB(255, 0, 255)); //착용
	IMAGEMANAGER->addImage("검31", "image/item/weapon/sword/FireDragonKillerDrop(92x40)1x1.bmp", 96, 30, true, RGB(255, 0, 255)); //드랍
	IMAGEMANAGER->addImage("검32", "image/item/weapon/sword/FireDragonKillerInven(13x30)1x1.bmp", 10, 32, true, RGB(255, 0, 255)); //인벤


	IMAGEMANAGER->addImage("검30", "image/item/weapon/sword/FireDragonKiller(40x92)1x1.bmp", 40, 92, true, RGB(255, 0, 255)); //착용
	IMAGEMANAGER->addImage("검31", "image/item/weapon/sword/FireDragonKillerDrop(92x40)1x1.bmp", 92, 40, true, RGB(255, 0, 255)); //드랍
	IMAGEMANAGER->addImage("검32", "image/item/weapon/sword/FireDragonKillerInven(13x30)1x1.bmp", 13, 30, true, RGB(255, 0, 255)); //인벤

	IMAGEMANAGER->addFrameImage("검40", "image/item/weapon/sword/CosmosSword(360x90)12x1.bmp", 360, 90, 12, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("검41", "image/item/weapon/sword/CosmosSwordDrop(90x30)1x1.bmp", 90, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("검42", "image/item/weapon/sword/CosmosSwordInven(11x30)1x1.bmp", 11, 30, 1, 1, true, RGB(255, 0, 255));



	//원거리무기 이미지 
	IMAGEMANAGER->addImage("총10", "image/item/weapon/gun/deadlyKiss(80x20)1x1.bmp", 80, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("총11", "image/item/weapon/gun/deadlyKissDrop(80x20)1x1.bmp", 80, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("총12", "image/item/weapon/gun/deadlyKissInven(40x10)1x1.bmp", 40, 10, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("총20", "image/item/weapon/gun/matchlockGun(70x18)1x1.bmp", 70, 18, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("총21", "image/item/weapon/gun/matchlockGunDrop(70x18)1x1.bmp", 70, 18, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("총22", "image/item/weapon/gun/matchlockGunInven(27x8)1x1.bmp", 27, 8, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("총30", "image/item/weapon/gun/railGun(600x30)7x1.bmp", 600, 30, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("총31", "image/item/weapon/gun/RailGunInvenDrop(86x30)1x1.bmp", 86, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("총32", "image/item/weapon/gun/RailGunInven(21x9)1x1.bmp", 21, 9, 1, 1, true, RGB(255, 0, 255));


	IMAGEMANAGER->addImage("총40", "image/item/weapon/gun/flameThrower(80x40)1x1.bmp", 80, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("총41", "image/item/weapon/gun/flameThrowerDrop(80x40)1x1.bmp", 80, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("총42", "image/item/weapon/gun/flameThrowerInven(22x11)1x1.bmp", 40, 10, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("활10", "image/item/weapon/bow/Crossbow(100x34)2x1.bmp", 100, 34, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("활11", "image/item/weapon/bow/CrossbowDrop(50x31)1x1.bmp", 50, 31, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("활12", "image/item/weapon/bow/CrossbowDrop(18x11)1x1.bmp", 18, 11, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("활20", "image/item/weapon/bow/darkbow(300x50)6x1.bmp", 300, 50, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("활21", "image/item/weapon/bow/darkbowDrop(50x27)1x1.bmp", 50, 31, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("활22", "image/item/weapon/bow/darkbowInven(17x15)1x1.bmp", 50, 31, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("활30", "image/item/weapon/bow/lightbringer(300x50)6x1.bmp", 300, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("활31", "image/item/weapon/bow/lightbringerDrop(50x22)1x1.bmp", 50, 22, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("활32", "image/item/weapon/bow/CrossbowDrop(50x31)1x1.bmp", 50, 31, true, RGB(255, 0, 255));


	//방패 이미지

	IMAGEMANAGER->addImage("방패10", "image/item/weapon/shield/DashShield(50x45)1x1.bmp", 50, 45, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("방패11", "image/item/weapon/shield/DashShieldDrop(50x45)1x1.bmp", 50, 45, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("방패12", "image/item/weapon/shield/DashShieldInven(28x25)1x1.bmp", 28, 25, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("방패20", "image/item/weapon/shield/HeaterShield(40x65)1x1.bmp", 40, 65, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("방패21", "image/item/weapon/shield/HeaterShieldDrop(65x40)1x1.bmp", 65, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("방패22", "image/item/weapon/shield/HeaterShieldInven(11x18)1x1.bmp", 11, 18, true, RGB(255, 0, 255));



	


	return S_OK;
}