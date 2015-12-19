#ifndef __GAME_OVER_H__
#define __GAME_OVER_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Level0.h"
#include "Egypt.h"

USING_NS_CC;

class GameOver : public cocos2d::Layer
{
private:
	EventKeyboard::KeyCode _pressedKey;

public:
	Size visibleSize;

	int level;
	int checkpoint;
	int option;

	Sprite* background;
	Sprite* cursor;
	Label* text1;
	Label* text2;

	void update(float dt);
	void goToLevel0(Ref *pSender);
	void goToLevelEgipt(Ref *pSender, int checkpoint);

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);

	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(GameOver);
};

#endif // __GAME_OVER_H__