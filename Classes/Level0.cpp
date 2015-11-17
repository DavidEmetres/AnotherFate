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
	curDetail = 5;
	contactBody = PhysicsBody::create();

	//CREATE BACKGROUND LAYERS

	createBackground();

	//CREATE ANIMATED OBJECTS

	createAnimations();

	//CREATE INTERACTIVE ITEMS

	int tag;

	vasijaPequeña1 = new Item(2, 1397, 90);
	objectsVector.pushBack(vasijaPequeña1);
	tag = (vasijaPequeña1->itemType * 100) + objectsVector.getIndex(vasijaPequeña1);
	vasijaPequeña1->itemCollider->setTag(tag);
	addChild(vasijaPequeña1->itemArt, 3);

	vasijaPequeña2 = new Item(2, 1800, 90);
	objectsVector.pushBack(vasijaPequeña2);
	tag = (vasijaPequeña2->itemType * 100) + objectsVector.getIndex(vasijaPequeña2);
	vasijaPequeña2->itemCollider->setTag(tag);
	addChild(vasijaPequeña2->itemArt, 3);

	//CREATE CHARACTER

	Iniko = new Character();

	addChild(Iniko->runningSoundColliderSprite, 3);
	addChild(Iniko->visionColliderSpriteLeft, 3);
	addChild(Iniko->visionColliderSpriteRight, 3);
	addChild(Iniko->characterIdlerightspritebatch, 3);
	addChild(Iniko->characterRunningRightspritebatch, 3);
	addChild(Iniko->characterIdleleftspritebatch, 3);
	addChild(Iniko->characterRunningLeftspritebatch, 3);
	addChild(Iniko->characterVision, 3);
	addChild(Iniko->AKey, 3);

	//CREATE ENEMYS

	enemy1 = new Enemy();
	enemysVector.pushBack(enemy1);
	tag = 100 + enemysVector.getIndex(enemy1);
	enemy1->enemyCollider->setTag(tag);
	enemy1->enemyArt->setScaleX(-1);
	addChild(enemy1->enemyArt, 3);
	addChild(enemy1->detect, 3);

	//CREATE FLOOR

	Layer3 = Sprite::create("images/Level0/Layers/Level0_Layer3.png");
	Layer3->setPosition(Point((Layer3->getContentSize().width / 2), (Layer3->getContentSize().height / 2) ));

	addChild(Layer3, 3);

	Floor = Sprite::create("images/Level0/Assets/FloorCollider.png");
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
	
	//CREATE VIRTUAL CAMERA

	changeCameraFollow(Iniko->characterIdlerightspritebatch);

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

	//GENERAL MOVEMENT

	if (moveRight && !moveCam && !Iniko->stealth)
	{
		Iniko->facingRight = true;
		Iniko->characterMove(1, dt);
		Iniko->characterIdlerightspritebatch->setVisible(false);
		Iniko->characterIdleleftspritebatch->setVisible(false);
		Iniko->characterRunningLeftspritebatch->setVisible(false);
		Iniko->characterRunningRightspritebatch->setVisible(true);
	}

	if (moveLeft && !moveCam && !Iniko->stealth)
	{
		Iniko->facingRight = false;
		Iniko->characterMove(2, dt);
		Iniko->characterIdlerightspritebatch->setVisible(false);
		Iniko->characterIdleleftspritebatch->setVisible(false);
		Iniko->characterRunningRightspritebatch->setVisible(false);
		Iniko->characterRunningLeftspritebatch->setVisible(true);
	}

	//STEALTH MOVEMENT

	if (moveRight && !moveCam && Iniko->stealth)
	{
		Iniko->facingRight = true;
		Iniko->characterMove(1, dt);
		Iniko->characterIdlerightspritebatch->setVisible(false);
		Iniko->characterIdleleftspritebatch->setVisible(false);
		Iniko->characterRunningLeftspritebatch->setVisible(false);
		Iniko->characterRunningRightspritebatch->setVisible(true);
	}

	if (moveLeft && !moveCam && Iniko->stealth)
	{
		Iniko->facingRight = false;
		Iniko->characterMove(2, dt);
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

	//CAMERA MOVEMENT

	if (moveRight && moveCam && !Iniko->visionCollideRight)
	{
		Iniko->facingRight = true;
		Iniko->characterIdlerightspritebatch->setVisible(true);
		Iniko->characterIdleleftspritebatch->setVisible(false);
		Iniko->characterRunningLeftspritebatch->setVisible(false);
		Iniko->characterRunningRightspritebatch->setVisible(false);
		Iniko->moveCam(1, dt);
	}
	
	if (moveLeft && moveCam && !Iniko->visionCollideLeft)
	{
		Iniko->facingRight = false;
		Iniko->characterIdlerightspritebatch->setVisible(false);
		Iniko->characterIdleleftspritebatch->setVisible(true);
		Iniko->characterRunningLeftspritebatch->setVisible(false);
		Iniko->characterRunningRightspritebatch->setVisible(false);
		Iniko->moveCam(2, dt);
	}

	//COLLISION UPDATE

	switch (contactBody->getTag() / 100)
	{
		case 1:
			enemysVector.at(contactBody->getTag() - 100)->detectCharacter();
			break;

		case 2:
			if (key == 'A')
			{
				objectsVector.at(contactBody->getTag() - 200)->getThrow(Iniko->facingRight);
				changeCameraFollow(contactBody->getNode());
				break;
			}
	}

	//CHECK RUNNING SOUND IF NOT STEALTH

	if (Iniko->stealth || (!moveRight && !moveLeft))
		Iniko->runningSoundCollider->setEnable(false);

	else
		Iniko->runningSoundCollider->setEnable(true);

	//TESTING COLLISIONS UPDATE

	enemy1->detect->setPositionX(enemy1->enemyArt->getPosition().x);
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

	if (bodyA->getTag() == 00)											//IF CHARACTER COLLIDES WITH..
	{
		switch (bodyB->getTag()/100)
		{
			/*case 1:														//..AN ENEMY
				contactBody = bodyB;
				break;*/

			case 2:														//..AN OBJECT
				contactBody = bodyB;
				Iniko->AKey->setVisible(true);
				break;
		}
	}

	if (bodyB->getTag() == 00)											//IF CHARACTER COLLIDES WITH..
	{
		switch (bodyA->getTag()/100)
		{
			/*case 1:														//..AN ENEMY
				contactBody = bodyA;
				break;*/

			case 2:														//..AN OBJECT
				contactBody = bodyA;
				Iniko->AKey->setVisible(true);
				break;
		}
	}

	if (bodyA->getTag() == 01)											//IF CHARACTER RUNNING SOUND COLLIDES WITH..
	{
		switch (bodyB->getTag() / 100)
		{
			case 1:														//..AN ENEMY
				contactBody = bodyB;
				break;
		}
	}

	if (bodyB->getTag() == 01)											//IF CHARACTER RUNNING SOUND COLLIDES WITH..
	{
		switch (bodyA->getTag() / 100)
		{
			case 1:														//..AN ENEMY
				contactBody = bodyA;
				break;
		}
	}

	if (bodyA->getTag() == 03)											//IF CHARACTER VISION COLLIDES WITH..
	{
		switch (bodyB->getTag())
		{
			case 02:													//..VISION COLLIDER
				if (moveRight)
					Iniko->visionCollideRight = true;

				else if (moveLeft)
					Iniko->visionCollideLeft = true;

				break;
		}
	}

	if (bodyB->getTag() == 03)											//IF CHARACTER VISION COLLIDES WITH..
	{
		switch (bodyA->getTag())
		{
			case 02:													//..VISION COLLIDER
				if (moveRight)
					Iniko->visionCollideRight = true;

				else if (moveLeft)
					Iniko->visionCollideLeft = true;

				break;
		}
	}

	if (bodyB->getTag() == -1)											//IF FLOOR COLLIDES WITH..
	{
		switch (bodyA->getTag()/100)
		{
			case 2:														//..AN OBJECT
				if(objectsVector.at(bodyA->getTag() - 200)->thrown)
					removeChild(objectsVector.at(bodyA->getTag() - 200)->itemArt);

				changeCameraFollow(Iniko->characterIdleRight);
				break;
		}

		//DEFAULT ACTIONS TO EVERYONE

		bodyA->setVelocity(Vec2::ZERO);
		bodyA->setGravityEnable(false);
		fixPosition(bodyA->getNode(), bodyB->getNode());
	}

	if (bodyA->getTag() == -1)											//IF FLOOR COLLIDES WITH..
	{
		switch (bodyB->getTag()/100)
		{
			case 2:														//..AN OBJECT
				if (objectsVector.at(bodyB->getTag() - 200)->thrown)
					removeChild(objectsVector.at(bodyB->getTag() - 200)->itemArt);

				changeCameraFollow(Iniko->characterIdleRight);
				break;
		}

		//DEFAULT ACTIONS TO EVERYONE

		bodyB->setVelocity(Vec2::ZERO);
		bodyB->setGravityEnable(false);
		fixPosition(bodyB->getNode(), bodyA->getNode());
	}

	return true;
}

