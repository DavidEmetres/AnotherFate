#ifndef __LEVEL_0_H__
#define __LEVEL_0_H__

#include "cocos2d.h"
#include "Character.h"
#include "Item.h"
#include "Enemy.h"
#include "PowerUps.h"
#include "Egipt.h"

USING_NS_CC;

class Level0 : public cocos2d::Layer
{
private:
	PhysicsWorld *mWorld;

	EventKeyboard::KeyCode _pressedKey;

public:
	Size visibleSize;

	Sprite* Layer0;
	Sprite* Layer1;
	Sprite* Layer2;
	Sprite* Layer3;
	Sprite* Layer4;

	Sprite* Floor;
	PhysicsBody* FloorCollider;
	Sprite* Wall0;
	PhysicsBody* WallCollider0;
	Sprite* Wall1;
	PhysicsBody* WallCollider1;
	Sprite* Wall2;
	PhysicsBody* WallCollider2;
	Sprite* Wall3;
	PhysicsBody* WallCollider3;
	Sprite* DrinkMachineColliderSprite;
	PhysicsBody* DrinkMachineCollider;
	
	CCParticleSystemQuad* portalParticles;
	CCParticleSystemQuad* portalRayParticles;

	Sprite* loadingScreen;

	Vector<Item*> objectsVector;

	Item* vasijaPequeña1;
	Item* vasijaPequeña2;
	Item* vasijaGrande1;
	Item* jumpZone1;
	Item* portal1;
	
	Character* Iniko;

	Vector<Enemy*> enemysVector;
	Vector<Enemy*> enemysFollowing;

	Enemy* enemy1;
	Enemy* enemy2;

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

	PhysicsBody* contactBody;
	PhysicsBody* contactFloor;
	PhysicsBody* contactEnemy;

	void update(float dt);
	void createBackground();
	void createAnimations();
	void keyNull();
	void objectBehaviour(PhysicsBody* body, int phase);
	void EnterPortal();
	void goToLevelEgipt(Ref *pSender);

	void setPhysicsWorld(PhysicsWorld *world);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);
	bool onContactBegin(PhysicsContact &contact);
	bool onContactSeparate(PhysicsContact &contact);
	
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(Level0);
};

#endif // __LEVEL_0_H__