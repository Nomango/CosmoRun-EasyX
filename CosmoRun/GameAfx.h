#pragma once
#include "Command.h"
#include "GameUI.h"
#include "Button.h"
#include "Menu.h"
#include "Game.h"
#include "Ball.h"
#include "Tail.h"
#include "Floor.h"

// 屏幕大小
#define WID 800
#define LEN 600
// 三种板块类型
#define F1 4
#define F2 8
#define F3 16
// 十二种板块方向
#define F1_LEFT_UP    F1+0
#define F1_LEFT_DOWN  F1+1
#define F1_RIGHT_UP   F1+2
#define F1_RIGHT_DOWN F1+3
#define F2_LEFT_UP    F2+0
#define F2_DOWN       F2+1
#define F2_UP         F2+2
#define F2_RIGHT_DOWN F2+3
#define F3_UP         F3+0
#define F3_RIGHT_UP   F3+1
#define F3_LEFT_DOWN  F3+2
#define F3_DOWN       F3+3

// 鼠标键盘消息
extern Command cmd;