#include "Character.h"

USING_NS_CC;

Character::Character(int level, int checkpoint)
{
	visibleSize = Director::getInstance()->getVisibleSize();

	facingRight = true;
	stealth = false;
	hide = false;
	jumping = false;
	wallTouch = NULL;
	wallTouchSide = ' ';
	gameOver = false;
	initposx = 0;
	initposy = 0;
	this->checkpoint = checkpoint;
	velocity = 0;
	forceRet = 1;

	forceBarBorder = Sprite::create("images/Characters/Iniko/GUI/BarBorder.png");
	forceBarBorder->setVisible(false);

	forceBar = CCProgressTimer::create(CCSprite::create("images/Characters/Iniko/GUI/ForceBar.png"));
	forceBar->setType(CCProgressTimerType::BAR);
	forceBar->setAnchorPoint(ccp(0, 0));
	forceBar->setBarChangeRate(ccp(1, 0));
	forceBar->setVisible(false);

	createAnimation();

	//JUMPING ART

	characterJumpingRight = Sprite::create("images/Characters/Iniko/InikoJumping_Right.png");
	characterJumpingRight->setPosition(Point(initposx, initposy));
	characterJumpingRightCollider = PhysicsBody::createBox(Size(characterJumpingRight->getContentSize().width, characterJumpingRight->getContentSize().height));
	characterJumpingRightCollider->setContactTestBitmask(true);
	characterJumpingRightCollider->setDynamic(true);
	characterJumpingRightCollider->setCollisionBitmask(0);
	characterJumpingRightCollider->setTag(9000);

	characterJumpingRight->setPhysicsBody(characterJumpingRightCollider);

	characterJumpingLeft = Sprite::create("images/Characters/Iniko/InikoJumping_Left.png");
	characterJumpingLeft->setPosition(Point(initposx, initposy));
	characterJumpingLeftCollider = PhysicsBody::createBox(Size(characterJumpingLeft->getContentSize().width, characterJumpingLeft->getContentSize().height));
	characterJumpingLeftCollider->setContactTestBitmask(true);
	characterJumpingLeftCollider->setDynamic(true);
	characterJumpingLeftCollider->setCollisionBitmask(0);
	characterJumpingLeftCollider->setTag(9000);

	characterJumpingLeft->setPhysicsBody(characterJumpingLeftCollider);

	//CHARACTER COLLIDERS
	//TAGS-> 9000:CHARACTER COLLIDER; 9100:RUNNING SOUND COLLIDER; 9002:VISION BORDER COLLIDER; 9003:VISION COLLIDER;

	runningSoundColliderSprite = Sprite::create("images/Characters/Iniko/Colliders/RunningSoundCollider.png");
	runningSoundColliderSprite->setPosition(Point(characterIdleRight->getPosition().x, characterIdleRight->getPosition().y));
	runningSoundCollider = PhysicsBody::createBox(Size(runningSoundColliderSprite->getContentSize().width, runningSoundColliderSprite->getContentSize().height));
	runningSoundCollider->setContactTestBitmask(true);
	runningSoundCollider->setDynamic(true);
	runningSoundCollider->setCollisionBitmask(0);
	runningSoundCollider->setTag(9100);

	runningSoundColliderSprite->setPhysicsBody(runningSoundCollider);

	//CHARACTER GUI

	characterVision = Sprite::create();
	characterVision->setPosition(Point(characterIdleRight->getPosition().x, characterIdleRight->getPosition().y));

	AKey = Sprite::create("images/Characters/Iniko/GUI/AKey.png");
	AKey->setPosition(Point(characterIdleRight->getPosition().x, characterIdleRight->getPosition().y + (characterIdleRight->getContentSize().height/2 + 80)));
	AKey->setVisible(false);

	SKey = Sprite::create("images/Characters/Iniko/GUI/SKey.png");
	SKey->setPosition(Point(characterIdleRight->getPosition().x, characterIdleRight->getPosition().y + (characterIdleRight->getContentSize().height / 2 + 150)));
	SKey->setVisible(false);

	//SET POSITION

	switch (level)
	{
	case 0:

		switch (checkpoint)
		{
		case 0:
			initposx = 900;
			initposy = (characterIdleRight->getContentSize().height / 2 + 80);
			break;
		}

		break;

	case 1:

		switch (checkpoint)
		{
		case 0:
			initposx = 100;
			//initposx = 14381;
			initposy = (characterIdleRight->getContentSize().height / 2 + 90);
			//initposx = 14381 + 10550;
			//initposy = characterIdleRight->getContentSize().height / 2;
			break;
		}

		break;
	}

	characterIdleRight->setPosition(Point(initposx, initposy));
	characterIdleLeft->setPosition(Point(initposx, initposy));
	characterRunningRight->setPosition(Point(initposx, initposy));
	characterRunningLeft->setPosition(Point(initposx, initposy));
	characterJumpingRight->setPosition(Point(initposx, initposy));
	characterJumpingLeft->setPosition(Point(initposx, initposy));
}

