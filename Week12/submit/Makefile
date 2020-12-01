#########################################################
###########MAKE FILE#####################################
#########################################################
 
 
 
 
all: assembler

asm_parser.o: asm_parser.c
	clang -c asm_parser.c

assembler: assembler.c asm_parser.o
	clang assembler.c asm_parser.o -o assembler

clean:
	rm -rf *.o

clobber: clean
	rm -rf assembler
 
 
 
########################################################HW11
# all: program1 program2 program3

# my_string.o: my_string.c
# 		clang -c my_string.c 
	
# program1.o: program1.c
# 		clang -c program1.c

# program1: program1.o my_string.o
# 		clang my_string.o program1.o -o program1


# program2.o: program2.c
# 		clang -c program2.c
		
# program2: program2.o my_string.o
# 		clang my_string.o program2.o -o program2

# program3: program3.c 
# 		clang program3.c -o program3


# clean:
# 		rm -rf *.o

# clobber: clean
# 		rm -rf program1 program2  program3
############################################################