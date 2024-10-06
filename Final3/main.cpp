#include "Header.h"

int main() {
	map.init();
	map.show_init();
	SetTargetFPS(60);

	InitWindow(1600, 900, "An Ordinary Match but I'm the Ball");
	SetWindowPosition(GetScreenWidth() / 2 - 100, GetScreenHeight() / 2);

	img_soccer = LoadImage("resources\\SoccerBall.png");
	ImageFormat(&img_soccer, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
	txt_soccer = LoadTextureFromImage(img_soccer);
	SetWindowIcon(img_soccer);
	InitAudioDevice();
	sound_blackScreen = LoadSound("resources\\fight.wav");
	f = LoadSound("resources\\face_the_facts.wav");
	sound_welcome = LoadSound("resources\\song18.mp3");
	cw = LoadSound("resources\\coach_whistle.wav");
	sound_lose = LoadSound("resources\\horror_lose_.wav");
	sound_victory = LoadSound("resources\\crowd_applause.wav");
	switch_music();

	while (!WindowShouldClose()) {
		if (shouldClose) CloseWindow();

		if (DrawMap::st == DrawMap::In)
			interact_withinGame();

		BeginDrawing();

		
		DrawMap::draw();
		switch_music();

		EndDrawing();
	}
	UnloadImage(img_soccer);
	UnloadTexture(txt_soccer);
	UnloadSound(sound_blackScreen);
	UnloadSound(sound_welcome);
	UnloadSound(cw);
	UnloadSound(sound_lose);
	UnloadSound(sound_victory);
	CloseAudioDevice();
}
