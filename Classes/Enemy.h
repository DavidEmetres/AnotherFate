#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"

USING_NS_CC;

class Enemy : public cocos2d::Layer
{
public:
	int posInitial;
	int posFinal;
	float waitingTime;
	int velocity;
	int type;
	int displacement;
	bool facingRight;
	bool die;

	Sprite* enemyArt;
	PhysicsBody* enemyCollider;

	Sprite* enemyVision;
	PhysicsBody* enemyVisionCollider;

	Sprite* detect;

	FiniteTimeAction* movement;
	CallFunc* callback;
	Sequence* sequence;

	void createAnimation(int type);
	void movementFinished();
	void enemyMovement();
	void detectCharacter();
	void moveVision();

	Enemy(int posInitial, int posFinal, float waitingTime, int velocity, int type);
};

#endif // __ENEMY_H__