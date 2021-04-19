#include <stdio.h>
#include <stdlib.h>

#define T 5


double f(double x, double y)
{
	return x-y*(x-3);
}

double f1(double x, double y)
{
	return 1-((x-3)*f(x,y))-y;
}
	

void method_runge_kutt(double h, double x0, double y0)
{
	int z = 5;
	for (double i = x0; i <= x0 + T; i += h)
	{
		z--;
		if (z >= 0)
			printf("%5lf  ", i);
	}
	printf("%5lf\n", x0+T);
	z = 4;
	double y = y0;
	printf("%5lf  ", y);
	for (double i = x0 + h; i <= x0 + T; i += h)
	{
		z--;
		double k1 = f(i, y);
		double k2 = f(i + h / 2, y + (h * k1) / 2);
		double k3 = f(i + h / 2, y + (h * k2) / 2);
		double k4 = f(i + h, y + h * k3);
		y += h * (k1 + 2 * k2 + 2 * k3 + k4) / 6;

		if (z >= 0)
			printf("%5lf  ", y);
	}
	printf("%5lf  ", y);
	printf("\n");
}


int main()
{
	double h, step[3] = { 0.5, 0.1, 0.01 };
	for (int i = 0; i < 3; i++) {
		h = step[i];
		printf("h=%lf\n", h);
		method_runge_kutt(h, 0, 0);
	}

}