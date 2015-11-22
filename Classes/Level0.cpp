#include "AppDelegate.h"
#include "Level0.h"

USING_NS_CC;

Scene* Level0::createScene()
{
	auto scene = Scene::createWithPhysics();

	auto layer = Level0::create();
	layer->setPhysicsWorld(scene->getPhysicsWorld());

	scene->addChild(layer);

	return scene;
}

bool Level0::init()
{
	if (!Layer::init())
	{
		return false;
	}

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

	//CREATE BACKGROUND LAYERS

	createBackground();

	//CREATE ANIMATED OBJECTS

	createAnimations();

	//CREATE INTERACTIVE ITEMS

	int tag;

	vasijaPequeña1 = new Item(2, 1397, 90);
	objectsVector.pushBack(vasijaPequeña1);
	tag = (vasijaPequeña1->itemType * 1000) + objectsVector.getIndex(vasijaPequeña1);
	vasijaPequeña1->itemCollider->setTag(tag);
	addChild(vasijaPequeña1->itemArt, 3);

	vasijaPequeña2 = new Item(2, 1800, 90);
	objectsVector.pushBack(vasijaPequeña2);
	tag = (vasijaPequeña1->itemType * 1000) + objectsVector.getIndex(vasijaPequeña2);
	vasijaPequeña2->itemCollider->setTag(tag);
	addChild(vasijaPequeña2->itemArt, 3);

	vasijaGrande1 = new Item(3, 3100, 90);
	objectsVector.pushBack(vasijaGrande1);
	tag = (vasijaGrande1->itemType * 1000) + objectsVector.getIndex(vasijaGrande1);
	vasijaGrande1->itemCollider->setTag(tag);
	addChild(vasijaGrande1->itemArt, 3);

	jumpZone1 = new Item(4, 1230, 90);
	objectsVector.pushBack(jumpZone1);
	tag = (jumpZone1->itemType * 1000) + objectsVector.getIndex(jumpZone1);
	jumpZone1->itemCollider->setTag(tag);
	jumpZone1->force = Vec2(200, 950);
	jumpZone1->right = true;
	addChild(jumpZone1->itemArt, 3);

	//CREATE CHARACTER

	Iniko = new Character();

	addChild(Iniko->runningSoundColliderSprite, 3);
	addChild(Iniko->characterIdlerightspritebatch, 3);
	addChild(Iniko->characterRunningRightspritebatch, 3);
	addChild(Iniko->characterIdleleftspritebatch, 3);
	addChild(Iniko->characterRunningLeftspritebatch, 3);
	addChild(Iniko->characterVision, 5);
	addChild(Iniko->AKey, 3);
	addChild(Iniko->SKey, 3);

	//CREATE ENEMYS

	enemy1 = new Enemy(3000, 5000, 2.0f, 5, 1);
	enemysVector.pushBack(enemy1);
	tag = 1000 + enemysVector.getIndex(enemy1);
	enemy1->enemyCollider->setTag(tag);
	addChild(enemy1->enemyArt, 3);
	addChild(enemy1->detect, 3);
	tag += 100;
	enemy1->enemyVisionCollider->setTag(tag);
	addChild(enemy1->enemyVision, 3);

	enemy2 = new Enemy(5000, 3000, 2.0f, 5, 1);
	enemysVector.pushBack(enemy2);
	tag = 1000 + enemysVector.getIndex(enemy2);
	enemy2->enemyCollider->setTag(tag);
	addChild(enemy2->enemyArt, 3);
	addChild(enemy2->detect, 3);
	tag += 100;
	enemy2->enemyVisionCollider->setTag(tag);
	addChild(enemy2->enemyVision, 3);

	//CREATE FLOOR AND WALLS COLLIDERS

	Layer3 = Sprite::create("images/Level0/Layers/Level0_Layer3.png");
	Layer3->setPosition(Point((Layer3->getContentSize().width / 2), (Layer3->getContentSize().height / 2) ));

	addChild(Layer3, 3);

	Floor = Sprite::create("images/Level0/Colliders/FloorCollider.png");
	Floor->setPosition(Point((Floor->getContentSize().width / 2), (Floor->getContentSize().height / 2)));
	Floor->setVisible(false);

	addChild(Floor, 3);

	FloorCollider = PhysicsBody::createBox(Size(Floor->getContentSize().width, Floor->getContentSize().height));
	FloorCollider->setContactTestBitmask(true);
	FloorCollider->setDynamic(true);
	FloorCollider->setCollisionBitmask(0);
	FloorCollider->setGravityEnable(false);
	FloorCollider->setTag(-1);

	Floor->setPhysicsBody(FloorCollider);

	Wall1 = Sprite::create("images/Level0/Colliders/WallCollider1.png");
	Wall1->setPosition(Point(Wall1->getContentSize().width/2, (visibleSize.height - Wall1->getContentSize().height/2)));
	Wall1->setVisible(false);

	addChild(Wall1, 3);

	WallCollider1 = PhysicsBody::createBox(Size(Wall1->getContentSize().width, Wall1->getContentSize().height));
	WallCollider1->setContactTestBitmask(true);
	WallCollider1->setDynamic(true);
	WallCollider1->setCollisionBitmask(0);
	WallCollider1->setGravityEnable(false);
	WallCollider1->setTag(-2);

	Wall1->setPhysicsBody(WallCollider1);

	Wall2 = Sprite::create("images/Level0/Colliders/WallCollider1.png");
	Wall2->setPosition(Point(11472, (visibleSize.height - Wall2->getContentSize().height / 2)));
	Wall2->setVisible(false);

	addChild(Wall2, 3);

	WallCollider2 = PhysicsBody::createBox(Size(Wall1->getContentSize().width, Wall1->getContentSize().height));
	WallCollider2->setContactTestBitmask(true);
	WallCollider2->setDynamic(true);
	WallCollider2->setCollisionBitmask(0);
	WallCollider2->setGravityEnable(false);
	WallCollider2->setTag(-2);

	Wall2->setPhysicsBody(WallCollider2);

	Wall3 = Sprite::create("images/Level0/Colliders/WallCollider3.png");
	Wall3->setPosition(Point((Layer0->getContentSize().width - Wall3->getContentSize().width/2), Wall3->getContentSize().height/2));
	Wall3->setVisible(false);

	addChild(Wall3, 3);

	WallCollider3 = PhysicsBody::createBox(Size(Wall3->getContentSize().width, Wall3->getContentSize().height));
	WallCollider3->setContactTestBitmask(true);
	WallCollider3->setDynamic(true);
	WallCollider3->setCollisionBitmask(0);
	WallCollider3->setGravityEnable(false);
	WallCollider3->setTag(-2);

	Wall3->setPhysicsBody(WallCollider3);

	DrinkMachineColliderSprite = Sprite::create("images/Level0/Colliders/MaquinaRefrescosCollider.png");
	DrinkMachineColliderSprite->setPosition(Point(1310 + DrinkMachineColliderSprite->getContentSize().width/2, 497 - DrinkMachineColliderSprite->getContentSize().height/2));
	DrinkMachineColliderSprite->setVisible(false);

	addChild(DrinkMachineColliderSprite, 3);

	DrinkMachineCollider = PhysicsBody::createBox(Size(DrinkMachineColliderSprite->getContentSize().width, DrinkMachineColliderSprite->getContentSize().height));
	DrinkMachineCollider->setContactTestBitmask(true);
	DrinkMachineCollider->setDynamic(true);
	DrinkMachineCollider->setCollisionBitmask(0);
	DrinkMachineCollider->setGravityEnable(false);
	DrinkMachineCollider->setTag(-1);

	DrinkMachineColliderSprite->setPhysicsBody(DrinkMachineCollider);

	//CREATE VIRTUAL CAMERA

	//changeCameraFollow(Iniko->characterVision);

	//INITIALIZE UPDATE FUNCTION

	this->scheduleUpdate();
	
	//CREATE KEY INPUTS LISTENERS

	auto listener = EventListenerKeyboard::create();

	listener->onKeyPressed = CC_CALLBACK_2(Level0::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(Level0::onKeyReleased, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	//CREATE PHYSIC CONTACT LISTENER

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Level0::onContactBegin, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(Level0::onContactSeparate, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	return true;
}

void Level0::createBackground()
{
	Layer0 = Sprite::create("images/Level0/Layers/Level0_Layer0.png");
	Layer0->setPosition(Point((Layer0->getContentSize().width/2), (Layer0->getContentSize().height/2)));

	addChild(Layer0, 0);
	
	Layer1 = Sprite::create("images/Level0/Layers/Level0_Layer1.png");
	Layer1->setPosition(Point((Layer1->getContentSize().width/2), (Layer1->getContentSize().height/2)));

	addChild(Layer1, 1);
	
	Layer2 = Sprite::create("images/Level0/Layers/Level0_Layer2.png");
	Layer2->setPosition(Point((Layer2->getContentSize().width/2), (Layer2->getContentSize().height/2)));

	addChild(Layer2, 2);
	
	Layer4 = Sprite::create("images/Level0/Layers/Level0_Layer4.png");
	Layer4->setPosition(Point((Layer4->getContentSize().width/2), (Layer4->getContentSize().height/2)));

	addChild(Layer4, 4);
}

void Level0::update(float dt)
{
	//FACING UPDATE

	if (Iniko->facingRight && !moveRight && !moveLeft)
	{
		Iniko->characterIdlerightspritebatch->setVisible(true);
		Iniko->characterIdleleftspritebatch->setVisible(false);
		Iniko->characterRunningRightspritebatch->setVisible(false);
		Iniko->characterRunningLeftspritebatch->setVisible(false);
	}

	if (!Iniko->facingRight && !moveRight && !moveLeft)
	{
		Iniko->characterIdlerightspritebatch->setVisible(false);
		Iniko->characterIdleleftspritebatch->setVisible(true);
		Iniko->characterRunningRightspritebatch->setVisible(false);
		Iniko->characterRunningLeftspritebatch->setVisible(false);
	}

	//MOVEMENT UPDATE

	//ENEMY MOVEMENT

	for (int i = 0; i < enemysVector.size(); i++)
	{
		if(!enemysVector.at(i)->die)
			enemysVector.at(i)->moveVision();
	}

	//GENERAL MOVEMENT

	if (moveRight && moveLeft && !moveCam && !Iniko->stealth && !Iniko->hide)
	{
		Iniko->characterIdlerightspritebatch->setVisible(true);
		Iniko->characterIdleleftspritebatch->setVisible(false);
		Iniko->characterRunningRightspritebatch->setVisible(false);
		Iniko->characterRunningLeftspritebatch->setVisible(false);
	}

	else if (moveRight && !moveCam && !Iniko->stealth && !Iniko->hide)
	{
		Iniko->facingRight = true;

		Iniko->characterIdleRight->setPosition(Iniko->characterIdleRight->getPosition().x + (800 * dt), Iniko->characterIdleRight->getPosition().y);

		Iniko->characterIdlerightspritebatch->setVisible(false);
		Iniko->characterIdleleftspritebatch->setVisible(false);
		Iniko->characterRunningLeftspritebatch->setVisible(false);
		Iniko->characterRunningRightspritebatch->setVisible(true);
	}

	else if (moveLeft && !moveCam && !Iniko->stealth && !Iniko->hide)
	{
		Iniko->facingRight = false;

		Iniko->characterIdleLeft->setPosition(Iniko->characterIdleLeft->getPosition().x - (800 * dt), Iniko->characterIdleLeft->getPosition().y);

		Iniko->characterIdlerightspritebatch->setVisible(false);
		Iniko->characterIdleleftspritebatch->setVisible(false);
		Iniko->characterRunningRightspritebatch->setVisible(false);
		Iniko->characterRunningLeftspritebatch->setVisible(true);
	}

	//STEALTH MOVEMENT

	if (moveLeft && moveRight && !moveCam && Iniko->stealth && !Iniko->hide)
	{
		Iniko->characterIdlerightspritebatch->setVisible(true);
		Iniko->characterIdleleftspritebatch->setVisible(false);
		Iniko->characterRunningRightspritebatch->setVisible(false);
		Iniko->characterRunningLeftspritebatch->setVisible(false);
	}

	else if (moveRight && !moveCam && Iniko->stealth && !Iniko->hide)
	{
		Iniko->facingRight = true;

		Iniko->characterIdleRight->setPosition(Iniko->characterIdleRight->getPosition().x + (500 * dt), Iniko->characterIdleRight->getPosition().y);

		Iniko->characterIdlerightspritebatch->setVisible(false);
		Iniko->characterIdleleftspritebatch->setVisible(false);
		Iniko->characterRunningLeftspritebatch->setVisible(false);
		Iniko->characterRunningRightspritebatch->setVisible(true);
	}

	else if (moveLeft && !moveCam && Iniko->stealth && !Iniko->hide)
	{
		Iniko->facingRight = false;

		Iniko->characterIdleLeft->setPosition(Iniko->characterIdleLeft->getPosition().x - (500 * dt), Iniko->characterIdleLeft->getPosition().y);

		Iniko->characterIdlerightspritebatch->setVisible(false);
		Iniko->characterIdleleftspritebatch->setVisible(false);
		Iniko->characterRunningRightspritebatch->setVisible(false);
		Iniko->characterRunningLeftspritebatch->setVisible(true);
	}

	//STOPS IF MOVE IN TWO DIRECTIONS

	if (moveLeft && moveRight)
	{
		Iniko->facingRight = true;
		Iniko->characterIdlerightspritebatch->setVisible(true);
		Iniko->characterIdleleftspritebatch->setVisible(false);
		Iniko->characterRunningLeftspritebatch->setVisible(false);
		Iniko->characterRunningRightspritebatch->setVisible(false);
	}

	//CHARACTER ART UPDATE
	
	if (Iniko->facingRight)
	{
		Iniko->runningSoundColliderSprite->setPosition(Iniko->characterIdleRight->getPosition());
		Iniko->characterRunningLeft->setPosition(Iniko->characterIdleRight->getPosition());
		Iniko->characterRunningRight->setPosition(Iniko->characterIdleRight->getPosition());
		Iniko->characterIdleLeft->setPosition(Iniko->characterIdleRight->getPosition());
		Iniko->characterIdleRight->setPosition(Iniko->characterIdleRight->getPosition());
		Iniko->characterVision->setPosition(Iniko->characterIdleRight->getPosition());
		Iniko->AKey->setPosition(Iniko->characterIdleRight->getPosition().x, Iniko->characterIdleRight->getPosition().y + (Iniko->characterIdleRight->getContentSize().height / 2 + 80));
		Iniko->SKey->setPosition(Iniko->characterIdleRight->getPosition().x, Iniko->characterIdleRight->getPosition().y + (Iniko->characterIdleRight->getContentSize().height / 2 + 150));
	}

	else
	{
		Iniko->runningSoundColliderSprite->setPosition(Iniko->characterIdleLeft->getPosition());
		Iniko->characterRunningLeft->setPosition(Iniko->characterIdleLeft->getPosition());
		Iniko->characterRunningRight->setPosition(Iniko->characterIdleLeft->getPosition());
		Iniko->characterIdleLeft->setPosition(Iniko->characterIdleLeft->getPosition());
		Iniko->characterIdleRight->setPosition(Iniko->characterIdleLeft->getPosition());
		Iniko->characterVision->setPosition(Iniko->characterIdleLeft->getPosition());
		Iniko->AKey->setPosition(Iniko->characterIdleLeft->getPosition().x, Iniko->characterIdleLeft->getPosition().y + (Iniko->characterIdleLeft->getContentSize().height / 2 + 80));
		Iniko->SKey->setPosition(Iniko->characterIdleLeft->getPosition().x, Iniko->characterIdleLeft->getPosition().y + (Iniko->characterIdleLeft->getContentSize().height / 2 + 150));
	}

	//COLLISION UPDATE

	if (this->getScale() == 1)
	{
		switch (contactEnemy->getTag() / 100)
		{
			case 10:														//ENEMY
				if (enemysVector.at(contactEnemy->getTag() - 1000)->facingRight && Iniko->facingRight && !enemysVector.at(contactEnemy->getTag() - 1000)->detect->isVisible())
				{
					if (key == 'Q' && !Iniko->hide)
					{
						enemysVector.at(contactEnemy->getTag() - 1000)->die = true;
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyVision->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->detect->setVisible(false);
					}
				}

				if (!enemysVector.at(contactEnemy->getTag() - 1000)->facingRight && !Iniko->facingRight && !enemysVector.at(contactEnemy->getTag() - 1000)->detect->isVisible())
				{
					if (key == 'Q' && !Iniko->hide)
					{
						enemysVector.at(contactEnemy->getTag() - 1000)->die = true;
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyVision->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->detect->setVisible(false);
					}
				}
				break;
		}

		switch (contactBody->getTag() / 100)
		{
			case 20:														//THROWABLE OBJECT
				if (key == ' ' && AKeyCounter > 0)
				{
					objectsVector.at(contactBody->getTag() - 2000)->getThrow(Iniko->facingRight, AKeyCounter);
					//changeCameraFollow(contactBody->getNode());
					followObject = contactBody->getNode();
				}
				break;

			case 30:														//OBJECTO TO HIDE
				if (key == 'U')
				{
					if (!Iniko->hide)
						Iniko->getHide(true);
				}
				break;

			case 40:														//JUMP ZONE
				if (objectsVector.at(contactBody->getTag() - 4000)->right && Iniko->facingRight)
				{
					Iniko->SKey->setVisible(true);

					if (key == 'S' && !moveRight && !moveLeft)
					{
						Iniko->characterIdleRight->setPosition(Point(Iniko->characterIdleRight->getPosition().x, Iniko->characterIdleRight->getPosition().y + 5));
						Iniko->characterIdleRightCollider->setVelocity(objectsVector.at(contactBody->getTag() - 4000)->force);
						Iniko->jumping = true;
					}
				}

				else if (!objectsVector.at(contactBody->getTag() - 4000)->right && !Iniko->facingRight)
				{
					Iniko->SKey->setVisible(true);

					if (key == 'S' && !moveRight && !moveLeft)
					{
						Iniko->characterIdleLeft->setPosition(Point(Iniko->characterIdleLeft->getPosition().x, Iniko->characterIdleLeft->getPosition().y + 5));
						Iniko->characterIdleLeftCollider->setVelocity(objectsVector.at(contactBody->getTag() - 4000)->force);
						Iniko->jumping = true;
					}
				}

				else
					Iniko->SKey->setVisible(false);

				break;
		}
	}

	//WALL COLLISION

	if (Iniko->wallTouch != NULL)
	{
		if (!Iniko->facingRight && Iniko->characterIdleRight->getPosition().x > Iniko->wallTouch->getPosition().x)
		{
			moveLeft = false;
			Iniko->characterIdleRight->setPosition(Point(Iniko->wallTouch->getPosition().x + Iniko->wallTouch->getContentSize().width / 2 + Iniko->characterIdleRight->getContentSize().width / 2, Iniko->characterIdleRight->getPosition().y));
		}

		else if (Iniko->facingRight && Iniko->characterIdleRight->getPosition().x < Iniko->wallTouch->getPosition().x)
		{
			moveRight = false;
			Iniko->characterIdleRight->setPosition(Point(Iniko->wallTouch->getPosition().x - Iniko->wallTouch->getContentSize().width / 2 - Iniko->characterIdleRight->getContentSize().width / 2, Iniko->characterIdleRight->getPosition().y));
		}
	}

	//FALLING UPDATE

	if (Iniko->characterIdleRightCollider->getVelocity().y < 0)
	{
		Iniko->jumping = false;
		
		if (Iniko->facingRight)
		{
			Iniko->characterIdlerightspritebatch->setVisible(true);
			Iniko->characterIdleleftspritebatch->setVisible(false);
		}

		else
		{
			Iniko->characterIdlerightspritebatch->setVisible(false);
			Iniko->characterIdleleftspritebatch->setVisible(true);
		}

		moveRight = false;
		moveLeft = false;
		Iniko->characterRunningLeftspritebatch->setVisible(false);
		Iniko->characterRunningRightspritebatch->setVisible(false);
	}

	//KEY PRESSED HANDLER

	if (key == 'A' && (contactBody->getTag() / 100) == 20)
	{
		AKeyCounter += 500 * dt;
	}

	else
		AKeyCounter = 0;

	if (Iniko->hide)
	{
		if (key == 'D')
			Iniko->getHide(false);
	}

	//CHECK RUNNING SOUND

	if (Iniko->stealth || (!moveRight && !moveLeft) || Iniko->hide)
		Iniko->runningSoundCollider->setEnable(false);

	else
		Iniko->runningSoundCollider->setEnable(true);

	//TESTING COLLISIONS UPDATE

	if(!enemy1->die)
		enemy1->detect->setPositionX(enemy1->enemyArt->getPosition().x);
	if(!enemy2->die)
		enemy2->detect->setPositionX(enemy2->enemyArt->getPosition().x);

	//CAM FOLLOW AND ZOOM OUT UPDATE

	if (this->getScale() == 0.5)
	{
		Point screenCenter = Point(visibleSize.width / 2, visibleSize.height / 2);
		Point offSetToCenter = ccpSub(screenCenter, Iniko->characterVision->getPosition());

		this->setPosition(ccpMult(offSetToCenter, this->getScale()));
		this->setPosition(ccpSub(this->getPosition(), ccpMult(offSetToCenter, (0.5 - this->getScale()) / (0.5 - 1.0f))));
	}

	else if(this->getScale() == 1 && followObject == NULL)
	{
		Point screenCenter = Point(visibleSize.width / 2, visibleSize.height / 2);
		Point offSetToCenter = ccpSub(screenCenter, Iniko->characterVision->getPosition());

		this->setPosition(ccpMult(offSetToCenter, this->getScale()));
		this->setPosition(ccpSub(this->getPosition(), ccpMult(offSetToCenter, (1 - this->getScale()) / (1.0f))));
		this->setPositionY(this->getPositionY() - offSetToCenter.y - (Iniko->characterIdleRight->getPosition().y - (Iniko->characterIdleRight->getContentSize().height / 2 + 80)));
	}

	else if (this->getScale() == 1 && followObject != NULL)
	{
		Point screenCenter = Point(visibleSize.width / 2, visibleSize.height / 2);
		Point offSetToCenter = ccpSub(screenCenter, followObject->getPosition());

		this->setPosition(ccpMult(offSetToCenter, this->getScale()));
		this->setPosition(ccpSub(this->getPosition(), ccpMult(offSetToCenter, (1 - this->getScale()) / (1.0f))));
		this->setPositionY(this->getPositionY() - offSetToCenter.y);
	}

	//FLOOR COLLISION UPDATE

	if(contactFloor != NULL)
	{
		if ((Iniko->characterIdleRight->getPosition().y - Iniko->characterIdleRight->getContentSize().height / 2) < (contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 - 10))
		{
			Iniko->characterIdleRight->setPosition(Point(Iniko->characterIdleRight->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + Iniko->characterIdleRight->getContentSize().height / 2 - 5));
		}
	}
}

void Level0::setPhysicsWorld(PhysicsWorld *world)
{
	mWorld = world;
	mWorld->setGravity(Vec2(0, -1000));
}

bool Level0::onContactBegin(PhysicsContact &contact)
{
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();

	if (bodyA->getTag()/100 == 90)										//IF CHARACTER COLLIDES WITH..
	{
		switch (bodyB->getTag()/100)
		{
			case 30:													//..AN OBJECT TO HIDE
				contactBody = bodyB;
				break;
		
			case 10:													//..AN ENEMY
				if(!enemysVector.at(bodyB->getTag() - 1000)->die)
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

	if (bodyB->getTag()/100 == 90)										//IF CHARACTER COLLIDES WITH..
	{
		switch (bodyA->getTag()/100)
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

	if (bodyA->getTag()/100 == 91)										//IF CHARACTER RUNNING SOUND COLLIDES WITH..
	{
		switch (bodyB->getTag() / 100)
		{
			case 10:													//..AN ENEMY
				if(!enemysVector.at(bodyB->getTag() - 1000)->die)
					enemysVector.at(bodyB->getTag() - 1000)->detectCharacter();
				break;
		}
	}

	if (bodyB->getTag()/100 == 91)										//IF CHARACTER RUNNING SOUND COLLIDES WITH..
	{
		switch (bodyA->getTag() / 100)
		{
			case 10:													//..AN ENEMY
				if(!enemysVector.at(bodyB->getTag() - 1000)->die)
					enemysVector.at(bodyA->getTag() - 1000)->detectCharacter();
				break;
		}
	}

	if (bodyA->getTag() / 100 == 11)									//IF ENEMY VISION COLLIDES WITH..
	{
		if (!enemysVector.at(bodyA->getTag() - 1100)->die)
		{
			switch (bodyB->getTag() / 100)
			{
				case 90:												//..CHARACTER
					enemysVector.at(bodyA->getTag() - 1100)->detectCharacter();
					break;
			}
		}
	}

	if (bodyB->getTag() / 100 == 11)									//IF ENEMY VISION COLLIDES WITH..
	{
		if (!enemysVector.at(bodyB->getTag() - 1100)->die)
		{
			switch (bodyA->getTag() / 100)
			{
				case 90:												//..CHARACTER
					enemysVector.at(bodyB->getTag() - 1100)->detectCharacter();
					break;
			}
		}
	}

	if (bodyB->getTag() == -1)											//IF FLOOR COLLIDES WITH..
	{
		switch (bodyA->getTag()/100)
		{
			case 20:													//..AN OBJECT
				if (objectsVector.at(bodyA->getTag() - 2000)->thrown)
				{
					removeChild(objectsVector.at(bodyA->getTag() - 2000)->itemArt);
					//changeCameraFollow(Iniko->characterVision);
					followObject = NULL;
				}
				
				break;
		}

		//DEFAULT ACTIONS TO EVERYONE

		if (bodyA->getTag()/100 == 90)
		{
			if (!Iniko->jumping)
			{
				bodyA->setVelocity(Vec2::ZERO);
				bodyA->setGravityEnable(false);

				contactFloor = bodyB;
			}
		}

		else
		{
			bodyA->setVelocity(Vec2::ZERO);
			bodyA->setGravityEnable(false);
		}
	}

	if (bodyA->getTag() == -1)											//IF FLOOR COLLIDES WITH..
	{
		switch (bodyB->getTag()/100)
		{
			case 20:													//..AN OBJECT
				if (objectsVector.at(bodyB->getTag() - 2000)->thrown)
				{
					removeChild(objectsVector.at(bodyB->getTag() - 2000)->itemArt);
					//changeCameraFollow(Iniko->characterVision);
					followObject = NULL;
				}

				break;
		}

		//DEFAULT ACTIONS TO EVERYONE

		if (bodyB->getTag()/100 == 90)
		{
			if (!Iniko->jumping)
			{
				bodyB->setVelocity(Vec2::ZERO);
				bodyB->setGravityEnable(false);

				contactFloor = bodyA;
			}
		}

		else
		{
			bodyB->setVelocity(Vec2::ZERO);
			bodyB->setGravityEnable(false);
		}
	}

	if (bodyB->getTag() == -2)											//IF WALL COLLIDES WITH..
	{
		if(bodyA->getTag()/100 == 90)									//CHARACTER
			Iniko->wallTouch = bodyB->getNode();

		switch (bodyA->getTag() / 100)
		{
			case 20:													//..AN OBJECT
				if (objectsVector.at(bodyA->getTag() - 2000)->thrown)
				{
					removeChild(objectsVector.at(bodyA->getTag() - 2000)->itemArt);
					//changeCameraFollow(Iniko->characterVision);
					followObject = NULL;
				}
				
				break;
		}
	}

	if (bodyA->getTag() == -2)											//IF WALL COLLIDES WITH..
	{
		if (bodyB->getTag()/100 == 90)									//CHARACTER
			Iniko->wallTouch = bodyA->getNode();

		switch (bodyB->getTag() / 100)
		{
			case 20:													//..AN OBJECT
				if (objectsVector.at(bodyB->getTag() - 2000)->thrown)
				{
					removeChild(objectsVector.at(bodyB->getTag() - 2000)->itemArt);
					//changeCameraFollow(Iniko->characterVision);
					followObject = NULL;
				}
				
				break;
		}
	}

	return true;
}

bool Level0::onContactSeparate(PhysicsContact &contact)
{
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();

	if (bodyA->getTag()/100 == 90)										//IF CHARACTER STOPS TO COLLIDES WITH..
	{
		switch (bodyB->getTag() / 100)
		{
			case 10:													//..AN ENEMY
				if (!enemysVector.at(bodyB->getTag() - 1000)->die)
				{
					contactEnemy = PhysicsBody::create();
					contactEnemy->setTag(9999);
				}
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

	if (bodyB->getTag()/100 == 90)										//IF CHARACTER STOPS TO COLLIDES WITH..
	{
		switch (bodyA->getTag() / 100)
		{
			case 10:													//..AN ENEMY
				if (enemysVector.at(bodyA->getTag() - 1000)->die)
				{
					contactEnemy = PhysicsBody::create();
					contactEnemy->setTag(9999);
				}
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

	if (bodyA->getTag()/100 == 91)										//IF CHARACTER RUNNING SOUND STOPS TO COLLIDES WITH..
	{
		switch (bodyB->getTag() / 100)
		{

		}
	}

	if (bodyB->getTag()/100 == 91)										//IF CHARACTER RUNNING SOUND STOPS TO COLLIDES WITH..
	{
		switch (bodyA->getTag() / 100)
		{

		}
	}

	if (bodyB->getTag() == -2)											//IF WALL STOPS TO COLLIDES WITH..
	{
		if (bodyA->getTag() == 00)										//CHARACTER
			Iniko->wallTouch = NULL;
	}

	if (bodyA->getTag() == -2)											//IF WALL STOPS TO COLLIDES WITH..
	{
		if (bodyB->getTag() == 00)										//CHARACTER
			Iniko->wallTouch = NULL;
	}

	if (bodyB->getTag() == -1)											//IF FLOOR STOPS TO COLLIDES WITH..
	{
		bodyA->setGravityEnable(true);
		contactFloor = NULL;
	}

	if (bodyA->getTag() == -1)											//IF FLOOR STOPS TO COLLIDES WITH..
	{
		bodyB->setGravityEnable(true);
		contactFloor = NULL;
	}

	return true;
}

void Level0::changeCameraFollow(Node* target)
{
	cameraFollow = this->runAction(Follow::create(target, Rect(0, visibleSize.height / 2, Layer0->getContentSize().width, 0)));
}

void Level0::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event)
{
	_pressedKey = keyCode;
	
	switch (_pressedKey)
	{
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			moveRight = true;
			break;

		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			moveLeft = true;
			break;

		case EventKeyboard::KeyCode::KEY_SPACE:
			this->setScale(0.5);
			moveCam = true;
			break;

		case EventKeyboard::KeyCode::KEY_SHIFT:
			Iniko->stealth = true;
			break;

		case EventKeyboard::KeyCode::KEY_A:
			key = 'A';
			break;

		case EventKeyboard::KeyCode::KEY_S:
			key = 'S';
			this->runAction(Sequence::create(DelayTime::create(0.001f), CallFunc::create(CC_CALLBACK_0(Level0::keyNull, this)), NULL));
			break;

		case EventKeyboard::KeyCode::KEY_Q:
			key = 'Q';
			this->runAction(Sequence::create(DelayTime::create(0.001f), CallFunc::create(CC_CALLBACK_0(Level0::keyNull, this)), NULL));
			break;

		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			key = 'U';
			this->runAction(Sequence::create(DelayTime::create(0.001f), CallFunc::create(CC_CALLBACK_0(Level0::keyNull, this)), NULL));
			break;

		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			key = 'D';
			this->runAction(Sequence::create(DelayTime::create(0.001f), CallFunc::create(CC_CALLBACK_0(Level0::keyNull, this)), NULL));
			break;
	}
}

void Level0::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event)
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

		case EventKeyboard::KeyCode::KEY_SPACE:
			_pressedKey = EventKeyboard::KeyCode::KEY_NONE;
			this->setScale(1);
			moveCam = false;
			break;

		case EventKeyboard::KeyCode::KEY_SHIFT:
			_pressedKey = EventKeyboard::KeyCode::KEY_NONE;
			Iniko->stealth = false;
			break;

		case EventKeyboard::KeyCode::KEY_A:
			_pressedKey = EventKeyboard::KeyCode::KEY_NONE;
			key = ' ';
			AKeyCounter += 600;
			if (AKeyCounter > 1100)
				AKeyCounter = 1100;
			break;

		case EventKeyboard::KeyCode::KEY_S:
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
	}
}

void Level0::createAnimations()
{
	//PORTAL PARTICLES

	portalParticles = CCParticleSystemQuad::create("Particles/PortalParticles/portal_particle.plist");
	portalParticles->setScale(0.4);
	portalParticles->setPosition(Point(2370, 338));
	portalParticles->setPositionType(kCCPositionTypeRelative);
	addChild(portalParticles, 1);

	portalRayParticles = CCParticleSystemQuad::create("Particles/PortalRayParticles/portalray_particle.plist");
	portalRayParticles->setScale(0.4);
	portalRayParticles->setPosition(Point(2370, 345));
	portalRayParticles->setPositionType(kCCPositionTypeRelative);
	addChild(portalRayParticles, 1);
}

void Level0::keyNull()
{
	key = ' ';
}