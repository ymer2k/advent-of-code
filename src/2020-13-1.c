#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_NR_OF_ROWS 10
#define MAX_LINE_LENGTH 200


//declare functions
FILE * getInputData(char path[]);


char ** create2dDataArray()
{
    //allocate memory on the heap.
    char **dataArray = malloc(MAX_NR_OF_ROWS * sizeof(char *));
    for(int i=0; i != MAX_NR_OF_ROWS; ++i)
    {
        dataArray[i] = malloc(MAX_LINE_LENGTH * sizeof(char));
    }
    return dataArray;
}

char** getDataArray(char ** dataArray)
{
    //Fill the 2d array pointer with data.
    char str[MAX_LINE_LENGTH] = {0};
    int k = 0;
    FILE *fp = getInputData("C:\\Users\\Jonas\\Cprojects\\advent-of-code-2020\\test\\2020-13-1\\2020-13-1-data.txt");
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

int getStringLength(char dataArray[])
{
    int i = 0;
    while(dataArray[i] != '\0')
    {
        i++;
    }
    return i;
}

int strToNr(char string[])
{
    int stringLength = getStringLength(string);
    char number[5];
    int i;
    for(i=0; string[i] > '9'; i++) //Skip any numbers in front of the number.
        ;
    memcpy(number,&string[i],stringLength);
    number[stringLength]='\0';
    return atoi(number);

}

void findEarliestBus()
{
    char ** dataArray = create2dDataArray();
    dataArray = getDataArray(dataArray);
    int depatureTime = atoi(dataArray[0]);
    char * token;
    const char s[2] = ",";
    int tempID = 0;
    int tempWaitTime = 0;
    int currentWaitTime = 0;

    //Get first token
    token = strtok(dataArray[1],s);
    tempID = strToNr(token);
    tempWaitTime = tempID - (depatureTime % tempID);


    //get the rest of the tokens
    while( token != NULL)
    {
        if(token[0] == 'x') //skip if and x
        {
            token = strtok(NULL,s);
            continue;
        }

        if((currentWaitTime=strToNr(token)-(depatureTime % strToNr(token))) < tempWaitTime) //compare and save the shortest wait time
        {
            tempWaitTime = currentWaitTime;
            tempID = strToNr(token);
        }
        token = strtok(NULL,s);
    }

    printf("shortest wait time:%d ID:%d answer:%d",tempWaitTime,tempID,tempID*tempWaitTime);
}

int main(void)
{
    findEarliestBus();
    return 0;
}
