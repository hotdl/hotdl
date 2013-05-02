#include "Board.h"

bool Board::init()
{
	bool bRet = false;
	do 
	{
		selected = false;
		this->setTouchEnabled(true);
		size = CCDirector::sharedDirector()->getWinSize();

		gemSize.width = size.width/COL;
		gemSize.height = size.height/(ROW+2);
		numTotalGems = COL*ROW;
		numGemInCol = new int[COL];
		timeSinceAddInCol = new int[COL];
		landInCol = new int[COL];
		for(int i = 0; i < COL; i++)
		{
			numGemInCol[i] = 0;
			timeSinceAddInCol[i] = 0;
			landInCol[i] = 0;
		}
		fallingGems = new Gem*[numTotalGems];
		for(int i = 0; i < numTotalGems; i++)
		{
			fallingGems[i] = NULL;
		}
		fallingIndex = 0;
		isFalling = false;
		finishRemoval = false;

		//初始化batchNode
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(
			"images/images.plist",
			"images/images.png");
		CCTexture2D* texture = CCTextureCache::sharedTextureCache()->textureForKey("images/images.png");
		node = CCSpriteBatchNode::createWithTexture(texture);
		this->addChild(node);

		int x = size.width;
		int y = size.height;

		//加入mark精灵，初始化不显示
		mark = CCSprite::create("images/hint.png");
		mark->setAnchorPoint(ccp(0, 0));
		mark->setPosition(ccp(0, 0));
		mark->setScaleX((size.width)/(COL*mark->getContentSize().width));
		mark->setScaleY((size.height)/((ROW+2)*mark->getContentSize().height));
		mark->setTag(SELECTED);
		mark->setVisible(false);
		this->addChild(mark);

		//初始化board,生成Gems
		createGems();

		this->schedule(schedule_selector(Board::update), 0.1f);

		bRet = true;
	} while (0);
	return bRet;
}

CCScene* Board::scene()
{
	CCScene* scene = NULL;
	do 
	{
		scene = CCScene::create();
		CC_BREAK_IF(!scene);
		Board* layer = Board::create();
		CC_BREAK_IF(!layer);
		scene->addChild(layer);
	} while (0);
	return scene;
}

void Board::onEnter()
{
	CCDirector* director = CCDirector::sharedDirector();
	director->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	CCLayer::onEnter();
}

void Board::onExit()
{
	CCDirector* director = CCDirector::sharedDirector();
	director->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}

bool Board::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
	if(isFalling)
		return false;
	CCPoint pos = pTouch->getLocation();
	if(pos.y > size.height*10.0/12.0)
		return false;

	if(selected)
	{
		if(isNeighbor(getGemByPosition(select), getGemByPosition(pos)))
		{
			swapTwoGems(getGemByPosition(select), getGemByPosition(pos));
		}
		int x = floor(pos.x/gemSize.width)*gemSize.width;
		int y = floor(pos.y/gemSize.height)*gemSize.height;
		mark->setPosition(ccp(x, y));
		mark->setVisible(true);
		select = pos;
		return true;
	}
	else
	{
		int x = floor(pos.x/gemSize.width)*gemSize.width;
		int y = floor(pos.y/gemSize.height)*gemSize.height;
		mark->setPosition(ccp(x, y));
		mark->setVisible(true);
		selected = true;
		select = pos;
		return true;
	}
	
}

/*
void Board::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent)
{
	CCPoint startPos = pTouch->getStartLocation();
	Gem* gem = getGemByPosition(startPos);
	gem->setAnchorPoint(ccp(0.5, 0.5));
	mark->setAnchorPoint(ccp(0.5, 0.5));
	gem->setPosition(pTouch->getLocation());
	mark->setPosition(pTouch->getLocation());
	
}*/

void Board::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent)
{/*
	CCPoint upPos = pTouch->getLocation();
	CCPoint downPos = pTouch->getStartLocation();
	if(!(upPos.y > size.height*10.0/12.0))
	{
		Gem*& gem1 = getGemByPosition(downPos);
		Gem*& gem2 = getGemByPosition(upPos);
		if(isNeighbor(gem1, gem2))
		{
			swapTwoGems(gem1, gem2);
			Gem* gem = getGemByPosition(upPos);		
			mark->setPosition(gem->getSprite()->getPosition());
			mark->setVisible(true);
			select = upPos;
		}
	}*/
}

