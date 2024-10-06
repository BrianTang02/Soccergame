#pragma once
#include "Header.h"

class DrawMap {
	public:
		enum MatchState {Menu, Before, In, After, Kicked};	//所处窗口枚举
		inline static MatchState st{Menu};
		inline static int frameCount; //帧数计算
		inline static int maxFrame = 750; //动画最大帧数

		static void draw(); //总绘制函数
		static void drawBackground1(); //绘制球场 
		static void drawball(double pos_x, double pos_y, double h); //绘制球
		static void drawperson(double pos_x, double pos_y, Point spd); //绘制球员
 		static void drawtip(); //绘制弹窗

		static void windowTremble();//核心功能实现 窗口颤抖

	private:

};
