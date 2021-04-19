#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define T 0.0001
#define A 0
#define B 4
#define P 10

double funktion(double x)
{
	return 1/(5-x);
}


void method_right_rectangle(double a, double b, double funk(double))
{
	//FILE* file = fopen("Result.txt", "a");
	printf(" _________________________________________ \n");
	printf("|         method_right_rectangle          |\n");
	printf("|_________________________________________|\n");
	printf("|  N  |     H     |     S     |    dS     |\n");
	double s = 0;
	double s0 = 0;
	int n = P;

	do
	{
		double h = (b - a) / n;
		s0 = s;
		s = 0;
		for (double i = a; i < b; i += h)
		{
			s += h * funk(i + h);
		}
		//printf("%lf\n", s);
		printf("|%5d|%11lf|%11lf|%11lf|\n", n, h, s, fabs(s - s0));
		n *= 2;
	} while (fabs(s - s0) > T);
	printf("|_________________________________________|\n");
	//fclose(file);
}

int main()
{

	method_right_rectangle(A, B, funktion);
	

}