#pragma once

class Game
{
	friend class Floor;
	friend class Ball;
public:
	Game();
	~Game();
	void start();	// 进入游戏
	bool run;
	bool exit;		// 退出游戏为true
	bool restart;	// 重新开始游戏为true

	void Draw();
	void Move();
private:
	float FloorColor;
	double speed;
	const double BASE_SPEED;
	const double SPEED;
	const double FLOOR_AFTER;
	const double FLOOR_BEFORE;
	Floor* headfloor;
	Ball* cosmo;
	int score;
	bool wait;
	void Init();
	void Play();
	void GetCommand();
	void DrawCosmo();
	void DrawFloor();
	void FloorColorChange();
	void Act(double x0, double y0);
	void ChangeDirect();
	void Speed();
	bool JudgeNext();
	void JudgeDie();
	bool JudgeOut();
	void PrintScore();
	void End();
	void Wait();
	void Option();
	bool $return();
	bool $restart();
	void addFloor();
	Floor* GetLastFloor();
	void deleteHeadFloor();
	void deleteAllFloor();
	void deleteCosmo();
	void bkcolorgrad(COLORREF bkcolor);
	void sleep();
};

extern Game *game;
// 线程用于绘制图形
DWORD WINAPI Thread_MoveAndDraw(PVOID pMyPara);