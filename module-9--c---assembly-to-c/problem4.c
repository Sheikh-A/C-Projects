/********************************************************
 * file name   : problem2.c                             *
 * author      : Thomas Farmer
 * description : C program to call LC4-Assembly TRAP_PUTC
 *               the TRAP is called through the wrapper 
 *               lc4putc() (located in lc4_stdio.asm)   *
 ********************************************************
*
*/

int main() {

	char ch_arr[3][10] = {
                         {'I', ' ', 'l', 'o', 'v', 'e', ' '},
                         {'C', 'I', 'T',' '},
                         {'5', '9', '3'}
                     };

	return (0) ;

}
