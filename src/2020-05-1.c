#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


int cmpfunc (const void * a, const void * b)
{
    return ( *(int*)a - *(int*)b );
}

int convert_to_decimal(char seatPosBinary[])
{
    //remove leading zeros
    while(seatPosBinary[0] == '0')
    {
        seatPosBinary++; //pointer arithmetics increases the pointers address by 1, removing the first element.
    }

    //convert to long long
    char *eptr;
    long long n = strtoll(seatPosBinary, &eptr, 10);

    int dec = 0, i = 0, rem;
    while (n != 0)
    {
        rem = n % 10;
        n /= 10;
        dec += rem * pow(2, i);
        ++i;
    }
    return dec;
}

char * convert_letters_to_binary(char seatPosLetters[])
{
    char * mySeatInfo;
    mySeatInfo = malloc (sizeof(char)*50);
    char mySeatInfoTemp[50] = {0};
    int index = 0;
    while(index < 10)
    {
        if(seatPosLetters[index] == 'L' || seatPosLetters[index] == 'F')
        {
            mySeatInfoTemp[index] = '0';
        }
        else
        {
            mySeatInfoTemp[index] = '1';
        }
        index++;
    }

    strcpy(mySeatInfo,mySeatInfoTemp);

    return mySeatInfo;
}

int main(void)
{
    char path[1000] = "C:\\Users\\Jonas\\Cprojects\\advent-of-code-2020\\test\\2020-05-1\\2020-05-1-data.txt"; // Added some space for array[0]

    FILE *fp = fopen(path, "r");

    //check if we successfully opened the file
    if(fp == NULL)
    {
        printf("Failed to open file\n");
    }

    int seatIDs [1000] = {0};
    char seatRow[100] = {0};
    char seatCol[100] = {0};
    int highestID=0;
    int index = 0;
    int seatRowDec[1000] = {0};
    int seatColDec[1000] = {0};
    char * seatInfoBinary;
    char str[50];
    while(fgets(str,50,fp))
    {
        seatInfoBinary = convert_letters_to_binary(str);
        memcpy(seatRow,&seatInfoBinary[0],7);
        memcpy(seatCol,&seatInfoBinary[7],3);

        seatRowDec[index] = convert_to_decimal(seatRow);
        seatColDec[index] = convert_to_decimal(seatCol);

        seatIDs[index] = seatRowDec[index]*8+seatColDec[index];
        if(highestID < ( seatIDs[index] ) )
        {
            highestID = seatIDs[index];
        }
        index++;
    }

    // Part 2. Find my seat ID.
    size_t lengthOfSeatIDs = sizeof(seatIDs)/sizeof(seatIDs[0]);

    qsort(seatIDs, lengthOfSeatIDs, sizeof(int), cmpfunc);


    for(int i=0; i < lengthOfSeatIDs-2; i++) //because we look 2 ahead. in the if statement
    {
        if((seatIDs[i+2]-seatIDs[i]) == 3 )
        {
            printf("My seat ID:%d\n",seatIDs[i+1]+1);
            break;
        }
    }
    printf("HighestID:%d\n",highestID);
    free(seatInfoBinary);
}
