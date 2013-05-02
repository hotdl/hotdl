#include "Gem.h"

Gem::Gem()
{
	sprt = NULL;
	type = Blank;
	speed = 0;
}

Gem::~Gem()
{
	sprt = NULL;
	type = Blank;
	speed = 0;
}

void Gem::setSprite(CCSprite*& sprt)
{
	this->sprt = sprt;
}

CCSprite*& Gem::getSprite()
{
	return sprt;
}

void Gem::setType(GemType type)
{
	this->type = type;
}

GemType Gem::getType()
{
	return type;
}

int Gem::getSpeed()
{
	return speed;
}

void Gem::setSpeed(int s)
{
	speed = s;
}