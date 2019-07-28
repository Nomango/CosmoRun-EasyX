#include "stdafx.h"
#include "Floor.h"


Floor::Floor() :LENOFSIDE(34)
{
	start_gap = 40;
	on_gap = 0;
	end_gap = 0;
	Next = NULL;
	Prev = NULL;
	create_bug = false;
	CosmoOnColor = 0;
	dx = 0;
	dy = 0;
	dz = 0;
}
Floor::~Floor()
{}

/*   ³õÊ¼»¯°å¿é   */
bool Floor::Set()
{
	do {
		// °å¿é³õÊ¼»¯³ö´í
		if (create_bug) return false;

		// ÈýÖÖ°å¿éÀàÐÍºÍËÄÖÖ·½Ïò
		mode = (int)pow(double(2), rand() % 3 + 2) + rand() % 4;

		// ¸ù¾Ý°å¿éÀàÐÍµÃµ½×ø±ê
		GetLocation();
	} while (!FitRule() || !JudgeCoincidence());	// ¼ì²é°å¿éÀàÐÍÊÇ·ñ·ûºÏ¹æÔò
	return true;
}

void Floor::gap(double speed)
{
	if (start_gap) start_gap--;		// ¶¯»­Ð§¹û
	if (end_gap >= 1) end_gap++;	// ¶¯»­Ð§¹û
	if (on_gap) {
		on_gap--;
		CosmoOnColor += 0.005f;
	}
	d = (40 - start_gap) / 40.0 * ((int)(20.0 / speed) - end_gap) / (int)(20.0 / speed);	// ¶¯»­Ð§¹û
}

void Floor::drawshadow()
{
	setlinecolor(0x444444);
	setfillcolor(0x444444);
	if (mode & F1) {
		x1 = x - 2 * LENOFSIDE*d, y1 = y;
		x2 = x, y2 = y + LENOFSIDE*d;
		x3 = x + 2 * LENOFSIDE*d, y3 = y;
		x4 = x, y4 = y - LENOFSIDE*d;
		draw_f(x1, y1 + 4, x2, y2 + 4, x3, y3 + 4, x4, y4 + 4);
	}
	else if (mode & F2) {
		x1 = x - LENOFSIDE*d, y1 = y - LENOFSIDE * 2 * 0.75*d;
		x2 = x + LENOFSIDE*d, y2 = y - LENOFSIDE * 2 * 0.25*d;
		x3 = x + LENOFSIDE*d, y3 = y + LENOFSIDE * 2 * 0.75*d;
		x4 = x - LENOFSIDE*d, y4 = y + LENOFSIDE * 2 * 0.25*d;
		draw_f(x1 + 4, y1 + 4, x2 + 4, y2 + 4, x3 + 4, y3 + 4, x4 + 4, y4 + 4);
	}
	else if (mode & F3) {
		x1 = x - LENOFSIDE*d, y1 = y - LENOFSIDE * 2 * 0.25*d;
		x2 = x + LENOFSIDE*d, y2 = y - LENOFSIDE * 2 * 0.75*d;
		x3 = x + LENOFSIDE*d, y3 = y + LENOFSIDE * 2 * 0.25*d;
		x4 = x - LENOFSIDE*d, y4 = y + LENOFSIDE * 2 * 0.75*d;
		draw_f(x1 - 4, y1 + 4, x2 - 4, y2 + 4, x3 - 4, y3 + 4, x4 - 4, y4 + 4);
	}
}

