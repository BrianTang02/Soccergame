#include "Header.h"

void DrawMap::draw() {
	switch (DrawMap::st) {
		case DrawMap::Menu: {
			ClearBackground(WHITE);

			const char text[3][40] = {"An Ordinary Match\n  But I'm the Ball", "Start", "Exit"};

			Font font = GetFontDefault();
			font.baseSize = 80;

			DrawText(text[0], 800 - 370, 45, font.baseSize, BLACK);

			Rectangle rect[2] = {{600, 350, 400, 150}, {600, 550, 400, 150}};
			DrawRectangleLines(600, 350, 400, 150, BLACK);
			DrawRectangleLines(600, 550, 400, 150, BLACK);

			DrawText(text[1], 800 - 112, 425 - 38, font.baseSize, BLACK);
			DrawText(text[2], 800 - 80, 635 - 38, font.baseSize, BLACK);

			Vector2 pos = GetMousePosition();
			auto col = Color{130, 130, 130, 50};

			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(pos, rect[0]))
				DrawRectangle(600, 350, 400, 150, col);
			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(pos, rect[1]))
				DrawRectangle(600, 550, 400, 150, col);

			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(pos, rect[0])) {
				DrawMap::st = DrawMap::In;
				//			switch_music();
				SetWindowSize(1800, 3200);
				SetWindowPosition(GetScreenWidth() / 2 - 700, GetScreenHeight() / 2 - 700);
			}

			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(pos, rect[1]))
				shouldClose = 1;
		}
		break;
		case DrawMap::Before:
			drawBackground1();
			break;

		case DrawMap::In:
			if (map.show == 0) DrawMap::frameCount = 0;
			if (map.show == 3 && DrawMap::frameCount < DrawMap::maxFrame)
				DrawMap::frameCount++;
			if (DrawMap::frameCount >= DrawMap::maxFrame && map.show == 3) map.show = 2;
			if (DrawMap::frameCount > 60 + 60 && map.show == 3 && DrawMap::frameCount < DrawMap::maxFrame) {
				ClearBackground(BLACK);
				drawball((map.ball)->pos.x, (map.ball)->pos.y, (map.ball)->h);
				if (DrawMap::frameCount < 500 + 60) {
					windowTremble();
					if (DrawMap::frameCount % 3 == 0)
						SetWindowPosition(GetScreenWidth() / 2 - 1100, GetScreenHeight() / 2 - 500);
				}

				if (DrawMap::frameCount > 120 + 60)
					DrawText("When Nobody is Kicking,", 800, 200, 100, WHITE);
				if (DrawMap::frameCount > 180 + 60)
					DrawText("A Ball has to Kick Himself.", 770, 350, 100, WHITE);

				if (DrawMap::frameCount > 300 + 60)
					DrawText("I'm only a Ball.", 1000, 700, 100, WHITE);
				if (DrawMap::frameCount > 360 + 60)
					DrawText("But I", 1230, 850, 100, WHITE);
				if (DrawMap::frameCount > 420 + 60)
					DrawText("Shall Win the Match!", 870, 1000, 100, WHITE);
			} else {
				ClearBackground(WHITE);
				drawBackground1();
				drawball((map.ball)->pos.x, (map.ball)->pos.y, (map.ball)->h);
				for (int i = 0; i < map.tiger_num; i++) {
					drawperson(map.tiger[i]->pos.x, map.tiger[i]->pos.y, map.tiger[i]->spd);
				}
				drawtip();
			}
			break;

		case DrawMap::After:
			break;

		case DrawMap::Kicked:
			++DrawMap::frameCount;
			if (DrawMap::frameCount < 120) {
				ClearBackground(BLACK);
				if (DrawMap::frameCount > 60)
					map.ball->spd = {200, 0};
				drawball((map.ball)->pos.x, (map.ball)->pos.y, (map.ball)->h);
				windowTremble();
				if (DrawMap::frameCount % 3 == 0)
					SetWindowPosition(GetScreenWidth() / 2 - 1100, GetScreenHeight() / 2 - 500);
			}
			break;
	}
}



