#include "PowerUps.h"

USING_NS_CC;

PowerUps::PowerUps(int type)
{
	visibleSize = Director::getInstance()->getVisibleSize();

	this->type = type;
	activated = false;
	finish = false;
	rightDirection = false;
	initialPos = 0;

	createArt(type);
}

void PowerUps::createArt(int type)
{
	switch (type)
	{
		case 1:													//FLY POWER
			flyParticle = CCParticleSystemQuad::create("Particles/ParticlesFly/flyParticle.plist");
			flyParticle->setPositionType(kCCPositionTypeRelative);
			flyParticle->setScale(0.5);
			flyParticle->setVisible(false);
			flyParticleSmoke = CCParticleSystemQuad::create("Particles/ParticlesFly/flyParticleSmoke.plist");
			flyParticleSmoke->setPositionType(kCCPositionTypeRelative);
			flyParticleSmoke->setVisible(false);

			flyParticleCollider = PhysicsBody::createCircle(flyParticle->getContentSize().width/2);
			flyParticleCollider->setContactTestBitmask(true);
			flyParticleCollider->setDynamic(true);
			flyParticleCollider->setCollisionBitmask(0);
			flyParticleCollider->setGravityEnable(false);
			flyParticleCollider->setTag(4100);
			flyParticleCollider->setEnable(false);

			flyParticle->setPhysicsBody(flyParticleCollider);
			break;

		case 2:													//SHADOWS POWER
			shadowParticle = CCParticleSystemQuad::create("Particles/ShadowParticles/shadow_particle.plist");
			shadowParticle->setPositionType(kCCPositionTypeRelative);
			shadowParticle->setVisible(false);
			shadowParticle->setSpeed(300);
			shadowParticle->setGravity(Vec2(0, -300));
			shadowParticle->setLife(2);
			break;
	}
}

void PowerUps::ended(int waiting)
{
	CallFunc* callback = CallFunc::create([this]()
	{
		activated = false;
	});

	finish = true;
	endSequence = Sequence::create(DelayTime::create(waiting), callback, NULL);
	
	if (type == 1)
		flyParticle->runAction(endSequence);

	else if (type == 2)
		shadowParticle->runAction(endSequence);
}