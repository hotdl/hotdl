#pragma once
#include "Constant.h"

using namespace cocos2d;

class GameScene : public CCLayer
{
public:
	virtual bool init();
	static CCScene* scene();
	void menuPauseCallback(CCObject* pSender);
	CREATE_FUNC(GameScene);
};