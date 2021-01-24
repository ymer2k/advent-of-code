#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_NR_OF_ROWS 10
#define MAX_LINE_LENGTH 200

/*Made a non general solution. Will only work for my data input. Can be made into a general solution by checking to see which numbers are has many steps
away as the ID itself. For example in the example ID 7 is 7 steps away from ID 19. Just moving on from this one.
The problem is that, in my case ID13 is 13 steps away from 419 and 41,37 and 17 is correct number of steps away from 421 but I can only choose 419 or 421.
So I would have to do that separates the two and choose the one with the highest product. In my case 41*37*421*17 is much smaller than 13*419. So I would choose
the former.

Just getting the product could be done something like this

    for(int k=0; count>k; k++)
    {
        if( ( IDPosition[id[k]] + id[k] ) <= (sizeof(IDPosition) / sizeof(int)) && IDPosition[ IDPosition[id[k]] + id[k] ] != 0  )
        {
            stepSize *= id[k];
        }else if( ( IDPosition[id[k]] - id[k] ) >= 0 && IDPosition[ IDPosition[id[k]] - id[k] ] != 0  )
        {
            stepSize *= id[k];
        }
    }

    But I'm not sure right now how to separate 419 products and 421. Would maybe do the loop once and continue with the first find and then replace 419 with
    an x in the next loop or something. Anyway I will just leave this assignment now.

*/
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



void validate(long long time,int IDPosition[],int id[],int IdCount)
{
    /* Checks if all the IDs are in the right position  */
    time -= IDPosition[421]; // to get to IDPosition for 13 (first ID).
    for(int j=0; IdCount > j; j++) //go through all IDs and test if their t mod with itself is zero.
    {

        if( (time + IDPosition[id[j]]) % id[j])
        {
            printf("%d is wrong\n",id[j]);
        }

    }
    printf("all IDs correct\n");
}

void winContest()
{
    char ** dataArray = create2dDataArray();
    dataArray = getDataArray(dataArray);
    char * token;
    const char s[2] = ",";
    int tempID = 0;
    int count =0;
    int position = 0;
    int id[100] = {0};
    int IDPosition[2000]= {0};
    char tempString[200] = {0};
    strcpy(tempString,dataArray[1]);
    //Get first token
    token = strtok(tempString,s);
    tempID = strToNr(token);

    //get the rest of the tokens
    while( token != NULL)
    {
        if(token[0] == 'x') //skip if and x
        {
            position++;
            token = strtok(NULL,s);
            continue;
        }

        tempID = strToNr(token);

        IDPosition[tempID] = position; //save the position in the vector of the current ID.
        id[count] = tempID;
        token = strtok(NULL,s);

        count++;
        position++;
    }
    int matches =0; //counts how many IDs depart in the right order compared to the largestID
    int i;
    long long int currentTime = 0;
    //int idReduced[] = {13,19,23,29,419}; //can reduce the id check to only these nr because we know that the numbers used to get the stepsize (currentTime) will be correct
    //count-=4; //remove some Ids to check because we already know that they are correct (slight speedup)
    for(i = 1; matches != count; i++) //loop until we find all matches ie. the right t that solves the problem.
    {
        for(int j=0; count > j; j++) //go through all IDs and test if their t mod with itself is zero.
        {
            /* we need to check for a certain time step if at that time step each ID has a zero mod with itself. If all match then we found the right time */
            //current time will be for the correct position for ID 421. so adjust from there.

            currentTime = (long long) 41*37*421*17*i; //This will step every time these IDs depart at the same time, which WILL happen in the coorrect answer.

            if( (currentTime+(IDPosition[id[j]]-IDPosition[421])) % id[j] != 0 ) //CHANGE to idreduced if reduced one is used.
            {
                matches=0;
                break; //go to the next i iteration.
            }
            else
            {
                matches++;
            }
        }

    }
    validate(currentTime,IDPosition,id,9); //used to check
    printf("%d\n",i);
    printf("Earliest Timestamp is:%I64d",(currentTime)-IDPosition[421]);
}

int main(void)
{
    winContest();
    return 0;
}
