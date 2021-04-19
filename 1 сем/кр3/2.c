#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main()
{
	char a1[250]="", a2[250]="";
	char b[500]="";
	scanf("%s %s", &a1, &a2);
	if (strlen(a1) > strlen(a2))
	{
		strcat(b, a2);
		strcat(b, a1);
	}else{
		strcat(b, a1);
		strcat(b, a2);
	}
	printf("%s",b);
}