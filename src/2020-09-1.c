#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LINE_LENGTH 20
#define MAX_NR_OF_ROWS 1010
#define PREAMBLE_LENGTH 25

//declare functions
char** getDataArray();
FILE * getInputData(char path[]);
long long findNumber();
int checkIfNumberIsCorrect(char ** dataArray,int index);

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

    //fill the 2darray pointer with data.
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



    for(int index = 0; index <= 1000; index++)
    {
        if(checkIfNumberIsCorrect(dataArray,index) == 0)
        {
            return atoll(dataArray[PREAMBLE_LENGTH+index]);
        }
    }
    return 0;
}

int checkIfNumberIsCorrect(char ** dataArray,int index)
{
    for(int i=0; i<PREAMBLE_LENGTH; i++)
    {
        for(int k=0; k <PREAMBLE_LENGTH; k++)
        {
            if( atoll(dataArray[i+index]) != atoll(dataArray[k+index]) ) //ignore checking a number with itself.
            {
                if( (atoll(dataArray[i+index]) + atoll(dataArray[k+index])) == atoll(dataArray[PREAMBLE_LENGTH+index]) )
                {
                    return 1; // Yes we found a match
                }

            }

        }
    }
    return 0; //No we couldnt find a correct number
}


int main(void)
{
    long long inCorrectNumber;
    inCorrectNumber = findNumber();
    printf("The incorrect number is:%I64d\n",inCorrectNumber);
    return 1;
}





