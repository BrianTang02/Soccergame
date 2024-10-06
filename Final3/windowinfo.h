#pragma once
#include "Header.h"

class WindowInfo{
public:
	enum MatchState{Menu, Before, In, After, Kicked} st{Menu};
	const Point size{1600, 900};
	int frameCount;
};
