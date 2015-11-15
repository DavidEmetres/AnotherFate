#include "Item.h"

USING_NS_CC;

Item::Item(int type, int posx, int posy)
{
	visibleSize = Director::getInstance()->getVisibleSize();

	itemType = type;
	this->posx = posx;
	this->posy = posy;

	thrown = false;

	createArt(itemType);

	itemCollider = PhysicsBody::createBox(Size((itemArt->getContentSize().width), (itemArt->getContentSize().height)));
	itemCollider->setContactTestBitmask(true);
	itemCollider->setDynamic(true);
	itemCollider->setCollisionBitmask(0);

	itemArt->setPhysicsBody(itemCollider);
}

void Item::createArt(int type)
{
	switch (type)
	{
		case 2:							//VASIJA PEQUEÑA
			itemArt = Sprite::create("images/Level0/Assets/VasijaPequena.png");
			itemArt->setPosition(Point(posx, (posy + itemArt->getContentSize().height/2)));
			break;
	}
}

void Item::getThrow(bool direction)
{
	itemArt->setPosition(Point(itemArt->getPosition().x, itemArt->getPosition().y + 5));

	if (direction)
	{
		itemCollider->setVelocity(Vec2(600, 600));
		itemArt->runAction(RotateBy::create(2.0f, 360));
	}

	else
	{
		itemCollider->setVelocity(Vec2(-600, 600));
		itemArt->runAction(RotateBy::create(2.0f, -360));
	}

	thrown = true;
}