void Floor::draw(float FloorColor)
{
	setlinecolor(0x444444);
	setfillcolor(0x444444);
	if (mode & F1) {
		x1 = x - 2 * LENOFSIDE*d, y1 = y;
		x2 = x, y2 = y + LENOFSIDE*d;
		x3 = x + 2 * LENOFSIDE*d, y3 = y;
		x4 = x, y4 = y - LENOFSIDE*d;
		setfillcolor(HSLtoRGB(FloorColor, 0.8f + 2 * CosmoOnColor, 0.5f + CosmoOnColor));
		draw_f(x1, y1, x2, y2, x3, y3, x4, y4);
	}
	else if (mode & F2) {
		x1 = x - LENOFSIDE*d, y1 = y - LENOFSIDE * 2 * 0.75*d;
		x2 = x + LENOFSIDE*d, y2 = y - LENOFSIDE * 2 * 0.25*d;
		x3 = x + LENOFSIDE*d, y3 = y + LENOFSIDE * 2 * 0.75*d;
		x4 = x - LENOFSIDE*d, y4 = y + LENOFSIDE * 2 * 0.25*d;
		setfillcolor(HSLtoRGB(FloorColor, 0.8f + 2 * CosmoOnColor, 0.38f + CosmoOnColor));
		draw_f(x1, y1, x2, y2, x3, y3, x4, y4);
	}
	else if (mode & F3) {
		x1 = x - LENOFSIDE*d, y1 = y - LENOFSIDE * 2 * 0.25*d;
		x2 = x + LENOFSIDE*d, y2 = y - LENOFSIDE * 2 * 0.75*d;
		x3 = x + LENOFSIDE*d, y3 = y + LENOFSIDE * 2 * 0.25*d;
		x4 = x - LENOFSIDE*d, y4 = y + LENOFSIDE * 2 * 0.75*d;
		setfillcolor(HSLtoRGB(FloorColor, 0.8f + 2 * CosmoOnColor, 0.26f + CosmoOnColor));
		draw_f(x1, y1, x2, y2, x3, y3, x4, y4);
	}
}

