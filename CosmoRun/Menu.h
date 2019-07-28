#pragma once

class Menu
{
public:
	Menu();
	~Menu();
	void Set(int wid, int len);	// ���ò˵�����С
	void Show();	// ��ʾ�˵���
	void Hide();	// ���ز˵���
	void Text(int x, int y, char *text, int font_size = 25, int font_bold = 600, COLORREF font_color = BLACK);	// ��ʾ����
	void sleep();
private:
	const int MENU_SPEED;
	int wid;
	int len;
	COLORREF menu_color;
	IMAGE background;
};