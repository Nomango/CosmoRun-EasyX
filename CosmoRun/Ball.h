#pragma once

class Ball
{
	friend class Floor;
	friend class Game;
	friend class Tail;
public:
	Ball();
	~Ball();
	int direct;		// �˶�����
	Floor* on;		// ָ��cosmo���ڵİ��
	Tail* tail;		// ָ��cosmo��β��
	void draw();	// ��cosmo
	void movetail(double x0, double y0, double speed);
private:
	void initTail();	// ��ʼ��β��
};