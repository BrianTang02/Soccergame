#include "Header.h"


Tiger::Tiger() {
	pos = {3000, 3000};
	spd = {-1, 0};
	can_move = false;
	can_kick = false;
	kick_dis = 60;
	kick_out_spd = 50;
	max_spd_ground = 10;
}

void Tiger::init(Point start_pos) {
	pos = start_pos;
	spd = {-1, 0};
	can_move = false;
	can_kick = false;
};

void Tiger::begin_match() {
	can_move = true;
	can_kick = true;
}

void Tiger::stop() {
	can_move = false;
	can_kick = false;
}

void Tiger::update_spd(Point ball_pos) {
	double dis_x = ball_pos.x - pos.x;
	double dis_y = ball_pos.y - pos.y;
	spd.x = max_spd_ground * dis_x / sqrt(dis_x * dis_x + dis_y * dis_y);
	spd.y = max_spd_ground * dis_y / sqrt(dis_x * dis_x + dis_y * dis_y);
	if (!can_move) spd = {-1, 0};
};

void Tiger::update_pos() {
	if (!can_move) return;
	pos += spd;
};


