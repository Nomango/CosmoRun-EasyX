#include "stdafx.h"

// 线程用于绘制图形
DWORD WINAPI Thread_MoveAndDraw(PVOID pMyPara)
{
	while (1) {
		if (game != nullptr) {
			// 游戏界面
			game->Draw();
			// 移动板块
			game->Move();
			// 游戏结束
			if (!game->run)
				break;
		}
		Sleep(3);
	};
	return 0;
}

Game *game = nullptr;

/*   游戏初始化   */
Game::Game() :BASE_SPEED(0.45), SPEED(0.002), FLOOR_AFTER(3), FLOOR_BEFORE(15)
{
	srand((unsigned int)time(NULL));
	score = 0;
	speed = BASE_SPEED;
	FloorColor = rand() % 6 * 60.0f;
	run = false;
	exit = false;
	restart = false;
	wait = false;
	cosmo = new Ball();
	headfloor = new Floor;
}

Game::~Game()
{
	deleteAllFloor();
	deleteCosmo();
}

/*   开始游戏   */
void Game::start()
{
	// 背景色变黑
	bkcolorgrad(BLACK);

	// 初始化
	Init();

	// 进入游戏
	Play();

	// 背景色变白
	bkcolorgrad(WHITE);
}


void Game::Init()
{
	// 起始板块初始化
	headfloor->Prev = NULL;
	headfloor->x = WID / 2;
	headfloor->y = LEN / 2;
	headfloor->mode = 4 + rand() % 4;
	headfloor->CosmoOnColor = 0.1f;
	// 设置cosmo
	cosmo->on = headfloor;
	cosmo->direct = headfloor->mode;
	// 初始化板块
	for (int i = 0; i < FLOOR_BEFORE; i++) {
		addFloor();
		Floor* p = GetLastFloor();
		while (1) {
			Draw();
			if (exit || restart)
				break;
			if (i == FLOOR_BEFORE - 1) {
				if (p->start_gap == 0)
					break;
			}
			else if (p->start_gap <= 30)
				break;
			Sleep(3);
		}
	}
	// 点击开始游戏
	Wait();
}

void Game::Play()
{
	run = true;
	//线程作用：绘制游戏图形
	CreateThread(NULL, 0, Thread_MoveAndDraw, NULL, 0, NULL);
	// 开始游戏
	while (1) {
		// 获取指令
		GetCommand();
		// 检查进入下一板块
		if (JudgeNext()) {
			// 调整速度
			Speed();
			// 检查出界
			JudgeDie();
		}
		// 游戏结束
		if (exit || restart) {
			run = false;
			break;
		}
		sleep();
	};
}

void Game::GetCommand()
{
	if (cmd.getClick()) {
		cmd.setClick(false);
		ChangeDirect();
	}
}

void Game::Draw()
{
	static Button btn_menu(WID - 120, 10, 100, 50, "选项", 28);
	// 清空屏幕
	cleardevice();
	// 画板块
	DrawFloor();
	// 画cosmo
	DrawCosmo();
	// 显示得分
	PrintScore();
	// 选项按钮
	btn_menu.Show();
	// 批量显示绘图
	FlushBatchDraw();
	if (btn_menu.press)
		Option();
}

void Game::DrawCosmo()
{
	cosmo->draw();
}

void Game::DrawFloor()
{
	// 画阴影
	Floor* p = headfloor;
	do {
		p->gap(speed);	// 板块动画
		p->drawshadow();
		if (p->Next == NULL)
			break;
		p = p->Next;
	} while (1);
	// 画板块
	p = headfloor;
	do {
		p->draw(FloorColor);
		if (p->Next == NULL)
			break;
		p = p->Next;
	} while (1);
	// 变颜色
	FloorColorChange();
	// 删板块
	if (headfloor->end(speed))
		deleteHeadFloor();
}