void DrawMap::drawBackground1() {
	SetWindowSize(2500, 1375);
	ClearBackground(GREEN);

	const double a = 10;
	for (double x = 130; x < 200; x += 2 * a)
		for (double y = 580; y < 975; y += 2 * a)
			DrawRectangle(x, y, std::min(a, 200 - x), std::min(a, 975 - y), Color{170, 170, 170, 150});

	for (double x = 2310; x < 2375; x += 2 * a)
		for (double y = 580; y < 975; y += 2 * a)
			DrawRectangle(x, y, std::min(a, 2375 - x), std::min(a, 975 - y), Color{170, 170, 170, 150});

	DrawLineEx({125, 450}, {450, 450}, 10, WHITE);
	DrawLineEx({125, 1100}, {450, 1100}, 10, WHITE);
	DrawLineEx({450, 450}, {450, 1100}, 10, WHITE);
	DrawPolyLinesEx({1250, 775}, 128, 200, 0, 10, WHITE);
	DrawLineEx({2375, 1100}, {2050, 1100}, 10, WHITE);
	DrawLineEx({2050, 450}, {2050, 1100}, 10, WHITE);
	DrawLineEx({2375, 450}, {2050, 450}, 10, WHITE);

	DrawPolyLinesEx({400, 775}, 128, 200, 0, 10, WHITE);
	DrawPolyLinesEx({2100, 775}, 128, 200, 0, 10, WHITE);
	DrawRectangle(200, 450 + 5, 245, 550 - 10, GREEN);
	DrawRectangle(2375 - 325 + 5, 450 + 5, 245, 550 - 10, GREEN);

	DrawLineEx({125, 575}, {200, 575}, 10, Color{130, 130, 130, 175});
	DrawLineEx({125, 975}, {200, 975}, 10, Color{130, 130, 130, 175});
	DrawLineEx({200, 575}, {200, 975}, 10, Color{130, 130, 130, 175});
	DrawLineEx({2375, 575}, {2300, 575}, 10, Color{130, 130, 130, 175});
	DrawLineEx({2375, 975}, {2300, 975}, 10, Color{130, 130, 130, 175});
	DrawLineEx({2300, 575}, {2300, 975}, 10, Color{130, 130, 130, 175});

	DrawLineEx({125, 25}, {2375, 25}, 10, WHITE);
	DrawLineEx({125, 200}, {2375, 200}, 10, WHITE);
	DrawLineEx({125, 250}, {2375, 250}, 10, WHITE);
	DrawLineEx({125, 1300}, {2375, 1300}, 10, WHITE);
	DrawLineEx({125, 250}, {125, 1300}, 10, WHITE);
	DrawLineEx({2375, 250}, {2375, 1300}, 10, WHITE);
	DrawLineEx({1250, 250}, {1250, 1300}, 10, WHITE);

	DrawCircle(1250, 775, 15, WHITE);
	DrawCircle(400 - 100, 775, 15, WHITE);
	DrawCircle(2100 + 100, 775, 15, WHITE);

	
	Rectangle rect = {125, 35, 300, 155};
	DrawRectangleLinesEx(rect, 8, BLACK);
	std::string s1, s2;
	if (map.myscore < 10) s1 = "0" + std::to_string(map.myscore);
	else s1 = std::to_string(map.myscore);
	if (map.enemyscore < 10) s2 = "0" + std::to_string(map.enemyscore);
	else s2 = std::to_string(map.enemyscore);
	std::string temp_s = s1 + ":" + s2;
	const char* s = temp_s.c_str();
	Vector2 size = MeasureTextEx(GetFontDefault(), s, 100, 0);
	DrawText(s, 150, 118 - size.y / 2, 100, BLACK);

	DrawText("Press WASD to move, SPACE to jump, TAB back to menu", 480, 124 - size.y / 2, 68, GRAY);

}

