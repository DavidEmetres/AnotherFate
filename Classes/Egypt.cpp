#include "AppDelegate.h"
#include "Egypt.h"

USING_NS_CC;

Scene* Egypt::createScene()
{
	auto scene = Scene::createWithPhysics();

	auto layer = Egypt::create();
	layer->setPhysicsWorld(scene->getPhysicsWorld());

	scene->addChild(layer);

	return scene;
}

bool Egypt::init()
{
	if (!Layer::init())
	{
		return false;
	}

	this->setScale(0.7);

	//INITIALIZE ATRIBUTES

	visibleSize = Director::getInstance()->getVisibleSize();

	moveRight = false;
	moveLeft = false;
	moveCam = false;
	key = ' ';
	AKeyCounter = 0;
	contactBody = PhysicsBody::create();
	contactFloor = NULL;
	contactEnemy = PhysicsBody::create();

	//CREATE PARALLAX NODE

	backgroundNode = CCParallaxNode::create();
	//addChild(backgroundNode, -1);

	//CREATE BACKGROUND LAYERS

	createBackground();

	//CREATE ANIMATED OBJECTS

	createAnimations();

	//CREATE POWER UPS

	power1 = new PowerUps(1);
	addChild(power1->flyParticle, 5);
	addChild(power1->flyParticleSmoke, 5);

	power2 = new PowerUps(2);
	addChild(power2->shadowParticle, 6);

	//CREATE INTERACTIVE ITEMS

	//VASIJAS

	vasijaPequena1 = new Item(2, 2000, 90);
	objectsVector.pushBack(vasijaPequena1);
	tag = (vasijaPequena1->itemType * 1000) + objectsVector.getIndex(vasijaPequena1);
	vasijaPequena1->itemCollider->setTag(tag);
	addChild(vasijaPequena1->itemArt, 5);
	tag += 100;
	vasijaPequena1->itemSoundCollider->setTag(tag);
	addChild(vasijaPequena1->itemSound, 5);

	//VASIJAS GRANDES

	vasijaGrande1 = new Item(3, 14381 + 3520, 90);
	objectsVector.pushBack(vasijaGrande1);
	tag = (vasijaGrande1->itemType * 1000) + objectsVector.getIndex(vasijaGrande1);
	vasijaGrande1->itemCollider->setTag(tag);
	addChild(vasijaGrande1->itemArt, 5);

	//CREATE INTERACTIVE ITEMS

	//CREATE FLOOR LAYERS

	Layer51 = Sprite::create("images/Egipt/Layers/Egipt_Layer5_Modulo1.png");
	Layer51->setPosition(Point(Layer51->getContentSize().width / 2 - 2000, Layer51->getContentSize().height / 2 - 1670));

	addChild(Layer51, 5);

	Layer52 = Sprite::create("images/Egipt/Layers/Egipt_Layer5_Modulo2.png");
	Layer52->setPosition(Point(Layer52->getContentSize().width / 2 + 14168 - 2000, Layer52->getContentSize().height / 2 - 1675));

	addChild(Layer52, 5);

	Layer53 = Sprite::create("images/Egipt/Layers/Egipt_Layer5_Modulo3.png");
	Layer53->setPosition(Point(Layer53->getContentSize().width / 2 + 14177 + 14168 - 2000, Layer53->getContentSize().height / 2 - 1670));

	addChild(Layer53, 5);

	Layer54 = Sprite::create("images/Egipt/Layers/Egipt_Layer5_Modulo4.png");
	Layer54->setPosition(Point(Layer54->getContentSize().width / 2 + 14177 + 14177 + 14162 - 2000, Layer54->getContentSize().height / 2 - 1670));

	addChild(Layer54, 5);

	//CREATE FLOOR LAYERS

	//FLOOR COLLIDERS

	Floor1 = Sprite::create("images/Egipt/Colliders/FloorCollider1.png");
	Floor1->setScaleX(13);
	Floor1->setPosition(Point((Floor1->getContentSize().width / 2) - 2000, (Floor1->getContentSize().height / 2) - 10));
	Floor1->setVisible(false);

	addChild(Floor1, 5);

	FloorCollider1 = PhysicsBody::createBox(Size(Floor1->getContentSize().width * 13, Floor1->getContentSize().height));
	FloorCollider1->setContactTestBitmask(true);
	FloorCollider1->setDynamic(true);
	FloorCollider1->setCollisionBitmask(0);
	FloorCollider1->setGravityEnable(false);
	FloorCollider1->setTag(-1);

	Floor1->setPhysicsBody(FloorCollider1);

	//////////////////////////////////

	Floor1Modulo1 = Sprite::create();
	Floor1Modulo1->setPosition(Point(12802, 769));
	Floor1Modulo1->setVisible(true);

	addChild(Floor1Modulo1, 5);

	FloorCollider1Modulo1 = PhysicsBody::createBox(Size(1080, 80));
	FloorCollider1Modulo1->setContactTestBitmask(true);
	FloorCollider1Modulo1->setDynamic(true);
	FloorCollider1Modulo1->setCollisionBitmask(0);
	FloorCollider1Modulo1->setGravityEnable(false);
	FloorCollider1Modulo1->setTag(-1);

	Floor1Modulo1->setPhysicsBody(FloorCollider1Modulo1);

	//////////////////////////////////

	Floor2Modulo1 = Sprite::create();
	Floor2Modulo1->setPosition(Point(15828, 769));
	Floor2Modulo1->setVisible(true);

	addChild(Floor2Modulo1, 5);

	FloorCollider2Modulo1 = PhysicsBody::createBox(Size(1860, 80));
	FloorCollider2Modulo1->setContactTestBitmask(true);
	FloorCollider2Modulo1->setDynamic(true);
	FloorCollider2Modulo1->setCollisionBitmask(0);
	FloorCollider2Modulo1->setGravityEnable(false);
	FloorCollider2Modulo1->setTag(-1);

	Floor2Modulo1->setPhysicsBody(FloorCollider2Modulo1);

	//////////////////////////////////

	Floor3Modulo1 = Sprite::create();
	Floor3Modulo1->setPosition(Point(16552, 1142));
	Floor3Modulo1->setVisible(true);

	addChild(Floor3Modulo1, 5);

	FloorCollider3Modulo1 = PhysicsBody::createBox(Size(340, 80));
	FloorCollider3Modulo1->setContactTestBitmask(true);
	FloorCollider3Modulo1->setDynamic(true);
	FloorCollider3Modulo1->setCollisionBitmask(0);
	FloorCollider3Modulo1->setGravityEnable(false);
	FloorCollider3Modulo1->setTag(-1);

	Floor3Modulo1->setPhysicsBody(FloorCollider3Modulo1);

	//////////////////////////////////

	Floor4Modulo1 = Sprite::create();
	Floor4Modulo1->setPosition(Point(17177, 1289));
	Floor4Modulo1->setVisible(true);

	addChild(Floor4Modulo1, 5);

	FloorCollider4Modulo1 = PhysicsBody::createBox(Size(570, 80));
	FloorCollider4Modulo1->setContactTestBitmask(true);
	FloorCollider4Modulo1->setDynamic(true);
	FloorCollider4Modulo1->setCollisionBitmask(0);
	FloorCollider4Modulo1->setGravityEnable(false);
	FloorCollider4Modulo1->setTag(-1);

	Floor4Modulo1->setPhysicsBody(FloorCollider4Modulo1);

	//////////////////////////////////

	Floor5Modulo1 = Sprite::create();
	Floor5Modulo1->setPosition(Point(14294, 440));
	Floor5Modulo1->setVisible(true);

	addChild(Floor5Modulo1, 5);

	FloorCollider5Modulo1 = PhysicsBody::createBox(Size(340, 80));
	FloorCollider5Modulo1->setContactTestBitmask(true);
	FloorCollider5Modulo1->setDynamic(true);
	FloorCollider5Modulo1->setCollisionBitmask(0);
	FloorCollider5Modulo1->setGravityEnable(false);
	FloorCollider5Modulo1->setTag(-1);

	Floor5Modulo1->setPhysicsBody(FloorCollider5Modulo1);

	//////////////////////////////////

	Floor6Modulo1 = Sprite::create();
	Floor6Modulo1->setPosition(Point(21294, 769));
	Floor6Modulo1->setVisible(true);

	addChild(Floor6Modulo1, 5);

	FloorCollider6Modulo1 = PhysicsBody::createBox(Size(1400, 80));
	FloorCollider6Modulo1->setContactTestBitmask(true);
	FloorCollider6Modulo1->setDynamic(true);
	FloorCollider6Modulo1->setCollisionBitmask(0);
	FloorCollider6Modulo1->setGravityEnable(false);
	FloorCollider6Modulo1->setTag(-1);

	Floor6Modulo1->setPhysicsBody(FloorCollider6Modulo1);

	//////////////////////////////////

	Floor7Modulo1 = Sprite::create();
	Floor7Modulo1->setPosition(Point(21171, 1142));
	Floor7Modulo1->setVisible(true);

	addChild(Floor7Modulo1, 5);

	FloorCollider7Modulo1 = PhysicsBody::createBox(Size(340, 80));
	FloorCollider7Modulo1->setContactTestBitmask(true);
	FloorCollider7Modulo1->setDynamic(true);
	FloorCollider7Modulo1->setCollisionBitmask(0);
	FloorCollider7Modulo1->setGravityEnable(false);
	FloorCollider7Modulo1->setTag(-1);

	Floor7Modulo1->setPhysicsBody(FloorCollider7Modulo1);

	//////////////////////////////////

	Floor8Modulo1 = Sprite::create();
	Floor8Modulo1->setPosition(Point(21717, 1265));
	Floor8Modulo1->setVisible(true);

	addChild(Floor8Modulo1, 5);

	FloorCollider8Modulo1 = PhysicsBody::createBox(Size(570, 80));
	FloorCollider8Modulo1->setContactTestBitmask(true);
	FloorCollider8Modulo1->setDynamic(true);
	FloorCollider8Modulo1->setCollisionBitmask(0);
	FloorCollider8Modulo1->setGravityEnable(false);
	FloorCollider8Modulo1->setTag(-1);

	Floor8Modulo1->setPhysicsBody(FloorCollider8Modulo1);

	//////////////////////////////////

	Floor9Modulo1 = Sprite::create();
	Floor9Modulo1->setPosition(Point(22585, 1570));
	Floor9Modulo1->setVisible(true);

	addChild(Floor9Modulo1, 5);

	FloorCollider9Modulo1 = PhysicsBody::createBox(Size(180, 80));
	FloorCollider9Modulo1->setContactTestBitmask(true);
	FloorCollider9Modulo1->setDynamic(true);
	FloorCollider9Modulo1->setCollisionBitmask(0);
	FloorCollider9Modulo1->setGravityEnable(false);
	FloorCollider9Modulo1->setTag(-1);

	Floor9Modulo1->setPhysicsBody(FloorCollider9Modulo1);

	//////////////////////////////////

	Floor10Modulo1 = Sprite::create();
	Floor10Modulo1->setPosition(Point(23516, 440));
	Floor10Modulo1->setVisible(true);

	addChild(Floor10Modulo1, 5);

	FloorCollider10Modulo1 = PhysicsBody::createBox(Size(340, 80));
	FloorCollider10Modulo1->setContactTestBitmask(true);
	FloorCollider10Modulo1->setDynamic(true);
	FloorCollider10Modulo1->setCollisionBitmask(0);
	FloorCollider10Modulo1->setGravityEnable(false);
	FloorCollider10Modulo1->setTag(-1);

	Floor10Modulo1->setPhysicsBody(FloorCollider10Modulo1);

	//////////////////////////////////

	Floor11Modulo1 = Sprite::create();
	Floor11Modulo1->setPosition(Point(24586, 440));
	Floor11Modulo1->setVisible(true);

	addChild(Floor11Modulo1, 5);

	FloorCollider11Modulo1 = PhysicsBody::createBox(Size(340, 80));
	FloorCollider11Modulo1->setContactTestBitmask(true);
	FloorCollider11Modulo1->setDynamic(true);
	FloorCollider11Modulo1->setCollisionBitmask(0);
	FloorCollider11Modulo1->setGravityEnable(false);
	FloorCollider11Modulo1->setTag(-1);

	Floor11Modulo1->setPhysicsBody(FloorCollider11Modulo1);

	//////////////////////////////////

	Floor12Modulo1 = Sprite::create();
	Floor12Modulo1->setPosition(Point(25706, 440));
	Floor12Modulo1->setVisible(true);

	addChild(Floor12Modulo1, 5);

	FloorCollider12Modulo1 = PhysicsBody::createBox(Size(340, 80));
	FloorCollider12Modulo1->setContactTestBitmask(true);
	FloorCollider12Modulo1->setDynamic(true);
	FloorCollider12Modulo1->setCollisionBitmask(0);
	FloorCollider12Modulo1->setGravityEnable(false);
	FloorCollider12Modulo1->setTag(-1);

	Floor12Modulo1->setPhysicsBody(FloorCollider12Modulo1);

	//FLOOR COLLIDERS

	//WALL COLLIDERS

	Wall0 = Sprite::create("images/Egipt/Colliders/Wall0Collider.png");
	Wall0->setPosition(Point((Wall0->getContentSize().width / 2) - 300, (Wall0->getContentSize().height / 2)));
	Wall0->setVisible(false);

	addChild(Wall0, 5);

	Wall0Collider = PhysicsBody::createBox(Size(Wall0->getContentSize().width, Wall0->getContentSize().height));
	Wall0Collider->setContactTestBitmask(true);
	Wall0Collider->setDynamic(true);
	Wall0Collider->setCollisionBitmask(0);
	Wall0Collider->setGravityEnable(false);
	Wall0Collider->setTag(-2);

	Wall0->setPhysicsBody(Wall0Collider);

	//////////////////////////////////

	Wall1Modulo1 = Sprite::create();
	Wall1Modulo1->setPosition(Point(16892, 1008));
	Wall1Modulo1->setVisible(true);

	addChild(Wall1Modulo1, 5);

	Wall1ColliderModulo1 = PhysicsBody::createBox(Size(80, 530));
	Wall1ColliderModulo1->setContactTestBitmask(true);
	Wall1ColliderModulo1->setDynamic(true);
	Wall1ColliderModulo1->setCollisionBitmask(0);
	Wall1ColliderModulo1->setGravityEnable(false);
	Wall1ColliderModulo1->setTag(-2);

	Wall1Modulo1->setPhysicsBody(Wall1ColliderModulo1);

	//////////////////////////////////

	Wall2Modulo1 = Sprite::create();
	Wall2Modulo1->setPosition(Point(16892, 1058));
	Wall2Modulo1->setVisible(true);

	addChild(Wall2Modulo1, 5);

	Wall2ColliderModulo1 = PhysicsBody::createBox(Size(80, 530));
	Wall2ColliderModulo1->setContactTestBitmask(true);
	Wall2ColliderModulo1->setDynamic(true);
	Wall2ColliderModulo1->setCollisionBitmask(0);
	Wall2ColliderModulo1->setGravityEnable(false);
	Wall2ColliderModulo1->setTag(-2);

	Wall2Modulo1->setPhysicsBody(Wall2ColliderModulo1);

	//////////////////////////////////

	Wall3Modulo1 = Sprite::create();
	Wall3Modulo1->setPosition(Point(22574.5, 833));
	Wall3Modulo1->setVisible(true);

	addChild(Wall3Modulo1, 5);

	Wall3ColliderModulo1 = PhysicsBody::createBox(Size(660, 1460));
	Wall3ColliderModulo1->setContactTestBitmask(true);
	Wall3ColliderModulo1->setDynamic(true);
	Wall3ColliderModulo1->setCollisionBitmask(0);
	Wall3ColliderModulo1->setGravityEnable(false);
	Wall3ColliderModulo1->setTag(-2);

	Wall3Modulo1->setPhysicsBody(Wall3ColliderModulo1);

	//////////////////////////////////

	//CREATE CHARACTER

	Iniko = new Character(1, 0);

	addChild(Iniko->runningSoundColliderSprite, 5);
	addChild(Iniko->characterIdlerightspritebatch, 5);
	addChild(Iniko->characterRunningRightspritebatch, 5);
	addChild(Iniko->characterIdleleftspritebatch, 5);
	addChild(Iniko->characterRunningLeftspritebatch, 5);
	addChild(Iniko->characterJumpingRight, 5);
	addChild(Iniko->characterJumpingLeft, 5);

	addChild(Iniko->characterVision, 5);
	addChild(Iniko->AKey, 5);
	addChild(Iniko->SKey, 5);
	addChild(Iniko->forceBar, 5);
	addChild(Iniko->forceBarBorder, 5);

	//INITIALIZE UPDATE FUNCTION

	this->scheduleUpdate();

	//CREATE KEY INPUTS LISTENERS

	auto listener = EventListenerKeyboard::create();

	listener->onKeyPressed = CC_CALLBACK_2(Egypt::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(Egypt::onKeyReleased, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	//CREATE PHYSIC CONTACT LISTENER

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Egypt::onContactBegin, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(Egypt::onContactSeparate, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	return true;
}

void Egypt::createBackground()
{
	Layer0 = Sprite::create("images/Egipt/Layers/Egipt_Layer.png");
	Layer0->setPosition(Point((Layer0->getContentSize().width / 2) - 3000, (Layer0->getContentSize().height / 2)));
	//Layer0->setTag(80);

	addChild(Layer0, 0);
	//backgroundNode->addChild(Layer0, 0, Point(0, 0), Point(Layer0->getContentSize().width/2 - 2000, Layer0->getContentSize().height/2));

	Layer1 = Sprite::create("images/Egipt/Layers/Egipt_Layer1.png");
	Layer1->setPosition(Point((Layer1->getContentSize().width / 2) - 2000, (Layer1->getContentSize().height / 2)));
	Layer1->setTag(81);

	addChild(Layer1, 1);
	//backgroundNode->addChild(Layer1, 1, Point(0.01, 0), Point((Layer1->getContentSize().width / 2) - 2000, (Layer1->getContentSize().height / 2)));

	Layer2 = Sprite::create("images/Egipt/Layers/Egipt_Layer2.png");
	Layer2->setPosition(Point((Layer2->getContentSize().width / 2) - 2000, (Layer2->getContentSize().height / 2)));
	Layer2->setTag(82);

	addChild(Layer2, 2);
	//backgroundNode->addChild(Layer2, 2, Point(0.02, 0), Point((Layer2->getContentSize().width / 2) - 2000, (Layer2->getContentSize().height / 2)));

	Layer3 = Sprite::create("images/Egipt/Layers/Egipt_Layer3.png");
	Layer3->setPosition(Point((Layer3->getContentSize().width / 2) - 2000, (Layer3->getContentSize().height / 2)));
	Layer3->setTag(83);

	addChild(Layer3, 3);
	//backgroundNode->addChild(Layer3, 3, Point(0.03, 0), Point((Layer3->getContentSize().width / 2) - 2000, (Layer3->getContentSize().height / 2)));

	Layer4 = Sprite::create("images/Egipt/Layers/Egipt_Layer4.png");
	Layer4->setPosition(Point((Layer4->getContentSize().width / 2) - 2000, (Layer4->getContentSize().height / 2)));
	Layer4->setTag(84);

	//addChild(Layer4, 4);
	//backgroundNode->addChild(Layer4, 4, Point(0.3, 0), Point((Layer4->getContentSize().width / 2) - 2000, (Layer4->getContentSize().height / 2)));

	//ILUMINATION

	Layer61 = Sprite::create("images/Egipt/Layers/Egipt_Layer6_Modulo1.png");
	Layer61->setPosition(Point(Layer61->getContentSize().width / 2 - 2000, Layer61->getContentSize().height / 2 - 1665));

	addChild(Layer61, 6);

	Layer62 = Sprite::create("images/Egipt/Layers/Egipt_Layer6_Modulo2.png");
	Layer62->setPosition(Point(Layer62->getContentSize().width / 2 + 14171 - 2000, Layer62->getContentSize().height / 2 - 1665));

	addChild(Layer62, 6);

	Layer63 = Sprite::create("images/Egipt/Layers/Egipt_Layer6_Modulo3.png");
	Layer63->setPosition(Point(Layer63->getContentSize().width / 2 + 14177 + 14146 - 2000, Layer63->getContentSize().height / 2 - 1665));

	addChild(Layer63, 6);

	Layer64 = Sprite::create("images/Egipt/Layers/Egipt_Layer6_Modulo4.png");
	Layer64->setPosition(Point(Layer64->getContentSize().width / 2 + 14177 + 14177 + 14146 - 2000, Layer64->getContentSize().height / 2 - 1665));

	addChild(Layer64, 6);
}

void Egypt::update(float dt)
{
	deltaTime = dt;

	//VELOCITY UPDATE

	//if (!Iniko->jumping)
	//{
	Iniko->characterRunningRightCollider->setVelocity(Vec2(500 * Iniko->velocity, Iniko->characterRunningRightCollider->getVelocity().y));
	Iniko->characterRunningLeftCollider->setVelocity(Vec2(500 * Iniko->velocity, Iniko->characterRunningLeftCollider->getVelocity().y));
	Iniko->characterJumpingRightCollider->setVelocity(Vec2(500 * Iniko->velocity, Iniko->characterJumpingRightCollider->getVelocity().y));
	Iniko->characterJumpingLeftCollider->setVelocity(Vec2(500 * Iniko->velocity, Iniko->characterJumpingLeftCollider->getVelocity().y));
	//}

	/*else if(Iniko->characterJumpingLeftCollider->getVelocity().y < 0 || Iniko->characterJumpingRightCollider->getVelocity().y < 0)
	{
	Iniko->characterRunningRightCollider->setVelocity(Vec2(250 * Iniko->velocity, Iniko->characterRunningRightCollider->getVelocity().y));
	Iniko->characterRunningLeftCollider->setVelocity(Vec2(250 * Iniko->velocity, Iniko->characterRunningLeftCollider->getVelocity().y));
	Iniko->characterJumpingRightCollider->setVelocity(Vec2(250 * Iniko->velocity, Iniko->characterJumpingRightCollider->getVelocity().y));
	Iniko->characterJumpingLeftCollider->setVelocity(Vec2(250 * Iniko->velocity, Iniko->characterJumpingLeftCollider->getVelocity().y));
	}*/

	//VELOCITY UPDATE

	//EVENTS

	if (Iniko->characterIdleRight->getPositionX() >= 7400 && Iniko->characterIdleRight->getPositionX() <= 7500)
	{
		/*Iniko->runningSoundColliderSprite->setZOrder(5);
		Iniko->characterIdlerightspritebatch->setZOrder(5);
		Iniko->characterRunningRightspritebatch->setZOrder(5);
		Iniko->characterIdleleftspritebatch->setZOrder(5);
		Iniko->characterRunningLeftspritebatch->setZOrder(5);
		Iniko->characterVision->setZOrder(5);
		Iniko->AKey->setZOrder(5);
		Iniko->SKey->setZOrder(5);*/
	}

	if (Iniko->characterVision->getPositionX() >= (14381 + 10460) && Iniko->characterVision->getPositionX() <= (14381 + 10685))
	{
		if (key == 'U')
		{
			Iniko->facingRight = false;
			Iniko->characterIdleLeft->setPosition(14381 + 10550, 1386 - Iniko->characterIdleRight->getContentSize().height / 2);
		}
	}

	/*if (Iniko->characterIdleRight->getPositionX() >= 500 && !ready)
	{
		ready = true;

		enemy1 = new Enemy(14381 + 3920, 14381 + 3920, 2.0f, 5, 1);
		enemy1->staticEnemy = true;
		enemysVector.pushBack(enemy1);
		tag = 1000 + enemysVector.getIndex(enemy1);
		enemy1->enemyCollider->setTag(tag);
		//enemy1->enemyArt->setPositionY(2000);
		addChild(enemy1->enemyArt, 5);
		addChild(enemy1->detect, 5);
		tag += 100;
		enemy1->enemyVisionCollider->setTag(tag);
		addChild(enemy1->enemyVision, 5);

		enemy3 = new Enemy(14381 + 9000, 14381 + 7750, 2.0f, 4, 1);
		enemysVector.pushBack(enemy3);
		tag = 1000 + enemysVector.getIndex(enemy3);
		enemy3->enemyCollider->setTag(tag);
		addChild(enemy3->enemyArt, 5);
		addChild(enemy3->detect, 5);
		tag += 100;
		enemy3->enemyVisionCollider->setTag(tag);
		addChild(enemy3->enemyVision, 5);

		enemy4 = new Enemy(14381 + 10200, 14381 + 10200, 2.0f, 5, 1);
		enemysVector.pushBack(enemy4);
		tag = 1000 + enemysVector.getIndex(enemy4);
		enemy4->enemyCollider->setTag(tag);
		addChild(enemy4->enemyArt, 5);
		addChild(enemy4->detect, 5);
		tag += 100;
		enemy4->enemyVisionCollider->setTag(tag);
		addChild(enemy4->enemyVision, 5);
	}*/

	/*if (Iniko->characterIdleRight->getPositionX() > (14381 + 13570))
	{
	gameOver();
	}*/

	//EVENTS

	//Z ORDER FIX

	if (contactFloor != NULL && Iniko->characterVision->getPosition().y > 300)
	{
		/*Iniko->runningSoundColliderSprite->setZOrder(4);
		Iniko->characterIdlerightspritebatch->setZOrder(4);
		Iniko->characterRunningRightspritebatch->setZOrder(4);
		Iniko->characterIdleleftspritebatch->setZOrder(4);
		Iniko->characterRunningLeftspritebatch->setZOrder(4);
		Iniko->characterVision->setZOrder(4);
		Iniko->AKey->setZOrder(4);
		Iniko->SKey->setZOrder(4);*/
	}

	//Z ODER FIX

	//PARALLAX

	Layer0->setPosition(Point((Layer0->getContentSize().width / 2) - 3000 + Iniko->characterVision->getPosition().x, (Layer0->getContentSize().height / 2)));
	Layer1->setPosition(Point((Layer1->getContentSize().width / 2) - 2000 + Iniko->characterVision->getPosition().x - Iniko->characterVision->getPosition().x * 0.05, (Layer1->getContentSize().height / 2)));
	Layer2->setPosition(Point((Layer2->getContentSize().width / 2) - 2000 + Iniko->characterVision->getPosition().x - Iniko->characterVision->getPosition().x * 0.06, (Layer2->getContentSize().height / 2)));
	Layer3->setPosition(Point((Layer3->getContentSize().width / 2) - 2000 + Iniko->characterVision->getPosition().x - Iniko->characterVision->getPosition().x * 0.07, (Layer3->getContentSize().height / 2)));
	//Layer4->setPosition(Point((Layer4->getContentSize().width / 2) - 2000 + Iniko->characterVision->getPosition().x - Iniko->characterVision->getPosition().x * 0.7, (Layer4->getContentSize().height / 2)));

	//PARALLAX

	//POWER UPS UPDATE

	power1->flyParticleSmoke->setPosition(power1->flyParticle->getPosition());

	if (!power1->activated && !power1->finish)
	{
		power1->flyParticle->setPosition(Iniko->characterVision->getPosition());
	}

	else if (power1->activated && !power1->finish)
	{
		if (power1->flyParticle->getPosition().x >= power1->initialPos + 3000)
		{
			power1->finish = true;
			power1->activated = false;
			power1->flyParticleCollider->setEnable(false);
		}

		else if (power1->flyParticle->getPosition().x <= power1->initialPos - 3000)
		{
			power1->finish = true;
			power1->activated = false;
			power1->flyParticleCollider->setEnable(false);
		}

		if (power1->rightDirection)
		{
			power1->flyParticle->setPositionX(power1->flyParticle->getPosition().x + (800 * dt));
		}

		else if (!power1->rightDirection)
		{
			power1->flyParticle->setPositionX(power1->flyParticle->getPosition().x - (800 * dt));
		}
	}

	else if (power1->finish && !power1->activated)
	{
		if (power1->flyParticle->getPosition().y < 3000)
			power1->flyParticle->setPositionY(power1->flyParticle->getPosition().y + (600 * dt));
	}

	power2->shadowParticle->setPosition(Iniko->characterVision->getPosition());

	if (!power2->activated && power2->finish)
	{
		power2->shadowParticle->setDuration(0);
		power2->shadowParticle->setGravity(Vec2(-100, 0));

		Iniko->runningSoundCollider->setEnable(true);
		Iniko->characterIdleRight->setOpacity(255);
		Iniko->characterIdleRightCollider->setEnable(true);
		Iniko->characterIdleLeft->setOpacity(255);
		Iniko->characterIdleLeftCollider->setEnable(true);
		Iniko->characterRunningRight->setOpacity(255);
		Iniko->characterRunningRightCollider->setEnable(true);
		Iniko->characterRunningLeft->setOpacity(255);
		Iniko->characterRunningLeftCollider->setEnable(true);
	}

	//POWERS UPDATE

	//FACING UPDATE

	if (Iniko->facingRight && !moveRight && !moveLeft /*&& !Iniko->jumping*/)
	{
		Iniko->characterIdlerightspritebatch->setVisible(true);
		Iniko->characterIdleleftspritebatch->setVisible(false);
		Iniko->characterRunningRightspritebatch->setVisible(false);
		Iniko->characterRunningLeftspritebatch->setVisible(false);
		Iniko->characterJumpingRight->setVisible(false);
		Iniko->characterJumpingLeft->setVisible(false);
	}

	if (!Iniko->facingRight && !moveRight && !moveLeft/* && !Iniko->jumping*/)
	{
		Iniko->characterIdlerightspritebatch->setVisible(false);
		Iniko->characterIdleleftspritebatch->setVisible(true);
		Iniko->characterRunningRightspritebatch->setVisible(false);
		Iniko->characterRunningLeftspritebatch->setVisible(false);
		Iniko->characterJumpingRight->setVisible(false);
		Iniko->characterJumpingLeft->setVisible(false);
	}

	//FACING UPDATE

	//ENEMY MOVEMENT

	for (int i = 0; i < enemysVector.size(); i++)
	{
		if (!enemysVector.at(i)->die && !enemysVector.at(i)->stunned)
		{
			enemysVector.at(i)->moveVision();

			if (enemysVector.at(i)->alertedEnemy)
			{
				enemysVector.at(i)->alertedSound = false;
				enemysVector.at(i)->followPos = Iniko->characterIdleRight->getPosition().x;
				enemysVector.at(i)->enemyArt->stopAction(enemysVector.at(i)->sequence);
				enemysVector.at(i)->detectCharacter(dt);
			}

			else if (enemysVector.at(i)->alertedSound)
			{
				enemysVector.at(i)->enemyArt->stopAction(enemysVector.at(i)->sequence);
				enemysVector.at(i)->detectCharacter(dt);
			}

			else if (enemysVector.at(i)->returning)
			{
				enemysVector.at(i)->detectCharacter(dt);
			}
		}
	}

	//ENEMY MOVEMENT

	//GENERAL MOVEMENT

	if (moveRight && moveLeft && !moveCam && !Iniko->stealth && !Iniko->hide)
	{
		Iniko->characterIdlerightspritebatch->setVisible(true);
		Iniko->characterIdleleftspritebatch->setVisible(false);
		Iniko->characterRunningRightspritebatch->setVisible(false);
		Iniko->characterRunningLeftspritebatch->setVisible(false);
		Iniko->characterJumpingLeft->setVisible(false);
		Iniko->characterJumpingRight->setVisible(false);
	}

	/*else if (moveCam)
	{
	if (Iniko->facingRight)
	{
	Iniko->characterIdlerightspritebatch->setVisible(true);
	Iniko->characterIdleleftspritebatch->setVisible(false);
	Iniko->characterRunningRightspritebatch->setVisible(false);
	Iniko->characterRunningLeftspritebatch->setVisible(false);
	}

	else
	{
	Iniko->characterIdlerightspritebatch->setVisible(false);
	Iniko->characterIdleleftspritebatch->setVisible(true);
	Iniko->characterRunningRightspritebatch->setVisible(false);
	Iniko->characterRunningLeftspritebatch->setVisible(false);
	}
	}*/

	else if (moveRight && !moveCam && !Iniko->stealth && !Iniko->hide /*&& !Iniko->jumping*/)
	{
		if (Iniko->wallTouch == NULL)
		{
			Iniko->facingRight = true;

			//Iniko->characterIdleRight->setPosition(Iniko->characterIdleRight->getPosition().x + (800 * dt), Iniko->characterIdleRight->getPosition().y);
			//Iniko->characterIdleRightCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));
			/*Iniko->characterRunningRightCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));
			Iniko->characterRunningLeftCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));
			Iniko->characterIdleRightCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));
			Iniko->characterIdleLeftCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));*/

			Iniko->velocity = 1;

			Iniko->characterIdlerightspritebatch->setVisible(false);
			Iniko->characterIdleleftspritebatch->setVisible(false);
			Iniko->characterRunningLeftspritebatch->setVisible(false);
			Iniko->characterRunningRightspritebatch->setVisible(true);
			Iniko->characterJumpingLeft->setVisible(false);
			Iniko->characterJumpingRight->setVisible(false);
		}

		else if (Iniko->wallTouch != NULL && Iniko->wallTouchSide == 'R')
		{
			if (!Iniko->jumping)
			{
				Iniko->facingRight = true;

				//Iniko->characterIdleRight->setPosition(Iniko->characterIdleRight->getPosition().x + (800 * dt), Iniko->characterIdleRight->getPosition().y);
				//Iniko->characterIdleRightCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));
				/*Iniko->characterRunningRightCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterRunningLeftCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleRightCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleLeftCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));*/

				Iniko->velocity = 1;

				Iniko->characterIdlerightspritebatch->setVisible(false);
				Iniko->characterIdleleftspritebatch->setVisible(false);
				Iniko->characterRunningLeftspritebatch->setVisible(false);
				Iniko->characterRunningRightspritebatch->setVisible(true);
				Iniko->characterJumpingLeft->setVisible(false);
				Iniko->characterJumpingRight->setVisible(false);

				Iniko->wallTouch = NULL;
				Iniko->wallTouchSide = ' ';
			}

			else
			{
				Iniko->facingRight = true;

				//Iniko->characterIdleRight->setPosition(Iniko->characterIdleRight->getPosition().x + (800 * dt), Iniko->characterIdleRight->getPosition().y);
				//Iniko->characterIdleRightCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));
				/*Iniko->characterRunningRightCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterRunningLeftCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleRightCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleLeftCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));*/

				Iniko->velocity = 1;

				Iniko->characterIdlerightspritebatch->setVisible(false);
				Iniko->characterIdleleftspritebatch->setVisible(false);
				Iniko->characterRunningLeftspritebatch->setVisible(false);
				Iniko->characterRunningRightspritebatch->setVisible(false);
				Iniko->characterJumpingLeft->setVisible(false);
				Iniko->characterJumpingRight->setVisible(true);

				Iniko->wallTouch = NULL;
				Iniko->wallTouchSide = ' ';
			}
		}

		else if (Iniko->wallTouch != NULL && Iniko->wallTouchSide == 'L')
		{
			if (!Iniko->jumping)
			{
				Iniko->characterIdlerightspritebatch->setVisible(true);
				Iniko->characterIdleleftspritebatch->setVisible(false);
				Iniko->characterRunningLeftspritebatch->setVisible(false);
				Iniko->characterRunningRightspritebatch->setVisible(false);
				Iniko->characterJumpingLeft->setVisible(false);
				Iniko->characterJumpingRight->setVisible(false);

				//Iniko->characterIdleRightCollider->setVelocity(Vec2(0, Iniko->characterIdleRightCollider->getVelocity().y));
				/*Iniko->characterRunningRightCollider->setVelocity(Vec2(0, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterRunningLeftCollider->setVelocity(Vec2(0, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleRightCollider->setVelocity(Vec2(0, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleLeftCollider->setVelocity(Vec2(0, Iniko->characterIdleRightCollider->getVelocity().y));*/

				Iniko->velocity = 0;
			}

			else
			{
				Iniko->characterIdlerightspritebatch->setVisible(false);
				Iniko->characterIdleleftspritebatch->setVisible(false);
				Iniko->characterRunningLeftspritebatch->setVisible(false);
				Iniko->characterRunningRightspritebatch->setVisible(false);
				Iniko->characterJumpingLeft->setVisible(false);
				Iniko->characterJumpingRight->setVisible(true);

				Iniko->characterJumpingRightCollider->setVelocity(Vec2(0, Iniko->characterJumpingRightCollider->getVelocity().y));
				Iniko->characterJumpingLeftCollider->setVelocity(Vec2(0, Iniko->characterJumpingLeftCollider->getVelocity().y));
				Iniko->characterRunningRightCollider->setVelocity(Vec2(0, Iniko->characterRunningRightCollider->getVelocity().y));
				Iniko->characterRunningLeftCollider->setVelocity(Vec2(0, Iniko->characterRunningLeftCollider->getVelocity().y));
				Iniko->characterIdleRightCollider->setVelocity(Vec2(0, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleLeftCollider->setVelocity(Vec2(0, Iniko->characterIdleLeftCollider->getVelocity().y));

				Iniko->velocity = 0;
			}
		}
	}

	else if (moveLeft && !moveCam && !Iniko->stealth && !Iniko->hide/* && !Iniko->jumping*/)
	{
		if (Iniko->wallTouch == NULL)
		{
			Iniko->facingRight = false;

			//Iniko->characterIdleLeft->setPosition(Iniko->characterIdleLeft->getPosition().x - (800 * dt), Iniko->characterIdleLeft->getPosition().y);
			//Iniko->characterIdleLeftCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));
			/*Iniko->characterRunningRightCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));
			Iniko->characterRunningLeftCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));
			Iniko->characterIdleRightCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));
			Iniko->characterIdleLeftCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));*/

			Iniko->velocity = -1;

			Iniko->characterIdlerightspritebatch->setVisible(false);
			Iniko->characterIdleleftspritebatch->setVisible(false);
			Iniko->characterRunningRightspritebatch->setVisible(false);
			Iniko->characterRunningLeftspritebatch->setVisible(true);
			Iniko->characterJumpingLeft->setVisible(false);
			Iniko->characterJumpingRight->setVisible(false);
		}

		else if (Iniko->wallTouch != NULL && Iniko->wallTouchSide == 'L')
		{
			if (!Iniko->jumping)
			{
				Iniko->facingRight = false;

				//Iniko->characterIdleLeft->setPosition(Iniko->characterIdleLeft->getPosition().x - (800 * dt), Iniko->characterIdleLeft->getPosition().y);
				//Iniko->characterIdleLeftCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));
				/*Iniko->characterRunningRightCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterRunningLeftCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleRightCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleLeftCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));*/

				Iniko->velocity = -1;

				Iniko->characterIdlerightspritebatch->setVisible(false);
				Iniko->characterIdleleftspritebatch->setVisible(false);
				Iniko->characterRunningRightspritebatch->setVisible(false);
				Iniko->characterRunningLeftspritebatch->setVisible(true);
				Iniko->characterJumpingLeft->setVisible(false);
				Iniko->characterJumpingRight->setVisible(false);

				Iniko->wallTouch = NULL;
				Iniko->wallTouchSide = ' ';
			}

			else
			{
				Iniko->facingRight = false;

				//Iniko->characterIdleLeft->setPosition(Iniko->characterIdleLeft->getPosition().x - (800 * dt), Iniko->characterIdleLeft->getPosition().y);
				//Iniko->characterIdleLeftCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));
				/*Iniko->characterRunningRightCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterRunningLeftCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleRightCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleLeftCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));*/

				Iniko->velocity = -1;

				Iniko->characterIdlerightspritebatch->setVisible(false);
				Iniko->characterIdleleftspritebatch->setVisible(false);
				Iniko->characterRunningRightspritebatch->setVisible(false);
				Iniko->characterRunningLeftspritebatch->setVisible(false);
				Iniko->characterJumpingLeft->setVisible(true);
				Iniko->characterJumpingRight->setVisible(false);

				Iniko->wallTouch = NULL;
				Iniko->wallTouchSide = ' ';
			}
		}

		else if (Iniko->wallTouch != NULL && Iniko->wallTouchSide == 'R')
		{
			if (!Iniko->jumping)
			{
				Iniko->characterIdlerightspritebatch->setVisible(false);
				Iniko->characterIdleleftspritebatch->setVisible(true);
				Iniko->characterRunningLeftspritebatch->setVisible(false);
				Iniko->characterRunningRightspritebatch->setVisible(false);
				Iniko->characterJumpingLeft->setVisible(false);
				Iniko->characterJumpingRight->setVisible(false);

				//Iniko->characterIdleLeftCollider->setVelocity(Vec2(0, Iniko->characterIdleRightCollider->getVelocity().y));
				/*Iniko->characterRunningRightCollider->setVelocity(Vec2(0, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterRunningLeftCollider->setVelocity(Vec2(0, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleRightCollider->setVelocity(Vec2(0, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleLeftCollider->setVelocity(Vec2(0, Iniko->characterIdleRightCollider->getVelocity().y));*/

				Iniko->velocity = 0;
			}

			else
			{
				Iniko->characterIdlerightspritebatch->setVisible(false);
				Iniko->characterIdleleftspritebatch->setVisible(false);
				Iniko->characterRunningLeftspritebatch->setVisible(false);
				Iniko->characterRunningRightspritebatch->setVisible(false);
				Iniko->characterJumpingLeft->setVisible(true);
				Iniko->characterJumpingRight->setVisible(false);

				Iniko->characterJumpingRightCollider->setVelocity(Vec2(0, Iniko->characterJumpingRightCollider->getVelocity().y));
				Iniko->characterJumpingLeftCollider->setVelocity(Vec2(0, Iniko->characterJumpingLeftCollider->getVelocity().y));
				Iniko->characterRunningRightCollider->setVelocity(Vec2(0, Iniko->characterRunningRightCollider->getVelocity().y));
				Iniko->characterRunningLeftCollider->setVelocity(Vec2(0, Iniko->characterRunningLeftCollider->getVelocity().y));
				Iniko->characterIdleRightCollider->setVelocity(Vec2(0, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleLeftCollider->setVelocity(Vec2(0, Iniko->characterIdleLeftCollider->getVelocity().y));

				Iniko->velocity = 0;
			}
		}
	}

	else
		Iniko->velocity = 0;

	//GENERAL MOVEMENT

	//STEALTH MOVEMENT

	if (moveLeft && moveRight && !moveCam && Iniko->stealth && !Iniko->hide)
	{
		Iniko->characterIdlerightspritebatch->setVisible(true);
		Iniko->characterIdleleftspritebatch->setVisible(false);
		Iniko->characterRunningRightspritebatch->setVisible(false);
		Iniko->characterRunningLeftspritebatch->setVisible(false);
		Iniko->characterJumpingLeft->setVisible(false);
		Iniko->characterJumpingRight->setVisible(false);
	}

	else if (moveRight && !moveCam && Iniko->stealth && !Iniko->hide /*&& !Iniko->jumping*/)
	{
		if (Iniko->wallTouch == NULL)
		{
			Iniko->facingRight = true;

			//Iniko->characterIdleRight->setPosition(Iniko->characterIdleRight->getPosition().x + (800 * dt), Iniko->characterIdleRight->getPosition().y);
			//Iniko->characterIdleRightCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));
			/*Iniko->characterRunningRightCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));
			Iniko->characterRunningLeftCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));
			Iniko->characterIdleRightCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));
			Iniko->characterIdleLeftCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));*/

			Iniko->velocity = 0.5;

			Iniko->characterIdlerightspritebatch->setVisible(true);
			Iniko->characterIdleleftspritebatch->setVisible(false);
			Iniko->characterRunningLeftspritebatch->setVisible(false);
			Iniko->characterRunningRightspritebatch->setVisible(false);
			Iniko->characterJumpingLeft->setVisible(false);
			Iniko->characterJumpingRight->setVisible(false);
		}

		else if (Iniko->wallTouch != NULL && Iniko->wallTouchSide == 'R')
		{
			if (!Iniko->jumping)
			{
				Iniko->facingRight = true;

				//Iniko->characterIdleRight->setPosition(Iniko->characterIdleRight->getPosition().x + (800 * dt), Iniko->characterIdleRight->getPosition().y);
				//Iniko->characterIdleRightCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));
				/*Iniko->characterRunningRightCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterRunningLeftCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleRightCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleLeftCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));*/

				Iniko->velocity = 0.5;

				Iniko->characterIdlerightspritebatch->setVisible(false);
				Iniko->characterIdleleftspritebatch->setVisible(false);
				Iniko->characterRunningLeftspritebatch->setVisible(false);
				Iniko->characterRunningRightspritebatch->setVisible(true);
				Iniko->characterJumpingLeft->setVisible(false);
				Iniko->characterJumpingRight->setVisible(false);

				Iniko->wallTouch = NULL;
				Iniko->wallTouchSide = ' ';
			}

			else
			{
				Iniko->facingRight = true;

				//Iniko->characterIdleRight->setPosition(Iniko->characterIdleRight->getPosition().x + (800 * dt), Iniko->characterIdleRight->getPosition().y);
				//Iniko->characterIdleRightCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));
				/*Iniko->characterRunningRightCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterRunningLeftCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleRightCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleLeftCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));*/

				Iniko->velocity = 0.5;

				Iniko->characterIdlerightspritebatch->setVisible(false);
				Iniko->characterIdleleftspritebatch->setVisible(false);
				Iniko->characterRunningLeftspritebatch->setVisible(false);
				Iniko->characterRunningRightspritebatch->setVisible(false);
				Iniko->characterJumpingLeft->setVisible(false);
				Iniko->characterJumpingRight->setVisible(true);

				Iniko->wallTouch = NULL;
				Iniko->wallTouchSide = ' ';
			}
		}

		else if (Iniko->wallTouch != NULL && Iniko->wallTouchSide == 'L')
		{
			if (!Iniko->jumping)
			{
				Iniko->characterIdlerightspritebatch->setVisible(true);
				Iniko->characterIdleleftspritebatch->setVisible(false);
				Iniko->characterRunningLeftspritebatch->setVisible(false);
				Iniko->characterRunningRightspritebatch->setVisible(false);
				Iniko->characterJumpingLeft->setVisible(false);
				Iniko->characterJumpingRight->setVisible(false);

				//Iniko->characterIdleRightCollider->setVelocity(Vec2(0, Iniko->characterIdleRightCollider->getVelocity().y));
				/*Iniko->characterRunningRightCollider->setVelocity(Vec2(0, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterRunningLeftCollider->setVelocity(Vec2(0, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleRightCollider->setVelocity(Vec2(0, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleLeftCollider->setVelocity(Vec2(0, Iniko->characterIdleRightCollider->getVelocity().y));*/

				Iniko->velocity = 0;
			}

			else
			{
				Iniko->characterIdlerightspritebatch->setVisible(false);
				Iniko->characterIdleleftspritebatch->setVisible(false);
				Iniko->characterRunningLeftspritebatch->setVisible(false);
				Iniko->characterRunningRightspritebatch->setVisible(false);
				Iniko->characterJumpingLeft->setVisible(false);
				Iniko->characterJumpingRight->setVisible(true);

				Iniko->characterJumpingRightCollider->setVelocity(Vec2(0, Iniko->characterJumpingRightCollider->getVelocity().y));
				Iniko->characterJumpingLeftCollider->setVelocity(Vec2(0, Iniko->characterJumpingLeftCollider->getVelocity().y));
				Iniko->characterRunningRightCollider->setVelocity(Vec2(0, Iniko->characterRunningRightCollider->getVelocity().y));
				Iniko->characterRunningLeftCollider->setVelocity(Vec2(0, Iniko->characterRunningLeftCollider->getVelocity().y));
				Iniko->characterIdleRightCollider->setVelocity(Vec2(0, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleLeftCollider->setVelocity(Vec2(0, Iniko->characterIdleLeftCollider->getVelocity().y));

				Iniko->velocity = 0;
			}
		}
	}

	else if (moveLeft && !moveCam && Iniko->stealth && !Iniko->hide/* && !Iniko->jumping*/)
	{
		if (Iniko->wallTouch == NULL)
		{
			Iniko->facingRight = false;

			//Iniko->characterIdleLeft->setPosition(Iniko->characterIdleLeft->getPosition().x - (800 * dt), Iniko->characterIdleLeft->getPosition().y);
			//Iniko->characterIdleLeftCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));
			/*Iniko->characterRunningRightCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));
			Iniko->characterRunningLeftCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));
			Iniko->characterIdleRightCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));
			Iniko->characterIdleLeftCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));*/

			Iniko->velocity = -0.5;

			Iniko->characterIdlerightspritebatch->setVisible(false);
			Iniko->characterIdleleftspritebatch->setVisible(false);
			Iniko->characterRunningRightspritebatch->setVisible(false);
			Iniko->characterRunningLeftspritebatch->setVisible(true);
			Iniko->characterJumpingLeft->setVisible(false);
			Iniko->characterJumpingRight->setVisible(false);
		}

		else if (Iniko->wallTouch != NULL && Iniko->wallTouchSide == 'L')
		{
			if (!Iniko->jumping)
			{
				Iniko->facingRight = false;

				//Iniko->characterIdleLeft->setPosition(Iniko->characterIdleLeft->getPosition().x - (800 * dt), Iniko->characterIdleLeft->getPosition().y);
				//Iniko->characterIdleLeftCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));
				/*Iniko->characterRunningRightCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterRunningLeftCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleRightCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleLeftCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));*/

				Iniko->velocity = -0.5;

				Iniko->characterIdlerightspritebatch->setVisible(false);
				Iniko->characterIdleleftspritebatch->setVisible(false);
				Iniko->characterRunningRightspritebatch->setVisible(false);
				Iniko->characterRunningLeftspritebatch->setVisible(true);
				Iniko->characterJumpingLeft->setVisible(false);
				Iniko->characterJumpingRight->setVisible(false);

				Iniko->wallTouch = NULL;
				Iniko->wallTouchSide = ' ';
			}

			else
			{
				Iniko->facingRight = false;

				//Iniko->characterIdleLeft->setPosition(Iniko->characterIdleLeft->getPosition().x - (800 * dt), Iniko->characterIdleLeft->getPosition().y);
				//Iniko->characterIdleLeftCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));
				/*Iniko->characterRunningRightCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterRunningLeftCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleRightCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleLeftCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));*/

				Iniko->velocity = -0.5;

				Iniko->characterIdlerightspritebatch->setVisible(false);
				Iniko->characterIdleleftspritebatch->setVisible(false);
				Iniko->characterRunningRightspritebatch->setVisible(false);
				Iniko->characterRunningLeftspritebatch->setVisible(false);
				Iniko->characterJumpingLeft->setVisible(true);
				Iniko->characterJumpingRight->setVisible(false);

				Iniko->wallTouch = NULL;
				Iniko->wallTouchSide = ' ';
			}
		}

		else if (Iniko->wallTouch != NULL && Iniko->wallTouchSide == 'R')
		{
			if (!Iniko->jumping)
			{
				Iniko->characterIdlerightspritebatch->setVisible(false);
				Iniko->characterIdleleftspritebatch->setVisible(true);
				Iniko->characterRunningLeftspritebatch->setVisible(false);
				Iniko->characterRunningRightspritebatch->setVisible(false);
				Iniko->characterJumpingLeft->setVisible(false);
				Iniko->characterJumpingRight->setVisible(false);

				//Iniko->characterIdleLeftCollider->setVelocity(Vec2(0, Iniko->characterIdleRightCollider->getVelocity().y));
				/*Iniko->characterRunningRightCollider->setVelocity(Vec2(0, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterRunningLeftCollider->setVelocity(Vec2(0, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleRightCollider->setVelocity(Vec2(0, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleLeftCollider->setVelocity(Vec2(0, Iniko->characterIdleRightCollider->getVelocity().y));*/

				Iniko->velocity = 0;
			}

			else
			{
				Iniko->characterIdlerightspritebatch->setVisible(false);
				Iniko->characterIdleleftspritebatch->setVisible(false);
				Iniko->characterRunningLeftspritebatch->setVisible(false);
				Iniko->characterRunningRightspritebatch->setVisible(false);
				Iniko->characterJumpingLeft->setVisible(true);
				Iniko->characterJumpingRight->setVisible(false);

				Iniko->characterJumpingRightCollider->setVelocity(Vec2(0, Iniko->characterJumpingRightCollider->getVelocity().y));
				Iniko->characterJumpingLeftCollider->setVelocity(Vec2(0, Iniko->characterJumpingLeftCollider->getVelocity().y));
				Iniko->characterRunningRightCollider->setVelocity(Vec2(0, Iniko->characterRunningRightCollider->getVelocity().y));
				Iniko->characterRunningLeftCollider->setVelocity(Vec2(0, Iniko->characterRunningLeftCollider->getVelocity().y));
				Iniko->characterIdleRightCollider->setVelocity(Vec2(0, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleLeftCollider->setVelocity(Vec2(0, Iniko->characterIdleLeftCollider->getVelocity().y));

				Iniko->velocity = 0;
			}
		}
	}

	//STEALTH MOVEMENT

	//STOPS IF MOVE IN TWO DIRECTIONS

	if (moveLeft && moveRight)
	{
		Iniko->facingRight = true;
		Iniko->characterIdlerightspritebatch->setVisible(true);
		Iniko->characterIdleleftspritebatch->setVisible(false);
		Iniko->characterRunningLeftspritebatch->setVisible(false);
		Iniko->characterRunningRightspritebatch->setVisible(false);
		Iniko->characterJumpingLeft->setVisible(false);
		Iniko->characterJumpingRight->setVisible(false);
	}

	//STOPS IF MOVE IN TWO DIRECTIONS

	//CHARACTER ART UPDATE

	if (Iniko->facingRight)
	{
		if (Iniko->jumping || contactFloor == NULL)
		{
			Iniko->runningSoundColliderSprite->setPosition(Iniko->characterJumpingRight->getPosition());
			Iniko->characterRunningLeft->setPosition(Iniko->characterJumpingRight->getPosition());
			Iniko->characterRunningRight->setPosition(Iniko->characterJumpingRight->getPosition());
			Iniko->characterIdleLeft->setPosition(Iniko->characterJumpingRight->getPosition());
			Iniko->characterIdleRight->setPosition(Iniko->characterJumpingRight->getPosition());
			Iniko->characterJumpingRight->setPosition(Iniko->characterJumpingRight->getPosition());
			Iniko->characterJumpingLeft->setPosition(Iniko->characterJumpingRight->getPosition());
			Iniko->characterVision->setPosition(Iniko->characterJumpingRight->getPosition());
			Iniko->AKey->setPosition(Iniko->characterJumpingRight->getPosition().x, Iniko->characterJumpingRight->getPosition().y + (Iniko->characterJumpingRight->getContentSize().height / 2 + 80));
			Iniko->SKey->setPosition(Iniko->characterJumpingRight->getPosition().x, Iniko->characterJumpingRight->getPosition().y + (Iniko->characterJumpingRight->getContentSize().height / 2 + 150));
		}

		else
		{
			Iniko->runningSoundColliderSprite->setPosition(Iniko->characterRunningRight->getPosition());
			Iniko->characterRunningLeft->setPosition(Iniko->characterRunningRight->getPosition());
			Iniko->characterRunningRight->setPosition(Iniko->characterRunningRight->getPosition());
			Iniko->characterIdleLeft->setPosition(Iniko->characterRunningRight->getPosition());
			Iniko->characterIdleRight->setPosition(Iniko->characterRunningRight->getPosition());
			Iniko->characterJumpingRight->setPosition(Iniko->characterRunningRight->getPosition().x, Iniko->characterRunningRight->getPosition().y + 3);
			Iniko->characterJumpingLeft->setPosition(Iniko->characterRunningRight->getPosition().x, Iniko->characterRunningRight->getPosition().y + 3);
			Iniko->characterVision->setPosition(Iniko->characterRunningRight->getPosition());
			Iniko->AKey->setPosition(Iniko->characterRunningRight->getPosition().x, Iniko->characterRunningRight->getPosition().y + (Iniko->characterRunningRight->getContentSize().height / 2 + 80));
			Iniko->SKey->setPosition(Iniko->characterRunningRight->getPosition().x, Iniko->characterRunningRight->getPosition().y + (Iniko->characterRunningRight->getContentSize().height / 2 + 150));
		}

		/*Iniko->runningSoundColliderSprite->setPosition(Iniko->characterIdleRight->getPosition());
		Iniko->characterRunningLeft->setPosition(Iniko->characterIdleRight->getPosition());
		Iniko->characterRunningRight->setPosition(Iniko->characterIdleRight->getPosition());
		Iniko->characterIdleLeft->setPosition(Iniko->characterIdleRight->getPosition());
		Iniko->characterIdleRight->setPosition(Iniko->characterIdleRight->getPosition());
		Iniko->characterVision->setPosition(Iniko->characterIdleRight->getPosition());
		Iniko->AKey->setPosition(Iniko->characterIdleRight->getPosition().x, Iniko->characterIdleRight->getPosition().y + (Iniko->characterIdleRight->getContentSize().height / 2 + 80));
		Iniko->SKey->setPosition(Iniko->characterIdleRight->getPosition().x, Iniko->characterIdleRight->getPosition().y + (Iniko->characterIdleRight->getContentSize().height / 2 + 150));*/
	}

	else if (!Iniko->facingRight)
	{
		if (Iniko->jumping || contactFloor == NULL)
		{
			Iniko->runningSoundColliderSprite->setPosition(Iniko->characterJumpingLeft->getPosition());
			Iniko->characterRunningLeft->setPosition(Iniko->characterJumpingLeft->getPosition());
			Iniko->characterRunningRight->setPosition(Iniko->characterJumpingLeft->getPosition());
			Iniko->characterIdleLeft->setPosition(Iniko->characterJumpingLeft->getPosition());
			Iniko->characterIdleRight->setPosition(Iniko->characterJumpingLeft->getPosition());
			Iniko->characterJumpingRight->setPosition(Iniko->characterJumpingLeft->getPosition());
			Iniko->characterJumpingLeft->setPosition(Iniko->characterJumpingLeft->getPosition());
			Iniko->characterVision->setPosition(Iniko->characterJumpingLeft->getPosition());
			Iniko->AKey->setPosition(Iniko->characterJumpingLeft->getPosition().x, Iniko->characterJumpingLeft->getPosition().y + (Iniko->characterJumpingLeft->getContentSize().height / 2 + 80));
			Iniko->SKey->setPosition(Iniko->characterJumpingLeft->getPosition().x, Iniko->characterJumpingLeft->getPosition().y + (Iniko->characterJumpingLeft->getContentSize().height / 2 + 150));
		}

		else
		{
			Iniko->runningSoundColliderSprite->setPosition(Iniko->characterRunningLeft->getPosition());
			Iniko->characterRunningLeft->setPosition(Iniko->characterRunningLeft->getPosition());
			Iniko->characterRunningRight->setPosition(Iniko->characterRunningLeft->getPosition());
			Iniko->characterIdleLeft->setPosition(Iniko->characterRunningLeft->getPosition());
			Iniko->characterIdleRight->setPosition(Iniko->characterRunningLeft->getPosition());
			Iniko->characterJumpingRight->setPosition(Iniko->characterRunningLeft->getPosition().x, Iniko->characterRunningLeft->getPosition().y + 3);
			Iniko->characterJumpingLeft->setPosition(Iniko->characterRunningLeft->getPosition().x, Iniko->characterRunningLeft->getPosition().y + 3);
			Iniko->characterVision->setPosition(Iniko->characterRunningLeft->getPosition());
			Iniko->AKey->setPosition(Iniko->characterRunningLeft->getPosition().x, Iniko->characterRunningLeft->getPosition().y + (Iniko->characterRunningLeft->getContentSize().height / 2 + 80));
			Iniko->SKey->setPosition(Iniko->characterRunningLeft->getPosition().x, Iniko->characterRunningLeft->getPosition().y + (Iniko->characterRunningLeft->getContentSize().height / 2 + 150));
		}

		/*Iniko->runningSoundColliderSprite->setPosition(Iniko->characterIdleLeft->getPosition());
		Iniko->characterRunningLeft->setPosition(Iniko->characterIdleLeft->getPosition());
		Iniko->characterRunningRight->setPosition(Iniko->characterIdleLeft->getPosition());
		Iniko->characterIdleLeft->setPosition(Iniko->characterIdleLeft->getPosition());
		Iniko->characterIdleRight->setPosition(Iniko->characterIdleLeft->getPosition());
		Iniko->characterVision->setPosition(Iniko->characterIdleLeft->getPosition());
		Iniko->AKey->setPosition(Iniko->characterIdleLeft->getPosition().x, Iniko->characterIdleLeft->getPosition().y + (Iniko->characterIdleLeft->getContentSize().height / 2 + 80));
		Iniko->SKey->setPosition(Iniko->characterIdleLeft->getPosition().x, Iniko->characterIdleLeft->getPosition().y + (Iniko->characterIdleLeft->getContentSize().height / 2 + 150));*/
	}

	//CHARACTER ART UPDATE

	//SALTO UPDATE

	/*if (Iniko->jumping)
	{
	if (Iniko->facingRight)
	{
	Iniko->characterIdlerightspritebatch->setVisible(false);
	Iniko->characterIdleleftspritebatch->setVisible(false);
	Iniko->characterRunningLeftspritebatch->setVisible(false);
	Iniko->characterRunningRightspritebatch->setVisible(true);
	}

	else if (!Iniko->facingRight)
	{
	Iniko->characterIdlerightspritebatch->setVisible(false);
	Iniko->characterIdleleftspritebatch->setVisible(false);
	Iniko->characterRunningLeftspritebatch->setVisible(true);
	Iniko->characterRunningRightspritebatch->setVisible(false);
	}
	}*/

	//WALL COLLISION

	if (Iniko->wallTouch != NULL)
	{
		if (!Iniko->facingRight && (Iniko->characterIdleLeft->getPosition().x - Iniko->characterIdleLeft->getContentSize().width / 2) > (Iniko->wallTouch->getPosition().x + Iniko->wallTouch->getContentSize().width / 2))
		{
			Iniko->wallTouchSide = 'R';
		}

		else if (Iniko->facingRight && (Iniko->characterIdleRight->getPosition().x + Iniko->characterIdleLeft->getContentSize().width / 2) < (Iniko->wallTouch->getPosition().x - Iniko->wallTouch->getContentSize().width / 2))
		{
			Iniko->wallTouchSide = 'L';
		}
	}

	//JUMPING UPDATE

	if (Iniko->jumping || (Iniko->characterJumpingRightCollider->getVelocity().y < 0) || (Iniko->characterJumpingLeftCollider->getVelocity().y < 0))
	{
		Iniko->characterIdleLeftCollider->setGravityEnable(true);
		Iniko->characterIdleRightCollider->setGravityEnable(true);
		Iniko->characterRunningRightCollider->setGravityEnable(true);
		Iniko->characterRunningLeftCollider->setGravityEnable(true);
		Iniko->characterJumpingRightCollider->setGravityEnable(true);
		Iniko->characterJumpingLeftCollider->setGravityEnable(true);

		Iniko->characterIdlerightspritebatch->setVisible(false);
		Iniko->characterRunningRightspritebatch->setVisible(false);
		Iniko->characterIdleleftspritebatch->setVisible(false);
		Iniko->characterRunningLeftspritebatch->setVisible(false);

		if (Iniko->facingRight)
		{
			Iniko->characterJumpingRight->setVisible(true);
			Iniko->characterJumpingLeft->setVisible(false);

			/*Iniko->runningSoundColliderSprite->setPosition(Iniko->characterJumpingRight->getPosition());
			Iniko->characterRunningLet->setPosition(Iniko->characterJumpingRight->getPosition());
			Iniko->characterRunningRight->setPosition(Iniko->characterJumpingRight->getPosition());
			Iniko->characterIdleLeft->setPosition(Iniko->characterJumpingRight->getPosition());
			Iniko->characterIdleRight->setPosition(Iniko->characterJumpingRight->getPosition());
			Iniko->characterVision->setPosition(Iniko->characterJumpingRight->getPosition());
			Iniko->AKey->setPosition(Iniko->characterJumpingRight->getPosition().x, Iniko->characterJumpingRight->getPosition().y + (Iniko->characterJumpingRight->getContentSize().height / 2 + 80));
			Iniko->SKey->setPosition(Iniko->characterJumpingRight->getPosition().x, Iniko->characterJumpingRight->getPosition().y + (Iniko->characterJumpingRight->getContentSize().height / 2 + 150));*/
		}

		else
		{
			Iniko->characterJumpingRight->setVisible(false);
			Iniko->characterJumpingLeft->setVisible(true);

			/*Iniko->runningSoundColliderSprite->setPosition(Iniko->characterJumpingLeft->getPosition());
			Iniko->characterRunningLeft->setPosition(Iniko->characterJumpingLeft->getPosition());
			Iniko->characterRunningRight->setPosition(Iniko->characterJumpingLeft->getPosition());
			Iniko->characterIdleLeft->setPosition(Iniko->characterJumpingLeft->getPosition());
			Iniko->characterIdleRight->setPosition(Iniko->characterJumpingLeft->getPosition());
			Iniko->characterVision->setPosition(Iniko->characterJumpingLeft->getPosition());
			Iniko->AKey->setPosition(Iniko->characterJumpingLeft->getPosition().x, Iniko->characterJumpingLeft->getPosition().y + (Iniko->characterJumpingLeft->getContentSize().height / 2 + 80));
			Iniko->SKey->setPosition(Iniko->characterJumpingLeft->getPosition().x, Iniko->characterJumpingLeft->getPosition().y + (Iniko->characterJumpingLeft->getContentSize().height / 2 + 150));*/
		}
	}

	if (key == 'S' && !Iniko->jumping && Iniko->characterJumpingLeftCollider->getVelocity().y >= 0 && Iniko->characterJumpingRightCollider->getVelocity().y >= 0)
	{
		if (Iniko->facingRight)
		{
			//moveCam = true;

			/*Iniko->runningSoundColliderSprite->setZOrder(4);
			Iniko->characterIdlerightspritebatch->setZOrder(4);
			Iniko->characterRunningRightspritebatch->setZOrder(4);
			Iniko->characterIdleleftspritebatch->setZOrder(4);
			Iniko->characterRunningLeftspritebatch->setZOrder(4);
			Iniko->characterVision->setZOrder(4);
			Iniko->AKey->setZOrder(4);
			Iniko->SKey->setZOrder(4);*/

			Iniko->jumping = true;

			Iniko->characterJumpingRight->setPositionY(Iniko->characterRunningRight->getPosition().y + 50);

			//Iniko->characterJumpingRightCollider->setGravityEnable(true);
			Iniko->characterJumpingRightCollider->setVelocity(Vec2(Iniko->characterRunningRightCollider->getVelocity().x, 750));

			Iniko->characterJumpingLeft->setPositionY(Iniko->characterRunningRight->getPosition().y + 50);

			//Iniko->characterJumpingLeftCollider->setGravityEnable(true);
			Iniko->characterJumpingLeftCollider->setVelocity(Vec2(Iniko->characterRunningLeftCollider->getVelocity().x, 750));
			/*
			//Iniko->characterRunningRight->setPosition(Point(Iniko->characterRunningRight->getPosition().x, Iniko->characterRunningRight->getPosition().y + 5));
			Iniko->characterRunningRightCollider->setGravityEnable(true);
			Iniko->characterRunningRightCollider->setVelocity(Vec2(Iniko->characterRunningRightCollider->getVelocity().x, 500));
			//Iniko->characterRunningRightCollider->setVelocity(Vec2(Iniko->characterRunningRightCollider->getVelocity().x, 500));

			//Iniko->characterRunningLeft->setPosition(Point(Iniko->characterRunningLeft->getPosition().x, Iniko->characterRunningLeft->getPosition().y + 5));
			//Iniko->characterRunningLeftCollider->setVelocity(Vec2(Iniko->characterRunningLeftCollider->getVelocity().x, 500));
			Iniko->characterRunningLeftCollider->setGravityEnable(true);
			Iniko->characterRunningLeftCollider->setVelocity(Vec2(Iniko->characterRunningRightCollider->getVelocity().x, 500));

			//Iniko->characterIdleRight->setPosition(Point(Iniko->characterIdleRight->getPosition().x, Iniko->characterIdleRight->getPosition().y + 5));
			//Iniko->characterIdleRightCollider->setVelocity(Vec2(Iniko->characterIdleRightCollider->getVelocity().x, 500));
			Iniko->characterIdleRightCollider->setGravityEnable(true);
			Iniko->characterIdleRightCollider->setVelocity(Vec2(Iniko->characterRunningRightCollider->getVelocity().x, 500));

			//Iniko->characterIdleLeft->setPosition(Point(Iniko->characterIdleLeft->getPosition().x, Iniko->characterIdleLeft->getPosition().y + 5));
			//Iniko->characterIdleLeftCollider->setVelocity(Vec2(Iniko->characterIdleLeftCollider->getVelocity().x, 500));
			Iniko->characterIdleLeftCollider->setGravityEnable(true);
			Iniko->characterIdleLeftCollider->setVelocity(Vec2(Iniko->characterRunningRightCollider->getVelocity().x, 500));*/
		}

		if (!Iniko->facingRight)
		{
			//moveCam = true;

			/*Iniko->runningSoundColliderSprite->setZOrder(4);
			Iniko->characterIdlerightspritebatch->setZOrder(4);
			Iniko->characterRunningRightspritebatch->setZOrder(4);
			Iniko->characterIdleleftspritebatch->setZOrder(4);
			Iniko->characterRunningLeftspritebatch->setZOrder(4);
			Iniko->characterVision->setZOrder(4);
			Iniko->AKey->setZOrder(4);
			Iniko->SKey->setZOrder(4);*/

			Iniko->jumping = true;

			Iniko->characterJumpingLeft->setPositionY(Iniko->characterRunningLeft->getPosition().y + 50);

			//Iniko->characterJumpingLeftCollider->setGravityEnable(true);
			Iniko->characterJumpingLeftCollider->setVelocity(Vec2(Iniko->characterRunningLeftCollider->getVelocity().x, 750));

			Iniko->characterJumpingRight->setPositionY(Iniko->characterRunningRight->getPosition().y + 50);

			//Iniko->characterJumpingRightCollider->setGravityEnable(true);
			Iniko->characterJumpingRightCollider->setVelocity(Vec2(Iniko->characterRunningRightCollider->getVelocity().x, 750));
			/*
			//Iniko->characterRunningRight->setPosition(Point(Iniko->characterRunningRight->getPosition().x, Iniko->characterRunningRight->getPosition().y + 5));
			//Iniko->characterRunningRightCollider->setVelocity(Vec2(Iniko->characterRunningRightCollider->getVelocity().x, 500));
			Iniko->characterRunningRightCollider->setGravityEnable(true);
			Iniko->characterRunningRightCollider->setVelocity(Vec2(Iniko->characterRunningLeftCollider->getVelocity().x, 500));

			//Iniko->characterRunningLeft->setPosition(Point(Iniko->characterRunningRight->getPosition().x, Iniko->characterRunningRight->getPosition().y + 5));
			//Iniko->characterRunningLeftCollider->setVelocity(Vec2(Iniko->characterRunningLeftCollider->getVelocity().x, 500));
			Iniko->characterRunningLeftCollider->setGravityEnable(true);
			Iniko->characterRunningLeftCollider->setVelocity(Vec2(Iniko->characterRunningLeftCollider->getVelocity().x, 500));

			//Iniko->characterIdleRight->setPosition(Point(Iniko->characterIdleRight->getPosition().x, Iniko->characterIdleRight->getPosition().y + 5));
			//Iniko->characterIdleRightCollider->setVelocity(Vec2(Iniko->characterIdleRightCollider->getVelocity().x, 500));
			Iniko->characterIdleRightCollider->setGravityEnable(true);
			Iniko->characterIdleRightCollider->setVelocity(Vec2(Iniko->characterRunningLeftCollider->getVelocity().x, 500));

			//Iniko->characterIdleLeft->setPosition(Point(Iniko->characterIdleLeft->getPosition().x, Iniko->characterIdleLeft->getPosition().y + 5));
			//Iniko->characterIdleLeftCollider->setVelocity(Vec2(Iniko->characterIdleLeftCollider->getVelocity().x, 500));
			Iniko->characterIdleLeftCollider->setGravityEnable(true);
			Iniko->characterIdleLeftCollider->setVelocity(Vec2(Iniko->characterRunningLeftCollider->getVelocity().x, 500));*/
		}
	}

	/*if (Iniko->SKey->isVisible())
	{
	if (key == 'S')
	{
	//moveRight = false;
	//moveLeft = false;
	moveCam = true;

	Iniko->runningSoundColliderSprite->setZOrder(4);
	Iniko->characterIdlerightspritebatch->setZOrder(4);
	Iniko->characterRunningRightspritebatch->setZOrder(4);
	Iniko->characterIdleleftspritebatch->setZOrder(4);
	Iniko->characterRunningLeftspritebatch->setZOrder(4);
	Iniko->characterVision->setZOrder(4);
	Iniko->AKey->setZOrder(4);
	Iniko->SKey->setZOrder(4);

	Iniko->jumping = true;

	if (Iniko->facingRight)
	{
	Iniko->characterIdleRight->setPosition(Point(Iniko->characterIdleRight->getPosition().x, Iniko->characterIdleRight->getPosition().y + 5));
	Iniko->characterIdleRightCollider->setVelocity(objectsVector.at(contactBody->getTag() - 4000)->force);
	}

	else
	{
	Iniko->characterIdleLeft->setPosition(Point(Iniko->characterIdleLeft->getPosition().x, Iniko->characterIdleLeft->getPosition().y + 5));
	Iniko->characterIdleLeftCollider->setVelocity(objectsVector.at(contactBody->getTag() - 4000)->force);
	}
	}
	}*/

	//FALLING UPDATE

	if (Iniko->characterJumpingRightCollider->getVelocity().y < 0 || Iniko->characterJumpingLeftCollider->getVelocity().y < 0)
	{
		/*if (Iniko->characterIdleRightCollider->getVelocity().x == 0 && Iniko->characterIdleLeftCollider->getVelocity().x == 0)
		{
		Iniko->runningSoundColliderSprite->setZOrder(5);
		Iniko->characterIdlerightspritebatch->setZOrder(5);
		Iniko->characterRunningRightspritebatch->setZOrder(5);
		Iniko->characterIdleleftspritebatch->setZOrder(5);
		Iniko->characterRunningLeftspritebatch->setZOrder(5);
		Iniko->characterVision->setZOrder(5);
		Iniko->AKey->setZOrder(5);
		Iniko->SKey->setZOrder(5);
		}*/

		//Iniko->jumping = false;

		/*if (Iniko->facingRight)
		{
		Iniko->characterIdlerightspritebatch->setVisible(true);
		Iniko->characterIdleleftspritebatch->setVisible(false);
		}

		else
		{
		Iniko->characterIdlerightspritebatch->setVisible(false);
		Iniko->characterIdleleftspritebatch->setVisible(true);
		}

		//moveRight = false;
		//moveLeft = false;
		//moveCam = true;
		Iniko->characterRunningLeftspritebatch->setVisible(false);
		Iniko->characterRunningRightspritebatch->setVisible(false);*/
	}

	//FALLING UPDATE

	//KEY PRESSED HANDLER

	if (key == 'W' && (contactBody->getTag() / 100) == 20)
	{
		moveCam = true;

		AKeyCounter += 250 * Iniko->forceRet * dt;

		if (AKeyCounter >= 500)
		{
			Iniko->forceRet = -1;
		}

		else if (AKeyCounter <= 5)
		{
			Iniko->forceRet = 1;
		}

		Iniko->forceBar->setPosition(Iniko->characterIdleRight->getPosition().x - 85, Iniko->characterIdleRight->getPosition().y - 170);
		Iniko->forceBarBorder->setPosition(Iniko->forceBar->getPosition().x + Iniko->forceBarBorder->getContentSize().width / 2, Iniko->forceBar->getPosition().y + Iniko->forceBarBorder->getContentSize().height / 2);
		Iniko->forceBarBorder->setVisible(true);
		Iniko->forceBar->setVisible(true);
		Iniko->forceBar->setPercentage(AKeyCounter / 5);
	}

	else if (key == ' ' && (contactBody->getTag() / 100) == 20)
	{
		moveCam = false;

		if (AKeyCounter > 0)
		{
			followObject = contactBody->getNode();
			objectsVector.at(contactBody->getTag() - 2000)->getThrow(Iniko->facingRight, AKeyCounter);
			Iniko->forceBarBorder->setVisible(false);
			Iniko->forceBar->setVisible(false);
			Iniko->forceBar->setPercentage(0);
			Iniko->forceRet = 1;
			AKeyCounter = 0;
		}
	}

	else
	{
		Iniko->forceBarBorder->setVisible(false);
		Iniko->forceBar->setVisible(false);
		Iniko->forceBar->setPercentage(0);
		Iniko->forceRet = 1;
		AKeyCounter = 0;
	}

	if (Iniko->hide)
	{
		if (key == 'D')
		{
			Iniko->getHide(false);
			key == ' ';
		}
	}

	/*if (key == '1' && !power1->finish && !power1->activated)
	{
	if (Iniko->facingRight)
	power1->rightDirection = true;

	else
	power1->rightDirection = false;

	power1->activated = true;
	power1->flyParticle->setVisible(true);
	power1->flyParticleSmoke->setVisible(true);
	power1->flyParticleCollider->setEnable(true);
	power1->initialPos = Iniko->characterVision->getPosition().x;
	}

	if (key == '2' && !power2->finish && !power2->activated)
	{
	power2->activated = true;
	//power2->shadowParticle->setVisible(true);

	//Iniko->runningSoundCollider->setEnable(false);
	Iniko->characterIdleRight->setOpacity(128);
	//Iniko->characterIdleRightCollider->setEnable(false);
	Iniko->characterIdleLeft->setOpacity(128);
	//Iniko->characterIdleLeftCollider->setEnable(false);
	Iniko->characterRunningRight->setOpacity(128);
	//Iniko->characterRunningRightCollider->setEnable(false);
	Iniko->characterRunningLeft->setOpacity(128);
	//Iniko->characterRunningLeftCollider->setEnable(false);

	power2->ended(5);
	}*/

	//KEY PRESSED HANDLER

	//CHECK RUNNING SOUND

	if (Iniko->stealth || (!moveRight && !moveLeft) || Iniko->hide || power2->activated || Iniko->jumping)
		Iniko->runningSoundCollider->setEnable(false);

	else
		Iniko->runningSoundCollider->setEnable(true);

	//CHECK RUNNING SOUND

	//FLOOR COLLISION UPDATE

	if (contactFloor != NULL)
	{
		if (Iniko->facingRight)
		{
			if ((Iniko->characterIdleRight->getPosition().y - Iniko->characterIdleRight->getContentSize().height / 2) < (contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 - 10))
			{
				Iniko->characterIdleRight->setPosition(Point(Iniko->characterIdleRight->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + Iniko->characterIdleRight->getContentSize().height / 2 - 5));
			}

			if ((Iniko->characterRunningRight->getPosition().y - Iniko->characterRunningRight->getContentSize().height / 2) < (contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 - 10))
			{
				Iniko->characterRunningRight->setPosition(Point(Iniko->characterRunningRight->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + Iniko->characterRunningRight->getContentSize().height / 2 - 5));
			}

			if ((Iniko->characterJumpingRight->getPosition().y - Iniko->characterJumpingRight->getContentSize().height / 2) < (contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 - 5))
			{
				Iniko->characterJumpingRight->setPosition(Point(Iniko->characterJumpingRight->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + 157));
			}
		}

		else if (!Iniko->facingRight)
		{
			if ((Iniko->characterIdleLeft->getPosition().y - Iniko->characterIdleLeft->getContentSize().height / 2) < (contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 - 10))
			{
				Iniko->characterIdleLeft->setPosition(Point(Iniko->characterIdleLeft->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + Iniko->characterIdleLeft->getContentSize().height / 2 - 5));
			}

			if ((Iniko->characterRunningLeft->getPosition().y - Iniko->characterRunningLeft->getContentSize().height / 2) < (contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 - 10))
			{
				Iniko->characterRunningLeft->setPosition(Point(Iniko->characterRunningLeft->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + Iniko->characterRunningLeft->getContentSize().height / 2 - 5));
			}

			if ((Iniko->characterJumpingLeft->getPosition().y - Iniko->characterJumpingLeft->getContentSize().height / 2) < (contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 - 5))
			{
				Iniko->characterJumpingLeft->setPosition(Point(Iniko->characterJumpingLeft->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + 157));
			}
		}
	}

	//FLOOR COLLISION UPDATE

	//COLLISION UPDATE

	switch (contactEnemy->getTag() / 100)
	{
	case 10:														//ENEMY
		if (enemysVector.at(contactEnemy->getTag() - 1000)->alertedEnemy && !power2->activated && !enemysVector.at(contactEnemy->getTag() - 1000)->stunned && !enemysVector.at(contactEnemy->getTag() - 1000)->die)
		{
			Iniko->die();
			moveRight = false;
			moveLeft = false;
			Iniko->characterVision->runAction(Sequence::create(DelayTime::create(3), CallFunc::create(CC_CALLBACK_0(Egypt::gameOver, this)), NULL));
		}

		else if (enemysVector.at(contactEnemy->getTag() - 1000)->facingRight && Iniko->facingRight && !enemysVector.at(contactEnemy->getTag() - 1000)->alertedEnemy && Iniko->stealth)
		{
			if (Iniko->characterIdleRight->getPosition().x > enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->getPosition().x + 50 && !enemysVector.at(contactEnemy->getTag() - 1000)->stunned && !enemysVector.at(contactEnemy->getTag() - 1000)->die)
			{
				enemysVector.at(contactEnemy->getTag() - 1000)->returning = false;
				enemysVector.at(contactEnemy->getTag() - 1000)->alertedSound = false;
				enemysVector.at(contactEnemy->getTag() - 1000)->alertedEnemy = true;
			}

			else if (key == 'Q' && !Iniko->hide)
			{
				enemysVector.at(contactEnemy->getTag() - 1000)->die = true;
				enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->setVisible(false);
				enemysVector.at(contactEnemy->getTag() - 1000)->enemyVision->setVisible(false);
				enemysVector.at(contactEnemy->getTag() - 1000)->detect->setVisible(false);
			}
		}

		else if (!enemysVector.at(contactEnemy->getTag() - 1000)->facingRight && !Iniko->facingRight && !enemysVector.at(contactEnemy->getTag() - 1000)->alertedEnemy && Iniko->stealth)
		{
			if (Iniko->characterIdleLeft->getPosition().x < enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->getPosition().x - 50 && !enemysVector.at(contactEnemy->getTag() - 1000)->stunned && !enemysVector.at(contactEnemy->getTag() - 1000)->die)
			{
				enemysVector.at(contactEnemy->getTag() - 1000)->returning = false;
				enemysVector.at(contactEnemy->getTag() - 1000)->alertedSound = false;
				enemysVector.at(contactEnemy->getTag() - 1000)->alertedEnemy = true;
			}

			else if (key == 'Q' && !Iniko->hide)
			{
				enemysVector.at(contactEnemy->getTag() - 1000)->die = true;
				enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->setVisible(false);
				enemysVector.at(contactEnemy->getTag() - 1000)->enemyVision->setVisible(false);
				enemysVector.at(contactEnemy->getTag() - 1000)->detect->setVisible(false);
			}
		}

		else if (!enemysVector.at(contactEnemy->getTag() - 1000)->stunned && !Iniko->stealth && !enemysVector.at(contactEnemy->getTag() - 1000)->die)
		{
			Iniko->die();
			moveRight = false;
			moveLeft = false;
			Iniko->characterVision->runAction(Sequence::create(DelayTime::create(3), CallFunc::create(CC_CALLBACK_0(Egypt::gameOver, this)), NULL));
		}

		break;
	}

	switch (contactBody->getTag() / 100)
	{
	case 20:														//THROWABLE OBJECT
																	/*if (key == ' ' && AKeyCounter > 0)
																	{
																	followObject = contactBody->getNode();
																	objectsVector.at(contactBody->getTag() - 2000)->getThrow(Iniko->facingRight, AKeyCounter);
																	}*/
		break;

	case 30:														//OBJECTO TO HIDE
		if (key == 'U')
		{
			if (!Iniko->hide)
				Iniko->getHide(true);
		}
		break;

	}

	//COLLISION UPDATE

	//CAMERA FOLLOW AND ZOOM OUT UPDATE

	if (followObject != NULL)
	{
		Point screenCenter = Point(visibleSize.width / 2, visibleSize.height / 2);
		Point offSetToCenter = ccpSub(screenCenter, followObject->getPosition());

		this->setPosition(ccpMult(offSetToCenter, this->getScale()));
		this->setPositionY(this->getPositionY() - offSetToCenter.y);
	}

	else if (followObject == NULL)
	{
		Point screenCenter = Point(visibleSize.width / 2, visibleSize.height / 2);
		//Point offSetToCenter = ccpSub(screenCenter, Iniko->characterIdleRight->getPosition());
		Point offSetToCenter = ccpSub(screenCenter, Iniko->characterRunningRight->getPosition());

		this->setPosition(ccpMult(offSetToCenter, this->getScale()));
		this->setPositionY(this->getPositionY() - offSetToCenter.y - (Iniko->characterVision->getPosition().y - (313 / 2 + Floor1->getContentSize().height)));
	}

	//CAMERA FOLLOW AND ZOOM OUT UPDATE

	//OBJECT POSITION UPDATE WHEN THROW

	if (followObject != NULL)
	{
		//objectsVector.at(followObject->getTag() - 2000)->itemSound->setPosition(objectsVector.at(followObject->getTag() - 2000)->itemArt->getPosition());
		moveCam = true;
	}

	//OBJECT POSITION UPDATE WHEN THROW
}

void Egypt::setPhysicsWorld(PhysicsWorld *world)
{
	mWorld = world;
	mWorld->setGravity(Vec2(0, -1000));
}

bool Egypt::onContactBegin(PhysicsContact &contact)
{
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();

	if (bodyA->getTag() / 100 == 90)										//IF CHARACTER COLLIDES WITH..
	{
		switch (bodyB->getTag() / 100)
		{
		case 30:													//..AN OBJECT TO HIDE
			contactBody = bodyB;
			break;

		case 10:													//..AN ENEMY
			if (!enemysVector.at(bodyB->getTag() - 1000)->die)
				contactEnemy = bodyB;
			break;

		case 20:													//..A THROWABLE OBJECT
			contactBody = bodyB;
			Iniko->AKey->setVisible(true);
			break;

		case 40:													//..A JUMP ZONE
			contactBody = bodyB;
			break;
		}
	}

	if (bodyB->getTag() / 100 == 90)										//IF CHARACTER COLLIDES WITH..
	{
		switch (bodyA->getTag() / 100)
		{
		case 30:													//..AN OBJECT TO HIDE
			contactBody = bodyA;
			break;

		case 10:													//..AN ENEMY
			if (!enemysVector.at(bodyA->getTag() - 1000)->die)
				contactEnemy = bodyA;
			break;

		case 20:													//..A THROWABLE OBJECT
			contactBody = bodyA;
			Iniko->AKey->setVisible(true);
			break;

		case 40:													//..A JUMP ZONE
			contactBody = bodyA;
			break;
		}
	}

	if (bodyA->getTag() / 100 == 11)									//IF ENEMY VISION COLLIDES WITH..
	{
		if (!enemysVector.at(bodyA->getTag() - 1100)->die && !enemysVector.at(bodyA->getTag() - 1100)->stunned)
		{
			switch (bodyB->getTag() / 100)
			{
			case 90:												//..CHARACTER
				if (!power2->activated)
				{
					enemysVector.at(bodyA->getTag() - 1100)->returning = false;
					enemysVector.at(bodyA->getTag() - 1100)->alertedSound = false;
					enemysVector.at(bodyA->getTag() - 1100)->alertedEnemy = true;
				}
				break;
			}
		}
	}

	if (bodyB->getTag() / 100 == 11)									//IF ENEMY VISION COLLIDES WITH..
	{
		if (!enemysVector.at(bodyB->getTag() - 1100)->die && !enemysVector.at(bodyB->getTag() - 1100)->stunned)
		{
			switch (bodyA->getTag() / 100)
			{
			case 90:												//..CHARACTER
				if (!power2->activated)
				{
					enemysVector.at(bodyB->getTag() - 1100)->returning = false;
					enemysVector.at(bodyB->getTag() - 1100)->alertedSound = false;
					enemysVector.at(bodyB->getTag() - 1100)->alertedEnemy = true;
				}
				break;
			}
		}
	}

	if (bodyA->getTag() / 100 == 10)									//IF ENEMY COLLIDES WITH..
	{
		if (!enemysVector.at(bodyA->getTag() - 1000)->die && !enemysVector.at(bodyA->getTag() - 1000)->stunned)
		{
			switch (bodyB->getTag() / 100)
			{
			case 91:												//..CHARACTER RUNNING SOUND
				if (!Iniko->stealth && !power2->activated)
				{
					enemysVector.at(bodyA->getTag() - 1000)->alertedSound = true;
					enemysVector.at(bodyA->getTag() - 1000)->followPos = Iniko->characterIdleRight->getPosition().x;
				}
				break;

			case 21:												//..ITEM SOUND
				enemysVector.at(bodyA->getTag() - 1000)->alertedSound = true;
				enemysVector.at(bodyA->getTag() - 1000)->followPos = objectsVector.at(bodyB->getTag() - 2100)->itemArt->getPosition().x;
				break;

			case 41:												//..FLY POWER
				enemysVector.at(bodyA->getTag() - 1000)->stunned = true;
				enemysVector.at(bodyA->getTag() - 1000)->enemyVision->setVisible(false);
				enemysVector.at(bodyA->getTag() - 1000)->detect->setVisible(false);
				//power1->flyParticle->setPosition(enemysVector.at(bodyA->getTag() - 1000)->getPosition());
				power1->flyParticleCollider->setEnable(false);
				power1->ended(3);
				enemysVector.at(bodyA->getTag() - 1000)->recovery();
				break;
			}
		}
	}

	if (bodyB->getTag() / 100 == 10)									//IF ENEMY COLLIDES WITH..
	{
		if (!enemysVector.at(bodyB->getTag() - 1000)->die && !enemysVector.at(bodyB->getTag() - 1000)->stunned)
		{
			switch (bodyA->getTag() / 100)
			{
			case 91:												//..CHARACTER RUNNING SOUND
				if (!Iniko->stealth && !power2->activated)
				{
					enemysVector.at(bodyB->getTag() - 1000)->alertedSound = true;
					enemysVector.at(bodyB->getTag() - 1000)->followPos = Iniko->characterIdleRight->getPosition().x;
				}
				break;

			case 21:												//..ITEM SOUND
				enemysVector.at(bodyB->getTag() - 1000)->alertedSound = true;
				enemysVector.at(bodyB->getTag() - 1000)->followPos = objectsVector.at(bodyA->getTag() - 2100)->itemArt->getPosition().x;
				break;

			case 41:												//..FLY POWER
				enemysVector.at(bodyB->getTag() - 1000)->stunned = true;
				enemysVector.at(bodyB->getTag() - 1000)->enemyVision->setVisible(false);
				enemysVector.at(bodyB->getTag() - 1000)->detect->setVisible(false);
				//power1->flyParticle->setPosition(enemysVector.at(bodyB->getTag() - 1000)->getPosition());
				power1->flyParticleCollider->setEnable(false);
				power1->ended(3);
				enemysVector.at(bodyB->getTag() - 1000)->recovery();
				break;
			}
		}
	}

	if (bodyB->getTag() == -1)											//IF FLOOR COLLIDES WITH..
	{
		switch (bodyA->getTag() / 100)
		{
		case 20:													//..AN OBJECT
			if (objectsVector.at(bodyA->getTag() - 2000)->thrown)
			{
				objectsVector.at(bodyA->getTag() - 2000)->itemArt->runAction(Sequence::create(CallFunc::create(CC_CALLBACK_0(Egypt::objectBehaviour, this, bodyA, 1)), DelayTime::create(0.1), CallFunc::create(CC_CALLBACK_0(Egypt::objectBehaviour, this, bodyA, 2)), NULL));
			}

			break;
		}

		//DEFAULT ACTIONS TO EVERYONE

		if (bodyA->getTag() / 100 == 90)
		{
			//if (!Iniko->jumping)
			//{
			/*if ((Iniko->characterIdleRightCollider->getVelocity().y < 0) && (Iniko->characterIdleLeftCollider->getVelocity().y < 0))
			{
			moveCam = false;
			}*/

			/*if ((Iniko->characterRunningRightCollider->getVelocity().y < 0) && (Iniko->characterRunningLeftCollider->getVelocity().y < 0))
			{
			moveCam = false;
			}*/

			if (Iniko->characterJumpingRightCollider->getVelocity().y < 0 || Iniko->characterJumpingLeftCollider->getVelocity().y < 0)
			{
				if (((Iniko->characterJumpingRight->getPosition().y) >(bodyB->getNode()->getPosition().y + bodyB->getNode()->getContentSize().height / 2)) || ((Iniko->characterJumpingLeft->getPosition().y) >(bodyB->getNode()->getPosition().y + bodyB->getNode()->getContentSize().height / 2)))
				{
					Iniko->jumping = false;
					Iniko->stealth = false;

					Iniko->characterJumpingRightCollider->setVelocity(Vec2(Iniko->characterJumpingRightCollider->getVelocity().x, 0));
					Iniko->characterJumpingLeftCollider->setVelocity(Vec2(Iniko->characterJumpingRightCollider->getVelocity().x, 0));
					Iniko->characterRunningRightCollider->setVelocity(Vec2(Iniko->characterJumpingRightCollider->getVelocity().x, 0));
					Iniko->characterRunningLeftCollider->setVelocity(Vec2(Iniko->characterJumpingRightCollider->getVelocity().x, 0));
					Iniko->characterIdleRightCollider->setVelocity(Vec2(Iniko->characterJumpingRightCollider->getVelocity().x, 0));
					Iniko->characterIdleLeftCollider->setVelocity(Vec2(Iniko->characterJumpingRightCollider->getVelocity().x, 0));

					//bodyA->setVelocity(Vec2::ZERO);
					Iniko->characterJumpingRightCollider->setGravityEnable(false);
					Iniko->characterJumpingLeftCollider->setGravityEnable(false);
					Iniko->characterRunningRightCollider->setGravityEnable(false);
					Iniko->characterRunningLeftCollider->setGravityEnable(false);
					Iniko->characterIdleRightCollider->setGravityEnable(false);
					Iniko->characterIdleLeftCollider->setGravityEnable(false);

					/*Iniko->characterJumpingRightCollider->setGravityEnable(false);
					Iniko->characterJumpingLeftCollider->setGravityEnable(false);
					Iniko->characterRunningRightCollider->setGravityEnable(false);
					Iniko->characterRunningLeftCollider->setGravityEnable(false);
					Iniko->characterIdleRightCollider->setGravityEnable(false);
					Iniko->characterIdleLeftCollider->setGravityEnable(false);*/

					contactFloor = bodyB;

					Iniko->characterIdleLeft->setPosition(Point(Iniko->characterIdleLeft->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + Iniko->characterIdleLeft->getContentSize().height / 2 - 5));
					Iniko->characterRunningLeft->setPosition(Point(Iniko->characterRunningLeft->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + Iniko->characterRunningLeft->getContentSize().height / 2 - 5));
					Iniko->characterJumpingLeft->setPosition(Point(Iniko->characterJumpingLeft->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + Iniko->characterJumpingLeft->getContentSize().height / 2));
					Iniko->characterIdleRight->setPosition(Point(Iniko->characterIdleRight->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + Iniko->characterIdleRight->getContentSize().height / 2 - 5));
					Iniko->characterRunningRight->setPosition(Point(Iniko->characterRunningRight->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + Iniko->characterRunningRight->getContentSize().height / 2 - 5));
					Iniko->characterJumpingRight->setPosition(Point(Iniko->characterJumpingRight->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + Iniko->characterJumpingRight->getContentSize().height / 2));
				}
			}

			//}

			//moveCam = false;
		}

		else
		{
			bodyA->setVelocity(Vec2::ZERO);
			bodyA->setGravityEnable(false);
		}
	}

	if (bodyA->getTag() == -1)											//IF FLOOR COLLIDES WITH..
	{
		switch (bodyB->getTag() / 100)
		{
		case 20:													//..AN OBJECT
			if (objectsVector.at(bodyB->getTag() - 2000)->thrown)
			{
				objectsVector.at(bodyB->getTag() - 2000)->itemArt->runAction(Sequence::create(CallFunc::create(CC_CALLBACK_0(Egypt::objectBehaviour, this, bodyB, 1)), DelayTime::create(0.1), CallFunc::create(CC_CALLBACK_0(Egypt::objectBehaviour, this, bodyB, 2)), NULL));

			}

			break;
		}

		//DEFAULT ACTIONS TO EVERYONE

		if (bodyB->getTag() / 100 == 90)
		{
			//if (!Iniko->jumping)
			//{
			/*if ((Iniko->characterIdleRightCollider->getVelocity().y < 0) && (Iniko->characterIdleLeftCollider->getVelocity().y < 0))
			{
			moveCam = false;
			}*/

			/*if ((Iniko->characterRunningRightCollider->getVelocity().y < 0) && (Iniko->characterRunningLeftCollider->getVelocity().y < 0))
			{
			moveCam = false;
			}*/

			if (Iniko->characterJumpingRightCollider->getVelocity().y < 0 || Iniko->characterJumpingRightCollider->getVelocity().y < 0)
			{
				if (((Iniko->characterJumpingRight->getPosition().y) >(bodyB->getNode()->getPosition().y + bodyB->getNode()->getContentSize().height / 2)) || ((Iniko->characterJumpingLeft->getPosition().y) >(bodyB->getNode()->getPosition().y + bodyB->getNode()->getContentSize().height / 2)))
				{
					Iniko->jumping = false;
					Iniko->stealth = false;

					Iniko->characterJumpingRightCollider->setVelocity(Vec2(Iniko->characterJumpingRightCollider->getVelocity().x, 0));
					Iniko->characterJumpingLeftCollider->setVelocity(Vec2(Iniko->characterJumpingRightCollider->getVelocity().x, 0));
					Iniko->characterRunningRightCollider->setVelocity(Vec2(Iniko->characterJumpingRightCollider->getVelocity().x, 0));
					Iniko->characterRunningLeftCollider->setVelocity(Vec2(Iniko->characterJumpingRightCollider->getVelocity().x, 0));
					Iniko->characterIdleRightCollider->setVelocity(Vec2(Iniko->characterJumpingRightCollider->getVelocity().x, 0));
					Iniko->characterIdleLeftCollider->setVelocity(Vec2(Iniko->characterJumpingRightCollider->getVelocity().x, 0));

					//bodyA->setVelocity(Vec2::ZERO);

					Iniko->characterJumpingRightCollider->setGravityEnable(false);
					Iniko->characterJumpingLeftCollider->setGravityEnable(false);
					Iniko->characterRunningRightCollider->setGravityEnable(false);
					Iniko->characterRunningLeftCollider->setGravityEnable(false);
					Iniko->characterIdleRightCollider->setGravityEnable(false);
					Iniko->characterIdleLeftCollider->setGravityEnable(false);

					//bodyB->setVelocity(Vec2::ZERO);
					//bodyB->setGravityEnable(false);

					contactFloor = bodyA;

					Iniko->characterIdleLeft->setPosition(Point(Iniko->characterIdleLeft->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + Iniko->characterIdleLeft->getContentSize().height / 2 - 5));
					Iniko->characterRunningLeft->setPosition(Point(Iniko->characterRunningLeft->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + Iniko->characterRunningLeft->getContentSize().height / 2 - 5));
					Iniko->characterJumpingLeft->setPosition(Point(Iniko->characterJumpingLeft->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + Iniko->characterJumpingLeft->getContentSize().height / 2));
					Iniko->characterIdleRight->setPosition(Point(Iniko->characterIdleRight->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + Iniko->characterIdleRight->getContentSize().height / 2 - 5));
					Iniko->characterRunningRight->setPosition(Point(Iniko->characterRunningRight->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + Iniko->characterRunningRight->getContentSize().height / 2 - 5));
					Iniko->characterJumpingRight->setPosition(Point(Iniko->characterJumpingRight->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + Iniko->characterJumpingRight->getContentSize().height / 2));
				}
			}

			//}

			//moveCam = false;
		}

		else
		{
			bodyB->setVelocity(Vec2::ZERO);
			bodyB->setGravityEnable(false);
		}
	}

	if (bodyB->getTag() == -2)											//IF WALL COLLIDES WITH..
	{
		switch (bodyA->getTag() / 100)
		{
		case 90:													//CHARACTER
			Iniko->wallTouch = bodyB->getNode();
			break;

		case 20:													//..AN OBJECT
			if (objectsVector.at(bodyA->getTag() - 2000)->thrown)
			{
				objectsVector.at(bodyA->getTag() - 2000)->itemArt->runAction(Sequence::create(CallFunc::create(CC_CALLBACK_0(Egypt::objectBehaviour, this, bodyA, 1)), DelayTime::create(0.1), CallFunc::create(CC_CALLBACK_0(Egypt::objectBehaviour, this, bodyA, 2)), NULL));
			}

			break;
		}
	}

	if (bodyA->getTag() == -2)											//IF WALL COLLIDES WITH..
	{
		switch (bodyB->getTag() / 100)
		{
		case 90:													//CHARACTER
			Iniko->wallTouch = bodyA->getNode();
			break;

		case 20:													//..AN OBJECT
			if (objectsVector.at(bodyB->getTag() - 2000)->thrown)
			{
				objectsVector.at(bodyB->getTag() - 2000)->itemArt->runAction(Sequence::create(CallFunc::create(CC_CALLBACK_0(Egypt::objectBehaviour, this, bodyB, 1)), DelayTime::create(0.1), CallFunc::create(CC_CALLBACK_0(Egypt::objectBehaviour, this, bodyB, 2)), NULL));
			}

			break;
		}
	}

	if (bodyB->getTag() == -3)											//IF ENEMY WALL COLLIDES WITH..
	{
		switch (bodyA->getTag() / 100)
		{
		case 10:													//ENEMY
			enemysVector.at(bodyA->getTag() - 1000)->alertedEnemy = false;
			enemysVector.at(bodyA->getTag() - 1000)->alertedSound = false;
			enemysVector.at(bodyA->getTag() - 1000)->returning = true;
			break;
		}
	}

	if (bodyA->getTag() == -3)											//IF ENEMY WALL COLLIDES WITH..
	{
		switch (bodyB->getTag() / 100)
		{
		case 10:													//ENEMY
			enemysVector.at(bodyB->getTag() - 1000)->alertedEnemy = false;
			enemysVector.at(bodyB->getTag() - 1000)->alertedSound = false;
			enemysVector.at(bodyB->getTag() - 1000)->returning = true;
			break;
		}
	}

	return true;
}

bool Egypt::onContactSeparate(PhysicsContact &contact)
{
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();

	if (bodyA->getTag() / 100 == 90)										//IF CHARACTER STOPS TO COLLIDES WITH..
	{
		switch (bodyB->getTag() / 100)
		{
		case 10:													//..AN ENEMY
			contactEnemy = PhysicsBody::create();
			contactEnemy->setTag(9999);
			break;

		case 40:													//..A JUMP ZONE
			Iniko->SKey->setVisible(false);
			contactBody = PhysicsBody::create();
			contactBody->setTag(9999);
			break;

		case 30:													//..AN OBJECT TO HIDE
			contactBody = PhysicsBody::create();
			contactBody->setTag(9999);
			break;

		case 20:													//..A THROWABLE OBJECT
			Iniko->AKey->setVisible(false);
			contactBody = PhysicsBody::create();
			contactBody->setTag(9999);
			break;
		}
	}

	if (bodyB->getTag() / 100 == 90)										//IF CHARACTER STOPS TO COLLIDES WITH..
	{
		switch (bodyA->getTag() / 100)
		{
		case 10:													//..AN ENEMY
			contactEnemy = PhysicsBody::create();
			contactEnemy->setTag(9999);
			break;

		case 40:													//..A JUMP ZONE
			Iniko->SKey->setVisible(false);
			contactBody = PhysicsBody::create();
			contactBody->setTag(9999);
			break;

		case 30:													//..AN OBJECT TO HIDE
			contactBody = PhysicsBody::create();
			contactBody->setTag(9999);
			break;

		case 20:													//..A THROWABLE OBJECT
			Iniko->AKey->setVisible(false);
			contactBody = PhysicsBody::create();
			contactBody->setTag(9999);
			break;
		}
	}

	if (bodyA->getTag() / 100 == 10)									//IF ENEMY STOPS TO COLLIDE WITH..
	{
		switch (bodyB->getTag() / 100)
		{
		case 91:													//CHARACTER RUNNING SOUND
																	//enemysVector.at(bodyA->getTag() - 1000)->alertedSound = false;
			break;
		}
	}

	if (bodyB->getTag() / 100 == 10)									//IF ENEMY STOPS TO COLLIDE WITH..
	{
		switch (bodyA->getTag() / 100)
		{
		case 91:													//CHARACTER RUNNING SOUND
																	//enemysVector.at(bodyB->getTag() - 1000)->alertedSound = false;
			break;
		}
	}

	if (bodyA->getTag() / 100 == 11)									//IF ENEMY VISION STOPS TO COLLIDE WITH..
	{
		switch (bodyB->getTag() / 100)
		{
		case 90:													//CHARACTER
			enemysVector.at(bodyA->getTag() - 1100)->alertedEnemy = false;
			enemysVector.at(bodyA->getTag() - 1100)->alertedSound = true;
			enemysVector.at(bodyA->getTag() - 1100)->followPos = Iniko->characterIdleRight->getPosition().x;
			break;
		}
	}

	if (bodyB->getTag() / 100 == 11)									//IF ENEMY VISION STOPS TO COLLIDE WITH..
	{
		switch (bodyA->getTag() / 100)
		{
		case 90:													//CHARACTER
			enemysVector.at(bodyB->getTag() - 1100)->alertedEnemy = false;
			enemysVector.at(bodyB->getTag() - 1100)->alertedSound = true;
			enemysVector.at(bodyB->getTag() - 1100)->followPos = Iniko->characterIdleRight->getPosition().x;
			break;
		}
	}

	if (bodyB->getTag() == -2)											//IF WALL STOPS TO COLLIDES WITH..
	{
		switch (bodyA->getTag() / 100)
		{
		case 90:													//CHARACTER
			Iniko->wallTouch = NULL;
			Iniko->wallTouchSide = ' ';
			break;
		}
	}

	if (bodyA->getTag() == -2)											//IF WALL STOPS TO COLLIDES WITH..
	{
		switch (bodyB->getTag() / 100)
		{
		case 90:													//CHARACTER
			Iniko->wallTouch = NULL;
			Iniko->wallTouchSide = ' ';
			break;
		}
	}

	if (bodyB->getTag() == -1)											//IF FLOOR STOPS TO COLLIDES WITH..
	{
		if (bodyA->getTag() / 100 == 90)
		{
			//if (!Iniko->jumping)
			//{
			/*if ((Iniko->characterIdleRightCollider->getVelocity().y < 0) && (Iniko->characterIdleLeftCollider->getVelocity().y < 0))
			{
			moveCam = false;
			}*/

			/*if ((Iniko->characterRunningRightCollider->getVelocity().y < 0) && (Iniko->characterRunningLeftCollider->getVelocity().y < 0))
			{
			moveCam = false;
			}*/

			//bodyA->setVelocity(Vec2::ZERO);
			//bodyA->setGravityEnable(false);

			Iniko->characterJumpingRightCollider->setGravityEnable(true);
			Iniko->characterJumpingLeftCollider->setGravityEnable(true);
			Iniko->characterRunningRightCollider->setGravityEnable(true);
			Iniko->characterRunningLeftCollider->setGravityEnable(true);
			Iniko->characterIdleRightCollider->setGravityEnable(true);
			Iniko->characterIdleLeftCollider->setGravityEnable(true);

			//contactFloor = bodyB;
			//}

			//moveCam = false;
			contactFloor = NULL;
		}

		//bodyA->setGravityEnable(true);
		//contactFloor = NULL;
	}

	if (bodyA->getTag() == -1)											//IF FLOOR STOPS TO COLLIDES WITH..
	{
		if (bodyB->getTag() / 100 == 90)
		{
			//if (!Iniko->jumping)
			//{
			/*if ((Iniko->characterIdleRightCollider->getVelocity().y < 0) && (Iniko->characterIdleLeftCollider->getVelocity().y < 0))
			{
			moveCam = false;
			}*/

			/*if ((Iniko->characterRunningRightCollider->getVelocity().y < 0) && (Iniko->characterRunningLeftCollider->getVelocity().y < 0))
			{
			moveCam = false;
			}*/

			//bodyA->setVelocity(Vec2::ZERO);
			//bodyA->setGravityEnable(false);

			Iniko->characterJumpingRightCollider->setGravityEnable(true);
			Iniko->characterJumpingLeftCollider->setGravityEnable(true);
			Iniko->characterRunningRightCollider->setGravityEnable(true);
			Iniko->characterRunningLeftCollider->setGravityEnable(true);
			Iniko->characterIdleRightCollider->setGravityEnable(true);
			Iniko->characterIdleLeftCollider->setGravityEnable(true);

			//contactFloor = bodyB;
			//}

			//moveCam = false;
			contactFloor = NULL;
		}

		//bodyB->setGravityEnable(true);
		//contactFloor = NULL;
	}

	return true;
}

void Egypt::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event)
{
	_pressedKey = keyCode;

	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		if (!Iniko->gameOver)
			moveRight = true;
		break;

	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		if (!Iniko->gameOver)
			moveLeft = true;
		break;
	}

	if (!Iniko->gameOver)
	{
		switch (_pressedKey)
		{
			/*case EventKeyboard::KeyCode::KEY_SPACE:
			if (followObject == NULL && !Iniko->jumping && (Iniko->characterJumpingRightCollider->getVelocity().y >= 0) && (Iniko->characterJumpingLeftCollider->getVelocity().y >= 0))
			{
			this->setScale(0.5);

			moveCam = true;
			}
			break;*/

		case EventKeyboard::KeyCode::KEY_TAB:
			if (!Iniko->jumping && (Iniko->characterJumpingRightCollider->getVelocity().y >= 0) && (Iniko->characterJumpingLeftCollider->getVelocity().y >= 0))
				Iniko->stealth = true;

			break;

		case EventKeyboard::KeyCode::KEY_W:
			if (!Iniko->jumping && (Iniko->characterJumpingRightCollider->getVelocity().y >= 0) && (Iniko->characterJumpingLeftCollider->getVelocity().y >= 0))
				key = 'W';
			break;

		case EventKeyboard::KeyCode::KEY_SPACE:
			if (!Iniko->jumping && (Iniko->characterJumpingRightCollider->getVelocity().y >= 0) && (Iniko->characterJumpingLeftCollider->getVelocity().y >= 0))
			{
				key = 'S';
				this->runAction(Sequence::create(DelayTime::create(0.001f), CallFunc::create(CC_CALLBACK_0(Egypt::keyNull, this)), NULL));
			}
			break;

		case EventKeyboard::KeyCode::KEY_Q:
			if (!Iniko->jumping && (Iniko->characterJumpingRightCollider->getVelocity().y >= 0) && (Iniko->characterJumpingLeftCollider->getVelocity().y >= 0))
			{
				key = 'Q';
				this->runAction(Sequence::create(DelayTime::create(0.001f), CallFunc::create(CC_CALLBACK_0(Egypt::keyNull, this)), NULL));
			}
			break;

		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			if (!Iniko->jumping && (Iniko->characterJumpingRightCollider->getVelocity().y >= 0) && (Iniko->characterJumpingLeftCollider->getVelocity().y >= 0))
			{
				key = 'U';
				this->runAction(Sequence::create(DelayTime::create(0.001f), CallFunc::create(CC_CALLBACK_0(Egypt::keyNull, this)), NULL));
			}
			break;

		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			if (!Iniko->jumping && (Iniko->characterJumpingRightCollider->getVelocity().y >= 0) && (Iniko->characterJumpingLeftCollider->getVelocity().y >= 0))
			{
				key = 'D';
				this->runAction(Sequence::create(DelayTime::create(0.001f), CallFunc::create(CC_CALLBACK_0(Egypt::keyNull, this)), NULL));
			}
			break;

		case EventKeyboard::KeyCode::KEY_1:
			if (!Iniko->jumping && (Iniko->characterJumpingRightCollider->getVelocity().y >= 0) && (Iniko->characterJumpingLeftCollider->getVelocity().y >= 0) && !Iniko->hide)
			{
				key = '1';
				this->runAction(Sequence::create(DelayTime::create(0.001f), CallFunc::create(CC_CALLBACK_0(Egypt::keyNull, this)), NULL));
			}
			break;

		case EventKeyboard::KeyCode::KEY_2:
			if (!Iniko->jumping && (Iniko->characterJumpingRightCollider->getVelocity().y >= 0) && (Iniko->characterJumpingLeftCollider->getVelocity().y >= 0) && !Iniko->hide)
			{
				key = '2';
				this->runAction(Sequence::create(DelayTime::create(0.001f), CallFunc::create(CC_CALLBACK_0(Egypt::keyNull, this)), NULL));
			}
			break;
		}
	}
}

void Egypt::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		_pressedKey = EventKeyboard::KeyCode::KEY_NONE;
		moveRight = false;
		break;

	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		_pressedKey = EventKeyboard::KeyCode::KEY_NONE;
		moveLeft = false;
		break;

		/*case EventKeyboard::KeyCode::KEY_SPACE:
		_pressedKey = EventKeyboard::KeyCode::KEY_NONE;
		if (this->getScale() == 0.5)
		{
		this->setScale(0.7);

		moveCam = false;
		}
		break;*/

	case EventKeyboard::KeyCode::KEY_TAB:
		_pressedKey = EventKeyboard::KeyCode::KEY_NONE;
		Iniko->stealth = false;
		break;

	case EventKeyboard::KeyCode::KEY_SPACE:
		_pressedKey = EventKeyboard::KeyCode::KEY_NONE;
		key = ' ';
		break;

	case EventKeyboard::KeyCode::KEY_Q:
		_pressedKey = EventKeyboard::KeyCode::KEY_NONE;
		key = ' ';
		break;

	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		_pressedKey = EventKeyboard::KeyCode::KEY_NONE;
		key = ' ';
		break;

	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		_pressedKey = EventKeyboard::KeyCode::KEY_NONE;
		key = ' ';
		break;

	case EventKeyboard::KeyCode::KEY_1:
		_pressedKey = EventKeyboard::KeyCode::KEY_NONE;
		key = ' ';
		break;

	case EventKeyboard::KeyCode::KEY_2:
		_pressedKey = EventKeyboard::KeyCode::KEY_NONE;
		key = ' ';
		break;
	}

	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_W:
		_pressedKey = EventKeyboard::KeyCode::KEY_NONE;
		AKeyCounter += 300;
		if (AKeyCounter > 800)
			AKeyCounter = 800;
		key = ' ';
		break;
	}
}

void Egypt::createAnimations()
{
	//PORTAL PARTICLES

	portalParticles = CCParticleSystemQuad::create("Particles/PortalParticles/portal_particle.plist");
	portalParticles->setScale(0.4);
	portalParticles->setPosition(Point(0, 338));
	portalParticles->setPositionType(kCCPositionTypeRelative);
	addChild(portalParticles, 5);
}

void Egypt::keyNull()
{
	key = ' ';
}

void Egypt::objectBehaviour(PhysicsBody* body, int phase)
{
	if (phase == 1)
	{
		objectsVector.at(body->getTag() - 2000)->itemSoundCollider->setEnable(true);
	}

	else
	{
		objectsVector.at(body->getTag() - 2000)->itemSoundCollider->setEnable(false);
		objectsVector.at(body->getTag() - 2000)->itemArt->setVisible(false);
		objectsVector.at(body->getTag() - 2000)->itemCollider->setEnable(false);
		objectsVector.at(body->getTag() - 2000)->itemArt->stopAllActions();
		//removeChild(objectsVector.at(body->getTag() - 2000)->itemArt);
		followObject = NULL;
		moveCam = false;
	}
}

void Egypt::gameOver()
{
	auto scene = GameOver::createScene();
	scene->setTag(10 + Iniko->checkpoint);

	Director::getInstance()->replaceScene(TransitionFade::create(1.5, scene));
}