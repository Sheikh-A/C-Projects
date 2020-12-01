/*************************************************************************/
/* File Name : my_string.c 											     */
/* Purpose   : this C-file defines the functions previously declared	 */
/*             in the my_string.h header file 						     */
/*																		 */
/* Author(s) : tjf & you 											     */
/*************************************************************************/

#include "my_string.h"

// strlen functions takes in a pointer to a string and return its length
//

//ARRAY IMPLEMENTATION
size_t2 my_strlen  (const char *str) {

	size_t2 len = 0 ;
	while (str[len] != '\0') {  // count up to the first NULL
		len++ ; 
	}
	return (len) ;

}

//POINTER IMPLEMENTATION
size_t2 my_strlen2 (const char *str) {

	const char* s;
	for (s = str; *s; ++s) ;
	return (s - str);

}


/* CIT 593 students: TODO: implement the remaining string functions
   that were declared in my_string.h */

//MY_STRCPY 
/*
The C library function char *strcpy(char *dest, const char *src) copies the string pointed to, by src to dest.
Declaration
Following is the declaration for strcpy() function.

char *strcpy(char *dest, const char *src)
Parameters
dest − This is the pointer to the destination array where the content is to be copied.
src − This is the string to be copied.
Return Value
This returns a pointer to the destination string dest.

functions to copy a string

char* my_strcpy  (char *dest, const char *src) ;
char* my_strcpy2 (char *dest, const char *src) ;

*/

char* my_strcpy  (char *dest, const char *src) {
    int string_length; //Initialize variable for str lenght
    
    string_length = my_strlen(src);
    
    for (int i = 0; i < string_length; ++i) {
        dest[i] = src[i]; //COPY Contents to new string
    }
     dest[string_length] = '\0'; //Set Null condition
    
    return dest; //return string
}

//POINTER FUNCTION


char* my_strcpy2 (char *dest, const char *src) {
    
    char* string_copy = dest;
    const char* s;//initialize variable
   
    //Using Pointer Arithmetic for Array: *s == as long as char exists, keep looping
    for(s = src; *s; ++s) {
        *dest = *s;
        ++dest;
    }
    
    *dest = '\0';
    
    return string_copy;
    
}

/* functions to search a string

char* my_strchr  (const char *str, int c) ;
char* my_strchr2 (const char *str, int c) ;
Description
The C library function char *strchr(const char *str, int c) searches for the first occurrence of the character c (an unsigned char) in the string pointed to by the argument str.

Declaration
Following is the declaration for strchr() function.

char *strchr(const char *str, int c)
Parameters
str − This is the C string to be scanned.

c − This is the character to be searched in str.

Return Value
This returns a pointer to the first occurrence of the character c in the string str, or NULL if the character is not found.

*/


char* my_strchr (const char *str, int c) { 
    
    //Define the null value
    int null_value = '\0';
    
    //Using While Loop
    while (*str != null_value) {
    
       //Check if c is in string
        if (c == *str) {
            return str;
        } 
        
        //ELSE
          str++;
        
	}
	return (char*) '\0';
    

}


//POINTER ARITHMETIC

char* my_strchr2 (const char *str, int c) {
    
    const char *stringpointer; //initialize
    char *finalString; //initialize
    int string_length = my_strlen(str);
    
    
    for(int i =0; i < string_length; i++, str++) {
        
        if(c == *str) {
            stringpointer = str;
            break;
        }
    }
    
    //Now use the pointer and a while loop
    
    //Check if the next letters are equal
    while(*stringpointer == *finalString) {
        
        return finalString;
    }
    
}


/* functions to concatenate string
 char* my_strcat  (char *dest, const char *src) ;
char* my_strcat2 (char *dest, const char *src) ;
Description
The C library function char *strcat(char *dest, const char *src) appends the string pointed to by src to the end of the string pointed to by dest.

Declaration
Following is the declaration for strcat() function.

char *strcat(char *dest, const char *src)
Parameters
dest − This is pointer to the destination array, which should contain a C string, and should be large enough to contain the concatenated resulting string.

src − This is the string to be appended. This should not overlap the destination.

Return Value
This function returns a pointer to the resulting string dest.
  
 */

