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




obj playermovement(obj);


int main()
{

	system("pause");
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