#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"

USING_NS_CC;

class Item : public cocos2d::Layer
{
public:
	Size visibleSize;

	Sprite* itemArt;
	int itemType;
	int posx;
	int posy;
	PhysicsBody* itemCollider;

	bool thrown;

	void createArt(int type);
	void getThrow(bool direction);

	Item(int type, int posx, int posy);
};

#endif // __ITEM_H__