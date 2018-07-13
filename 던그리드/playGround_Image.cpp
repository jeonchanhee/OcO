#include "stdafx.h"
#include "playGround.h"


HRESULT playGround::Image_init(void)
{
	IMAGEMANAGER->addImage("cursor", "image/UI/Cursor(61,70).bmp", 0, 0, 61, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("black", "image/UI/Black(1920x1080).bmp", 0, 0, 1920, 1080, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("gray", "image/UI/gray(1920x1080).bmp", 0, 0, 1920, 1080, false, RGB(255, 0, 255), true);

	IMAGEMANAGER->addFrameImage("map", "image/map/Map(2208x2496,23x26).bmp", 0, 0, 2208, 2496, SAMPLETILEX, SAMPLETILEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("map2", "image/map/Map2(736x832,23x26).bmp", 0, 0, 736, 832, SAMPLETILEX, SAMPLETILEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("floor0", "image/map/Floor0.bmp", 0, 0, 384, 96,true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("floor1", "image/map/Floor1.bmp", 0, 0, 4164, 864,true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("floor2", "image/map/Floor2.bmp", 0, 0, 4164, 864,true, RGB(255, 0, 255));
	

	//==========�⺻UI==========
	IMAGEMANAGER->addImage("hpBar", "image/UI/UIhpBar(469x120).bmp", 0, 0, 469, 120, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("hp", "image/UI/UIhp(294,60).bmp", 0, 0, 294, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("hpb", "image/UI/UIhpb(294,60).bmp", 0, 0, 294, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("dashBar", "image/UI/UIdashBar(400x300,1,5).bmp", 0, 0, 400, 300,1,5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("dash", "image/UI/UIdash(54x24).bmp", 0, 0, 54, 24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("thank", "image/UI/UIresThank.bmp", 0, 0, 317, 76, true, RGB(255, 0, 255));
	

	//==========Ÿ��Ʋ�̹���==========
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
	IMAGEMANAGER->addImage("edge", "image/UI/edge.bmp", 0, 0, 600, 1080, true, RGB(255, 0, 255));
	
	//========�����̹���=========
	IMAGEMANAGER->addImage("setting", "image/UI/Sky_Night(1920x1080).bmp", 1920, 1080, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("exitImage", "image/UI/exitButton(200x100,2x1).bmp", 200, 100, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("soundbar", "image/UI/sounbar(900x50).bmp", 900, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("toggleCheck", "image/UI/toggleCheck(200x100,2x1).bmp", 200, 100, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("soundIcon", "image/UI/soundSetIcon(200x100,2x1).bmp", 200, 100, 2, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("keyIcon", "image/etc/keyboard(432x84,3x1).bmp", 432, 84, 3, 1, true, RGB(255, 0, 255));
	
	//==========��UI=============
	IMAGEMANAGER->addFrameImage("leftDoor", "image/etc/stele_left(384x2304,4x6).bmp", 0, 0, 384, 2304, 4, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("rightDoor", "image/etc/stele_right(384x2304,4x6).bmp", 0, 0, 384, 2304, 4, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("updownDoor", "image/etc/stele(2304x384,6x4).bmp", 0, 0, 2304, 384, 6, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("torch", "image/etc/torch(1200x150,8x1).bmp", 0, 0, 1200, 150, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("dungeonDoor", "image/etc/door(1750x800,5x2).bmp", 0, 0, 1750, 800, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("portal", "image/UI/portal(1296x384,9x2).bmp", 0, 0, 1296, 384, 9, 2, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->addImage("BackSky", "image/UI/BackSky(1920x1080).bmp", 0, 0, 1920, 1080, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BackMountain", "image/UI/BackMountain(2451x1080).bmp", 0, 0, 2451, 1080, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BackForest", "image/UI/BackForest(3638x1080).bmp", 0, 0, 3638, 1080, true, RGB(255, 0, 255));

	//==========�ǹ�==========
	IMAGEMANAGER->addImage("school", "image/UI/A_TrainingSchool(1620x456).bmp", 0, 0, 1620, 456, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("shop", "image/UI/A_Shop(1254,792).bmp", 0, 0, 1254, 792, true, RGB(255, 0, 255));

	//==========�κ��丮==========
	IMAGEMANAGER->addImage("inven", "image/UI/Inventory(707x1080).bmp", 0, 0, 707, 1080, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("inven0", "image/UI/Inven0(270x172).bmp", 0, 0, 270, 172, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("invenRectOff", "image/UI/inventoryM.bmp", 0, 0, 114, 114, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("invenRectOn", "image/UI/UIinvenslot.bmp", 0, 0, 114, 114, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("invenRectOnAc", "image/UI/Inven1(114x114).bmp" , 0, 0, 114, 114, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("mouseOnMain", "image/UI/mainWeaponOnMouse.bmp", 0, 0, 114, 114, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("mouseOnAs", "image/UI/assistWeaponOnMouse.bmp", 0, 0, 114, 114, true, RGB(255, 0, 255));

	//==========Ʈ���̴�==========
	IMAGEMANAGER->addImage("training", "image/UI/UItraning(1920x1080).bmp", 0, 0, 1920, 1080, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("trainI", "image/UI/Ticon(1080x216,15x3).bmp", 0, 0, 1080, 216, 15, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("trainB", "image/UI/UItrainB(535x214,5x2).bmp", 0, 0, 535, 214 ,5 ,2, true, RGB(255, 0, 255));

	//==========����==========
	IMAGEMANAGER->addImage("shopUI", "image/UI/UIshop(720x1080).bmp", 0, 0, 720, 1080, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("slot", "image/UI/UISslot(493x126).bmp", 0, 0, 493, 126, true, RGB(255, 0, 255));

	//==========�������==========
	IMAGEMANAGER->addImage("restaurant", "image/UI/UIrestaurant(1920x1080).bmp", 0, 0, 1920, 1080, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("reslot", "image/UI/UIrestaurantTab(600,270).bmp", 0, 0, 600, 270, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("scroll", "image/UI/UIscroll(42,432).bmp", 0, 0, 42, 432, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("rest", "image/UI/UIrestaurantTable(1146x2142,1,3).bmp", 0, 0, 1146, 2142,1,3, true, RGB(255, 0, 255));

	//=========�����������=========
	IMAGEMANAGER->addImage("d_restaurant", "image/UI/A_DungeonInn(1188x552).bmp", 0, 0, 1188, 552, true, RGB(255, 0, 255));


	//==========Ž������==========
	IMAGEMANAGER->addImage("reward", "image/UI/UIreward(1920x1080).bmp", 0, 0, 1920, 1080, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("expBar", "image/UI/UIexpBar(1920x24).bmp", 0, 0, 1920, 24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("suck", "image/UI/suck(4572x4590,6x9).bmp", 0, 0, 4572, 4590, 6, 9, true, RGB(255, 0, 255));

	//==========�÷��̾�==========
	IMAGEMANAGER->addFrameImage("�⺻�÷��̾�", "image/player/normalPlayer(640x360,8x4).bmp", 640, 360, 8, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addRotateFrameImage("�����÷��̾�", "image/player/princessPlayer(480x320,6x4).bmp", 480, 320, 6, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addRotateImage("�÷��̾��", "image/player/hand(6x6,1x1).bmp", 10, 10, true, RGB(1, 2, 5));
	IMAGEMANAGER->addImage("ü�¹�", "image/player/hpBar(50x50,1x1).bmp", 50, 50, false, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("ü�¹��ⷷ�ⷷ", "image/UI/hpBarWave(120x50,6x1).bmp", 144, 60, 6, 1, true, RGB(255, 0, 255));


	//==========��=============
	IMAGEMANAGER->addFrameImage("skeletonArcher", "image/enemy/skeletonArcher(100X80,2X1).bmp", 0, 0, 100, 80, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addRotateFrameImage("skeletonBow", "image/enemy/skeletonBow2(150X25,6X1).bmp", 150, 25, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addRotateImage("arrow", "image/enemy/arrow(40x10,1x1).bmp", 40, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("arrow2", "image/enemy/arrow(40x10,1x1).bmp", 40, 10, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bansheeIdleAttack", "image/enemy/bansheeIdleAttack(600x440,6x4).bmp", 0, 0,  600, 440, 6, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bansheeNormalBullet", "image/enemy/bansheeNormalBullet(280x80,4x1).bmp", 0, 0, 280, 80, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("batMoveDie", "image/enemy/batMoveDie(1120x180,7x2).bmp", 0, 0, 1120, 180, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bigWhiteSkelAttack", "image/enemy/bigWhiteSkelAttack(2160x340,12x2).bmp", 0, 0, 2520, 600, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bigWhiteSkelIdleMove", "image/enemy/bigWhiteSkelIdleMove(780x680,6x4).bmp", 0, 0, 780, 680, 6, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BombBatExplosion", "image/enemy/BombBatExplosion(486x27,18x1).bmp", 0, 0, 486, 27, 18, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bossBullet", "image/enemy/bossBullet(650x65,10x1).bmp", 0, 0, 650, 65, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bossHand", "image/enemy/bossHand(3300x1400,10x4).bmp", 0, 0, 3300, 1400, 10, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bossHit", "image/enemy/bossHit(1530x132,5x1).bmp", 0, 0, 1530, 132, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bossHPBar", "image/enemy/bossHPBar(750x100,1x1).bmp", 0, 0, 750, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bossIdleAttackDie", "image/enemy/bossIdleAttackDie(4620x1100,11x2).bmp", 0, 0, 4620, 1100, 11, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bossLaser", "image/enemy/bossLaser(1550x2100,1x7).bmp", 0, 0, 1550, 2100, 1, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bossRLaser", "image/enemy/bossRLaser(1550x2100,1x7).bmp", 0, 0, 1550, 2100, 1, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bossRedBar", "image/enemy/bossRedBar(750x100,1x1).bmp", 0, 0, 750, 100, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("bossSword", "image/enemy/bossSword(1260x390,10x1).bmp", 0, 0, 1260, 390, 10, 1, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addRotateFrameImage("RotateBossSword", "image/enemy/bossSword(1260x390,10x1).bmp", 1260, 390, 10, 1, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addRotateImage("RotateBossSword", "image/enemy/sword(390x126,1x1).bmp", 390, 126, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bossSword", "image/enemy/sword(126x390,1x1).bmp", 126, 390, true, RGB(255, 0, 255));
	IMAGEMANAGER->addRotateImage("RotateBossSword", "image/enemy/sword(390x126,1x1).bmp", 390, 126, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("cowIdleChargeAttack", "image/enemy/cowIdleChargeAttack(1840x1320,8x6).bmp", 0, 0, 1840, 1320, 8, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("fatherBatBullet", "image/enemy/fatherBatBullet(100x20,5x1).bmp", 0, 0, 100, 20, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("fatherBatBullet2", "image/enemy/fatherBatBullet(250x50,5x1).bmp", 0, 0, 250, 50, 5, 1, true, RGB(255, 0, 255));
	EFFECTMANAGER->addEffect("fatherBatBulletFX", "image/enemy/fatherBatBulletFX(396x36,11x1).bmp",396, 36, 396/11, 36, 1.0f, 0.3f, 5);
	EFFECTMANAGER->addEffect("fatherBatBulletFX2", "image/enemy/fatherBatBulletFX(550x50,11x1).bmp", 550,50,550/11,50, 1.0f, 0.3f, 5);
	IMAGEMANAGER->addFrameImage("giantBat", "image/enemy/giantBat(2240x1080,7x6).bmp", 0, 0, 2240, 1080, 7, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("giantRedBatAttack", "image/enemy/giantRedBatAttack(3000x400,10x2).bmp", 0, 0, 3000, 400, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("giantRedBatIdleDie", "image/enemy/giantRedBatIdleDie(2100x600,7x3).bmp", 0, 0, 2100, 600, 7, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("monsterHPBar", "image/enemy/monsterHPBar(80x10,1x1).bmp", 0, 0, 80, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("monsterRedBar", "image/enemy/monsterRedBar(80x10,1x1).bmp", 0, 0, 80, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("redBatMoveAttackDie", "image/enemy/redBatMoveAttackDie(1280x450,8x5).bmp", 0, 0, 1280, 450, 8, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("skelBone", "image/enemy/skelBone(480x60,8x1).bmp", 0, 0, 480, 60, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("skelDogIdle", "image/enemy/skelDogIdle(500x180,5x2).bmp", 0, 0, 500, 180, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("skelDogMoveDie", "image/enemy/skelDogMoveDie(700x270,7x3).bmp", 0, 0, 700, 270, 7, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bossBackBullet", "image/enemy/bossBackBullet(1500x115,10x1).bmp", 0, 0, 1750, 160, 10, 1, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("arrowEffect", "image/enemy/arrowEffect(720x370,3x1).bmp", 0, 0, 720, 370, 3, 1, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("bansheeBigBullet", "image/enemy/bansheeBigBullet(480x110,6x1).bmp", 0, 0, 480, 110, 6, 1, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("bossBack", "image/enemy/bossBack(2400x300,8x1).bmp", 0, 0, 2400, 300, 8, 1, true, RGB(255, 0, 255));
	//EFFECTMANAGER->addEffect("bossBack", "image/enemy/bossBack(2400x300,8x1).bmp", 1600, 200, 1600 / 8, 200, 1, 0.1f, 10);
	IMAGEMANAGER->addFrameImage("dieEffect", "image/enemy/dieEffect(4224x384,11x1).bmp", 0, 0, 4224, 384, 11, 1, true, RGB(255, 0, 255));
	EFFECTMANAGER->addEffect("dieEffect", "image/enemy/dieEffect(4224x384,11x1).bmp", 4224, 384, 4224 / 11, 384, 1, 0.1f, 50);
	EFFECTMANAGER->addEffect("bossCollisionBullet", "image/enemy/bossCollisionEffect(1100x100,11x1).bmp", 1100, 100, 1100 / 11, 100, 1.0f, 0.3f, 1);
	EFFECTMANAGER->addEffect("bansheeBigBullet", "image/enemy/bansheeBigBullet(480x110,6x1).bmp", 480, 110, 480 / 6, 110, 1.0f, 0.3f, 1);
	EFFECTMANAGER->addEffect("arrowEffect", "image/enemy/arrowEffect(300x100,3x1).bmp", 300, 100, 300 /3, 100, 1.0f, 0.3f, 1);
	EFFECTMANAGER->addEffect("bossSword", "image/enemy/dieEffect(4224x384,11x1).bmp", 4224, 384, 4224 / 11, 384, 5, 0.3f, 1);

	//==========���̾�α�=============
	IMAGEMANAGER->addImage("uiBack", "image/UI/UIdia(1920x400).bmp", 1920, 400, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ansBack", "image/UI/UIdias(400x250).bmp", 400, 250, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ansFront", "image/UI/UIdiac(313x63).bmp", 313, 63, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("uiNext", "image/UI/UIdiaTri(50x70).bmp", 50, 70, true, RGB(255, 0, 255));
	
	// ============== ������  ================
	// �ٰŸ� ���� �̹���
	//�ٲ� 07 12 	//�ٲ� 07 12 	//�ٲ� 07 12
	IMAGEMANAGER->addImage("��10", "image/item/weapon/sword/ShortSwordDrop(81x30)1x1.bmp", 81, 30, true, RGB(255, 0, 255)); //��� 
	IMAGEMANAGER->addImage("��11", "image/item/weapon/sword/ShortSwordInven(30x80)1x1.bmp", 30, 80, true, RGB(255, 0, 255)); //�κ�
	IMAGEMANAGER->addRotateImage("��12", "image/item/weapon/sword/ShortSword(81x30)1x1.bmp", 81, 30, true, RGB(255, 0, 255)); //����

	IMAGEMANAGER->addImage("��20", "image/item/weapon/sword/MuramasaDrop(96x30)1x1.bmp", 96, 30, true, RGB(255, 0, 255));	//���
	IMAGEMANAGER->addImage("��21", "image/item/weapon/sword/MuramasaInven(28x80)1x1.bmp", 28, 80, true, RGB(255, 0, 255));	//�κ�
	IMAGEMANAGER->addRotateImage("��22", "image/item/weapon/sword/Muramasa(96X30)1x1.bmp", 96, 30, true, RGB(255, 0, 255));	//����

	IMAGEMANAGER->addImage("��30", "image/item/weapon/sword/FireDragonKillerDrop(92x40)1x1.bmp", 92, 40, true, RGB(255, 0, 255));	//���
	IMAGEMANAGER->addImage("��31", "image/item/weapon/sword/FireDragonKillerinven(35x80)1x1.bmp", 35, 80, true, RGB(255, 0, 255));	//�κ�
	IMAGEMANAGER->addRotateImage("��32", "image/item/weapon/sword/FireDragonKiller(92x40)1x1.bmp", 92, 40, true, RGB(255, 0, 255));	//����


	IMAGEMANAGER->addImage("��40", "image/item/weapon/sword/DemonSwordDrop(60x20)1x1.bmp", 60, 20, true, RGB(255, 0, 255));					//���
	IMAGEMANAGER->addImage("��41", "image/item/weapon/sword/DemonSwordInven(27x80)1x1.bmp", 27, 80, true, RGB(255, 0, 255));					//�κ�
	IMAGEMANAGER->addRotateImage("��42", "image/item/weapon/sword/DemonSword(60x20)1x1.bmp", 60, 20, true, RGB(255, 0, 255));					//����

	IMAGEMANAGER->addImage("��50", "image/item/weapon/sword/CosmosSwordDrop(90x30)1x1.bmp", 90, 30, true, RGB(255, 0, 255));					// ���
	IMAGEMANAGER->addImage("��51", "image/item/weapon/sword/CosmosSwordInven(27x80)1x1.bmp", 27, 80, true, RGB(255, 0, 255));				// �κ�
	IMAGEMANAGER->addRotateImage("��52", "image/item/weapon/sword/CosmosSword(90x30)1x1.bmp", 90, 30, true, RGB(255, 0, 255));					// ����
	
	IMAGEMANAGER->addImage("��60", "image/item/weapon/sword/EternalSwordDrop(123x50)1x1.bmp", 123, 50, true, RGB(255, 0, 255));				// ���
	IMAGEMANAGER->addImage("��61", "image/item/weapon/sword/EternalSwordInven(33x80)1x1.bmp", 33, 80, true, RGB(255, 0, 255));				// �κ�
	IMAGEMANAGER->addRotateImage("��62", "image/item/weapon/sword/EternalSword(123x50)1x1.bmp", 123, 50, true, RGB(255, 0, 255));			// ����

	IMAGEMANAGER->addImage("��70", "image/item/weapon/sword/BloodStoneSwordDrop(73x30)1x1.bmp", 73, 30, true, RGB(255, 0, 255));				// ���
	IMAGEMANAGER->addImage("��71", "image/item/weapon/sword/BloodStoneSwordInven(33x80)1x1.bmp", 33, 80, true, RGB(255, 0, 255));				// �κ�
	IMAGEMANAGER->addRotateImage("��72", "image/item/weapon/sword/BloodStoneSword(73x30)1x1.bmp", 73, 30, true, RGB(255, 0, 255));			// ����

	IMAGEMANAGER->addImage("��80", "image/item/weapon/sword/bossSwordDrop(93x30)1x1.bmp", 93, 30, true, RGB(255, 0, 255));					// ���
	IMAGEMANAGER->addImage("��81", "image/item/weapon/sword/BossSwordInven(38x80)1x1.bmp", 38, 80, true, RGB(255, 0, 255));					// �κ�
	IMAGEMANAGER->addRotateImage("��82", "image/item/weapon/sword/bossSword(93x30)1x1.bmp", 93, 30, true, RGB(255, 0, 255));					// ����

	IMAGEMANAGER->addImage("��90", "image/item/weapon/sword/RapierOfSuperSpeedDrop(115x30)1x1.bmp", 115, 30, true, RGB(255, 0, 255));		// ���
	IMAGEMANAGER->addImage("��91", "image/item/weapon/sword/RapierOfSuperSpeedInven(21x80)1x1.bmp", 21, 80, true, RGB(255, 0, 255));			// �κ�
	IMAGEMANAGER->addRotateImage("��92", "image/item/weapon/sword/RapierOfSuperSpeed(115x30)1x1.bmp", 115, 30, true, RGB(255, 0, 255));		// ����

	IMAGEMANAGER->addImage("��100", "image/item/weapon/sword/VineSwordDrop(131x47)1x1.bmp", 131, 47, true, RGB(255, 0, 255));				// ���
	IMAGEMANAGER->addImage("��101", "image/item/weapon/sword/VineSwordInven(30x80)1x1.bmp", 30, 80, true, RGB(255, 0, 255));					// �κ�
	IMAGEMANAGER->addRotateImage("��102", "image/item/weapon/sword/VineSword(131x47)1x1.bmp", 131, 47, true, RGB(255, 0, 255));				// ����
	//�ٲ� 07 12
	// =================S=T==A==R==T==========================================
	//�ٲ� 07 12
	IMAGEMANAGER->addImage("�ظ�10", "image/item/weapon/hammer/SteelWarHammerDrop(85x50)1x1.bmp", 85, 50, true, RGB(255, 0, 255));	//���
	IMAGEMANAGER->addImage("�ظ�11", "image/item/weapon/hammer/SteelWarHammerInven(50x80)1x1.bmp", 50, 80, true, RGB(255, 0, 255));	//�κ�
	IMAGEMANAGER->addImage("�ظ�12", "image/item/weapon/hammer/SteelWarHammerRight(50x85)1x1.bmp", 50, 85, true, RGB(255, 0, 255));	//����
	


	IMAGEMANAGER->addImage("�ظ�20", "image/item/weapon/hammer/DragonHammerDrop(79x50)1x1.bmp", 79, 50, true, RGB(255, 0, 255));		//���
	IMAGEMANAGER->addImage("�ظ�21", "image/item/weapon/hammer/DragonHammerInven(50x80)1x1.bmp", 50, 80, true, RGB(255, 0, 255));	//�κ�
	IMAGEMANAGER->addRotateImage("�ظ�22", "image/item/weapon/hammer/DragonHammer(50x79)1x1.bmp", 50, 79, true, RGB(255, 0, 255));	//����


	//���Ÿ����� �̹��� 
	//��ȣ��	//�ٲ� 07 12



	IMAGEMANAGER->addRotateImage("��1��", "image/item/weapon/gun/matchlockGunLeft(100x30)1x1.bmp", 100, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addRotateImage("��1��", "image/item/weapon/gun/matchlockGunRight(100x30)1x1.bmp", 100, 30, true, RGB(255, 0, 255));

	IMAGEMANAGER->addRotateImage("��2��", "image/item/weapon/gun/deadlyKissLeft(100x25)1x1.bmp", 100, 25, true, RGB(255, 0, 255));	
	IMAGEMANAGER->addRotateImage("��2��", "image/item/weapon/gun/deadlyKissRight(100x25)1x1.bmp", 100, 25, true, RGB(255, 0, 255));	

	IMAGEMANAGER->addRotateImage("��3��", "image/item/weapon/gun/flameThrowerLeft(100x50)1x1.bmp", 100, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addRotateImage("��3��", "image/item/weapon/gun/flameThrowerRight(100x50)1x1.bmp", 100, 50, true, RGB(255, 0, 255));

	IMAGEMANAGER->addRotateFrameImage("��4��", "image/item/weapon/gun/railGunLeft(600x30)7x1.bmp", 600, 30 , 7 , 1 , true, RGB(255, 0, 255));
	IMAGEMANAGER->addRotateFrameImage("��4��", "image/item/weapon/gun/railGunRight(600x30)7x1.bmp", 600, 30, 7 , 1 , true, RGB(255, 0, 255));

	//�ǵ�����3	//�ٲ� 07 12

	IMAGEMANAGER->addImage("��10", "image/item/weapon/gun/matchlockGunDrop(70x18)1x1.bmp", 70, 18, true, RGB(255, 0, 255));			// ���
	IMAGEMANAGER->addImage("��11", "image/item/weapon/gun/MatchlockGunInven(80x24)1x1.bmp", 80, 24, true, RGB(255, 0, 255));			// �κ�
	IMAGEMANAGER->addRotateImage("��12", "image/item/weapon/gun/matchlockGun(70x18)1x1.bmp", 70, 18, true, RGB(255, 0, 255));		// ����
	

	IMAGEMANAGER->addImage("��20", "image/item/weapon/gun/deadlyKissDrop(80x20)1x1.bmp", 80, 20, true, RGB(255, 0, 255));			// ���
	IMAGEMANAGER->addImage("��21", "image/item/weapon/gun/deadlyKissInven(80x20)1x1.bmp", 80, 20, true, RGB(255, 0, 255));			// �κ�
	IMAGEMANAGER->addRotateImage("��22", "image/item/weapon/gun/deadlyKiss(80x20)1x1.bmp", 80, 20, true, RGB(255, 0, 255));			// ����

	IMAGEMANAGER->addImage("��30", "image/item/weapon/gun/flameThrowerDrop(80x40)1x1.bmp", 80, 40, true, RGB(255, 0, 255));			// ���
	IMAGEMANAGER->addImage("��31", "image/item/weapon/gun/FlameThrowerInven(80x40)1x1.bmp", 80, 40, true, RGB(255, 0, 255));			// �κ�
	IMAGEMANAGER->addRotateImage("��32", "image/item/weapon/gun/flameThrower(80x40)1x1.bmp", 80, 40, true, RGB(255, 0, 255));		// ����

	IMAGEMANAGER->addImage("��40", "image/item/weapon/gun/RailGunInvenDrop(86x30)1x1.bmp", 86, 30, true, RGB(255, 0, 255));					// ���
	IMAGEMANAGER->addImage("��41", "image/item/weapon/gun/RailGunInven(80x34)1x1.bmp", 80, 34, true, RGB(255, 0, 255));						// �κ�
	IMAGEMANAGER->addRotateFrameImage("��42", "image/item/weapon/gun/railGun(600x30)7x1.bmp", 600, 30, 7, 1, true, RGB(255, 0, 255));		// ����

	//�ٲ�018 07 12	//�ٲ� 07 12
	IMAGEMANAGER->addImage("Ȱ10", "image/item/weapon/bow/CrossbowDrop(50x31)1x1.bmp", 50, 31, true, RGB(255, 0, 255));						// ���
	IMAGEMANAGER->addImage("Ȱ11", "image/item/weapon/bow/CrossbowInven(80x50)1x1.bmp", 80, 50, true, RGB(255, 0, 255));						// �κ�
	IMAGEMANAGER->addRotateFrameImage("Ȱ12", "image/item/weapon/bow/Crossbow(100x34)2x1.bmp", 100, 34, 2, 1, true, RGB(255, 0, 255));		// ����

	IMAGEMANAGER->addImage("Ȱ20", "image/item/weapon/bow/darkbowDrop(50x27)1x1.bmp", 50, 27, true, RGB(255, 0, 255));						// ��� 
	IMAGEMANAGER->addImage("Ȱ21", "image/item/weapon/bow/DarkBowInven(91x80)1x1.bmp", 91, 80, true, RGB(255, 0, 255));						// �κ�
	IMAGEMANAGER->addRotateFrameImage("Ȱ22", "image/item/weapon/bow/darkbow(420x70)6x1.bmp", 420, 70, 6, 1, true, RGB(255, 0, 255));		// ����

	IMAGEMANAGER->addImage("Ȱ30", "image/item/weapon/bow/lightbringerDrop(50x22)1x1.bmp", 50, 22, true, RGB(255, 0, 255));					// ���
	IMAGEMANAGER->addImage("Ȱ31", "image/item/weapon/bow/lightbringerInven(35x80)1x1.bmp", 35, 80, true, RGB(255, 0, 255));					// �κ�
	IMAGEMANAGER->addRotateFrameImage("Ȱ32", "image/item/weapon/bow/lightbringer(300x50)6x1.bmp", 300, 50, 6, 1, true, RGB(255, 0, 255));	// ����
	




	//�������� �������� �������� �������� �������� �������� �������� �������� ��������
	IMAGEMANAGER->addRotateFrameImage("�Ѿ�0", "image/item/weapon/gun/matchlockGunBullet(5x1).bmp",750,30,5,1,true , RGB(255,0,255));
	IMAGEMANAGER->addRotateFrameImage("�Ѿ�1", "image/item/weapon/gun/deadlyKissBullet(1200x110,12x1).bmp",1000,92,12,1,true, RGB(255,0,255 ));
	IMAGEMANAGER->addRotateFrameImage("�Ѿ�2", "image/item/weapon/gun/flameThrower(400x125,8x1).bmp",400,125,8,1,true, RGB(255 , 0 , 255));
	IMAGEMANAGER->addRotateFrameImage("�Ѿ�3", "image/item/weapon/gun/railGunBullet(300x100,6x1).bmp",300,100,6,1,true, RGB(255,0,255 ));
	IMAGEMANAGER->addRotateImage("ȭ��", "image/item/weapon/bow/Ȱ ����Ʈ/arrow.bmp", 50, 5, true, RGB(255, 0, 255));

		
	// �� �̹���


	IMAGEMANAGER->addImage("�Ƹ�10", "image/item/armor/ClothArmorDrop(30x27)1x1.bmp", 30, 27, true, RGB(255, 0, 255));	// ���
	IMAGEMANAGER->addImage("�Ƹ�11", "image/item/armor/ClothArmorInven(80x72)1x1.bmp", 80, 72, true, RGB(255, 0, 255));	// �κ�
	
	IMAGEMANAGER->addImage("�Ƹ�20", "image/item/armor/LeatherArmorDrop(30x24)1x1.bmp", 30, 24, true, RGB(255, 0, 255));		// ���
	IMAGEMANAGER->addImage("�Ƹ�21", "image/item/armor/LeatherArmorInven(80x64)1x1.bmp", 80, 64, true, RGB(255, 0, 255));	// �κ�
	
	IMAGEMANAGER->addImage("�Ƹ�30", "image/item/armor/CowLeatherDrop(30x24)1x1.bmp", 30, 24, true, RGB(255, 0, 255));	// ���
	IMAGEMANAGER->addImage("�Ƹ�31", "image/item/armor/CowLeatherInven(80x64)1x1.bmp", 80, 64, true, RGB(255, 0, 255));	// �κ�
	
	IMAGEMANAGER->addImage("�Ƹ�40", "image/item/armor/ChainArmorDrop(30x30)1x1.bmp", 30, 30, true, RGB(255, 0, 255));	// ���
	IMAGEMANAGER->addImage("�Ƹ�41", "image/item/armor/ChainArmorInven(80x80)1x1.bmp", 80, 80, true, RGB(255, 0, 255));	// �κ�
	

	IMAGEMANAGER->addImage("����10", "image/item/shield/HeaterShieldDrop(65x40)1x1.bmp", 65, 40, true, RGB(255, 0, 255));		// ���
	IMAGEMANAGER->addImage("����11", "image/item/shield/HeaterShieldInven(50x80)1x1.bmp", 50 , 80, true, RGB(255, 0, 255));	// �κ�
	IMAGEMANAGER->addImage("����12", "image/item/shield/HeaterShield(40x65)1x1.bmp", 40, 65, true, RGB(255, 0, 255));			// ����

	IMAGEMANAGER->addImage("����20", "image/item/shield/DashShieldDrop(50x45)1x1.bmp", 50, 45, true, RGB(255, 0, 255));		// ���
	IMAGEMANAGER->addImage("����21", "image/item/shield/DashShieldInven(80x71)1x1.bmp", 80, 71, true, RGB(255, 0, 255));		// �κ�
	IMAGEMANAGER->addImage("����22", "image/item/shield/DashShield(50x45)1x1.bmp", 50, 45, true, RGB(255, 0, 255));			// ����




	//�Ǽ��縮 �̹���(���� ���/ ����/ ��)
	IMAGEMANAGER->addImage("����10", "image/item/second/BlessOfSageDrop(20x20)1x1.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����11", "image/item/second/BlessOfSageInven(55x80)1x1.bmp", 55, 80, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("����20", "image/item/second/BloodOfSrobeoDrop(25x31)1x1.bmp", 25, 31, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����21", "image/item/second/BloodOfSrobeoInven(65x80)1x1.bmp", 65, 80, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("����30", "image/item/second/WingDrop(30x21)1x1.bmp", 30, 21, true, RGB(255, 0, 255));			// ���
	IMAGEMANAGER->addImage("����31", "image/item/second/WingInven(80x56)1x1.bmp", 80, 56, true, RGB(255, 0, 255));			// �κ�
	IMAGEMANAGER->addFrameImage("����32", "image/item/second/Wing(350x43)7x1.bmp", 350, 43, 7, 1, true, RGB(255, 0, 255));	// ����

	IMAGEMANAGER->addImage("����40", "image/item/second/MartialArtOfTigerDrop(30x25)1x1.bmp", 30, 25, true, RGB(255, 0, 255));			// ���
	IMAGEMANAGER->addImage("����41", "image/item/second/MartialArtOfTigerInven(80x67)1x1.bmp", 80, 67, true, RGB(255, 0, 255));			// �κ�
	IMAGEMANAGER->addFrameImage("����42", "image/item/second/MartialArtOfTiger(441x49)9x1.bmp", 441, 49, 9, 1, true, RGB(255, 0, 255));	// ����

	IMAGEMANAGER->addImage("�Ǽ�10", "image/item/accessory/BloodStoneRingDrop(30x35)1x1.bmp", 30, 35, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�Ǽ�11", "image/item/accessory/BloodStoneRingInven(69x80)1x1.bmp", 69, 80, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("�Ǽ�20", "image/item/accessory/EnvirokEpauletDrop(30x29)1x1.bmp", 30, 29, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�Ǽ�21", "image/item/accessory/EnvirokEpauletInven(80x77)1x1.bmp", 80, 77, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("�Ǽ�30", "image/item/accessory/FrostChockerDrop(30x28)1x1.bmp", 30, 28, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�Ǽ�31", "image/item/accessory/FrostChockerInven(80x75)1x1.bmp", 80, 75, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("�Ǽ�40", "image/item/accessory/GerberaRingDrop(30x34)1x1.bmp", 30, 34, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�Ǽ�41", "image/item/accessory/GerberaRingInven(71x80)1x1.bmp", 71, 80, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("��10", "image/item/pet/petDrop(95x22)5x1.bmp", 95, 22, 5, 1, true, RGB(255, 0, 255));	// ���
	IMAGEMANAGER->addImage("��11", "image/item/pet/petInven(69x80)1x1.bmp", 69, 80, true, RGB(255, 0, 255));				// �κ�
	IMAGEMANAGER->addFrameImage("��12", "image/item/pet/pet(240x22)12x1.bmp", 240, 22, 12, 1, true, RGB(255, 0, 255));	// ����


	//���� �̹���
	IMAGEMANAGER->addImage("����10", "image/item/food/01_bread(73x30)1x1.bmp", 438, 180, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����11", "image/item/food/02_FriedEgg(73x30)1x1.bmp", 438, 180, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����12", "image/item/food/03_grilledMushroom(73x30)1x1.bmp", 438, 180, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����20", "image/item/food/04_TamatoSoup(73x30)1x1.bmp", 438, 180, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����21", "image/item/food/05_OnionSoup(73x30)1x1.bmp", 438, 180, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����22", "image/item/food/06_VegetableSalsaSoup(73x30)1x1.bmp", 438, 180, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����30", "image/item/food/07_ChocolateCookie(73x30)1x1.bmp", 438, 180, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����31", "image/item/food/08_RaspberryCookie(73x30)1x1.bmp", 438, 180, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����32", "image/item/food/09_GriffonEggOmelette(73x30)1x1.bmp", 438, 180, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����40", "image/item/food/10_DeluxeBurger(73x48)1x1.bmp", 438, 288, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����41", "image/item/food/11_HotChickenStew(73x35)1x1.bmp", 438, 210, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����42", "image/item/food/12_MinotaursSteak(73x32)1x1.bmp", 438, 192, true, RGB(255, 0, 255));

	//�������� �̹���
	IMAGEMANAGER->addFrameImage("����1", "image/item/healing/heal1(216x24)9x1.bmp", 216, 24, 9, 1, true, RGB(255, 0, 255));		// ������ �̹���
	IMAGEMANAGER->addFrameImage("����2", "image/item/healing/heal2(480x30)16x1.bmp", 480, 30, 16, 1, true, RGB(255, 0, 255));	// ������ �̹���


	//�ڽ� / ���� �̹���

	IMAGEMANAGER->addFrameImage("��������1", "image/item/treasurebox/bossbox(80x28)2x1.bmp", 80, 28, 2, 1, true, RGB(255, 0, 255));	//������
	IMAGEMANAGER->addFrameImage("�Ϲݻ���1", "image/item/treasurebox/coinbox(54x16)2x1.bmp", 80 * 4, 28 * 4, 2, 1, true, RGB(255, 0, 255));	//������
	
	IMAGEMANAGER->addFrameImage("����1", "image/item/treasurebox/coin(56x7)8x1.bmp", 56, 7, 8, 1, true, RGB(255, 0, 255));		// ������
	IMAGEMANAGER->addFrameImage("���1", "image/item/treasurebox/gold(140x9)7x1.bmp", 140, 9, 7, 1, true, RGB(255, 0, 255));		// ������

	//Effect
	EFFECTMANAGER->addEffect("��ÿ���", "image/player/dashManLeft(320x95,4x1).bmp", 320, 95, 80, 95, 1.0f, 0.3f, 5);
	EFFECTMANAGER->addEffect("��ÿ�����", "image/player/dashManRight(320x95,4x1).bmp", 320, 95, 80, 95, 1.0f, 0.3f, 5);
	EFFECTMANAGER->addEffect("���ʰ�����", "image/player/leftRunDust(200x40,5x1).bmp", 250, 50, 50, 50, 1.0f, 0.3f, 1);
	EFFECTMANAGER->addEffect("�����ʰ�����", "image/player/rightRunDust(200x40,5x1).bmp", 250, 50, 50, 50, 1.0f, 0.3f, 1);
	EFFECTMANAGER->addEffect("�����߾�", "image/player/jumpEffect(350x70,5x1).bmp", 350, 70, 70, 70, 1.0f, 0.3f, 1);
	EFFECTMANAGER->addEffect("�̰��̴������߾�", "image/player/doubleJumpEffect(420x70,6x1).bmp", 420, 70, 70, 70, 1.0f, 0.3f, 1);
	//sword Effect 
	IMAGEMANAGER->addRotateFrameImage("��1ȿ��", "image/item/weapon/sword/effect/swing(600x109,4x1).bmp", 600 , 109 , 4 , 1, true , RGB(255,0,255));
	IMAGEMANAGER->addRotateFrameImage("��2ȿ��", "image/item/weapon/sword/effect/fireswing(800x91,7x1).bmp", 800, 91, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addRotateFrameImage("��3ȿ��", "image/item/weapon/sword/effect/emeraldEffect(900x93,7x1).bmp", 900, 93, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addRotateFrameImage("��4ȿ��", "image/item/weapon/sword/effect/bossSwordEffect(600x100,4x1).bmp", 600 , 100 , 4 , 1, true , RGB(255,0,255));


	//���� NPC
	IMAGEMANAGER->addFrameImage("���ǽ�1", "image/npc/inn(420x200)6x2.bmp", 420, 200 , 6, 2, true, RGB(255, 0, 255)); // �����Ĵ� ���ܸ�
	IMAGEMANAGER->addFrameImage("���ǽ�2", "image/npc/weaponNPC(800x392)4x2.bmp", 800, 392, 4, 2, true, RGB(255, 0, 255)); // ��� �Ǹ��ϴ� ������
	IMAGEMANAGER->addFrameImage("N������", "image/npc/merchant(700x400,7x4).bmp", 560, 360, 7, 4, true, RGB(255, 0, 255)); 
	IMAGEMANAGER->addFrameImage("NƮ���̳�", "image/npc/commander(700x400,7x4).bmp", 700, 400, 7, 4, true, RGB(255, 0, 255)); 
	IMAGEMANAGER->addFrameImage("N����", "image/npc/elder(700x400,7x4).bmp", 700, 400, 7, 4, true, RGB(255, 0, 255));


	//�̴ϸ�
	IMAGEMANAGER->addImage("playerIcon", "image/icon/playerIcon(20x20).bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("npcIcon", "image/icon/npcIcon(20x20).bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("enemyIcon", "image/icon/enemyIcon(20x20).bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("portalIcon", "image/icon/worm(80x40,2x1).bmp", 80, 40, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("heightDoorIcon", "image/icon/heightDoorIcon(10x50).bmp", 10, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("tabMap1", "image/icon/tabMap(1920x1080).bmp", 1920,1080,true,RGB(255,0,255));
	IMAGEMANAGER->addImage("tabMap2", "image/icon/tabMap2(1920x1080,1x1).bmp", 1920, 1080, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("tabMap3", "image/icon/tabMap3(1920x1080,1x1).bmp", 1920, 1080, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("tabMap4", "image/icon/tabMap4(1920x1080,1x1).bmp", 1920, 1080, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("minimap0", "image/icon/minimap1(120x120).bmp", 120, 120, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("minimap9", "image/icon/minimap2(120x120).bmp", 120, 120, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("minimap1", "image/icon/minimap3(120x120).bmp", 120, 120, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("minimap2", "image/icon/minimap4(120x120).bmp", 120, 120, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("minimap3", "image/icon/minimap5(120x120).bmp", 120, 120, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("minimap4", "image/icon/minimap6(120x120).bmp", 120, 120, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("minimap5", "image/icon/minimap7(120x120).bmp", 120, 120, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("minimap6", "image/icon/minimap8(120x120).bmp", 120, 120, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("minimap7", "image/icon/minimap9(120x120).bmp", 120, 120, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("minimap10", "image/icon/minimap11(120x120).bmp", 120, 120, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("minimap8", "image/icon/minimapBoss(120x120).bmp", 120, 120, true, RGB(255, 0, 255));
	//�ȼ�
	IMAGEMANAGER->addImage("pixel", 4800, 2400);

	//f��ư

	IMAGEMANAGER->addImage("f��ư", "image/icon/Keyboard_F(50x54)1x1.bmp", 50, 54, true, RGB(255, 0, 255));

	//========�ӽ÷� �ִϸ��̼� �߰���!==============
	KEYANIMANAGER->addDefaultFrameAnimation("torchAni", "torch", 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("portalAni", "portal", 9, 17, 10, false, true);
	return S_OK;
}