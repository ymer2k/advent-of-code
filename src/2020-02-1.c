    #include <stdio.h>
    #include <stdlib.h>

    int check_valid_password_part2(char *password,char *letter, int min, int max)
    {
        int letterCount =0;
        if(password[min-1] == letter[0])
        {
            letterCount++;
        }
        if(password[max-1] == letter[0])
        {
            letterCount++;
        }
        if(letterCount == 1)
        {
            return 1;
        }else{return -1;}
    }

int check_valid_password(int letterCount,int min, int max)
{
    if(min <= letterCount && letterCount <= max)
    {
        return 1;
    }
    return -1;
}

int letter_Counter(char *password, char * letter)
{
    int letterCount=0; //nr of letters in password
    for(int index=0; index < strlen(password); index++ )
    {
        if(password[index] == letter[0] )
        {
            letterCount++;
        }
    }
    return letterCount;
}

    int main(void)
    {
    char str[50];
    const char LINE[] = "-";
    const char SPACE[] = " ";
    const char COLON[] = ":";



    int validCount = 0;
    int validCount2 =0;
    char * token;
    int min = 0;
    int max = 0;
    char* letter; // has to be a pointer for some reason to work with strtok
    char* password;
    char path[1000] = "C:\\Users\\Jonas\\Cprojects\\advent-of-code-2020\\test\\2020-02-1\\2020-02-1-data.txt";
    FILE *fp = fopen(path, "r");

    //check if we sucesfully opened the file
    if(fp == NULL)
    {

        printf("Failed to open file\n");
    }


    //loop through all lines, split up into pieces, count letters, check if valid
    while(fgets(str,50,fp))
    {
        token = strtok(str,LINE);
        min = atoi(token); //
        token = strtok(NULL, SPACE);
        max = atoi(token);
        token = strtok(NULL, COLON);
        letter = token;
        token = strtok(NULL, COLON);
        password = &token[1]; // remove the first char of the token. i.e. the space " ". Have to put &token for it to work //password doesn't actually contain the password string just a pointer to the password.


        if(check_valid_password(letter_Counter(password, letter),min,max)==1)
        {
            validCount++;
        }

        if(check_valid_password_part2(password,letter,min,max)==1)
        {
            validCount2++;
        }
    }
    printf("%d passwords are valid\n",validCount);


    printf("%d passwords with the second policy are valid\n",validCount2);

    //test code
    //char test[] = "2-4 p: vpkpp";

    //This part of the code splits each line up into chunks useful to figure out if the password is valid or not.
    //I think token points first to the seperated part then to the rest of the string and the strtok(NULL, " ") just continues
    // and looks for the next delimiter  to break the rest of the string up.
//    token = strtok(test,LINE);
//    min = atoi(token); //
//    token = strtok(NULL, SPACE);
//    max = atoi(token);
//    token = strtok(NULL, COLON);
//    letter = token;
//    token = strtok(NULL, COLON);
//    password = &token[1]; // remove the first char of the token. i.e. the space " ". Have to put &token for it to work //password doesn't actually contain the password string just a pointer to the password.



//    printf("min:%d\n",min);
//    printf("max:%d\n",max);
//    printf("letter:%s\n",letter);
//    printf("password:%s\n",password);









//reference code how strtok works
//   char strt[80] = "This is - www.tutorialspoint.com - website";
//   const char s[2] = "-";
//   char *tokens;
//
//   /* get the first token */
//   tokens = strtok(strt, s);
//
//   /* walk through other tokens */
//   while( tokens != NULL ) {
//      printf( " %s\n", tokens );
//
//      tokens = strtok(NULL, s);
//   }






    }
