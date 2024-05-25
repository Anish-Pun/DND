#include <stdio.h>
#include"json.h"


void parsejson(char *equipment.json)
{
    FILE *fp;
    char buff[255];
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        return;
    }
    while (fgets(buff, 255, (FILE *)fp))
    {
        printf("%s", buff);
    }
    fclose(fp);
}