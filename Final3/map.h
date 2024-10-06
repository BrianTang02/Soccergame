#pragma once
#include "Header.h"

class Map {
		friend class DrawMap;
	public:
		Ball* ball;
		Tiger* tiger[20];
		static Point ball_start_pos, tiger_up_pos; //球初始位置
		int state;// 2初始化完位置但不能动 0 游戏中 1 进球

		int show;// 当前展示哪个窗口 0开场动画 1比赛中 2关卡选择 3开场动画后半部分
		int show2;// 判断开场动画是否结束
		int show3;// 多余变量 未使用
		void show_init(); //开场动画预处理
		void show_begin(); //开场动画开始

		int myscore;  //我方得分
		int enemyscore;  //敌方得分

		int m; //当前选择关卡
		bool hard; //游戏难度

		Map();
		void init(); //起始化比赛
		void begin_match(); //开始比赛

		double dis(Point a, Point b);
		static bool cmp(Tiger*, Tiger*);
		
		void tiger_move(); //球员自动寻路
		void about_kick(); //球员踢球检索
		void if_goal(int goal); //每帧结算进球检索

	private:
		int tiger_num; //当前场上球员数量
};
