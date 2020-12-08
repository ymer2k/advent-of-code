    #include <stdio.h>
    #include <stdlib.h>



int main(void)
{
    int numberOfPassports=1; // plus 1 because it doesn't end with an empty line
    ////////////////
    char path[1000] = "C:\\Users\\Jonas\\Cprojects\\advent-of-code-2020\\test\\2020-04-1\\2020-04-1-data.txt";
    FILE *fp = fopen(path, "r");


    //check if we successfully opened the file
    if(fp == NULL)
    {

        printf("Failed to open file\n");
    }


    int passportValidCounter=0;
    int dataFieldCounter=0; //Used to count how many data fields a passport has.
    int cidExists=0; //Used to check if cid exists in the passport or not.
    char str[100];

    while(fgets(str,100,fp))
    {
        //check if new line is empty (i.e. contains ONLY a n\)
        if(str[0] == '\n')
        {
            //End of passport. Reset counters
            cidExists = 0;
            dataFieldCounter = 0;
            numberOfPassports++;
        }

        //check if cid exists in the current str
        if(strstr(str,"cid") != NULL)
        {
            cidExists=1;
        }

        //count data fields by checking number of ':'.
        int index=0;
        while(str[index] != NULL)
        {
            if(str[index] == ':')
            {
                dataFieldCounter++;
            }
            index++;
        }

        //check if valid passport
        if(dataFieldCounter == 8 || cidExists == 0 && dataFieldCounter == 7)
        {
            passportValidCounter++;
            dataFieldCounter=0;
        }


    }


    printf("Number of valid passports equals: %d\n",passportValidCounter);
    printf("Total number of passports: %d",numberOfPassports);
}