Gem*& Board::getGemByPosition(const CCPoint& pos)
{
	int col = pos.x*COL/size.width;
	int row = pos.y*(ROW+2)/size.height;
	return boardGems.at(row*COL+col);
}

bool Board::isNeighbor(Gem* gem1, Gem* gem2)
{
	if(gem1 == NULL || gem2 == NULL)
		return false;
	CCPoint pos1 = gem1->getSprite()->getPosition();
	CCPoint pos2 = gem2->getSprite()->getPosition();
	if(pos1.y == pos2.y && pos1.x == pos2.x)
		return false;
	if(pos1.y == pos2.y && std::abs(pos1.x-pos2.x) <= size.width/COL)
	{
		return true;
	}
	if(pos1.x == pos2.x && std::abs(pos1.y-pos2.y) <= size.height/(ROW+2))
	{
		return true;
	}
	return false;
}

void Board::swapTwoGems(Gem*& gem1, Gem*& gem2)
{
	Gem* tmp = gem1;
	gem1 = gem2;
	gem2 = tmp;
	CCPoint pos = gem1->getSprite()->getPosition();
	gem1->getSprite()->setPosition(gem2->getSprite()->getPosition());
	gem2->getSprite()->setPosition(pos);
}

void Board::createGems()
{
	srand((unsigned int)time(0));
	int type;
	for(int i = 0; i < ROW; i++)
		for(int j = 0; j < COL; j++)
		{
			//得到有效的类型
			if(i < 2 && j < 2)
			{
				type = CCRANDOM_0_1()*7;
			}
			else
			{
				if(i >= 2 && j >= 2)
				{
					do 
					{
						type = CCRANDOM_0_1()*7;
					} while ((type == boardGems.at(i*COL+j-1)->getType()
						&& type == boardGems.at(i*COL+j-2)->getType())
						|| (type == boardGems.at((i-1)*COL+j)->getType()
						&& type == boardGems.at((i-2)*COL+j)->getType()));
				}
				else if(j >= 2)
				{
					do 
					{
						type = CCRANDOM_0_1()*7;
					} while (type == boardGems.at(i*COL+j-1)->getType()
						&& type == boardGems.at(i*COL+j-2)->getType());
				}
				else if(i >= 2)
				{
					do 
					{
						type = CCRANDOM_0_1()*7;
					} while (type == boardGems.at((i-1)*COL+j)->getType()
						&& type == boardGems.at((i-2)*COL+j)->getType());
				}
			}

			std::string s = "0.png";
			s[0] = type+'0';
			CCSprite* sprt = CCSprite::createWithSpriteFrameName(s.c_str());
			sprt->setAnchorPoint(ccp(0, 0));
			sprt->setPosition(ccp(j*(size.width/(float)COL), i*(size.height/(float)(ROW+2))));
			sprt->setScaleX(gemSize.width/sprt->getContentSize().width);
			sprt->setScaleY(gemSize.height/sprt->getContentSize().height);
			node->addChild(sprt);
			Gem* gem = new Gem();
			gem->setType((GemType)type);
			gem->setSprite(sprt);
			boardGems.push_back(gem);
			numGemInCol[j]++;
			landInCol[j] += gemSize.height;
		}
}

/*
void Board::breakGems()
{
	
}
*/
	
set<int> Board::findConnectedGems()
{
	set<int> cg;
	for(int i = 0; i < ROW; i++)
	{
		int n = 1;
		GemType type0 = boardGems.at(i*COL)->getType();
		for(int j = 1; j < COL; j++)
		{
			int idx = i*COL+j;
			if(boardGems.at(idx)->getType() == type0)
			{
				n++;
				if(n >= 3)
				{
					cg.insert(idx-2);
					cg.insert(idx-1);
					cg.insert(idx);
				}
			}
			else
			{
				type0 = boardGems.at(idx)->getType();
				n = 1;
			}
		}
	}
	for(int j = 0; j < COL; j++)
	{
		int n = 1;
		GemType type0 = boardGems.at(j)->getType();
		for(int i = 1; i < ROW; i++)
		{
			int idx = i*COL+j;
			if(boardGems.at(idx)->getType() == type0)
			{
				n++;
				if(n >= 3)
				{
					cg.insert(idx-2*COL);
					cg.insert(idx-COL);
					cg.insert(idx);
				}
			}
			else
			{
				type0 = boardGems.at(idx)->getType();
				n = 1;
			}
		}
	}
	return cg;
}