void Game::ChangeDirect()
{
	// 若当前方向与板块方向相同
	// 找到下一个不同于当前的方向
	Floor* p = headfloor;
	if (cosmo->direct == cosmo->on->mode) {
		// 板块方向共有12种
		// cosmo运动方向只有4种
		// 分板块处理运动方向
		do {
			if (cosmo->on->mode & F1) {
				if (cosmo->direct == F1_LEFT_UP || cosmo->direct == F3_UP || cosmo->direct == F2_LEFT_UP) {
					if (p->mode != F1_LEFT_UP &&       p->mode != F3_UP &&       p->mode != F2_LEFT_UP)
						break;
				}
				else if (cosmo->direct == F1_LEFT_DOWN || cosmo->direct == F2_DOWN || cosmo->direct == F3_LEFT_DOWN) {
					if (p->mode != F1_LEFT_DOWN &&       p->mode != F2_DOWN &&       p->mode != F3_LEFT_DOWN)
						break;
				}
				else if (cosmo->direct == F1_RIGHT_UP || cosmo->direct == F2_UP || cosmo->direct == F3_RIGHT_UP) {
					if (p->mode != F1_RIGHT_UP &&       p->mode != F2_UP &&       p->mode != F3_RIGHT_UP)
						break;
				}
				else if (cosmo->direct == F1_RIGHT_DOWN || cosmo->direct == F3_DOWN || cosmo->direct == F2_RIGHT_DOWN) {
					if (p->mode != F1_RIGHT_DOWN &&       p->mode != F3_DOWN &&       p->mode != F2_RIGHT_DOWN)
						break;
				}
			}
			else if (cosmo->on->mode & F2) {
				if (cosmo->direct == F2_LEFT_UP || cosmo->direct == F1_LEFT_UP || cosmo->direct == F3_LEFT_DOWN) {
					if (p->mode != F2_LEFT_UP &&       p->mode != F1_LEFT_UP &&       p->mode != F3_LEFT_DOWN)
						break;
				}
				else if (cosmo->direct == F2_DOWN || cosmo->direct == F1_LEFT_DOWN || cosmo->direct == F3_DOWN) {
					if (p->mode != F2_DOWN &&       p->mode != F1_LEFT_DOWN &&       p->mode != F3_DOWN)
						break;
				}
				else if (cosmo->direct == F2_UP || cosmo->direct == F1_RIGHT_UP || cosmo->direct == F3_UP) {
					if (p->mode != F2_UP &&       p->mode != F1_RIGHT_UP &&       p->mode != F3_UP)
						break;
				}
				else if (cosmo->direct == F2_RIGHT_DOWN || cosmo->direct == F1_RIGHT_DOWN || cosmo->direct == F3_RIGHT_UP) {
					if (p->mode != F2_RIGHT_DOWN &&       p->mode != F1_RIGHT_DOWN &&       p->mode != F3_RIGHT_UP)
						break;
				}
			}
			else if (cosmo->on->mode & F3) {
				if (cosmo->direct == F3_UP || cosmo->direct == F1_LEFT_UP || cosmo->direct == F2_UP) {
					if (p->mode != F3_UP &&       p->mode != F1_LEFT_UP &&       p->mode != F2_UP)
						break;
				}
				else if (cosmo->direct == F3_RIGHT_UP || cosmo->direct == F1_RIGHT_UP || cosmo->direct == F2_RIGHT_DOWN) {
					if (p->mode != F3_RIGHT_UP &&       p->mode != F1_RIGHT_UP &&       p->mode != F2_RIGHT_DOWN)
						break;
				}
				else if (cosmo->direct == F3_LEFT_DOWN || cosmo->direct == F1_LEFT_DOWN || cosmo->direct == F2_LEFT_UP) {
					if (p->mode != F3_LEFT_DOWN &&       p->mode != F1_LEFT_DOWN &&       p->mode != F2_LEFT_UP)
						break;
				}
				else if (cosmo->direct == F3_DOWN || cosmo->direct == F1_RIGHT_DOWN || cosmo->direct == F2_DOWN) {
					if (p->mode != F3_DOWN &&       p->mode != F1_RIGHT_DOWN &&       p->mode != F2_DOWN)
						break;
				}
			}
			if (p->Next == NULL)
				break;
			else
				p = p->Next;
		} while (1);
		cosmo->direct = p->mode;
	}
	else cosmo->direct = cosmo->on->mode;
}

void Game::FloorColorChange()
{
	static int score_0 = 0, d = 0, D = 0;
	static bool change = false;
	if (score % (20 + score / 100 * 20) == 0 && score != 0 && score_0 != score) {
		change = true;
		score_0 = score;
		D = (rand() % 3 + 1) * 120;
	}
	if (change) {
		FloorColor += 0.5f;
		d++;
		if (d == D) {
			d = 0;
			change = false;
		}
	}
	while (FloorColor > 360)
		FloorColor -= 360;
}

