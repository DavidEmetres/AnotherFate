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
	followPos = 0;
	alertedEnemy = false;
	alertedSound = false;
	stunned = false;
	staticEnemy = false;
	stopped = false;

	returning = false;

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
	following = MoveBy::create(0, Vec2::ZERO);

	callback = CallFunc::create([this]() 
	{
		this->movementFinished();
	});

	if (!staticEnemy)
	{
		sequence = Sequence::create(movement, DelayTime::create(waitingTime), callback, NULL);
		returnsequence = Sequence::create(DelayTime::create(3), CallFunc::create(CC_CALLBACK_0(Enemy::returned, this)), NULL);
		recoverySequence = Sequence::create(DelayTime::create(5), CallFunc::create(CC_CALLBACK_0(Enemy::returned, this)), NULL);

		enemyArt->runAction(sequence);
		
		/*if (type == 1)
		{
			enemy1WalkingRight->runAction(sequence);
			enemy1WalkingLeft->runAction(sequence);
		}*/
	}
}

void Enemy::createAnimation(int type)
{
	int res;
	float factor = Director::getInstance()->getContentScaleFactor();

	if (factor >= 1)
		res = 1;
	else if (factor >= 0.71)
		res = 2;
	else
		res = 3;

	char str[100] = { 0 };

	if (type == 1)
	{
		enemyArt = Sprite::create("images/Characters/Enemy1/Enemy1.png");
		enemyArt->setPosition(Point(posInitial, enemyArt->getContentSize().height / 2 + 80));

		enemyCollider = PhysicsBody::createBox(Size(enemyArt->getContentSize().width, enemyArt->getContentSize().height));
		enemyCollider->setContactTestBitmask(true);
		enemyCollider->setDynamic(true);
		enemyCollider->setCollisionBitmask(0);

		enemyArt->setPhysicsBody(enemyCollider);

		//ENEMY 1 RIGHT WALK

		sprintf(str, "SpriteSheets/Characters/Enemy1/enemigo1_andar_right/enemigo_andar_right%d.png", res);
		enemy1WalkingRightspritebatch = SpriteBatchNode::create(str);
		SpriteFrameCache* enemy1WalkingRightcache = SpriteFrameCache::getInstance();
		sprintf(str, "SpriteSheets/Characters/Enemy1/enemigo1_andar_right/enemigo_andar_right%d.plist", res);
		enemy1WalkingRightcache->addSpriteFramesWithFile(str);

		enemy1WalkingRight = Sprite::createWithSpriteFrameName("Enemigo1_andar(derecha)_00001.png");
		enemy1WalkingRightspritebatch->addChild(enemy1WalkingRight);
		enemy1WalkingRightspritebatch->setVisible(true);

		Vector<SpriteFrame*> enemy1WalkingRightanimFrames(40);

		for (int i = 1; i <= 40; i++)
		{
			sprintf(str, "Enemigo1_andar(derecha)_%05d.png", i);
			SpriteFrame* frame = enemy1WalkingRightcache->getSpriteFrameByName(str);
			enemy1WalkingRightanimFrames.pushBack(frame);
		}

		Animation* enemy1WalkingRightanimation = Animation::createWithSpriteFrames(enemy1WalkingRightanimFrames, 0.05f);
		enemy1WalkingRight->runAction(RepeatForever::create(Animate::create(enemy1WalkingRightanimation)));

		//ENEMY 1 LEFT WALK

		sprintf(str, "SpriteSheets/Characters/Enemy1/enemigo1_andar_left/enemigo_andar_left%d.png", res);
		enemy1WalkingLeftspritebatch = SpriteBatchNode::create(str);
		SpriteFrameCache* enemy1WalkingLeftcache = SpriteFrameCache::getInstance();
		sprintf(str, "SpriteSheets/Characters/Enemy1/enemigo1_andar_left/enemigo_andar_left%d.plist", res);
		enemy1WalkingLeftcache->addSpriteFramesWithFile(str);

		enemy1WalkingLeft = Sprite::createWithSpriteFrameName("Enemigo1_andar_00001.png");
		enemy1WalkingLeftspritebatch->addChild(enemy1WalkingLeft);
		enemy1WalkingLeftspritebatch->setVisible(true);

		Vector<SpriteFrame*> enemy1WalkingLeftanimFrames(40);

		for (int i = 1; i <= 40; i++)
		{
			sprintf(str, "Enemigo1_andar_%05d.png", i);
			SpriteFrame* frame = enemy1WalkingLeftcache->getSpriteFrameByName(str);
			enemy1WalkingLeftanimFrames.pushBack(frame);
		}

		Animation* enemy1WalkingLeftanimation = Animation::createWithSpriteFrames(enemy1WalkingLeftanimFrames, 0.05f);
		enemy1WalkingLeft->runAction(RepeatForever::create(Animate::create(enemy1WalkingLeftanimation)));

		//ENEMY 1 RIGHT RUN

		sprintf(str, "SpriteSheets/Characters/Enemy1/enemigo1_correr_derecha/enemigo1_correr_right%d.png", res);
		enemy1RunningRightspritebatch = SpriteBatchNode::create(str);
		SpriteFrameCache* enemy1RunningRightcache = SpriteFrameCache::getInstance();
		sprintf(str, "SpriteSheets/Characters/enemy1/enemigo1_correr_derecha/enemigo1_correr_right%d.plist", res);
		enemy1RunningRightcache->addSpriteFramesWithFile(str);

		enemy1RunningRight = Sprite::createWithSpriteFrameName("Enemigo1_correr_derecha_00001.png");
		enemy1RunningRightspritebatch->addChild(enemy1RunningRight);
		enemy1RunningRightspritebatch->setVisible(true);

		Vector<SpriteFrame*> enemy1RunningRightanimFrames(40);

		for (int i = 1; i <= 40; i++)
		{
			sprintf(str, "Enemigo1_correr_derecha_%05d.png", i);
			SpriteFrame* frame = enemy1RunningRightcache->getSpriteFrameByName(str);
			enemy1RunningRightanimFrames.pushBack(frame);
		}

		Animation* enemy1RunningRightanimation = Animation::createWithSpriteFrames(enemy1RunningRightanimFrames, 0.02f);
		enemy1RunningRight->runAction(RepeatForever::create(Animate::create(enemy1RunningRightanimation)));

		//ENEMY 1 LEFT RUN

		sprintf(str, "SpriteSheets/Characters/Enemy1/enemigo1_correr_izquierda/enemigo1_correr_izquierda%d.png", res);
		enemy1RunningLeftspritebatch = SpriteBatchNode::create(str);
		SpriteFrameCache* enemy1RunningLeftcache = SpriteFrameCache::getInstance();
		sprintf(str, "SpriteSheets/Characters/Enemy1/enemigo1_correr_izquierda/enemigo1_correr_izquierda%d.plist", res);
		enemy1RunningLeftcache->addSpriteFramesWithFile(str);

		enemy1RunningLeft = Sprite::createWithSpriteFrameName("Enemigo1_correr_00001.png");
		enemy1RunningLeftspritebatch->addChild(enemy1RunningLeft);
		enemy1RunningLeftspritebatch->setVisible(true);

		Vector<SpriteFrame*> enemy1RunningLeftanimFrames(40);

		for (int i = 1; i <= 40; i++)
		{
			sprintf(str, "Enemigo1_correr_%05d.png", i);
			SpriteFrame* frame = enemy1RunningLeftcache->getSpriteFrameByName(str);
			enemy1RunningLeftanimFrames.pushBack(frame);
		}

		Animation* enemy1RunningLeftanimation = Animation::createWithSpriteFrames(enemy1RunningLeftanimFrames, 0.02f);
		enemy1RunningLeft->runAction(RepeatForever::create(Animate::create(enemy1RunningLeftanimation)));

		//ENEMY 1 MATAR FRENTE DERECHA

		sprintf(str, "SpriteSheets/Characters/Enemy1/enemigo1_matar_right/enemigo1_matar_right%d.png", res);
		enemy1KillFrontRightspritebatch = SpriteBatchNode::create(str);
		SpriteFrameCache* enemy1KillFrontRightcache = SpriteFrameCache::getInstance();
		sprintf(str, "SpriteSheets/Characters/Enemy1/enemigo1_matar_right/enemigo1_matar_right%d.plist", res);
		enemy1KillFrontRightcache->addSpriteFramesWithFile(str);

		enemy1KillFrontRight = Sprite::createWithSpriteFrameName("Enemigo1Asesino_00001.png");
		enemy1KillFrontRightspritebatch->addChild(enemy1KillFrontRight);
		enemy1KillFrontRightspritebatch->setVisible(true);

		Vector<SpriteFrame*> enemy1KillFrontRightanimFrames(80);

		for (int i = 1; i <= 80; i++)
		{
			auto str = StringUtils::format("Enemigo1Asesino_%05d.png", i);
			//sprintf(str, "Enemigo2Asesino_derecha_%05d.png", i);
			SpriteFrame* frame = enemy1KillFrontRightcache->getSpriteFrameByName(str);
			enemy1KillFrontRightanimFrames.pushBack(frame);
		}

		enemy1KillFrontRightanimation = Animation::createWithSpriteFrames(enemy1KillFrontRightanimFrames, 0.03f);
		enemy1KillFrontRight->runAction(Animate::create(enemy1KillFrontRightanimation));

		//ENEMY 1 MATAR FRENTE IZQUIERDA

		sprintf(str, "SpriteSheets/Characters/Enemy1/enemigo1_matar_izquierda/enemigo1_matar_left%d.png", res);
		enemy1KillFrontLeftspritebatch = SpriteBatchNode::create(str);
		SpriteFrameCache* enemy1KillFrontLeftcache = SpriteFrameCache::getInstance();
		sprintf(str, "SpriteSheets/Characters/Enemy1/enemigo1_matar_izquierda/enemigo1_matar_left%d.plist", res);
		enemy1KillFrontLeftcache->addSpriteFramesWithFile(str);

		enemy1KillFrontLeft = Sprite::createWithSpriteFrameName("Enemigo1Asesino_derecha_00001.png");
		enemy1KillFrontLeftspritebatch->addChild(enemy1KillFrontLeft);
		enemy1KillFrontLeftspritebatch->setVisible(true);

		Vector<SpriteFrame*> enemy1KillFrontLeftanimFrames(80);

		for (int i = 1; i <= 80; i++)
		{
			auto str = StringUtils::format("Enemigo1Asesino_derecha_%05d.png", i);
			//sprintf(str, "Enemigo2Asesino_%05d.png", i);
			SpriteFrame* frame = enemy1KillFrontLeftcache->getSpriteFrameByName(str);
			enemy1KillFrontLeftanimFrames.pushBack(frame);
		}

		enemy1KillFrontLeftanimation = Animation::createWithSpriteFrames(enemy1KillFrontLeftanimFrames, 0.03f);
		enemy1KillFrontLeft->runAction(Animate::create(enemy1KillFrontLeftanimation));

		//ENEMY 1 MUERTE DERECHA

		sprintf(str, "SpriteSheets/Characters/Enemy1/iniko_matar_1_right/iniko_matar_1_right%d.png", res);
		enemy1DeathRightspritebatch = SpriteBatchNode::create(str);
		SpriteFrameCache* enemy1DeathRightcache = SpriteFrameCache::getInstance();
		sprintf(str, "SpriteSheets/Characters/Enemy1/iniko_matar_1_right/iniko_matar_1_right%d.plist", res);
		enemy1DeathRightcache->addSpriteFramesWithFile(str);

		enemy1DeathRight = Sprite::createWithSpriteFrameName("InikoAsesina_00001.png");
		enemy1DeathRightspritebatch->addChild(enemy1DeathRight);
		enemy1DeathRightspritebatch->setVisible(true);

		Vector<SpriteFrame*> enemy1DeathRightanimFrames(60);

		for (int i = 1; i <= 60; i++)
		{
			auto str = StringUtils::format("InikoAsesina_%05d.png", i);
			//sprintf(str, "Enemigo2Asesino_%05d.png", i);
			SpriteFrame* frame = enemy1DeathRightcache->getSpriteFrameByName(str);
			enemy1DeathRightanimFrames.pushBack(frame);
		}

		enemy1DeathRightanimation = Animation::createWithSpriteFrames(enemy1DeathRightanimFrames, 0.03f);
		enemy1DeathRight->runAction(Animate::create(enemy1DeathRightanimation));

		//ENEMY 1 MUERTE IZQUIERDA

		sprintf(str, "SpriteSheets/Characters/Enemy1/iniko_matar_1_izquierda/iniko_matar_1_right%d.png", res);
		enemy1DeathLeftspritebatch = SpriteBatchNode::create(str);
		SpriteFrameCache* enemy1DeathLeftcache = SpriteFrameCache::getInstance();
		sprintf(str, "SpriteSheets/Characters/Enemy1/iniko_matar_1_izquierda/iniko_matar_1_right%d.plist", res);
		enemy1DeathLeftcache->addSpriteFramesWithFile(str);

		enemy1DeathLeft = Sprite::createWithSpriteFrameName("InikoAsesina_izquierda_00001.png");
		enemy1DeathLeftspritebatch->addChild(enemy1DeathLeft);
		enemy1DeathLeftspritebatch->setVisible(true);

		Vector<SpriteFrame*> enemy1DeathLeftanimFrames(60);

		for (int i = 1; i <= 60; i++)
		{
			auto str = StringUtils::format("InikoAsesina_izquierda_%05d.png", i);
			//sprintf(str, "Enemigo2Asesino_%05d.png", i);
			SpriteFrame* frame = enemy1DeathLeftcache->getSpriteFrameByName(str);
			enemy1DeathLeftanimFrames.pushBack(frame);
		}

		enemy1DeathLeftanimation = Animation::createWithSpriteFrames(enemy1DeathLeftanimFrames, 0.03f);
		enemy1DeathLeft->runAction(Animate::create(enemy1DeathLeftanimation));

		//ENEMY 1 MATAR ESPALDA DERECHA

		sprintf(str, "SpriteSheets/Characters/Enemy1/enemigo1_matar_detras_right/enemigo1_matar_detras_right%d.png", res);
		enemy1KillBackRightspritebatch = SpriteBatchNode::create(str);
		SpriteFrameCache* enemy1KillBackRightcache = SpriteFrameCache::getInstance();
		sprintf(str, "SpriteSheets/Characters/Enemy1/enemigo1_matar_detras_right/enemigo1_matar_detras_right%d.plist", res);
		enemy1KillBackRightcache->addSpriteFramesWithFile(str);

		enemy1KillBackRight = Sprite::createWithSpriteFrameName("Enemigo1Asesino_derecha_detras_00001.png");
		enemy1KillBackRightspritebatch->addChild(enemy1KillBackRight);
		enemy1KillBackRightspritebatch->setVisible(true);

		Vector<SpriteFrame*> enemy1KillBackRightanimFrames(80);

		for (int i = 1; i <= 80; i++)
		{
			auto str = StringUtils::format("Enemigo1Asesino_derecha_detras_%05d.png", i);
			//sprintf(str, "Enemigo2Asesino_derecha_detras_%05d.png", i);
			SpriteFrame* frame = enemy1KillBackRightcache->getSpriteFrameByName(str);
			enemy1KillBackRightanimFrames.pushBack(frame);
		}

		enemy1KillBackRightanimation = Animation::createWithSpriteFrames(enemy1KillBackRightanimFrames, 0.03f);
		enemy1KillBackRight->runAction(Animate::create(enemy1KillBackRightanimation));

		//ENEMY 1 MATAR ESPALDA IZQUIERDA

		sprintf(str, "SpriteSheets/Characters/Enemy1/enemigo1_matar_detras_left/enemigo1_matar_detras_left%d.png", res);
		enemy1KillBackLeftspritebatch = SpriteBatchNode::create(str);
		SpriteFrameCache* enemy1KillBackLeftcache = SpriteFrameCache::getInstance();
		sprintf(str, "SpriteSheets/Characters/Enemy1/enemigo1_matar_detras_left/enemigo1_matar_detras_left%d.plist", res);
		enemy1KillBackLeftcache->addSpriteFramesWithFile(str);

		enemy1KillBackLeft = Sprite::createWithSpriteFrameName("Enemigo1Asesino_detras_00001.png");
		enemy1KillBackLeftspritebatch->addChild(enemy1KillBackLeft);
		enemy1KillBackLeftspritebatch->setVisible(true);

		Vector<SpriteFrame*> enemy1KillBackLeftanimFrames(80);

		for (int i = 1; i <= 80; i++)
		{
			auto str = StringUtils::format("Enemigo1Asesino_detras_%05d.png", i);
			//sprintf(str, "Enemigo2Asesino_detras_%05d", i);
			SpriteFrame* frame = enemy1KillBackLeftcache->getSpriteFrameByName(str);
			enemy1KillBackLeftanimFrames.pushBack(frame);
		}

		enemy1KillBackLeftanimation = Animation::createWithSpriteFrames(enemy1KillBackLeftanimFrames, 0.03f);
		enemy1KillBackLeft->runAction(Animate::create(enemy1KillBackLeftanimation));

		//ENEMY 1 IDLE RIGHT

		sprintf(str, "SpriteSheets/Characters/Enemy1/enemigo1_trescuartos_derecha/enemigo1_trescuartos_right%d.png", res);
		enemy1IdleRightspritebatch = SpriteBatchNode::create(str);
		SpriteFrameCache* enemy1IdleRightcache = SpriteFrameCache::getInstance();
		sprintf(str, "SpriteSheets/Characters/Enemy1/enemigo1_trescuartos_derecha/enemigo1_trescuartos_right%d.plist", res);
		enemy1IdleRightcache->addSpriteFramesWithFile(str);

		enemy1IdleRight = Sprite::createWithSpriteFrameName("Enemigo1_trescuartos_derecha_00001.png");
		enemy1IdleRightspritebatch->addChild(enemy1IdleRight);
		enemy1IdleRightspritebatch->setVisible(true);

		Vector<SpriteFrame*> enemy1IdleRightanimFrames(40);

		for (int i = 1; i <= 40; i++)
		{
			auto str = StringUtils::format("Enemigo1_trescuartos_derecha_%05d.png", i);
			//sprintf(str, "Enemigo2Asesino_%05d.png", i);
			SpriteFrame* frame = enemy1IdleRightcache->getSpriteFrameByName(str);
			enemy1IdleRightanimFrames.pushBack(frame);
		}

		enemy1IdleRightanimation = Animation::createWithSpriteFrames(enemy1IdleRightanimFrames, 0.03f);
		enemy1IdleRight->runAction(RepeatForever::create(Animate::create(enemy1IdleRightanimation)));

		//ENEMY 1 IDLE LEFT

		sprintf(str, "SpriteSheets/Characters/Enemy1/enemigo1_trescuartos_izquierda/enemigo1_trescuartos_left%d.png", res);
		enemy1IdleLeftspritebatch = SpriteBatchNode::create(str);
		SpriteFrameCache* enemy1IdleLeftcache = SpriteFrameCache::getInstance();
		sprintf(str, "SpriteSheets/Characters/Enemy1/enemigo1_trescuartos_izquierda/enemigo1_trescuartos_left%d.plist", res);
		enemy1IdleLeftcache->addSpriteFramesWithFile(str);

		enemy1IdleLeft = Sprite::createWithSpriteFrameName("Enemigo1_trescuartos_izquierda_00001.png");
		enemy1IdleLeftspritebatch->addChild(enemy1IdleLeft);
		enemy1IdleLeftspritebatch->setVisible(true);

		Vector<SpriteFrame*> enemy1IdleLeftanimFrames(40);

		for (int i = 1; i <= 40; i++)
		{
			auto str = StringUtils::format("Enemigo1_trescuartos_izquierda_%05d.png", i);
			//sprintf(str, "Enemigo2Asesino_%05d.png", i);
			SpriteFrame* frame = enemy1IdleLeftcache->getSpriteFrameByName(str);
			enemy1IdleLeftanimFrames.pushBack(frame);
		}

		enemy1IdleLeftanimation = Animation::createWithSpriteFrames(enemy1IdleLeftanimFrames, 0.03f);
		enemy1IdleLeft->runAction(RepeatForever::create(Animate::create(enemy1IdleLeftanimation)));

		///////////////////////////////////
	}

	else if (type == 2)
	{
		enemyArt = Sprite::create("images/Characters/Enemy1/Enemy1.png");
		enemyArt->setPosition(Point(posInitial, enemyArt->getContentSize().height / 2 + 80));

		enemyCollider = PhysicsBody::createBox(Size(enemyArt->getContentSize().width, enemyArt->getContentSize().height));
		enemyCollider->setContactTestBitmask(true);
		enemyCollider->setDynamic(true);
		enemyCollider->setCollisionBitmask(0);

		enemyArt->setPhysicsBody(enemyCollider);

		//ENEMY 2 RIGHT WALK

		sprintf(str, "SpriteSheets/Characters/Enemy2/enemigo2_andar_right/enemigo2_andar_right%dplist.png", res);
		enemy2WalkingRightspritebatch = SpriteBatchNode::create(str);
		SpriteFrameCache* enemy2WalkingRightcache = SpriteFrameCache::getInstance();
		sprintf(str, "SpriteSheets/Characters/Enemy2/enemigo2_andar_right/enemigo2_andar_right%dplist.plist", res);
		enemy2WalkingRightcache->addSpriteFramesWithFile(str);

		enemy2WalkingRight = Sprite::createWithSpriteFrameName("Enemigo2_andar(derecha)_00001.png");
		enemy2WalkingRightspritebatch->addChild(enemy2WalkingRight);
		enemy2WalkingRightspritebatch->setVisible(true);

		Vector<SpriteFrame*> enemy2WalkingRightanimFrames(40);

		for (int i = 1; i <= 40; i++)
		{
			sprintf(str, "Enemigo2_andar(derecha)_%05d.png", i);
			SpriteFrame* frame = enemy2WalkingRightcache->getSpriteFrameByName(str);
			enemy2WalkingRightanimFrames.pushBack(frame);
		}

		Animation* enemy2WalkingRightanimation = Animation::createWithSpriteFrames(enemy2WalkingRightanimFrames, 0.05f);
		enemy2WalkingRight->runAction(RepeatForever::create(Animate::create(enemy2WalkingRightanimation)));

		//ENEMY 2 LEFT WALK

		sprintf(str, "SpriteSheets/Characters/Enemy2/enemigo2_andar_left/enemigo2_andar_left%d0.png", res);
		enemy2WalkingLeftspritebatch = SpriteBatchNode::create(str);
		SpriteFrameCache* enemy2WalkingLeftcache = SpriteFrameCache::getInstance();
		sprintf(str, "SpriteSheets/Characters/Enemy2/enemigo2_andar_left/enemigo2_andar_left%d0.plist", res);
		enemy2WalkingLeftcache->addSpriteFramesWithFile(str);

		enemy2WalkingLeft = Sprite::createWithSpriteFrameName("Enemigo2_andar_00001.png");
		enemy2WalkingLeftspritebatch->addChild(enemy2WalkingLeft);
		enemy2WalkingLeftspritebatch->setVisible(true);

		Vector<SpriteFrame*> enemy2WalkingLeftanimFrames(40);

		for (int i = 1; i <= 40; i++)
		{
			sprintf(str, "Enemigo2_andar_%05d.png", i);
			SpriteFrame* frame = enemy2WalkingLeftcache->getSpriteFrameByName(str);
			enemy2WalkingLeftanimFrames.pushBack(frame);
		}

		Animation* enemy2WalkingLeftanimation = Animation::createWithSpriteFrames(enemy2WalkingLeftanimFrames, 0.05f);
		enemy2WalkingLeft->runAction(RepeatForever::create(Animate::create(enemy2WalkingLeftanimation)));

		//ENEMY 2 RIGHT RUN

		sprintf(str, "SpriteSheets/Characters/Enemy2/enemigo2_correr_right/enemigo2_correr_right%dplist.png", res);
		enemy2RunningRightspritebatch = SpriteBatchNode::create(str);
		SpriteFrameCache* enemy2RunningRightcache = SpriteFrameCache::getInstance();
		sprintf(str, "SpriteSheets/Characters/Enemy2/enemigo2_correr_right/enemigo2_correr_right%dplist.plist", res);
		enemy2RunningRightcache->addSpriteFramesWithFile(str);

		enemy2RunningRight = Sprite::createWithSpriteFrameName("Enemigo2_correr_derecha_00001.png");
		enemy2RunningRightspritebatch->addChild(enemy2RunningRight);
		enemy2RunningRightspritebatch->setVisible(true);

		Vector<SpriteFrame*> enemy2RunningRightanimFrames(40);

		for (int i = 1; i <= 40; i++)
		{
			sprintf(str, "Enemigo2_correr_derecha_%05d.png", i);
			SpriteFrame* frame = enemy2RunningRightcache->getSpriteFrameByName(str);
			enemy2RunningRightanimFrames.pushBack(frame);
		}

		Animation* enemy2RunningRightanimation = Animation::createWithSpriteFrames(enemy2RunningRightanimFrames, 0.02f);
		enemy2RunningRight->runAction(RepeatForever::create(Animate::create(enemy2RunningRightanimation)));

		//ENEMY 2 LEFT RUN

		sprintf(str, "SpriteSheets/Characters/Enemy2/enemigo2_correr_left/enemigo2_correr_left%dplist.png", res);
		enemy2RunningLeftspritebatch = SpriteBatchNode::create(str);
		SpriteFrameCache* enemy2RunningLeftcache = SpriteFrameCache::getInstance();
		sprintf(str, "SpriteSheets/Characters/Enemy2/enemigo2_correr_left/enemigo2_correr_left%dplist.plist", res);
		enemy2RunningLeftcache->addSpriteFramesWithFile(str);

		enemy2RunningLeft = Sprite::createWithSpriteFrameName("Enemigo2_correr_00001.png");
		enemy2RunningLeftspritebatch->addChild(enemy2RunningLeft);
		enemy2RunningLeftspritebatch->setVisible(true);

		Vector<SpriteFrame*> enemy2RunningLeftanimFrames(40);

		for (int i = 1; i <= 40; i++)
		{
			sprintf(str, "Enemigo2_correr_%05d.png", i);
			SpriteFrame* frame = enemy2RunningLeftcache->getSpriteFrameByName(str);
			enemy2RunningLeftanimFrames.pushBack(frame);
		}

		Animation* enemy2RunningLeftanimation = Animation::createWithSpriteFrames(enemy2RunningLeftanimFrames, 0.02f);
		enemy2RunningLeft->runAction(RepeatForever::create(Animate::create(enemy2RunningLeftanimation)));

		//ENEMY 2 MATAR FRENTE DERECHA

		sprintf(str, "SpriteSheets/Characters/Enemy2/enemigo2_matar_right/enemigo2_matar_right%d.png", res);
		enemy2KillFrontRightspritebatch = SpriteBatchNode::create(str);
		SpriteFrameCache* enemy2KillFrontRightcache = SpriteFrameCache::getInstance();
		sprintf(str, "SpriteSheets/Characters/Enemy2/enemigo2_matar_right/enemigo2_matar_right%d.plist", res);
		enemy2KillFrontRightcache->addSpriteFramesWithFile(str);

		enemy2KillFrontRight = Sprite::createWithSpriteFrameName("Enemigo2Asesino_derecha_00001.png");
		enemy2KillFrontRightspritebatch->addChild(enemy2KillFrontRight);
		enemy2KillFrontRightspritebatch->setVisible(true);

		Vector<SpriteFrame*> enemy2KillFrontRightanimFrames(80);

		for (int i = 1; i <= 80; i++)
		{
			auto str = StringUtils::format("Enemigo2Asesino_derecha_%05d.png", i);
			//sprintf(str, "Enemigo2Asesino_derecha_%05d.png", i);
			SpriteFrame* frame = enemy2KillFrontRightcache->getSpriteFrameByName(str);
			enemy2KillFrontRightanimFrames.pushBack(frame);
		}

		enemy2KillFrontRightanimation = Animation::createWithSpriteFrames(enemy2KillFrontRightanimFrames, 0.03f);
		enemy2KillFrontRight->runAction(Animate::create(enemy2KillFrontRightanimation));

		//ENEMY 2 MATAR FRENTE IZQUIERDA

		sprintf(str, "SpriteSheets/Characters/Enemy2/enemigo2_matar_left/enemigo2_matar_left%d.png", res);
		enemy2KillFrontLeftspritebatch = SpriteBatchNode::create(str);
		SpriteFrameCache* enemy2KillFrontLeftcache = SpriteFrameCache::getInstance();
		sprintf(str, "SpriteSheets/Characters/Enemy2/enemigo2_matar_left/enemigo2_matar_left%d.plist", res);
		enemy2KillFrontLeftcache->addSpriteFramesWithFile(str);

		enemy2KillFrontLeft = Sprite::createWithSpriteFrameName("Enemigo2Asesino_00001.png");
		enemy2KillFrontLeftspritebatch->addChild(enemy2KillFrontLeft);
		enemy2KillFrontLeftspritebatch->setVisible(true);

		Vector<SpriteFrame*> enemy2KillFrontLeftanimFrames(80);

		for (int i = 1; i <= 80; i++)
		{
			auto str = StringUtils::format("Enemigo2Asesino_%05d.png", i);
			//sprintf(str, "Enemigo2Asesino_%05d.png", i);
			SpriteFrame* frame = enemy2KillFrontLeftcache->getSpriteFrameByName(str);
			enemy2KillFrontLeftanimFrames.pushBack(frame);
		}

		enemy2KillFrontLeftanimation = Animation::createWithSpriteFrames(enemy2KillFrontLeftanimFrames, 0.03f);
		enemy2KillFrontLeft->runAction(Animate::create(enemy2KillFrontLeftanimation));

		//ENEMY 2 MUERTE DERECHA

		sprintf(str, "SpriteSheets/Characters/Enemy2/iniko_matar_enemigo2_right/iniko_matar_derecha%d.png", res);
		enemy2DeathRightspritebatch = SpriteBatchNode::create(str);
		SpriteFrameCache* enemy2DeathRightcache = SpriteFrameCache::getInstance();
		sprintf(str, "SpriteSheets/Characters/Enemy2/iniko_matar_enemigo2_right/iniko_matar_derecha%d.plist", res);
		enemy2DeathRightcache->addSpriteFramesWithFile(str);

		enemy2DeathRight = Sprite::createWithSpriteFrameName("InikoAsesina2_00001.png");
		enemy2DeathRightspritebatch->addChild(enemy2DeathRight);
		enemy2DeathRightspritebatch->setVisible(true);

		Vector<SpriteFrame*> enemy2DeathRightanimFrames(60);

		for (int i = 1; i <= 60; i++)
		{
			auto str = StringUtils::format("InikoAsesina2_%05d.png", i);
			//sprintf(str, "Enemigo2Asesino_%05d.png", i);
			SpriteFrame* frame = enemy2DeathRightcache->getSpriteFrameByName(str);
			enemy2DeathRightanimFrames.pushBack(frame);
		}

		enemy2DeathRightanimation = Animation::createWithSpriteFrames(enemy2DeathRightanimFrames, 0.03f);
		enemy2DeathRight->runAction(Animate::create(enemy2DeathRightanimation));

		//ENEMY 2 MUERTE IZQUIERDA

		sprintf(str, "SpriteSheets/Characters/Enemy2/iniko_matar_enemigo2_left/iniko_matar_enemigo2_izquierda%d.png", res);
		enemy2DeathLeftspritebatch = SpriteBatchNode::create(str);
		SpriteFrameCache* enemy2DeathLeftcache = SpriteFrameCache::getInstance();
		sprintf(str, "SpriteSheets/Characters/Enemy2/iniko_matar_enemigo2_left/iniko_matar_enemigo2_izquierda%d.plist", res);
		enemy2DeathLeftcache->addSpriteFramesWithFile(str);

		enemy2DeathLeft = Sprite::createWithSpriteFrameName("InikoAsesina2_derecha_00001.png");
		enemy2DeathLeftspritebatch->addChild(enemy2DeathLeft);
		enemy2DeathLeftspritebatch->setVisible(true);

		Vector<SpriteFrame*> enemy2DeathLeftanimFrames(60);

		for (int i = 1; i <= 60; i++)
		{
			auto str = StringUtils::format("InikoAsesina2_derecha_%05d.png", i);
			//sprintf(str, "Enemigo2Asesino_%05d.png", i);
			SpriteFrame* frame = enemy2DeathLeftcache->getSpriteFrameByName(str);
			enemy2DeathLeftanimFrames.pushBack(frame);
		}

		enemy2DeathLeftanimation = Animation::createWithSpriteFrames(enemy2DeathLeftanimFrames, 0.03f);
		enemy2DeathLeft->runAction(Animate::create(enemy2DeathLeftanimation));

		//ENEMY 2 MATAR ESPALDA DERECHA

		sprintf(str, "SpriteSheets/Characters/Enemy2/enemigo2_matar_detras_derecha/enemigo2_matar_detras_right%d.png", res);
		enemy2KillBackRightspritebatch = SpriteBatchNode::create(str);
		SpriteFrameCache* enemy2KillBackRightcache = SpriteFrameCache::getInstance();
		sprintf(str, "SpriteSheets/Characters/Enemy2/enemigo2_matar_detras_derecha/enemigo2_matar_detras_right%d.plist", res);
		enemy2KillBackRightcache->addSpriteFramesWithFile(str);

		enemy2KillBackRight = Sprite::createWithSpriteFrameName("Enemigo2Asesino_derecha_detras_00001.png");
		enemy2KillBackRightspritebatch->addChild(enemy2KillBackRight);
		enemy2KillBackRightspritebatch->setVisible(true);

		Vector<SpriteFrame*> enemy2KillBackRightanimFrames(80);

		for (int i = 1; i <= 80; i++)
		{
			auto str = StringUtils::format("Enemigo2Asesino_derecha_detras_%05d.png", i);
			//sprintf(str, "Enemigo2Asesino_derecha_detras_%05d.png", i);
			SpriteFrame* frame = enemy2KillBackRightcache->getSpriteFrameByName(str);
			enemy2KillBackRightanimFrames.pushBack(frame);
		}

		enemy2KillBackRightanimation = Animation::createWithSpriteFrames(enemy2KillBackRightanimFrames, 0.03f);
		enemy2KillBackRight->runAction(Animate::create(enemy2KillBackRightanimation));

		//ENEMY 2 MATAR ESPALDA IZQUIERDA

		sprintf(str, "SpriteSheets/Characters/Enemy2/enemigo2_matar_detras_izquierda/enemigo2_matar_detras_left%d.png", res);
		enemy2KillBackLeftspritebatch = SpriteBatchNode::create(str);
		SpriteFrameCache* enemy2KillBackLeftcache = SpriteFrameCache::getInstance();
		sprintf(str, "SpriteSheets/Characters/Enemy2/enemigo2_matar_detras_izquierda/enemigo2_matar_detras_left%d.plist", res);
		enemy2KillBackLeftcache->addSpriteFramesWithFile(str);

		enemy2KillBackLeft = Sprite::createWithSpriteFrameName("Enemigo2Asesino_detras_00001.png");
		enemy2KillBackLeftspritebatch->addChild(enemy2KillBackLeft);
		enemy2KillBackLeftspritebatch->setVisible(true);

		Vector<SpriteFrame*> enemy2KillBackLeftanimFrames(80);

		for (int i = 1; i <= 80; i++)
		{
			auto str = StringUtils::format("Enemigo2Asesino_detras_%05d.png", i);
			//sprintf(str, "Enemigo2Asesino_detras_%05d", i);
			SpriteFrame* frame = enemy2KillBackLeftcache->getSpriteFrameByName(str);
			enemy2KillBackLeftanimFrames.pushBack(frame);
		}

		enemy2KillBackLeftanimation = Animation::createWithSpriteFrames(enemy2KillBackLeftanimFrames, 0.03f);
		enemy2KillBackLeft->runAction(Animate::create(enemy2KillBackLeftanimation));
		
		//ENEMY 2 IDLE RIGHT

		sprintf(str, "SpriteSheets/Characters/Enemy2/enemigo2_trescuartos_derecha/enemigo2_trescuartos_derecha%d.png", res);
		enemy2IdleRightspritebatch = SpriteBatchNode::create(str);
		SpriteFrameCache* enemy2IdleRightcache = SpriteFrameCache::getInstance();
		sprintf(str, "SpriteSheets/Characters/Enemy2/enemigo2_trescuartos_derecha/enemigo2_trescuartos_derecha%d.plist", res);
		enemy2IdleRightcache->addSpriteFramesWithFile(str);

		enemy2IdleRight = Sprite::createWithSpriteFrameName("Enemigo2_trescuartos_00001.png");
		enemy2IdleRightspritebatch->addChild(enemy2IdleRight);
		enemy2IdleRightspritebatch->setVisible(true);

		Vector<SpriteFrame*> enemy2IdleRightanimFrames(40);

		for (int i = 1; i <= 40; i++)
		{
			auto str = StringUtils::format("Enemigo2_trescuartos_%05d.png", i);
			//sprintf(str, "Enemigo2Asesino_%05d.png", i);
			SpriteFrame* frame = enemy2IdleRightcache->getSpriteFrameByName(str);
			enemy2IdleRightanimFrames.pushBack(frame);
		}

		enemy2IdleRightanimation = Animation::createWithSpriteFrames(enemy2IdleRightanimFrames, 0.03f);
		enemy2IdleRight->runAction(RepeatForever::create(Animate::create(enemy2IdleRightanimation)));

		//ENEMY 2 IDLE LEFT

		sprintf(str, "SpriteSheets/Characters/Enemy2/enemigo2_trescuartos_izquierda/enemigo2_trescuartos_left%d.png", res);
		enemy2IdleLeftspritebatch = SpriteBatchNode::create(str);
		SpriteFrameCache* enemy2IdleLeftcache = SpriteFrameCache::getInstance();
		sprintf(str, "SpriteSheets/Characters/Enemy2/enemigo2_trescuartos_izquierda/enemigo2_trescuartos_left%d.plist", res);
		enemy2IdleLeftcache->addSpriteFramesWithFile(str);

		enemy2IdleLeft = Sprite::createWithSpriteFrameName("Enemigo2trescuartos_izquierda_00001.png");
		enemy2IdleLeftspritebatch->addChild(enemy2IdleLeft);
		enemy2IdleLeftspritebatch->setVisible(true);

		Vector<SpriteFrame*> enemy2IdleLeftanimFrames(40);

		for (int i = 1; i <= 40; i++)
		{
			auto str = StringUtils::format("Enemigo2trescuartos_izquierda_%05d.png", i);
			//sprintf(str, "Enemigo2Asesino_%05d.png", i);
			SpriteFrame* frame = enemy2IdleLeftcache->getSpriteFrameByName(str);
			enemy2IdleLeftanimFrames.pushBack(frame);
		}

		enemy2IdleLeftanimation = Animation::createWithSpriteFrames(enemy2IdleLeftanimFrames, 0.03f);
		enemy2IdleLeft->runAction(RepeatForever::create(Animate::create(enemy2IdleLeftanimation)));

		///////////////////////////////////
	}

	detect = Sprite::create("images/Characters/Enemy1/GUI/Detect.png");
	detect->setPosition(Point(enemyArt->getPosition().x, enemyArt->getPosition().y + enemyArt->getContentSize().height / 2 + detect->getContentSize().height / 2));
	detect->setVisible(false);
}

