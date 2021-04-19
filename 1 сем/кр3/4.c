#include <stdio.h>
#include <stdlib.h>


int main()
{
	FILE* file = fopen("file_text.txt", "r");
	int ds=0,kol_slov_m10=0,kol_str_na_glas=0;
	if (!file)
	{
		puts("Oshobka");
		exit(1);
	}
		
	char c;
	int flag = 1;
	do
	{
		c = fgetc(file);
		printf("%c", c);
		if (flag == 1)
		{
			flag = 0;
			if (c == 'A' ||
				c == 'E' ||
				c == 'Y' ||
				c == 'U' ||
				c == 'O' ||
				c == 'I' ||
				c == 'a' ||
				c == 'e' ||
				c == 'y' ||
				c == 'u' ||
				c == 'o' ||
				c == 'i' )
			{
				kol_str_na_glas++;
			}
		}
		if (c == ' ' || c == '\n' || c==EOF)
		{
			if (ds != 0 && ds < 10)
			{
				kol_slov_m10++;
			}
			if (c == '\n')
				flag = 1;
			ds = 0;
		}else{
			ds++;
		}
	} while (c!=EOF);

	puts("\n");
	fclose(file);
	printf("%d\n%d\n", kol_slov_m10, kol_str_na_glas);
}