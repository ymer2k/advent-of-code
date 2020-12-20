#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LINE_SIZE 200
#define OUR_BAG "shiny gold"
#define EMPTY_BAG " no other bags"

//declare functions
int getMainBagSeperateIndex(char line[MAX_LINE_SIZE]);
int getNextIndexForContentBag(char line[MAX_LINE_SIZE]);


FILE * getInputData(char path[])
{
    FILE *fp = fopen(path,"r");
    if(fp == NULL)
    {
        printf("Failed to open file\n");
    }
    return fp;
}

int getParentBagCount(char bagName[])
{
    int temp=0;
    int product =0;
    int parentMultiplier=0;
    char str[MAX_LINE_SIZE] = {0};
    FILE *fp;

    fp = getInputData("C:\\Users\\Jonas\\Cprojects\\advent-of-code-2020\\test\\2020-07-1\\2020-07-1-data.txt");
    while(fgets(str,MAX_LINE_SIZE,fp) != NULL)
    {
        char nextBagInContent[MAX_LINE_SIZE] = {0};
        char bagContent[MAX_LINE_SIZE] = {0};
        char parentBag[MAX_LINE_SIZE] = {0};
        int mainBagSeperateIndex = getMainBagSeperateIndex(str);
        memcpy( bagContent, &str[mainBagSeperateIndex], strlen(str) ); // get what is in the parent bag.

        //extract the parent bag from the string.
        memcpy( parentBag, &str[0], mainBagSeperateIndex );
        parentBag[mainBagSeperateIndex]= '\0'; //To make sure the string ends properly. Good practice.

        if(strstr(parentBag,bagName) != NULL) // checks if the bagName we are looking at is this lines's parent. IF IT IS THEN GO IN
        {

            if(strstr(bagContent,EMPTY_BAG) != NULL) // CHECK if bagContent is empty
            {
                return 0;
            }

            //get the index for the next bag in content
            int nextBagContentIndex = getNextIndexForContentBag(bagContent);

            while(nextBagContentIndex != -1) //repeat taking next bags from the content bag until we can't find anymore.
            {
                //get the parentMultiplier
                parentMultiplier = bagContent[1]-'0'; // since atoi doesn't work with individual chars this works instead. 1 because the number is after a space

                memcpy( nextBagInContent, &bagContent[3], nextBagContentIndex-3 ); // get the next bag in bagContent bagContent[3] and -3 to remove the number in front and shift it back 3.
                nextBagInContent[nextBagContentIndex-3] = '\0'; // to end the string properly.
                memcpy(bagContent,&bagContent[nextBagContentIndex+1],strlen(bagContent)); // Exclude the nextBagInContent from bagContent. +1 to remove the ','

                if(nextBagInContent[strlen(nextBagInContent)-1] == 's') //check if the the last char is an 's' in bags. Because that causes problems. -1 because of zero index
                {
                    nextBagInContent[strlen(nextBagInContent)-1] = '\0'; // remove the 's'. -1 because of zero index
                }

                //the recursive equation:
                //1+temp because all the bags inside of temp should be multiplied by the number of parent bags.
                //1 because we need to include how many parent bags there were in the count count!
                temp = getParentBagCount(nextBagInContent);
                product += parentMultiplier * (1 + temp);

                nextBagContentIndex = getNextIndexForContentBag(bagContent); // Now that child is finished, go to the next child on this line.
            }
        }
    }
    //This could be optimized. after we found the parent we were looking for and checked all the children, we will be returned to the loop of the parent.
    //Even though we found the parent it will still go through the rest of the list until the end and the reach the return statement.
    //Could fix it with some check that looks if we already found the parent and then we can immediately return after going through all the parents children but this is good enough.
    return product;
}

int getMainBagSeperateIndex(char line[MAX_LINE_SIZE])
{
    //returns the index after the four first spaces in the input string.
    int spaceCount = 0;
    for(int i=0; line[i] != '\n'; i++)
    {
        if(line[i] == ' ')
        {
            spaceCount++;

            if(spaceCount == 4)
            {
                return i;
            }
        }
    }
    return -1;
}

int getNextIndexForContentBag(char line[MAX_LINE_SIZE])
{
    int i =0;
    //returns the index after the three first spaces in the input string. i.e. the next bag that the parent contains.
    while(line[i] != '\0')
    {
        if(line[i] == ',' || line[i] == '.')
        {
            return i; //
        }
        i++;
    }
    return -1;
}

char * doesBagExist(char bagContent[], char bagName[])
{
    //checks if bag is contained within the current bags content
    return strstr(bagContent,bagName);
}

int main(void)
{
    int bagCounter = getParentBagCount(OUR_BAG);
    printf("Total nr of parent bags:%d",bagCounter);
    return 1;
}
