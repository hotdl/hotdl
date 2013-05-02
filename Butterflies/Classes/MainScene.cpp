#include "MainScene.h"

CCScene* MainScene::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		MainScene *layer = MainScene::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
	bool bRet = false;
	do 
	{
		//////////////////////////////////////////////////////////////////////////
		// super init first
		//////////////////////////////////////////////////////////////////////////

		CC_BREAK_IF(! CCLayer::init());

		//////////////////////////////////////////////////////////////////////////
		// add your codes below...
		//////////////////////////////////////////////////////////////////////////

		// 1. Add a menu item with "X" image, which is clicked to quit the program.

		// Create a "close" menu item with close icon, it's an auto release object.
/*		CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
			"CloseNormal.png",
			"CloseSelected.png",
			this,
			menu_selector(GameScene::menuCloseCallback));
		CC_BREAK_IF(! pCloseItem);

		// Place the menu item bottom-right conner.
		pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));

		// Create a menu with the "close" menu item, it's an auto release object.
		CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
		pMenu->setPosition(CCPointZero);
		CC_BREAK_IF(! pMenu);

		// Add the menu to HelloWorld layer as a child layer.
		this->addChild(pMenu, 1);
*/
		// 2. Add a label shows "Hello World".

		// Create a label and initialize with string "Hello World".
/*		CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
		CC_BREAK_IF(! pLabel);

		// Get window size and place the label upper. 
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		pLabel->setPosition(ccp(size.width / 2, size.height - 50));

		// Add the label to HelloWorld layer as a child layer.
		this->addChild(pLabel, 1);
*/
		// 3. Add add a splash screen, show the cocos2d splash image.

		size = CCDirector::sharedDirector()->getWinSize();

		CCSprite* pSprite = CCSprite::create("images/background.png");
		CC_BREAK_IF(! pSprite);

		// Place the sprite on the center of the screen
		pSprite->setPosition(ccp(size.width/2, size.height/2));

		// Add the sprite to HelloWorld layer as a child layer.
		this->addChild(pSprite, 0);
		
		CCMenuItemFont* itemPlay = CCMenuItemFont::create("Play", this, menu_selector(MainScene::menuPlayCallback));
		CCMenuItemFont* itemOptions = CCMenuItemFont::create("Options", this, menu_selector(MainScene::menuOptionsCallback));
		CCMenuItemFont* itemScores = CCMenuItemFont::create("Scores", this, menu_selector(MainScene::menuScoresCallback));
		CCMenuItemFont* itemAbout = CCMenuItemFont::create("About", this, menu_selector(MainScene::menuAboutCallback));
		CCMenuItemFont* itemQuit = CCMenuItemFont::create("Quit", this, menu_selector(MainScene::menuCloseCallback));
		CCMenu* menu = CCMenu::create(itemPlay, itemOptions, itemScores, itemAbout, itemQuit, NULL);
		menu->alignItemsVerticallyWithPadding(20);
		this->addChild(menu, 1);

		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(
			"images/images.plist",
			"images/images.png");
		CCTexture2D* texture = CCTextureCache::sharedTextureCache()->textureForKey("images/images.png");
		node = CCSpriteBatchNode::createWithTexture(texture);
		this->addChild(node);

		this->schedule(schedule_selector(MainScene::update), 0.1f);

		bRet = true;
	} while (0);

	return bRet;
}

void MainScene::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();
}

void MainScene::menuPlayCallback(CCObject* pSender)
{
	CCScene* scene = GameScene::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFadeTR::create(1.2f, scene));
}

void MainScene::menuOptionsCallback(CCObject* pSender)
{
	CCScene* scene = OptionScene::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFadeTR::create(1.2f, scene));
}

void MainScene::menuScoresCallback(CCObject* pSender)
{
	CCScene* scene = ScoreScene::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFadeTR::create(1.2f, scene));
}

void MainScene::menuAboutCallback(CCObject* pSender)
{
	CCScene* scene = AboutScene::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFadeTR::create(1.2f, scene));
}

void MainScene::update(float dt)
{
	//srand((unsigned int)time(0));
	if(CCRANDOM_0_1() < 0.02)
	{
		int type = CCRANDOM_0_1()*7;
		std::string s = "0.png";
		s[0] = type+'0';
		Gem* gem = new Gem();
		CCSprite* sprt = CCSprite::createWithSpriteFrameName(s.c_str());
		int x = CCRANDOM_0_1()*size.width;
		int y = size.height+(size.height/(ROW+2))/2;
		float scale = CCRANDOM_0_1()*0.8+0.2;
		int speed = CCRANDOM_0_1()*5;
		sprt->setPosition(ccp(x, y));
		sprt->setScale(scale);
		node->addChild(sprt);
		gem->setSprite(sprt);
		gem->setType((GemType)type);
		gem->setSpeed(speed);
		fallingGems.push_back(gem);
	}
	
	for(int i = fallingGems.size()-1; i >= 0; i--)
	{
		Gem* gem = fallingGems.at(i);
		CCPoint pos = gem->getSprite()->getPosition();
		pos.y -= gem->getSpeed();
		gem->getSprite()->setPosition(pos);
		if(pos.y < -size.height/(ROW+2)/2)
		{
			node->removeChild(gem->getSprite(), true);
			vector<Gem*>::iterator it = fallingGems.begin()+i;
			fallingGems.erase(it);
		}
	}
}