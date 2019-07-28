#include "stdafx.h"
#include "Menu.h"


Menu::Menu() : MENU_SPEED(60)
{
	wid = 400;
	len = 350;
	menu_color = 0xeeeeee;
}
Menu::~Menu()
{}

void Menu::Set(int wid, int len)
{
	this->wid = wid;
	this->len = len;
}

void Menu::Show()
{
	// 获取显示菜单前的背景
	getimage(&background, 0, 0, WID, LEN);
	setfillcolor(menu_color);
	setlinecolor(0xcccccc);
	for (int i = 1; i <= MENU_SPEED; i++) {
		fillroundrect((WID - wid) / 2, LEN / 2 - len / 2 * i / MENU_SPEED, (WID + wid) / 2, LEN / 2 + len / 2 * i / MENU_SPEED, 60, 20);
		FlushBatchDraw();
		sleep();
	}
}

void Menu::Hide()
{
	setfillcolor(menu_color);
	setlinecolor(0xcccccc);
	for (int i = MENU_SPEED; i >= 0; i--) {
		cleardevice();
		// 显示创建菜单前的背景
		putimage(0, 0, &background);
		fillroundrect((WID - wid) / 2, LEN / 2 - len / 2 * i / MENU_SPEED, (WID + wid) / 2, LEN / 2 + len / 2 * i / MENU_SPEED, 60, 20);
		FlushBatchDraw();
		sleep();
	}
	putimage(0, 0, &background);
	FlushBatchDraw();
}

void Menu::Text(int x, int y, char *text, int font_size, int font_bold, COLORREF font_color)
{
	settextstyle(font_size, 0, "微软雅黑", 0, 0, font_bold, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH);
	settextcolor(font_color);
	outtextxy(x, y, text);
}

void Menu::sleep()
{
	Sleep(3);
}