void Game::Move()
{
	// 板块方向共有12种
	// cosmo运动方向只有4种
	// 分板块处理运动方向
	if (cosmo->on->mode & F1) {
		if (cosmo->direct == F1_LEFT_UP || cosmo->direct == F3_UP || cosmo->direct == F2_LEFT_UP)
			Act(2.0, 1.0);
		else if (cosmo->direct == F1_LEFT_DOWN || cosmo->direct == F2_DOWN || cosmo->direct == F3_LEFT_DOWN)
			Act(2.0, -1.0);
		else if (cosmo->direct == F1_RIGHT_UP || cosmo->direct == F2_UP || cosmo->direct == F3_RIGHT_UP)
			Act(-2.0, 1.0);
		else if (cosmo->direct == F1_RIGHT_DOWN || cosmo->direct == F3_DOWN || cosmo->direct == F2_RIGHT_DOWN)
			Act(-2.0, -1.0);
	}
	else if (cosmo->on->mode & F2) {
		if (cosmo->direct == F2_LEFT_UP || cosmo->direct == F1_LEFT_UP || cosmo->direct == F3_LEFT_DOWN)
			Act(2.0, 1.0);
		else if (cosmo->direct == F2_DOWN || cosmo->direct == F1_LEFT_DOWN || cosmo->direct == F3_DOWN)
			Act(0, -2.0);
		else if (cosmo->direct == F2_UP || cosmo->direct == F1_RIGHT_UP || cosmo->direct == F3_UP)
			Act(0, 2.0);
		else if (cosmo->direct == F2_RIGHT_DOWN || cosmo->direct == F1_RIGHT_DOWN || cosmo->direct == F3_RIGHT_UP)
			Act(-2.0, -1.0);
	}
	else if (cosmo->on->mode & F3) {
		if (cosmo->direct == F3_UP || cosmo->direct == F1_LEFT_UP || cosmo->direct == F2_UP)
			Act(0, 2.0);
		else if (cosmo->direct == F3_RIGHT_UP || cosmo->direct == F1_RIGHT_UP || cosmo->direct == F2_RIGHT_DOWN)
			Act(-2.0, 1.0);
		else if (cosmo->direct == F3_LEFT_DOWN || cosmo->direct == F1_LEFT_DOWN || cosmo->direct == F2_LEFT_UP)
			Act(2.0, -1.0);
		else if (cosmo->direct == F3_DOWN || cosmo->direct == F1_RIGHT_DOWN || cosmo->direct == F2_DOWN)
			Act(0, -2.0);
	}
}

void Game::Act(double x0, double y0)	// 移动
{
	Floor* p = headfloor;
	while (p != NULL) {
		p->x += x0 * speed;
		p->y += y0 * speed;
		p = p->Next;
	}
	cosmo->movetail(x0, y0, speed);
}

void Game::PrintScore()
{
	static char print_score[5] = "000";
	sprintf_s(print_score, "%3d", score);

	setfillcolor(0xeeeeee);
	settextcolor(WHITE);
	settextstyle(40, 0, "微软雅黑", 0, 0, 800, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH);
	outtextxy(350, 0, print_score);
}

bool Game::JudgeNext()
{
	if (JudgeOut()) {
		cosmo->on = cosmo->on->Next;
		cosmo->on->lightup();
		if (score++ >= FLOOR_AFTER) {
			headfloor->end();
			addFloor();
		}
		return true;
	}
	return false;
}

void Game::JudgeDie()
{
	if (JudgeOut()) End();
}

bool Game::JudgeOut()
{
	if (cosmo->on->mode  & F1) {
		if (!(fabs((cosmo->on->y - LEN / 2) + 0.5*(WID / 2 - cosmo->on->x)) <= cosmo->on->LENOFSIDE + 1 &&
			fabs((cosmo->on->y - LEN / 2) - 0.5*(WID / 2 - cosmo->on->x)) <= cosmo->on->LENOFSIDE + 1))
			return true;
	}
	else if (cosmo->on->mode  & F2) {
		if (!(fabs((cosmo->on->y - LEN / 2) + 0.5*(WID / 2 - cosmo->on->x)) <= cosmo->on->LENOFSIDE + 1 &&
			fabs(WID / 2 - cosmo->on->x) <= cosmo->on->LENOFSIDE + 1))
			return true;
	}
	else if (cosmo->on->mode  & F3) {
		if (!(fabs((cosmo->on->y - LEN / 2) - 0.5*(WID / 2 - cosmo->on->x)) <= cosmo->on->LENOFSIDE + 1 &&
			fabs(WID / 2 - cosmo->on->x) <= cosmo->on->LENOFSIDE + 1))
			return true;
	}
	return false;
}

void Game::Speed()
{
	if (speed < BASE_SPEED + 300 * SPEED)
		speed = BASE_SPEED + score * SPEED;
}

void Game::End()
{
	run = false;
	Menu EndUI;
	EndUI.Show();
	EndUI.Text(315, 153, "游戏结束", 60, 800, 0x555555);
	EndUI.Text(315, 150, "游戏结束", 60, 800, WHITE);
	char print_score[] = "得分:000";
	sprintf_s(print_score, "得分:%d", score);
	EndUI.Text(350, 260, print_score, 40);
	Button btn_Restart(345, 330, 120, 30, "重新开始");
	Button btn_Return(345, 380, 120, 30, "主菜单");
	while (1) {
		btn_Restart.Show();
		btn_Return.Show();
		FlushBatchDraw();
		if (btn_Restart.press) {
			if ($restart()) {
				EndUI.Hide();
				restart = true;
				break;
			}
		}
		if (btn_Return.press) {
			if ($return()) {
				EndUI.Hide();
				exit = true;
				break;
			}
		}
		EndUI.sleep();
	};
}

