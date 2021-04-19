#include <stdio.h>
#include <stdlib.h>


int main()
{
	FILE* file1;
	FILE* file2;
	file1 = fopen("text_file.txt","r");
	if (!file1)
		exit(1);
	file2 = fopen("new_file.txt", "w");
	int s=0;
	char c;
	do{
		c = fgetc(file1);
		s++;
		if (s == 15)
		{
			s = 0;
			fprintf(file2,"%c ",c);
		}
	} while (c != EOF);
	fprintf(file2, "\n\n");
	fseek(file1, 0, SEEK_SET);
	fclose(file2);
	file2 = fopen("new_file.txt", "a");
	s = 0;
	int d = 0;
	do {
		c = fgetc(file1);
		d++;
		if (c == '\n' || c == EOF)
		{
			fseek(file1, d-(s/2)-1, SEEK_SET);
			char q;
			do {
				q = fgetc(file1);
				if(q!=EOF)
					fprintf(file2, "%c", q);
			} while (q != EOF && q != '\n');
			fseek(file1, d+1, SEEK_SET);
			d++;
			s = 0;
		}
		else {
			s++;
		}
	} while (c != EOF);
	fclose(file1);
	fclose(file2);
}