#include "ControlLayer.h"

ControlLayer::ControlLayer(void)
{
	scoreItem = nullptr;
	pPauseItem = nullptr;
}

ControlLayer::~ControlLayer(void)
{
}

bool ControlLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!Layer::init());

		auto winSize = Director::getInstance()->getWinSize();

		auto normalPause = Sprite::create("Play btn.png");
		auto pressedPause = Sprite::create("Pause btn.png");
		pPauseItem = MenuItemSprite::create(normalPause, pressedPause, CC_CALLBACK_1(ControlLayer::menuPauseCallback, this));
		pPauseItem->setPosition(Point(normalPause->getContentSize().width/2+10, 170));
        auto menuPause = Menu::create(pPauseItem, nullptr);
		menuPause->setPosition(Point::ZERO);
		this->addChild(menuPause,101);

		scoreItem = Label::createWithBMFont("font.fnt", "0");
		scoreItem->setColor(Color3B(143,146,147));
		scoreItem->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		scoreItem->setPosition(Point(pPauseItem->getPositionX()+normalPause->getContentSize().width/2+5, pPauseItem->getPositionY()));
		this->addChild(scoreItem);

		bRet = true;
	} while (0);

	return bRet;
}

void ControlLayer::menuPauseCallback(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button.mp3");
	if(!CCDirector::getInstance()->isPaused())
	{
		pPauseItem->setNormalImage(Sprite::create("Play btn.png"));
		pPauseItem->setSelectedImage(Sprite::create("Pause btn.png"));
		CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
		Director::getInstance()->pause();
		noTouchLayer = NoTouchLayer::create();
		this->addChild(noTouchLayer);
	}
	else
	{
		pPauseItem->setNormalImage(Sprite::create("Play btn.png"));
		pPauseItem->setSelectedImage(Sprite::create("Pause btn.png"));
		CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		Director::getInstance()->resume();
		this->removeChild(noTouchLayer,true);
	}
}

void ControlLayer::updateScore(int score)
{
	if (score>=0 && score<=MAX_SCORE)
	{
        Value strScore(score);
		scoreItem->setString(strScore.asString());
	}
}
