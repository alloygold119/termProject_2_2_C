#include "curses.h"
#include "panel.h"
#include <stdlib.h>
#include <time.h>


WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);
WINDOW *ground();
WINDOW *bomb_lv2();
WINDOW *bomb_lv1(int y, int x);

int main(int argc, char *argv[])
{
	WINDOW *my_win, *ground_win, *bomb_1;
	int startx, starty, width, height; //캐릭터와 관련된 변수
	int x_b, y_b, *arr; //폭탄에 관한 변수

	int ch, cnt = 0;

	initscr();
	cbreak();
	start_color();
	srand((unsigned)time(NULL));


	keypad(stdscr, TRUE);

	height = 1; //캐릭터 크기
	width = 3;
	starty = (LINES - height) / 2 ; //좌측하단 ((LINES  - height), 0) ; 중앙 ((LINES - height)/2, (COLS - width) /2); 
	startx = (COLS - width) / 2 ;
	printw("Press F1 to exit");
	refresh();
	curs_set(0); //커서 숨기기

	ground_win = ground();

	my_win = create_newwin(height, width, starty, startx);
	while ((ch = getch()) != KEY_F(1)) //캐릭터의 생성과 이동
	{

		switch (ch)
		{
		case KEY_LEFT:
			if (startx == 0)
			{
				startx = COLS - width + 1;
			}
			destroy_win(my_win);
			my_win = create_newwin(height, width, starty, --startx);
			break;
		case KEY_RIGHT:
			if (startx == COLS - width)
			{
				startx = -1;
			}
			destroy_win(my_win);
			my_win = create_newwin(height, width, starty, ++startx);
			break;
		case KEY_UP:
			if (starty == 1)
			{
				starty = (LINES - height);
			}

			destroy_win(my_win);
			my_win = create_newwin(height, width, --starty, startx);
			break;
		case KEY_DOWN:
			if (starty == (LINES - height - 1))
			{
				starty = 0;
			}
			destroy_win(my_win);
			my_win = create_newwin(height, width, ++starty, startx);
			break;
		}
		++cnt;
	}
	endwin();

	return 0;
}

WINDOW *create_newwin(int height, int width, int starty, int startx)
{
	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	wprintw(local_win, "i-i\n");

	wrefresh(local_win);

	return local_win;
}

void destroy_win(WINDOW *local_win)
{
	wclear(local_win);
	wrefresh(local_win);
	delwin(local_win);
}

WINDOW *ground()
{
	WINDOW *local_win;
	int i;

	local_win = newwin(1, COLS, LINES -1 , 0);
	for (i = 0; i < COLS; i++)
	{
		wprintw(local_win, "+");
	}
	wrefresh(local_win);

	return local_win;
}


WINDOW *bomb_lv1(int y, int x)
{
	WINDOW *local_win;

	local_win = newwin(1, 1, y, x);

	wprintw(local_win, "*");
	wrefresh(local_win);

	return local_win;
}

