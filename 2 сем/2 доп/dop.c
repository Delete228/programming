#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define N 100000000.0
#define R 10000.0

int RandomInt(int a, int b)
{
	return a + rand() % (b - a + 1);
}

double RandomFloat(double a, double b)
{
	return (float)rand() / RAND_MAX * (b - a) + a;
}

int main()
{
	srand(time(NULL));

	long long int in_round = 0;
	int q = 1;
	int t = 0;
	printf("[");

	for (int i = 0; i < 100; i++)
	{
		if (i % 10 == 0)
		{
			printf("|");
		}
		else {
			printf("-");
		}
		
	}
		
	printf("]\n");
	clock_t tim1 = clock();
	for (long long int i = 0; i < N; i++)
	{
		if (i > (N / 100) * q)
		{
			if (q == 1)
			{
				clock_t tim2 = clock();
				printf("Time 1: %.3lf   ~Time all Sec: %.1lf   ~Time all min: %.3lf\n[#", 
							(double)(tim2 - tim1) / CLOCKS_PER_SEC, 
							100*((double)(tim2 - tim1) / CLOCKS_PER_SEC), 
							100*((double)(tim2 - tim1) / (CLOCKS_PER_SEC*60)) );
			}

			printf("#");
			q++;
		}
		double x = RandomFloat(0.0, R);
		double y = RandomFloat(0.0, R);
		//printf("%5lf  %5lf  ", x, y);
		if ((x * x) + (y * y) < R*R)
		{
			in_round++;
			//printf("in\n");
		}
		else {
			//printf("out\n");
		}
			
	}
	printf("]\n");
	printf("Pi~=%lf", ((float)in_round/N)*4.0);
	
}