#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_INDEX_VALUE 630
#define MAX_LINE_LENGTH 10
#define OPERATION_LENGTH 4
#define MAX_NUMBER_LENGTH 5

//declare functions
char** getDataArray();
int getValueAfterOperation(char line[]);
int getNextIndexChange(char line[]);
int updateAccCount(char line[]);

FILE * getInputData(char path[])
{
    FILE *fp = fopen(path,"r");
    if(fp == NULL)
    {
        printf("Failed to open file\n");
    }
    return fp;
}

int getAccValue()
{
    int accCount = 0;
    int visitedIndexes[MAX_INDEX_VALUE] = {0};
    int index = 0;

    char** str = getDataArray();
    while(str[index] != NULL)
    {
        //if we already visited that index then return accCount before it updates.
        if(visitedIndexes[index] != 0)
        {
            free(str);
            return accCount;
        }

        accCount += updateAccCount(str[index]);
        visitedIndexes[index] = 1; //mark the index as visited.
        index += getNextIndexChange(str[index]);

    }
    free(str);
    return 0;

}

char** getDataArray()
{
    //Reserve memory on the stack for the array.
    char str[MAX_LINE_LENGTH] = {0};
    char **dataArray = malloc(MAX_INDEX_VALUE * sizeof(char *));
    int i = 0;
    for(i=0; i != MAX_INDEX_VALUE; ++i)
    {
        dataArray[i] = malloc(MAX_LINE_LENGTH * sizeof(char));
    }

    //fill the 2darray pointer with data.
    int k = 0;
    FILE *fp = getInputData("C:\\Users\\Jonas\\Cprojects\\advent-of-code-2020\\test\\2020-08-1\\2020-08-1-data.txt");
    while(fgets(str,MAX_LINE_LENGTH,fp) != NULL )
    {
        strcpy(dataArray[k],str);
        k++;
    }
    return dataArray;
}

int getNextIndexChange(char line[])
{
    if(line[0] == 'n') //Checks if its nop
    {
        return 1; //Do Nothing, just continue to next line
    }
    else if(line[0] == 'j')
    {
        return getValueAfterOperation(line);
    }
    else if(line[0] == 'a')
    {
        return 1; //continue to next line.
    }
    return 0;
}

int getValueAfterOperation(char line[])
{
    char number[MAX_NUMBER_LENGTH] = {0};
    memcpy(number,&line[OPERATION_LENGTH],strlen(line));
    number[OPERATION_LENGTH] = '\0';
    return atoi(number);
}

int updateAccCount(char line[]) //can have a regular old array here because the input argument is str[index]
{
    if(line[0] == 'a') // check if its acc
    {
        return getValueAfterOperation(line);
    }
    else
    {
        return 0;
    }
}

int main(void)
{
    int accCount = 0;
    accCount = getAccValue();
    printf("The accumulator value is:%d", accCount);

    return 1;
}





