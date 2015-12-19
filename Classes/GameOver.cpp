#include "AppDelegate.h"
#include "GameOver.h"

USING_NS_CC;

Scene* GameOver::createScene()
{
	auto scene = Scene::create();

	auto layer = GameOver::create();

	scene->addChild(layer);

	return scene;
}

bool GameOver::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//INITIALIZE ATRIBUTES

	visibleSize = Director::getInstance()->getVisibleSize();

	//level = this->getTag() / 10;
	//checkpoint = this->getTag() - level * 10;
	level = 1;
	checkpoint = 0;

	//TEXT

	text1 = Label::createWithSystemFont("Restart checkpoint", "Pixelade", 72);
	text1->setColor(Color3B(255, 255, 255));
	text1->setPosition(visibleSize.width/2, 470);
	addChild(text1, 2);

	text2 = Label::createWithSystemFont("Return to level selection", "Pixelade", 72);
	text2->setColor(Color3B(255, 255, 255));
	text2->setPosition(visibleSize.width / 2, 290);
	addChild(text2, 2);

	//BACKGROUND

	background = Sprite::create("images/GameOver/Background.png");
	background->setPosition(background->getContentSize().width / 2, background->getContentSize().height / 2);
	addChild(background, 1);

	//CURSOR

	cursor = Sprite::create("images/GameOver/Cursor.png");
	cursor->setPosition(400, 470);
	addChild(cursor, 2);

	option = 1;

	//SOUNDS

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/Click.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/Transition.mp3");

	//INITIALIZE UPDATE FUNCTION

	this->scheduleUpdate();

	//CREATE KEY INPUTS LISTENERS

	auto listener = EventListenerKeyboard::create();

	listener->onKeyPressed = CC_CALLBACK_2(GameOver::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(GameOver::onKeyReleased, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void GameOver::update(float dt)
{
	switch (option)
	{
		case 1:
			text1->setScale(1.1);
			cursor->setPosition(text1->getPosition().x - text1->getContentSize().width / 2 - 170, 470);
			text2->setScale(1);
			text2->setOpacity(120);
			text1->setOpacity(255);
			break;

		case 2:
			text2->setScale(1.1);
			cursor->setPosition(text2->getPosition().x - text2->getContentSize().width / 2 - 180, 290);
			text1->setScale(1);
			text1->setOpacity(120);
			text2->setOpacity(255);
			break;
	}
}

void GameOver::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event)
{
	_pressedKey = keyCode;

	switch (_pressedKey)
	{
		case EventKeyboard::KeyCode::KEY_KP_ENTER:
			switch (option)
			{
				case 1:
					switch (level)
					{
						case 1:
							CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/Transition.mp3");
							goToLevelEgipt(this, checkpoint);
							break;
					}
					break;

				case 2:
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/Transition.mp3");
					goToLevel0(this);
					break;
			}
			break;

		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			if (option == 2)
			{
				option = 1;
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/Click.mp3");
			}
			break;

		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			if (option == 1)
			{
				option = 2;
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/Click.mp3");
			}
			break;
	}
}

void GameOver::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event)
{
	switch (keyCode)
	{
		case EventKeyboard::KeyCode::KEY_ENTER:
			_pressedKey = EventKeyboard::KeyCode::KEY_NONE;
			break;

		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			_pressedKey = EventKeyboard::KeyCode::KEY_NONE;
			break;

		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			_pressedKey = EventKeyboard::KeyCode::KEY_NONE;
			break;
	}
}

void GameOver::goToLevel0(Ref *pSender)
{
	auto scene = Level0::createScene();
	Director::getInstance()->replaceScene(scene);
}

void GameOver::goToLevelEgipt(Ref *pSender, int checkpoint)
{
	auto scene = Egypt::createScene();
	scene->setTag(checkpoint);
	Director::getInstance()->replaceScene(scene);
}