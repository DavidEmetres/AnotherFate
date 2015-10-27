#ifndef __LEVEL_0_H__
#define __LEVEL_0_H__

#include "cocos2d.h"

class Level0 : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	void createBackground();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Level0);
};

#endif // __LEVEL_0_H__