void DrawMap::drawball(double pos_x, double pos_y, double h) {
	DrawCircle(pos_x, pos_y, std::max((double)5, 40 - (0.03 * h)), {130, 130, 130, 100});

	DrawTexture(txt_soccer, pos_x - 23, pos_y - 23 - h * 0.1, WHITE);

	
	
}


void DrawMap::drawperson(double pos_x, double pos_y, Point spd) {
	DrawCircle(pos_x, pos_y, 60, {130, 130, 130, 100});
	const double pi = acos(-1);
	Point spd1 = {spd.y, spd.x};
	double angle = atan2(spd.y, spd.x);
	double angle1 = atan2(spd1.y, spd1.x) / pi * 180;
	DrawCircle(pos_x, pos_y, 6, BLACK);
	DrawCircle(pos_x + cos(angle - pi / 2) * 18, pos_y + sin(angle - pi / 2) * 18, 18, BLUE);
	DrawCircle(pos_x - cos(angle - pi / 2) * 18, pos_y - sin(angle - pi / 2) * 18, 18, BLUE);
	DrawCircle(pos_x, pos_y, 20, BROWN);
	DrawRing({(float)pos_x, (float)pos_y}, 14, 20, angle1 - 60, angle1 + 60, 100, YELLOW);
}

void DrawMap::windowTremble() {
	Vector2 cur = GetWindowPosition();
	const int amp = 10;
	SetWindowPosition(cur.x + GetRandomValue(-amp, amp), cur.y + GetRandomValue(-amp, amp));
}