void Board::removeConnectedGems(set<int> cg)
{
	set<int>::iterator it;
	for(it = cg.begin(); it != cg.end(); it++)
	{
		int col = (*it) % COL;
		node->removeChild(boardGems.at((*it))->getSprite(), true);
		mark->setVisible(false);
		selected = false;
		boardGems.at((*it))->setType(Blank);
		numGemInCol[col]--;
		if((*it)/COL*gemSize.height < landInCol[col])
			landInCol[col] = (*it)/COL*gemSize.height;
	}
	for(it = cg.begin(); it != cg.end(); it++)
	{
		for(int i = 0; i < ROW; i++)
		{
			if((*it)+i*COL >= numTotalGems)
				break;
			if(boardGems.at((*it)+i*COL)->getType() != Blank)
			{
				boardGems.at((*it)+i*COL)->setSpeed(SPEED);
				fallingGems[fallingIndex++] = boardGems.at((*it)+i*COL);
				//fallingGems.push_back(boardGems.at((*it)+i*COL));
			}
		}
		int x = (*it) % COL;
		int y = ROW+ROW-numGemInCol[x]-1;
		int type = CCRANDOM_0_1()*7;
		std::string s = "0.png";
		s[0] = type+'0';
		CCSprite* sprt = CCSprite::createWithSpriteFrameName(s.c_str());
		sprt->setAnchorPoint(ccp(0, 0));
		sprt->setPosition(ccp(x*gemSize.width, y*gemSize.height));
		sprt->setScaleX(gemSize.width/sprt->getContentSize().width);
		sprt->setScaleY(gemSize.height/sprt->getContentSize().height);
		node->addChild(sprt);
		Gem* gem = new Gem();
		gem->setType((GemType)type);
		gem->setSprite(sprt);
		gem->setSpeed(SPEED);
		numGemInCol[x]++;
		fallingGems[fallingIndex++] = gem;
	}
	/*
	for(int i = 0; i < COL; i++)
	{
		int top = ROW;
		while(numGemInCol[i] < ROW)
		{
			int type = CCRANDOM_0_1()*7;
			std::string s = "0.png";
			s[0] = type+'0';
			CCSprite* sprt = CCSprite::createWithSpriteFrameName(s.c_str());
			sprt->setAnchorPoint(ccp(0, 0));
			sprt->setPosition(ccp(i*(size.width/(float)COL), top*(size.height/(float)(ROW+2))));
			sprt->setScaleX(gemSize.width/sprt->getContentSize().width);
			sprt->setScaleY(gemSize.height/sprt->getContentSize().height);
			node->addChild(sprt);
			Gem* gem = new Gem();
			gem->setType((GemType)type);
			gem->setSprite(sprt);
			gem->setSpeed(SPEED);
			numGemInCol[i]++;
			fallingGems[fallingIndex++] = gem;
			top++;
		}
	}*/
}

void Board::update(float dt)
{
	if(!isFalling)
	{
		set<int> cg = findConnectedGems();
		finishRemoval = false;
		removeConnectedGems(cg);
		finishRemoval = true;
	}
	if(finishRemoval)
	{
		for(int i = 0; i < numTotalGems; i++)
		{
			if(fallingGems[i] != NULL)
			{
				CCPoint pos;
				Gem* gem = fallingGems[i];
				if(gem->getType() != Blank)
				{
					pos = gem->getSprite()->getPosition();
					pos.y -= gem->getSpeed();
					gem->getSprite()->setPosition(pos);

					int col = (int)(pos.x/gemSize.width);
					if(pos.y <= landInCol[col] && gem->getSpeed() != 0)
					{
						gem->setSpeed(0);
						gem->getSprite()->setPosition(ccp(pos.x, landInCol[col]));
						boardGems[landInCol[col]/gemSize.height*COL+col] = fallingGems[i];
						landInCol[col] += gemSize.height;
						fallingGems[i] = NULL;
					}
				}
			}
		}
		for(int i = 0; i < COL; i++)
		{
			if(landInCol[i] < ROW*gemSize.height)
			{
				isFalling = true;
				break;
			}
			isFalling = false;
			fallingIndex = 0;
		}
	}
}

bool Board::isFallingEmpty()
{
	for(int i = 0; i < numTotalGems; i++)
	{
		if(fallingGems[i] != NULL)
			return false;
	}
	return true;
}