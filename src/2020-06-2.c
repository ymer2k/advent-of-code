#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>




int main(void)
{
    char path[1000] = "C:\\Users\\Jonas\\Cprojects\\advent-of-code-2020\\test\\2020-06-1\\2020-06-1-data.txt";
    FILE *fp = fopen(path,"r");
    //check if we successfully opened the file
    if(fp == NULL)
    {
        printf("Failed to open file\n");
    }

    char questionList[50] = "abcdefghijklmnopqrstuvwxyz";
    char questionListModifiable[50] = {0};
    strcpy(questionListModifiable,questionList);
    int yesQuestionCoutner[30] = {0};
    char str[100] = {0};
    int groupSumCount = 0;
    int totalSumCount = 0;
    int passangersInGroup = 0;
    while(fgets(str,100,fp))
    {
        if(str[0] == '\n')
        {
            //Go through the yesQuestionCounter array and find any question everyone in the group said yes to.
            for(int i=0; i< (sizeof(yesQuestionCoutner)/sizeof(yesQuestionCoutner[0])) ; i++)
            {
                if(yesQuestionCoutner[i] == passangersInGroup )
                {
                    groupSumCount += 1; //give one point if all passengers in a  group said yes to the same question.
                }

            }

            totalSumCount += groupSumCount; //add the groups sum to total sum
            groupSumCount=0; //reset the groups counter.
            passangersInGroup = 0;
            memset(yesQuestionCoutner,0,sizeof(yesQuestionCoutner));
            continue;
        }
        passangersInGroup++;

        //remove the new line character.
        if(str[strlen(str)-1] == '\n')
        {
            str[strlen(str)-1] = '\0';
        }

        for(int index=0; index < strlen(questionListModifiable); index++)
        {
            if(strchr(str,questionListModifiable[index])) //if the specific yes answered question is within the str string.
            {
                yesQuestionCoutner[index] += 1; // counting how often someone said yes to a specific quesiton.

            }

        }
    }

    //Have to do this after we go through all data because of the edge case that the last group does not end with a new line
    for(int j=0; j< (sizeof(yesQuestionCoutner)/sizeof(yesQuestionCoutner[0])) ; j++)
    {
        if(yesQuestionCoutner[j] == passangersInGroup )
        {
            groupSumCount += 1; //give one point if all passengers in a  group said yes to the same question.
        }
    }
    totalSumCount += groupSumCount; //add the groups sum to total sum

    printf("Total sum:%d\n",totalSumCount);
}
