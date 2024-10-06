#pragma once

class Ball;
class Map;
struct Point;
class Tiger;
class DrawMap;

#include <bits/stdc++.h>
#include <raylib.h>
#include "point.h"
#include "map.h"
#include "ball.h"
#include "tiger.h"
#include "drawmap.h"

extern Image img_soccer;
extern Texture txt_soccer;
extern Map map;
extern Sound sound_blackScreen, sound_welcome, f, cw, sound_victory, sound_lose;
extern bool shouldClose;

void interact_withinGame();

void switch_music();
