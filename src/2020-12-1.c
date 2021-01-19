#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_NR_OF_ROWS 1000
#define MAX_LINE_LENGTH 6


//declare functions
FILE * getInputData(char path[]);
int cosd(int degree);
int sind(int degree);


//We have to keep track of the x,y count and also which direction we are currently in so to be able to pass that info back and forth
//through functions. I will make a struct for the important values.

struct navigation
{
    int x; //movment in the W-E plane
    int y; //movment in the N-S plane
    int direction; //Current forward direction in degrees.
};

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
    FILE *fp = getInputData("C:\\Users\\Jonas\\Cprojects\\advent-of-code-2020\\test\\2020-12-1\\2020-12-1-data.txt");
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

void printArray(char ** array)
{
    for(int i =0; *array[i] != '\0'; i++)
        printf("%19s\n",array[i]);
}

int cosd(int degree)
{
    /* returns cosine of 0,90,180 and 270 */
    while(1)
    {
        switch(degree)
        {
        case 0:
            return 1;
        case 90:
            return 0;
        case 180:
            return -1;
        case 270:
            return 0;
        default:
            if(degree < 0) // if the degrees gets too large/small
            {
                degree+=360;
            }
            else
            {
                degree-=360;
            }
        }
    }
}

int sind(int degree)
{
    /* returns sine of 0,90,180 and 270 */
    while(1)
    {
        switch(degree)
        {
        case 0:
            return 0;
        case 90:
            return 1;
        case 180:
            return 0;
        case 270:
            return -1;
        default:
            if(degree < 0) // if the degrees gets too large/small
            {
                degree+=360;
            }
            else
            {
                degree-=360;
            }
        }
    }
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

struct navigation moveForward(struct navigation ferry,int distance)
{
    ferry.x += cosd(ferry.direction)*distance;
    ferry.y += sind(ferry.direction)*distance;

    return ferry;
};

struct navigation initializeNavigationStruct(struct navigation ferry)
{
    ferry.x = 0;
    ferry.y = 0;
    ferry.direction = 0;
    return ferry;
};

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

struct navigation changeDirection(struct navigation ferry,char string[])
{
    if(string[0] == 'R')
        ferry.direction -= strToNr(string);
    if(string[0] == 'L')
        ferry.direction += strToNr(string);
    return ferry;
};

int getManhattanDistance()
{
    char ** dataArray = create2dDataArray();
    dataArray = getDataArray(dataArray);
    struct navigation ferry;
    ferry = initializeNavigationStruct(ferry);

    for(int i=0; *dataArray[i] != '\0'; i++)
    {
        if(dataArray[i][0] == 'F')
        {
            ferry = moveForward(ferry,strToNr(dataArray[i]));
        }
        else if(dataArray[i][0] == 'R' || dataArray[i][0] == 'L')
        {
            ferry = changeDirection(ferry,dataArray[i]);
        }
        else if(dataArray[i][0] == 'N')
        {
            ferry.y += strToNr(dataArray[i]);
        }
        else if(dataArray[i][0] == 'E')
        {
            ferry.x += strToNr(dataArray[i]);
        }
        else if(dataArray[i][0] == 'S')
        {
            ferry.y -= strToNr(dataArray[i]);
        }
        else if(dataArray[i][0] == 'W')
        {
            ferry.x -= strToNr(dataArray[i]);
        }
    }

    printf("x distance:%d, y distance:%d\n",ferry.x,ferry.y);
    return abs(ferry.x)+abs(ferry.y);
}

int main(void)
{
    int manhattanDistance;
    manhattanDistance = getManhattanDistance();
    printf("Manhattan Distance:%d\n",manhattanDistance);
    return 0;
}
