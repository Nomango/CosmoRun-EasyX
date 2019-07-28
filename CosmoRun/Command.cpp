#include "stdafx.h"
#include "Command.h"

// 线程用于获取键盘鼠标消息
DWORD WINAPI Thread_GetMouseMsg(PVOID pMyPara)
{
	while (1) {
		// 获取鼠标消息
		if (MouseHit()) {
			cmd.msg = GetMouseMsg();
			if (!cmd.getLBdown() && cmd.msg.mkLButton) {
				cmd.setLBdown(true);
				cmd.setClick(true);
			}
			if (cmd.msg.uMsg == WM_LBUTTONUP)
				cmd.setLBdown(false);
		}
		// 获取键盘消息
		if (_kbhit())
			if (_getch() == ' ')
				cmd.setClick(true);
		Sleep(5);
	};
	return 0;
}

// 鼠标键盘消息
Command cmd;

Command::Command()
{
	click = false;
	LBdown = false;
}

bool Command::getClick()
{
	return click;
}

bool Command::getLBdown()
{
	return LBdown;
}

void Command::setClick(bool state)
{
	click = state;
}

void Command::setLBdown(bool state)
{
	LBdown = state;
}