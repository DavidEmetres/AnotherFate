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

	Sprite* Floor1;
	PhysicsBody* FloorCollider1;

	Sprite* Floor1Modulo1;
	PhysicsBody* FloorCollider1Modulo1;
	Sprite* Floor2Modulo1;
	PhysicsBody* FloorCollider2Modulo1;
	Sprite* Floor3Modulo1;
	PhysicsBody* FloorCollider3Modulo1;
	Sprite* Floor4Modulo1;
	PhysicsBody* FloorCollider4Modulo1;
	Sprite* Floor5Modulo1;
	PhysicsBody* FloorCollider5Modulo1;
	Sprite* Floor6Modulo1;
	PhysicsBody* FloorCollider6Modulo1;
	Sprite* Floor7Modulo1;
	PhysicsBody* FloorCollider7Modulo1;
	Sprite* Floor8Modulo1;
	PhysicsBody* FloorCollider8Modulo1;
	Sprite* Floor9Modulo1;
	PhysicsBody* FloorCollider9Modulo1;
	Sprite* Floor10Modulo1;
	PhysicsBody* FloorCollider10Modulo1;
	Sprite* Floor11Modulo1;
	PhysicsBody* FloorCollider11Modulo1;
	Sprite* Floor12Modulo1;
	PhysicsBody* FloorCollider12Modulo1;

	Sprite* Wall0;
	PhysicsBody* Wall0Collider;

	Sprite* Wall1Modulo1;
	PhysicsBody* Wall1ColliderModulo1;
	Sprite* Wall2Modulo1;
	PhysicsBody* Wall2ColliderModulo1;
	Sprite* Wall3Modulo1;
	PhysicsBody* Wall3ColliderModulo1;

	Sprite* Portal1;
	CCParticleSystemQuad* portalParticles;

	Vector<Item*> objectsVector;

	Item* vasijaGrande1;

	Item* vasijaPequena1;

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