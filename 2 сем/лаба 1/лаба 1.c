#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define T 0.0001
#define A -0.75
#define B 0
#define P 10

double funktion(double x)
{
	return (5*x)/(x*x-1);
}


void method_right_rectangle(double a, double b, double funk(double))
{
	FILE* file = fopen("Result.txt","a");
	fprintf(file, " _________________________________________ \n");
	fprintf(file, "|         method_right_rectangle          |\n");
	fprintf(file, "|_________________________________________|\n");
	fprintf(file, "|  N  |     H     |     S     |    dS     |\n");
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
			s += h * funk(i+h);
		}
		//printf("%lf\n", s);
		fprintf(file, "|%5d|%11lf|%11lf|%11lf|\n",n,h,s, fabs(s - s0));
		n *= 2;
	} while (fabs(s - s0) > T);
	fprintf(file, "|_________________________________________|\n");
	fclose(file);
}

void method_left_rectangle(double a, double b, double funk(double))
{
	FILE* file = fopen("Result.txt", "a");
	fprintf(file, " _________________________________________ \n");
	fprintf(file, "|         method_left_rectangle           |\n");
	fprintf(file, "|_________________________________________|\n");
	fprintf(file, "|  N  |     H     |     S     |    dS     |\n");
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
			s += h * funk(i);
		}
		//printf("%lf\n", s);
		fprintf(file, "|%5d|%11lf|%11lf|%11lf|\n", n, h, s, fabs(s - s0));
		n *= 2;
	} while (fabs(s - s0) > T);
	fprintf(file, "|_________________________________________|\n");
	fclose(file);
}

void method_middle_rectangle(double a, double b, double funk(double))
{
	FILE* file = fopen("Result.txt", "a");
	fprintf(file, " _________________________________________ \n");
	fprintf(file, "|         method_middle_rectangle         |\n");
	fprintf(file, "|_________________________________________|\n");
	fprintf(file, "|  N  |     H     |     S     |    dS     |\n");
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
			s += h * funk(i+h/2);
		}
		//printf("%lf\n", s);
		fprintf(file, "|%5d|%11lf|%11lf|%11lf|\n", n, h, s, fabs(s - s0));
		n *= 2;
	} while (fabs(s - s0) > T);
	fprintf(file, "|_________________________________________|\n");
	fclose(file);
}

void method_trapeze(double a, double b, double funk(double))
{
	FILE* file = fopen("Result.txt", "a");
	fprintf(file, " _________________________________________ \n");
	fprintf(file, "|             method_trapeze              |\n");
	fprintf(file, "|_________________________________________|\n");
	fprintf(file, "|  N  |     H     |     S     |    dS     |\n");
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
			s += h * (funk(i) + funk(i + h)) * 0.5;
		}
		//printf("%lf\n", s);
		fprintf(file, "|%5d|%11lf|%11lf|%11lf|\n", n, h, s, fabs(s - s0));
		n *= 2;
	} while (fabs(s - s0) > T);
	fprintf(file, "|_________________________________________|\n");
	fclose(file);
}

void method_simpson(double a, double b, double funk(double))
{
	FILE* file = fopen("Result.txt", "a");
	fprintf(file, " _________________________________________ \n");
	fprintf(file, "|             method_simpson              |\n");
	fprintf(file, "|_________________________________________|\n");
	fprintf(file, "|  N  |     H     |     S     |    dS     |\n");
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
			s +=( h *(funk(i) + 4*funk(i + h / 2) + funk(i + h)) )/ 6;
		}
		//printf("%lf\n", s);
		fprintf(file, "|%5d|%11lf|%11lf|%11lf|\n", n, h, s, fabs(s - s0));
		n *= 2;
	} while (fabs(s - s0) > T);
	fprintf(file, "|_________________________________________|\n");
	fclose(file);
}

int main()
{

	method_right_rectangle(A, B, funktion);
	method_left_rectangle(A, B, funktion);
	method_middle_rectangle(A, B, funktion);
	method_trapeze(A, B, funktion);
	method_simpson(A, B, funktion);

}