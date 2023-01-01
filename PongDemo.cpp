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



void showrec(obj ex);
obj playermovement(obj);


int main()
{
	obj player = { -300,0,10,40 };
	obj enemy = { 300,0,10,40 };
	initgraph(width, height, NULL);
	setorigin(width / 2, height / 2);
	setbkcolor(RGB(164, 225, 202));
	while (true)
	{
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
	if (GetAsyncKeyState(VK_LEFT))
	{
		ex.x -= 10;
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		ex.x += 10;
	}
	return ex;
}
void showrec(obj ex)
{
	solidrectangle(ex.x - (ex.widthsize), ex.y - (ex.heightsize), ex.x + (ex.widthsize), ex.y + (ex.heightsize));
}