#include "stdafx.h"
#include "Button.h"


/*   ��ʼ����ť   */
Button::Button(int btnx, int btny, int wid, int len, char *text, int font_size, int font_bold, COLORREF font_color)
{
	press = false;
	turnlittle = false;
	button_color = 0xeeeeee;// ��ť��ɫ
	color_gap = 0;			// �ݶȽ���ɫ
	this->text = text;		// ��ť����
	this->font_size = font_size;	// ��ť�����ֺ�
	this->font_bold = font_bold;	// ��ť���ִ�ϸ
	this->font_color = font_color;	// ��ť������ɫ
	this->btnxl = btnx;			// ��ť���Ͻ�x����
	this->btnyl = btny;			// ��ť���Ͻ�y����
	this->btnxr = btnx + wid;	// ��ť���½�x����
	this->btnyr = btny + len;	// ��ť���½�y����
	settextstyle(font_size, 0, "΢���ź�", 0, 0, font_bold, false, false, false);
	this->textx = this->btnxl + (wid - textwidth(text)) / 2;	// ����x����
	this->texty = this->btnyl + (len - textheight(text)) / 2;	// ����y����
}
Button::~Button()
{}

/*   ��ʾ��ť   */
void Button::Show()
{
	// ��������
	settextstyle(font_size, 0, "΢���ź�", 0, 0, font_bold, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH);
	settextcolor(font_color);

	// ��Բ�Ǿ��ΰ�ť
	setlinecolor(0xaaaaaa);
	setfillcolor(button_color);

	fillroundrect(btnxl, btnyl, btnxr, btnyr, 20, 20);

	// ��ʾ��ť����
	outtextxy(textx, texty, text);

	// ��ȡ�����Ϣ
	Mouse();
}


/*   ��ȡ�����Ϣ   */
void Button::Mouse()
{
	press = false;
	if (MouseOn()) {
		ChangeButtonColor(true);	// ����ڰ�ť��ʱ��ť��ɫ����
		if (cmd.msg.uMsg == WM_LBUTTONDOWN) {
			TurnLittle();// ����������ʱ��ť��С
		}
		if (cmd.msg.uMsg == WM_LBUTTONUP) {
			cmd.msg.uMsg = 0;
			press = true;	// �����ť
		}
	}
	else {
		ChangeButtonColor(false);	// ��겻�ڰ�ť��ʱ��ť��ɫ��ǳ
		TurnBig();
	}
}

/*   ���ָ��ť   */
bool Button::MouseOn()
{
	if (cmd.msg.x >= btnxl && cmd.msg.x <= btnxr && cmd.msg.y >= btnyl && cmd.msg.y <= btnyr)
		return true;
	else
		return false;
}

/*   ��ť����ɫ   */
void Button::ChangeButtonColor(bool flag)
{
	if (color_gap == 0) {
		if (flag && button_color != 0xbbbbbb) // ��ɫ
			button_color -= 0x111111;
		else if (!flag && button_color != 0xeeeeee) // ǳɫ
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
	// ����ԭ���İ�ťͼ��
	COLORREF bk = getpixel(btnxl, btnyl);
	setfillcolor(bk);
	setlinecolor(bk);
	fillroundrect(btnxl, btnyl, btnxr, btnyr, 20, 20);
	// ��ť��С
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
	// ��ť�Ŵ�
	btnxl -= 5;
	btnyl -= 2;
	btnxr += 5;
	btnyr += 2;
	turnlittle = false;
}