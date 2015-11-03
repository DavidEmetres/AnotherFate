#include "Item.h"

USING_NS_CC;

Item::Item(int type)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	itemType = type;

	createArt(itemType);

	itemCollider = PhysicsBody::createBox(Size(itemArt->getContentSize().width, itemArt->getContentSize().height));
	itemCollider->setContactTestBitmask(true);
	itemCollider->setDynamic(true);
	itemCollider->setCollisionBitmask(0);
	itemCollider->setTag(itemType); //TAG 2 = LAUNCHABLE ITEM

	itemArt->setPhysicsBody(itemCollider);
}

void Item::createArt(int type)
{
	switch (type)
	{
		case 2:							//VASIJA PEQUEÑA
			itemArt = Sprite::create("images/Level0/Assets/VasijaPequena.png");
			itemArt->setPosition(Point(1397, 90 + itemArt->getContentSize().height/2));
			break;
	}
}

void Item::getThrow()
{
	itemArt->setPosition(Point(itemArt->getPosition().x, itemArt->getPosition().y + 5));
	itemCollider->setVelocity(Vec2(500, 500));
}