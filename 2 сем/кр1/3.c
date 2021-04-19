#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 30
#define A -25000
#define B 25000

int RandomInt(int a, int b)
{
	return a + rand() % (b - a + 1);
}


void generation(int a[N])
{
	//FILE* file = fopen("input.txt", "w");
	//for (int i = 0; i < N; i++)
	//	fprintf(file, "%d ", RandomInt(A, B));
	//fclose(file);
	for (int i = 0; i < N; i++)
		a[i] = RandomInt(A, B);
}

void method_comb_sort(int a[N],int b1,int b2)
{
	int stepp = 0;
	
	clock_t tim1 = clock();
	double fakt = 1.2473309; // фактор уменьшения
	double step = b2 - 1;
	while (step >= 1) {
		for (double i = b1; i < b2 - step; ++i) {
			if (a[int(i)] < a[int(i + step)]) {
				int t = a[int(i + step)];
				a[int(i + step)] = a[int(i)];
				a[int(i)] = t;
				stepp++;
			}
		}
		step /= fakt;
	}
	clock_t tim2 = clock();
	
	printf("\n\nstep:%d\ttime:%lf\n", stepp, (double)(tim2 - tim1) / CLOCKS_PER_SEC);
}






int main(void)
{
	srand(time(NULL));
	int a[N];
	generation(a);
	for (int i = 0; i < N; i++)
	{
		if(i==N/2)
			printf("|");
		printf("%d ", a[i]);
	}
	
	method_comb_sort(a,0,N/2);
	printf("\n");
	for (int i = 0; i < N; i++)
	{
		if (i == N / 2)
			printf("|");
		printf("%d ", a[i]);
	}

}
