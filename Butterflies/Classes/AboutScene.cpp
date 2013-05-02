#include "AboutScene.h"

CCScene* AboutScene::scene()
{
	CCScene* scene = NULL;
	do 
	{
		scene = CCScene::create();
		CC_BREAK_IF(!scene);
		AboutScene* layer = AboutScene::create();
		CC_BREAK_IF(!layer);
		scene->addChild(layer);
	} while (0);
	return scene;
}

bool AboutScene::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());
		
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		
		CCSprite* aboutBg = CCSprite::create("images/about-bg.png");
		CC_BREAK_IF(!aboutBg);
		aboutBg->setPosition(ccp(size.width/2, size.height/2));
		this->addChild(aboutBg);

		CCMenuItemFont* back = CCMenuItemFont::create("Back", this, menu_selector(AboutScene::menuBackCallback));
		CCMenu* menu = CCMenu::create(back, NULL);
		menu->setPosition(ccp(size.width/2, 20));
		this->addChild(menu);

		bRet = true;
	} while (0);
	return bRet;
}

void AboutScene::menuBackCallback(CCObject* pSender)
{
	CCScene* scene = MainScene::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFadeTR::create(1.2f, scene));
}