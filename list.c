#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int Check(const char* name)
{
    DIR* dir = opendir(name);
    if(!dir)
    {
        return -1;
    }
    struct dirent *entry = readdir(dir);
    if(!entry)
    {
        closedir(dir);
        return -2;
    }
    closedir(dir);
    return 0;
}

void AddLine(char ***a, int *count,int columns)
{
    (*count) += 1;
    *a = (char**)realloc(*a,(*count) * sizeof(char**));
    (*a)[(*count)-1] = (char*)malloc((columns + 1) * sizeof(char*));
}

void listdir(const char *name,char ***destination,int *count)
{
    if(Check(name) != 0)
    {
        return ;
    }
    DIR *dir = opendir(name);
    struct dirent *entry = readdir(dir);
    int length = strlen(name);
    int curentLength = 0, newLength;
    char *path = NULL;
    do
    {
        if (entry->d_type == DT_DIR)
        {
            newLength = length + strlen(entry->d_name);
            if(newLength > curentLength)
            {
                path = (char*)realloc(path,(newLength + 1)*sizeof (char*));
                curentLength = newLength;
            }

            sprintf(path,"%s/%s", name, entry->d_name);

            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;

            listdir(path,destination,count);
        }
        else
        {
            AddLine(destination,count, + length + strlen(entry->d_name));
            sprintf((*destination)[(*count) - 1],"%s/%s", name, entry->d_name);
        }
    }
    while (entry = readdir(dir));
    free(path);
    closedir(dir);
}


void main(int argc,char **argv)
{
    if(argc < 3)
    {
        fprintf(stderr,"Not enough parameters\n");
        exit(EXIT_FAILURE);
    }
    int check;
    int i;
    for(i = 1; i < 3; i++)
    {   
        check = Check(argv[i]);
        if(check == 0)
            continue;
        if(check == -1)
        {
            fprintf(stderr,"Cannot open %s directory\n",((i == 2)? "first":"second"));
        }
        else
        {
            fprintf(stderr,"Cannot read %s directory\n",((i == 2)? "first":"second"));
        }
        exit(EXIT_FAILURE);
    }
    fprintf(stdout,"Starting...\n");
    char **filesFolder1 = (char**)malloc(sizeof(char**));
    filesFolder1[0] = NULL;
    int countFiles1 = 0;
    listdir(argv[1],&filesFolder1, &countFiles1);
    fprintf(stdout,"Stop!\n");
    for(int i = 0;i < countFiles1; i++)
    {
        strcpy(filesFolder1[i],filesFolder1[i] + strlen(argv[1]));
        fprintf(stdout, "%s\n",filesFolder1[i]);
    }
    fprintf(stdout,"\n\n");




    fprintf(stdout,"Starting...\n");
    char **filesFolder2 = (char**)malloc(sizeof(char**));
    filesFolder2[0] = NULL;
    int countFiles2 = 0;
    listdir(argv[2],&filesFolder2, &countFiles2);
    fprintf(stdout,"Stop!\n");
    for(int i = 0;i < countFiles2; i++)
    {
        strcpy(filesFolder2[i],filesFolder2[i] + strlen(argv[2]));
        fprintf(stdout, "%s\n",filesFolder2[i]);
    }
    fprintf(stdout,"\n\n");

    fprintf(stdout,"\n%s:\n",argv[1]);

    for(int i = 0; i < countFiles1; i++)
    {
        int found = 0;
        for(int j = 0;j < countFiles2; j++)
        {
            if(strcmp(filesFolder1[i],filesFolder2[j])==0)
            {
                found = 1;
                break;
            }
        }
        if(found == 0)
        {
           fprintf(stdout,"%s\n",filesFolder1[i]);
        }
    }
    fprintf(stdout,"\n%s:\n",argv[2]);
    
    for(int j = 0;j < countFiles2; j++)
    {
        int found = 0;
        for(int i = 0; i < countFiles1; i++)
        {
            if(strcmp(filesFolder1[i],filesFolder2[j])==0)
            {
                found = 1;
                break;
            }
        }
        if(found == 0)
        {
           fprintf(stdout,"%s\n",filesFolder2[j]);
        }
    }
    fprintf(stdout,"\n");
    exit(EXIT_SUCCESS);
}
