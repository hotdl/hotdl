#include "GameScene.h"

bool GameScene::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		CCSize size = CCDirector::sharedDirector()->getWinSize();

		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(
			"images/images.plist",
			"images/images.png");
		CCTexture2D* texture = CCTextureCache::sharedTextureCache()->textureForKey("images/images.png");
		CCSpriteBatchNode* node = CCSpriteBatchNode::createWithTexture(texture);
		this->addChild(node, 2);

		CCSprite* playBg = CCSprite::createWithSpriteFrameName("background.png");
		playBg->setPosition(ccp(size.width/2, size.height/2));
		this->addChild(playBg, -1);

		CCSprite* header = CCSprite::createWithSpriteFrameName("header.png");
		CCSize headerSize = header->getContentSize();
		header->setScaleX(size.width/headerSize.width);
		header->setScaleY(size.height*2/(float)(ROW+2)/headerSize.height);
		header->setAnchorPoint(ccp(0, 0));
		header->setPosition(ccp(0, size.height*ROW/(ROW+2)));
		node->addChild(header);

		CCSprite* net = CCSprite::createWithSpriteFrameName("net.png");
		net->setScaleX(size.width/net->getContentSize().width);
		net->setScaleY((size.height/(float)(ROW+2))/net->getContentSize().height);
		net->setAnchorPoint(ccp(0, 0));
		net->setPosition(ccp(0, size.height*10/12.0));
		node->addChild(net);

		CCSprite* spider = CCSprite::createWithSpriteFrameName("spider.png");
		spider->setScaleX((size.width/(float)COL)/spider->getContentSize().width);
		spider->setScaleY((size.width/(float)(ROW+2))/spider->getContentSize().height);
		spider->setAnchorPoint(ccp(0, 0));
		spider->setPosition(ccp(0, size.height*10/12.0));
		node->addChild(spider);

		int x = playBg->getContentSize().width;
		int y = playBg->getContentSize().height;

		CCMenuItemImage* pause = CCMenuItemImage::create("images/btn-pause.png",
			"images/btn-pause.png", this, menu_selector(GameScene::menuPauseCallback));
		CCSize imageSize = pause->getContentSize();
		pause->setScaleX((size.width/(float)COL)/imageSize.width);
		pause->setScaleY((size.height/(float)(ROW+2))/imageSize.height);
		CCMenu* menu = CCMenu::create(pause, NULL);
		menu->setPosition(ccp(16, size.height-16));
		this->addChild(menu, 3);
		
		Board* board = Board::create();
		this->addChild(board, 1);

		bRet = true;
	} while (0);
	return bRet;
}

CCScene* GameScene::scene()
{
	CCScene* scene = NULL;
	do 
	{
		scene = CCScene::create();
		CC_BREAK_IF(!scene);
		GameScene* layer = GameScene::create();
		CC_BREAK_IF(!layer);
		scene->addChild(layer);
	} while (0);
	return scene;
}

void GameScene::menuPauseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();
}