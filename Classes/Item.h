#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"

USING_NS_CC;

class Item : public cocos2d::Layer
{
public:
	Size visibleSize;

	int itemType;
	int posx;
	int posy;
	Vec2 force;
	bool right;

	Sprite* itemArt;
	PhysicsBody* itemCollider;

	bool thrown;

	void createArt(int type);
	void getThrow(bool direction, int force);

	Item(int type, int posx, int posy);
};

#endif // __ITEM_H__