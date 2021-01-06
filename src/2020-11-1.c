#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_NR_OF_ROWS 100
#define MAX_LINE_LENGTH 110
#define EMPTY_SEAT 'L'
#define OCCUPIED_SEAT '#'
#define FLOOR '.'

//#define EXACT_LINE_LENGTH 11 //(example data)
#define EXACT_LINE_LENGTH 99 //(real data)

//Adjacent seat numbers (example data)
//#define TOP_LEFT -13
//#define TOP -12
//#define TOP_RIGHT -11
//#define LEFT -1
//#define RIGHT 1
//#define BOTTOM_LEFT 11
//#define BOTTOM 12
//#define BOTTOM_RIGHT 13

//Adjacent seat numbers (real data)
#define TOP_LEFT -101
#define TOP -100
#define TOP_RIGHT -99
#define LEFT -1
#define RIGHT 1
#define BOTTOM_LEFT 99
#define BOTTOM 100
#define BOTTOM_RIGHT 101

//declare functions
FILE * getInputData(char path[]);


char * createDataArray1D()
{
    //Allocate memory on the Heap
    char *dataArray = malloc(MAX_LINE_LENGTH*MAX_NR_OF_ROWS * sizeof(char));
    return dataArray;
}

char * getBorder(char *dataArray)
{
    /* Adds a line of X as a border. */
    for(int i=0; i<EXACT_LINE_LENGTH+1; i++) //+1 for the border
    {
        dataArray[i] = 'X';
    }
    dataArray[EXACT_LINE_LENGTH+1] = '\n';
    dataArray[EXACT_LINE_LENGTH+2] = '\0';
    return dataArray;
}

char * getDataArray1D(char *array)
{
    /* Gets data and adds a border around it. \n acts as the right side border. */
    char str[MAX_LINE_LENGTH] = {0};
    FILE *fp = getInputData("C:\\Users\\Jonas\\Cprojects\\advent-of-code-2020\\test\\2020-11-1\\2020-11-1-data.txt");
    //Add top border
    char border[EXACT_LINE_LENGTH+2+1] = {0}; // +2 for the border and +1 for the '\0'. Should just make it a couple elements too big but no.
    strcat(border,getBorder(array));

    while(fgets(str,MAX_LINE_LENGTH,fp) != NULL )
    {
        strcat(array,"X"); // add left side border
        strcat(array,str);
    }
    strcat(array,"\n"); // add new line char to the last line just for consistency
    //add bottom border
    strcat(array,border);
    return array;
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

int checkAdjecentRuleTwo(char *dataArray, int index)
{
    /* Checks if 4 our more adjacent seats are occupied. Returns 0 if occupied and 1 if not occupied */
    int adjacentIndex[8] = {TOP_LEFT, TOP, TOP_RIGHT, LEFT, RIGHT, BOTTOM_LEFT, BOTTOM, BOTTOM_RIGHT};
    int occupiedSeats = 0;
    for(int i=0; i < 8; i++)
    {
        if(dataArray[adjacentIndex[i]+index] == '#')
        {
            occupiedSeats++;
        }
        if(occupiedSeats >= 4)
        {
            return 1;
        }
    }
    return 0;
}

int checkAdjecentRuleOne(char *dataArray,int index)
{
    /* Checks the adjacent seats if they are occupied or not. Returns 0 if occupied and 1 if not occupied */
    int adjacentIndex[8] = {TOP_LEFT, TOP, TOP_RIGHT, LEFT, RIGHT, BOTTOM_LEFT, BOTTOM, BOTTOM_RIGHT};
    for(int i=0; i < 8; i++)
    {
        if(dataArray[adjacentIndex[i]+index] == '#')
        {
            return 0;
        }
    }
    return 1;
}

int applyRuleTwo(char *dataArray,int index)
{
    if (dataArray[index] == '#' && checkAdjecentRuleTwo(dataArray,index) )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int applyRuleOne(char * dataArray, int index)
{
    if( dataArray[index] == 'L' && checkAdjecentRuleOne(dataArray,index) )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void printNrOfOccupiedSeats(char * dataArray)
{
    int occupiedSeats=0;
    for(int i = 0; dataArray[i] != '\0'; i++)
    {
        if(dataArray[i] == '#')
        {
            occupiedSeats++;
        }
    }
    printf("Number of Occubied Seats:%d",occupiedSeats);
}

void printArea(char * dataArray)
{
    printf("\n\n\n");
    for(int i = 0; dataArray[i] != '\0'; i++)
    {
        printf("%c",dataArray[i]);
    }
}

void simulateSeating()
{
    char * dataArray;
    dataArray = createDataArray1D();
    dataArray = getDataArray1D(dataArray);

    char tempArray[MAX_LINE_LENGTH*MAX_NR_OF_ROWS] = {0};
    strcpy(tempArray,dataArray);

    //printArea(dataArray);
    for(int j=0; j<99; j++) //repeat how many rounds the rules apply.
    {
        for(int i = 0; dataArray[i] != '\0'; i++)
        {
            if(applyRuleOne(dataArray,i))
            {
                tempArray[i] = '#';
            }

            if(applyRuleTwo(dataArray,i))
            {
                tempArray[i] = 'L';
            }
        }
        if(strcmp(dataArray,tempArray) == 0) //Break when new rounds does not change the array.
        {
            strcpy(dataArray,tempArray);
            printArea(dataArray);
            printf("\n\n\nNumber of rounds:%d\n",j);
            break;
        }
        else
        {
            strcpy(dataArray,tempArray);
            //printArea(dataArray);
        }
    }

    printNrOfOccupiedSeats(dataArray);
    free(dataArray);
}

int main(void)
{
    simulateSeating();
    return 0;
}
