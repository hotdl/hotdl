#pragma once
#include "Constant.h"

class Gem;

using namespace::cocos2d;

class MainScene : public CCLayer
{
public:
	virtual bool init();

	static CCScene* scene();

	void menuCloseCallback(CCObject* pSender);
	void menuPlayCallback(CCObject* pSender);
	void menuOptionsCallback(CCObject* pSender);
	void menuScoresCallback(CCObject* pSender);
	void menuAboutCallback(CCObject* pSender);

	void update(float dt);
	CREATE_FUNC(MainScene);

private:
	CCSpriteBatchNode* node;
	CCSize size;
	std::vector<Gem*> fallingGems;
};