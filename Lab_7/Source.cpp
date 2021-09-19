#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
char cursor(int x, int y) {
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[2]; COORD c = { x,y }; DWORD num_read;
	if (
		!ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read))

		return '\0';
	else
		return buf[0];

}
void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void draw_ship(int x, int y)
{
	gotoxy(x, y); printf(" <-0-> ");
}
void draw_bullet(int x, int y)
{
	gotoxy(x, y); printf("^");
}
void clear_bullet(int x, int y)
{
	gotoxy(x, y); printf(" ");
}
void spawn()
{
	gotoxy((rand() % 61) + 10, (rand() % 4) + 2);
	printf("*");
}

int main()
{
	char ch = '.';
	int x = 38, y = 20;
	int bx, by, i;
	int bullet = 0;
	int scores = 0;
	srand(time(NULL));
	gotoxy(75, 1);
	printf("%d", scores);
	draw_ship(x, y);
	spawn();
	do {
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a') { draw_ship(--x, y); }
			if (ch == 's') { draw_ship(++x, y); }
			if (bullet != 1 && ch == ' ') { bullet = 1; bx = x + 3; by = y - 1; }
			fflush(stdin);
		}
		if (bullet == 1) {

			clear_bullet(bx, by);
			if (by == 2) { bullet = 0; }
			else {
				if (cursor(bx, by - 1) == '*') {
					scores++;
					gotoxy(75, 1);
					printf("%d", scores);
					draw_bullet(bx, --by);
					Beep(700, 100);
					clear_bullet(bx, by);
					bullet = 0;
					spawn();
				}
				else { draw_bullet(bx, --by); }
			}

		}

		Sleep(100);
	} while (ch != 'x');
	return 0;
}