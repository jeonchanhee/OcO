#include "stdafx.h"
#include "playGround.h"


HRESULT playGround::Image_init(void)
{
	IMAGEMANAGER->addImage("cursor", "image/UI/Cursor(61,70).bmp", 0, 0, 61, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("black", "image/UI/Black(1920x1080).bmp", 0, 0, 1920, 1080, true, RGB(255, 0, 255), true);

	IMAGEMANAGER->addFrameImage("map", "image/map/Map(2208x2496,23x26).bmp", 0, 0, 2208, 2496, SAMPLETILEX, SAMPLETILEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("map2", "image/map/Map2(736x832,23x26).bmp", 0, 0, 736, 832, SAMPLETILEX, SAMPLETILEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("floor0", "image/map/Floor0.bmp", 0, 0, 384, 96,true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("floor1", "image/map/Floor1.bmp", 0, 0, 4164, 864,true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("floor2", "image/map/Floor2.bmp", 0, 0, 4164, 864,true, RGB(255, 0, 255));

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

	//==========��UI=============
	IMAGEMANAGER->addFrameImage("leftDoor", "image/etc/stele_left(384x2304,4x6).bmp", 0, 0, 384, 2304, 4, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("rightDoor", "image/etc/stele_right(384x2304,4x6).bmp", 0, 0, 384, 2304, 4, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("updownDoor", "image/etc/stele(2304x384,6x4).bmp", 0, 0, 2304, 384, 6, 4, true, RGB(255, 0, 255));
	//==========�κ��丮==========
	IMAGEMANAGER->addImage("inven", "image/UI/Inventory(707x1080).bmp", 0, 0, 707, 1080, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("inven0", "image/UI/Inven0(270x172).bmp", 0, 0, 270, 172, true, RGB(255, 0, 255));

	//==========Ʈ���̴�==========
	IMAGEMANAGER->addImage("training", "image/UI/UItraning(1920x1080).bmp", 0, 0, 1920, 1080, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("trainI", "image/UI/Ticon(1080x216,15x3).bmp", 0, 0, 1080, 216, 15, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("trainB", "image/UI/UItrainB(535x214,5x2).bmp", 0, 0, 535, 214 ,5 ,2, true, RGB(255, 0, 255));

	//==========����==========
	IMAGEMANAGER->addImage("shop", "image/UI/UIshop(720x1080).bmp", 0, 0, 720, 1080, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("slot", "image/UI/UISslot(493x126).bmp", 0, 0, 493, 126, true, RGB(255, 0, 255));

	//==========�������==========
	IMAGEMANAGER->addImage("restaurant", "image/UI/UIrestaurant(1920x1080).bmp", 0, 0, 1920, 1080, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("reslot", "image/UI/UIrestaurantTab(600,270).bmp", 0, 0, 600, 270, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("scroll", "image/UI/UIscroll(42,432).bmp", 0, 0, 42, 432, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("rest", "image/UI/UIrestaurantTable(1146x2142,1,3).bmp", 0, 0, 1146, 2142,1,3, true, RGB(255, 0, 255));

	//==========Ž������==========
	IMAGEMANAGER->addImage("reward", "image/UI/UIreward(1920x1080).bmp", 0, 0, 1920, 1080, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("expBar", "image/UI/UIexpBar(1920x24).bmp", 0, 0, 1920, 24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("suck", "image/UI/suck(4572x4590,6x9).bmp", 0, 0, 4572, 4590, 6, 9, true, RGB(255, 0, 255));

	//==========�÷��̾�==========
	IMAGEMANAGER->addFrameImage("�⺻�÷��̾�", "image/player/normalPlayer(640x360,8x4).bmp", 640, 360, 8, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addRotateFrameImage("�����÷��̾�", "image/player/princessPlayer(480x320,6x4).bmp", 480, 320, 6, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addRotateImage("�÷��̾��", "image/player/hand(6x6,1x1).bmp", 10, 10, true, RGB(1, 2, 5));
	IMAGEMANAGER->addImage("ü�¹�", "image/player/hpBar(50x50,1x1).bmp", 50, 50, false, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("ü�¹��ⷷ�ⷷ", "image/player/hpBarWave(120x50,6x1).bmp", 120, 50, 6, 1, true, RGB(255, 0, 255));


	//==========��=============
	IMAGEMANAGER->addFrameImage("skeletonArcher", "image/enemy/skeletonArcher(100X80,2X1).bmp", 0, 0, 100, 80, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addRotateFrameImage("skeletonBow", "image/enemy/skeletonBow2(150X25,6X1).bmp", 150, 25, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addRotateImage("arrow", "image/enemy/arrow(40x10,1x1).bmp", 40, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("arrowEffect", "image/enemy/arrowEffect(720x370,3x1).bmp", 0, 0, 720, 370, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bansheeBigBullet", "image/enemy/bansheeBigBullet(480x110,6x1).bmp", 0, 0, 480, 110, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bansheeIdleAttack", "image/enemy/bansheeIdleAttack(600x440,6x4).bmp", 0, 0,  600, 440, 6, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bansheeNormalBullet", "image/enemy/bansheeNormalBullet(280x80,4x1).bmp", 0, 0, 280, 80, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("batMoveDie", "image/enemy/batMoveDie(1120x180,7x2).bmp", 0, 0, 1120, 180, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bigWhiteSkelAttack", "image/enemy/bigWhiteSkelAttack(2160x340,12x2).bmp", 0, 0, 2520, 600, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bigWhiteSkelIdleMove", "image/enemy/bigWhiteSkelIdleMove(780x680,6x4).bmp", 0, 0, 780, 680, 6, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BombBatExplosion", "image/enemy/BombBatExplosion(486x27,18x1).bmp", 0, 0, 486, 27, 18, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bossBack", "image/enemy/bossBack(2400x300,8x1).bmp", 0, 0, 2400, 300, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bossBullet", "image/enemy/bossBullet(650x65,10x1).bmp", 0, 0, 650, 65, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bossHand", "image/enemy/bossHand(5940x1400,18x4).bmp", 0, 0, 5940, 1400, 18, 4, true, RGB(255, 0, 255));
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
	IMAGEMANAGER->addFrameImage("redBatMoveAttackDie", "image/enemy/redBatMoveAttackDie(1280x450,8x5).bmp", 0, 0, 1280, 450, 8, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("skelBone", "image/enemy/skelBone(480x60,8x1).bmp", 0, 0, 480, 60, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("skelDogIdle", "image/enemy/skelDogIdle(500x180,5x2).bmp", 0, 0, 500, 180, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("skelDogMoveDie", "image/enemy/skelDogMoveDie(700x270,7x3).bmp", 0, 0, 700, 270, 7, 3, true, RGB(255, 0, 255));


	//==========���̾�α�=============
	IMAGEMANAGER->addImage("uiBack", "image/UI/UIdia(1920x400).bmp", 1920, 400, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ansBack", "image/UI/UIdias(400x250).bmp", 400, 250, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ansFront", "image/UI/UIdiac(313x63).bmp", 313, 63, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("uiNext", "image/UI/UIdiaTri(50x70).bmp", 50, 70, true, RGB(255, 0, 255));
	
	// ============== ������  ================
	// �ٰŸ� ���� �̹���

	IMAGEMANAGER->addImage("��10", "image/item/weapon/sword/ShortSwordDrop(81x30)1x1.bmp", 81, 30, true, RGB(255, 0, 255)); //��� 
	IMAGEMANAGER->addImage("��11", "image/item/weapon/sword/ShortSwordInven(7x19)1x1.bmp", 7, 19, true, RGB(255, 0, 255)); //�κ�
	IMAGEMANAGER->addRotateImage("��12", "image/item/weapon/sword/ShortSword(81x30)1x1.bmp", 81, 30, true, RGB(255, 0, 255)); //����

	IMAGEMANAGER->addImage("��20", "image/item/weapon/sword/MuramasaDrop(96x30)1x1.bmp", 96, 30, true, RGB(255, 0, 255));	//���
	IMAGEMANAGER->addImage("��21", "image/item/weapon/sword/MuramasaInven(10x32)1x1.bmp", 10, 32, true, RGB(255, 0, 255));	//�κ�
	IMAGEMANAGER->addRotateImage("��22", "image/item/weapon/sword/Muramasa(30X96)1x1.bmp", 30, 96, true, RGB(255, 0, 255));	//����

	IMAGEMANAGER->addImage("��30", "image/item/weapon/sword/FireDragonKillerDrop(92x40)1x1.bmp", 92, 40, true, RGB(255, 0, 255));	//���
	IMAGEMANAGER->addImage("��31", "image/item/weapon/sword/FireDragonKillerinven(13x30)1x1.bmp", 13, 30, true, RGB(255, 0, 255));	//�κ�
	IMAGEMANAGER->addRotateImage("��32", "image/item/weapon/sword/FireDragonKiller(40x92)1x1.bmp", 40, 92, true, RGB(255, 0, 255));	//����


	IMAGEMANAGER->addImage("��40", "image/item/weapon/sword/DemonSwordDrop(60x20)1x1.bmp", 60, 20, true, RGB(255, 0, 255));					//���
	IMAGEMANAGER->addImage("��41", "image/item/weapon/sword/DemonSwordInven(20x60)1x1.bmp", 20, 60, true, RGB(255, 0, 255));					//�κ�
	IMAGEMANAGER->addRotateFrameImage("��42", "image/item/weapon/sword/DemonSword(216x80)9x1.bmp", 216, 80, 9, 1, true, RGB(255, 0, 255));	//����

	IMAGEMANAGER->addImage("��50", "image/item/weapon/sword/CosmosSwordDrop(90x30)1x1.bmp", 90, 30, true, RGB(255, 0, 255));						// ���
	IMAGEMANAGER->addImage("��51", "image/item/weapon/sword/CosmosSwordInven(11x33)1x1.bmp", 11, 33, true, RGB(255, 0, 255));				// �κ�
	IMAGEMANAGER->addRotateFrameImage("��52", "image/item/weapon/sword/CosmosSword(360x90)12x1.bmp", 360, 90, 12, 1, true, RGB(255, 0, 255));	// ����


	IMAGEMANAGER->addImage("�ظ�10", "image/item/weapon/hammer/SteelWarHammerDrop(85x50)1x1.bmp", 85, 50, true, RGB(255, 0, 255));	//���
	IMAGEMANAGER->addImage("�ظ�11", "image/item/weapon/hammer/SteelWarHammerInven(13x22)1x1.bmp", 13, 22, true, RGB(255, 0, 255));	//�κ�
	IMAGEMANAGER->addImage("�ظ�12", "image/item/weapon/hammer/SteelWarHammerRight(50x85)1x1.bmp", 50, 85, true, RGB(255, 0, 255));	//����
	


	IMAGEMANAGER->addImage("�ظ�20", "image/item/weapon/hammer/DragonHammerDrop(79x50)1x1.bmp", 79, 50, true, RGB(255, 0, 255));		//���
	IMAGEMANAGER->addImage("�ظ�21", "image/item/weapon/hammer/DragonHammerInven(26x41)1x1.bmp", 26, 41, true, RGB(255, 0, 255));	//�κ�
	IMAGEMANAGER->addRotateImage("�ظ�22", "image/item/weapon/hammer/DragonHammer(50x79)1x1.bmp", 50, 79, true, RGB(255, 0, 255));	//����


	//���Ÿ����� �̹��� 
	//��ȣ��
	//IMAGEMANAGER->addRotateImage("��10��", "image/item/weapon/gun/deadlyKissLeft(100x25)1x1.bmp", 100, 25, true, RGB(255, 0, 255));		// ����
	//IMAGEMANAGER->addRotateImage("��10��", "image/item/weapon/gun/deadlyKissRight(100x25)1x1.bmp", 100, 25, true, RGB(255, 0, 255));		// ����
	//�ǵ�����3

	IMAGEMANAGER->addImage("��10", "image/item/weapon/gun/matchlockGunDrop(70x18)1x1.bmp", 70, 18, true, RGB(255, 0, 255));			// ���
	IMAGEMANAGER->addImage("��11", "image/item/weapon/gun/matchlockGunInven(27x8)1x1.bmp", 27, 8, true, RGB(255, 0, 255));			// �κ�
	IMAGEMANAGER->addRotateImage("��12", "image/item/weapon/gun/matchlockGun(70x18)1x1.bmp", 70, 18, true, RGB(255, 0, 255));		// ����
	

	IMAGEMANAGER->addImage("��20", "image/item/weapon/gun/deadlyKissDrop(80x20)1x1.bmp", 80, 20, true, RGB(255, 0, 255));			// ���
	IMAGEMANAGER->addImage("��21", "image/item/weapon/gun/deadlyKissInven(40x10)1x1.bmp", 40, 10, true, RGB(255, 0, 255));			// �κ�
	IMAGEMANAGER->addRotateImage("��22", "image/item/weapon/gun/deadlyKiss(80x20)1x1.bmp", 80, 20, true, RGB(255, 0, 255));			// ����

	IMAGEMANAGER->addImage("��30", "image/item/weapon/gun/flameThrowerDrop(80x40)1x1.bmp", 80, 40, true, RGB(255, 0, 255));			// ���
	IMAGEMANAGER->addImage("��31", "image/item/weapon/gun/flameThrowerInven(22x11)1x1.bmp", 22, 11, true, RGB(255, 0, 255));			// �κ�
	IMAGEMANAGER->addRotateImage("��32", "image/item/weapon/gun/flameThrower(80x40)1x1.bmp", 80, 40, true, RGB(255, 0, 255));		// ����

	IMAGEMANAGER->addImage("��40", "image/item/weapon/gun/RailGunInvenDrop(86x30)1x1.bmp", 86, 30, true, RGB(255, 0, 255));					// ���
	IMAGEMANAGER->addImage("��41", "image/item/weapon/gun/RailGunInven(21x9)1x1.bmp", 21, 9, true, RGB(255, 0, 255));						// �κ�
	IMAGEMANAGER->addRotateFrameImage("��42", "image/item/weapon/gun/railGun(600x30)7x1.bmp", 600, 30, 7, 1, true, RGB(255, 0, 255));		// ����


	IMAGEMANAGER->addImage("Ȱ10", "image/item/weapon/bow/CrossbowDrop(50x31)1x1.bmp", 50, 31, true, RGB(255, 0, 255));						// ���
	IMAGEMANAGER->addImage("Ȱ11", "image/item/weapon/bow/CrossbowInven(18x11)1x1.bmp", 18, 11, true, RGB(255, 0, 255));						// �κ�
	IMAGEMANAGER->addRotateFrameImage("Ȱ12", "image/item/weapon/bow/Crossbow(100x34)2x1.bmp", 100, 34, 2, 1, true, RGB(255, 0, 255));		// ����

	IMAGEMANAGER->addImage("Ȱ20", "image/item/weapon/bow/darkbowDrop(50x27)1x1.bmp", 50, 27, true, RGB(255, 0, 255));						// ��� 
	IMAGEMANAGER->addImage("Ȱ21", "image/item/weapon/bow/darkbowInven(17x15)1x1.bmp", 17, 15, true, RGB(255, 0, 255));						// �κ�
	IMAGEMANAGER->addRotateFrameImage("Ȱ22", "image/item/weapon/bow/darkbow(300x50)6x1.bmp", 300, 50, 6, 1, true, RGB(255, 0, 255));		// ����

	IMAGEMANAGER->addImage("Ȱ30", "image/item/weapon/bow/lightbringerDrop(50x22)1x1.bmp", 50, 22, true, RGB(255, 0, 255));					// ���
	IMAGEMANAGER->addImage("Ȱ31", "image/item/weapon/bow/lightbringerInven(11x25)1x1.bmp", 11, 25, true, RGB(255, 0, 255));					// �κ�
	IMAGEMANAGER->addRotateFrameImage("Ȱ32", "image/item/weapon/bow/lightbringer(300x50)6x1.bmp", 300, 50, 6, 1, true, RGB(255, 0, 255));	// ����
	




	//�������� �������� �������� �������� �������� �������� �������� �������� ��������
	IMAGEMANAGER->addRotateFrameImage("�Ѿ�0", "image/item/weapon/gun/deadlyKissBullet(1200x110,12x1).bmp",1000,92,12,1,true, RGB(255,0,255 ));
	IMAGEMANAGER->addRotateFrameImage("�Ѿ�1", "image/item/weapon/gun/flameThrower(400x125,8x1).bmp",400,125,8,1,true, RGB(255 , 0 , 255));
	IMAGEMANAGER->addRotateFrameImage("�Ѿ�2", "image/item/weapon/gun/matchlockGunBullet(750x30,5x1).bmp",750,30,5,1,true , RGB(255,0,255));
	IMAGEMANAGER->addRotateFrameImage("�Ѿ�3", "image/item/weapon/gun/railGunBullet(300x100,6x1).bmp",300,100,6,1,true, RGB(255,0,255 ));

		
	// �� �̹���

	IMAGEMANAGER->addImage("�Ƹ�10", "image/item/armor/ClothArmorDrop(30x27)1x1.bmp", 30, 27, true, RGB(255, 0, 255));	// ���
	IMAGEMANAGER->addImage("�Ƹ�11", "image/item/armor/ClothArmorInven(30x27)1x1.bmp", 30, 27, true, RGB(255, 0, 255));	// �κ�
	
	IMAGEMANAGER->addImage("�Ƹ�20", "image/item/armor/LeatherArmorDrop(30x24)1x1.bmp", 30, 24, true, RGB(255, 0, 255));		// ���
	IMAGEMANAGER->addImage("�Ƹ�21", "image/item/armor/LeatherArmorInven(30x24)1x1.bmp", 30, 24, true, RGB(255, 0, 255));	// �κ�
	
	IMAGEMANAGER->addImage("�Ƹ�30", "image/item/armor/CowLeatherDrop(30x24)1x1.bmp", 30, 24, true, RGB(255, 0, 255));	// ���
	IMAGEMANAGER->addImage("�Ƹ�31", "image/item/armor/CowLeatherInven(30x24)1x1.bmp", 30, 24, true, RGB(255, 0, 255));	// �κ�
	
	IMAGEMANAGER->addImage("�Ƹ�40", "image/item/armor/ChainArmorDrop(30x30)1x1.bmp", 30, 30, true, RGB(255, 0, 255));	// ���
	IMAGEMANAGER->addImage("�Ƹ�41", "image/item/armor/ChainArmorInven(30x30)1x1.bmp", 30, 30, true, RGB(255, 0, 255));	// �κ�
	

	IMAGEMANAGER->addImage("����10", "image/item/shield/HeaterShieldDrop(65x40)1x1.bmp", 65, 40, true, RGB(255, 0, 255));		// ���
	IMAGEMANAGER->addImage("����11", "image/item/shield/HeaterShieldInven(11x18)1x1.bmp", 11, 18, true, RGB(255, 0, 255));	// �κ�
	IMAGEMANAGER->addImage("����12", "image/item/shield/HeaterShield(40x65)1x1.bmp", 40, 65, true, RGB(255, 0, 255));			// ����

	IMAGEMANAGER->addImage("����20", "image/item/shield/DashShieldDrop(50x45)1x1.bmp", 50, 45, true, RGB(255, 0, 255));		// ���
	IMAGEMANAGER->addImage("����21", "image/item/shield/DashShieldInven(28x25)1x1.bmp", 28, 25, true, RGB(255, 0, 255));		// �κ�
	IMAGEMANAGER->addImage("����22", "image/item/shield/DashShield(50x45)1x1.bmp", 50, 45, true, RGB(255, 0, 255));			// ����




	//�Ǽ��縮 �̹���(���� ���/ ����/ ��)
	IMAGEMANAGER->addImage("����10", "image/item/second/BlessOfSageDrop(20x20)1x1.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����11", "image/item/second/BlessOfSageInven(20x20)1x1.bmp", 20, 20, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("����20", "image/item/second/BloodOfSrobeoDrop(25x31)1x1.bmp", 25, 31, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����21", "image/item/second/BloodOfSrobeoInven(25x31)1x1.bmp", 25, 31, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("����30", "image/item/second/WingDrop(30x21)1x1.bmp", 30, 21, true, RGB(255, 0, 255));			// ���
	IMAGEMANAGER->addImage("����31", "image/item/second/WingInven(30x21)1x1.bmp", 30, 21, true, RGB(255, 0, 255));			// �κ�
	IMAGEMANAGER->addFrameImage("����32", "image/item/second/Wing(350x43)7x1.bmp", 350, 43, 7, 1, true, RGB(255, 0, 255));	// ����

	IMAGEMANAGER->addImage("����40", "image/item/second/MartialArtOfTigerDrop(30x25)1x1.bmp", 30, 25, true, RGB(255, 0, 255));			// ���
	IMAGEMANAGER->addImage("����41", "image/item/second/MartialArtOfTigerInven(30x25)1x1.bmp", 30, 25, true, RGB(255, 0, 255));			// �κ�
	IMAGEMANAGER->addFrameImage("����42", "image/item/second/MartialArtOfTiger(441x49)9x1.bmp", 441, 49, 9, 1, true, RGB(255, 0, 255));	// ����

	IMAGEMANAGER->addImage("�Ǽ�10", "image/item/accessory/BloodStoneRingDrop(30x35)1x1.bmp", 30, 35, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�Ǽ�11", "image/item/accessory/BloodStoneRingInven(30x35)1x1.bmp", 30, 35, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("�Ǽ�20", "image/item/accessory/EnvirokEpauletDrop(30x29)1x1.bmp", 30, 29, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�Ǽ�21", "image/item/accessory/EnvirokEpauletInven(30x29)1x1.bmp", 30, 29, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("�Ǽ�30", "image/item/accessory/FrostChockerDrop(30x28)1x1.bmp", 30, 28, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�Ǽ�31", "image/item/accessory/FrostChockerInven(30x28)1x1.bmp", 30, 28, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("�Ǽ�40", "image/item/accessory/GerberaRingDrop(30x34)1x1.bmp", 30, 34, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�Ǽ�41", "image/item/accessory/GerberaRingInven(30x34)1x1.bmp", 30, 34, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("��10", "image/item/pet/petDrop(95x22)5x1.bmp", 95, 22, 5, 1, true, RGB(255, 0, 255));	// ���
	IMAGEMANAGER->addImage("��11", "image/item/pet/petInven(19x22)1x1.bmp", 19, 22, true, RGB(255, 0, 255));				// �κ�
	IMAGEMANAGER->addFrameImage("��12", "image/item/pet/pet(240x22)12x1.bmp", 240, 22, 12, 1, true, RGB(255, 0, 255));	// ����


	//���� �̹���
	IMAGEMANAGER->addImage("����1", "image/item/food/1_bread(73x30)1x1.bmp", 73, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����2", "image/item/food/2_FriedEgg(73x30)1x1.bmp", 73, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����3", "image/item/food/03_grilledMushroom(73x30)1x1.bmp", 73, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����4", "image/item/food/04_TamatoSoup(73x30)1x1.bmp", 73, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����5", "image/item/food/05_OnionSoup(73x30)1x1.bmp", 73, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����6", "image/item/food/06_VegetableSalsaSoup(73x30)1x1.bmp", 73, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����7", "image/item/food/07_ChocolateCookie(73x30)1x1.bmp", 73, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����8", "image/item/food/08_RaspberryCookie(73x30)1x1.bmp", 73, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����9", "image/item/food/09_GriffonEggOmelette(73x30)1x1.bmp", 73, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����10", "image/item/food/10_DeluxeBurger(73x48)1x1.bmp", 73, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����11", "image/item/food/11_HotChickenStew(73x35)1x1.bmp", 73, 35, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����12", "image/item/food/12_MinotaursSteak(73x32)1x1.bmp", 73, 32, true, RGB(255, 0, 255));

	//�������� �̹���
	IMAGEMANAGER->addFrameImage("����1", "image/item/healing/heal1(216x24)9x1.bmp", 216, 24, 9, 1, true, RGB(255, 0, 255));		// ������ �̹���
	IMAGEMANAGER->addFrameImage("����2", "image/item/healing/heal2(480x30)16x1.bmp", 480, 30, 16, 1, true, RGB(255, 0, 255));	// ������ �̹���


	//�ڽ� / ���� �̹���

	IMAGEMANAGER->addFrameImage("��������1", "image/item/treasurebox/bossbox(80x28)2x1.bmp", 80, 28, 2, 1, true, RGB(255, 0, 255));	//������
	IMAGEMANAGER->addFrameImage("�Ϲݻ���1", "image/item/treasurebox/bossbox(80x28)2x1.bmp", 80, 28, 2, 1, true, RGB(255, 0, 255));	//������
	
	IMAGEMANAGER->addFrameImage("����1", "image/item/treasurebox/coin(56x7)8x1.bmp", 56, 7, 8, 1, true, RGB(255, 0, 255));		// ������
	IMAGEMANAGER->addFrameImage("���1", "image/item/treasurebox/gold(140x9)7x1.bmp", 140, 9, 7, 1, true, RGB(255, 0, 255));		// ������

	//����Ʈ ������������������������������    EFFECTMANAGER->addEffect
	EFFECTMANAGER->addEffect("��ÿ���", "image/player/dashManLeft(320x95,4x1).bmp", 320, 95, 80, 95, 1.0f, 0.3f, 5);
	EFFECTMANAGER->addEffect("��ÿ�����", "image/player/dashManRight(320x95,4x1).bmp", 320, 95, 80, 95, 1.0f, 0.3f, 5);
	EFFECTMANAGER->addEffect("���ʰ�����", "image/player/leftRunDust(200x40,5x1).bmp", 250, 50, 50, 50, 1.0f, 0.3f, 1);
	EFFECTMANAGER->addEffect("�����ʰ�����", "image/player/rightRunDust(200x40,5x1).bmp", 250, 50, 50, 50, 1.0f, 0.3f, 1);
	EFFECTMANAGER->addEffect("�����߾�", "image/player/jumpEffect(350x70,5x1).bmp", 350, 70, 70, 70, 1.0f, 0.3f, 1);
	EFFECTMANAGER->addEffect("�̰��̴������߾�", "image/player/doubleJumpEffect(420x70,6x1).bmp", 420, 70, 70, 70, 1.0f, 0.3f, 1);
	IMAGEMANAGER->addRotateFrameImage("�˾�����", "image/item/weapon/sword/effect/swing.bmp", 600 , 109 , 4 , 1, true , RGB(255,0,255));

	//���� �� ���ǽ�
	IMAGEMANAGER->addFrameImage("�������ǽ�10", "image/npc/inn(600x200,6x1).bmp", 600, 200, 6, 1, true, RGB(255, 0, 255)); // �����Ĵ� ���ܸ�
	IMAGEMANAGER->addFrameImage("�������ǽ�20", "image/npc/weaponNPC(400x196)4x1.bmp", 400, 196, 4, 1, true, RGB(255, 0, 255)); // ��� �Ǹ��ϴ� ������

	return S_OK;
}