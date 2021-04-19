#include <stdio.h>
#include <stdlib.h>


int main()
{
	FILE* file1 = fopen("file_text.txt", "r");
	FILE* file2 = fopen("file_new.txt", "w");
	int kols = 0;
	if (!file)
	{
		puts("Oshobka");
		exit(1);
	}
	char c;
	do
	{
		c = fgetc(file1);
		kols++;
		if (kols == 15)
		{
			fprintf(file2, "%c ", c);
			kols = 0;
		}


	} while (c != EOF);

	fclose(file2);

	int g = 0;
	kols = 0;
	fseek(file1, 0, SEEK_SET);
	file2 = fopen("file_new.txt", "a");
	fprintf(file2, "\n");
	do
	{
		c = fgetc(file1);
		g++;

		if (c == '\n' || c == EOF)
		{
			fseek(file1, g - (kols / 2) - 1, SEEK_SET);
			for (int i = fgetc(file1); i != '\n' && i != EOF; i = fgetc(file1))
			{
				fprintf(file2, "%c", i);
			}
			if(c!=EOF)
				fprintf(file2, "%c", c);
			g++;
			kols = 0;
		}
		else {
			kols++;
		}


	} while (c != EOF);
	fclose(file1);
	fclose(file2);
}