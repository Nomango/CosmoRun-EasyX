#pragma once

class Floor
{
	friend class Game;
	friend class Ball;
public:
	Floor();
	~Floor();
	const int LENOFSIDE;// ���̶Խ��߳���һ��
	int mode;			// �������
	Floor* Next;
	Floor* Prev;
	bool Set();
	void draw(float FloorColor);// �����
	void drawshadow();			// ����Ӱ
	void gap(double speed);
	void lightup();
	void end();
	bool end(double speed);
private:
	double x, y;			// �����������
	double x1, x2, x3, x4, y1, y2, y3, y4;	// ��鶥������
	double d;
	int dx, dy, dz;
	int start_gap, on_gap, end_gap;
	float CosmoOnColor;
	bool create_bug;	// ����������ʱΪtrue
	bool FitRule();			// ���� ����������Ƿ���Ϲ���
	bool JudgeCoincidence();// ��һ�� ������Ƿ��غ�
	void GetLocation();		// ���ݰ�����͵õ�����
	void draw_f(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);	// ���ı���
};