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

    //Fill the 2d array pointer with data. Add a zero adapter in the beginning.
    strcpy(dataArray[0],"0");
    int k = 1;
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

void addEndAdapter(char ** dataArray, int arrayLength)
{
    //add the end adapter.
    int lastAdapter = atoi(dataArray[arrayLength-1]);
    char line[MAX_LINE_LENGTH] = {0};
    sprintf(line, "%d", lastAdapter + 3); //Last adapter is 3 bigger than the second to last.
    strcpy(dataArray[arrayLength],line);
    dataArray[arrayLength+1][0] = '\0';
}

void printCombinations(char ** dataArray, int arrayLength)
{
    long long int multi[999]; //all numbers begin with multi = 1. keeps track of the multi for each number. multi is how many possible adapter combination that number can produce.
    multi[atoi(dataArray[arrayLength-1])] = 1; // initialize the ending adapter to have multi = 1.
    int currentNumber = 0;
    int nextNumber = 0; // nextNumber meaning the numbers in scope after the current number. Eg. current nr = 19 then next nr = 22.
    long long tempSum = 1; // start tempSum at 1 for the special case of the last adapter which has no nextNumber. tempSum sums the multi for nextNumber in scope.

    for(int i = arrayLength-1; i >= 0; --i) //-1 because of zero index. loop through from the last index tot he first
    {
        printf("\n");
        printf("\n");
        printf("Current Number:%d\n",atoi(dataArray[i]));
        printf("In scope: ");
        for(int j=1; j <= 3; j++) //loop through the closest three numbers
        {
            if(atoi(dataArray[i+j]) != '\0') // if we are not out of bounds.
            {
                currentNumber = atoi(dataArray[i]);
                nextNumber = atoi(dataArray[i+j]);
                if( (nextNumber - currentNumber) <= 3) //check the next three numbers after current number.
                {
                    printf(" %d,",atoi(dataArray[i+j]));
                    tempSum += multi[nextNumber];

                }
                else
                {
                    break;
                }

            }
            else
            {
                break;
            }

        }
        //update the multi array
        multi[currentNumber] = tempSum;
        tempSum = 0;

    }
    //Print result
    printf("\n\n");
    printf("Number of combinations:%I64d\n",multi[currentNumber]);
}

void countAdapterCombinations()
{
    char ** dataArray = getDataArray();
    int arrayLength = 0;

    //Get data, sort and add the first and last adapter.
    arrayLength = getArrayLength(dataArray);
    sortArray2(dataArray);
    addEndAdapter(dataArray,arrayLength);
    arrayLength = getArrayLength(dataArray);
    printCombinations(dataArray,arrayLength);
}

int main(void)
{
    countAdapterCombinations();
    return 0;
}