bool Level0::onContactSeparate(PhysicsContact &contact)
{
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();

	if (bodyA->getTag() == 00)											//IF CHARACTER STOPS TO COLLIDES WITH..
	{
		switch (bodyB->getTag() / 100)
		{
			case 1:														//..AN ENEMY
				contactBody = PhysicsBody::create();
				break;

			case 2:														//..AN OBJECT
				Iniko->AKey->setVisible(false);
				contactBody = PhysicsBody::create();
				break;
		}
	}

	if (bodyB->getTag() == 00)											//IF CHARACTER STOPS TO COLLIDES WITH..
	{
		switch (bodyA->getTag() / 100)
		{
			case 1:														//..AN ENEMY
				contactBody = PhysicsBody::create();
				break;

			case 2:														//..AN OBJECT
				Iniko->AKey->setVisible(false);
				contactBody = PhysicsBody::create();
				break;
		}
	}

	if (bodyA->getTag() == 01)											//IF CHARACTER RUNNING SOUND STOPS TO COLLIDES WITH..
	{
		switch (bodyB->getTag() / 100)
		{
			case 2:															//..AN OBJECT
				Iniko->AKey->setVisible(false);
				break;
		}
	}

	if (bodyB->getTag() == 01)											//IF CHARACTER RUNNING SOUND STOPS TO COLLIDES WITH..
	{
		switch (bodyA->getTag() / 100)
		{
			case 2:															//..AN OBJECT
				Iniko->AKey->setVisible(false);
				break;
		}
	}

	if (bodyA->getTag() == 03)											//IF CHARACTER VISION STOPS TO COLLIDES WITH..
	{
		switch (bodyB->getTag())
		{
			case 02:													//..VISION COLLIDER
				if (moveLeft)
					Iniko->visionCollideRight = false;

				else if (moveRight)
					Iniko->visionCollideLeft = false;

				break;
		}
	}

	if (bodyB->getTag() == 03)											//IF CHARACTER VISION STOPS TO COLLIDES WITH..
	{
		switch (bodyA->getTag())
		{
			case 02:													//..VISION COLLIDER
				if (moveLeft)
					Iniko->visionCollideRight = false;

				else if (moveRight)
					Iniko->visionCollideLeft = false;

				break;
		}
	}

	if (bodyB->getTag() == -1)											//IF FLOOR STOPS TO COLLIDES WITH..
	{
		bodyA->setGravityEnable(true);
	}

	if (bodyA->getTag() == -1)											//IF FLOOR STOPS TO COLLIDES WITH..
	{
		bodyB->setGravityEnable(true);
	}

	return true;
}