void Floor::draw_f(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
{
	// ¸ù¾Ý¶¥µã×ø±ê»­ËÄ±ßÐÎ
	POINT pts[] = { { (int)x1,(int)y1 },{ (int)x2,(int)y2 },{ (int)x3,(int)y3 },{ (int)x4,(int)y4 } };
	fillpolygon(pts, 4);
}

bool Floor::FitRule()	// ³õ²½ ¼ì²é°å¿éÀàÐÍÊÇ·ñ·ûºÏ¹æÔò
{
	// µÚÒ»Àà°å¿é³õÊ¼»¯
	if (mode & F1) {
		if (Prev->mode == F2_LEFT_UP ||
			Prev->mode == F2_RIGHT_DOWN ||
			Prev->mode == F3_LEFT_DOWN ||
			Prev->mode == F3_RIGHT_UP)
			return false;
		else if (mode == F1_LEFT_UP) {
			if (Prev->mode & F1) {
				if (Prev->mode == F1_RIGHT_DOWN)		// ·ÀÖ¹°å¿éÕÛ»Ø
					return false;
				else if (Prev->Prev != NULL && Prev->Prev->mode == F1_RIGHT_DOWN && (Prev->mode == F1_RIGHT_UP || Prev->mode == F1_LEFT_DOWN))	// ·ÀÖ¹°å¿éÓØ»Ø
					return false;
				// else 
			}
			else if (Prev->mode == F3_DOWN)	// ·ÀÖ¹°å¿éÕÛ»Ø
				return false;
			else if (Prev->Prev != NULL && Prev->mode == F3_UP && Prev->Prev->mode == F2_RIGHT_DOWN)	// ·ÀÖ¹°å¿éÓØ»Ø
				return false;
			// else
		}
		else if (mode == F1_LEFT_DOWN) {
			if (Prev->mode & F1) {
				if (Prev->mode == F1_RIGHT_UP) 	// ·ÀÖ¹°å¿éÕÛ»Ø
					return false;
				else if (Prev->Prev != NULL && Prev->Prev->mode == F1_RIGHT_UP && (Prev->mode == F1_LEFT_UP || Prev->mode == F1_RIGHT_DOWN))	// ·ÀÖ¹°å¿éÓØ»Ø
					return false;
				// else 
			}
			else if (Prev->mode == F2_UP) 	// ·ÀÖ¹°å¿éÕÛ»Ø
				return false;
			else if (Prev->Prev != NULL && Prev->mode == F2_DOWN && Prev->Prev->mode == F3_RIGHT_UP)	// ·ÀÖ¹°å¿éÓØ»Ø
				return false;
			// else
		}
		else if (mode == F1_RIGHT_UP) {
			if (Prev->mode & F1) {
				if (Prev->mode == F1_LEFT_DOWN) 	// ·ÀÖ¹°å¿éÕÛ»Ø
					return false;
				else if (Prev->Prev != NULL && Prev->Prev->mode == F1_LEFT_DOWN && (Prev->mode == F1_RIGHT_DOWN || Prev->mode == F1_LEFT_UP))	// ·ÀÖ¹°å¿éÓØ»Ø
					return false;
				// else 
			}
			else if (Prev->mode == F2_DOWN) 	// ·ÀÖ¹°å¿éÕÛ»Ø
				return false;
			else if (Prev->Prev != NULL && Prev->mode == F2_UP && Prev->Prev->mode == F3_LEFT_DOWN)	// ·ÀÖ¹°å¿éÓØ»Ø
				return false;
			// else
		}
		else if (mode == F1_RIGHT_DOWN) {
			if (Prev->mode & F1) {
				if (Prev->mode == F1_LEFT_UP) 	// ·ÀÖ¹°å¿éÕÛ»Ø
					return false;
				else if (Prev->Prev != NULL && Prev->Prev->mode == F1_LEFT_UP && (Prev->mode == F1_RIGHT_UP || Prev->mode == F1_LEFT_DOWN))	// ·ÀÖ¹°å¿éÓØ»Ø
					return false;
			}
			else if (Prev->mode == F3_UP) 	// ·ÀÖ¹°å¿éÕÛ»Ø
				return false;
			else if (Prev->Prev != NULL && Prev->mode == F3_DOWN && Prev->Prev->mode == F2_LEFT_UP)	// ·ÀÖ¹°å¿éÓØ»Ø
				return false;
			// else
		}
	}

	// µÚ¶þÀà°å¿é³õÊ¼»¯
	else if (mode & F2) {
		if (Prev->mode == F1_LEFT_UP ||
			Prev->mode == F1_RIGHT_DOWN ||
			Prev->mode == F3_UP ||
			Prev->mode == F3_DOWN)
			return false;
		else if (Prev->Prev != NULL && Prev->mode == F1_RIGHT_UP && Prev->Prev->mode == F3_DOWN)	// ·ÀÖ¹°å¿éÓØ»Ø
			return false;
		else if (Prev->Prev != NULL && Prev->mode == F1_LEFT_DOWN && Prev->Prev->mode == F3_UP)	// ·ÀÖ¹°å¿éÓØ»Ø
			return false;
		else if (mode == F2_UP) {
			if (Prev->mode == F1_LEFT_DOWN || Prev->mode == F2_DOWN) // ·ÀÖ¹°å¿é´íÎ»
				return false;
			else if (Prev->Prev != NULL && Prev->Prev->mode == F3_DOWN && (Prev->mode == F3_RIGHT_UP || Prev->mode == F3_LEFT_DOWN))	// ·ÀÖ¹°å¿éÓØ»Ø
				return false;
			else if (Prev->Prev != NULL && Prev->mode == F3_RIGHT_UP && Prev->Prev->mode == F1_LEFT_UP)	// ·ÀÖ¹°å¿éÓØ»Ø
				return false;
			else if (Prev->Prev != NULL && Prev->mode == F3_LEFT_DOWN && Prev->Prev->mode == F1_RIGHT_DOWN)	// ·ÀÖ¹°å¿éÓØ»Ø
				return false;
			else if (Prev->Prev != NULL && Prev->mode == F2_RIGHT_DOWN && Prev->Prev->mode == F1_LEFT_DOWN)	// ·ÀÖ¹°å¿éÓØ»Ø
				return false;
		}
		else if (mode == F2_DOWN) {
			if (Prev->mode == F1_RIGHT_UP || Prev->mode == F2_UP) // ·ÀÖ¹°å¿é´íÎ»
				return false;
			else if (Prev->Prev != NULL && Prev->Prev->mode == F3_UP && (Prev->mode == F3_RIGHT_UP || Prev->mode == F3_LEFT_DOWN))	// ·ÀÖ¹°å¿éÓØ»Ø
				return false;
			else if (Prev->Prev != NULL && Prev->mode == F3_RIGHT_UP && Prev->Prev->mode == F1_LEFT_UP)	// ·ÀÖ¹°å¿éÓØ»Ø
				return false;
			else if (Prev->Prev != NULL && Prev->mode == F3_LEFT_DOWN && Prev->Prev->mode == F1_RIGHT_DOWN)	// ·ÀÖ¹°å¿éÓØ»Ø
				return false;
			else if (Prev->Prev != NULL && Prev->mode == F2_LEFT_UP && Prev->Prev->mode == F1_RIGHT_UP)	// ·ÀÖ¹°å¿éÓØ»Ø
				return false;
		}
		else if (mode == F2_LEFT_UP) {
			if (Prev->mode == F2_RIGHT_DOWN || Prev->mode == F3_RIGHT_UP) // ·ÀÖ¹°å¿é´íÎ»
				return false;
			else if (Prev->Prev != NULL && Prev->mode == F3_LEFT_DOWN && Prev->Prev->mode == F1_RIGHT_DOWN)	// ·ÀÖ¹°å¿éÓØ»Ø
				return false;
			else if (Prev->Prev != NULL && Prev->mode == F1_RIGHT_UP && Prev->Prev->mode == F1_RIGHT_DOWN)	// ·ÀÖ¹°å¿éÓØ»Ø
				return false;
			else if (Prev->Prev != NULL && Prev->Prev->mode == F1_RIGHT_DOWN && (Prev->mode == F1_RIGHT_UP || Prev->mode == F1_LEFT_DOWN))	// ·ÀÖ¹°å¿éÓØ»Ø
				return false;
		}
		else if (mode == F2_RIGHT_DOWN) {
			if (Prev->mode == F3_LEFT_DOWN || Prev->mode == F2_LEFT_UP) // ·ÀÖ¹°å¿é´íÎ»
				return false;
			else if (Prev->Prev != NULL && Prev->mode == F3_RIGHT_UP && Prev->Prev->mode == F1_LEFT_UP)	// ·ÀÖ¹°å¿éÓØ»Ø
				return false;
			else if (Prev->Prev != NULL && Prev->mode == F1_LEFT_DOWN && Prev->Prev->mode == F1_LEFT_UP)	// ·ÀÖ¹°å¿éÓØ»Ø
				return false;
			else if (Prev->Prev != NULL && Prev->Prev->mode == F1_LEFT_UP && (Prev->mode == F1_RIGHT_UP || Prev->mode == F1_LEFT_DOWN))	// ·ÀÖ¹°å¿éÓØ»Ø
				return false;
		}
	}

	// µÚÈýÀà°å¿é³õÊ¼»¯
	else if (mode & F3) {
		if (Prev->mode == F1_LEFT_DOWN ||
			Prev->mode == F1_RIGHT_UP ||
			Prev->mode == F2_UP ||
			Prev->mode == F2_DOWN)
			return false;
		else if (Prev->Prev != NULL && Prev->mode == F1_RIGHT_DOWN && Prev->Prev->mode == F2_UP)	// ·ÀÖ¹°å¿éÓØ»Ø
			return false;
		else if (Prev->Prev != NULL && Prev->mode == F1_LEFT_UP && Prev->Prev->mode == F2_DOWN)	// ·ÀÖ¹°å¿éÓØ»Ø
			return false;
		else if (mode == F3_UP) {
			if (Prev->mode == F1_RIGHT_DOWN || Prev->mode == F3_DOWN) // ·ÀÖ¹°å¿é´íÎ»
				return false;
			else if (Prev->Prev != NULL && Prev->Prev->mode == F2_DOWN && (Prev->mode == F2_RIGHT_DOWN || Prev->mode == F2_LEFT_UP))	// ·ÀÖ¹°å¿éÓØ»Ø
				return false;
			else if (Prev->Prev != NULL && Prev->mode == F2_RIGHT_DOWN && Prev->Prev->mode == F1_LEFT_UP)	// ·ÀÖ¹°å¿éÓØ»Ø
				return false;
			else if (Prev->Prev != NULL && Prev->mode == F2_LEFT_UP && Prev->Prev->mode == F1_RIGHT_UP)	// ·ÀÖ¹°å¿éÓØ»Ø
				return false;
			else if (Prev->Prev != NULL && Prev->mode == F3_LEFT_DOWN && Prev->Prev->mode == F1_RIGHT_DOWN)	// ·ÀÖ¹°å¿éÓØ»Ø
				return false;
		}
		else if (mode == F3_DOWN) {
			if (Prev->mode == F1_LEFT_UP || Prev->mode == F3_UP) // ·ÀÖ¹°å¿é´íÎ»
				return false;
			else if (Prev->Prev != NULL && Prev->Prev->mode == F2_UP && (Prev->mode == F2_RIGHT_DOWN || Prev->mode == F2_LEFT_UP))	// ·ÀÖ¹°å¿éÓØ»Ø
				return false;
			else if (Prev->Prev != NULL && Prev->mode == F2_RIGHT_DOWN && Prev->Prev->mode == F1_LEFT_DOWN)	// ·ÀÖ¹°å¿éÓØ»Ø
				return false;
			else if (Prev->Prev != NULL && Prev->mode == F2_LEFT_UP && Prev->Prev->mode == F1_RIGHT_UP)	// ·ÀÖ¹°å¿éÓØ»Ø
				return false;
			else if (Prev->Prev != NULL && Prev->mode == F3_RIGHT_UP && Prev->Prev->mode == F1_LEFT_UP)	// ·ÀÖ¹°å¿éÓØ»Ø
				return false;
		}
		else if (mode == F3_LEFT_DOWN) {
			if (Prev->mode == F2_RIGHT_DOWN || Prev->mode == F3_RIGHT_UP) // ·ÀÖ¹°å¿é´íÎ»
				return false;
			else if (Prev->Prev != NULL && Prev->mode == F2_LEFT_UP && Prev->Prev->mode == F1_RIGHT_UP)	// ·ÀÖ¹°å¿éÓØ»Ø
				return false;
			else if (Prev->Prev != NULL && Prev->mode == F1_RIGHT_DOWN && Prev->Prev->mode == F1_RIGHT_UP)	// ·ÀÖ¹°å¿éÓØ»Ø
				return false;
			else if (Prev->Prev != NULL && Prev->Prev->mode == F1_RIGHT_UP && (Prev->mode == F1_RIGHT_DOWN || Prev->mode == F1_LEFT_UP))	// ·ÀÖ¹°å¿éÓØ»Ø
				return false;
		}
		else if (mode == F3_RIGHT_UP) {
			if (Prev->mode == F2_LEFT_UP || Prev->mode == F3_LEFT_DOWN) // ·ÀÖ¹°å¿é´íÎ»
				return false;
			else if (Prev->Prev != NULL && Prev->mode == F2_RIGHT_DOWN && Prev->Prev->mode == F1_LEFT_DOWN)	// ·ÀÖ¹°å¿éÓØ»Ø
				return false;
			else if (Prev->Prev != NULL && Prev->mode == F1_LEFT_UP && Prev->Prev->mode == F1_LEFT_DOWN)	// ·ÀÖ¹°å¿éÓØ»Ø
				return false;
			else if (Prev->Prev != NULL && Prev->Prev->mode == F1_LEFT_DOWN && (Prev->mode == F1_RIGHT_DOWN || Prev->mode == F1_LEFT_UP))	// ·ÀÖ¹°å¿éÓØ»Ø
				return false;
		}
	}
	/*   ½øÒ»²½ÅÐ¶Ï °å¿é×ø±êÊÇ·ñ·ûºÏ¹æÔò   */
	if (mode == F1_RIGHT_UP || mode == F2_UP) {
		dx = 1;
		dy = 0;
		dz = 0;
	}
	else if (mode == F1_LEFT_DOWN || mode == F2_DOWN) {
		dx = -1;
		dy = 0;
		dz = 0;
	}
	else if (mode == F1_LEFT_UP || mode == F3_UP) {
		dx = 0;
		dy = -1;
		dz = 0;
	}
	else if (mode == F1_RIGHT_DOWN || mode == F3_DOWN) {
		dx = 0;
		dy = 1;
		dz = 0;
	}
	else if (mode == F2_RIGHT_DOWN || mode == F3_RIGHT_UP) {
		dx = 0;
		dy = 0;
		dz = 1;
	}
	else if (mode == F2_LEFT_UP || mode == F3_LEFT_DOWN) {
		dx = 0;
		dy = 0;
		dz = -1;
	}

	// ¼ì²é°å¿éÊÇ·ñÓØ»Ø
	int dx0 = 0, dy0 = 0, dz0 = 0;
	if (this->Prev != NULL && this->Prev->Prev != NULL) {
		dx0 = dx + this->Prev->dx + this->Prev->Prev->dx;
		dy0 = dy + this->Prev->dy + this->Prev->Prev->dy;
		dz0 = dz + this->Prev->dz + this->Prev->Prev->dz;
		if ((dx0 == 0 && dy0 == 0 && (dz0 == 1 || dz0 == -1)) ||
			(dx0 == 0 && dz0 == 0 && (dy0 == 1 || dy0 == -1)) ||
			(dz0 == 0 && dy0 == 0 && (dx0 == 1 || dx0 == -1)))
			return false;
		if ((dx0 == -1 && dz0 == 1 && (dy0 == 1 || dy0 == -1)) ||
			(dx0 == 1 && dz0 == -1 && (dy0 == 1 || dy0 == -1)) ||
			(dx0 == -1 && dy0 == 1 && (dz0 == 1 || dz0 == -1)) ||
			(dx0 == 1 && dy0 == -1 && (dz0 == 1 || dz0 == -1)) ||
			(dz0 == 1 && dy0 == -1 && (dx0 == 1 || dx0 == -1)) ||
			(dz0 == -1 && dy0 == 1 && (dx0 == 1 || dx0 == -1)))
			return false;
		if ((dx0 == 1 && dy0 == 1 && dz0 == -1) ||
			(dx0 == -1 && dy0 == -1 && dz0 == 1))
			return false;
	}
	return true;
}

bool Floor::JudgeCoincidence()	// ¼ì²é°å¿éÊÇ·ñÖØºÏ
{
	POINT vertex[5];
	if (mode & F1) {
		vertex[0].x = (int)x - LENOFSIDE;
		vertex[0].y = (int)y - LENOFSIDE / 2;
		vertex[1].x = (int)x + LENOFSIDE;
		vertex[1].y = (int)y - LENOFSIDE / 2;
		vertex[2].x = (int)x - LENOFSIDE;
		vertex[2].y = (int)y + LENOFSIDE / 2;
		vertex[3].x = (int)x + LENOFSIDE;
		vertex[3].y = (int)y + LENOFSIDE / 2;
		vertex[4].x = (int)x;
		vertex[4].y = (int)y;
	}
	else if (mode & F2 || mode & F3) {
		vertex[0].x = (int)x - LENOFSIDE;
		vertex[0].y = (int)y;
		vertex[1].x = (int)x + LENOFSIDE;
		vertex[1].y = (int)y;
		vertex[2].x = (int)x;
		vertex[2].y = (int)y + LENOFSIDE;
		vertex[3].x = (int)x;
		vertex[3].y = (int)y - LENOFSIDE;
		vertex[4].x = (int)x;
		vertex[4].y = (int)y;
	}

	Floor* p = Prev;
	while (p->Prev != NULL) {
		p = p->Prev;
		for (int i = 0; i<5; i++) {
			if (p->mode & F1) {
				if (fabs((vertex[i].y - (int)p->y) + 0.5*((int)p->x - vertex[i].x)) <= LENOFSIDE + 1 &&
					fabs((vertex[i].y - (int)p->y) - 0.5*((int)p->x - vertex[i].x)) <= LENOFSIDE + 1) {
					create_bug = true;
					return false;
				}
			}
			else if (p->mode & F2) {
				if (fabs((vertex[i].y - (int)p->y) + 0.5*((int)p->x - vertex[i].x)) <= LENOFSIDE + 1 &&
					fabs(p->x - vertex[i].x) <= LENOFSIDE + 1) {
					create_bug = true;
					return false;
				}
			}
			else if (p->mode & F3) {
				if (fabs((vertex[i].y - (int)p->y) - 0.5*((int)p->x - vertex[i].x)) <= LENOFSIDE + 1 &&
					fabs(p->x - vertex[i].x) <= LENOFSIDE + 1) {
					create_bug = true;
					return false;
				}
			}
		}
	}
	return true;
}

void Floor::GetLocation()	// °å¿é×ø±ê
{
	// µÚÒ»Àà°å¿é×ø±ê
	if (mode & F1) {
		if (Prev->mode & F1) {
			if (Prev->mode == F1_LEFT_UP) {
				x = Prev->x - (2 * LENOFSIDE);
				y = Prev->y - (LENOFSIDE);
			}
			else if (Prev->mode == F1_LEFT_DOWN) {
				x = Prev->x - (2 * LENOFSIDE);
				y = Prev->y + (LENOFSIDE);
			}
			else if (Prev->mode == F1_RIGHT_UP) {
				x = Prev->x + (2 * LENOFSIDE);
				y = Prev->y - (LENOFSIDE);
			}
			else if (Prev->mode == F1_RIGHT_DOWN) {
				x = Prev->x + (2 * LENOFSIDE);
				y = Prev->y + (LENOFSIDE);
			}
		}
		else if (Prev->mode == F2_DOWN) {
			x = Prev->x - (2 * LENOFSIDE / 2);
			y = Prev->y + (int)(LENOFSIDE*1.5);
		}
		else if (Prev->mode == F2_UP) {
			x = Prev->x + (2 * LENOFSIDE / 2);
			y = Prev->y - (int)(LENOFSIDE*1.5);
		}
		else if (Prev->mode == F3_DOWN) {
			x = Prev->x + (2 * LENOFSIDE / 2);
			y = Prev->y + (int)(LENOFSIDE*1.5);
		}
		else if (Prev->mode == F3_UP) {
			x = Prev->x - (2 * LENOFSIDE / 2);
			y = Prev->y - (int)(LENOFSIDE*1.5);
		}
	}

	// µÚ¶þÀà°å¿é×ø±ê
	else if (mode & F2) {
		if (Prev->mode & F1) {
			if (Prev->mode == F1_RIGHT_UP) {
				x = Prev->x + (2 * LENOFSIDE / 2);
				y = Prev->y - (int)(1.5*LENOFSIDE);
			}
			else if (Prev->mode == F1_LEFT_DOWN) {
				x = Prev->x - (2 * LENOFSIDE / 2);
				y = Prev->y + (int)(1.5*LENOFSIDE);
			}
		}
		else if (Prev->mode & F2) {
			if (Prev->mode == F2_UP) {
				x = Prev->x;
				y = Prev->y - (2 * LENOFSIDE);
			}
			else if (Prev->mode == F2_DOWN) {
				x = Prev->x;
				y = Prev->y + (2 * LENOFSIDE);
			}
			else if (Prev->mode == F2_LEFT_UP) {
				x = Prev->x - (2 * LENOFSIDE);
				y = Prev->y - (LENOFSIDE);
			}
			else if (Prev->mode == F2_RIGHT_DOWN) {
				x = Prev->x + (2 * LENOFSIDE);
				y = Prev->y + (LENOFSIDE);
			}
		}
		else if (Prev->mode & F3) {
			if (Prev->mode == F3_RIGHT_UP) {
				x = Prev->x + (2 * LENOFSIDE);
				y = Prev->y;
			}
			else if (Prev->mode == F3_LEFT_DOWN) {
				x = Prev->x - (2 * LENOFSIDE);
				y = Prev->y;
			}
		}
	}

	// µÚÈýÀà°å¿é×ø±ê
	else if (mode & F3) {
		if (Prev->mode & F1) {
			if (Prev->mode == F1_RIGHT_DOWN) {
				x = Prev->x + (2 * LENOFSIDE / 2);
				y = Prev->y + (int)(1.5*LENOFSIDE);
			}
			else if (Prev->mode == F1_LEFT_UP) {
				x = Prev->x - (2 * LENOFSIDE / 2);
				y = Prev->y - (int)(1.5*LENOFSIDE);
			}
		}
		else if (Prev->mode & F2) {
			if (Prev->mode == F2_LEFT_UP) {
				x = Prev->x - (2 * LENOFSIDE);
				y = Prev->y;
			}
			else if (Prev->mode == F2_RIGHT_DOWN) {
				x = Prev->x + (2 * LENOFSIDE);
				y = Prev->y;
			}
		}
		else if (Prev->mode & F3) {
			if (Prev->mode == F3_UP) {
				x = Prev->x;
				y = Prev->y - (2 * LENOFSIDE);
			}
			else if (Prev->mode == F3_DOWN) {
				x = Prev->x;
				y = Prev->y + (2 * LENOFSIDE);
			}
			else if (Prev->mode == F3_RIGHT_UP) {
				x = Prev->x + (2 * LENOFSIDE);
				y = Prev->y - (LENOFSIDE);
			}
			else if (Prev->mode == F3_LEFT_DOWN) {
				x = Prev->x - (2 * LENOFSIDE);
				y = Prev->y + (LENOFSIDE);
			}
		}
	}
}

void Floor::lightup()
{
	on_gap = 20;
}

bool Floor::end(double speed)
{
	if ((int)(20.0 / speed) == end_gap)
		return true;
	return false;
}

void Floor::end()
{
	end_gap = 1;
}