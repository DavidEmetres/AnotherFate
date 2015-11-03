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

	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	moveRight = false;
	moveLeft = false;

	//CREATE BACKGROUND LAYERS

	createBackground();
	
	//CREATE ANIMATED OBJECTS

	////////////////COLLISION EXAMPLE//////////////////////////

	Portal2 = Sprite::create("images/Characters/Iniko.png");
	Portal2->setPosition(Point(1200, 800 + Portal2->getContentSize().height/2));
	addChild(Portal2, 3);

	Portal2Collider = PhysicsBody::createBox(Size(Portal2->getContentSize().width, Portal2->getContentSize().height));
	Portal2Collider->setContactTestBitmask(true);
	Portal2Collider->setDynamic(true);
	Portal2Collider->setCollisionBitmask(0);
	Portal2Collider->setTag(1); //TAG 1 = OBJECT
	
	Portal2->setPhysicsBody(Portal2Collider);

	////////////////COLLISION EXAMPLE//////////////////////////

	SpriteBatchNode* Portal1spritebatch = SpriteBatchNode::create("images/Level0/Assets/PortalSpriteSheet.png");
	SpriteFrameCache* Portal1cache = SpriteFrameCache::getInstance();
	Portal1cache->addSpriteFramesWithFile("images/Level0/Assets/PortalSpriteSheet.plist");
	
	Portal1 = Sprite::createWithSpriteFrameName("Portal1.png");
	Portal1->setPosition(Point(1530, 338));
	Portal1spritebatch->addChild(Portal1);
	addChild(Portal1spritebatch, 3);
	
	Vector<SpriteFrame*> Portal1animFrames(27);
	
	char str[100] = {0};
	for(int i = 1; i <= 27; i++)
	{
		sprintf(str, "Portal%d.png", i);
		SpriteFrame* frame = Portal1cache->getSpriteFrameByName(str);
		Portal1animFrames.pushBack(frame);
	}
	
	Animation* Portal1animation = Animation::createWithSpriteFrames(Portal1animFrames, 0.08f);
	Portal1->runAction(RepeatForever::create(Animate::create(Portal1animation)));

	//CREATE INTERACTIVE ITEMS

	vasijaPequeña1 = new Item(2);
	addChild(vasijaPequeña1->itemArt, 3);

	//CREATE CHARACTER

	Iniko = new Character();

	addChild(Iniko->characterArt, 3);
	
	//CREATE VIRTUAL CAMERA

	cameraFollow = this->runAction(Follow::create(Iniko->characterArt, Rect(0, visibleSize.height/2, 10500, 0)));

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
	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	Layer0 = Sprite::create("images/Level0/Layers/Level0_Layer0.png");
	Layer0->setPosition(Point(Layer0->getContentSize().width/2, visibleSize.height - Layer0->getContentSize().height/2));

	addChild(Layer0, 0);
	
	Layer1 = Sprite::create("images/Level0/Layers/Level0_Layer1.png");
	Layer1->setPosition(Point(Layer1->getContentSize().width/2, visibleSize.height - Layer1->getContentSize().height/2));

	addChild(Layer1, 1);
	
	Layer2 = Sprite::create("images/Level0/Layers/Level0_Layer2.png");
	Layer2->setPosition(Point(Layer2->getContentSize().width/2, visibleSize.height - Layer2->getContentSize().height/2));

	addChild(Layer2, 2);
	
	Layer3 = Sprite::create("images/Level0/Layers/Level0_Layer3.png");
	Layer3->setPosition(Point(Layer3->getContentSize().width/2, visibleSize.height - Layer3->getContentSize().height/2));

	addChild(Layer3, 3);

	Floor = Sprite::create("images/Level0/Assets/FloorCollider.png");
	Floor->setPosition(Point(Floor->getContentSize().width / 2, Floor->getContentSize().height / 2));

	addChild(Floor, 3);

	FloorCollider = PhysicsBody::createBox(Size(10500, 85));
	FloorCollider->setContactTestBitmask(true);
	FloorCollider->setDynamic(true);
	FloorCollider->setCollisionBitmask(0);
	FloorCollider->setGravityEnable(false);
	FloorCollider->setTag(-1);

	Floor->setPhysicsBody(FloorCollider);
	
	Layer4 = Sprite::create("images/Level0/Layers/Level0_Layer4.png");
	Layer4->setPosition(Point(Layer4->getContentSize().width/2, visibleSize.height - Layer4->getContentSize().height/2));

	addChild(Layer4, 4);
}

void Level0::update(float dt)
{
	if (moveRight)
	{
		Iniko->characterMove(1);
	}

	if (moveLeft)
	{
		Iniko->characterMove(2);
	}
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

	if (bodyA->getTag() == 0)
	{
		switch (bodyB->getTag())
		{
			case 2:
				vasijaPequeña1->getThrow();
				changeCameraFollow(bodyB->getNode());
				break;

			case 1:
				Portal2->setVisible(false);
				break;
		}
	}

	if (bodyB->getTag() == 0)
	{
		switch (bodyA->getTag())
		{
		case 2:
			vasijaPequeña1->getThrow();
			changeCameraFollow(bodyA->getNode());
			break;

		case 1:
			Portal2->setVisible(false);
			break;
		}
	}


	if (bodyB->getTag() == -1)
	{
		switch (bodyA->getTag())
		{
			case 2:
				changeCameraFollow(Iniko->characterArt);
				break;
		}

		bodyA->setVelocity(Vec2::ZERO);
		bodyA->setGravityEnable(false);
		fixPosition(bodyA->getNode(), bodyB->getNode());
	}

	if (bodyA->getTag() == -1)
	{
		switch (bodyB->getTag())
		{
			case 2:
				changeCameraFollow(Iniko->characterArt);
				break;
		}

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

	if (bodyB->getTag() == -1)
	{
		bodyA->setGravityEnable(true);
	}

	if (bodyA->getTag() == -1)
	{
		bodyB->setGravityEnable(true);
	}

	return true;
}

void Level0::changeCameraFollow(Node* target)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	cameraFollow = this->runAction(Follow::create(target, Rect(0, visibleSize.height / 2, 10500, 0)));
}

void Level0::fixPosition(Node* image, Node* floor)
{
	image->setPosition(image->getPosition().x, floor->getContentSize().height + image->getContentSize().height / 2 + 120);
}
