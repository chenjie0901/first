#include<stdio.h>
#include<stdlib.h>

int main()
{
	printf("%s", "   ");//��������������
	for (int i = 1; i < 10; i++)
	{
		printf("%-8d", i);//��ӡ������
	}
	printf("\n----------------------------------------------------------------------\n");
	//���ÿѭ��һ�Σ��ڲ�ѭ��ѭ������һ��
	for (int i = 1; i < 10; i++)
	{
		printf("%-3d", i);//��ӡ������
		for (int j = 1; j < 10; j++)
		{
			if(i>=j)printf("%d*%d=%-4d", i,j,i * j);
		}//�ڲ�ѭ��Ϊ�ᣬ���ѭ��Ϊ��
		printf("\n");
	}

	system("pause");
}