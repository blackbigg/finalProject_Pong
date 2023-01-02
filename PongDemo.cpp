#include <stdio.h>
#include <stdlib.h>
#include <easyx.h>


#define width 720
#define height 480
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
	int ballbelong;
	int playerscore;
	int enemyscore;
}ball;


void showrec(obj ex);
obj playermovement(obj);
void showball(ball);
ball ballmove(ball, obj, obj);
ball ballacceleration(ball, obj);
ball ballserve(ball, obj, obj);
void playerscore(ball);
void enemyscore(ball);
void vic(obj);
int main()
{
int choice = 0;
	while (choice <= 5) //進入選擇迴圈 選擇完3 4 5後還可以回到迴圈繼續選擇開始or離開
	{
		printf("歡迎來到Pong, 請選擇下列選項\n\n"
			"1.開始遊戲\n2.離開遊戲\n3.選擇視窗大小\n4.選擇視窗顏色\n5.選擇難易度\n");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:                          //選擇一 開始遊戲
			printf("開始\n");
			choice = 6;      //選擇開始跳出選擇迴圈
			break;
		case 2:                          //選擇二 離開遊戲
			printf("離開\n");
			choice = 6;      //選擇離開跳出選擇迴圈
			break;
		case 3:                          //選擇三 選擇視窗大小
			int size;
			printf("選擇視窗大小(1.720*480,2.800*600,3.1280*720)\n");
			scanf("%d", &size);
			if (size == 1)
				printf("視窗大小變更為 720*480\n");
			if (size == 2)
				printf("視窗大小變更為 800*600\n");
			if (size == 3)
				printf("視窗大小變更為 1280*720\n");
			
			break;
		case 4:                          //選擇四 選擇視窗顏色
			int R, G, B;
			printf("請輸入想要的R G B值\n");
			scanf("%d", &R);
			scanf("%d", &G);
			scanf("%d", &B);
			printf("已將螢幕顏色改為R=%d G=%d B=%d\n", R, G, B);
			break;
		case 5:                          //選擇五 選擇難易度
			int d;
			printf("請選擇難易度(簡單:1,普通:2,困難:3)\n");
			scanf("%d", &d);
			if (d == 1)
				printf("已將難度調整為 簡單\n");
			if (d == 2)
				printf("已將難度調整為 普通\n");
			if (d == 3)
				printf("已將難度調整為 困難\n");
			break;
		}
	}
	obj player = { -(width * 3 / 8),0,10,40 };
	obj enemy = { (width * 3 / 8),0,10,40 };
	ball ball = { 0,0,10,10,0 };

	initgraph(width, height, EX_SHOWCONSOLE);
	BeginBatchDraw();
	settextstyle(50, 0, 0);
	setorigin(width / 2, height / 2);
	setbkcolor(RGB(164, 225, 202));

	while (true)
	{
		line(0, -(height / 2), 0, (height / 2));
		player = playermovement(player);
		ball = ballserve(ball, player, enemy);
		ball = ballmove(ball, player, enemy);
		showrec(player);
		showrec(enemy);
		showball(ball);
		playerscore(ball);
		enemyscore(ball);
		FlushBatchDraw();
		Sleep(20);
		cleardevice();
		if (ball.playerscore == 10)
		{
			vic(player);
			
			break;
		}
		else if (ball.enemyscore == 10)
		{
			vic(enemy);
			
			break;
		}
	}
	EndBatchDraw();
	closegraph();
	return 0;
}


obj playermovement(obj ex)
{
	ex.speed = 0;
	if (ex.y - ex.heightsize >= -(height / 2))
	{
		if (GetAsyncKeyState('W'))
		{
			ex.speed = -10;
		}
	}
	if (ex.y + ex.heightsize <= (height / 2))
	{
		if (GetAsyncKeyState('S'))
		{
			ex.speed = 10;
		}
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
	if ((ex.x - ex.rad == player.x + player.widthsize) && (player.y - player.heightsize <= ex.y && ex.y <= player.y + player.heightsize))
	{
		ex = ballacceleration(ex, player);
		ex.speedx *= -1;
	}
	if ((ex.x + ex.rad == enemy.x - enemy.widthsize) && (enemy.y - enemy.heightsize <= ex.y && ex.y <= enemy.y + enemy.heightsize))
	{
		ex = ballacceleration(ex, enemy);
		ex.speedx *= -1;
	}
	if (ex.y <= -(height / 2) + ex.rad || ex.y >= (height / 2) - ex.rad ||
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
	if (obj.speed > 0 && ball.ballbelong == 0)
	{
		ball.speedy += 3;
	}
	if (obj.speed < 0 && ball.ballbelong == 0)
	{
		ball.speedy -= 3;
	}
	return ball;
}
ball ballserve(ball ball, obj player, obj enemy)
{
	if (ball.x == -(width / 2))
	{
		Sleep(50);
		ball.enemyscore += 1;
		ball.speedx = 0;
		ball.speedy = 0;
		ball.ballbelong = 1;
	}
	if (ball.x == (width / 2))
	{
		Sleep(50);
		ball.playerscore += 1;
		ball.speedx = 0;
		ball.speedy = 0;
		ball.ballbelong = 2;
	}
	if (ball.ballbelong == 1)
	{
		ball.x = player.x + player.widthsize + ball.rad;
		ball.y = player.y;
		if (GetAsyncKeyState('D'))
		{
			if (player.speed > 0)
			{
				ball.speedy = 5;
			}
			if (player.speed < 0)
			{
				ball.speedy = -5;
			}
			ball.speedx = 10;
			ball.ballbelong = 0;
		}
	}
	else if (ball.ballbelong == 2)
	{
		ball.x = enemy.x - enemy.widthsize - ball.rad;
		ball.y = enemy.y;
		if (GetAsyncKeyState(VK_LEFT))
		{
			if (player.speed > 0)
			{
				ball.speedy = 5;
			}
			if (player.speed < 0)
			{
				ball.speedy = -5;
			}
			ball.speedx = -10;
			ball.ballbelong = 0;
		}
	}

	return ball;
}
void playerscore(ball ball)
{
	char charsocre = ball.playerscore + '0';
	outtextxy(-(width * 1 / 8 + 25), -(height * 3 / 8), charsocre);
}
void enemyscore(ball ball)
{
	char charsocre = ball.enemyscore + '0';
	outtextxy((width * 1 / 8), -(height * 3 / 8), charsocre);
}
void vic(obj obj)
{
	for (int i = 0; i < 5; i++)
	{
		for (int r = 10; r <= 300; r += 5)
		{
			circle(obj.x, obj.y, r);
			FlushBatchDraw();
			Sleep(10);
			cleardevice();
		}
	}

}

