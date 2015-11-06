#include "Character.h"

USING_NS_CC;

Character::Character()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	factor = Size(visibleSize.width / 1920, visibleSize.height / 1080);

	characterArt = Sprite::create("images/Characters/Iniko.png");
	characterArt->setScaleX(factor.width);
	characterArt->setScaleY(factor.height);
	characterArt->setPosition(Point(visibleSize.width / 2, (characterArt->getContentSize().height / 2 + 90) * factor.height));

	characterCollider = PhysicsBody::createBox(Size((characterArt->getContentSize().width) * factor.width, (characterArt->getContentSize().height) * factor.height));
	characterCollider->setContactTestBitmask(true);
	characterCollider->setDynamic(true);
	characterCollider->setCollisionBitmask(0);
	characterCollider->setTag(0); //TAG 0 = CHARACTER

	characterArt->setPhysicsBody(characterCollider);

	createAnimation();

	characterVision = Sprite::create();
	characterVision->setPosition(Point(visibleSize.width / 2, (characterArt->getContentSize().height / 2 + 90) * factor.height));
}

void Character::characterMove(int direction)
{
	Vec2 newPos;


	switch (direction)
	{
		case 1:
			newPos = Vec2((characterArt->getPosition().x + 10) * factor.height, characterArt->getPosition().y);
			characterArt->setPosition(newPos);
			characterVision->setPosition(newPos);
			characterRunningRight->setPosition(newPos);
			characterRunningLeft->setPosition(newPos);
			break;

		case 2:
			newPos = Vec2((characterArt->getPosition().x - 10) * factor.height, characterArt->getPosition().y);
			characterArt->setPosition(newPos);
			characterVision->setPosition(newPos);
			characterRunningRight->setPosition(newPos);
			characterRunningLeft->setPosition(newPos);
			break;
	}
}

void Character::moveCam(int direction)
{
	Vec2 newPos;


	switch (direction)
	{
	case 1:
		newPos = Vec2((characterVision->getPosition().x + 15) * factor.height, characterVision->getPosition().y);
		characterVision->setPosition(newPos);
		break;

	case 2:
		newPos = Vec2((characterVision->getPosition().x - 15) * factor.height, characterVision->getPosition().y);
		characterVision->setPosition(newPos);
		break;
	}
}

void Character::createAnimation()
{
	int res;

	if (visibleSize.width >= 1920)				//CHECK RESOLUTION TO
		res = 1;								//SELECT THE SPRITE SHEET
	else if (visibleSize.width >= 1366)
		res = 2;
	else
		res = 3;

	char str[100] = { 0 };

	//INIKO RUNNING RIGHT

	sprintf(str, "images/Characters/SpriteSheets/Iniko/InikoRunningRight/InikoRunningRight%d.png", res);
	characterRunningRightspritebatch = SpriteBatchNode::create(str);
	SpriteFrameCache* characterRunningRightcache = SpriteFrameCache::getInstance();
	sprintf(str, "images/Characters/SpriteSheets/Iniko/InikoRunningRight/InikoRunningRight%d.plist", res);
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

	Animation* characterRunningRightanimation = Animation::createWithSpriteFrames(characterRunningRightanimFrames, 0.02f);
	characterRunningRight->runAction(RepeatForever::create(Animate::create(characterRunningRightanimation)));

	characterRunningRightCollider = PhysicsBody::createBox(Size((characterRunningRight->getContentSize().width) * factor.width, 313 * factor.height));
	characterRunningRightCollider->setContactTestBitmask(true);
	characterRunningRightCollider->setDynamic(true);
	characterRunningRightCollider->setCollisionBitmask(0);
	characterRunningRightCollider->setTag(0); //TAG 0 = CHARACTER

	characterRunningRight->setPhysicsBody(characterRunningRightCollider);

	//INIKO RUNNING LEFT

	sprintf(str, "images/Characters/SpriteSheets/Iniko/InikoRunningLeft/InikoRunningLeft%d.png", res);
	characterRunningLeftspritebatch = SpriteBatchNode::create(str);
	SpriteFrameCache* characterRunningLeftcache = SpriteFrameCache::getInstance();
	sprintf(str, "images/Characters/SpriteSheets/Iniko/InikoRunningLeft/InikoRunningLeft%d.plist", res);
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

	Animation* characterRunningLeftanimation = Animation::createWithSpriteFrames(characterRunningLeftanimFrames, 0.02f);
	characterRunningLeft->runAction(RepeatForever::create(Animate::create(characterRunningLeftanimation)));

	characterRunningLeftCollider = PhysicsBody::createBox(Size((characterRunningLeft->getContentSize().width) * factor.width, 313 * factor.height));
	characterRunningLeftCollider->setContactTestBitmask(true);
	characterRunningLeftCollider->setDynamic(true);
	characterRunningLeftCollider->setCollisionBitmask(0);
	characterRunningLeftCollider->setTag(0); //TAG 0 = CHARACTER

	characterRunningLeft->setPhysicsBody(characterRunningLeftCollider);
}