#include<stdio.h>
#include<stdlib.h>

int main()
{
	printf("%s", "   ");//间隔，对其横坐标
	for (int i = 1; i < 10; i++)
	{
		printf("%-8d", i);//打印横坐标
	}
	printf("\n----------------------------------------------------------------------\n");
	//外层每循环一次，内层循环循环完整一次
	for (int i = 1; i < 10; i++)
	{
		printf("%-3d", i);//打印纵坐标
		for (int j = 1; j < 10; j++)
		{
			if(i>=j)printf("%d*%d=%-4d", i,j,i * j);
		}//内层循环为横，外层循环为竖
		printf("\n");
	}

	system("pause");
}