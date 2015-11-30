#include "Item.h"

USING_NS_CC;

Item::Item(int type, int posx, int posy)
{
	visibleSize = Director::getInstance()->getVisibleSize();

	itemType = type;
	this->posx = posx;
	this->posy = posy;
	force = Vec2::ZERO;
	right = true;

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
		case 2:																				//VASIJA PEQUEÑA
			itemArt = Sprite::create("images/Level0/Assets/VasijaPequena.png");
			itemArt->setPosition(Point(posx, (posy + itemArt->getContentSize().height/2)));

			itemSound = Sprite::create("images/Level0/Colliders/VasijaPequenaSound.png");
			itemSound->setPosition(Point(posx, (posy + itemArt->getContentSize().height / 2)));
			itemSound->setVisible(false);

			itemSoundCollider = PhysicsBody::createCircle(itemSound->getContentSize().width);
			itemSoundCollider->setContactTestBitmask(true);
			itemSoundCollider->setDynamic(true);
			itemSoundCollider->setCollisionBitmask(0);
			itemSoundCollider->setEnable(false);

			itemSound->setPhysicsBody(itemSoundCollider);
			break;

		case 3:																				//VASIJA GRANDE
			itemArt = Sprite::create("images/Level0/Assets/VasijaGrande.png");
			itemArt->setPosition(Point(posx, (posy + itemArt->getContentSize().height / 2)));
			break;

		case 4:																				//OBJETO SALTO
			itemArt = Sprite::create();
			itemArt->setPosition(Point(posx, posy));
			break;
	}
}

void Item::getThrow(bool direction, int force)
{
	itemArt->setPosition(Point(itemArt->getPosition().x, itemArt->getPosition().y + 5));

	if (direction)
	{
		itemCollider->setVelocity(Vec2(force, force));
		itemArt->runAction(RotateBy::create(4.0f, 720));
	}

	else
	{
		itemCollider->setVelocity(Vec2(-force, force));
		itemArt->runAction(RotateBy::create(4.0f, -720));
	}

	thrown = true;
}