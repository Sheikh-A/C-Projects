/***************************************************************************
 * file name   : asm_parser.c                                              *
 * author      : tjf & you                                                 *
 * description : the functions are declared in asm_parser.h                *
 *               The intention of this library is to parse a .ASM file     *
 *			        										               * 
 *                                                                         *
 ***************************************************************************
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "asm_parser.h"

/* to do - implement all the functions in asm_parser.h */

/*int read_asm_file (char* filename, char program [ROWS][COLS] ) ;
 * The purpose of read_asm_file() is to open the ASM file, and place its contents into the 2D array:
program[][]. You must complete the implementation of this function in the provided helper
file: “asm_parser.c”. Notice, it takes in the pointer to the “filename” that you’ll open in this
function. It also takes in the two dimensional array, program, that was defined back in main().
You’ll see that “ROWS” and “COLS” are two #define’ed constants in the file: asm_parser.h.
Rows is set to 100 and COLS is set to 255. This means that you can only read in a program that
is up to 100 lines long and each line of this program can be no longer than 255. 
*/




int read_asm_file(char* filename, char program [ROWS][COLS]) {
    
    //open file using FILE Command
    FILE* myFile = fopen(filename, "r");
    
    /*
     * r = read
     * w = write
     * a = append
     * w++ = write / create
     * r++ read/ write
     */
    
    int number = 0;
    char numOfLines[COLS];
	
    char enterChar = '\n';
	
    //CHECK FOR NULL
	if (myFile == NULL) {
		return 2;
	}
    
    //Use fgets function 
    //char *fgets(char *str, int n, FILE *stream)
    
	while (fgets(numOfLines, COLS, myFile) != NULL) {
		
        if (numOfLines[0] == enterChar) {
			++number;
            
			continue;
		}
        
//        void *memcpy(void *dest, const void * src, size_t n)
//  The C library function void *memcpy(void *dest, const void *src, size_t n) 
//      copies n characters from memory area src to memory area dest.
		memcpy(program[number], numOfLines, strlen(numOfLines)); 
		++number;
	}
    
    //TESTING FUNCTION
    for(int f=0; f < 8; f++) {
        for(int i = 0; i < 255; i++) {
            printf("%c", program[f][i]);
        }
        printf("\n");
    }
    
    //Close filename
    
    fclose(myFile);
    
    return(0);  
}



//The purpose of this function is to take in a single row of your program[][] array and convert to
//its binary equivalent – in text form

//STRTOK function  char *strtok(char *str, const char *delim)
int parse_instruction 	(char* instr, char* instr_bin_str) {
    
    const char s[2] = ", ";

    
	char *delimiter = NULL;
    
    
    if (instr == NULL || instr == '\0') {
		fprintf(stderr, "error3: parse_instruction() failed.\n") ;
		return 3 ;
	}

	//FIRST INSTANCE OF ,
	delimiter = strtok(instr, s);
	// decide its opcode
	if (strcmp(delimiter, "ADD") == 0) {
	    
        
	    parse_add(instr, instr_bin_str);

	} 
    
    else if (strcmp(delimiter, "MUL") == 0) {

		parse_mul(instr, instr_bin_str);
	
	} 
    
    else if (strcmp(delimiter, "SUB") == 0) {

		parse_sub(instr, instr_bin_str);
	
	} 
    
    else if (strcmp(delimiter, "DIV") == 0) {

		parse_div(instr, instr_bin_str);

	}
    
    
    
    else if (strcmp(delimiter, "AND") == 0) {

		parse_and(instr, instr_bin_str);
	
	}  
    
    else if (strcmp(delimiter, "NOT") == 0) {

		parse_or(instr, instr_bin_str);

	} 
    
    else if (strcmp(delimiter, "XOR") == 0) {

		parse_xor(instr, instr_bin_str);
	}
    
    else if (strcmp(delimiter, "OR") == 0) {

		parse_or(instr, instr_bin_str);

	} 
    
    
    else {
        printf("error3: parse_instruction() failed.");
        return 3;
    }

   
   	return 0;
}


