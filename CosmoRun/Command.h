#pragma once

class Command
{
public:
	Command();
	bool getClick();
	void setClick(bool state);
	bool getLBdown();
	void setLBdown(bool state);
	MOUSEMSG msg;
private:
	bool click;
	bool LBdown;
};

// �߳����ڻ�ȡ���������Ϣ
DWORD WINAPI Thread_GetMouseMsg(PVOID pMyPara);