#pragma once
#include "Constant.h"

enum GemType;

class Gem
{
public:
	Gem();
	~Gem();
	void setSprite(CCSprite*& sprt);
	CCSprite*& getSprite();
	void setType(GemType type);
	GemType getType();
	int getSpeed();
	void setSpeed(int s);
private:
	CCSprite* sprt;
	GemType type;
	int speed;
};