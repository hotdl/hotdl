#pragma once
#include "Constant.h"

class OptionScene : public CCLayer
{
public:
	virtual bool init();
	static CCScene* scene();
	void menuBackCallback(CCObject* pSender);
	void menuMusicCallback(CCObject* pSender);
	CREATE_FUNC(OptionScene);
};