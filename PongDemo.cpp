#include <stdio.h>
#include <stdlib.h>



int main()
{
	int choice = 0;
	while (choice <= 5) //�i�J��ܰj�� ��ܧ�3 4 5���٥i�H�^��j���~���ܶ}�lor���}
	{
		printf("�w��Ө�Pong, �п�ܤU�C�ﶵ\n\n"
			"1.�}�l�C��\n2.���}�C��\n3.��ܵ����j�p\n4.��ܵ����C��\n5.���������\n");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:                          //��ܤ@ �}�l�C��
			printf("�}�l\n");
			choice = 6;      //��ܶ}�l���X��ܰj��
			break;
		case 2:                          //��ܤG ���}�C��
			printf("���}\n");
			choice = 6;      //������}���X��ܰj��
			break;
		case 3:                          //��ܤT ��ܵ����j�p
			int size;
			printf("��ܵ����j�p(1.720*480,2.800*600,3.1280*720)\n");
			scanf("%d", &size);
			if (size == 1)
				printf("�����j�p�ܧ� 720*480\n");
			if (size == 2)
				printf("�����j�p�ܧ� 800*600\n");
			if (size == 3)
				printf("�����j�p�ܧ� 1280*720\n");
			
			break;
		case 4:                          //��ܥ| ��ܵ����C��
			int R, G, B;
			printf("�п�J�Q�n��R G B��\n");
			scanf("%d", &R);
			scanf("%d", &G);
			scanf("%d", &B);
			printf("�w�N�ù��C��אּR=%d G=%d B=%d\n", R, G, B);
			break;
		case 5:                          //��ܤ� ���������
			int d;
			printf("�п��������(²��:1,���q:2,�x��:3)\n");
			scanf("%d", &d);
			if (d == 1)
				printf("�w�N���׽վ㬰 ²��\n");
			if (d == 2)
				printf("�w�N���׽վ㬰 ���q\n");
			if (d == 3)
				printf("�w�N���׽վ㬰 �x��\n");
			break;
		}
	}
	system("pause");
	return 0;
}

