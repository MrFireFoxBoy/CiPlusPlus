#include <iostream>
#include <stdlib.h>
const int n = 3;

int main()
{
	int mass[n + 1] = { 1,2,3,4 };
	int k = 0;
	int skip = 1;

	for (int i = 0; i <= n; i++)
	{
		printf("%d\n", mass[i]);
	}
	for (int i = 0; i < skip; i++)
	{
		k = mass[n];

		for (int j = n; j >= 0; j--)
		{
			mass[j] = mass[j - 1];
		}
		mass[0] = k;
	}

	printf("result \n");

	for (int i = 0; i <= n; i++)
	{
		printf("%d\n", mass[i]);
	}
}