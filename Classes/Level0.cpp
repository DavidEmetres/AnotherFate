#include "Level0.h"

USING_NS_CC;

Scene* Level0::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Level0::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Level0::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	
	moveRight = false;
	moveLeft = false;
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	createBackground();
	
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
	
	Iniko = Sprite::create("images/Characters/Iniko.png");
	Iniko->setPosition(Point(visibleSize.width/2, Iniko->getContentSize().height/2 + 85));
	
	addChild(Iniko, 3);
	
	this->runAction(Follow::create(Iniko, Rect(0, visibleSize.height/2, 10500, 0)));

	this->scheduleUpdate();
	
	auto listener = EventListenerKeyboard::create();

	listener->onKeyPressed = CC_CALLBACK_2(Level0::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(Level0::onKeyReleased, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

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
	
	Layer4 = Sprite::create("images/Level0/Layers/Level0_Layer4.png");
	Layer4->setPosition(Point(Layer4->getContentSize().width/2, visibleSize.height - Layer4->getContentSize().height/2));

	addChild(Layer4, 4);
}

void Level0::update(float dt)
{
	if(moveRight)
	{
		//backgroundMove(1);
		characterMove(1);
	}
	
	else if(moveLeft)
	{
		//backgroundMove(2);
		characterMove(2);
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
	if (_pressedKey == keyCode)
	{
		_pressedKey = EventKeyboard::KeyCode::KEY_NONE;
		moveRight = false;
		moveLeft = false;
	}
}

void Level0::backgroundMove(int direction)
{
	/*Vec2 newPos0;
	Vec2 newPos1;
	Vec2 newPos2;
	Vec2 newPos3;
	Vec2 newPos4;*/
	
	switch(direction)
	{
		case 1:
			/*newPos0 = Vec2(Layer0->getPosition().x - 6, Layer0->getPosition().y);
			Layer0->setPosition(newPos0);
			newPos1 = Vec2(Layer1->getPosition().x - 6, Layer1->getPosition().y);
			Layer1->setPosition(newPos1);
			newPos2 = Vec2(Layer2->getPosition().x - 6, Layer2->getPosition().y);
			Layer2->setPosition(newPos2);
			newPos3 = Vec2(Layer3->getPosition().x - 6, Layer3->getPosition().y);
			Layer3->setPosition(newPos3);
			newPos4 = Vec2(Layer4->getPosition().x - 6, Layer4->getPosition().y);
			Layer4->setPosition(newPos4);	*/	
			break;
			
		case 2:
			/*newPos0 = Vec2(Layer0->getPosition().x + 6, Layer0->getPosition().y);
			Layer0->setPosition(newPos0);
			newPos1 = Vec2(Layer1->getPosition().x + 6, Layer1->getPosition().y);
			Layer1->setPosition(newPos1);
			newPos2 = Vec2(Layer2->getPosition().x + 6, Layer2->getPosition().y);
			Layer2->setPosition(newPos2);
			newPos3 = Vec2(Layer3->getPosition().x + 6, Layer3->getPosition().y);
			Layer3->setPosition(newPos3);
			newPos4 = Vec2(Layer4->getPosition().x + 6, Layer4->getPosition().y);
			Layer4->setPosition(newPos4);	*/	
			break;
	}
}

void Level0::characterMove(int direction)
{
	Vec2 newPos;
	
	switch(direction)
	{
		case 1:
			newPos = Vec2(Iniko->getPosition().x + 6, Iniko->getPosition().y);
			Iniko->setPosition(newPos);			
			break;			
			
		case 2:
			newPos = Vec2(Iniko->getPosition().x - 6, Iniko->getPosition().y);
			Iniko->setPosition(newPos);			
			break;
	}
}
