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

	//CREATE BACKGROUND LAYERS

	createBackground();
	
	//CREATE ANIMATED OBJECTS

	int res;				

	if (visibleSize.width >= 1920)				//CHECK RESOLUTION TO
		res = 1;								//SELECT THE SPRITE SHEET
	else if (visibleSize.width >= 1366)
		res = 2;
	else
		res = 3;

	char str[100] = { 0 };

	sprintf(str, "images/Level0/Assets/SpriteSheets/Portal/FramesPortal%d.png", res);
	SpriteBatchNode* Portal1spritebatch = SpriteBatchNode::create(str);
	SpriteFrameCache* Portal1cache = SpriteFrameCache::getInstance();
	sprintf(str, "images/Level0/Assets/SpriteSheets/Portal/FramesPortal%d.plist", res);
	Portal1cache->addSpriteFramesWithFile(str);

	Portal1 = Sprite::createWithSpriteFrameName("Portal1.png");
	Portal1->setPosition(Point(1530, 338));
	Portal1spritebatch->addChild(Portal1);
	addChild(Portal1spritebatch, 3);
	
	Vector<SpriteFrame*> Portal1animFrames(27);
	
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
	addChild(Iniko->characterVision, 3);
	
	//CREATE VIRTUAL CAMERA

	changeCameraFollow(Iniko->characterArt);

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
	
	Layer3 = Sprite::create("images/Level0/Layers/Level0_Layer3.png");
	Layer3->setScaleX(factor.width);
	Layer3->setScaleY(factor.height);
	Layer3->setPosition(Point((Layer3->getContentSize().width/2) * factor.width, (Layer3->getContentSize().height/2) * factor.height));

	addChild(Layer3, 3);

	Floor = Sprite::create("images/Level0/Assets/FloorCollider.png");
	Floor->setScaleX(factor.width);
	Floor->setScaleY(factor.height);
	Floor->setPosition(Point((Floor->getContentSize().width/2) * factor.width, (Floor->getContentSize().height/2)) * factor.height);

	addChild(Floor, 3);

	FloorCollider = PhysicsBody::createBox(Size(Floor->getContentSize().width * factor.width, Floor->getContentSize().height * factor.height));
	FloorCollider->setContactTestBitmask(true);
	FloorCollider->setDynamic(true);
	FloorCollider->setCollisionBitmask(0);
	FloorCollider->setGravityEnable(false);
	FloorCollider->setTag(-1);

	Floor->setPhysicsBody(FloorCollider);
	
	Layer4 = Sprite::create("images/Level0/Layers/Level0_Layer4.png");
	Layer4->setScaleX(factor.width);
	Layer4->setScaleY(factor.height);
	Layer4->setPosition(Point((Layer4->getContentSize().width/2) * factor.width, (Layer4->getContentSize().height/2) * factor.height));

	addChild(Layer4, 4);
}

void Level0::update(float dt)
{
	if (moveRight && !moveCam)
	{
		Iniko->characterMove(1);
	}

	if (moveLeft && !moveCam)
	{
		Iniko->characterMove(2);
	}

	if (moveRight && moveCam)
	{
		Iniko->moveCam(1);
	}

	if (moveLeft && moveCam)
	{
		Iniko->moveCam(2);
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

	if (bodyA->getTag() == 0)							//IF CHARACTER COLLIDES WITH..
	{
		switch (bodyB->getTag())
		{
			case 2:										//..AN OBJECT
				vasijaPequeña1->getThrow();
				changeCameraFollow(bodyB->getNode());
				break;
		}
	}

	if (bodyB->getTag() == 0)							//IF CHARACTER COLLIDES WITH..
	{
		switch (bodyA->getTag())
		{
		case 2:											//..AN OBJECT
			vasijaPequeña1->getThrow();
			changeCameraFollow(bodyA->getNode());
			break;
		}
	}


	if (bodyB->getTag() == -1)							//IF FLOOR COLLIDES WITH..
	{
		switch (bodyA->getTag())
		{
			case 2:										//..AN OBJECT
				changeCameraFollow(Iniko->characterArt);
				break;
		}

		//DEFAULT ACTIONS TO EVERYONE

		bodyA->setVelocity(Vec2::ZERO);
		bodyA->setGravityEnable(false);
		fixPosition(bodyA->getNode(), bodyB->getNode());
	}

	if (bodyA->getTag() == -1)							//IF FLOOR COLLIDES WITH..
	{
		switch (bodyB->getTag())
		{
			case 2:										//..AN OBJECT
				changeCameraFollow(Iniko->characterArt);
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

	if (bodyB->getTag() == -1)							//IF FLOOR STOPS TO COLLIDES WITH..
	{
		bodyA->setGravityEnable(true);
	}

	if (bodyA->getTag() == -1)							//IF FLOOR STOPS TO COLLIDES WITH..
	{
		bodyB->setGravityEnable(true);
	}

	return true;
}

void Level0::changeCameraFollow(Node* target)
{
	cameraFollow = this->runAction(Follow::create(target, Rect(0, visibleSize.height/2, Layer0->getContentSize().width * factor.width, 0)));
}

void Level0::fixPosition(Node* image, Node* floor)
{
	image->setPosition(image->getPosition().x, (floor->getContentSize().height + image->getContentSize().height / 2 + 120) * factor.height);
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
		moveCam = false;
		changeCameraFollow(Iniko->characterArt);
		break;
	}
}