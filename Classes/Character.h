#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h"

USING_NS_CC;

class Character : public cocos2d::Layer
{
public:
	Size visibleSize;
	bool facingRight;
	Vec2 velocityDir;
	float velocity;
	bool visionCollideRight;
	bool visionCollideLeft;
	bool stealth;
	bool hide;

	Sprite* runningSoundColliderSprite;
	PhysicsBody* runningSoundCollider;

	Sprite* visionColliderSpriteLeft;
	PhysicsBody* visionColliderLeft;

	Sprite* visionColliderSpriteRight;
	PhysicsBody* visionColliderRight;

	Sprite* characterVision;
	PhysicsBody* characterVisionCollider;

	Sprite* characterIdleRight;
	PhysicsBody* characterIdleRightCollider;
	SpriteBatchNode* characterIdlerightspritebatch;

	Sprite* characterIdleLeft;
	PhysicsBody* characterIdleLeftCollider;
	SpriteBatchNode* characterIdleleftspritebatch;

	Sprite* characterRunningRight;
	PhysicsBody* characterRunningRightCollider;
	SpriteBatchNode* characterRunningRightspritebatch;

	Sprite* characterRunningLeft;
	PhysicsBody* characterRunningLeftCollider;
	SpriteBatchNode* characterRunningLeftspritebatch;
	
	Sprite* AKey;

	void characterMove(int direction, float deltaTime);
	void moveCam(int direction, float deltaTime);
	void getHide(bool in);
	void createAnimation();

	Character();
};

#endif // __CHARACTER_H__