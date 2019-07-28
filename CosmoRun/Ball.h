#pragma once

class Ball
{
	friend class Floor;
	friend class Game;
	friend class Tail;
public:
	Ball();
	~Ball();
	int direct;		// 运动方向
	Floor* on;		// 指向cosmo所在的板块
	Tail* tail;		// 指向cosmo的尾巴
	void draw();	// 画cosmo
	void movetail(double x0, double y0, double speed);
private:
	void initTail();	// 初始化尾巴
};