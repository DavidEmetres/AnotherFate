#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"

USING_NS_CC;

class Item : public cocos2d::Layer
{
public:
	Size visibleSize;
	Size factor;

	Sprite* itemArt;
	int itemType;
	int posx;
	int posy;
	PhysicsBody* itemCollider;

	void createArt(int type);
	void getThrow();

	Item(int type, int posx, int posy);
};

#endif // __ITEM_H__