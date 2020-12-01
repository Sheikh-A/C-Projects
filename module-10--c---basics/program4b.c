/********************************************************
 * file name   : program1.c                             *
 * author      : Thomas Farmer                          *
 * description : Hello World Program                    *
 *                                                      *
 ********************************************************
*
*/

#include <stdio.h>

void swap (int* a, int* b) { //we want to use POINTERS
    
    int c = 0 ;
    
    
    c = *a  ; /*C is equal to the pointer of a */

    *a = *b ; //a pointer = b pointer
    
    *b = c ; //swap the values with c
    
    printf("a = %d\n", *a);
    printf("b = %d\n", *b);
    
    //Here is where the swap occurs
    
    return;
   
}

int main () {
    
    int a = 5 ;
    int b = 10 ;
    
    printf("a= %d\n", a) ;
    printf("b= %d\n", b) ;
    
    swap(&a, &b); //swap the address of a and the address of b
    
    printf("a= %d\n", a) ;
    printf("b= %d\n", b) ;
    
        
	return (0) ;
}
