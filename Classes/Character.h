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
	int initposx;
	int initposy;
	int checkpoint;
	int forceRet;
	Sprite* forceBarBorder;
	CCProgressTimer* forceBar;

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

	Sprite* characterStealthRight;
	PhysicsBody* characterStealthRightCollider;
	SpriteBatchNode* characterStealthRightspritebatch;

	Sprite* characterStealthLeft;
	PhysicsBody* characterStealthLeftCollider;
	SpriteBatchNode* characterStealthLeftspritebatch;
	
	Sprite* characterJumpingRight;
	PhysicsBody* characterJumpingRightCollider;

	Sprite* characterJumpingLeft;
	PhysicsBody* characterJumpingLeftCollider;

	Sprite* characterVision;

	Sprite* AKey;
	Sprite* SKey;

	void getHide(bool in);
	void createAnimation();
	void jump(Vec2 force, bool right);
	void die();

	Character(int level, int checkpoint);
};

#endif // __CHARACTER_H__