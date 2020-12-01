#include <stdio.h>

int main() {
	int a = 10;
	unsigned long int b = 2;
	float f = 11;
	int* a_ptr = &a, **a_ptr_ptr = &a_ptr;
	char* c_code = "This is some C code!";
	char c_code2[50] = "This is some other C code v2";
	
	printf("1 This is inital C code! \n");
	printf("2 %s \n", c_code);
	printf("3 %s \n", c_code2);
	printf("4 %p \n", c_code);
	printf("5 x%X \n", c_code);
	
	a++;
	printf("5 a = %d \n", a);
	printf("6 Address of a is x%X \n", a_ptr);
	printf("7 Addres of a_ptr is x%X \n", a_ptr_ptr);
	
	a = a /b ;
	printf(" a / b = %d\n", a);
	
	f = f/ 2;
	printf("float f / b = %f\n", f);
	
	b = b-3;
	printf("b = %lu\n", b);
		
	
		
}