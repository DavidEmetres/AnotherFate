#include "Item.h"

USING_NS_CC;

Item::Item(int type)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	factor = Size(visibleSize.width / 1920, visibleSize.height / 1080);

	itemType = type;

	createArt(itemType);

	itemCollider = PhysicsBody::createBox(Size((itemArt->getContentSize().width) * factor.width, (itemArt->getContentSize().height) * factor.height));
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
			itemArt->setScaleX(factor.width);
			itemArt->setScaleY(factor.height);
			itemArt->setPosition(Point(1397 * factor.width, (90 + itemArt->getContentSize().height/2) * factor.height));
			break;
	}
}

void Item::getThrow()
{
	itemArt->setPosition(Point((itemArt->getPosition().x) * factor.width, (itemArt->getPosition().y + 5) * factor.height));
	itemCollider->setVelocity(Vec2(800, 600));
}