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
    int yesQuestionCoutner = 0;
    char str[100] = {0};
    int groupSumCount = 0;
    int totalSumCount = 0;
    while(fgets(str,100,fp))
    {
        if(str[0] == '\n')
        {
            totalSumCount += groupSumCount; //add the groups sum to total sum
            groupSumCount=0; //reset the groups counter.
            strcpy(questionListModifiable,questionList);        //reset questionListModifiable back to its original state.
            continue;
        }

        //remove the new line character.
        if(str[strlen(str)-1] == '\n')
        {
            str[strlen(str)-1] = '\0';
        }

        for(int index=0; index < strlen(questionListModifiable); index++)
        {
            if(strchr(str,questionListModifiable[index])) //if the specific yes answered question is within the str string.
            {
                questionListModifiable[index] = '0'; // modify the question list to remove the questions this group already answered yes to
                yesQuestionCoutner++;
            }

            if(yesQuestionCoutner == strlen(str)) //This unfortunately does not work for groups that answered yes on the same questions...
                //Should be changed so it does not continue looping until the end.
            {
                break;
            }
        }
        groupSumCount += yesQuestionCoutner; // add this passangers yes answers to the groups count.
        yesQuestionCoutner = 0; //reset the counter for this passanger
    }

    //Have to do this after we go through all data because of the edge case that the last group does not end with a new line
    totalSumCount += groupSumCount;

    printf("Total sum:%d\n",totalSumCount);
}
