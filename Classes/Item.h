#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"

USING_NS_CC;

class Item : public cocos2d::Layer
{
public:
	Sprite* itemArt;
	int itemType;
	PhysicsBody* itemCollider;

	void createArt(int type);
	void getThrow();

	Item(int type);
};

#endif // __ITEM_H__