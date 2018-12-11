#ifndef __GAME_LEVEL_H__
#define __GAME_LEVEL_H__

#include "cocos2d.h"
using namespace cocos2d;
class GameLevel : public cocos2d::Layer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	//static cocos2d::Scene* scene();

    // implement the "static node()" method manually
    CREATE_FUNC(GameLevel);

	void onTimeUp(float delta);

	//void onClickMenu(cocos2d::Ref* obj);

private:
	Label* labelLevel;
	Label* labelTargetScore;
};

#endif // __GAME_LEVEL_H__
