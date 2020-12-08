    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
void test(char * str)
{

    //initialize a string that can be modified.
char modifiableStr[100]; //new


    strcpy(modifiableStr,str); //new


if(modifiableStr[strlen(modifiableStr)-1] != '\n') //modified original: if(dataTypeStr[strlen(DataTypeStr)-1] != '\n')
{
    strcat(modifiableStr,"\n"); //modified orginal:  strcat(dataTypeStr,"\n");
}


char src[] = "1.2,3.5,4.2";
char *next = NULL;
char *first = strtok_s(src, ",", &next);



//char * token;
//token = strtok_s(NULL," ");
//        //token = strtok(NULL," ");




}

int check_if_invalid(char * dataTypeStr) //int check_if_invalid(char dataTypeStr[100])
{//input is a broken up data type string
    //returns 0 if invalid

    //initialize a string that can be modified.
char modifiableDataTypeStr[100]; //new


    strcpy(modifiableDataTypeStr,dataTypeStr); //new



    //Some data will end with \n and some will not. This makes sure all of them get a \n in the end.
if(modifiableDataTypeStr[strlen(modifiableDataTypeStr)-1] != '\n') //modified original: if(dataTypeStr[strlen(DataTypeStr)-1] != '\n')
{
    strcat(modifiableDataTypeStr,"\n"); //modified orginal:  strcat(dataTypeStr,"\n");
}


    char * token;
    //take out the data type from the string.
    token = strtok(modifiableDataTypeStr,":"); // modified original:  token = strtok(DataTypeStr,":")

    if(strcmp(token,"byr") == 0)
    {
        //get the rest of the string. (i.e. everything after the :)
        token = strtok(NULL," ");
        if(byr_invalidity_check(token))
        {
            return 1;
        }else{return 0;}
    }

    if(strcmp(token,"iyr") == 0)
    {
        //get the rest of the string. (i.e. everything after the :)
        token = strtok(NULL," ");
        if(iyr_invalidity_check(token))
        {
            return 1;
        }else{return 0;}
    }

        if(strcmp(token,"eyr") == 0)
    {
        //get the rest of the string. (i.e. everything after the :)
        token = strtok(NULL," ");
        if(eyr_invalidity_check(token))
        {
            return 1;
        }else{return 0;}
    }

            if(strcmp(token,"hgt") == 0)
    {
        //get the rest of the string. (i.e. everything after the :)
        token = strtok(NULL," ");
        if(hgt_invalidity_check(token))
        {
            return 1;
        }else{return 0;}
    }

            if(strcmp(token,"hcl") == 0)
    {
        //get the rest of the string. (i.e. everything after the :)
        token = strtok(NULL," ");
        if(hcl_invalidity_check(token))
        {
            return 1;
        }else{return 0;}
    }

            if(strcmp(token,"ecl") == 0)
    {
        //get the rest of the string. (i.e. everything after the :)
        token = strtok(NULL," ");
        if(ecl_invalidity_check(token))
        {
            return 1;
        }else{return 0;}
    }

                if(strcmp(token,"pid") == 0)
    {
        //get the rest of the string. (i.e. everything after the :)
        token = strtok(NULL," ");
        if(pid_invalidity_check(token))
        {
            return 1;
        }else{return 0;}
    }


    //When type of field is identified either call a new function to check the rules for that specific field or check it directly here. I think  new function is cleeaner.



}

int byr_invalidity_check(char * dataStr)
{

    if(  (strlen(dataStr) == 5)  && ( (1920 <= atoi(dataStr)) && (atoi(dataStr) <= 2002) ) ) //bug here. It strlen() counts the new line character \n as well so real length is 5.
    {
            return 1;
    }else{ return 0;}
}

int iyr_invalidity_check(char * dataStr)
{
    if(  strlen(dataStr) == 5 && ( (2010 <= atoi(dataStr)) && (atoi(dataStr) <= 2020) ) )
    {
            return 1;
    }else{ return 0;}
}

int eyr_invalidity_check(char * dataStr)
{
    if(  strlen(dataStr) == 5 && ( (2020 <= atoi(dataStr)) && (atoi(dataStr) <= 2030) ) )
    {
            return 1;
    }else{ return 0;}
}

