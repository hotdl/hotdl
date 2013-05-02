#pragma once
#include "Constant.h"

using namespace cocos2d;

class AboutScene : public CCLayer
{
public:
	virtual bool init();
	static CCScene* scene();
	void menuBackCallback(CCObject* pSender);
	CREATE_FUNC(AboutScene);
};