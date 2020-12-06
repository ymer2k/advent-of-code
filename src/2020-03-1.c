    #include <stdio.h>
    #include <stdlib.h>


int tree_encounter_checker(char array[400][50],int counter,const char str[], int xmovment, int ymovment)
{
 int treeEncounter=0;
    int x=0;
    int y=0;
    for(int index=0; index < counter;index++)
    {
        if(array[y][x] == '#')
        {
            treeEncounter++;
        }
        y=y+ymovment;
        x=x+xmovment;

        if(x > strlen(str)-1)
        {
            x=x-strlen(str); //reset to the left side of the slope again.
        }


    }


    printf("We encountered a tree %d times with a right:%d, down:%d\n",treeEncounter,xmovment,ymovment);
    return treeEncounter;
}

int main(void)
{
    char TREE = '#';
    char array[400][50];

    ////////////////
    char path[1000] = "C:\\Users\\Jonas\\Cprojects\\advent-of-code-2020\\test\\2020-03-1\\2020-03-1-data.txt";
    FILE *fp = fopen(path, "r");

    //check if we successfully opened the file
    if(fp == NULL)
    {

        printf("Failed to open file\n");
    }

    //save the data in an array
    char str[50];
    int counter=0;
    while(fgets(str,50,fp) != NULL)
    {
        strcpy(array[counter],str);
        counter++;
    }

////go down the slope one step down 3 steps right.
//    int treeEncounter=0;
//    int x=0;
//    int y=0;
//    for(int index=0; index < counter;index++)
//    {
//        if(array[y][x] == TREE)
//        {
//            treeEncounter++;
//        }
//        y++;
//        x=x+3;
//
//        if(x > strlen(str)-1)
//        {
//            x=x-strlen(str); //reset to the left side of the slope again.
//        }
//
//
//    }
//    printf("We encountered a tree %d times\n",treeEncounter);


    int encounter1 = tree_encounter_checker(array,counter,str,1,1);
    int encounter2 = tree_encounter_checker(array,counter,str,3,1);
    int encounter3 = tree_encounter_checker(array,counter,str,5,1);
    int encounter4 = tree_encounter_checker(array,counter,str,7,1);
    int encounter5 = tree_encounter_checker(array,counter,str,1,2); //works sometimes. Sometimes this line causes a segmentation fault
    int product = encounter1*encounter2*encounter3*encounter4*encounter5;

    printf("product of encounters:%d\n",product);



}
