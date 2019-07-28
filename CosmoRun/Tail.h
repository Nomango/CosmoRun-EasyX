#pragma once

class Tail
{
	friend class Ball;
public:
	Tail(int radius);
	~Tail();
	Tail* Prev;
	Tail* Next;
private:
	int radius;		// Î²°ÍµÄ°ë¾¶
	double x;		// ºá×ø±ê
	double y;		// ×Ý×ø±ê
	double dx;
	double dy;
};