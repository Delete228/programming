#include <stdio.h>
#include <stdlib.h>

#define N 6


int compare(const void* x1, const void* x2)
{
	return (*(int*)x2 - *(int*)x1);
}

int main()
{
	int a[N];
	FILE* file;
	file = fopen("data1.txt","r");
	if (!file)
		exit(1);
	for (int i = 0; i < N; i++)
	{
		fscanf(file, "%d", &a[i]);
		printf("%d ", a[i]);
	}
	fclose(file);
	puts("");
	for (int i = 0; i < N; i++)
	{
		a[i] += a[i] % 10;
	}
	qsort(a,N,sizeof(int),compare);
	for (int i = 0; i < N; i++)
	{
		printf("%d ", a[i]);
	}
	
}