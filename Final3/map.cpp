#include "Header.h"


Point Map::ball_start_pos = {300, 775};
Point Map::tiger_up_pos = {2075, 0};

Map::Map() {
	ball = new Ball;
	tiger_num = 5;
	for (int i = 0; i < 20; ++i) tiger[i] = new Tiger;
	state = 2;
	myscore = enemyscore = 0;
	show = 0;
	show2 = 0;
	m = 3;
	hard = false;
}

void Map::init() {
	ball->init(ball_start_pos);

	if (m == 5 && hard) tiger_num = 15;
	else if (m == 5) tiger_num = 10;
	else tiger_num = 5;

	if (m != 2 && m != 6) {
		tiger[0]->init({1650, 550});
		tiger[1]->init({1650, 775});
		tiger[2]->init({1650, 1000});
		tiger[3]->init({1950, 650});
		tiger[4]->init({1950, 900});
	} else if (m == 2) {
		tiger[0]->init({1450, 650});
		tiger[1]->init({1450, 900});
		tiger[2]->init({1700, 775});
		tiger[3]->init({1950, 650});
		tiger[4]->init({1950, 900});
	} else for (int i = 0; i < tiger_num; ++i) tiger[i]->init({2500, -100});
	for (int i = 0; i < tiger_num; i++) tiger[i]->kick_out_spd = 50;

	state = 2;

	if (tiger_num == 10) {
		tiger[5]->init({1750, 650});
		tiger[6]->init({1750, 900});
		tiger[7]->init({1850, 550});
		tiger[8]->init({1850, 775});
		tiger[9]->init({1850, 1000});
	}
	if (tiger_num == 15) {
		tiger[5]->init({1750, 650});
		tiger[6]->init({1750, 900});
		tiger[7]->init({1850, 550});
		tiger[8]->init({1850, 775});
		tiger[9]->init({1850, 1000});
		tiger[10]->init({1550, 650});
		tiger[11]->init({1550, 900});
		tiger[12]->init({1450, 550});
		tiger[13]->init({1450, 775});
		tiger[14]->init({1450, 1000});
	}

}

