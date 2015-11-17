#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"

USING_NS_CC;

class Enemy : public cocos2d::Layer
{
public:
	bool facingRight;

	Sprite* enemyArt;
	PhysicsBody* enemyCollider;

	Sprite* detect;

	FiniteTimeAction* movement;
	CallFunc* callback;
	Sequence* sequence;

	void movementFinished();
	void enemyMovement();
	void detectCharacter();

	Enemy();
};

#endif // __ENEMY_H__