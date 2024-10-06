#include "Header.h"

void draw(){
	switch(windowInfo.st){
		case WindowInfo::Menu:{
			SetWindowSize(1600, 900);
			SetWindowPosition(GetScreenWidth()/2-100, GetScreenHeight()/2);
			ClearBackground(WHITE);
			
			const char text[3][40] = {"An Ordinary Match\n  But I'm the Ball", "Start", "Exit"};

			Font font = GetFontDefault();
			font.baseSize = 80;
			
			DrawText(text[0], 800-370, 45, font.baseSize, BLACK);
			
			Rectangle rect[2] = {{600, 350, 400, 150}, {600, 550, 400, 150}};
			DrawRectangleLines(600, 350, 400, 150, BLACK);
			DrawRectangleLines(600, 550, 400, 150, BLACK);
			
			DrawText(text[1], 800-112, 425-38, font.baseSize, BLACK);
			DrawText(text[2], 800-80, 635-38, font.baseSize, BLACK);
			
			Vector2 pos = GetMousePosition();
			auto col = Color{130, 130, 130, 50};

			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(pos, rect[0]))
				DrawRectangle(600, 350, 400, 150, col);
			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(pos, rect[1]))
				DrawRectangle(600, 550, 400, 150, col);
			
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(pos, rect[0])){
				windowInfo.st = WindowInfo::In;
				SetWindowSize(1800, 3200);
				SetWindowPosition(GetScreenWidth()/2-700, GetScreenHeight()/2-700);
			}
				
			if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT) && CheckCollisionPointRec(pos, rect[1]))
				CloseWindow();
			}
			break;
		case WindowInfo::Before:
			drawBackground1();
			break;
			
		case WindowInfo::In:
			ClearBackground(WHITE);
			drawBackground1();
			drawball((map.ball)->pos.x,(map.ball)->pos.y,(map.ball)->h);
			for(int i=0;i<map.tiger_num;i++){
				drawperson(map.tiger[i]->pos.x,map.tiger[i]->pos.y,map.tiger[i]->spd, 0);
			}
			break;
		
		case WindowInfo::After:
			break;
		
		case WindowInfo::Kicked:
			++windowInfo.frameCount;
			if (windowInfo.frameCount < 120){
				ClearBackground(BLACK);
				//Vector2 cur = GetWindowPosition();
				//cur.x += (map.ball)->pos.x, cur.y += (map.ball)->pos.y;
				
				//SetWindowSize(600, 400);
				//SetWindowPosition((map.ball)->pos.x, (map.ball)->pos.y);
				
				//Vector2 cur2 = GetWindowPosition();
				if (windowInfo.frameCount > 60)
					map.ball->spd = {200, 0};
				drawball((map.ball)->pos.x,(map.ball)->pos.y,(map.ball)->h);
				windowTremble();
				if (windowInfo.frameCount%3 == 0) 
					SetWindowPosition(GetScreenWidth()/2-1100, GetScreenHeight()/2-500);
			}
			break;
	}
}

