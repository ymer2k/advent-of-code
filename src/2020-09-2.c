#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LINE_LENGTH 20
#define MAX_NR_OF_ROWS 1010
#define INVALID_NUMBER 1398413738

//declare functions
char** getDataArray();
FILE * getInputData(char path[]);
long long findNumber();
int findValidRangeUpperIndex(char ** dataArray,int index);
long long findSmallestNumberInRange(char ** dataArray,int lowerIndex, int upperIndex);
long long findLargestNumberInRange(char ** dataArray,int lowerIndex, int upperIndex);



char** getDataArray()
{
    //Reserve memory on the stack for the array.
    char str[MAX_LINE_LENGTH] = {0};
    char **dataArray = malloc(MAX_NR_OF_ROWS * sizeof(char *));
    int i = 0;
    for(i=0; i != MAX_NR_OF_ROWS; ++i)
    {
        dataArray[i] = malloc(MAX_LINE_LENGTH * sizeof(char));
    }

    //Fill the 2darray pointer with data.
    int k = 0;
    FILE *fp = getInputData("C:\\Users\\Jonas\\Cprojects\\advent-of-code-2020\\test\\2020-09-1\\2020-09-1-data.txt");
    while(fgets(str,MAX_LINE_LENGTH,fp) != NULL )
    {
        strcpy(dataArray[k],str);
        k++;
    }
    dataArray[k][0] = '\0'; //add a final null line.
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

long long findNumber()
{
    char** dataArray = getDataArray();
    int validRangeUpperIndex = 0;
    long long smallestNumber = 0;
    long long largestNumber = 0;

    for(int index = 0; index <= MAX_NR_OF_ROWS; index++)
    {
        validRangeUpperIndex = findValidRangeUpperIndex(dataArray,index);
        if(validRangeUpperIndex != 0)
        {
            largestNumber = findLargestNumberInRange(dataArray,index,validRangeUpperIndex);
            smallestNumber = findSmallestNumberInRange(dataArray,index,validRangeUpperIndex);
            return smallestNumber + largestNumber;
        }
    }
    return 0;
}

long long findLargestNumberInRange(char ** dataArray,int lowerIndex, int upperIndex)
{
    long long largestNumber = 0;
    for(int i=0; i <= (upperIndex-lowerIndex); i++)
    {

        if(atoll(dataArray[lowerIndex+i])> largestNumber)
        {
            largestNumber = atoll(dataArray[lowerIndex+i]);
        }
    }
    return largestNumber;
}

long long findSmallestNumberInRange(char ** dataArray,int lowerIndex, int upperIndex)
{
    long long smallestNumber = 9999999999999;
    for(int i=0; i <= (upperIndex-lowerIndex); i++)
    {

        if(atoll(dataArray[lowerIndex+i])< smallestNumber)
        {
            smallestNumber = atoll(dataArray[lowerIndex+i]);
        }
    }
    return smallestNumber;
}

int findValidRangeUpperIndex(char ** dataArray,int index)
{
    long long sum = 0;
    for(int i=0; i<MAX_NR_OF_ROWS; i++)
    {
        sum += atoll(dataArray[index+i]);
        if(sum == INVALID_NUMBER)
        {
            return index+i;
        }
        if(sum > INVALID_NUMBER)
        {
            return 0;
        }
    }
    return 0; //No we could not find a correct number
}


int main(void)
{
    long long encryptionWeakness;
    encryptionWeakness = findNumber();
    printf("The encryption weakness is:%I64d\n",encryptionWeakness);
    return 1;
}





