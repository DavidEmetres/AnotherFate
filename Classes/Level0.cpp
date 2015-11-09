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
	factor = Size(visibleSize.width / 1920, visibleSize.height / 1080);

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

	addChild(Iniko->characterIdlerightspritebatch, 3);
	addChild(Iniko->characterRunningRightspritebatch, 3);
	addChild(Iniko->characterIdleleftspritebatch, 3);
	addChild(Iniko->characterRunningLeftspritebatch, 3);
	addChild(Iniko->characterVision, 3);
	addChild(Iniko->AKey, 3);

	//CREATE FLOOR

	Layer3 = Sprite::create("images/Level0/Layers/Level0_Layer3.png");
	Layer3->setScaleX(factor.width);
	Layer3->setScaleY(factor.height);
	Layer3->setPosition(Point((Layer3->getContentSize().width / 2) * factor.width, (Layer3->getContentSize().height / 2) * factor.height));

	addChild(Layer3, 3);

	Floor = Sprite::create("images/Level0/Assets/FloorCollider.png");
	Floor->setScaleX(factor.width);
	Floor->setScaleY(factor.height);
	Floor->setPosition(Point((Floor->getContentSize().width / 2) * factor.width, (Floor->getContentSize().height / 2) * factor.height));
	Floor->setVisible(false);

	addChild(Floor, 3);

	FloorCollider = PhysicsBody::createBox(Size(Floor->getContentSize().width * factor.width, Floor->getContentSize().height * factor.height));
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
	Layer0->setScaleX(factor.width);
	Layer0->setScaleY(factor.height);
	Layer0->setPosition(Point((Layer0->getContentSize().width/2) * factor.width, (Layer0->getContentSize().height/2) * factor.height));

	addChild(Layer0, 0);
	
	Layer1 = Sprite::create("images/Level0/Layers/Level0_Layer1.png");
	Layer1->setScaleX(factor.width);
	Layer1->setScaleY(factor.height);
	Layer1->setPosition(Point((Layer1->getContentSize().width/2) * factor.width, (Layer1->getContentSize().height/2) * factor.height));

	addChild(Layer1, 1);
	
	Layer2 = Sprite::create("images/Level0/Layers/Level0_Layer2.png");
	Layer2->setScaleX(factor.width);
	Layer2->setScaleY(factor.height);
	Layer2->setPosition(Point((Layer2->getContentSize().width/2) * factor.width, (Layer2->getContentSize().height/2) * factor.height));

	addChild(Layer2, 2);
	
	Layer4 = Sprite::create("images/Level0/Layers/Level0_Layer4.png");
	Layer4->setScaleX(factor.width);
	Layer4->setScaleY(factor.height);
	Layer4->setPosition(Point((Layer4->getContentSize().width/2) * factor.width, (Layer4->getContentSize().height/2) * factor.height));

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

	if (moveRight && !moveCam)
	{
		Iniko->facingRight = true;
		Iniko->characterMove(1);
		Iniko->characterIdlerightspritebatch->setVisible(false);
		Iniko->characterIdleleftspritebatch->setVisible(false);
		Iniko->characterRunningLeftspritebatch->setVisible(false);
		Iniko->characterRunningRightspritebatch->setVisible(true);
	}

	if (moveLeft && !moveCam)
	{
		Iniko->facingRight = false;
		Iniko->characterMove(2);
		Iniko->characterIdlerightspritebatch->setVisible(false);
		Iniko->characterIdleleftspritebatch->setVisible(false);
		Iniko->characterRunningRightspritebatch->setVisible(false);
		Iniko->characterRunningLeftspritebatch->setVisible(true);
	}

	if (moveLeft && moveRight)
	{
		Iniko->facingRight = true;
		Iniko->characterIdlerightspritebatch->setVisible(true);
		Iniko->characterIdleleftspritebatch->setVisible(false);
		Iniko->characterRunningLeftspritebatch->setVisible(false);
		Iniko->characterRunningRightspritebatch->setVisible(false);
	}

	if (moveRight && moveCam)
	{
		Iniko->moveCam(1);
	}
	
	if (moveLeft && moveCam)
	{
		Iniko->moveCam(2);
	}

	//COLLISION UPDATE

	switch (contactBody->getTag() / 100)
	{
		case 2:
			if (key == 'A')
			{
				objectsVector.at(contactBody->getTag() - 200)->getThrow(Iniko->facingRight);
				changeCameraFollow(contactBody->getNode());
				break;
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

	if (bodyA->getTag() == 0)											//IF CHARACTER COLLIDES WITH..
	{
		contactBody = bodyB;

		switch (bodyB->getTag()/100)
		{
			case 2:														//..AN OBJECT
				Iniko->AKey->setVisible(true);
				break;
		}
	}

	if (bodyB->getTag() == 0)											//IF CHARACTER COLLIDES WITH..
	{
		contactBody = bodyA;

		switch (bodyA->getTag()/100)
		{
			case 2:														//..AN OBJECT
				Iniko->AKey->setVisible(true);
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

	if (bodyA->getTag() == 0)											//IF CHARACTER COLLIDES WITH..
	{
		switch (bodyB->getTag() / 100)
		{
			case 2:														//..AN OBJECT
				Iniko->AKey->setVisible(false);
				break;
		}
	}

	if (bodyB->getTag() == 0)											//IF CHARACTER COLLIDES WITH..
	{
		switch (bodyA->getTag() / 100)
		{
			case 2:														//..AN OBJECT
				Iniko->AKey->setVisible(false);
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

	contactBody = PhysicsBody::create();

	return true;
}

void Level0::changeCameraFollow(Node* target)
{
	cameraFollow = this->runAction(Follow::create(target, Rect(0, visibleSize.height/2, Layer0->getContentSize().width * factor.width, 0)));
}

void Level0::fixPosition(Node* image, Node* floor)
{
	image->setPosition(image->getPosition().x * factor.width, floor->getContentSize().height * factor.height + (image->getContentSize().height / 2 + 120) * factor.height);
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
			changeCameraFollow(Iniko->characterVision);
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
			changeCameraFollow(Iniko->characterIdleRight);
			Iniko->characterVision->setPosition(Iniko->characterIdleRight->getPosition().x, Iniko->characterIdleRight->getPosition().y);
			break;

		case EventKeyboard::KeyCode::KEY_A:
			_pressedKey = EventKeyboard::KeyCode::KEY_NONE;
			key = ' ';
			break;
	}
}

void Level0::createAnimations()
{
	int res;

	if (visibleSize.width >= 1920)				//CHECK RESOLUTION TO
		res = 1;								//SELECT THE SPRITE SHEET
	else if (visibleSize.width >= 1366)
		res = 2;
	else
		res = 3;

	char str[100] = { 0 };

	//PORTAL PARTICLES

	portalParticles = CCParticleSystemQuad::create("images/Particles/PortalParticles/portal_particle.plist");
	portalParticles->setPosition(Point(1530 * factor.height, 338 * factor.height));
	portalParticles->setScaleX(factor.width * 0.4);
	portalParticles->setScaleY(factor.height * 0.4);
	portalParticles->setPositionType(kCCPositionTypeRelative);
	addChild(portalParticles, 1);

	portalRayParticles = CCParticleSystemQuad::create("images/Particles/PortalRayParticles/portalray_particle.plist");
	portalRayParticles->setPosition(Point(1535 * factor.height, 345 * factor.height));
	portalRayParticles->setScaleX(factor.width * 0.42);
	portalRayParticles->setScaleY(factor.height * 0.42);
	portalRayParticles->setPositionType(kCCPositionTypeRelative);
	addChild(portalRayParticles, 1);
}

void Level0::keyNull()
{
	key = ' ';
}