char* my_strcat  (char *dest, const char *src) {
     
   int destination_length = my_strlen(dest);
   int src_length = my_strlen(src);
    
   for (int i = 0; i < src_length; i++) {
       
                   //H E L L O A L I
       //index based 0 1 2 3 4 5 6 7 
       
       dest[destination_length + i] += src[i];
   } 
    
   return dest;
      
}

//POINTER ARITHMETIC     
    
char* my_strcat2 (char *dest, const char *src) {
    
    char null_value = '\0';
    
    int destlength = my_strlen(dest);
    
    char *concatString = dest + destlength;
    
    const char* s;
    
    for(s = src; *s; ++s, ++concatString) { //Keep looping until null
        *concatString = *s;
    }
    
    concatString = null_value;
    
    return dest;
    

}

/* functions to compare two strings
Description
The C library function int strcmp(const char *str1, const char *str2) compares the string pointed to, by str1 to the string pointed to by str2.

Declaration
Following is the declaration for strcmp() function.

int strcmp(const char *str1, const char *str2)
Parameters
str1 − This is the first string to be compared.

str2 − This is the second string to be compared.

Return Value
This function return values that are as follows −

if Return value < 0 then it indicates str1 is less than str2.

if Return value > 0 then it indicates str2 is less than str1.

if Return value = 0 then it indicates str1 is equal to str2.



 *  */

int my_strcmp  (const char *str1, const char *str2) {
    
    int value = -1000; //indicates an ERROR
    int sumStr1 = 0;
    int sumStr2 = 0;
    
    
    for(int i =0; i < my_strlen(str1); i++) {
        sumStr1 += str1[i];
   
    }
    
    for(int i =0; i < my_strlen(str2); i++) {
        sumStr2 += str2[i];
   
    }
    
    if(sumStr1 > sumStr2) {
        return value = 1;
    } else if (sumStr1 < sumStr2) {
        return value = -1;
    } else if (sumStr1 == sumStr2) {
        return value = 0;
    } else {
        return value;
    }
    
    
}



//POINTER FUNCTION

int my_strcmp2 (const char *str1, const char *str2) {
    
    int value = -1000; //CHECK IF ERROR
    int sumStr1 = 0;
    int sumStr2 = 0;
    char *stringOnePointer;
    char *stringTwoPointer;
   
    //USING POITNERS
    for(stringTwoPointer = str2; *stringTwoPointer; ++stringTwoPointer) {
        sumStr2 += *stringTwoPointer;
   
    }
    
    for(stringOnePointer = str1; *stringOnePointer; ++stringOnePointer) {
        sumStr1 += *stringOnePointer;
   
    }
    
    if(sumStr1 > sumStr2) {
        return value = 1;
    } else if (sumStr1 < sumStr2) {
        return value = -1;
    } else if (sumStr1 == sumStr2) {
        return value = 0;
    } else {
        return value;
    }
      
  
}

//Reverse a String Function

char* my_strrev(char *my_str) {
    
    int i = 0;
    char temp;
    
    char* reversedString = my_str;
    int stringLength = my_strlen(my_str);
    
    int s = stringLength - 1;
    
    //Use  a temporary char to store the current variable before switching
    while(i < s) {
        temp = *my_str;
        *my_str = my_str[s];
        
        *(my_str + s) = temp;
        s--;
        i++;
        my_str++;
        
    }
    
    return reversedString;
    
}


//STR Case Function
char * my_strccase(char* str) {
    
    int stringLength = 0;
    
    stringLength = my_strlen(str);
    
    for(int i = 0; i < stringLength; i++) {
        
        int ascii_value = str[i];
        if((ascii_value >= 97) && (ascii_value <= 122)) {
            
            str[i] -= 32;
            
        } else if ((ascii_value >= 65) && (ascii_value <= 90)) {
            
            str[i] += 32;
            
        }
        
    }
                   
     return str;
    
    
}



