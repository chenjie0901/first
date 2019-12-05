#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <malloc.h>
#include <time.h>
#include <stdlib.h>
void setmouth(int x, int y);//���ù��
void background();//��������
void setcolour(int a);//������ɫ
void init();//��ʼ��
void hidemouth();//���ع��
void startfood();//��ʼ����ʳ��
void startsnack();//��ʼ����С��
void snackmove(int, int);//С���ƶ�
int checksnack(int);//С����ײ���
void snackdie();//С������
void showing();//������µ�show
void screenRefresh(int);//��Ļˢ��
void newfood();//������ʳ��
void updategoal();//���µ÷�
int movedire(int, int);//��ȡС�ߵ��ƶ�����
int snacklength = 3;//С�߳���
int snackhead = 2;//��ͷ
int snacktail = 0;//��β
int MaxLine = 40, MaxLie = 40;//�����������������
//�ṹ�屣��������������
struct map {
	int colour;
	int kind;
	char* display;
}
show[40][40], //չʾ��ͼ
wall = { 0x6C,1,"��" },//ǽ��
livearea = { 0x7F,2,"��" },//С�߻����
food = { 0x7C,3,"��" },//ʳ��
snack = { 0x7A,4,"��" };//С�����������

struct SnackMap
{
	int x;
	int y;

}SnackSite[100], FoodSite;

/***************************************
				������
****************************************/

int main()
{
	int olddirection = 'w'; //��ʼ�����ź�
	int newdirection = 0;//��ȡ�����ź�
	init();//��ʼ��

	setmouth(60, 0);
	setcolour(0xF0);
	printf("\n�÷֣�");
	printf("%d\n", snacklength - 3);
	printf("���л�ΪӢ�����뷨\n");
	printf("W A S D���ֱ��ʾ���� �� �� ��\n");
	printf("Copyright [2019.12.03] by [���ѧԺ]		");

	while (1) {
		if (_kbhit()) {  //��⻺�������Ƿ�������
			newdirection = tolower(_getch());  //���������е��������ַ�����ʽ����
			if (newdirection == 27) {
				break;
			}
			else {
				//��ȡС���µ��ƶ�����
				newdirection = movedire(olddirection, newdirection);
				if (newdirection != olddirection)
				{
					olddirection = newdirection;
				}
			}
		}
		screenRefresh(newdirection);
		Sleep(10);
	}
	return 0;
}
//���µ÷�
void updategoal()
{
	setcolour(0xF0);
	setmouth(60, 0);
	printf("\n�÷֣�%d", snacklength - 3);
}
//��ײ���
int checksnack(int newdirection)
{
	switch (newdirection)
	{
	case 'w':
		if ((show[SnackSite[snackhead].x - 1][SnackSite[snackhead].y].kind) == 1)
		{
			snackdie();
			return 0;
		}
		else if ((show[SnackSite[snackhead].x - 1][SnackSite[snackhead].y].kind) == 4)
		{
			snackdie();
			return 0;
		}
		else if ((show[SnackSite[snackhead].x - 1][SnackSite[snackhead].y].kind) == 3)
		{
			return 1;
		}
		else {
			return 2;

		}
		break;
	case 's':
		if ((show[SnackSite[snackhead].x + 1][SnackSite[snackhead].y].kind) == 1)
		{
			snackdie();
			return 0;
		}
		else if ((show[SnackSite[snackhead].x + 1][SnackSite[snackhead].y].kind) == 4)
		{
			snackdie();
			return 0;
		}
		else if ((show[SnackSite[snackhead].x + 1][SnackSite[snackhead].y].kind) == 3)
		{
			return 1;
		}
		else {
			return 2;
		}
		break;
	case 'a':
		if ((show[SnackSite[snackhead].x][SnackSite[snackhead].y - 1].kind) == 1)
		{
			snackdie();
			return 0;
		}
		else if ((show[SnackSite[snackhead].x][SnackSite[snackhead].y - 1].kind) == 4)
		{
			snackdie();
			return 0;
		}
		else if ((show[SnackSite[snackhead].x][SnackSite[snackhead].y - 1].kind) == 3)
		{
			return 1;
		}
		else {
			return 2;
		}
		break;
	case 'd':
		if ((show[SnackSite[snackhead].x][SnackSite[snackhead].y + 1].kind) == 1)
		{
			snackdie();
			return 0;
		}
		else if ((show[SnackSite[snackhead].x][SnackSite[snackhead].y + 1].kind) == 4)
		{
			snackdie();
			return 0;
		}
		else if ((show[SnackSite[snackhead].x][SnackSite[snackhead].y + 1].kind) == 3)
		{
			return 1;
		}
		else {
			return 2;
		}
		break;

	}
}

//������ʳ��
void newfood()
{
	srand((unsigned)time(NULL));
	FoodSite.x = rand() % 38 + 1;
	FoodSite.y = rand() % 38 + 1;
}

