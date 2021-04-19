#include <stdio.h>
#include <stdlib.h>

#define T 10


double f(double x, double y)
{
	return 1 - ((1 + x) * y) + y;
}

double f1(double x, double y)
{
	return -1 * (y + x * f(x, y));
}

void method_euler(double h, double x0, double y0)
{
	int z = 5;
	for (double i = x0; i <= x0 + T; i += h)
	{
		z--;
		if(z>=0)
			printf("%5lf  ", i);
	}
	z = 4;
	double y = y0;
	printf("\n%5lf  ", y);
	for (double i = x0+h; i <= x0 + T; i += h)
	{
		z--;
		y += h * f(i, y);
		if (z >= 0)
			printf("%5lf  ", y);
	}
	printf("\n");
}
void method_euler_mod(double h, double x0, double y0)
{
	int z = 4;
	double y = y0;
	printf("%5lf  ", y);
	for (double i = x0 + h; i <= x0 + T; i += h)
	{
		z--;
		y += h * f((i + h / 2), (y + (h / 2) * f1(i, y)));
		if (z >= 0)
			printf("%5lf  ", y);
	}
	printf("\n");
}
void method_euler_improve(double h, double x0, double y0)
{
	int z = 4;
	double y = y0;
	printf("%5lf  ", y);
	for (double i = x0 + h; i <= x0 + T; i += h)
	{
		z--;
		y += (h/2) * (f(i,y)+f(i+h,(y + h * f1(i, y))));
		if (z >= 0)
			printf("%5lf  ", y);
	}
	printf("\n");
}
void method_runge_kutt(double h, double x0, double y0)
{
	int z = 4;
	double y = y0;
	printf("%5lf  ", y);
	for (double i = x0 + h; i <= x0 + T; i += h)
	{
		z--;
		double k1 = f(i, y);
		double k2 = f(i + h / 2, y + (h*k1) / 2);
		double k3 = f(i + h / 2, y + (h*k2) / 2);
		double k4 = f(i + h, y + h*k3);
		y += h * (k1 + 2 * k2 + 2 * k3 + k4) / 6;

		if (z >= 0)
			printf("%5lf  ", y);
	}
	printf("\n");
}


int main()
{
	double h, step[3] = { 0.5, 0.1, 0.01 };
	for (int i = 0; i < 3; i++) {
		h = step[i];
		printf("h=%lf\n", h);
		method_euler(h, 0, 1);
		method_euler_mod(h, 0, 1);
		method_euler_improve(h,0,1);
		method_runge_kutt(h,0,1);
	}

}