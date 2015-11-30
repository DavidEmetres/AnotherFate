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
	int followPos;
	bool alertedEnemy;
	bool alertedSound;
	bool returning;
	bool stunned;

	Sprite* enemyArt;
	PhysicsBody* enemyCollider;

	Sprite* enemyVision;
	PhysicsBody* enemyVisionCollider;

	Sprite* detect;

	FiniteTimeAction* movement;
	FiniteTimeAction* following;
	CallFunc* callback;
	Sequence* sequence;
	Sequence* returnsequence;
	Sequence* recoverySequence;

	void createAnimation(int type);
	void movementFinished();
	void detectCharacter(float dt);
	void moveVision();
	void returned();
	void recovery();

	Enemy(int posInitial, int posFinal, float waitingTime, int velocity, int type);
};

#endif // __ENEMY_H__