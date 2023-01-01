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
	int speed;
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
ball ballmove(ball, obj, obj);
ball ballacceleration(ball, obj);
int main()
{
	obj player = { -300,0,10,40 };
	obj enemy = { 300,0,10,40 };
	ball ball = { 0,0,10,10,0 };

	initgraph(width, height, NULL);
	BeginBatchDraw();
	setorigin(width / 2, height / 2);
	setbkcolor(RGB(164, 225, 202));
	while (true)
	{
		player = playermovement(player);
		ball = ballmove(ball, player, enemy);
		showrec(player);
		showrec(enemy);
		showball(ball);
		FlushBatchDraw();
		Sleep(20);
		cleardevice();
	}
	system("pause");
	EndBatchDraw();
	closegraph();
	return 0;
}


obj playermovement(obj ex)
{
	ex.speed = 0;
	if (GetAsyncKeyState(VK_UP))
	{
		ex.speed = -10;
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		ex.speed = 10;
	}
	ex.y += ex.speed;
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
ball ballmove(ball ex, obj player, obj enemy)
{

	ex.x += ex.speedx;
	ex.y += ex.speedy;
	if (abs(ex.x) == width / 2 - ex.rad ||
		(ex.x - ex.rad == player.x + player.widthsize) && (player.y - player.heightsize <= ex.y && ex.y <= player.y + player.heightsize))
	{
		ex = ballacceleration(ex, player);
		ex.speedx *= -1;
	}
	if ((ex.x + ex.rad == enemy.x - enemy.widthsize) && (enemy.y - enemy.heightsize <= ex.y && ex.y <= enemy.y + enemy.heightsize))
	{
		ex = ballacceleration(ex, enemy);
		ex.speedx *= -1;
	}
	if (ex.y <= -300 + ex.rad || ex.y >= 300 - ex.rad ||
		(ex.y + ex.rad == player.y - player.heightsize || ex.y - ex.rad == player.y + player.heightsize) && player.x - player.widthsize <= ex.x && ex.x <= player.x + player.widthsize ||
		(ex.y + ex.rad == enemy.y - enemy.heightsize || ex.y - ex.rad == enemy.y + enemy.heightsize) && enemy.x - enemy.widthsize <= ex.x && ex.x <= enemy.x + enemy.widthsize
		)
	{
		ex.speedy *= -1;
	}
	return ex;
}
	ball ballacceleration(ball ball, obj obj)
	{
		if (obj.speed > 0)
		{
			ball.speedy += 3;
		}
		if (obj.speed < 0)
		{
			ball.speedy -= 3;
		}
		return ball;
	}