void Character::getHide(bool in)
{
	bool b;

	if (in)
	{
		b = false;
		hide = true;
	}

	else
	{
		b = true;
		hide = false;
	}

	runningSoundCollider->setEnable(b);
	characterIdleRight->setVisible(b);
	characterIdleRightCollider->setEnable(b);
	characterIdleLeft->setVisible(b);
	characterIdleLeftCollider->setEnable(b);
	characterRunningRight->setVisible(b);
	characterRunningRightCollider->setEnable(b);
	characterRunningLeft->setVisible(b);
	characterRunningLeftCollider->setEnable(b);
	characterJumpingRight->setVisible(b);
	characterJumpingRightCollider->setEnable(b);
	characterJumpingLeft->setVisible(b);
	characterJumpingLeftCollider->setEnable(b);
	//characterStealthRight->setVisible(b);
	//characterStealthRightCollider->setEnable(b);
	characterStealthLeft->setVisible(b);
	characterStealthLeftCollider->setEnable(b);
}

void Character::jump(Vec2 force, bool right)
{
	if (right && facingRight)
	{
		characterIdleRight->setPosition(Point(characterIdleRight->getPosition().x, characterIdleRight->getPosition().y + 5));
		characterIdleRightCollider->setVelocity(force);
		jumping = true;
	}

	else if (!right && !facingRight)
	{
		characterIdleRight->setPosition(Point(characterIdleRight->getPosition().x, characterIdleRight->getPosition().y + 5));
		characterIdleRightCollider->setVelocity(force);
		jumping = true;
	}
}

void Character::die()
{
	runningSoundCollider->setEnable(false);
	characterIdleRight->setVisible(false);
	characterIdleRightCollider->setEnable(false);
	characterIdleLeft->setVisible(false);
	characterIdleLeftCollider->setEnable(false);
	characterRunningRight->setVisible(false);
	characterRunningRightCollider->setEnable(false);
	characterRunningLeft->setVisible(false);
	characterRunningLeftCollider->setEnable(false);
	characterJumpingLeft->setVisible(false);
	characterJumpingLeftCollider->setEnable(false);
	characterJumpingRight->setVisible(false);
	characterJumpingRightCollider->setEnable(false);
	//characterStealthRight->setVisible(false);
	//characterStealthRightCollider->setEnable(false);
	characterStealthLeft->setVisible(false);
	characterStealthLeftCollider->setEnable(false);
	gameOver = true;
}

