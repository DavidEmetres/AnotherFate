#include "Character.h"

USING_NS_CC;

Character::Character()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	factor = Size(visibleSize.width / 1920, visibleSize.height / 1080);

	characterArt = Sprite::create("images/Characters/Iniko.png");
	characterArt->setScaleX(factor.width);
	characterArt->setScaleY(factor.height);
	characterArt->setPosition(Point(visibleSize.width / 2, characterArt->getContentSize().height / 2 + 90 * factor.height));

	characterCollider = PhysicsBody::createBox(Size((characterArt->getContentSize().width) * factor.width, (characterArt->getContentSize().height) * factor.height));
	characterCollider->setContactTestBitmask(true);
	characterCollider->setDynamic(true);
	characterCollider->setCollisionBitmask(0);
	characterCollider->setTag(0); //TAG 0 = CHARACTER

	characterArt->setPhysicsBody(characterCollider);

	characterVision = Sprite::create("images/Level0/Assets/VasijaPequena.png");
	characterVision->setScaleX(factor.width);
	characterVision->setScaleY(factor.height);
	characterVision->setPosition(Point(visibleSize.width / 2, characterArt->getContentSize().height / 2 + 90 * factor.height));
}

void Character::characterMove(int direction)
{
	Vec2 newPos;


	switch (direction)
	{
		case 1:
			newPos = Vec2(characterArt->getPosition().x + 6, characterArt->getPosition().y);
			characterArt->setPosition(newPos);
			characterVision->setPosition(newPos);
			break;

		case 2:
			newPos = Vec2(characterArt->getPosition().x - 6, characterArt->getPosition().y);
			characterArt->setPosition(newPos);
			characterVision->setPosition(newPos);
			break;
	}
}

void Character::moveCam(int direction)
{
	Vec2 newPos;


	switch (direction)
	{
	case 1:
		newPos = Vec2(characterVision->getPosition().x + 6, characterVision->getPosition().y);
		characterVision->setPosition(newPos);
		break;

	case 2:
		newPos = Vec2(characterVision->getPosition().x - 6, characterVision->getPosition().y);
		characterVision->setPosition(newPos);
		break;
	}
}