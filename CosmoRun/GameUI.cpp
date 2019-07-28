#include "stdafx.h"


/*    UI��ʼ��   */
GameUI::GameUI()
{
	// ��ʼ������
	initgraph(WID, LEN);

	// ʹ�� API �����޸Ĵ�������
	SetWindowText(GetHWnd(), "Cosmo Run");

	// ���ñ���ɫΪ��ɫ
	setbkcolor(WHITE);

	// ���ñ���ģʽΪ͸��
	setbkmode(TRANSPARENT);

	// �ñ���ɫ�����Ļ
	cleardevice();

	// ��������ͼ��
	BeginBatchDraw();

	//�߳����ã���ȡ�����Ϣ
	CreateThread(NULL, 0, Thread_GetMouseMsg, NULL, 0, NULL);
}

GameUI::~GameUI()
{}

/*    ���˵�UI   */
void GameUI::StartUI()
{
	// �������˵�
	Menu start_UI;

	while (1) {
		// ��ʾ���˵���
		start_UI.Show();

		// ��ʾ���˵�����
		start_UI.Text(278, 183, "Cosmo Run", 60, 800, 0x555555);
		start_UI.Text(278, 243, "      2.5D", 60, 800, 0x555555);
		start_UI.Text(275, 240, "      2.5D", 60, 800, WHITE);

		// �������˵���ť
		Button btn_start(350, 320, 120, 30, "��ʼ");		// ��ʼ��ť
		Button btn_howtoplay(350, 360, 120, 30, "˵��");	// ˵����ť
		Button btn_about(350, 400, 120, 30, "����");		// ���ڰ�ť

		float H = 0;
		while (1) {
			// ���˵�����ɫ����
			if (H >= 360) H = 0;
			else H += 0.4f;
			start_UI.Text(275, 180, "Cosmo Run", 60, 800, HSLtoRGB(H, 1, 0.5f));
			// ��ʾ��ť
			btn_start.Show();
			btn_howtoplay.Show();
			btn_about.Show();
			// ������ʾ��ͼ
			FlushBatchDraw();

			// ���°�ť���벻ͬ����
			if (btn_start.press) {
				start_UI.Hide();	// �������˵���
				Play();		// ��ʼ��Ϸ
				break;
			}
			else if (btn_howtoplay.press) {
				start_UI.Hide();	// �������˵���
				HowToPlay();		// ������Ϸ˵��
				break;
			}
			else if (btn_about.press) {
				start_UI.Hide();	// �������˵���
				About();			// �������
				break;
			}
			start_UI.sleep();
		}
	}
}

void GameUI::Play()
{
	game = new Game;		// ������Ϸ
	game->start();			// ��ʼ��Ϸ
	if (game->restart) {
		delete game;		// ɾ����Դ
		Play();
	}
	else if (game->exit) {
		delete game;		// ɾ����Դ
	}
	else {
		MessageBox(GetForegroundWindow(),
			"  δ֪�Ĵ���\n  ���˳���Ϸ��",
			"ERROR����",
			MB_OK | MB_ICONERROR);
		exit(0);
	}
}

void GameUI::HowToPlay()
{
	// ����˵���˵�
	Menu Howtoplay_UI;
	// ��ʾ˵���˵���
	Howtoplay_UI.Show();
	// ��ʾ˵���˵�����
	Howtoplay_UI.Text(318, 173, "��Ϸ˵��", 60, 800, 0x555555);
	Howtoplay_UI.Text(315, 170, "��Ϸ˵��", 60, 800, WHITE);
	Howtoplay_UI.Text(265, 250, "  ����С������ά���������б���");
	Howtoplay_UI.Text(255, 280, "�����Ļ�򰴿ո�ı������˶�����");
	Howtoplay_UI.Text(265, 310, "   С�Ĳ�Ҫ����������������ȥ");
	Howtoplay_UI.Text(265, 340, "       ��ʼ̽��Cosmo�ɣ�");

	// �������ذ�ť
	Button btn_return(345, 410, 120, 30, "����");

	while (1) {
		// ��ʾ��ť
		btn_return.Show();
		FlushBatchDraw();
		// ���°�ť�������˵�
		if (btn_return.press) {
			Howtoplay_UI.Hide();// ����˵���˵���
			return;				// �������˵�
		}
		Howtoplay_UI.sleep();
	}
}

void GameUI::About()
{
	// �������ڲ˵�
	Menu About_UI;
	// ��ʾ���ڲ˵���
	About_UI.Show();
	// ��ʾ���ڲ˵�����
	About_UI.Text(318, 153, "   ����", 60, 800, 0x555555);
	About_UI.Text(315, 150, "   ����", 60, 800, WHITE);
	About_UI.Text(280, 240, "    Made by: nomango");
	About_UI.Text(280, 280, "          2016.11.23");

	// �������ذ�ť
	Button btn_download(295, 340, 220, 30, "����������");
	Button btn_blog(295, 380, 220, 30, "nomango�Ĳ���");
	Button btn_return(345, 420, 120, 30, "����");

	while (1) {
		// ��ʾ��ť
		btn_return.Show();
		btn_blog.Show();
		btn_download.Show();
		FlushBatchDraw();
		// ���°�ť�����ص�ַ
		if (btn_download.press) {
			ShellExecute(NULL, "open", "http://www.nomango.cn/2016/09/22/160922-cosmorun-publish/", NULL, NULL, SW_SHOWNORMAL);
		}
		// ���°�ť�򿪲���
		if (btn_blog.press) {
			ShellExecute(NULL, "open", "http://www.nomango.cn", NULL, NULL, SW_SHOWNORMAL);
		}
		// ���°�ť�������˵�
		if (btn_return.press) {
			About_UI.Hide();// ���ع��ڲ˵���
			return;			// �������˵�
		}
		About_UI.sleep();
	}
}
