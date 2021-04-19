#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define A -10
#define B 10
#define N 10



int RandomInt(int a, int b)
{
	return a + rand() % (b - a + 1);
}

void funk1(int* a, int size)
{
	for (int i = 0; i < size; i++)
	{
		a[i] = RandomInt(A, B);
	}
}
void funk2(int* a, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%d ", a[i]);
	}
	puts("");
}
int funk3(int* a, int size)
{
	int minPol = 0;
	for (int i = 0; i < size; i++)
	{
		if (a[i] > 0)
		{
			minPol = a[i];
			break;
		}
	}
	for (int i = 0; i < size; i++)
	{
		if (a[i] > 0 && a[i]<minPol)
		{
			minPol = a[i];
		}
	}
	return minPol;
}
int funk4(int* a, int size)
{
	int maxOtr = 0;
	for (int i = 0; i < size; i++)
	{
		if (a[i] < 0)
		{
			maxOtr = a[i];
			break;
		}
	}
	for (int i = 0; i < size; i++)
	{
		if (a[i] < 0 && a[i] > maxOtr)
		{
			maxOtr = a[i];
		}
	}
	return maxOtr;
}
int main()
{
	srand(time(0));
	int a[N];
	funk1(a, N); //Заполнение
	funk2(a, N); //Вывод
	printf("%d", funk3(a, N) * funk4(a, N)); //funk3 - минимальное положительное; funk4 - максимальное отрицательное
	
}