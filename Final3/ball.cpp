#include "Header.h"

double Ball::delta_acc_ground = 4;
double Ball::delta_acc_sky = 1;
double Ball::f_ground = 2;
double Ball::f_sky = 0.1;
double Ball::max_spd_ground = 10;
double Ball::max_ground_x = 2375;
double Ball::max_ground_y = 1300;
double Ball::min_ground_x = 125;
double Ball::min_ground_y = 250;
double Ball::f_h = 3;

Ball::Ball() {
	pos = {500, 500};
	spd = {0, 0};
	acc = {0, 0};
	h = 0, h_spd = 0;
	can_move = false;
}

void Ball::init(Point start_pos) {
	pos = start_pos;
	spd = {0, 0};
	acc = {0, 0};
	h = 0, h_spd = 0;
	can_move = false;
};

void Ball::begin_match() {
	can_move = true;
}

void Ball::interact_wasd(int w, int a, int s, int d) {
	Point f = {0, 0};
	int delta_acc;
	if (h < 1e-7) {
		delta_acc = delta_acc_ground;
		f.x = f_ground, f.y = f_ground;
	} else    {
		delta_acc = delta_acc_sky;
		f.x = f_sky, f.y = f_sky;
	}
	Point delta = {(double)(d - a) * delta_acc, (double)(s - w) * delta_acc};
	if (!(spd.x == 0 && spd.y == 0) && h < 1e-7) {
		f.x *= spd.x / sqrt(spd.x * spd.x + spd.y * spd.y);
		f.y *= spd.y / sqrt(spd.x * spd.x + spd.y * spd.y);
	}
	if (!(spd.x == 0 && spd.y == 0) && h >= 1e-7) {
		f.x = spd.x * f.x;
		f.y = spd.y * f.y;
	}
	if (can_move) spd += delta;
	if (abs(spd.x) <= abs(f.x)) spd.x = 0;
	else spd.x -= f.x;
	if (abs(spd.y) <= abs(f.y)) spd.y = 0;
	else spd.y -= f.y;
};

void Ball::update_spd() {

	if (h < 1e-7) {
		double now_spd = sqrt(spd.x * spd.x + spd.y * spd.y);
		if (now_spd > max_spd_ground) {
			spd.x = max_spd_ground * spd.x / now_spd;
			spd.y = max_spd_ground * spd.y / now_spd;
		}
		if (h_spd < 1e-7) h_spd = 0;
	} else h_spd -= f_h;
};

void Ball::update_pos() {
	pos += spd;
	if (h >= 1e-7) {
		h += h_spd;
		if (h < 1e-7) {
			if (h_spd > -5) {
				h_spd = 0;
				h = 0;
			} else {
				h = 0.001;
				h_spd *= (-0.5);
			}
		}
	}
};

void Ball::bounce() {
	if (pos.x <= min_ground_x) {
		pos.x = min_ground_x;
		spd.x = (-0.6) * spd.x;
		acc.x = (-0.5) * acc.x;
	}
	if (pos.x >= max_ground_x) {
		pos.x = max_ground_x;
		spd.x = (-0.6) * spd.x;
		acc.x = (-0.5) * acc.x;
	}
	if (pos.y <= min_ground_y) {
		pos.y = min_ground_y;
		spd.y = (-0.6) * spd.y;
		acc.y = (-0.5) * acc.y;
	}
	if (pos.y >= max_ground_y) {
		pos.y = max_ground_y;
		spd.y = (-0.6) * spd.y;
		acc.y = (-0.5) * acc.y;
	}
};

void Ball::interact_jump(int start_h_spd) {
	if (!can_move) return;
	if (h < 1e-7) {
		h = 0.001;
		h_spd = start_h_spd;
	}
};

void Ball::player_control(int w, int a, int s, int d, int kongge) {
	if (kongge) interact_jump(80);
	interact_wasd(w, a, s, d);
	update_spd();
	update_pos();
};

void Ball::be_kicked(Point new_pos, double new_h_spd, double new_spd) {
	Point dis = new_pos - pos;
	spd.x = new_spd * dis.x / sqrt(dis.x * dis.x + dis.y * dis.y);
	spd.y = new_spd * dis.y / sqrt(dis.x * dis.x + dis.y * dis.y);
	h = 0.001;
	h_spd = new_h_spd;
};

int Ball::is_goal() {
	if (pos.x <= 125 && pos.y >= 575 && pos.y <= 975) return -1;
	if (pos.x >= 2375 && pos.y >= 575 && pos.y <= 975) return 1;
	else return 0;
}
