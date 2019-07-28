#include "stdafx.h"


/*    UI初始化   */
GameUI::GameUI()
{
	// 初始化画布
	initgraph(WID, LEN);

	// 使用 API 函数修改窗口名称
	SetWindowText(GetHWnd(), "Cosmo Run");

	// 设置背景色为白色
	setbkcolor(WHITE);

	// 设置背景模式为透明
	setbkmode(TRANSPARENT);

	// 用背景色清空屏幕
	cleardevice();

	// 批量处理图像
	BeginBatchDraw();

	//线程作用：获取鼠标信息
	CreateThread(NULL, 0, Thread_GetMouseMsg, NULL, 0, NULL);
}

GameUI::~GameUI()
{}

/*    主菜单UI   */
void GameUI::StartUI()
{
	// 创建主菜单
	Menu start_UI;

	while (1) {
		// 显示主菜单栏
		start_UI.Show();

		// 显示主菜单文字
		start_UI.Text(278, 183, "Cosmo Run", 60, 800, 0x555555);
		start_UI.Text(278, 243, "      2.5D", 60, 800, 0x555555);
		start_UI.Text(275, 240, "      2.5D", 60, 800, WHITE);

		// 创建主菜单按钮
		Button btn_start(350, 320, 120, 30, "开始");		// 开始按钮
		Button btn_howtoplay(350, 360, 120, 30, "说明");	// 说明按钮
		Button btn_about(350, 400, 120, 30, "关于");		// 关于按钮

		float H = 0;
		while (1) {
			// 主菜单渐变色文字
			if (H >= 360) H = 0;
			else H += 0.4f;
			start_UI.Text(275, 180, "Cosmo Run", 60, 800, HSLtoRGB(H, 1, 0.5f));
			// 显示按钮
			btn_start.Show();
			btn_howtoplay.Show();
			btn_about.Show();
			// 批量显示绘图
			FlushBatchDraw();

			// 按下按钮进入不同功能
			if (btn_start.press) {
				start_UI.Hide();	// 隐藏主菜单栏
				Play();		// 开始游戏
				break;
			}
			else if (btn_howtoplay.press) {
				start_UI.Hide();	// 隐藏主菜单栏
				HowToPlay();		// 进入游戏说明
				break;
			}
			else if (btn_about.press) {
				start_UI.Hide();	// 隐藏主菜单栏
				About();			// 进入关于
				break;
			}
			start_UI.sleep();
		}
	}
}

void GameUI::Play()
{
	game = new Game;		// 创建游戏
	game->start();			// 开始游戏
	if (game->restart) {
		delete game;		// 删除资源
		Play();
	}
	else if (game->exit) {
		delete game;		// 删除资源
	}
	else {
		MessageBox(GetForegroundWindow(),
			"  未知的错误！\n  将退出游戏！",
			"ERROR！！",
			MB_OK | MB_ICONERROR);
		exit(0);
	}
}

void GameUI::HowToPlay()
{
	// 创建说明菜单
	Menu Howtoplay_UI;
	// 显示说明菜单栏
	Howtoplay_UI.Show();
	// 显示说明菜单文字
	Howtoplay_UI.Text(318, 173, "游戏说明", 60, 800, 0x555555);
	Howtoplay_UI.Text(315, 170, "游戏说明", 60, 800, WHITE);
	Howtoplay_UI.Text(265, 250, "  控制小球在三维立体世界中奔跑");
	Howtoplay_UI.Text(255, 280, "点击屏幕或按空格改变它的运动方向");
	Howtoplay_UI.Text(265, 310, "   小心不要让它掉到宇宙外面去");
	Howtoplay_UI.Text(265, 340, "       开始探索Cosmo吧！");

	// 创建返回按钮
	Button btn_return(345, 410, 120, 30, "返回");

	while (1) {
		// 显示按钮
		btn_return.Show();
		FlushBatchDraw();
		// 按下按钮返回主菜单
		if (btn_return.press) {
			Howtoplay_UI.Hide();// 隐藏说明菜单栏
			return;				// 返回主菜单
		}
		Howtoplay_UI.sleep();
	}
}

void GameUI::About()
{
	// 创建关于菜单
	Menu About_UI;
	// 显示关于菜单栏
	About_UI.Show();
	// 显示关于菜单文字
	About_UI.Text(318, 153, "   关于", 60, 800, 0x555555);
	About_UI.Text(315, 150, "   关于", 60, 800, WHITE);
	About_UI.Text(280, 240, "    Made by: nomango");
	About_UI.Text(280, 280, "          2016.11.23");

	// 创建返回按钮
	Button btn_download(295, 340, 220, 30, "下载完整版");
	Button btn_blog(295, 380, 220, 30, "nomango的博客");
	Button btn_return(345, 420, 120, 30, "返回");

	while (1) {
		// 显示按钮
		btn_return.Show();
		btn_blog.Show();
		btn_download.Show();
		FlushBatchDraw();
		// 按下按钮打开下载地址
		if (btn_download.press) {
			ShellExecute(NULL, "open", "http://www.nomango.cn/2016/09/22/160922-cosmorun-publish/", NULL, NULL, SW_SHOWNORMAL);
		}
		// 按下按钮打开博客
		if (btn_blog.press) {
			ShellExecute(NULL, "open", "http://www.nomango.cn", NULL, NULL, SW_SHOWNORMAL);
		}
		// 按下按钮返回主菜单
		if (btn_return.press) {
			About_UI.Hide();// 隐藏关于菜单栏
			return;			// 返回主菜单
		}
		About_UI.sleep();
	}
}