double Map::dis(Point a, Point b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

bool Map::cmp(Tiger* e, Tiger* f) {
	return e->pos.x * e->pos.x + e->pos.y * e->pos.y <
	       f->pos.x * f->pos.x + f->pos.y * f->pos.y;
}


void Map::tiger_move() {
	double x0 = ball->pos.x, y0 = ball->pos.y;
	for (int i = 0; i < tiger_num; i++) tiger[i]->pos -= ball->pos;
	std::sort(tiger, tiger + tiger_num, cmp);
	for (int i = 0; i < tiger_num; i++) tiger[i]->pos += ball->pos;
	double x1 = tiger[0]->pos.x, y1 = tiger[0]->pos.y;
	double x2 = tiger[1]->pos.x, y2 = tiger[1]->pos.y;
	switch (m) {
		case 1:
			for (int i = 0; i < tiger_num; ++i) tiger[i]->max_spd_ground = 5;
			if (hard) for (int i = 0; i < tiger_num; ++i) tiger[i]->max_spd_ground = 10;
			tiger[0]->update_spd({x0, y0});
			tiger[1]->update_spd({x0 - y0 + y1, x0 + y0 - x1});
			tiger[2]->update_spd({x0 + y0 - y1, -x0 + y0 + x1});
			tiger[3]->update_spd({(x0 + 2375) / 2, (y0 + 975) / 2});
			tiger[4]->update_spd({(x0 + 2375) / 2, (y0 + 575) / 2}); // 3+2阵型
			break;
		case 2:
			for (int i = 0; i < tiger_num; ++i) tiger[i]->max_spd_ground = 7;
			if (hard) for (int i = 0; i < tiger_num; ++i) tiger[i]->max_spd_ground = 10;
			tiger[0]->update_spd({x0, y0});
			if ((x0 - x2) * (y1 - y2) - (y0 - y2) * (x1 - x2) >= 0) tiger[1]->update_spd({x0 - y0 + y1, x0 + y0 - x1});
			else tiger[1]->update_spd({x0 + y0 - y1, -x0 + y0 + x1});
			tiger[2]->update_spd({(x0 * 3 + 2375) / 4, (y0 * 3 + 775) / 4});
			if (tiger[3]->pos.y <= tiger[4]->pos.y) {
				Tiger* tmp = tiger[3];
				tiger[3] = tiger[4];
				tiger[4] = tmp;
			}
			tiger[3]->update_spd({(x0 + 2375) / 2, (y0 + 1100) / 2});
			tiger[4]->update_spd({(x0 + 2375) / 2, (y0 + 450) / 2}); //2+2+1阵型
			break;
		case 3:
			for (int i = 0; i < tiger_num; ++i) tiger[i]->max_spd_ground = 9;
			if (hard) for (int i = 0; i < tiger_num; ++i) tiger[i]->max_spd_ground = 10;
			tiger[0]->update_spd({x0, y0});
			if (dis(tiger[1]->pos, {x0 - y0 + y1, x0 + y0 - x1}) >= dis(tiger[1]->pos, {x0 + y0 - y1, -x0 + y0 + x1})) {
				Tiger* tmp = tiger[1];
				tiger[1] = tiger[2];
				tiger[2] = tmp;
			}
			tiger[1]->update_spd({x0 - y0 + y1, x0 + y0 - x1});
			tiger[2]->update_spd({x0 + y0 - y1, -x0 + y0 + x1});
			tiger[3]->update_spd({(x0 + 2375) / 2, (y0 + 975) / 2});
			tiger[4]->update_spd({(x0 + 2375) / 2, (y0 + 575) / 2}); // 3+2阵型
			break;
		case 4:
			for (int i = 1; i <= 4; ++i) tiger[i]->update_spd({2500, -100});
			tiger[0]->max_spd_ground = 11;
			if (hard) {
				tiger[0]->max_spd_ground = 13;
				tiger[0]->kick_out_spd = 60;
			}
			if (tiger[0]->pos.x >= x0)tiger[0]->update_spd({(x0 + tiger[0]->pos.x) / 2, y0});
			else tiger[0]->update_spd({(x0 + 2375) / 2, y0}); //11速能力者
			break;
		case 5:
			for (int i = 0; i < tiger_num; ++i) tiger[i]->max_spd_ground = 7;
			for (int i = 0; i < tiger_num; ++i) tiger[i]->kick_out_spd = 50;
			tiger[0]->update_spd({x0, y0});
			if (dis(tiger[1]->pos, {x0 - y0 + y1, x0 + y0 - x1}) >= dis(tiger[1]->pos, {x0 + y0 - y1, -x0 + y0 + x1})) {
				Tiger* tmp = tiger[1];
				tiger[1] = tiger[2];
				tiger[2] = tmp;
			}
			tiger[1]->update_spd({x0 - y0 + y1, x0 + y0 - x1});
			tiger[2]->update_spd({x0 + y0 - y1, -x0 + y0 + x1});
			tiger[3]->update_spd({(x0 + 2375) / 2, (y0 + 975) / 2});
			tiger[4]->update_spd({(x0 + 2375) / 2, (y0 + 575) / 2});

			for (int i = 5; i < tiger_num; ++i) {
				tiger[i]->spd = {0, 0};
			}
			break;
		case 6:
			for (int i = 0; i <= 4; ++i) tiger[i]->update_spd({2500, -100});
			break;
	}

	for (int i = 0; i < tiger_num; i++) tiger[i]->update_pos();
}

void Map::about_kick() {
	double mindis = 2000;
	bool be_kicked = false;
	int kick_man = -1;
	for (int i = 0; i < tiger_num; i++) {
		if (dis(tiger[i]->pos, ball->pos) <= mindis && tiger[i]->can_kick) {
			mindis = dis(tiger[i]->pos, ball->pos);
			if (mindis <= tiger[i]->kick_dis) {
				be_kicked = true;
				kick_man = i;
			}
		}
	}
	if (be_kicked) ball->be_kicked({125, 775}, 40, tiger[kick_man]->kick_out_spd);
}


void Map::if_goal(int goal) {
	if (goal == 0) return;
	if (goal == 1) myscore++;
	if (goal == -1) enemyscore++;
	for (int i = 0; i < tiger_num; i++) {
		tiger[i]->stop();
	}
	ball->can_move = false;
	state++;
	state %= 3;
}

void Map::begin_match() {
	for (int i = 0; i < tiger_num; i++) {
		tiger[i]->begin_match();
	}
	ball->begin_match();
}

void Map::show_init() {
	ball->init({1150, 775});
}

void Map::show_begin() {
	ball->begin_match();
	tiger[0]->begin_match();
	tiger[0]->kick_out_spd = 140;
}