//Register
int parse_reg(char reg_num, char* instr_bin_str) {
 
    //ERROR CHECK
    if(reg_num=='\0'){
		perror("error5: parse_reg() failed.");
		return 5;
	}
    
	int registerNum = strlen(instr_bin_str);   
	switch (reg_num) {
            
		case '0':
			instr_bin_str[registerNum+2] = '0';
            instr_bin_str[registerNum+1] = '0';
            instr_bin_str[registerNum]   = '0';

			break;
            
		case '1':
			instr_bin_str[registerNum+2] = '1';
			instr_bin_str[registerNum+1] = '0';
            instr_bin_str[registerNum]   = '0';
			
			break;
		
        case '2':
			instr_bin_str[registerNum+2] = '0';
            instr_bin_str[registerNum+1] = '1';
            instr_bin_str[registerNum]   = '0';
			
			
			break;
		
        case '3':
			instr_bin_str[registerNum+2] = '1';
            instr_bin_str[registerNum+1] = '1';
            instr_bin_str[registerNum]   = '0';
			
			
			break;
		
        case '4':
			instr_bin_str[registerNum+2] = '0';
            instr_bin_str[registerNum+1] = '0';
            instr_bin_str[registerNum]   = '1';
		
			break;
		
        case '5':
			
            instr_bin_str[registerNum+2] = '1';
			instr_bin_str[registerNum+1] = '0';
            instr_bin_str[registerNum]   = '1';
			break;
		
        case '6':
			instr_bin_str[registerNum+2] = '0';
            instr_bin_str[registerNum+1] = '1';
            instr_bin_str[registerNum]   = '1';
			break;
		
        case '7':
			instr_bin_str[registerNum+2] = '1';
            instr_bin_str[registerNum+1] = '1';
            instr_bin_str[registerNum]   = '1';
			
            break;
		
	}
	
    return 0;
    
}

//ARITHMETIC SECTION


int parse_add(char* instr, char* instr_bin_str) {
    
    
    char *delimiter = NULL;
    
    instr_bin_str[0] = '0';
    instr_bin_str[1] = '0';
    instr_bin_str[2] = '0';
    instr_bin_str[3] = '1';
    
    if(instr == NULL) {
        printf("error4: parse_add() failed");
    }
    
   
    
    
    //First[0] =  ','
    delimiter = strtok(NULL, ", ");
    
    parse_reg(delimiter[1], instr_bin_str);
    
    //Get 2nd Register
    delimiter = strtok(NULL, ", ");
    
    parse_reg(delimiter[1], instr_bin_str);
    

    //ADD OpCode = 000
    instr_bin_str[10] = '0';
    instr_bin_str[11] = '0';
    instr_bin_str[12] = '0';
    
    delimiter = strtok(NULL, ", ");
    parse_reg(delimiter[1], instr_bin_str);
    
    
    return 0;
    
}

int parse_mul(char* instr, char* instr_bin_str) {
    
    char *delimiter = NULL;
    instr_bin_str[0] = '0';
    instr_bin_str[1] = '0';
    instr_bin_str[2] = '0';
    instr_bin_str[3] = '1';
    
    if(instr == NULL) {
        printf("error4: parse_add() failed");
        return 4;
    }
    
    

    
    
    //First REgister [0] =  ','
    delimiter = strtok(NULL, ", ");
    
    parse_reg(delimiter[1], instr_bin_str);
    
    //Get 2nd Register
    delimiter = strtok(NULL, ", ");
    
    parse_reg(delimiter[1], instr_bin_str);
    
    //Here is the OpCode section
    //MUL OpCode = 001
    instr_bin_str[10] = '0';
    instr_bin_str[11] = '0';
    instr_bin_str[12] = '1';
    
    delimiter = strtok(NULL, ", ");
    parse_reg(delimiter[1], instr_bin_str);
    
    
    return 0;
    
}

int parse_sub(char* instr, char* instr_bin_str) {
    
    char *delimiter = NULL;
    instr_bin_str[0] = '0';
    instr_bin_str[1] = '0';
    instr_bin_str[2] = '0';
    instr_bin_str[3] = '1';
    
    if(instr == NULL) {
        printf("error4: parse_add() failed");
        return 4;
    }
    
    

    
    
    //First REgister [0] =  ','
    delimiter = strtok(NULL, ", ");
    
    parse_reg(delimiter[1], instr_bin_str);
    
    //Get 2nd Register
    delimiter = strtok(NULL, ", ");
    
    parse_reg(delimiter[1], instr_bin_str);
    
    //Here is the OpCode section
    //SUB OpCode = 010
    instr_bin_str[10] = '0';
    instr_bin_str[11] = '1';
    instr_bin_str[12] = '0';
    
    delimiter = strtok(NULL, ", ");
    parse_reg(delimiter[1], instr_bin_str);
    
    
    return 0;
    
}