//ˢ����Ļ
void screenRefresh(int newdirection)
{
	int re = 0;
	int i = 0;
	re = checksnack(newdirection);
	snackmove(newdirection, re);
	background();
	show[FoodSite.x][FoodSite.y] = food;
	for (i = 0; i <= snackhead; i++)
	{
		if (i == snackhead) {
			show[SnackSite[i].x][SnackSite[i].y] = snack;
			show[SnackSite[i].x][SnackSite[i].y].colour = 0x75;

		}
		else {
			show[SnackSite[i].x][SnackSite[i].y] = snack;
		}

	}

	showing();
	if (re == 1)
	{
		snacklength++;
		updategoal();
		newfood();
	}


}
/*********************************************
				��ȡ���µķ���
**********************************************/
int movedire(int olddirection, int newdirection)
{
	if (newdirection == 'w' || newdirection == 'a' || newdirection == 's' || newdirection == 'd')
	{

		return newdirection;
	}
	else {
		return olddirection;
	}

}

/**********************************
		  չʾ���µ�show
*********************************/

void showing()
{
	int line, lie;
	for (line = 0; line < MaxLine; line++)
	{
		for (lie = 0; lie < MaxLie; lie++)
		{
			setmouth(line, lie);
			setcolour(show[line][lie].colour);
			printf("%s", show[line][lie].display);

		}
	}

}

/******************************************
			С������
*******************************************/


void snackdie()
{
	setmouth(20, 5);
	printf("Game over! �������������Ϸ��");
	Sleep(5000);
	_getch();
	exit(0);
}

//С���ƶ�
void snackmove(int newdirection, int re)
{
	int i = 0;

	switch (newdirection)
	{
	case 'w':
		for (i = 0; i < snackhead; i++) {
			SnackSite[i].x = SnackSite[i + 1].x;
			SnackSite[i].y = SnackSite[i + 1].y;
		}
		SnackSite[snackhead].x -= 1;
		if (re == 1)
		{
			snackhead += 1;
			SnackSite[snackhead].x = SnackSite[snackhead - 1].x - 1;
			SnackSite[snackhead].y = SnackSite[snackhead - 1].y;

		}
		break;
	case 's':
		for (i = 0; i < snackhead; i++) {
			SnackSite[i].x = SnackSite[i + 1].x;
			SnackSite[i].y = SnackSite[i + 1].y;
		}
		SnackSite[snackhead].x += 1;
		if (re == 1)
		{
			snackhead += 1;
			SnackSite[snackhead].x = SnackSite[snackhead - 1].x + 1;
			SnackSite[snackhead].y = SnackSite[snackhead - 1].y;

		}
		break;
	case 'a':
		for (i = 0; i < snackhead; i++) {
			SnackSite[i].x = SnackSite[i + 1].x;
			SnackSite[i].y = SnackSite[i + 1].y;
		}
		SnackSite[snackhead].y -= 1;
		if (re == 1)
		{
			snackhead += 1;
			SnackSite[snackhead].x = SnackSite[snackhead - 1].x;
			SnackSite[snackhead].y = SnackSite[snackhead - 1].y - 1;

		}
		break;
	case 'd':
		for (i = 0; i < snackhead; i++) {
			SnackSite[i].x = SnackSite[i + 1].x;
			SnackSite[i].y = SnackSite[i + 1].y;
		}
		SnackSite[snackhead].y += 1;
		if (re == 1)
		{
			snackhead += 1;
			SnackSite[snackhead].x = SnackSite[snackhead - 1].x;
			SnackSite[snackhead].y = SnackSite[snackhead - 1].y + 1;

		}
		break;

	}

}



//��ʼʳ��


void startfood()
{
	FoodSite.x = 5;
	FoodSite.y = 10;
	show[5][10] = food;
}



//��ʼС��

void startsnack()
{
	SnackSite[0].x = 35;
	SnackSite[0].y = 13;
	SnackSite[1].x = 35;
	SnackSite[1].y = 12;
	SnackSite[2].x = 35;
	SnackSite[2].y = 11;
	show[35][11] = snack;
	show[35][11].colour = 0x75;
	show[35][12] = snack;
	show[35][13] = snack;
}

/*******************************
	��ʼ������show�ṹ������
*******************************/

void init()
{
	//���ô��ڴ�С
	system("mode con:cols=140 lines=50");
	//���ع��
	hidemouth();
	//���ɱ���ͼ
	background();
	//������ʼʳ��
	startfood();
	//������ʼС������
	startsnack();
	//��ʾ
	showing();
}


/**************************************
			���ɱ���ͼ
**************************************/
void background()
{
	int line, lie;
	for (line = 0; line < MaxLine; line++)
	{
		for (lie = 0; lie < MaxLie; lie++)
		{
			setmouth(line, lie);
			if (lie == 0 || lie == MaxLie - 1 || line == 0 || line == MaxLine - 1) {
				show[line][lie] = wall;
			}
			else {
				show[line][lie] = livearea;
			}

		}
	}
}

/********************************
		������λ��
*********************************/

void setmouth(int x, int y)
{
	COORD coord;
	coord.X = y * 2;  //��3��
	coord.Y = x;  //��3��
	//��ȡ����̨���������
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	//���ù��λ��
	SetConsoleCursorPosition(ConsoleHandle, coord);
}

//�����������ɫ
void setcolour(int a)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, a);
}


//���ع��
void hidemouth()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//��ȡ����̨�����Ϣ
	CursorInfo.bVisible = 0; //���ؿ���̨���
	SetConsoleCursorInfo(handle, &CursorInfo);//���ÿ���̨���״̬

}