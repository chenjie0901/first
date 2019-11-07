#include<stdio.h>


int main()
{
	
	printf("\n");
	int a;
	int i;
	int x;
	scanf_s("%d",&x);
	long c = 0;

	for (i = 0; i < 20; i++)
	{
		a = x % 10;
		x = x / 10;
		c = a + c * 10;
		if (c > 0x7fffffff || c < (signed int)0x80000000)
		{
			return 0;
		}
		if (x == 0)
			break;
	}
	printf("%d", c);
	return 0;
}
