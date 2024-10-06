#include "Header.h"

void interact_withinGame() {
	if (map.show == 0) {
		int enter;
		enter = IsKeyPressed(KEY_ENTER) ? 1 : 0;
		if (enter && map.state == 2) {
			map.show_begin();
			map.show2 = 1;
			map.state = 1;
		} else if (map.state == 2 && map.show2 == 1) {
			map.show = 3;
			map.state = 1;
		}
		map.ball->player_control(0, 0, 0, 0, 0);
		map.ball->bounce();
		map.tiger_move();
		int goal = map.ball->is_goal();
		map.about_kick();
		map.if_goal(goal);
	} else if (map.show == 2) {
		int tab;
		tab = IsKeyPressed(KEY_TAB) ? 1 : 0;
		if (tab) map.show = 1;
	} else if (map.show == 3) {
		map.ball->player_control(0, 0, 0, 0, 0);
		map.ball->bounce();
	} else {
		int tab;
		tab = IsKeyPressed(KEY_TAB) ? 1 : 0;
		if (tab) map.show = 2;
		int enter;
		enter = IsKeyPressed(KEY_ENTER) ? 1 : 0;
		if (enter && map.state == 1) {
			map.state++;
			map.state %= 3;
			map.init();
		}
		int w, a, s, d, space;
		w = IsKeyDown(KEY_W) ? 1 : 0;
		a = IsKeyDown(KEY_A) ? 1 : 0;
		s = IsKeyDown(KEY_S) ? 1 : 0;
		d = IsKeyDown(KEY_D) ? 1 : 0;
		space = IsKeyDown(KEY_SPACE) ? 1 : 0;
		if ((w || a || s || d || space) && map.state == 2) {
			map.state++;
			map.state %= 3;
			map.begin_match();
		}
		map.ball->player_control(w, a, s, d, space);
		map.ball->bounce();
		map.tiger_move();
		int goal = map.ball->is_goal();
		map.about_kick();
		if (map.state == 0) map.if_goal(goal);
	}
}

void switch_music() {
	switch (DrawMap::st) {
		case DrawMap::Menu:
			StopSound(f);
			if (!IsSoundPlaying(sound_welcome)) PlaySound(sound_welcome);
			break;
		case DrawMap::Before:
			StopSound(sound_blackScreen);
			StopSound(sound_welcome);
			PlaySound(f);
			break;
		case DrawMap::In:
			StopSound(sound_welcome);
			if (map.show == 0) {
				StopSound(sound_blackScreen);
				StopSound(sound_victory);
				StopSound(sound_lose);
				if (!IsSoundPlaying(cw)) PlaySound(cw);
				
			} else if (map.show == 3 || map.show == 1 || map.show == 2) {
				StopSound(cw);
				if (DrawMap::frameCount > 60 + 60 && DrawMap::frameCount < DrawMap::maxFrame - 1) {
					StopSound(f);
					if (!IsSoundPlaying(sound_blackScreen)) PlaySound(sound_blackScreen);
				} else {
					if (DrawMap::frameCount >= DrawMap::maxFrame - 1 && IsSoundPlaying(sound_blackScreen)) {
						StopSound(sound_blackScreen);
						if (!IsSoundPlaying(f)) PlaySound(f);
					}
					switch (map.state) {
						case 0:
							StopSound(sound_victory);
							StopSound(sound_lose);
							StopSound(sound_blackScreen);
							if (!IsSoundPlaying(f)) PlaySound(f);
							break;
						case 1:
							switch (map.ball->is_goal()) {
								case 1:
									StopSound(sound_blackScreen);
									StopSound(f);
									if (!IsSoundPlaying(sound_victory)) PlaySound(sound_victory);
									break;
								case -1:
									StopSound(sound_blackScreen);
									StopSound(f);
									if (!IsSoundPlaying(sound_lose)) PlaySound(sound_lose);
									break;
								default:
									StopSound(sound_blackScreen);
							}
							break;

						case 2:
							StopSound(sound_blackScreen);
							if (!IsSoundPlaying(f)) PlaySound(f);
							break;
					}
				}
			}
			break;
		case DrawMap::After:
			StopSound(sound_blackScreen);
			StopSound(sound_welcome);
			PlaySound(f);
			break;
		case DrawMap::Kicked:
			StopSound(f);
			StopSound(sound_welcome);
			PlaySound(sound_blackScreen);
			break;
	}
}