void Level0::changeCameraFollow(Node* target)
{
	cameraFollow = this->runAction(Follow::create(target, Rect(0, visibleSize.height / 2, Layer0->getContentSize().width, 0)));
}

void Level0::fixPosition(Node* image, Node* floor)
{
	image->setPosition(image->getPosition().x, floor->getContentSize().height + (image->getContentSize().height / 2 + 120));
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
			moveCam = true;
			Iniko->visionCollideLeft = false;
			Iniko->visionCollideRight = false;
			changeCameraFollow(Iniko->characterVision);
			break;

		case EventKeyboard::KeyCode::KEY_SHIFT:
			Iniko->stealth = true;
			break;

		case EventKeyboard::KeyCode::KEY_A:
			key = 'A';
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
			moveCam = false;
			Iniko->visionCollideLeft = false;
			Iniko->visionCollideRight = false;
			changeCameraFollow(Iniko->characterIdleRight);
			Iniko->characterVision->setPosition(Iniko->characterIdleRight->getPosition().x, Iniko->characterIdleRight->getPosition().y);
			break;

		case EventKeyboard::KeyCode::KEY_SHIFT:
			_pressedKey = EventKeyboard::KeyCode::KEY_NONE;
			Iniko->stealth = false;
			break;

		case EventKeyboard::KeyCode::KEY_A:
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
	portalParticles->setPosition(Point(1530, 338));
	portalParticles->setPositionType(kCCPositionTypeRelative);
	addChild(portalParticles, 1);

	portalRayParticles = CCParticleSystemQuad::create("Particles/PortalRayParticles/portalray_particle.plist");
	portalRayParticles->setScale(0.4);
	portalRayParticles->setPosition(Point(1535, 345));
	portalRayParticles->setPositionType(kCCPositionTypeRelative);
	addChild(portalRayParticles, 1);
}

void Level0::keyNull()
{
	key = ' ';
}