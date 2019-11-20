#include<stdio.h>
#include<stdlib.h>

int whilenum(int num)
{
	int i = 0;
	while (num)
	{
		num /= 10;
		i++;
	}
	return i;
}



void main()
{
	int num;
	scanf_s("%d", &num);
	printf("while=%d", whilenum(num));


	system("pause");
}