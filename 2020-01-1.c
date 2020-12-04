    #include <stdio.h>
    #include <stdlib.h>
    #include <errno.h>


int findProduct2(char array[200][6])
{

    for(int index =0; index < 200; index++)
    {
        for(int index2 =0; index2 <200; index2 ++)
        {
            if((atoi(array[index]) + atoi(array[index2])) == 2020)
            {
                return ( atoi(array[index]) * atoi(array[index2]) );
            }

        }

    }

}

int findProduct3(char array[200][6])
{

    for(int index =0; index < 200; index++)
    {
        for(int index2 =0; index2 <200; index2 ++)
        {
            for(int index3 =0; index3 <200; index3 ++)
            {
                if((atoi(array[index]) + atoi(array[index2]) + atoi(array[index3]) ) == 2020)
                {
                    return ( atoi(array[index]) * atoi(array[index2]) * atoi(array[index3]) );

                }

            }

        }

    }
}


    int findProduct2Fail(FILE *fp){ //doesn't work. first fgets will take the first nr, second will go 2nd nr to last nr
        // and then exit both while loops
        char str[6];
        char str2[6];

        while(fgets(str,6,fp) != NULL){
            while(fgets(str2,6,fp) != NULL){
                if( (atoi(str) + atoi(str2)) == 2020 ){
                    return (atoi(str) * atoi(str2));
                }

            }

        }

    return 0;
    }


    int main(){
    char str[6]; //maximum 4 numbers + the NULL character "\0"
    int counter =0;
    int temp;
    char path[1000] = "C:\\Users\\Jonas\\Cprojects\\advent-of-code-2020\\test\\2020-01-1\\2020-01-1-data.txt"; // Added some space for array[0]
    //char path[1000] = "C:/Users/Jonas/Cprojects/advent-of-code-2020/test/2020-01-1/2020-01-1-data.txt/"; // Added some space for array[0]

    char c;
    //FILE *fp = fopen(path, "r");

    FILE *fp = fopen(path, "r");

    //check if we sucesfully opened the file
    if(fp == NULL){

        printf("Failed to open file\n");
    }

//Test code
//    fgets(str,6,fp);
//    printf("number: %s",str);
//    printf("New line\n");
//    fgets(str,6,fp);
//    printf("number: %s",str);
//    printf("New line\n");
//    fgets(str,6,fp);
//    printf("number: %s",str);


        //code to save the stream into an array.
        char array[200][6];
        while(fgets(str,6,fp) != NULL){
            //printf("%s",str);
            //puts(str);
            strcpy(array[counter],str); //apparently we have to do this to massaign a new string to array
            counter++;
        }
        printf("\n");
      printf(" THis is the number Im after: %s\n",array[199]);

/*

      //The double for loops to find a +b = 2020
      int a=0;
      int b=0;
      for(int index =0; index < 200; index++){
        a = atoi(array[index]); //the atoi function changes a string into an int.
        for(int index2 =0; index2 <200; index2 ++){
               // printf("current b: %d", atoi(array[index2]));
            if((a + atoi(array[index2])) == 2020){
                b = atoi(array[index2]);
                printf("These are the numbers, a=%d b=%d",a,b);
                break;
            }

        }

      }

*/

int result2 = findProduct2(array);
printf("The product for two numbers is: %d\n",result2);
int result3 = findProduct3(array);
printf("The product for three numbers is: %d\n",result3);

fclose(fp);

    //prints the content of fp
//   c = fgetc(fp); //fgetc getst the next char
//   while ( c != EOF){
//        printf("%c",c);
//        c = fgetc(fp);
//
//   }
//    fclose(fp);



    printf("neger");

    }
