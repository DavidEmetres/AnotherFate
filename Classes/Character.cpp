#include "Character.h"

USING_NS_CC;

Character::Character()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	characterArt = Sprite::create("images/Characters/Iniko.png");
	characterArt->setPosition(Point(visibleSize.width / 2, characterArt->getContentSize().height / 2 + 90));

	characterCollider = PhysicsBody::createBox(Size(characterArt->getContentSize().width, characterArt->getContentSize().height));
	characterCollider->setContactTestBitmask(true);
	characterCollider->setDynamic(true);
	characterCollider->setCollisionBitmask(0);
	characterCollider->setTag(0); //TAG 0 = CHARACTER

	characterArt->setPhysicsBody(characterCollider);
}

void Character::characterMove(int direction)
{
	Vec2 newPos;


	switch (direction)
	{
		case 1:
			newPos = Vec2(characterArt->getPosition().x + 6, characterArt->getPosition().y);
			characterArt->setPosition(newPos);
			break;

		case 2:
			newPos = Vec2(characterArt->getPosition().x - 6, characterArt->getPosition().y);
			characterArt->setPosition(newPos);
			break;
	}
}