void Enemy::movementFinished()
{
	if (!staticEnemy)
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
}

void Enemy::detectCharacter(float dt)
{
	if (returning)
	{
		if (enemyArt->getPosition().x >= (posInitial - 50) && enemyArt->getPosition().x <= (posInitial + 50))
		{
			enemyArt->setPosition(Vec2(posInitial, enemyArt->getPosition().y));
			returning = false;
			alertedEnemy = false;
			alertedSound = false;

			if ((posFinal - posInitial) > 0)
			{
				facingRight = true;
			}

			else
			{
				facingRight = false;
			}

			movement = MoveBy::create(velocity, Vec2(posFinal - posInitial, 0));

			callback = CallFunc::create([this]()
			{
				this->movementFinished();
			});

			sequence = Sequence::create(DelayTime::create(2), movement, DelayTime::create(waitingTime), callback, NULL);

			if (enemyArt->numberOfRunningActions() == 0)
			{
				enemyArt->runAction(sequence);
			}
		}

		else if (enemyArt->getPosition().x > (posInitial + 50))
		{
			facingRight = false;

			enemyArt->setPosition(enemyArt->getPosition().x - (500 * dt), enemyArt->getPosition().y);
		}

		else if (enemyArt->getPosition().x < (posInitial - 50))
		{
			facingRight = true;

			enemyArt->setPosition(enemyArt->getPosition().x + (500 * dt), enemyArt->getPosition().y);
		}
	}
	
	else if (enemyArt->getPosition().x >= (followPos - 50) && enemyArt->getPosition().x <= (followPos + 50))
	{
		alertedEnemy = false;
		alertedSound = false;

		if (enemyArt->numberOfRunningActions() == 0)
		{
			stopped = true;
			returnsequence = Sequence::create(DelayTime::create(3), CallFunc::create(CC_CALLBACK_0(Enemy::returned, this)), NULL);
			enemyArt->runAction(returnsequence);
		}
	}

	else if (enemyArt->getPosition().x > (followPos + 50))
	{
		facingRight = false;

		enemyArt->setPosition(enemyArt->getPosition().x - (900 * dt), enemyArt->getPosition().y);
	}

	else if (enemyArt->getPosition().x < (followPos - 50))
	{
		facingRight = true;

		enemyArt->setPosition(enemyArt->getPosition().x + (900 * dt), enemyArt->getPosition().y);
	}
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

void Enemy::returned()
{
	returning = true;
	enemyArt->stopAction(returnsequence);
}

void Enemy::recovery()
{
	CallFunc* recoverycallback = CallFunc::create([this]()
	{
		stunned = false;
		
		if(!die)
			enemyVision->setVisible(true);
		
		returning = true;
		enemyArt->stopAction(recoverySequence);
	});

	enemyArt->stopAction(sequence);
	recoverySequence = Sequence::create(DelayTime::create(3), recoverycallback, NULL);
	enemyArt->runAction(recoverySequence);
}

void Enemy::death()
{
	enemyArt->setVisible(false);
}