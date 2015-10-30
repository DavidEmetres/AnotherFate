#ifndef __LEVEL_0_H__
#define __LEVEL_0_H__

#include "cocos2d.h"

USING_NS_CC;

class Level0 : public cocos2d::Layer
{
private:
	EventKeyboard::KeyCode _pressedKey;

public:
	Sprite *Layer0;
	Sprite *Layer1;
	Sprite *Layer2;
	Sprite *Layer3;
	Sprite *Layer4;
	Sprite *Iniko;
	
	bool moveRight;
	bool moveLeft;
	
	void update(float dt);
	void createBackground();
	void backgroundMove(int direction);
	void characterMove(int direction);
	
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);
	
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Level0);
};

#endif // __LEVEL_0_H__