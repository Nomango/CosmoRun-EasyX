#include "stdafx.h"
#include "Button.h"


/*   初始化按钮   */
Button::Button(int btnx, int btny, int wid, int len, char *text, int font_size, int font_bold, COLORREF font_color)
{
	press = false;
	turnlittle = false;
	button_color = 0xeeeeee;// 按钮颜色
	color_gap = 0;			// 梯度渐变色
	this->text = text;		// 按钮文字
	this->font_size = font_size;	// 按钮文字字号
	this->font_bold = font_bold;	// 按钮文字粗细
	this->font_color = font_color;	// 按钮文字颜色
	this->btnxl = btnx;			// 按钮左上角x坐标
	this->btnyl = btny;			// 按钮左上角y坐标
	this->btnxr = btnx + wid;	// 按钮右下角x坐标
	this->btnyr = btny + len;	// 按钮右下角y坐标
	settextstyle(font_size, 0, "微软雅黑", 0, 0, font_bold, false, false, false);
	this->textx = this->btnxl + (wid - textwidth(text)) / 2;	// 文字x坐标
	this->texty = this->btnyl + (len - textheight(text)) / 2;	// 文字y坐标
}
Button::~Button()
{}

/*   显示按钮   */
void Button::Show()
{
	// 设置字体
	settextstyle(font_size, 0, "微软雅黑", 0, 0, font_bold, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH);
	settextcolor(font_color);

	// 画圆角矩形按钮
	setlinecolor(0xaaaaaa);
	setfillcolor(button_color);

	fillroundrect(btnxl, btnyl, btnxr, btnyr, 20, 20);

	// 显示按钮文字
	outtextxy(textx, texty, text);

	// 获取鼠标消息
	Mouse();
}


/*   获取鼠标消息   */
void Button::Mouse()
{
	press = false;
	if (MouseOn()) {
		ChangeButtonColor(true);	// 鼠标在按钮上时按钮颜色变深
		if (cmd.msg.uMsg == WM_LBUTTONDOWN) {
			TurnLittle();// 鼠标左键按下时按钮变小
		}
		if (cmd.msg.uMsg == WM_LBUTTONUP) {
			cmd.msg.uMsg = 0;
			press = true;	// 点击按钮
		}
	}
	else {
		ChangeButtonColor(false);	// 鼠标不在按钮上时按钮颜色变浅
		TurnBig();
	}
}

/*   鼠标指向按钮   */
bool Button::MouseOn()
{
	if (cmd.msg.x >= btnxl && cmd.msg.x <= btnxr && cmd.msg.y >= btnyl && cmd.msg.y <= btnyr)
		return true;
	else
		return false;
}

/*   按钮渐变色   */
void Button::ChangeButtonColor(bool flag)
{
	if (color_gap == 0) {
		if (flag && button_color != 0xbbbbbb) // 深色
			button_color -= 0x111111;
		else if (!flag && button_color != 0xeeeeee) // 浅色
			button_color += 0x111111;
		color_gap = 6;
	}
	else
		color_gap--;
}

void Button::TurnLittle()
{
	if (turnlittle)
		return;
	// 覆盖原来的按钮图案
	COLORREF bk = getpixel(btnxl, btnyl);
	setfillcolor(bk);
	setlinecolor(bk);
	fillroundrect(btnxl, btnyl, btnxr, btnyr, 20, 20);
	// 按钮缩小
	btnxl += 5;
	btnyl += 2;
	btnxr -= 5;
	btnyr -= 2;
	turnlittle = true;
}

void Button::TurnBig()
{
	if (!turnlittle)
		return;
	// 按钮放大
	btnxl -= 5;
	btnyl -= 2;
	btnxr += 5;
	btnyr += 2;
	turnlittle = false;
}