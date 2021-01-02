#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_NR_OF_ROWS 100
#define MAX_LINE_LENGTH 10

//declare functions
char** getDataArray();
FILE * getInputData(char path[]);
int ** getIntDataArray();
int getThreeJoltDiff(char **dataArray, int arrayLength);
int getOneJoltDiff(char **dataArray, int arrayLength);
void sortArray2(char ** dataArray);

char** getDataArray()
{
    //Reserve memory on the stack for the array.
    char str[MAX_LINE_LENGTH] = {0};
    //allocate memory on the heap.
    char **dataArray = malloc(MAX_NR_OF_ROWS * sizeof(char *));
    for(int i=0; i != MAX_NR_OF_ROWS; ++i)
    {
        dataArray[i] = malloc(MAX_LINE_LENGTH * sizeof(char));
    }

    //Fill the 2d array pointer with data.
    int k = 0;
    FILE *fp = getInputData("C:\\Users\\Jonas\\Cprojects\\advent-of-code-2020\\test\\2020-10-1\\2020-10-1-data.txt");
    while(fgets(str,MAX_LINE_LENGTH,fp) != NULL )
    {
        strcpy(dataArray[k],str);
        k++;
    }
    dataArray[k][0] = '\0';
    return dataArray;
}

FILE * getInputData(char path[])
{
    FILE *fp = fopen(path,"r");
    if(fp == NULL)
    {
        printf("Failed to open file\n");
    }
    return fp;
}

int getArrayLength(char ** dataArray)
{
    int i = 0;
    while(*dataArray[i] != '\0') //Now suddenly we have to dereference dataArray... In previous assignments I didnt have to do that. Edit: maybe I never did before...
    {
        i++;
    }
    return i;
}

/* Sorts the array from smallest to largest number */
void sortArray2(char ** dataArray)
{
    char temp[MAX_LINE_LENGTH] = {0};
    for(int i=0; *dataArray[i+1] != '\0'; i++) //Same as in getArrayLength. I think we have to dereference because otherwise we compare a pointer to and null character.
    {
        for(int k=0; atoi(dataArray[k+1]) > 0; k++)
        {
            if(atoi(dataArray[k]) > atoi(dataArray[k+1]))
            {
                strcpy(temp,dataArray[k]);
                strcpy(dataArray[k],dataArray[k+1]);
                strcpy(dataArray[k+1],temp);
            }
        }
    }
}

int countJoltDifferencesAndGetProduct()
{
    char ** dataArray = getDataArray();
    int arrayLength = getArrayLength(dataArray);
    sortArray2(dataArray);

    return (getOneJoltDiff(dataArray, arrayLength) * getThreeJoltDiff(dataArray,arrayLength));
}

int getOneJoltDiff(char **dataArray, int arrayLength)
{
    int oneJoltCounter=0;
    for(int i=0; (i+1) < arrayLength; ++i )
    {
        if( (atoi(dataArray[i+1]) - atoi(dataArray[i])) == 1 )
        {
            oneJoltCounter++;
        }
    }

    //Edge cases.
    //Charging outlet is 0 jolts so check if 0 to the first adapter is equal to 1.
    if(atoi(dataArray[0]) == 1)
    {
        oneJoltCounter++;
    }
    return oneJoltCounter;
}

int getThreeJoltDiff(char **dataArray, int arrayLength)
{
    int threeJoltCounter=0;
    for(int i=0; (i+1) < arrayLength; ++i )
    {
        if( (atoi(dataArray[i+1]) - atoi(dataArray[i])) == 3 )
        {
            threeJoltCounter++;
        }
    }

    //Edge cases
    //Charging outlet is 0 jolts so check if 0 to the first adapter is equal to 3.
    if(atoi(dataArray[0]) == 3)
    {
        threeJoltCounter++;
    }

    //The device has a built in adapter always 3 higher than the highest adapter, so add 1.
    threeJoltCounter++;

    return threeJoltCounter;
}

int main(void)
{
    printf("Answer:%d\n",countJoltDifferencesAndGetProduct());
    return 0;
}
