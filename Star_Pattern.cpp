#include<stdio.h>
#include<conio.h>
int main()
{
	int i=0;
	int j=0;
	for(i=0;i<=5;i++)
	{
		for(j=0;j<=i;j++)
		{
			printf("*");
		}
        printf("\n");
	}
	return 0;
}
