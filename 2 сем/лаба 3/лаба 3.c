#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100000
#define A -25000
#define B 25000

int RandomInt(int a, int b)
{
	return a + rand() % (b - a + 1);
}


void generation()
{
	FILE* file = fopen("input.txt", "w");
	for (int i = 0; i < N; i++)
		fprintf(file, "%d ", RandomInt(A, B));
	fclose(file);
}
void read_file(int a[N])
{
	FILE* file = fopen("input.txt", "r");
	if (file == 0)
		exit(1);
	for (int i = 0; i < N; i++)
		fscanf(file, "%d", &a[i]);
	fclose(file);
}
void method_simple_sort()
{
	int a[N];
	int step = 0;
	read_file(a);
	//for (int i = 0; i < N; i++)
		//printf("%d ", a[i]);
	printf("\n");
	
	clock_t tim1 = clock();
	for (int i = 0; i < N - 1; i++)
	{
		int min = i + 1;
		for (int j = i + 1; j < N; j++)
			if (a[min] > a[j])
				min = j;
		if (a[min] < a[i])
		{
			int q = a[min];
			a[min] = a[i];
			a[i] = q;
			step++;
		}
	}
	clock_t tim2 = clock();
	//for (int i = 0; i < N; i++)
		//printf("%d ", a[i]);
	printf("\n\nstep:%d\ttime:%lf\n", step, (double)(tim2 - tim1) / CLOCKS_PER_SEC);
}
void method_puzirek()
{
	int a[N];
	unsigned long int step = 0;
	read_file(a);
	//for (int i = 0; i < N; i++)
		//printf("%d ", a[i]);
	//printf("\n");
	clock_t tim1 = clock();
	int q = 1;
	while (q > 0)
	{
		q = 0;
		for (int i = 0; i < N - 1; i++)
		{
			if (a[i] > a[i + 1])
			{
				int t = a[i];
				a[i] = a[i + 1];
				a[i + 1] = t;
				step++;
				q++;
			}
		}
	}
	clock_t tim2 = clock();
	//for (int i = 0; i < N; i++)
		//printf("%d ", a[i]);
	printf("\n\nstep:%ld\ttime:%lf\n", step, (double)(tim2 - tim1) / CLOCKS_PER_SEC);
}
void method_comb_sort()
{
	int a[N], stepp = 0;
	read_file(a);
	//for (int i = 0; i < N; i++)
		//printf("%d ", a[i]);
	//printf("\n");
	clock_t tim1 = clock();
	double fakt = 1.2473309; // фактор уменьшения
	double step = N - 1;
	while (step >= 1) {
		for (double i = 0; i < N - step; ++i) {
			if (a[int(i)] > a[int(i + step)]) {
				int t = a[int(i + step)];
				a[int(i + step)] = a[int(i)];
				a[int(i)] = t;
				stepp++;
			}
		}
		step /= fakt;
	}
	clock_t tim2 = clock();
	//for (int i = 0; i < N; i++)
		//printf("%d ", a[i]);
	printf("\n\nstep:%d\ttime:%lf\n", stepp, (double)(tim2 - tim1) / CLOCKS_PER_SEC);
}

int qsort(int a[N], int left, int right)
{
	int i = left, j = right;
	int temp, pivot = a[(left + right) / 2];
	int step = 0;

	while (i <= j)
	{
		while (a[i] < pivot) i++;
		while (a[j] > pivot) j--;

		if (i <= j)
		{
			if (a[i] > a[j])
			{
				temp = a[i]; 
				a[i] = a[j];
				a[j] = temp;
				step++;
			}

			i++; j--;
		}

	};

	if (left < j) 
		step+=qsort(a, left, j);
	if (i < right) 
		step+=qsort(a, i, right);
	return step;
}

void method_quik_sort()
{
	int a[N], step = 0;
	read_file(a);
	//for (int i = 0; i < N; i++)
		//printf("%d ", a[i]);
	//printf("\n");
	clock_t tim1 = clock();
	step = qsort(a, 0, N - 1);
	clock_t tim2 = clock();
	//for (int i = 0; i < N; i++)
		//printf("%d ", a[i]);
	printf("\n\nstep:%d\ttime:%lf\n", step, (double)(tim2 - tim1) / CLOCKS_PER_SEC);
}


int main(void) 
{
	srand(time(NULL));
	generation();
	method_simple_sort();
	method_puzirek();
	method_comb_sort();
	method_quik_sort();
	
	
}