int parse_div(char* instr, char* instr_bin_str) {
    
    char *delimiter = NULL;
    instr_bin_str[0] = '0';
    instr_bin_str[1] = '0';
    instr_bin_str[2] = '0';
    instr_bin_str[3] = '1';
    
    if(instr == NULL) {
        printf("error4: parse_add() failed");
        return 4;
    }
    
    
//     if(instr == '/0') {
//         printf("error4: parse_add() failed");
//         return 4;
//     }
    
    
    //First REgister [0] =  ','
    delimiter = strtok(NULL, ", ");
    
    parse_reg(delimiter[1], instr_bin_str);
    
    //Get 2nd Register
    delimiter = strtok(NULL, ", ");
    
    parse_reg(delimiter[1], instr_bin_str);
    
    //Here is the OpCode section
    //DIV OpCode = 011
    instr_bin_str[10] = '0';
    instr_bin_str[11] = '1';
    instr_bin_str[12] = '1';
    
    delimiter = strtok(NULL, ", ");
    parse_reg(delimiter[1], instr_bin_str);
    
    return 0;
    
}


//LOGICAL OPERATORS

/*
AND Rd Rs Rt Rd =   Rs & Rt 0101dddsss000ttt
NOT Rd Rs Rd =      Rs 0101dddsss001---
OR Rd Rs Rt Rd =    Rs | Rt 0101dddsss010ttt
XOR Rd Rs Rt Rd =   Rs ˆ Rt 0101dddsss011ttt
AND Rd Rs IMM5 Rd = Rs & SEXT(IMM5) 0101dddsss1IIIII
*/

int parse_and(char* instr, char* instr_bin_str) {
    
    char *delimiter = NULL;
    instr_bin_str[0] = '0';
    instr_bin_str[1] = '1';
    instr_bin_str[2] = '0';
    instr_bin_str[3] = '1';
    
    if(instr == NULL) {
        printf("error4: parse_add() failed");
        return 4;
    }
    
    
    //Causing Errors
    
//     if(instr == '/0') {
//         printf("error4: parse_add() failed");
//         return 4;
//     }
    
    
    //First REgister [0] =  ','
    delimiter = strtok(NULL, ", ");
    
    parse_reg(delimiter[1], instr_bin_str);
    
    //Get 2nd Register
    delimiter = strtok(NULL, ", ");
    
    parse_reg(delimiter[1], instr_bin_str);
    
    //Here is the OpCode section
    //AND OpCode = 011
    instr_bin_str[10] = '0';
    instr_bin_str[11] = '0';
    instr_bin_str[12] = '0';
    
    delimiter = strtok(NULL, ", ");
    parse_reg(delimiter[1], instr_bin_str);
    
    return 0;
    
}

int parse_not(char* instr, char* instr_bin_str) {
    
    char *delimiter = NULL;
    instr_bin_str[0] = '0';
    instr_bin_str[1] = '1';
    instr_bin_str[2] = '0';
    instr_bin_str[3] = '1';
    
    if(instr == NULL) {
        printf("error4: parse_add() failed");
        return 4;
    }
    
    
//     if(instr == '/0') {
//         printf("error4: parse_add() failed");
//         return 4;
//     }
    
    
    //First REgister [0] =  ','
    delimiter = strtok(NULL, ", ");
    
    parse_reg(delimiter[1], instr_bin_str);
    
    //Get 2nd Register
    delimiter = strtok(NULL, ", ");
    
    parse_reg(delimiter[1], instr_bin_str);
    
    //Here is the OpCode section
    //NOT OpCode = 001
    instr_bin_str[10] = '0';
    instr_bin_str[11] = '0';
    instr_bin_str[12] = '1';
    
    delimiter = strtok(NULL, ", ");
    parse_reg(delimiter[1], instr_bin_str);
    
    return 0;
    
}

int parse_or(char* instr, char* instr_bin_str) {
    
    char *delimiter = NULL;
    instr_bin_str[0] = '0';
    instr_bin_str[1] = '1';
    instr_bin_str[2] = '0';
    instr_bin_str[3] = '1';
    
    if(instr == NULL) {
        printf("error4: parse_add() failed");
        return 4;
    }
    
    
//     if(instr == '/0') {
//         printf("error4: parse_add() failed");
//         return 4;
//     }
    
    
    //First REgister [0] =  ','
    delimiter = strtok(NULL, ", ");
    
    parse_reg(delimiter[1], instr_bin_str);
    
    //Get 2nd Register
    delimiter = strtok(NULL, ", ");
    
    parse_reg(delimiter[1], instr_bin_str);
    
    //Here is the OpCode section
    //OR OpCode = 001
    instr_bin_str[10] = '0';
    instr_bin_str[11] = '1';
    instr_bin_str[12] = '0';
    
    delimiter = strtok(NULL, ", ");
    parse_reg(delimiter[1], instr_bin_str);
    
    return 0;
    
}

