/*************************************************************************/
/* File Name : program1.c 											     */
/* Purpose   : this C-file tests the functions of the "my_string" library*/
/*                                                                       */
/*                                                                       */
/* Author(s) : Ali 											     */
/*************************************************************************/

#include <stdio.h>
#include <string.h>
#include "my_string.h"
#define MAX_VALUE 250


int main (int argc, char** argv) {
    
   int integerCounter = 0; 
   int charCounter = 0; 
   int isNumber;
    
   char StringArrayList[argc][MAX_VALUE];
   
   char StringArrayMain[MAX_VALUE] = "";
   char* StringArrayMainPointer = StringArrayMain;  
    
   int IntegerArrayList[argc];
   int* intgerPointer = IntegerArrayList;
    
    for (int i = 0; i < argc; i++ ) {
        
        if(sscanf(argv[i], "%d", &isNumber) != 1) {
            //NOT A NUMBER
            
            
            StringArrayMainPointer += sprintf(StringArrayMainPointer, "%s ", argv[i]); 
            ++charCounter;
        } else {
            //This is an integer
            *intgerPointer = isNumber;
            ++integerCounter;
            ++intgerPointer;

        }
    }
    
    
   
    printf("****INTEGER ARRAY**\n");
    
    //Print a for loop for all numbers in array:
    
    for(int s = 0; s < integerCounter; s++) {
        printf("Integer Array is %d at index %d \n", IntegerArrayList[s], s);
    }
    
    printf("****STRING ARRAY**\n");
    //Printing the string array with space in between
    
    printf("%s \n", StringArrayMain);
   
    
    
   
    
    return(0);
    
    
}