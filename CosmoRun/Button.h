#pragma once

class Button
{
public:
	Button(int btnx, int btny, int wid, int len, char *text, int font_size = 30, int font_bold = 400, COLORREF font_color = BLACK);
	~Button();
	bool press;		// 按下按钮为true
	void Show();	// 显示按钮
private:
	COLORREF button_color;
	int color_gap;
	int textx;
	int texty;
	char *text;
	int font_size;
	int font_bold;
	unsigned int font_color;
	int btnxl;
	int btnyl;
	int btnxr;
	int btnyr;
	bool turnlittle;
	void Mouse();
	bool MouseOn();
	void TurnLittle();
	void TurnBig();
	void ChangeButtonColor(bool flag);
};