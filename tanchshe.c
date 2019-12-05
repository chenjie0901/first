#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <malloc.h>
#include <time.h>
#include <stdlib.h>
void setmouth(int x, int y);//设置光标
void background();//背景生成
void setcolour(int a);//设置颜色
void init();//初始化
void hidemouth();//隐藏光标
void startfood();//初始创建食物
void startsnack();//初始创建小蛇
void snackmove(int, int);//小蛇移动
int checksnack(int);//小蛇碰撞检测
void snackdie();//小蛇死亡
void showing();//输出最新的show
void screenRefresh(int);//屏幕刷新
void newfood();//创建新食物
void updategoal();//更新得分
int movedire(int, int);//获取小蛇的移动方向
int snacklength = 3;//小蛇长度
int snackhead = 2;//蛇头
int snacktail = 0;//蛇尾
int MaxLine = 40, MaxLie = 40;//定义最大行数，列数
//结构体保存各个事物的属性
struct map {
	int colour;
	int kind;
	char* display;
}
show[40][40], //展示地图
wall = { 0x6C,1,"■" },//墙体
livearea = { 0x7F,2,"□" },//小蛇活动区域
food = { 0x7C,3,"★" },//食物
snack = { 0x7A,4,"●" };//小蛇蛇体的属性

struct SnackMap
{
	int x;
	int y;

}SnackSite[100], FoodSite;

/***************************************
				主程序
****************************************/

int main()
{
	int olddirection = 'w'; //初始键盘信号
	int newdirection = 0;//获取键盘信号
	init();//初始化

	setmouth(60, 0);
	setcolour(0xF0);
	printf("\n得分：");
	printf("%d\n", snacklength - 3);
	printf("请切换为英文输入法\n");
	printf("W A S D键分别表示：上 左 下 右\n");
	printf("Copyright [2019.12.03] by [光电学院]		");

	while (1) {
		if (_kbhit()) {  //检测缓冲区中是否有数据
			newdirection = tolower(_getch());  //将缓冲区中的数据以字符的形式读出
			if (newdirection == 27) {
				break;
			}
			else {
				//获取小蛇新的移动方向
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
//更新得分
void updategoal()
{
	setcolour(0xF0);
	setmouth(60, 0);
	printf("\n得分：%d", snacklength - 3);
}
//碰撞检测
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

//创建新食物
void newfood()
{
	srand((unsigned)time(NULL));
	FoodSite.x = rand() % 38 + 1;
	FoodSite.y = rand() % 38 + 1;
}

//刷新屏幕
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
				获取最新的方向
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
		  展示最新的show
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
			小蛇死亡
*******************************************/


void snackdie()
{
	setmouth(20, 5);
	printf("Game over! 按任意键结束游戏！");
	Sleep(5000);
	_getch();
	exit(0);
}

//小蛇移动
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



//初始食物


void startfood()
{
	FoodSite.x = 5;
	FoodSite.y = 10;
	show[5][10] = food;
}



//初始小蛇

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
	初始化生成show结构体数组
*******************************/

void init()
{
	//设置窗口大小
	system("mode con:cols=140 lines=50");
	//隐藏光标
	hidemouth();
	//生成背景图
	background();
	//创建初始食物
	startfood();
	//创建初始小蛇蛇体
	startsnack();
	//显示
	showing();
}


/**************************************
			生成背景图
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
		定义光标位置
*********************************/

void setmouth(int x, int y)
{
	COORD coord;
	coord.X = y * 2;  //第3列
	coord.Y = x;  //第3行
	//获取控制台缓冲区句柄
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	//设置光标位置
	SetConsoleCursorPosition(ConsoleHandle, coord);
}

//设置种类的颜色
void setcolour(int a)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, a);
}


//隐藏光标
void hidemouth()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
	CursorInfo.bVisible = 0; //隐藏控制台光标
	SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态

}
