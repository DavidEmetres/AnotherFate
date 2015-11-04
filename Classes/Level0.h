#ifndef __LEVEL_0_H__
#define __LEVEL_0_H__

#include "cocos2d.h"
#include "Character.h"
#include "Item.h"

USING_NS_CC;

class Level0 : public cocos2d::Layer
{
private:
	PhysicsWorld *mWorld;

	EventKeyboard::KeyCode _pressedKey;

public:
	Size visibleSize;
	Size factor;

	Sprite* Layer0;
	Sprite* Layer1;
	Sprite* Layer2;
	Sprite* Layer3;
	Sprite* Floor;
	PhysicsBody* FloorCollider;
	Sprite* Layer4;
	
	Sprite* Portal1;

	Item* vasijaPequeña1;
	
	Character* Iniko;

	Action* cameraFollow;

	bool moveRight;
	bool moveLeft;
	bool moveCam;
	
	void update(float dt);
	void createBackground();
	void changeCameraFollow(Node* target);
	void fixPosition(Node* image, Node* floor);
	
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