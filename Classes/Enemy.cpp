#include "Enemy.h"

USING_NS_CC;

Enemy::Enemy(int posInitial, int posFinal, float waitingTime, int velocity, int type)
{
	this->posInitial = posInitial;
	this->posFinal = posFinal;
	this->waitingTime = waitingTime;
	this->velocity = velocity;
	this->type = type;

	if ((posFinal - posInitial) > 0)
	{
		facingRight = true;
		displacement = posFinal - posInitial;
	}

	else
	{
		facingRight = false;
		displacement = posInitial - posFinal;
	}

	die = false;

	createAnimation(type);

	//CREATE COLLIDERS
	//TAGS-> 10:ENEMY; 11:ENEMY VISION; 12:ENEMY KILL COLLIDER;

	enemyVision = Sprite::create("images/Characters/Enemy1/Colliders/Enemy1Vision.png");
	enemyVision->setPosition(Point(enemyArt->getContentSize().width/2 + enemyVision->getContentSize().width/2, enemyArt->getPosition().y));

	enemyVisionCollider = PhysicsBody::createBox(Size(enemyVision->getContentSize().width, enemyVision->getContentSize().height));
	enemyVisionCollider->setContactTestBitmask(true);
	enemyVisionCollider->setDynamic(true);
	enemyVisionCollider->setCollisionBitmask(0);

	enemyVision->setPhysicsBody(enemyVisionCollider);

	//CREATE MOVEMENT SEQUENCE

	movement = MoveBy::create(velocity, Vec2(posFinal - posInitial, 0));

	callback = CallFunc::create([this]() 
	{
		this->movementFinished();
	});

	sequence = Sequence::create(movement, DelayTime::create(waitingTime), callback, NULL);

	enemyArt->runAction(sequence);
}

void Enemy::createAnimation(int type)
{
	switch (type)
	{
		case 1:
			enemyArt = Sprite::create("images/Characters/Enemy1/Enemy1.png");
			enemyArt->setPosition(Point(posInitial, enemyArt->getContentSize().height / 2 + 80));

			enemyCollider = PhysicsBody::createBox(Size(enemyArt->getContentSize().width, enemyArt->getContentSize().height));
			enemyCollider->setContactTestBitmask(true);
			enemyCollider->setDynamic(true);
			enemyCollider->setCollisionBitmask(0);

			enemyArt->setPhysicsBody(enemyCollider);
			break;
	}

	detect = Sprite::create("images/Characters/Enemy1/GUI/Detect.png");
	detect->setPosition(Point(enemyArt->getPosition().x, enemyArt->getPosition().y + enemyArt->getContentSize().height / 2 + detect->getContentSize().height / 2));
	detect->setVisible(false);
}

void Enemy::movementFinished()
{
	if (facingRight)
	{
		movement = MoveBy::create(velocity, Vec2(-(displacement), 0));
		sequence = Sequence::create(movement, DelayTime::create(waitingTime), callback, NULL);
		facingRight = false;
		enemyArt->runAction(sequence);
	}

	else
	{
		movement = MoveBy::create(velocity, Vec2(displacement, 0));
		sequence = Sequence::create(movement, DelayTime::create(waitingTime), callback, NULL);
		facingRight = true;
		enemyArt->runAction(sequence);
	}
}

void Enemy::detectCharacter()
{
	detect->setVisible(true);
}

void Enemy::moveVision()
{
	if (facingRight)
	{
		enemyVision->setPosition(Point(enemyArt->getPosition().x + (enemyArt->getContentSize().width / 2 + enemyVision->getContentSize().width / 2), enemyArt->getPosition().y));
	}

	else
	{
		enemyVision->setPosition(Point(enemyArt->getPosition().x - (enemyArt->getContentSize().width / 2 + enemyVision->getContentSize().width / 2), enemyArt->getPosition().y));
	}
}