#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int RandomInt(int a, int b)
{
	return a + rand() % (b - a + 1);
}

int main()
{
	srand(time(0));
	char a[250]="";
	int q = 0;
	scanf("%s", &a);
	while (a[q] != 0)
	{
		q++;
	}
	printf("%d\n",q);
	printf("Slucaini simvol: %d\n", a[RandomInt(0,q-1)]);
}