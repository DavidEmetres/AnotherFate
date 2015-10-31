#include "Character.h"

USING_NS_CC;

Character::Character()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	characterArt = Sprite::create("images/Characters/Iniko.png");
	characterArt->setPosition(Point(visibleSize.width / 2, characterArt->getContentSize().height / 2 + 85));

	characterCollider = PhysicsBody::createCircle(characterArt->getContentSize().width / 2);
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
		case 1:		//MOVE RIGHT
			newPos = Vec2(characterArt->getPosition().x + 6, characterArt->getPosition().y);
			characterArt->setPosition(newPos);
			break;

		case 2:		//MOVE LEFT
			newPos = Vec2(characterArt->getPosition().x - 6, characterArt->getPosition().y);
			characterArt->setPosition(newPos);
			break;
	}
}