void DrawMap::drawtip() {
	if (map.show == 2) {
		DrawRectangle(125, 200, 2250, 300, {130, 130, 130, 140});
		const char text[10][40] = {"Level Selection", "Level 1", "Level 2", "Level 3", "Level 4", "Level 5", "Freedom", "Hard", "Easy"};
		Font font = GetFontDefault();
		font.baseSize = 150;
		DrawText(text[0], 670, 290, font.baseSize, BLACK);
		DrawRectangle(250, 575, 500, 200, {130, 130, 130, 140});
		DrawRectangle(1000, 575, 500, 200, {130, 130, 130, 140});
		DrawRectangle(1750, 575, 500, 200, {130, 130, 130, 140});
		DrawRectangle(250, 875, 500, 200, {130, 130, 130, 140});
		DrawRectangle(1000, 875, 500, 200, {130, 130, 130, 140});
		DrawRectangle(1750, 875, 500, 200, {130, 130, 130, 140});

		if (map.hard)
			DrawRectangle(250, 1150, 300, 150, Color{255, 0, 0, 200});
		else
			DrawRectangle(250, 1150, 300, 150, Color{130, 130, 130, 140});

		if (!map.hard) {
			DrawText(text[1], 250 + 80, 575 + 50, 100, BLACK);
			DrawText(text[2], 1000 + 80, 575 + 50, 100, BLACK);
			DrawText(text[3], 1750 + 80, 575 + 50, 100, BLACK);
			DrawText(text[4], 250 + 80, 875 + 50, 100, BLACK);
			DrawText(text[5], 1000 + 80, 875 + 50, 100, BLACK);
			DrawText(text[6], 1750 + 50, 875 + 50, 100, BLACK);
		} else {
			DrawText(text[1], 250 + 80, 575 + 50, 100, RED);
			DrawText(text[2], 1000 + 80, 575 + 50, 100, RED);
			DrawText(text[3], 1750 + 80, 575 + 50, 100, RED);
			DrawText(text[4], 250 + 80, 875 + 50, 100, RED);
			DrawText(text[5], 1000 + 80, 875 + 50, 100, RED);
			DrawText(text[6], 1750 + 50, 875 + 50, 100, BLACK);
		}

		if (map.hard)
			DrawText(text[7], 250 + 27, 1150 + 30, 100, BLACK);
		else
			DrawText(text[8], 250 + 27, 1150 + 30, 100, BLACK);


		Vector2 pos = GetMousePosition();

		if (CheckCollisionPointRec(pos, {250, 575, 500, 200}))
			DrawRectangle(250, 575, 500, 200, Color{130, 130, 130, 125});
		if (CheckCollisionPointRec(pos, {1000, 575, 500, 200}))
			DrawRectangle(1000, 575, 500, 200, Color{130, 130, 130, 125});
		if (CheckCollisionPointRec(pos, {1750, 575, 500, 200}))
			DrawRectangle(1750, 575, 500, 200, Color{130, 130, 130, 125});
		if (CheckCollisionPointRec(pos, {250, 875, 500, 200}))
			DrawRectangle(250, 875, 500, 200, Color{130, 130, 130, 125});
		if (CheckCollisionPointRec(pos, {1000, 875, 500, 200}))
			DrawRectangle(1000, 875, 500, 200, Color{130, 130, 130, 125});
		if (CheckCollisionPointRec(pos, {1750, 875, 500, 200}))
			DrawRectangle(1750, 875, 500, 200, Color{130, 130, 130, 125});

		if (CheckCollisionPointRec(pos, {250, 1150, 300, 150})) {
			if (map.hard)
				DrawRectangle(250, 1150, 300, 150, Color{255, 0, 0, 100});
			else
				DrawRectangle(250, 1150, 300, 150, Color{130, 130, 130, 100});
		}

		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(pos, {250, 575, 500, 200})) {
			map.show = 1;
			map.m = 1;
			map.init();
			map.myscore = map.enemyscore = 0;
		}
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(pos, {1000, 575, 500, 200})) {
			map.show = 1;
			map.m = 2;
			map.init();
			map.myscore = map.enemyscore = 0;
		}
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(pos, {1750, 575, 500, 200})) {
			map.show = 1;
			map.m = 3;
			map.init();
			map.myscore = map.enemyscore = 0;
		}
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(pos, {250, 875, 500, 200})) {
			map.show = 1;
			map.m = 4;
			map.init();
			map.myscore = map.enemyscore = 0;
		}
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(pos, {1000, 875, 500, 200})) {
			map.show = 1;
			map.m = 5;
			map.init();
			map.myscore = map.enemyscore = 0;
		}
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(pos, {1750, 875, 500, 200})) {
			map.show = 1;
			map.m = 6;
			map.init();
			map.myscore = map.enemyscore = 0;
		}
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(pos, {250, 1150, 300, 150})) {
			if (map.hard) map.hard = false;
			else map.hard = true;
		}

	}


	std::string _k1 = "Press WASD or SPACE to start";
	std::string _k2 = "Press ENTER to continue";
	std::string _k3 = "Press ENTER to start";
	const char * l3 = _k3.c_str();
	const char * l1 = _k1.c_str();
	const char * l2 = _k2.c_str();
	switch (map.state) {
		case 2:
			if (map.show == 3) break;
			if (map.show == 2) break;
			if (map.show == 0 && map.show2 == 1) break;
			if (map.show == 0 && map.show2 == 0) {
				DrawRectangle(125, 1100, 2250, 150, {130, 130, 130, 100});
				DrawText(l3, 690, 1125, 100, {0, 0, 0, 100});
				break;
			}
			DrawRectangle(125, 1100, 2250, 150, {130, 130, 130, 100});
			DrawText(l1, 425, 1125, 100, {0, 0, 0, 100});
			break;
		case 1:
			if (map.show == 0) break;
			if (map.show == 3) break;
			if (map.show == 2) break;
			DrawRectangle(125, 1100, 2250, 150, {130, 130, 130, 100});
			DrawText(l2, 640, 1125, 100, {0, 0, 0, 100});
			break;
		case 0:

			break;

	}
}
