#include "ScoreScene.h"

CCScene* ScoreScene::scene()
{
	CCScene* scene = NULL;
	do 
	{
		scene = CCScene::create();
		CC_BREAK_IF(!scene);
		ScoreScene* layer = ScoreScene::create();
		CC_BREAK_IF(!layer);
		scene->addChild(layer);
	} while (0);
	return scene;
}

bool ScoreScene::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		CCSize size = CCDirector::sharedDirector()->getWinSize();

		CCSprite* scoreBg = CCSprite::create("images/background.png");
		CC_BREAK_IF(!scoreBg);
		scoreBg->setPosition(ccp(size.width/2, size.height/2));
		this->addChild(scoreBg);

		CCLabelTTF* title, *score1, *score2, *score3, *score4, *score5;
		title = CCLabelTTF::create("HIGH SCORES", "Arial", 24);
		score1 = CCLabelTTF::create("0", "Arial", 24);
		score2 = CCLabelTTF::create("0", "Arial", 24);
		score3 = CCLabelTTF::create("0", "Arial", 24);
		score4 = CCLabelTTF::create("0", "Arial", 24);
		score5 = CCLabelTTF::create("0", "Arial", 24);
		title->setPosition(ccp(size.width/2, size.height-40));
		score1->setPosition(ccp(size.width/2, size.height-120));
		score2->setPosition(ccp(size.width/2, size.height-170));
		score3->setPosition(ccp(size.width/2, size.height-220));
		score4->setPosition(ccp(size.width/2, size.height-260));
		score5->setPosition(ccp(size.width/2, size.height-300));
		this->addChild(title);
		this->addChild(score1);
		this->addChild(score2);
		this->addChild(score3);
		this->addChild(score4);
		this->addChild(score5);

		CCMenuItemFont* back = CCMenuItemFont::create("Back", this, menu_selector(ScoreScene::menuBackCallback));
		CC_BREAK_IF(!back);
		CCMenu* menu = CCMenu::create(back, NULL);
		CC_BREAK_IF(!menu);
		menu->setPosition(ccp(size.width/2, 20));
		this->addChild(menu);

		bRet = true;
	} while (0);
	return bRet;
}

void ScoreScene::menuBackCallback(CCObject* pSender)
{
	CCScene* scene = MainScene::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFadeTR::create(1.2f, scene));
}

