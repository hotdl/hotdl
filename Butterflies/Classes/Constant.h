#pragma once
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "AboutScene.h"
#include "GameScene.h"
#include "Gem.h"
#include "MainScene.h"
#include "OptionScene.h"
#include "ScoreScene.h"
#include "Board.h"
#include <string>
#include <vector>
#include <cmath>
#include <set>

#define ROW 10
#define COL 8
#define SPEED 20

enum GemType
{
	Blank = -1,
	White = 0,
	Red = 1,
	Orange = 2,
	Yellow = 3,
	Green = 4,
	Blue = 5,
	Purple = 6
};