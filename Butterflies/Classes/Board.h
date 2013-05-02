#pragma once
#include "Constant.h"

#define SELECTED 0

using namespace std;

class Board : public CCLayer
{
public:
	virtual bool init();
	static CCScene* scene();
	virtual void onEnter();
	virtual void onExit();
	virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent);
//	virtual void ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent);
	virtual void ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent);

	Gem*& getGemByPosition(const CCPoint& pos);
	bool isNeighbor(Gem* gem1, Gem* gem2);
	void swapTwoGems(Gem*& gem1, Gem*& gem2);
	void createGems();
	set<int> findConnectedGems();
	void removeConnectedGems(set<int> cg);
	bool isFallingEmpty();
//	bool breakGems(Gem* gem);
//	vector<Gem*> getNeighbors(Gem* gem);
//	void getBrokenGems();
//	void breakGems();

	void update(float dt);
	CREATE_FUNC(Board);
private:
	CCSize gemSize;
	int numTotalGems;
	int* numGemInCol;
	int* timeSinceAddInCol;
	int* landInCol;
	Gem** fallingGems;
	int fallingIndex;
	vector<Gem*> boardGems;
	CCSize size;
	CCSpriteBatchNode* node;
	CCSprite* mark;
	CCPoint select;
	bool selected;
	set<Gem*> cg;
	bool isFalling;
	bool finishRemoval;
};