void Character::createAnimation()
{
	int res;
	float factor = Director::getInstance()->getContentScaleFactor();

	if (factor >= 1)
		res = 1;
	else if (factor >= 0.71)
		res = 2;
	else
		res = 3;

	char str[100] = { 0 };

	//INIKO IDLE RIGHT

	sprintf(str, "SpriteSheets/Characters/Iniko/Iniko_IdleRight/InikoIdle_Right%d.png", res);
	characterIdlerightspritebatch = SpriteBatchNode::create(str);
	SpriteFrameCache* characterIdleRightcache = SpriteFrameCache::getInstance();
	sprintf(str, "SpriteSheets/Characters/Iniko/Iniko_IdleRight/InikoIdle_Right%d.plist", res);
	characterIdleRightcache->addSpriteFramesWithFile(str);

	characterIdleRight = Sprite::createWithSpriteFrameName("InikoIdle_Right1.png");
	characterIdlerightspritebatch->addChild(characterIdleRight);
	characterIdlerightspritebatch->setVisible(true);

	Vector<SpriteFrame*> characterIdleRightanimFrames(12);

	for (int i = 1; i <= 12; i++)
	{
		sprintf(str, "InikoIdle_Right%d.png", i);
		SpriteFrame* frame = characterIdleRightcache->getSpriteFrameByName(str);
		characterIdleRightanimFrames.pushBack(frame);
	}

	Animation* characterIdleRightanimation = Animation::createWithSpriteFrames(characterIdleRightanimFrames, 0.1f);
	characterIdleRight->runAction(RepeatForever::create(Animate::create(characterIdleRightanimation)));

	characterIdleRightCollider = PhysicsBody::createBox(Size((characterIdleRight->getContentSize().width), 301));
	characterIdleRightCollider->setContactTestBitmask(true);
	characterIdleRightCollider->setDynamic(true);
	characterIdleRightCollider->setCollisionBitmask(0);
	characterIdleRightCollider->setTag(9000);

	characterIdleRight->setPhysicsBody(characterIdleRightCollider);

	//INIKO IDLE LEFT

	sprintf(str, "SpriteSheets/Characters/Iniko/Iniko_IdleLeft/InikoIdle_Left%d.png", res);
	characterIdleleftspritebatch = SpriteBatchNode::create(str);
	SpriteFrameCache* characterIdleLeftcache = SpriteFrameCache::getInstance();
	sprintf(str, "SpriteSheets/Characters/Iniko/Iniko_IdleLeft/InikoIdle_Left%d.plist", res);
	characterIdleLeftcache->addSpriteFramesWithFile(str);

	characterIdleLeft = Sprite::createWithSpriteFrameName("InikoIdle_Left1.png");
	characterIdleleftspritebatch->addChild(characterIdleLeft);
	characterIdleleftspritebatch->setVisible(false);

	Vector<SpriteFrame*> characterIdleLeftanimFrames(12);

	for (int i = 1; i <= 12; i++)
	{
		sprintf(str, "InikoIdle_Left%d.png", i);
		SpriteFrame* frame = characterIdleLeftcache->getSpriteFrameByName(str);
		characterIdleLeftanimFrames.pushBack(frame);
	}

	Animation* characterIdleLeftanimation = Animation::createWithSpriteFrames(characterIdleLeftanimFrames, 0.1f);
	characterIdleLeft->runAction(RepeatForever::create(Animate::create(characterIdleLeftanimation)));

	characterIdleLeftCollider = PhysicsBody::createBox(Size((characterIdleLeft->getContentSize().width), 301));
	characterIdleLeftCollider->setContactTestBitmask(true);
	characterIdleLeftCollider->setDynamic(true);
	characterIdleLeftCollider->setCollisionBitmask(0);
	characterIdleLeftCollider->setTag(9000);

	characterIdleLeft->setPhysicsBody(characterIdleLeftCollider);

	//INIKO RUNNING RIGHT

	sprintf(str, "SpriteSheets/Characters/Iniko/InikoRunningRight/InikoRunningRight%d.png", res);
	characterRunningRightspritebatch = SpriteBatchNode::create(str);
	SpriteFrameCache* characterRunningRightcache = SpriteFrameCache::getInstance();
	sprintf(str, "SpriteSheets/Characters/Iniko/InikoRunningRight/InikoRunningRight%d.plist", res);
	characterRunningRightcache->addSpriteFramesWithFile(str);

	characterRunningRight = Sprite::createWithSpriteFrameName("InikoRunning_Right1.png");
	characterRunningRightspritebatch->addChild(characterRunningRight);
	characterRunningRightspritebatch->setVisible(false);

	Vector<SpriteFrame*> characterRunningRightanimFrames(34);

	for (int i = 1; i <= 34; i++)
	{
		sprintf(str, "InikoRunning_Right%d.png", i);
		SpriteFrame* frame = characterRunningRightcache->getSpriteFrameByName(str);
		characterRunningRightanimFrames.pushBack(frame);
	}

	Animation* characterRunningRightanimation = Animation::createWithSpriteFrames(characterRunningRightanimFrames, 0.025f);
	characterRunningRight->runAction(RepeatForever::create(Animate::create(characterRunningRightanimation)));

	characterRunningRightCollider = PhysicsBody::createBox(Size((characterRunningRight->getContentSize().width), 304));
	characterRunningRightCollider->setContactTestBitmask(true);
	characterRunningRightCollider->setDynamic(true);
	characterRunningRightCollider->setCollisionBitmask(0);
	characterRunningRightCollider->setTag(9000);

	characterRunningRight->setPhysicsBody(characterRunningRightCollider);

	//INIKO RUNNING LEFT

	sprintf(str, "SpriteSheets/Characters/Iniko/InikoRunningLeft/InikoRunningLeft%d.png", res);
	characterRunningLeftspritebatch = SpriteBatchNode::create(str);
	SpriteFrameCache* characterRunningLeftcache = SpriteFrameCache::getInstance();
	sprintf(str, "SpriteSheets/Characters/Iniko/InikoRunningLeft/InikoRunningLeft%d.plist", res);
	characterRunningLeftcache->addSpriteFramesWithFile(str);

	characterRunningLeft = Sprite::createWithSpriteFrameName("InikoRunning_Left1.png");
	characterRunningLeftspritebatch->addChild(characterRunningLeft);
	characterRunningLeftspritebatch->setVisible(false);

	Vector<SpriteFrame*> characterRunningLeftanimFrames(34);

	for (int i = 1; i <= 34; i++)
	{
		sprintf(str, "InikoRunning_Left%d.png", i);
		SpriteFrame* frame = characterRunningLeftcache->getSpriteFrameByName(str);
		characterRunningLeftanimFrames.pushBack(frame);
	}

	Animation* characterRunningLeftanimation = Animation::createWithSpriteFrames(characterRunningLeftanimFrames, 0.025f);
	characterRunningLeft->runAction(RepeatForever::create(Animate::create(characterRunningLeftanimation)));

	characterRunningLeftCollider = PhysicsBody::createBox(Size((characterRunningLeft->getContentSize().width), 304));
	characterRunningLeftCollider->setContactTestBitmask(true);
	characterRunningLeftCollider->setDynamic(true);
	characterRunningLeftCollider->setCollisionBitmask(0);
	characterRunningLeftCollider->setTag(9000);

	characterRunningLeft->setPhysicsBody(characterRunningLeftCollider);
}