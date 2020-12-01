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
#define MAX_LENGTH 200




int main() {
    
    //TESTING my_strrev() & my_strccase()
    
    char test_string[MAX_LENGTH] = "Tom";
    printf("Reversed String: %s \n", my_strrev(test_string));
    
    
    char test_string2[MAX_LENGTH] = "Tom";
    
    printf("Converted Letter String: %s \n", my_strccase(test_string2));
    
    //TESTING my_strrev() & my_strccase()
    
    char test_string3[MAX_LENGTH] = "Ali";
    printf("Reversed String: %s \n", my_strrev(test_string3));
    
    
    char test_string4[MAX_LENGTH] = "Ali2";
    
    printf("Converted Letter String: %s \n", my_strccase(test_string4));
    
  
    return (0);
    
    
}