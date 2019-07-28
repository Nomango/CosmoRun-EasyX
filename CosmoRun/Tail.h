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
	int radius;		// β�͵İ뾶
	double x;		// ������
	double y;		// ������
	double dx;
	double dy;
};