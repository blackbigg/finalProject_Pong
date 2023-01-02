#include <stdio.h>
#include <stdlib.h>



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
	system("pause");
	return 0;
}