void drawBackground(){
	SetWindowSize(1800, 3200);
	Image img = LoadImage("resources\\ground.png");
	ImageFormat(&img, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
	Texture2D txt = LoadTextureFromImage(img);
	//DrawTexture(Texture2D texture, int posX, int posY, Color tint);
	DrawTexture(txt, 0, 0,WHITE);
	UnloadImage(img);
	UnloadTexture(txt);
	
//	Image img2 = LoadImage("resources\\SoccerBall.png");
//	ImageFormat(&img2, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
//	Texture2D a2 = LoadTextureFromImage(img2);
//	Texture2D txt2 = LoadTextureFromImage(img2);
//	//DrawTexture(Texture2D texture, int posX, int posY, Color tint);
//	DrawTexture(txt2, 0, 0,WHITE);
}


void drawBackground1(){
	SetWindowSize(2500,1375);
	ClearBackground(GREEN);
	
	const double a = 10;
	for (double x = 130; x < 200; x += 2*a)
		for (double y = 580; y < 975; y += 2*a)
			DrawRectangle(x, y, std::min(a, 200-x), std::min(a, 975-y), Color{170, 170, 170, 150});
	
	for (double x = 2310; x < 2375; x += 2*a)
		for (double y = 580; y < 975; y += 2*a)
			DrawRectangle(x, y, std::min(a, 2375-x), std::min(a, 975-y), Color{170, 170, 170, 150});
	
	DrawLineEx({125,450}, {450,450}, 10, WHITE);
	DrawLineEx({125,1100}, {450,1100}, 10, WHITE);
	DrawLineEx({450,450}, {450,1100}, 10, WHITE);
	DrawPolyLinesEx({1250,775}, 128, 200, 0, 10, WHITE);
	DrawLineEx({2375,1100}, {2050,1100}, 10, WHITE);
	DrawLineEx({2050,450}, {2050,1100}, 10, WHITE);
	DrawLineEx({2375,450}, {2050,450}, 10, WHITE);
	
	DrawPolyLinesEx({400,775}, 128, 200, 0, 10, WHITE);
	DrawPolyLinesEx({2100,775}, 128, 200, 0, 10, WHITE);
	DrawRectangle(200,450+5,245,550-10,GREEN);
	DrawRectangle(2375-325+5,450+5,245,550-10,GREEN);
	
	DrawLineEx({125,575},{200,575},10,Color{130, 130, 130, 175});
	DrawLineEx({125,975},{200,975},10,Color{130, 130, 130, 175});
	DrawLineEx({200,575},{200,975},10, Color{130, 130, 130, 175});
	DrawLineEx({2375,575},{2300,575},10,Color{130, 130, 130, 175});
	DrawLineEx({2375,975},{2300,975},10,Color{130, 130, 130, 175});
	DrawLineEx({2300,575},{2300,975},10, Color{130, 130, 130, 175});
	
	DrawLineEx({125,25}, {2375,25}, 10, WHITE);
	DrawLineEx({125,200}, {2375,200}, 10, WHITE);
	DrawLineEx({125,250}, {2375,250}, 10, WHITE);
	DrawLineEx({125,1300}, {2375,1300}, 10, WHITE);
	DrawLineEx({125,250}, {125,1300}, 10, WHITE);
	DrawLineEx({2375,250}, {2375,1300}, 10, WHITE);
	DrawLineEx({1250,250}, {1250,1300}, 10, WHITE);
	
	DrawCircle(1250, 775, 15, WHITE);
	DrawCircle(400-100, 775, 15, WHITE);
	DrawCircle(2100+100, 775, 15, WHITE);
	
	for (int x = 700; x < 2000; x += 100)
		for (int y = 60; y < 190; y += 50)
			drawperson(x, y, {0, 1}, 1);
	
	drawball(450,450,0);
	drawperson(300,400,{-10,10}, 0);
	
	//score bar
	Rectangle rect = {135, 35, 300, 155};
	DrawRectangleLinesEx(rect, 8, BLACK);
	int s1 = 2, s2 = 1;	//逻辑模块传参
	std::string temp_s = std::to_string(s1)+": "+std::to_string(s2);
	const char* s = temp_s.c_str();
	Vector2 size = MeasureTextEx(GetFontDefault(), s, 100, 0);
	DrawText(s, 285-size.x/2, 112-size.y/2, 100, BLACK);
	
	//DrawPolyLinesEx({450,450}, 128, 33, 0, 5, RED);	
	//void DrawEllipseLines(int centerX, int centerY, float radiusH, float radiusV, Color color); 
	//void DrawLine(int startPosX, int startPosY, int endPosX, int endPosY, Color color);
	//void DrawLineEx(Vector2 startPos, Vector2 endPos, float thick, Color color);
	//void DrawCircleLines(int centerX, int centerY, float radius, Color color); 
	//void DrawPolyLinesEx(Vector2 center, int sides, float radius, float rotation, float lineThick, Color color);
	//void DrawRectangle(int posX, int posY, int width, int height, Color color);  
}

void drawball(double pos_x, double pos_y,double h){
	DrawCircle(pos_x,pos_y,std::max((double)5,40-(0.03*h)),{130,130,130,100});

	DrawTexture(txt_soccer, pos_x-23, pos_y-23-h*0.1,WHITE);
	//DrawRing({1000,1000},20,30,30,150,100,BLACK);
	
	//void DrawRing(Vector2 center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color color); 
}


void drawperson(double pos_x,double pos_y,Point spd, bool isAudience){
	if (!isAudience) DrawCircle(pos_x,pos_y,60,{130,130,130,100});
	const double pi = acos(-1);
	Point spd1 = {spd.y, spd.x};
	double angle = atan2(spd.y, spd.x);
	double angle1 = atan2(spd1.y, spd1.x)/pi*180;
	DrawCircle(pos_x, pos_y, 6, BLACK);
	DrawCircle(pos_x+cos(angle-pi/2)*18, pos_y+sin(angle-pi/2)*18, 18, BLUE);
	DrawCircle(pos_x-cos(angle-pi/2)*18, pos_y-sin(angle-pi/2)*18, 18, BLUE);
	DrawCircle(pos_x, pos_y, 20, BROWN);
	DrawRing({pos_x,pos_y}, 14, 20, angle1-60, angle1+60, 100, YELLOW);
}

void windowTremble(){
	Vector2 cur = GetWindowPosition();
	const int amp = 10;
	SetWindowPosition(cur.x+GetRandomValue(-amp, amp), cur.y+GetRandomValue(-amp, amp));
}
