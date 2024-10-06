#pragma once

#include "Header.h"

class Tiger {
	public:
		friend class Map;
		friend class DrawMap;

		Tiger();
		void init(Point start_pos); //初始化
		void begin_match(); //变为可移动状态
		void stop(); //变为不可移动状态

		void update_spd(Point ball_pos); //更新速度
		void update_pos(); //更新位置
	private:
		Point pos; //位置
		Point spd; //速度
		bool can_move; //能否移动
		bool can_kick; //能否踢球
		int kick_dis; //踢球判定距离
		int kick_out_spd; //踢球踢出距离
		int max_spd_ground; //最大移动速度
};
