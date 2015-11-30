#ifndef __POWER_UPS_H__
#define __POWER_UPS_H__

#include "cocos2d.h"

USING_NS_CC;

class PowerUps : public cocos2d::Layer
{
public:
	Size visibleSize;

	int type;
	bool activated;
	bool finish;
	bool rightDirection;
	int initialPos;

	CCParticleSystem* flyParticle;
	CCParticleSystem* flyParticleSmoke;
	PhysicsBody* flyParticleCollider;

	CCParticleSystem* shadowParticle;

	Sequence* endSequence;

	void createArt(int type);
	void ended(int waiting);

	PowerUps(int type);
};

#endif // __POWER_UPS_H__