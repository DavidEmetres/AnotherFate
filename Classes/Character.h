#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h"

USING_NS_CC;

class Character : public cocos2d::Layer
{
public:
	Size visibleSize;
	Size factor;

	std::string res;

	Sprite* characterArt;
	Sprite* characterVision;
	PhysicsBody* characterCollider;

	void characterMove(int direction);
	void moveCam(int direction);

	Character();
};

#endif // __CHARACTER_H__