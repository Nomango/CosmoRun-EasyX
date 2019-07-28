#include "stdafx.h"
#include "Ball.h"


Ball::Ball()
{
	direct = 0;
	tail = new Tail(13);
	initTail();
}

Ball::~Ball()
{}

void Ball::initTail()
{
	for (int i = 13; i > 1; i--) {
		for (int j = 0; j < 7; j++) {
			Tail* c = this->tail;
			while (c->Next != NULL)
				c = c->Next;
			Tail* cn = new Tail(i);
			cn->Prev = c;
			c->Next = cn;
		}
	}
}

void Ball::draw()
{
	// »­Cosmo
	setfillcolor(WHITE);
	solidcircle(WID / 2, LEN / 2, 13);

	Tail* c = this->tail;
	while (1) {
		solidcircle(WID / 2 + (int)c->x, LEN / 2 + (int)c->y, c->radius);
		if (c->Next == NULL)
			break;
		else
			c = c->Next;
	}
}

void Ball::movetail(double x0, double y0, double speed)
{
	Tail* c = this->tail;
	c->dx = c->x;
	c->dy = c->y;
	c->x = x0 * speed;
	c->y = y0 * speed;
	while (c->Next != NULL) {
		c = c->Next;
		c->x = c->Prev->x + c->Prev->dx;
		c->y = c->Prev->y + c->Prev->dy;
	}
	while (c->Prev != NULL) {
		c->dx = c->Prev->dx;
		c->dy = c->Prev->dy;
		c = c->Prev;
	}
}