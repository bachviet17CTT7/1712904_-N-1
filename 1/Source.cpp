#include <stdio.h>
#include <conio.h>
#include <io.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

void getInfo(FILE* inFile, FILE)
{
	int ch;
	while (1)
	{
		ch = fgetc(inFile);
		if ( ch == '"')
		{
			fgetc(inFile);
			if (ch == '"' || ch == EOF)
			{
				break;
			}


		}
		else
			break;
	}
}

void main()
{
	char* fnamein = "Sinh Vien.csv";
	FILE*fin = fopen(fnamein, "r");
	if (fin == NULL)
	{
		printf("File %s not found\n",fnamein);
		return;
	}

	char*fnameout = "Data receive.htm";
	FILE*fout = fopen(fnameout, "wt");
	if (fout == NULL)
	{
		printf("Cannot open %s!\n",fnameout);
		fclose(fin);
		return;
	}
	transFile(fin, fout);
	fclose(fin);
	fclose(fout);
}