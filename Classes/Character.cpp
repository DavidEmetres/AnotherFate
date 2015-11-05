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
			newPos = Vec2(characterArt->getPosition().x + 2, characterArt->getPosition().y);
			characterArt->setPosition(newPos);
			characterVision->setPosition(newPos);
			characterRunningRight->setPosition(newPos);
			break;

		case 2:
			newPos = Vec2(characterArt->getPosition().x - 2, characterArt->getPosition().y);
			characterArt->setPosition(newPos);
			characterVision->setPosition(newPos);
			characterRunningRight->setPosition(newPos);
			break;
	}
}

void Character::moveCam(int direction)
{
	Vec2 newPos;


	switch (direction)
	{
	case 1:
		newPos = Vec2(characterVision->getPosition().x + 5, characterVision->getPosition().y);
		characterVision->setPosition(newPos);
		break;

	case 2:
		newPos = Vec2(characterVision->getPosition().x - 5, characterVision->getPosition().y);
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

	sprintf(str, "images/Characters/SpriteSheets/Iniko/InikoRuning_Right%d.png", res);
	characterRunningRightspritebatch = SpriteBatchNode::create(str);
	SpriteFrameCache* characterRunningRightcache = SpriteFrameCache::getInstance();
	sprintf(str, "images/Characters/SpriteSheets/Iniko/InikoRuning_Right%d.plist", res);
	characterRunningRightcache->addSpriteFramesWithFile(str);

	characterRunningRight = Sprite::createWithSpriteFrameName("InikoRuning_Right1.png");
	characterRunningRightspritebatch->addChild(characterRunningRight);
	characterRunningRightspritebatch->setVisible(false);

	Vector<SpriteFrame*> characterRunningRightanimFrames(34);

	for (int i = 1; i <= 34; i++)
	{
		sprintf(str, "InikoRuning_Right%d.png", i);
		SpriteFrame* frame = characterRunningRightcache->getSpriteFrameByName(str);
		characterRunningRightanimFrames.pushBack(frame);
	}

	Animation* characterRunningRightanimation = Animation::createWithSpriteFrames(characterRunningRightanimFrames, 0.035f);
	characterRunningRight->runAction(RepeatForever::create(Animate::create(characterRunningRightanimation)));

	characterRunningRightCollider = PhysicsBody::createBox(Size((characterRunningRight->getContentSize().width) * factor.width, 313 * factor.height));
	characterRunningRightCollider->setContactTestBitmask(true);
	characterRunningRightCollider->setDynamic(true);
	characterRunningRightCollider->setCollisionBitmask(0);
	characterRunningRightCollider->setTag(0); //TAG 0 = CHARACTER

	characterRunningRight->setPhysicsBody(characterRunningRightCollider);
}