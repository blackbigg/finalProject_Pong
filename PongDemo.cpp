#include <stdio.h>
#include <stdlib.h>
#include <easyx.h>


int width = 800;
int height = 600;
int R = 164, G = 225, B = 202;
int Difficulty = 3;
int playgame = 0;

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
obj enemyAI(obj, int, ball);
int main()
{
	int choice = 0;
	while (choice <= 5) //進入選擇迴圈 選擇完3 4 5後還可以回到迴圈繼續選擇開始or離開
	{
		printf("Welcome to Pong Game select\n\n"
			"1.Start\n2.Quit\n3.Window Size\n4.Window Color\n5.Difficulty\n");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:                          //選擇一 開始遊戲
			
			choice = 6;      //選擇開始跳出選擇迴圈
			playgame = 1;
			break;
		case 2:                          //選擇二 離開遊戲
			
			choice = 6;      //選擇離開跳出選擇迴圈
			break;
		case 3:                          //選擇三 選擇視窗大小
			int size;
			printf("Choose Window Size(1. 720*480 , 2. 800*600 , 3. 1280*720)\n");
			scanf("%d", &size);
			if (size == 1)
			{
				width = 720;
				height = 480;
			}
			if (size == 2)
			{
				width = 800;
				height = 600;
			}
			if (size == 3)
			{
				width = 1280;
				height = 720;
			}
			break;
		case 4:                          //選擇四 選擇視窗顏色
			printf("Input RGB Value\n");
			scanf("%d", &R);
			scanf("%d", &G);
			scanf("%d", &B);
			break;
		case 5:                          //選擇五 選擇難易度
			int d;
			printf("Choose(1.Easy,2.Normal,3.Hrd)\n");
			scanf("%d", &d);
			if (d == 1)
				Difficulty = 1;
			if (d == 2)
				Difficulty = 2;
			if (d == 3)
				Difficulty = 3;
			break;
		}
	}
	obj player = { -(width * 3 / 8),0,10,40 };
	obj enemy = { (width * 3 / 8),0,10,40,10 };
	ball ball = { 0,0,10,0,0 ,1 };

	initgraph(width, height, EX_SHOWCONSOLE);
	BeginBatchDraw();
	settextstyle(50, 0, 0);
	setorigin(width / 2, height / 2);
	setbkcolor(RGB(R, G, B));
	if (playgame == 1)
	{
		while (true)
		{
			line(0, -(height / 2), 0, (height / 2));
			player = playermovement(player);
			enemy = enemyAI(enemy, Difficulty, ball);
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
	}

	EndBatchDraw();
	closegraph();
	return 0;
}


obj playermovement(obj player)
{
	player.speed = 0;
	if (player.y - player.heightsize > -(height / 2))
	{
		if (GetAsyncKeyState('W'))
		{
			player.speed = -10;
		}
	}
	if (player.y + player.heightsize < (height / 2))
	{
		if (GetAsyncKeyState('S'))
		{
			player.speed = 10;
		}
	}
	player.y += player.speed;
	return player;
}
void showrec(obj obj)
{
	solidrectangle(obj.x - (obj.widthsize), obj.y - (obj.heightsize), obj.x + (obj.widthsize), obj.y + (obj.heightsize));
}
void showball(ball ball)
{
	solidcircle(ball.x, ball.y, ball.rad);
}
ball ballmove(ball ball, obj player, obj enemy)
{

	ball.x += ball.speedx;
	ball.y += ball.speedy;
	if ((ball.x - ball.rad == player.x + player.widthsize) && (player.y - player.heightsize <= ball.y && ball.y <= player.y + player.heightsize))
	{
		ball = ballacceleration(ball, player);
		ball.speedx *= -1;
	}
	if ((ball.x + ball.rad == enemy.x - enemy.widthsize) && (enemy.y - enemy.heightsize <= ball.y && ball.y <= enemy.y + enemy.heightsize))
	{
		ball = ballacceleration(ball, enemy);
		ball.speedx *= -1;
	}
	if (ball.y <= -(height / 2) + ball.rad || ball.y >= (height / 2) - ball.rad ||
		(ball.y + ball.rad == player.y - player.heightsize || ball.y - ball.rad == player.y + player.heightsize) && player.x - player.widthsize <= ball.x && ball.x <= player.x + player.widthsize ||
		(ball.y + ball.rad == enemy.y - enemy.heightsize || ball.y - ball.rad == enemy.y + enemy.heightsize) && enemy.x - enemy.widthsize <= ball.x && ball.x <= enemy.x + enemy.widthsize
		)
	{
		ball.speedy *= -1;
	}
	return ball;
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
		
		if (GetAsyncKeyState(VK_SPACE))
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
	
	
			if (enemy.speed > 0)
			{
				ball.speedy = 5;
			}
			if (enemy.speed < 0)
			{
				ball.speedy = -5;
			}
			ball.speedx = -10;
			ball.ballbelong = 0;
		
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
obj enemyAI(obj enemy, int difficluty, ball ball)
{
	if (difficluty == 1)
	{
		enemy.speed = 0;
	}
	if (difficluty == 2)
	{

		if (enemy.y - enemy.heightsize == -(height / 2))
		{
			enemy.speed = 10;
		}
		if (enemy.y + enemy.heightsize == height / 2)
		{
			enemy.speed = -10;
		}
		enemy.y += enemy.speed;
	}
	if (difficluty == 3)
	{
		if ((ball.speedx==0||ball.speedy==0) && ball.ballbelong != 2)
		{

				if (ball.y<enemy.y)
				{
					enemy.y += -10;
				}
				if (ball.y>enemy.y)
				{
					enemy.y += 10;
				}
			
		}
		if (enemy.y - enemy.heightsize > -(height / 2)&&ball.speedy<0&&ball.ballbelong!=2)
		{
			if (ball.speedy>-10)
			{
			enemy.y += ball.speedy;
			}
			else
			{
				enemy.y += -10;
			}
		}
		if (enemy.y + enemy.heightsize < (height / 2)&&ball.speedy>0&& ball.ballbelong != 2)
		{
			if (ball.speedy < 10)
			{
				enemy.y += ball.speedy;
			}
			else
			{
				enemy.y += 10;
			}
		}
	}

	return enemy;
}