int hgt_invalidity_check(char * dataStr)
{
    char number[10];
    char unit[10];
    size_t stringLength = strlen(dataStr);

//check of invalid data i.e. no unit.
    if(stringLength < 5) // smaller than 5 because of the \n in the end
    {
        return 0;
    }


    memcpy(unit, &dataStr[stringLength-3],2); // minus 3 because of \n in the end + in or cm.
    unit[2]= '\0';
    if(unit[0] == 'c')
    {
        memcpy(number, &dataStr[0],3); //3 because its cm so should be three numbers.
        number[3] = '\0';
        if( ( (150 <= atoi(number)) && (atoi(number) <= 193) ) )
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    if(unit[0] == 'i')
    {
        memcpy(number, &dataStr[0],2); //2 because its cm so should be three numbers.
        number[2] = '\0';
        if( ( (59 <= atoi(number)) && (atoi(number) <= 76) ) )
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

int hcl_invalidity_check(char * dataStr)
{
        char legalChars[] = "0123456789abcdef";
        size_t stringLength = strlen(dataStr);
        int legalCharCounter=0;

        if(dataStr[0] != '#')
        {
            return 0;
        }

// All valid data has to be 8 characters including \n
    if(stringLength != 8)
    {
        return 0;
    }

    for(int index=1; index < strlen(dataStr)-1 ;index++) //-1  because of \n  //start on 1 to avoid the #
    {
        for(int index2=0; index < strlen(legalChars)-1;index2++) //-1 because of zero indexing.
        {
                    if(dataStr[index] == legalChars[index2])
                    {
                        legalCharCounter++;
                        break; //found the legal Char so can break this loop to change to the next char in dataStr
                    }

        }
    }
if(legalCharCounter != 6) //not counting #
{
    return 0;
}else{return 1;}


}

#define NUMBER_OF_STRINGS 6
#define MAX_STRING_SIZE 10 //should work with this as 4 but doesn't for some reason. Has to be 5 or more. Still dont understand why.
int ecl_invalidity_check(char * dataStr)
{
    int legalStringCounter = 0;
    size_t stringLength = strlen(dataStr);

      // All valid data has to be 3 characters including \n
    if(stringLength != 4)
    {
        return 0;
    }

        char legalStrings[NUMBER_OF_STRINGS][MAX_STRING_SIZE] =
        { "amb\n",
          "blu\n",
          "brn\n",
          "gry\n",
          "hzl\n",
          "oth\n"
        };




        for(int index=0; index < NUMBER_OF_STRINGS;index++)
        {
                    if( strcmp(dataStr,legalStrings[index]) == 0)
                    {
                        legalStringCounter++;
                        break; //found the legal String so can break this loop. LegalStringCounter can not get higher than 1 anyway because we block strings longer than 4.
                    }

        }

if(legalStringCounter != 1)
{
    return 0;
}else{return 1;}


}

int pid_invalidity_check(char * dataStr)
{
            int legalCharCounter=0;

    if(  strlen(dataStr) != 10) //9 digits plus \n
    {
            return 0;
    }

    if(dataStr[0] != '0')
    {
            return 0;
    }

    char legalChars[] = "0123456789";



    for(int index=0; index < strlen(dataStr)-1 ;index++) // -1 because of \n
    {
        for(int index2=0; index < strlen(legalChars)-1;index2++) //-1 because of zero indexing.
        {
                    if(dataStr[index] == legalChars[index2])
                    {
                        legalCharCounter++;
                        break; //found the legal Char so can break this loop to change to the next char in dataStr
                    }

        }
    }

if(legalCharCounter != 9)
{
    return 0;
}else{return 1;}
}

int main(void)
{
char string[] = "eyr:1972 cid:100";
char * test_token;
test_token = strtok(string," ");
    test(test_token);

    test_token = strtok(NULL," ");

    /////---------------Test end--------------------/////////
    int numberOfPassports=1; // plus 1 because it doesn't end with an empty line
    ////////////////
    char path[1000] = "C:\\Users\\Jonas\\Cprojects\\advent-of-code-2020\\test\\2020-04-1\\2020-04-2-data-invalid.txt";
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
    char * token;
    char strTok[100]; //This variable is used to be modified by the strtok function
    int validData=1; //1 is valid.


    while(fgets(str,100,fp))
    {
        strcpy(strTok,str); //I copy str to strTok because str gets modified in strtok if I would have used it there.

        //split up data fields.
        //get first token
        token = strtok(strTok," ");

        //get the other tokens
        while(token != NULL)
        {
            if(token != "\n")
            {

               validData = check_if_invalid(token); //Check if the tokens data is invalid

            }
            token = strtok(NULL," ");
        }


        //check if new line is empty (i.e. contains ONLY a n\)
        if(str[0] == '\n')
        {
            //End of passport. Reset counters
            cidExists = 0;
            dataFieldCounter = 0;
            numberOfPassports++;
            continue; //we dont have to do the rest below for the new line.
        }

        //check if cid exists in the current str //This should be made into a function.
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
        if(dataFieldCounter == 8 && validData == 1 || (cidExists == 0 && dataFieldCounter == 7 && validData == 1))
        {
            passportValidCounter++;
            dataFieldCounter=0;
        }

    }


    printf("Number of valid passports equals: %d\n",passportValidCounter);
    printf("Total number of passports: %d",numberOfPassports);
}
