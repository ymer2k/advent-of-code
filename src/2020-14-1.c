#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_NR_OF_ROWS 600
#define MAX_LINE_LENGTH 200
#define BIT_LENGTH 36
#define MAX_MEM_SIZE 99999


//declare functions
FILE * getInputData(char path[]);
char * decToBin(int decNr);

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
    FILE *fp = getInputData("C:\\Users\\Jonas\\Cprojects\\advent-of-code-2020\\test\\2020-14-1\\2020-14-1-data.txt");
    while(fgets(str,MAX_LINE_LENGTH,fp) != NULL )
    {
        strcpy(dataArray[k],str);
        k++;
    }

    dataArray[k][0] = '\0'; //Put a null char on the last line.
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

int getMemoryAddress(char charArray[])
{
    char *p1, *p2;
    char number[10] = {0};

    p1 = strstr(charArray,"["); //get pointer to first bracket.
    p2 = strstr(charArray,"]"); //get pointer to second bracket.
    //printf("%.*s\n",p2-p1-1,p1 + 1);
    memcpy( number, &p1[1], p2-p1-1 ); //copy the number inside the brackets.

    return atoi(number);
}

int getValue(char charArray[])
{
    char *p1;
    p1 = strstr(charArray,"="); //get pointer to equal sign.
    return atoi(p1+1);
}

char * applyMask(char value[],char mask[])
{
    char * result = malloc((BIT_LENGTH+1) * sizeof(char));
    for(int n=0; n<BIT_LENGTH; n++)
    {
//        if(mask[n] == 'X')
//            {
//            result[n]=value[n];
//            }else
//            {
//                result[n]=mask[n];
//            }
        result[n] = (mask[n] == 'X') ? value[n] : mask[n]; //shorter way to write the above commented code.

    }
    result[BIT_LENGTH]='\0';
    return result;
}

long long binToDecV2(char binNr[],int startPwr, long long sum)
{
    /* binary numbers to dec numbers, splits the array up into 4 bit chunks */
    int chunkSize = 4;
    char subString[5]= {0};
    int i=0; // first 2^0.
    for(int k=1; k * chunkSize <= BIT_LENGTH; k++)
    {
        //take out 4 bits each cycle
        memcpy(subString,&binNr[(BIT_LENGTH)-(k*chunkSize)],chunkSize);
        printf("subString:%s\n",subString);

        long long n = atoll(subString);
        long long dec = 0, rem;
        while (n != 0)
        {
            rem = n % 10;
            n /= 10;
            dec += rem * pow(2, i);
            ++i;
        }
        sum += dec;
        i=k*chunkSize; //change the power to start at the next chunk (eg. second chunk start at 2^4)
    }
    printf("sum:%I64d\n",sum);
    return sum;
}

void sumValues()
{
    int memoryAddress;
    int value;
    char * binValuePointer;
    char ** dataArray = create2dDataArray();
    //Have to put it on the heap because its too big to put on stack. Calloc initializes the allocated memory to zero.
    long long *mem = calloc( MAX_MEM_SIZE, sizeof(long long));
    dataArray = getDataArray(dataArray);
    char mask[BIT_LENGTH+1] = {0}; //plus one for  null char

    int n;
    for(n =0; dataArray[n][0] != '\0' ; n++)
    {
        if(dataArray[n][1] == 'a') //check if we reached a new mask
        {
            memcpy(mask,&dataArray[n][7],BIT_LENGTH); // Get only the bit part of the mask line.
            printf("mask:%s\n",mask);
            continue; //since we reached a new mask we can go to the next line.
        }
        //the remaining code just applies the mask to the value and saves it at the corresponding mem address.

        //get the memory address
        memoryAddress = getMemoryAddress(dataArray[n]);
        printf("%d\n",memoryAddress);

        //get the value to be written to the memoryAddress.
        value = getValue(dataArray[n]);
        printf("%d\n",value);

        //convert the value to 36bit binary numbers (chars).
        binValuePointer = decToBin(value);
        printf("%s\n",binValuePointer);

        char * finalResultBin = applyMask(binValuePointer,mask);
        printf("QUICK RESULT:%s\n",finalResultBin);

        /*Now we can properly apply the mask to values. Now we have to convert the result of the mask back to
        decimal numbers.
        */
        long long finalResultDec = binToDecV2(finalResultBin,0,0);

        //long long finalResultDec = binToDec(finalResultBin);
        printf("Final dec result:%I64d\n",finalResultDec);

        /*
        Now we have to create an int array to store the dec value
         of the result of each mask.  */
        //Save the result to the mem array.
        mem[memoryAddress] = finalResultDec;
    }

    /*
    sum all values left in mem.
    To make it faster, save all memory addresses in another int array.
    Then loop through the memory address int array and use it for mem to sum all the values left in memory!
    Simple.
    */
    long long sum=0;
    for(int k=0; k<MAX_MEM_SIZE; k++)
    {
        sum += mem[k];
    }
    printf("sum of all values in mem:%I64d\n",sum);
}

char * decToBin(int decNr)
{
    /* Converts a decimal number to binary string. Returns a pointer to char binary number. */
    char charArray[BIT_LENGTH+1] = {0};
    char tempArray[BIT_LENGTH+1] = {0};

    /* Tried to malloc immediately on tempArray but it just gave trash data even though I added zeros infront. Now instead
    I do all the changes on tempArray then just in the end copy it over to tempArrayPointer and return that. */
    char *tempArrayPointer = malloc((BIT_LENGTH+1) * sizeof(char));
    int a[BIT_LENGTH],i;
    //Special case if decNr is 0. Then just return a 36 zero string.
    if(decNr == 0)
    {
        for(int j=0; j<BIT_LENGTH; j++)
        {
            tempArray[j] = '0';
        }
        strcpy(tempArrayPointer,tempArray);
        printf("%s",tempArrayPointer);
        return tempArrayPointer;
    }

    for(i=0; decNr>0; i++)
    {
        a[i]=decNr%2;
        decNr=decNr/2;
    }

    //flip the bits to the opposite order and convert to a char array
    int pos=0;
    for(i=i-1; i>=0; i--) // The bit order is inverted so this for loop switches them to the right position
    {
        charArray[pos] = a[i] + '0'; // convert to chars.
        pos++;
    }

    //Add leading zeros in the beginning of the string.
    int k = BIT_LENGTH-strlen(charArray); //How many zeros to add.

    for(int j=0; j<k; j++)
    {
        tempArray[j] = '0';
    }
    strcat(tempArray,charArray); //Add the bin number at the end of the leading zeros.


    strcpy(tempArrayPointer,tempArray); //Just Copy everything to the pointer and return it.
    printf("\n%s\n",tempArrayPointer);
    return tempArrayPointer;
}

int main(void)
{
    //decToBin(11);
    sumValues();
    return 0;
}