void Game::Option()
{
	Menu OptionUI;
	OptionUI.Show();
	OptionUI.Text(363, 153, "选项", 60, 800, 0x555555);
	OptionUI.Text(360, 150, "选项", 60, 800, WHITE);
	//	Button btn_GameSet( 350, 250, 120, 30, "设置");
	Button btn_Restart(350, 300, 120, 30, "重新开始");
	Button btn_Return(350, 350, 120, 30, "主菜单");
	Button btn_Resume(350, 400, 120, 30, "返回游戏");
	while (1) {
		//		btn_GameSet.Show();
		btn_Restart.Show();
		btn_Return.Show();
		btn_Resume.Show();
		FlushBatchDraw();
		//if(btn_GameSet.press) 
		if (btn_Restart.press) {
			if ($restart()) {
				OptionUI.Hide();
				restart = true;
				break;
			}
		}
		if (btn_Return.press) {
			if ($return()) {
				OptionUI.Hide();
				exit = true;
				break;
			}
		}
		if (btn_Resume.press) {
			OptionUI.Hide();
			Wait();
			break;
		}
		OptionUI.sleep();
	};
}

void Game::Wait()
{
	if (wait) return;
	wait = true;
	cmd.setClick(false);
	while (1) {
		Draw();
		if (cmd.getClick()) { // 点击继续游戏
			cmd.setClick(false);
			break;
		}
		if (exit || restart)
			break;
	};
	wait = false;
}

bool Game::$restart()
{
	Menu $restart;
	$restart.Set(300, 100);
	$restart.Show();
	$restart.Text(330, 270, "确定要重新开始？", 30, 800);
	Button btn_yes(310, 310, 80, 30, "是");
	Button btn_no(430, 310, 80, 30, "否");
	while (1) {
		btn_yes.Show();
		btn_no.Show();
		FlushBatchDraw();
		if (btn_yes.press)
			return true;
		if (btn_no.press) {
			$restart.Hide();
			return false;
		}
		$restart.sleep();
	};
}

bool Game::$return()
{
	Menu $return;
	$return.Set(300, 100);
	$return.Show();
	$return.Text(320, 270, "确定要返回主菜单？", 30, 800);
	Button btn_yes(310, 310, 80, 30, "是");
	Button btn_no(430, 310, 80, 30, "否");
	while (1) {
		btn_yes.Show();
		btn_no.Show();
		FlushBatchDraw();
		if (btn_yes.press)
			return true;
		if (btn_no.press) {
			$return.Hide();
			return false;
		}
		$return.sleep();
	};
}

void Game::addFloor()
{
	Floor* p = GetLastFloor();
	Floor* pn = new Floor;
	pn->Prev = p;
	// 若板块重合，重置重合板块
	if (!pn->Set()) {
		// 截断板块链表
		p->Prev->Prev->Next = NULL;
		// 删除板块链表
		delete p->Prev;
		delete p;
		delete pn;
		// 加入板块链表
		addFloor();
		addFloor();
		addFloor();
	}
	else {
		p->Next = pn;
	}
}

Floor* Game::GetLastFloor()
{
	Floor* p = headfloor;
	while (p->Next != NULL) {
		p = p->Next;
	}
	return p;
}

void Game::deleteHeadFloor()
{
	Floor* p = headfloor;
	headfloor = headfloor->Next;
	headfloor->Prev = NULL;
	delete p;
}

void Game::deleteAllFloor()
{
	Floor* p = headfloor;
	Floor* pr = p->Next;
	do {
		delete p;
		if (pr == NULL)
			break;
		else {
			p = pr;
			pr = pr->Next;
		}
	} while (1);
}

void Game::deleteCosmo()
{
	Tail* c = cosmo->tail;
	Tail* cr = c->Next;
	do {
		delete c;
		if (cr == NULL)
			break;
		else {
			c = cr;
			cr = cr->Next;
		}
	} while (1);
	delete cosmo;
}

void Game::bkcolorgrad(COLORREF bkcolor)
{
	// 背景色渐变
	if (bkcolor == BLACK) {
		for (int i = 255; i >= 0; i -= 2) {
			setbkcolor(RGB(i, i, i));	// 设置背景色
			cleardevice();			// 用背景色清空屏幕
			FlushBatchDraw();		// 批量显示绘图
			Sleep(1);
		}
	}
	else if (bkcolor == WHITE) {
		for (int i = 0; i <= 255; i += 2) {
			setbkcolor(RGB(i, i, i));	// 设置背景色
			cleardevice();			// 用背景色清空屏幕
			FlushBatchDraw();		// 批量显示绘图
			Sleep(1);
		}
	}
}

void Game::sleep()
{
	Sleep(10);
}
