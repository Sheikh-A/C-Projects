/*************************************************************************/
/* File Name : program1.c 											     */
/* Purpose   : this C-file tests the functions of the "my_string" library*/
/*                                                                       */
/*                                                                       */
/* Author(s) : tjf & you 											     */
/*************************************************************************/

#include <stdio.h>
#include <string.h>
#include "my_string.h"
#define MAX_LENGTH 200


int main() {

	// a string we will test with
	char my_string [100] = "Tom" ;

	// test of strlen() functions 
	printf ("Sample string: \"%s\" \n", my_string) ;
	printf (" string's length: strlen()     = %lu \n",   strlen  (my_string)) ;
	printf (" string's length: my_strlen()  = %lu \n", my_strlen (my_string)) ;
	printf (" string's length: my_strlen2() = %lu \n", my_strlen2(my_string)) ;

    /* CIT 593 students: TODO: add code to test your my_string.h functions */
    
    
    // Testing Copy String Function Method 1
    printf("**************************STRING COPY ARRAY METHOD \n");
    char test_string [MAX_LENGTH] = "Test Copy" ;
	char copied_string [MAX_LENGTH];

    printf("Library Function = %s\n", strcpy(copied_string, test_string));
	printf("Ali Function = %s\n", my_strcpy(copied_string, test_string));
    
    char new_string [MAX_LENGTH];
    printf("Library Function = %s \n ", strcpy(new_string, "testing123"));
    printf("Ali Function = %s \n ", my_strcpy(new_string, "testing123"));
    
    
    // Testing Copy String Function Method 2
    printf("**************************STRING COPY POINTER METHOD \n");
	char testM2_string [MAX_LENGTH] = "Test Copy" ;
	char copiedM2_string [MAX_LENGTH];

    printf("Library Function = %s\n", strcpy(copiedM2_string, testM2_string));
	printf("Ali Function = %s\n", my_strcpy2(copiedM2_string, testM2_string));
    
    char new_string_M2 [MAX_LENGTH];
    printf("Library Function = %s \n ", strcpy(new_string_M2, "testing123"));
    printf("Ali Function = %s \n ", my_strcpy2(new_string_M2, "testing123"));
    
    // Testing strchr() String Function Method 1
    printf("**************************STRING String Function Method 1 \n");
	int char1 = 'a';
    int char2 = 'b';
    
    char* strchrStringTest = "123111ali sheikh";
    
    char* libraryOnechr = strchr(strchrStringTest, char1);
    char* libraryTwochr = strchr(strchrStringTest, char2);
    
    printf("Char: %c String: %s  LibraryOne:%s \n", char1, strchrStringTest, libraryOnechr);
    printf("DOES NOT EXIST Char: %c String: %s  LibraryOne:%s \n", char2, strchrStringTest, libraryTwochr);
    

    char* MylibraryOnechr = my_strchr(strchrStringTest, char1);
    char* MylibraryTwochr = my_strchr(strchrStringTest, char2);
    
    printf("Char: %c String: %s  LibraryOne:%s \n", char1, strchrStringTest, MylibraryOnechr);
    printf("DOES NOT EXIST Char: %c String: %s  LibraryOne:%s \n", char2, strchrStringTest, MylibraryTwochr);

    
        
    // Testing strchr() String Function Method 2
    printf("**************************STRING String Function Method 2 \n");
	int char3 = 'a';
    int char4 = 'b';
    
    char* strchrStringTest2 = "123111ali sheikh";
    
    char* MlibraryOnechr = strchr(strchrStringTest2, char3);
    char* MlibraryTwochr = strchr(strchrStringTest2, char4);
    
    printf("Char: %c String: %s  LibraryOne:%s \n", char1, strchrStringTest2, libraryOnechr);
    printf("DOES NOT EXIST Char: %c String: %s  LibraryOne:%s \n", char2, strchrStringTest2, libraryTwochr);
    

    char* MylibraryOnechr2 = my_strchr(strchrStringTest2, char3);
    char* MylibraryTwochr2 = my_strchr(strchrStringTest2, char4);
    
    printf("Char: %c String: %s  LibraryOne:%s \n", char3, strchrStringTest2, MylibraryOnechr2);
    printf("DOES NOT EXIST Char: %c String: %s  LibraryOne:%s \n", char4, strchrStringTest2, MylibraryTwochr2);
    
    // Testing strchr() CONCAT
    printf("**************************STRING String CONCAT1 \n");
	
    
    char dest[MAX_LENGTH] = "Hello";
    char src[MAX_LENGTH] = "Ali Sheikh";
    
    
    printf("CONCAT 1 %s \n", strcat(dest, src));
    
    char dest1[MAX_LENGTH] = "Hello";
    char src1[MAX_LENGTH] = "Ali Sheikh";
    
    printf("CONCAT 1 %s \n", my_strcat(dest1, src1));
    
    printf("**************************STRING String CONCAT2 \n");
    
    char dest2[MAX_LENGTH] = "Hello";
    char src2[MAX_LENGTH] = "Ali Sheikh";
    
    printf("CONCAT 2 %s \n", my_strcat2(dest2, src2));
    
    printf("**************************STRING COMPARE M1 \n");
    
    char* strC1 = "abcdef" ;
    char* strC2 = "ABCDEF" ;
    
    printf(" Should be > 0 %d \n", strcmp(strC1, strC2));
    printf(" Should be > 0 %d \n", my_strcmp(strC1, strC2));
    
    printf(" Should be < 0 %d \n", strcmp(strC2, strC1));
    printf(" Should be < 0 %d \n", my_strcmp(strC2, strC1));
    
    char* strC3 = "abc" ;
    char* strC4 = "abc" ;
    
    printf(" Should be = 0 %d \n", strcmp(strC3, strC4));
    printf(" Should be = 0 %d \n", my_strcmp(strC3, strC4));
    
    printf("**************************STRING COMPARE M2 \n");
        
    printf(" Should be > 0 %d \n", strcmp(strC1, strC2));
    printf(" Should be > 0 %d \n", my_strcmp2(strC1, strC2));
    
    printf(" Should be < 0 %d \n", strcmp(strC2, strC1));
    printf(" Should be < 0 %d \n", my_strcmp2(strC2, strC1));
    
    printf(" Should be = 0 %d \n", strcmp(strC3, strC4));
    printf(" Should be = 0 %d \n", my_strcmp2(strC3, strC4));

    
	

	return (0) ;

}