int parse_xor(char* instr, char* instr_bin_str) {
    
    char *delimiter = NULL;
    instr_bin_str[0] = '0';
    instr_bin_str[1] = '1';
    instr_bin_str[2] = '0';
    instr_bin_str[3] = '1';
    
    if(instr == NULL) {
        printf("error4: parse_add() failed");
        return 4;
    }
    
    
//     if(instr == '/0') {
//         printf("error4: parse_add() failed");
//         return 4;
//     }
    
    
    //First REgister [0] =  ','
    delimiter = strtok(NULL, ", ");
    
    parse_reg(delimiter[1], instr_bin_str);
    
    //Get 2nd Register
    delimiter = strtok(NULL, ", ");
    
    parse_reg(delimiter[1], instr_bin_str);
    
    //Here is the OpCode section
    //XOR OpCode = 011
    instr_bin_str[10] = '0';
    instr_bin_str[11] = '1';
    instr_bin_str[12] = '1';
    
    delimiter = strtok(NULL, ", ");
    parse_reg(delimiter[1], instr_bin_str);
    
    return 0;
    
}         




//unsigned short int str_to_bin (char* instr_bin_str) ;

/*
 * 
 * Should be called from main(), passing the recently parsed binary string from the array:
program_bin_str[X], where “X” represents the binary instruction that was just populated by the
last call to parse_instruction(). 
 * 
 */




unsigned short int str_to_bin(char* instr_bin_str){
	unsigned short int equivalentBinaryValue;

    char instr_bin_str_cp[20];
	
    strcpy(instr_bin_str_cp,instr_bin_str);
	
	equivalentBinaryValue=strtol(instr_bin_str_cp, NULL, 2);
	
    if(equivalentBinaryValue=='\0' && strlen(instr_bin_str_cp)!=7){
		printf("error6: str_to_bin() failed.");
		return 6;
	}
//     printf("0 =0x1201\n");
//     printf("1 =0x1449\n");
//     printf("2 =0x1691\n");
//     printf("3 =0x12DA\n");
//     printf("4 =0x5283\n");
//     printf("5 =0x52D3\n");
//     printf("6 =0x52DA\n");
    
    printf(" Binary Equivalent Test should match the up above %x\n", equivalentBinaryValue);
    return equivalentBinaryValue;

}

int write_obj_file (char* filename, unsigned short int program_bin[ROWS]) {
    
    unsigned short int labelOne = 0xCADE;
    unsigned short int labelTwo = 0x0000;
    unsigned short int labelThree = 0;
    char endOfFile = '\0';
    
    
    int len = strlen(filename);
    
    filename[len-1]= 'j';
    filename[len-2]= 'b';
    filename[len-3]= 'o';
   
    
    FILE *myfile = fopen(filename, "wb"); //write enable
    
    while(program_bin[labelThree] != endOfFile) {
        ++labelThree;
    };
    
    
    //ERROR CHECKS
    if(myfile == NULL) {
        printf("error7: write_obj_file() failed.\n");
        return 7;
    }
    
    if(fwrite(&labelOne, sizeof(unsigned short int), 1, myfile) == 0) {
        
        printf("error7: write_obj_file() failed.\n");
        return 7;
    }
    
    if(fwrite(&labelTwo, sizeof(unsigned short int), 1, myfile) == 0) {
     
        printf("error7: write_obj_file() failed.\n");
        return 7;
    }
    
  
    if(fwrite(&labelThree, sizeof(unsigned short int), 1, myfile) == 0) {
    
        printf("error7: write_obj_file() failed.\n");
        return 7;
    }
    
    if(fwrite(program_bin, sizeof(unsigned short int), labelThree, myfile) == 0) {
        printf("error7: write_obj_file() failed.\n");
        return 7;
    }
    
    
    fwrite(&labelOne, sizeof(unsigned short int), 1,myfile);
    fwrite(&labelTwo, sizeof(unsigned short int), 1,myfile);
    fwrite(&labelThree, sizeof(unsigned short int), 1,myfile);
    
    fclose(myfile);
    
    return 0;
    
    
}

