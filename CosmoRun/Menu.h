#pragma once

class Menu
{
public:
	Menu();
	~Menu();
	void Set(int wid, int len);	// 设置菜单栏大小
	void Show();	// 显示菜单栏
	void Hide();	// 隐藏菜单栏
	void Text(int x, int y, char *text, int font_size = 25, int font_bold = 600, COLORREF font_color = BLACK);	// 显示文字
	void sleep();
private:
	const int MENU_SPEED;
	int wid;
	int len;
	COLORREF menu_color;
	IMAGE background;
};