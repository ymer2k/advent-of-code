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

void flipNopAndJmp(char ** arrayPointer,int index)
{

    if(arrayPointer[index][0] == 'j')
    {
        arrayPointer[index][0] = 'n';

    }
    else
    {
        arrayPointer[index][0] = 'j';
    }
}

int getAccValue()
{
    int accCount = 0;
    int visitedIndexes[MAX_INDEX_VALUE] = {0};
    int nopJmpIndexes[MAX_INDEX_VALUE] = {0};
    int index = 0;
    int notFirstRound = 0;
    int currentNopJmpIndex = -1;
    char** str = getDataArray();

    while(1)
    {
        while(str[index][0] != '\0')
        {
            //if we already visited that index then it failed and we should reset
            if(visitedIndexes[index] != 0)
            {
                //Revert the jmp -> nop OR nop -> jmp changes made! I.e Make str same as it originally was.
                if(notFirstRound != 0)
                {
                    flipNopAndJmp(str,currentNopJmpIndex);
                }
                memset(visitedIndexes,0,sizeof(visitedIndexes)); //reset
                index = 0; //reset
                accCount = 0; //reset
                currentNopJmpIndex = 0; //reset

                //put this in a function with a pointer to nopJmpIndexes as input. returns the popped index and modifies the original array using the pointer.
                //But then the function would do two things, find the index and set the corresponding index to zero in nopJmpIndexes. Ill just keep it.
                while(nopJmpIndexes[currentNopJmpIndex] != 1) //find the first nop/jmp index and reset that specific index in nopJmpIndexes, keep the index.
                {
                    currentNopJmpIndex++;
                }
                nopJmpIndexes[currentNopJmpIndex] = 0;
                break;
            }

            //changes a nop into a jmp and jmp into a nop.
            if(index == currentNopJmpIndex)
            {
                flipNopAndJmp(str,index);
            }

            accCount += updateAccCount(str[index]);
            visitedIndexes[index] = 1; //mark the index as visited.
            if((str[index][0] == 'j' || str[index][0] == 'n' ) && notFirstRound != 1 )
            {
                nopJmpIndexes[index] = 1; //save the index that has nop or jmp.
            }

            index += getNextIndexChange(str[index]);

        }
        if(str[index][0] == '\0')
        {
            free(str);
            return accCount; //stop if we managed to reach the end.
        }
        else
        {
            notFirstRound = 1;
        }
    }
    //If we reached here it means we reached the end!
    free(str);
    return accCount;

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
    dataArray[k][0] = '\0'; //add a final null line.
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


    if(line[1] == 'o' && atoi(number) == 0) //exception if a nop +0 changed into a jop +0
    {
        return 1;
    }

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
    printf("The accumulator value is:%d\n", accCount);
    return 1;
}





