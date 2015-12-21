#ifndef __Egypt_H__
#define __Egypt_H__

#include "cocos2d.h"
#include "Character.h"
#include "Item.h"
#include "Enemy.h"
#include "PowerUps.h"
#include "GameOver.h"

USING_NS_CC;

class Egypt : public cocos2d::Layer
{
private:
	PhysicsWorld *mWorld;

	EventKeyboard::KeyCode _pressedKey;

public:
	Size visibleSize;

	CCParallaxNode* backgroundNode;

	Sprite* Layer0;
	Sprite* Layer1;
	Sprite* Layer2;
	Sprite* Layer3;
	Sprite* Layer4;
	Sprite* Layer51;
	Sprite* Layer52;
	Sprite* Layer53;
	Sprite* Layer54;
	Sprite* Layer61;
	Sprite* Layer62;
	Sprite* Layer64;
	Sprite* Layer63;
	Sprite* Layer72;
	Sprite* Layer73;

	Sprite* barco1;
	PhysicsBody* barco1Collider;
	Sprite* barco2;
	PhysicsBody* barco2Collider;

	Sprite* Floor1;
	PhysicsBody* FloorCollider1;
	Sprite* Floor2;
	PhysicsBody* FloorCollider2;
	Sprite* Floor3;
	PhysicsBody* FloorCollider3;

	Sprite* Floor1Modulo1;
	PhysicsBody* FloorCollider1Modulo1;
	Sprite* Floor2Modulo1;
	PhysicsBody* FloorCollider2Modulo1;

	Sprite* Floor1Modulo2;
	PhysicsBody* FloorCollider1Modulo2;
	Sprite* Floor2Modulo2;
	PhysicsBody* FloorCollider2Modulo2;
	Sprite* Floor3Modulo2;
	PhysicsBody* FloorCollider3Modulo2;
	Sprite* Floor4Modulo2;
	PhysicsBody* FloorCollider4Modulo2;
	Sprite* Floor5Modulo2;
	PhysicsBody* FloorCollider5Modulo2;
	Sprite* Floor6Modulo2;
	PhysicsBody* FloorCollider6Modulo2;
	Sprite* Floor7Modulo2;
	PhysicsBody* FloorCollider7Modulo2;
	Sprite* Floor8Modulo2;
	PhysicsBody* FloorCollider8Modulo2;
	Sprite* Floor9Modulo2;
	PhysicsBody* FloorCollider9Modulo2;
	Sprite* Floor10Modulo2;
	PhysicsBody* FloorCollider10Modulo2;
	Sprite* Floor11Modulo2;
	PhysicsBody* FloorCollider11Modulo2;
	Sprite* Floor12Modulo2;
	PhysicsBody* FloorCollider12Modulo2;
	Sprite* Floor13Modulo2;
	PhysicsBody* Floor13ColliderModulo2;

	Sprite* Floor1Modulo3;
	PhysicsBody* Floor1ColliderModulo3;
	Sprite* Floor2Modulo3;
	PhysicsBody* Floor2ColliderModulo3;
	Sprite* Floor3Modulo3;
	PhysicsBody* Floor3ColliderModulo3;
	Sprite* Floor4Modulo3;
	PhysicsBody* Floor4ColliderModulo3;
	Sprite* Floor5Modulo3;
	PhysicsBody* Floor5ColliderModulo3;
	Sprite* Floor6Modulo3;
	PhysicsBody* Floor6ColliderModulo3;
	Sprite* Floor7Modulo3;
	PhysicsBody* Floor7ColliderModulo3;
	Sprite* Floor8Modulo3;
	PhysicsBody* Floor8ColliderModulo3;
	Sprite* Floor9Modulo3;
	PhysicsBody* Floor9ColliderModulo3;
	Sprite* Floor10Modulo3;
	PhysicsBody* Floor10ColliderModulo3;
	Sprite* Floor11Modulo3;
	PhysicsBody* Floor11ColliderModulo3;
	Sprite* Floor12Modulo3;
	PhysicsBody* Floor12ColliderModulo3;
	Sprite* Floor13Modulo3;
	PhysicsBody* Floor13ColliderModulo3;

	Sprite* Floor1Modulo4;
	PhysicsBody* Floor1ColliderModulo4;

	Sprite* Wall0;
	PhysicsBody* Wall0Collider;
	Sprite* Wall1;
	PhysicsBody* Wall1Collider;
	Sprite* Wall2;
	PhysicsBody* Wall2Collider;
	Sprite* Wall3;
	PhysicsBody* Wall3Collider;

	Sprite* Wall1Modulo2;
	PhysicsBody* Wall1ColliderModulo2;
	Sprite* Wall2Modulo2;
	PhysicsBody* Wall2ColliderModulo2;
	Sprite* Wall3Modulo2;
	PhysicsBody* Wall3ColliderModulo2;

	Sprite* Wall1Modulo4;
	PhysicsBody* Wall1ColliderModulo4;

	Sprite* Portal1;
	CCParticleSystemQuad* portalParticles;

	CCParticleSystemQuad* fireParticle1;
	CCParticleSystemQuad* fireParticle2;
	CCParticleSystemQuad* fireParticle3;
	CCParticleSystemQuad* fireParticle4;
	CCParticleSystemQuad* fireParticle5;
	CCParticleSystemQuad* fireParticle6;

	Vector<Item*> objectsVector;

	Item* vasijaGrande1;
	Item* vasijaGrande2;

	Item* vasijaPequena1;
	Item* vasijaPequena2;
	Item* vasijaPequena3;
	Item* vasijaPequena4;
	Item* vasijaPequena5;
	Item* vasijaPequena6;

	Item* jumpZone1;
	Item* jumpZone2;
	Item* jumpZone3;
	Item* jumpZone4;
	Item* jumpZone5;
	Item* jumpZone6;
	Item* jumpZone7;
	Item* jumpZone8;
	Item* jumpZone9;
	Item* jumpZone10;
	Item* jumpZone11;

	Character* Iniko;

	Vector<Enemy*> enemysVector;
	Vector<Enemy*> enemysFollowing;

	Enemy* enemy1;
	Enemy* enemy2;
	Enemy* enemy3;
	Enemy* enemy4;
	Enemy* enemy5;
	Enemy* enemy6;
	Enemy* enemy7;

	Node* followObject;

	PowerUps* power1;
	PowerUps* power2;

	Action* cameraFollow;
	Action* keyAction;
	CCCallFunc* actionCall;

	bool moveRight;
	bool moveLeft;
	bool moveCam;
	char key;
	int AKeyCounter;
	float deltaTime;
	int tag;

	PhysicsBody* contactBody;
	PhysicsBody* contactFloor;
	PhysicsBody* contactEnemy;

	bool ready;

	void update(float dt);
	void createBackground();
	void createAnimations();
	void keyNull();
	void objectBehaviour(PhysicsBody* body, int phase);
	void gameOver();
	void enemyDeath(int tg);
	void inikoStopsKill();
	void enemyDying();

	void setPhysicsWorld(PhysicsWorld *world);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);
	bool onContactBegin(PhysicsContact &contact);
	bool onContactSeparate(PhysicsContact &contact);

	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(Egypt);
};

#endif // __Egypt_H__