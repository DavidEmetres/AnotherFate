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
	bool staticEnemy;
	bool stopped;

	Sprite* enemyArt;
	PhysicsBody* enemyCollider;

	Sprite* enemy1WalkingRight;
	PhysicsBody* enemy1WalkingRightCollider;
	SpriteBatchNode* enemy1WalkingRightspritebatch;

	Sprite* enemy1WalkingLeft;
	PhysicsBody* enemy1WalkingLeftCollider;
	SpriteBatchNode* enemy1WalkingLeftspritebatch;

	Sprite* enemy1RunningRight;
	PhysicsBody* enemy1RunningRightCollider;
	SpriteBatchNode* enemy1RunningRightspritebatch;

	Sprite* enemy1RunningLeft;
	PhysicsBody* enemy1RunningLeftCollider;
	SpriteBatchNode* enemy1RunningLeftspritebatch;

	Sprite* enemy1KillFrontRight;
	PhysicsBody* enemy1KillFrontRightCollider;
	SpriteBatchNode* enemy1KillFrontRightspritebatch;
	Animation* enemy1KillFrontRightanimation;

	Sprite* enemy1KillFrontLeft;
	PhysicsBody* enemy1KillFrontLeftCollider;
	SpriteBatchNode* enemy1KillFrontLeftspritebatch;
	Animation* enemy1KillFrontLeftanimation;

	Sprite* enemy1KillBackRight;
	PhysicsBody* enemy1KillBackRightCollider;
	SpriteBatchNode* enemy1KillBackRightspritebatch;
	Animation* enemy1KillBackRightanimation;

	Sprite* enemy1KillBackLeft;
	PhysicsBody* enemy1KillBackLeftCollider;
	SpriteBatchNode* enemy1KillBackLeftspritebatch;
	Animation* enemy1KillBackLeftanimation;

	Sprite* enemy1DeathLeft;
	PhysicsBody* enemy1DeathLeftCollider;
	SpriteBatchNode* enemy1DeathLeftspritebatch;
	Animation* enemy1DeathLeftanimation;

	Sprite* enemy1DeathRight;
	PhysicsBody* enemy1DeathRightCollider;
	SpriteBatchNode* enemy1DeathRightspritebatch;
	Animation* enemy1DeathRightanimation;

	Sprite* enemy1IdleRight;
	PhysicsBody* enemy1IdleRightCollider;
	SpriteBatchNode* enemy1IdleRightspritebatch;
	Animation* enemy1IdleRightanimation;

	Sprite* enemy1IdleLeft;
	PhysicsBody* enemy1IdleLeftCollider;
	SpriteBatchNode* enemy1IdleLeftspritebatch;
	Animation* enemy1IdleLeftanimation;

	//////////////////////////////////////////////

	Sprite* enemy2WalkingRight;
	PhysicsBody* enemy2WalkingRightCollider;
	SpriteBatchNode* enemy2WalkingRightspritebatch;

	Sprite* enemy2WalkingLeft;
	PhysicsBody* enemy2WalkingLeftCollider;
	SpriteBatchNode* enemy2WalkingLeftspritebatch;

	Sprite* enemy2RunningRight;
	PhysicsBody* enemy2RunningRightCollider;
	SpriteBatchNode* enemy2RunningRightspritebatch;

	Sprite* enemy2RunningLeft;
	PhysicsBody* enemy2RunningLeftCollider;
	SpriteBatchNode* enemy2RunningLeftspritebatch;

	Sprite* enemy2KillFrontRight;
	PhysicsBody* enemy2KillFrontRightCollider;
	SpriteBatchNode* enemy2KillFrontRightspritebatch;
	Animation* enemy2KillFrontRightanimation;

	Sprite* enemy2KillFrontLeft;
	PhysicsBody* enemy2KillFrontLeftCollider;
	SpriteBatchNode* enemy2KillFrontLeftspritebatch;
	Animation* enemy2KillFrontLeftanimation;

	Sprite* enemy2KillBackRight;
	PhysicsBody* enemy2KillBackRightCollider;
	SpriteBatchNode* enemy2KillBackRightspritebatch;
	Animation* enemy2KillBackRightanimation;

	Sprite* enemy2KillBackLeft;
	PhysicsBody* enemy2KillBackLeftCollider;
	SpriteBatchNode* enemy2KillBackLeftspritebatch;
	Animation* enemy2KillBackLeftanimation;

	Sprite* enemy2DeathLeft;
	PhysicsBody* enemy2DeathLeftCollider;
	SpriteBatchNode* enemy2DeathLeftspritebatch;
	Animation* enemy2DeathLeftanimation;

	Sprite* enemy2DeathRight;
	PhysicsBody* enemy2DeathRightCollider;
	SpriteBatchNode* enemy2DeathRightspritebatch;
	Animation* enemy2DeathRightanimation;

	Sprite* enemy2IdleRight;
	PhysicsBody* enemy2IdleRightCollider;
	SpriteBatchNode* enemy2IdleRightspritebatch;
	Animation* enemy2IdleRightanimation;

	Sprite* enemy2IdleLeft;
	PhysicsBody* enemy2IdleLeftCollider;
	SpriteBatchNode* enemy2IdleLeftspritebatch;
	Animation* enemy2IdleLeftanimation;

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

	void death();

	Enemy(int posInitial, int posFinal, float waitingTime, int velocity, int type);
};

#endif // __ENEMY_H__