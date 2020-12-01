/***************************************************************************
 * file name   : assembler.c                                               *
 * author      : tjf & you                                                 *
 * description : This program will assemble a .ASM file into a .OBJ file   *
 *               This program will use the "asm_parser" library to achieve *
 *			     its functionality.										   * 
 *                                                                         *
 ***************************************************************************
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "asm_parser.h"

int main(int argc, char** argv) {

	char* filename = NULL ;					// name of ASM file
    
	char  program [ROWS][COLS] ; 			// ASM file line-by-line
	
    char  program_bin_str [ROWS][17] ; 		// instructions converted to a binary string
	
    unsigned short int program_bin [ROWS] ; // instructions in binary (HEX)
    
    char endOfFile = '\0';
    int numberRow = 0;

    ///////////////////////////////////////////////////////////////START
    //First thing to implement is to check if argc has arguments, and if it does, point “filename” to the argument
    //that contains the passed in string that is the file’s name
    
   
   if(argv[1] == NULL || argc <= 1) {
       printf("error1: usage: ./assembler <assembly_file.asm> \n");
       return 1;
   }
    
    
   if (argv[1] && argc >= 2) {
		filename = argv[1];
       
       printf("%s\n", filename);
	
	} else {
		printf("error1: usage: ./assembler <assembly_file.asm>\n");
		return 1;
	}
	
	// reading the asm file    
	
    if(read_asm_file(filename, program) ==0) {
            for(int f = 0; f < 100; ++f) {
                if(program[f][0] == endOfFile) {
                    break;
                }
            }
        
    } else if (read_asm_file(filename, program) ==2) {
        printf("error2: read_asm_file() failed.\n");
        return 2;
    } 
	
	
	
	while (program[numberRow][0] != endOfFile) {
		char *instr_bin_str = program_bin_str[numberRow];
        
        char *instr = program[numberRow];
		
		
		parse_instruction(instr, instr_bin_str);
		printf("%s \n", instr_bin_str);
		
        program_bin[numberRow] = str_to_bin(instr_bin_str);
		
		numberRow++;
	}
    
  
    
    //Write the obj file
    write_obj_file(filename, program_bin);
	
    
    return 0;
    
}