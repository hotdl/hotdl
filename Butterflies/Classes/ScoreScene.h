#pragma once
#include "Constant.h"

class ScoreScene : public CCLayer
{
public:
	virtual bool init();
	static CCScene* scene();
	void menuBackCallback(CCObject* pSender);
	CREATE_FUNC(ScoreScene);
};