#pragma once

class Floor
{
	friend class Game;
	friend class Ball;
public:
	Floor();
	~Floor();
	const int LENOFSIDE;// 板块短对角线长的一半
	int mode;			// 板块类型
	Floor* Next;
	Floor* Prev;
	bool Set();
	void draw(float FloorColor);// 画板块
	void drawshadow();			// 画阴影
	void gap(double speed);
	void lightup();
	void end();
	bool end(double speed);
private:
	double x, y;			// 板块中心坐标
	double x1, x2, x3, x4, y1, y2, y3, y4;	// 板块顶点坐标
	double d;
	int dx, dy, dz;
	int start_gap, on_gap, end_gap;
	float CosmoOnColor;
	bool create_bug;	// 创建板块出错时为true
	bool FitRule();			// 初步 检查板块类型是否符合规则
	bool JudgeCoincidence();// 进一步 检查板块是否重合
	void GetLocation();		// 根据板块类型得到坐标
	void draw_f(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);	// 画四边形
};