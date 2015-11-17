#include "Enemy.h"

USING_NS_CC;

Enemy::Enemy()
{
	enemyArt = Sprite::create("images/Characters/Enemy1/Enemy1.png");
	enemyArt->setPosition(Point(3000, (enemyArt->getContentSize().height / 2 + 80)));
	enemyCollider = PhysicsBody::createBox(Size(enemyArt->getContentSize().width, enemyArt->getContentSize().height));
	enemyCollider->setContactTestBitmask(true);
	enemyCollider->setDynamic(true);
	enemyCollider->setCollisionBitmask(0);

	enemyArt->setPhysicsBody(enemyCollider);

	detect = Sprite::create("images/Characters/Enemy1/GUI/Detect.png");
	detect->setPosition(Point(enemyArt->getPosition().x, enemyArt->getPosition().y + enemyArt->getContentSize().height/2 + detect->getContentSize().height/2));
	detect->setVisible(false);

	facingRight = true;

	movement = MoveBy::create(5, Vec2(1500, 0));

	callback = CallFunc::create([this]() 
	{
		this->movementFinished();
	});

	sequence = Sequence::create(movement, callback, NULL);

	enemyArt->runAction(sequence);
}

void Enemy::movementFinished()
{
	if (facingRight)
	{
		movement = MoveBy::create(5, Vec2(-1500, 0));;
		sequence = Sequence::create(DelayTime::create(2.0f), movement, callback, NULL);
		enemyArt->runAction(sequence);
	}

	else
	{
		movement = MoveBy::create(5, Vec2(1500, 0));
		sequence = Sequence::create(DelayTime::create(2.0f), movement, callback, NULL);
		enemyArt->runAction(sequence);
	}

	if (facingRight)
	{
		facingRight = false;
	}
	
	else
	{
		facingRight = true;
	}
}

void Enemy::detectCharacter()
{
	detect->setVisible(true);
}