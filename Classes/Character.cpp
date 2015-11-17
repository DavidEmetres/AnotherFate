#include "Character.h"

USING_NS_CC;

Character::Character()
{
	visibleSize = Director::getInstance()->getVisibleSize();

	facingRight = true;
	visionCollideRight = false;
	visionCollideLeft = false;
	stealth = false;

	createAnimation();

	characterIdleRight->setPosition(Point(900, (characterIdleRight->getContentSize().height / 2 + 80)));
	characterIdleLeft->setPosition(Point(900, (characterIdleRight->getContentSize().height / 2 + 80)));
	characterRunningRight->setPosition(Point(900, (characterIdleRight->getContentSize().height / 2 + 80)));
	characterRunningLeft->setPosition(Point(900, (characterIdleRight->getContentSize().height / 2 + 80)));

	characterVision = Sprite::create();
	characterVision->setPosition(Point(900, (characterIdleRight->getContentSize().height / 2 + 80)));
	characterVisionCollider = PhysicsBody::createBox(Size(10, 10));
	characterVisionCollider->setContactTestBitmask(true);
	characterVisionCollider->setDynamic(true);
	characterVisionCollider->setCollisionBitmask(0);
	characterVisionCollider->setTag(03);

	characterVision->setPhysicsBody(characterVisionCollider);

	//CHARACTER COLLIDERS
	//TAGS-> 00:CHARACTER COLLIDER; 01:RUNNING SOUND COLLIDER; 02:VISION BORDER COLLIDER; 03:VISION COLLIDER;

	runningSoundColliderSprite = Sprite::create("images/Characters/Iniko/Colliders/RunningSoundCollider.png");
	runningSoundColliderSprite->setPosition(Point(characterIdleRight->getPosition().x, characterIdleRight->getPosition().y));
	runningSoundCollider = PhysicsBody::createBox(Size(runningSoundColliderSprite->getContentSize().width, runningSoundColliderSprite->getContentSize().height));
	runningSoundCollider->setContactTestBitmask(true);
	runningSoundCollider->setDynamic(true);
	runningSoundCollider->setCollisionBitmask(0);
	runningSoundCollider->setTag(01);

	runningSoundColliderSprite->setPhysicsBody(runningSoundCollider);

	visionColliderSpriteLeft = Sprite::create("images/Characters/Iniko/Colliders/VisionCollider.png");
	visionColliderSpriteLeft->setPosition(Point(characterIdleRight->getPosition().x - 900, characterIdleRight->getPosition().y));
	visionColliderLeft = PhysicsBody::createBox(Size(visionColliderSpriteLeft->getContentSize().width, visionColliderSpriteLeft->getContentSize().height));
	visionColliderLeft->setContactTestBitmask(true);
	visionColliderLeft->setDynamic(true);
	visionColliderLeft->setCollisionBitmask(0);
	visionColliderLeft->setTag(02);

	visionColliderSpriteLeft->setPhysicsBody(visionColliderLeft);

	visionColliderSpriteRight = Sprite::create("images/Characters/Iniko/Colliders/VisionCollider.png");
	visionColliderSpriteRight->setPosition(Point(characterIdleRight->getPosition().x + 900, characterIdleRight->getPosition().y));
	visionColliderRight = PhysicsBody::createBox(Size(visionColliderSpriteRight->getContentSize().width, visionColliderSpriteRight->getContentSize().height));
	visionColliderRight->setContactTestBitmask(true);
	visionColliderRight->setDynamic(true);
	visionColliderRight->setCollisionBitmask(0);
	visionColliderRight->setTag(02);

	visionColliderSpriteRight->setPhysicsBody(visionColliderRight);

	//CHARACTER GUI

	AKey = Sprite::create("images/Characters/Iniko/GUI/AKey.png");
	AKey->setPosition(Point(characterIdleRight->getPosition().x, characterIdleRight->getPosition().y + (characterIdleRight->getContentSize().height/2 + 80)));
	AKey->setVisible(false);
}

void Character::characterMove(int direction, float deltaTime)
{
	Vec2 newPos;

	switch (direction)
	{
		case 1:
			if(stealth)
				newPos = Vec2(characterIdleRight->getPosition().x + (200 * deltaTime), characterIdleRight->getPosition().y);
			else
				newPos = Vec2(characterIdleRight->getPosition().x + (800 * deltaTime), characterIdleRight->getPosition().y);
			runningSoundColliderSprite->setPosition(newPos);
			visionColliderSpriteLeft->setPosition(newPos.x - 900, newPos.y);
			visionColliderSpriteRight->setPosition(newPos.x + 900, newPos.y);
			characterVision->setPosition(newPos);
			characterRunningRight->setPosition(newPos);
			characterRunningLeft->setPosition(newPos);
			characterIdleRight->setPosition(newPos);
			characterIdleLeft->setPosition(newPos);
			AKey->setPositionX(newPos.x);
			break;

		case 2:
			if(stealth)
				newPos = Vec2(characterIdleRight->getPosition().x - (200 * deltaTime), characterIdleRight->getPosition().y);
			else
				newPos = Vec2(characterIdleRight->getPosition().x - (800 * deltaTime), characterIdleRight->getPosition().y);
			runningSoundColliderSprite->setPosition(newPos);
			visionColliderSpriteLeft->setPosition(newPos.x - 900, newPos.y);
			visionColliderSpriteRight->setPosition(newPos.x + 900, newPos.y);
			characterVision->setPosition(newPos);
			characterRunningRight->setPosition(newPos);
			characterRunningLeft->setPosition(newPos);
			characterIdleRight->setPosition(newPos);
			characterIdleLeft->setPosition(newPos);
			AKey->setPositionX(newPos.x);
			break;
	}
}

void Character::moveCam(int direction, float deltaTime)
{
	Vec2 newPos;

	switch (direction)
	{
		case 1:
			newPos = Vec2(characterVision->getPosition().x + (1500 * deltaTime), characterVision->getPosition().y);
			characterVision->setPosition(newPos);
			break;

		case 2:
			newPos = Vec2(characterVision->getPosition().x - (1500 * deltaTime), characterVision->getPosition().y);
			characterVision->setPosition(newPos);
			break;
	}
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
	characterIdleRightCollider->setTag(00);

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
	characterIdleLeftCollider->setTag(00);

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

	Animation* characterRunningRightanimation = Animation::createWithSpriteFrames(characterRunningRightanimFrames, 0.03f);
	characterRunningRight->runAction(RepeatForever::create(Animate::create(characterRunningRightanimation)));

	characterRunningRightCollider = PhysicsBody::createBox(Size((characterRunningRight->getContentSize().width), 304));
	characterRunningRightCollider->setContactTestBitmask(true);
	characterRunningRightCollider->setDynamic(true);
	characterRunningRightCollider->setCollisionBitmask(0);
	characterRunningRightCollider->setTag(00);

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

	Animation* characterRunningLeftanimation = Animation::createWithSpriteFrames(characterRunningLeftanimFrames, 0.03f);
	characterRunningLeft->runAction(RepeatForever::create(Animate::create(characterRunningLeftanimation)));

	characterRunningLeftCollider = PhysicsBody::createBox(Size((characterRunningLeft->getContentSize().width), 304));
	characterRunningLeftCollider->setContactTestBitmask(true);
	characterRunningLeftCollider->setDynamic(true);
	characterRunningLeftCollider->setCollisionBitmask(0);
	characterRunningLeftCollider->setTag(00);

	characterRunningLeft->setPhysicsBody(characterRunningLeftCollider);
}