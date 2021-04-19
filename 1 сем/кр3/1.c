#include <stdio.h>
#include <string.h>

#define N 56

struct chocalate {
	char firma[250];
	char marka[250];
	char type[250];
	char dobavki[250];
	int ves;
	int cena;
};



int main()
{
	struct chocalate CHOC[N];
	for (int i = 0; i < N; i++)
	{
		printf("Puts chocalate nomer %d config: \n", i);
		printf("Firma: ");
		scanf("%s", CHOC[i].firma);
		printf("Marka: ");
		scanf("%s", CHOC[i].marka);
		printf("Type: ");
		scanf("%s", CHOC[i].type);
		printf("Dobavki: ");
		scanf("%s", CHOC[i].dobavki);
		printf("Ves: ");
		scanf("%d", &CHOC[i].ves);
		printf("Cena: ");
		scanf("%d", &CHOC[i].cena);
	}

	puts("\n");
	printf("|Nomer chocolata| Firma       | Marka       | Type        | Dobavki    | Ves  | Cena |\n");
	for (int i = 0; i < N; i++)
	{
		printf("| Chocolate %3d | %10s  | %10s  | %10s  | %10s | %4d | %4d |\n",
			i,
			CHOC[i].firma,
			CHOC[i].marka,
			CHOC[i].type,
			CHOC[i].dobavki,
			CHOC[i].ves,
			CHOC[i].cena);
	}

	puts("\nVvedite nazvanie firmi: ");
	char a[250];
	scanf("%s", &a);
	puts("");
	int c = 0;
	for (int i = 0; i < N; i++)
	{
		if (strcmp(CHOC[i].firma,a)==0)
		{
			c++;
			printf("Chocolate %d; firma: %s; marka: %s; type: %s; dobavki: %s; ves: %d; cena %d\n",
				c,
				CHOC[i].firma,
				CHOC[i].marka,
				CHOC[i].type,
				CHOC[i].dobavki,
				CHOC[i].ves,
				CHOC[i].cena);
		}
	}
	puts("\n");

	int min_ves = CHOC[0].ves;
	for (int i = 0; i < N; i++)
	{
		if (min_ves > CHOC[i].ves)
			min_ves = CHOC[i].ves;
	}
	puts("Samaia legkaia marka(marki) chocolate: ");
	for (int i = 0; i < N; i++)
	{
		if (min_ves == CHOC[i].ves)
			printf("%s ", CHOC[i].marka);
	}
	
}