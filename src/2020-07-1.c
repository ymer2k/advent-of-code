#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LINE_SIZE 200
#define MAX_BAG_NAME_SIZE 30
#define MAX_PARENT_COUNT 400

FILE * getInputData(char path[])
{
    FILE *fp = fopen(path,"r");

    if(fp == NULL)
    {
        printf("Failed to open file\n");
    }

    return fp;
}

int getParentBagCount(char bagName[],char (*pointerToParentBagsFound)[MAX_BAG_NAME_SIZE])
{
    //char parentBagsFound[MAX_PARENT_COUNT][MAX_BAG_NAME_SIZE] = {{0}};
    int parentBagCounter = 0;
    char str[MAX_LINE_SIZE] = {0};
    FILE *fp;

    fp = getInputData("C:\\Users\\Jonas\\Cprojects\\advent-of-code-2020\\test\\2020-07-1\\2020-07-1-data.txt");
    while (!feof(fp))
    {
        fgets(str, MAX_LINE_SIZE, fp);

        char bagContent[MAX_LINE_SIZE] = {0};
        char parentBag[MAX_LINE_SIZE] = {0};
        int mainBagSeperateIndex = getMainBagSeperateIndex(str);
        memcpy( bagContent, &str[mainBagSeperateIndex], strlen(str) );

        if(doesBagExist(bagContent,bagName))
        {
            //extract the parent bag from the string.
            memcpy( parentBag, &str[0], mainBagSeperateIndex-1 ); // -1 to not get the s on "bags"
            int index = getNewParentIndexIfNewParent(parentBag,pointerToParentBagsFound); // The index is just the first empty row.
            if( 0 <= index)
            {
                parentBagCounter++;
                strcpy(pointerToParentBagsFound[index],parentBag); //save  found parent bag;
                parentBagCounter += getParentBagCount(parentBag,pointerToParentBagsFound); //Enter the function again with the new parent bag
            }
        }
    }
    //No parent bag found
    return parentBagCounter;
}

int getMainBagSeperateIndex(char line[MAX_LINE_SIZE])
{
    //returns the index after the three first spaces in the input string.
    int spaceCount = 0;
    for(int i=0; line[i] != '\n'; i++)
    {
        if(line[i] == ' ')
        {
            spaceCount++;

            if(spaceCount == 3)
            {
                return i;
            }
        }
    }
}

int doesBagExist(char bagContent[], char bagName[])
{
    //checks if bag is contained within the curernt bags content
    return strstr(bagContent,bagName);
}

int getNewParentIndexIfNewParent(char parentBag[],char (*parentBagsFound)[MAX_BAG_NAME_SIZE])
{
    //If not in the list returns the index to put the new parent bag.
    int parentBagsFoundLength = getArrayLength(parentBagsFound);
    for(int i=0; i < parentBagsFoundLength ; i++)
    {
        if(strcmp(parentBagsFound[i],parentBag) == 0) //If we already added the parent bag then dont explore that bag again.
        {
            return -1; //It is in the array so not new parent.
        }
    }
    return parentBagsFoundLength; //It is not in the list. returns index for new parent
}

int getArrayLength(char (*array)[MAX_BAG_NAME_SIZE])
{
    //checks how many strings the array has.
    int i =0;
    while(*( *(array + i) + 0) != 0) // *( *(array + i) + 0) means we will access the first element of each row.
    {
        //printf("array element:%d equals:%s\n",i,array[i]);
        i++;
    }
    return i;
}

int main(void)
{
    int bagCounter = 0;
    char parentBagsFound[MAX_PARENT_COUNT][MAX_BAG_NAME_SIZE] = {{0}}; //an array where we store our already found parent bags
    const char ourBag[] = "shiny gold";
    bagCounter += getParentBagCount(ourBag,&parentBagsFound);
    printf("Total nr of parent bags:%d",bagCounter);
    return 1;

}
