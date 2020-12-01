
#include <stdio.h>

// int foobar(void* ptr) {
//     char* curr = (char*) ptr;
    
//     printf("my string is %s\n", curr);
// }



int foobar (char* str) {
    printf("my string is %s\n", str);
}


int global_var =5;

int main() {
    
    int myint = 5;
    int* ptr = &myint;
    
    char my_array[] = {'H','e','l','l','o',' ','C','l','a','s','s','\0'}; //is already an Address
    char* my_array_ptr = my_array; //my_array contains the Address of H
    
    
    printf("my_array is %s\n", my_array);
    //Hello Class
     
    //printf("my_array's location in memory is &p\n", &my_array);
    //0x7fff8ed2c680
    
    char* literal_ptr = "Goodbye";
    
    //printf("literal_ptr point to the string %s\n", literal_ptr);
    // (s = string) Goodbye
    
    
    //printf("string's location in memory is %p\n", literal_ptr);
    // p = pointer
    // 0x40078d
        
    //printf("literal_ptrs location in memory is %p\n", &literal_ptr);
    //pointer is at 0x7ffef2d76e38
    
    //printf("%c\n", literal_ptr[3])
    // %c is character
    // d
    
    //literal_ptr = literal_ptr + 3
    //printf("%s\n", literal_ptr);
    // 0 1 2 3 4 5 6
    // G o o d b y e - > 
    // dbye
    
    //foobar(literal_ptr)
    // my string is Goodbye
    //
    //foobar(my_array)
    //my string is Hello Class (array)
    
    return 0;
    
}