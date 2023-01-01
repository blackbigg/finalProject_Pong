#include <stdio.h>
#include <stdlib.h>
#include <easyx.h>

#define width 800
#define height 600

typedef struct
{
	int x;
	int y;
	int widthsize;
	int heightsize;
}obj;

typedef struct
{
	int x;
	int y;
	int rad;
	int speedx;
	int speedy;
}ball;


void showrec(obj ex);
obj playermovement(obj);
void showball(ball);

int main()
{
	obj player = { -300,0,10,40 };
	obj enemy = { 300,0,10,40 };
	ball ball = { 0,0,10,5,5 };

	initgraph(width, height, NULL);
	setorigin(width / 2, height / 2);
	setbkcolor(RGB(164, 225, 202));
	while (true)
	{
		player = playermovement(player);
		showrec(player);
		showrec(enemy);
		showball(ball);
		Sleep(20);
		cleardevice();
	}
	system("pause");
	closegraph();
	return 0;
}


obj playermovement(obj ex)
{
	if (GetAsyncKeyState(VK_UP))
	{
		ex.y -= 10;
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		ex.y += 10;
	}
	return ex;
}
void showrec(obj ex)
{
	solidrectangle(ex.x - (ex.widthsize), ex.y - (ex.heightsize), ex.x + (ex.widthsize), ex.y + (ex.heightsize));
}
void showball(ball ex)
{
	solidcircle(ex.x, ex.y, ex.rad);
}