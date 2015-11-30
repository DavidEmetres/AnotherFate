#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h"
#include "PowerUps.h"

USING_NS_CC;

class Character : public cocos2d::Layer
{
public:
	Size visibleSize;
	bool facingRight;
	Vec2 velocityDir;
	float velocity;
	bool stealth;
	bool hide;
	bool jumping;
	Node* wallTouch;
	char wallTouchSide;
	bool gameOver;

	Sprite* runningSoundColliderSprite;
	PhysicsBody* runningSoundCollider;

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
	
	Sprite* characterVision;

	Sprite* AKey;
	Sprite* SKey;

	void getHide(bool in);
	void createAnimation();
	void jump(Vec2 force, bool right);
	void die();

	Character();
};

#endif // __CHARACTER_H__