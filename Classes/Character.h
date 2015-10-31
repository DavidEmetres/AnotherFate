#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h"

USING_NS_CC;

class Character : public cocos2d::Layer
{
public:
	Sprite* characterArt;
	PhysicsBody* characterCollider;

	void characterMove(int direction);

	Character();
};

#endif // __CHARACTER_H__