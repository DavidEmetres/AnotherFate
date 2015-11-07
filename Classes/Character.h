#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h"

USING_NS_CC;

class Character : public cocos2d::Layer
{
public:
	Size visibleSize;
	Size factor;

	Sprite* characterArt;
	PhysicsBody* characterCollider;

	Sprite* characterRunningRight;
	PhysicsBody* characterRunningRightCollider;
	SpriteBatchNode* characterRunningRightspritebatch;

	Sprite* characterRunningLeft;
	PhysicsBody* characterRunningLeftCollider;
	SpriteBatchNode* characterRunningLeftspritebatch;

	Sprite* characterVision;
	Sprite* AKey;

	void characterMove(int direction);
	void moveCam(int direction);
	void createAnimation();

	Character();
};

#endif // __CHARACTER_H__