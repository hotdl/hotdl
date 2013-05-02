#include "OptionScene.h"

CCScene* OptionScene::scene()
{
	CCScene* scene = NULL;
	do 
	{
		scene = CCScene::create();
		CC_BREAK_IF(!scene);
		OptionScene* layer = OptionScene::create();
		CC_BREAK_IF(!layer);
		scene->addChild(layer);
	} while (0);
	return scene;
}

bool OptionScene::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::create());

		CCSize size = CCDirector::sharedDirector()->getWinSize();

		CCSprite* optionBg = CCSprite::create("images/background.png");
		CC_BREAK_IF(!optionBg);
		optionBg->setPosition(ccp(size.width/2, size.height/2));
		this->addChild(optionBg);

		CCLabelTTF* title = CCLabelTTF::create("Music", "Arial", 36);
		title->setPosition(ccp(size.width/2, size.height/2+50));
		this->addChild(title);

		CCMenuItemToggle* music = CCMenuItemToggle::createWithTarget(this, 
			menu_selector(OptionScene::menuMusicCallback), 
			CCMenuItemFont::create("On"),
			CCMenuItemFont::create("Off"), 
			NULL);
		CCMenu* m_menu = CCMenu::create(music, NULL);
		this->addChild(m_menu);

		CCMenuItemFont* back = CCMenuItemFont::create("Back", this, menu_selector(OptionScene::menuBackCallback));
		CCMenu* b_menu = CCMenu::create(back, NULL);
		b_menu->setPosition(ccp(size.width/2, 20));
		this->addChild(b_menu);

		bRet = true;
	} while (0);
	return bRet;
}

void OptionScene::menuBackCallback(CCObject* pSender)
{
	CCScene* scene = MainScene::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFadeTR::create(1.2f, scene));
}

void OptionScene::menuMusicCallback(CCObject* pSender)
{
	
}