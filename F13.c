#include <stdlib.h>
#include <stdio.h>


void main(int argc, char **argv)
{
    if(argc < 3)
    {
        fprintf(stderr,"Not enough parameters\n");
         exit(EXIT_FAILURE);
    }
	FILE *fp = fopen(argv[1],"r");
    if (fp == NULL)
    {
	   fprintf(stderr,"fopen() failed in file %s at line # %d", __FILE__,__LINE__);
	   exit(EXIT_FAILURE);
    }
 	char ch = *argv[2];
	char parseCh;
	int count = 0;
	while (!feof(fp))
	{
		fscanf(fp,"%c",&parseCh);
		if(ch == parseCh)
			count++;
	}
  	fclose(fp);
    fprintf(stdout,"%d\n",count);
    exit(EXIT_SUCCESS);
}

