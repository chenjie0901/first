#include<stdio.h>
#include<stdlib.h>

int get10n(int n)
{
	int res = 1;
	for (int i = 0; i < n; i++)
	{
		res *= 10;
	}
	return res;
}

int main()
{
	int num;
	scanf_s("%d", &num);
	int numA = num;
	printf("要逆转的数据%d", num);
	int wei;
	for (wei=0;num!=0;num/=10)
	{
		wei++;
	}
	//printf("位数为%d\n", wei);

	int last = 0;
	for (int i = 0; i < wei; i++)
	{
		int nowwei = 0;
		//printf("\n%d", numA / get10n(i)%10);
		nowwei = numA / get10n(i) % 10;
		last += nowwei * get10n(wei - 1 - i);
	}
	printf("转换以后的结果%d\n",last);



	system("pause");
}
